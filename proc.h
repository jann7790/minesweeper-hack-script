#pragma once
#include<iostream>
#include <Windows.h>
#include <vector>
#include <TlHelp32.h>

using namespace std;
DWORD GetProcId(const wchar_t* procName);

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modname);

uintptr_t FindDMAAddyy(HANDLE hproc, uintptr_t ptr, std::vector<unsigned int>offsets);

