// 2022/1/17 19:45:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma warning(push, 0)
#pragma warning(disable : 4668)
#include <iostream>
#include <fstream>
#pragma warning(pop)


using namespace std;


static unsigned int CalculateCRC32(char *buffer, int size)
{
    unsigned int result = 0;

    while (size--)
    {
        result += *buffer++;
    }

    return result;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Using :" << endl;
        cout << "        checsum input_file.bin" << endl;
        return -1;
    }

    ifstream ifile;
    ifile.open(string(argv[1]) + ".bin", ios::in | ios::binary);

    if (ifile.is_open())
    {
        ofstream ofile;
        ofile.open(string(argv[1]) + ".crc32", ios::out | ios::trunc);

        ifile.seekg(0, ifile.end);
        int length = (int)ifile.tellg();
        ifile.seekg(0, ifile.beg);

        while(length)
        {
            cout << length << endl;

            char buffer[1024];

            int read_bytes = (length < 1024) ? length : 1024;

            length -= read_bytes;

            ifile.read(buffer, read_bytes);

            ofile << read_bytes << " " << CalculateCRC32(buffer, read_bytes) << endl;
        }

        ofile.close();
        ifile.close();
    }
    else
    {
        cout << "ERROR !!! Input file " << argv[1] << ".bin" << " not found" << endl;
        return -1;
    }

    return 0;
}
