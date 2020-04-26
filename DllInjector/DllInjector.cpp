// DllInjector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "windows.h"
#include <stdio.h>
#include "../myapi.h"

int main()
{
    auto r = sum(2, 3);
    printf("sum returns %d \n", r);

    const auto hLibrary = LoadLibraryW(L"DllToInject.dll");
    if (nullptr == hLibrary)
    {
        printf("LoadLibraryW returns %lu \n", GetLastError());
    }
    const auto pMul = reinterpret_cast<PFN_mul>(GetProcAddress(hLibrary, "_mul@8"));
    if (nullptr == pMul)
    {
        printf("GetProcAddress returns %lu \n", GetLastError());
    }
    r = pMul(2, 3);
    printf("mul returns %d \n", r);

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
