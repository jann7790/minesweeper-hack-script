
#include "proc.h"


int main()
{
    
    DWORD procId = GetProcId(L"Winmine__XP.exe");

    uintptr_t moduleBase = GetModuleBaseAddress(procId, L"Winmine__XP.exe");

    cout << "addr:" << hex << "0x" << moduleBase<<endl;

    HANDLE hProcess = 0;

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    uintptr_t buffer = 0;
    uintptr_t initPtr = moduleBase + 0x5361;//left top
    uintptr_t mineNumPtr = moduleBase + 0x56A4;//mineNum
    uintptr_t mineNum = 0;
    
    ReadProcessMemory(hProcess, (byte*)mineNumPtr, &mineNum, 1, 0);
    cout << "mineNum:" << dec << mineNum << endl;
    
    int h = 0;
    int w = 0;
    switch (mineNum)
    {
    case 10:
        h = 9;
        w = 9;
        cout << h<< " "<<w<< endl;
        break;
    case 40:
        h = 16;
        w = 16;
        cout << h << " " << w << endl;
        break;
    case 99:
        h = 16;
        w = 30;
        cout << h << " " << w << endl;
        break;
    }
    uintptr_t initPtr2 = initPtr;

    for (size_t i = 0; i < h; i++)
    {
        for (size_t j = 0; j < w; j++)
        {
            ReadProcessMemory(hProcess, (byte*)initPtr, &buffer, 1, nullptr);
            if (buffer == 0x8f) {
                cout << "x ";
            }
            else
            {
                cout << "o ";
            }
            initPtr++;
        }
        initPtr = initPtr - w + 0x20;
        cout << endl;
    }

   initPtr = initPtr2;
   uintptr_t writingData = 0xE;
    for (size_t i = 0; i < h; i++)
    {
        for (size_t j = 0; j < w; j++)
        {
            ReadProcessMemory(hProcess, (byte*)initPtr, &buffer, 1, nullptr);
            if (buffer == 0x8f) {
                WriteProcessMemory(hProcess, (byte*)initPtr, &writingData, 1, nullptr);
            }
            initPtr++;
        }
        initPtr = initPtr - w + 0x20;
        cout << endl;
    }

    getchar();
}

