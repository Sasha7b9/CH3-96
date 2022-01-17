// 2022/1/16 17:01:44 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/FDrive.h"
#include "Hardware/HAL/HAL.h"
#include "Hardware/HAL/FLASH.h"
#include <usbh_diskio.h>
#include <ctype.h>
#include <ffconf.h>


#define FILE_FIRMWARE "CH3-96.bin"
#define FILE_CHECKSUM "CH3-96.crc32"
#define FILE_CLEAR    "clear.txt"


struct StructForReadDir
{
    char nameDir[_MAX_LFN + 1];
    char lfn[(_MAX_LFN + 1)];
    FILINFO fno;
    DIR dir;
};


struct StateDisk
{
    enum E
    {
        Idle,
        Start
    };
};

static HCD_HandleTypeDef handleHCD;

static USBH_HandleTypeDef handleUSBH;

// ������� ��������� ����� ����������
static float percentsUpdate = 0.0F;

// ��������� ������
static State::E state = State::Start;

static FATFS        USBDISKFatFS;
static char         USBDISKPath[4];
static StateDisk::E stateDisk;
static int          connection;
static int          active;


static bool GetNameFile(pchar fullPath, int numFile, char *nameFileOut, StructForReadDir *s);
static bool GetNextNameFile(char *nameFileOut, StructForReadDir *s);
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8 id);
static bool Process();

void *FDrive::GetHandleHCD()
{
    return &handleHCD;
}


void *FDrive::GetHandleUSBH()
{
    return &handleUSBH;
}


void FDrive::Init()
{
    stateDisk = StateDisk::Idle;
    connection = 0;
    active = 0;

    if(FATFS_LinkDriver(&USBH_Driver, USBDISKPath) == FR_OK)
    {
        USBH_StatusTypeDef res = USBH_Init(&handleUSBH, USBH_UserProcess, 0);
        res = USBH_RegisterClass(&handleUSBH, USBH_MSC_CLASS);
        res = USBH_Start(&handleUSBH);
    }
}



void USBH_UserProcess(USBH_HandleTypeDef *, uint8 id)
{
    switch(id)
    {
    case HOST_USER_SELECT_CONFIGURATION:
        break;

    case HOST_USER_CLASS_ACTIVE:
        active++;
        stateDisk = StateDisk::Start;
        break;

    case HOST_USER_CLASS_SELECTED:
        break;

    case HOST_USER_CONNECTION:
        connection++;
        state = State::Mount;
        f_mount(NULL, static_cast<TCHAR const *>(""), 0);
        break;

    case HOST_USER_DISCONNECTION:
        break;

    default:
        // ������ �� ������
        break;
    }
}



void FDrive::AttemptUpdate()
{
    uint timeStart = TIME_MS;

    while(TIME_MS - timeStart < TIME_WAIT && !Process())
    {
    }

    if((connection != 0 && active == 0) ||      // ���� ����� ����������, �� � �������� ��������� ������-�� �� �������
        (active != 0 && state != State::Mount)) // ��� ������� � �������� ���������, �� ������-�� �� ���������� ������� ������������
    {
        HAL_NVIC_SystemReset();
    }

    if(state == State::Mount)                   // ��� ��������, ��� ���� ������ �������������
    {
        if(FileExist(FILE_CLEAR))
        {
            EraseSettings();
        }

        for (int i = 0; i < 10; i++)            // ������� ������� ����� ������, ��� ����� �������� USB � �����������.
        {                                       // ���������������� ��-�� ������� �����
            if (FileExist(FILE_FIRMWARE))       // ���� �� ����� ���������� ��������
            {
                if (Upgrade())
                {
                    break;
                }
            }
        }
    }
    else if(state == State::WrongFlash)         // ���� �� ������� ��������������
    {
        HAL_TIM::DelayMS(5000);
    }

    state = State::Ok;
}



static bool Process()
{
    USBH_Process(&handleUSBH);
    if(stateDisk == StateDisk::Start)
    {
        if(f_mount(&(USBDISKFatFS), static_cast<TCHAR const *>(USBDISKPath), 0) == FR_OK)
        {
            return true;
        }
        else
        {
            state = State::WrongFlash;
            return false;
        }
    }
    return false;
}



static void ToLower(char *str)
{
    while(*str)
    {
        *str = static_cast<char>(tolower(*str));
        str++;
    }
}



bool FDrive::FileExist(pchar fileName)
{
    char nameFile[255];
    char f[255];
    strcpy(f, fileName);
    ToLower(f);
    StructForReadDir strd;

    if(GetNameFile("\\", 0, nameFile, &strd))
    {
        ToLower(nameFile);
        if(strcmp(f, nameFile) == 0)
        {
            return true;
        }
        while(GetNextNameFile(nameFile, &strd))
        {
            ToLower(nameFile);
            if(strcmp(f, nameFile) == 0)
            {
                return true;
            }
        }
    }

    return false;
}



static bool GetNameFile(pchar fullPath, int numFile, char *nameFileOut, StructForReadDir *s)
{
    memcpy(reinterpret_cast<uint8 *>(s->nameDir), const_cast<char *>(fullPath), strlen(fullPath)); //-V2567
    s->nameDir[strlen(fullPath)] = '\0';

    DIR *pDir = &s->dir;
    FILINFO *pFNO = &s->fno;
    if(f_opendir(pDir, s->nameDir) == FR_OK)
    {
        int numFiles = 0;
        bool alreadyNull = false;
        while(true)
        {
            if(f_readdir(pDir, pFNO) != FR_OK)
            {
                *nameFileOut = '\0';
                f_closedir(pDir);
                return false;
            }
            if(pFNO->fname[0] == 0)
            {
                if(alreadyNull)
                {
                    *nameFileOut = '\0';
                    f_closedir(pDir);
                    return false;
                }
                alreadyNull = true;
            }
            if(numFile == numFiles && (pFNO->fattrib & AM_DIR) == 0)
            {
                strcpy(nameFileOut, pFNO->fname);
                return true;
            }
            if((pFNO->fattrib & AM_DIR) == 0 && (pFNO->fname[0] != '.'))
            {
                numFiles++;
            }
        }
    }
    return false;
}



static bool GetNextNameFile(char *nameFileOut, StructForReadDir *s)
{
    FILINFO *pFNO = &s->fno;
    bool alreadyNull = false;
    while(true)
    {
        if(f_readdir(&s->dir, &s->fno) != FR_OK)
        {
            *nameFileOut = '\0';
            f_closedir(&s->dir);
            return false;
        }
        if(s->fno.fname[0] == 0)
        {
            if(alreadyNull)
            {
                *nameFileOut = '\0';
                f_closedir(&s->dir);
                return false;
            }
            alreadyNull = true;
        }
        else
        {
            if((pFNO->fattrib & AM_DIR) == 0 && pFNO->fname[0] != '.')
            {
                strcpy(nameFileOut, pFNO->fname);
                return true;
            }
        }
    }
}


int FDrive::OpenForRead(FIL *file, pchar fileName)
{
    if(f_open(file, fileName, FA_READ) == FR_OK)
    {
        return (int)f_size(file);
    }
    return -1;
}


int FDrive::Read(FIL *file, int numBytes, void *buffer)
{
    uint readed = 0;
    if(f_read(file, buffer, static_cast<UINT>(numBytes), &readed) == FR_OK)
    {
        return static_cast<int>(readed);
    }
    return -1;
}


void FDrive::Close(FIL *file)
{
    f_close(file);
}


void FDrive::LL_::InitHCD(void *host)
{
    USBH_HandleTypeDef *phost = static_cast<USBH_HandleTypeDef *>(host);

    handleHCD.Instance = USB_OTG_FS;
    handleHCD.Init.speed = HCD_SPEED_HIGH;
    handleHCD.Init.Host_channels = 12;
    handleHCD.Init.dma_enable = 0;
    handleHCD.Init.low_power_enable = 0;
    handleHCD.Init.phy_itface = HCD_PHY_EMBEDDED;
    handleHCD.Init.Sof_enable = 0;
    handleHCD.Init.vbus_sensing_enable = 0;
    handleHCD.Init.use_external_vbus = 0;

    handleHCD.pData = phost;
    phost->pData = &handleHCD;

    HAL_HCD_Init(&handleHCD);

    USBH_LL_SetTimer(phost, HAL_HCD_GetCurrentFrame(&handleHCD));
}


void FDrive::LL_::SetToggle(uint8 pipe, uint8 toggle)
{
    if(handleHCD.hc[pipe].ep_is_in)
    {
        handleHCD.hc[pipe].toggle_in = toggle;
    }
    else
    {
        handleHCD.hc[pipe].toggle_out = toggle;
    }
}


uint8 FDrive::LL_::GetToggle(uint8 pipe)
{
    uint8 toggle = 0;

    if(handleHCD.hc[pipe].ep_is_in)
    {
        toggle = handleHCD.hc[pipe].toggle_in;
    }
    else
    {
        toggle = handleHCD.hc[pipe].toggle_out;
    }
    return toggle;
}


void FDrive::EraseSettings()
{
    HAL_EEPROM::EraseSector(0x080C0000);
}


bool FDrive::ReadChecksums(FIL *file, uint sums[128])
{
    Close(file);

    OpenForRead(file, FILE_CHECKSUM);

    int size = 0;

    Read(file, 4, &size);

    for (int i = 0; i < 128; i++)
    {
        if (Read(file, 4, &sums[i]) == -1)
        {
            break;
        }
    }

    Close(file);

    OpenForRead(file, FILE_CHECKSUM);

    Read(file, 4, &size);

    for (int i = 0; i < 128; i++)
    {
        uint hash = 0;

        if (Read(file, 4, &hash) == -1)
        {
            break;
        }

        if (sums[i] != hash)
        {
            return false;
        }
    }

    return true;
}


bool FDrive::Upgrade()
{
    FIL fFirmware;
    FIL fChecksum;

    bool result = false;

    if (FDrive::OpenForRead(&fChecksum, FILE_CHECKSUM) <= 0)
    {
        goto ExitUpgrade;
    }

    int size = 0;

    FDrive::Read(&fChecksum, 4, &size);                             // ��������� ������ �����

    if (size != FDrive::OpenForRead(&fFirmware, FILE_FIRMWARE))     // ���� �� �� ������������� ������� ����� � ���������
    {
        goto ExitUpgrade;
    }

    FLASH_::Prepare();

    int num_zones = size / 1024;

    if ((size % 1024) != 0)
    {
        num_zones++;
    }

    int last_bytes = size;

    while (last_bytes)
    {
        int num_zone = 0;

        int size_zone = (last_bytes < 1024) ? last_bytes : 1024;

        uint8 zone[1024];

        ReadZone(&fChecksum, &fFirmware, num_zone, size_zone, zone);

        FLASH_::WriteData(FLASH_::ADDR_SECTOR_PROGRAM_TEMP + num_zone * 1024, zone, size_zone);

        num_zone++;

        last_bytes -= size_zone;
    }

    HAL_EEPROM::EraseSector(FLASH_::ADDR_SECTOR_PROGRAM_0);

    FLASH_::WriteData(FLASH_::ADDR_SECTOR_PROGRAM_0, (void *)FLASH_::ADDR_SECTOR_PROGRAM_TEMP, size);

    result = true;

ExitUpgrade:

    FDrive::Close(&fFirmware);
    FDrive::Close(&fChecksum);

    return result;
}


float FDrive::PercentsUpdated()
{
    return percentsUpdate;
}


State::E FDrive::State()
{
    return state;
}
