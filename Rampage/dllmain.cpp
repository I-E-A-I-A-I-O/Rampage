// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include "main.h"
#include "MainScript.hpp"
#include "UIScript.hpp"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        scriptRegister(hModule, Rampage::on_start);
        scriptRegisterAdditionalThread(hModule, Rampage::UI::on_start);
        break;
    case DLL_PROCESS_DETACH:
        Rampage::on_abort();
        Rampage::UI::on_abort();
        scriptUnregister(hModule);
        break;
    }
    return TRUE;
}

