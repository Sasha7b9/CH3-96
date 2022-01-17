// 2022/1/16 17:01:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <ff.h>

#define TIME_WAIT   3000    // ����� ������ ��������


struct State
{
    enum E
    {
        Start,
        Mount,            // ������������ ������
        WrongFlash,       // ������ ����, �� ��������� ������
        RequestAction,    // ��� ������ - ���������� ��� ���
        NotFile,          // ���� ���� �������������, �� ���������� �� �� ����
        Upgrade,          // ������� ��������
        Ok                // ���������� ������ ���������
    };
};


class FDrive
{
    friend class CPU;

public:
    static void Init();

    // ������� ������� ����������
    static void AttemptUpdate();

    static bool FileExist(pchar fileName);

    // ��������� ���� ��� ������. ���������� ������ �����
    static int OpenFileForRead(FIL *file, pchar fileName);

    // ��������� �� ��������� ����� numBytes ����. ���������� ����� ������� ��������� ����
    static int ReadFromFile(FIL *file, int numBytes, uint8 *buffer);

    static void CloseOpenedFile(FIL *file);

    static void *GetHandleHCD();

    static void *GetHandleUSBH();

    static float PercentsUpdated();

    static State::E State();

    class LL_
    {
    public:
        static void InitHCD(void *phost);

        static void SetToggle(uint8 pipe, uint8 toggle);

        static uint8 GetToggle(uint8 pipe);
    };
};
