// 2022/1/17 19:45:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma warning(push, 0)
#pragma warning(disable : 4668)
#include <iostream>
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

    return 0;
}
