// 2022/1/17 19:45:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma warning(push, 0)
#pragma warning(disable : 4668)
#include <iostream>
#include <fstream>
#pragma warning(pop)


using namespace std;


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
        ifile.close();
    }
    else
    {
        cout << "ERROR !!! Input file " << argv[1] << ".bin" << " not found" << endl;
        return -1;
    }

    return 0;
}
