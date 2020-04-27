// DllInjector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "windows.h"
#include <stdio.h>
#include "../myapi.h"

void TestStaticImport()
{
    const auto r = sum(2, 3);
    printf("sum returns %d \n", r);
}

HMODULE TestDirectLoadLibarary()
{
    const auto hLibrary = LoadLibraryW(L"DllToInject.dll");
    if (nullptr == hLibrary)
    {
        printf("LoadLibraryW failed %lu \n", GetLastError());
    }
    return hLibrary;
}

HMODULE TestLocalThreadLoadLibrary32()
{
    DWORD tid, exitCode;
    const auto pLoadLibraryW = reinterpret_cast<LPTHREAD_START_ROUTINE>(&LoadLibraryW);
    auto lpParameter = const_cast<wchar_t*>(L"DllToInject.dll");
    const auto hThread = CreateThread(nullptr, 0, pLoadLibraryW, lpParameter, 0, &tid);
    if (nullptr == hThread)
    {
        printf("CreateThread failed %lu \n", GetLastError());
        return nullptr;
    }
    WaitForSingleObject(hThread, INFINITE);
    GetExitCodeThread(hThread, &exitCode);
    CloseHandle(hThread);
#ifndef WIN64
    return reinterpret_cast<HMODULE>(exitCode); //32-bit only magic
#else
    return nullptr;
#endif
}

void TestDynamicImport(HMODULE hLibrary)
{
    if (nullptr == hLibrary) return;
    const auto pMul = reinterpret_cast<PFN_mul>(GetProcAddress(hLibrary, "_mul@8"));
    if (nullptr == pMul)
    {
        printf("GetProcAddress failed %lu \n", GetLastError());
    }
    const auto r = pMul(2, 3);
    printf("mul returns %d \n", r);
}

int main()
{
    TestStaticImport();
    TestDynamicImport(TestDirectLoadLibarary());
    TestDynamicImport(TestLocalThreadLoadLibrary32());

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
