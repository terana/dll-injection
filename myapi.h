#pragma once

#ifdef DLL_TO_INJECT
#define MYAPI __declspec(dllexport) __stdcall
#else
#define MYAPI __declspec(dllimport) __stdcall
#endif

#define MYAPI_C extern "C"

MYAPI_C int MYAPI sum(int a, int b);