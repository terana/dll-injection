#include "pch.h"
#define DLL_TO_INJECT
#include "../myapi.h"

MYAPI_C int MYAPI sum(int a, int b)
{
    return a + b;
}

MYAPI_C int MYAPI mul(int a, int b)
{
    return a * b;
}