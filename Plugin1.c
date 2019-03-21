// Plugin1.c --- PluginFramework Plugin #1
// Copyright (C) 2019 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
// This file is public domain software.
#include "Plugin.h"
#include <assert.h>
#include <strsafe.h>

static HINSTANCE s_hinstDLL;

// API Name: Plugin_Load
// Purpose: The framework loads the plugin component.
// TODO: Load the plugin.
PLUGIN_API BOOL APIENTRY
Plugin_Load(PLUGIN *pi, LPARAM lParam)
{
    if (!pi)
    {
        assert(0);
        return FALSE;
    }
    if (pi->framework_version < FRAMEWORK_VERSION)
    {
        assert(0);
        return FALSE;
    }
    if (lstrcmpi(pi->framework_name, FRAMEWORK_NAME) != 0)
    {
        assert(0);
        return FALSE;
    }
    if (pi->framework_instance == NULL)
    {
        assert(0);
        return FALSE;
    }

    pi->plugin_version = 1;
    StringCbCopy(pi->plugin_product_name, sizeof(pi->plugin_product_name), TEXT("Plugin #1"));
    StringCbCopy(pi->plugin_filename, sizeof(pi->plugin_filename), TEXT("Plugin1.plugin"));
    StringCbCopy(pi->plugin_company, sizeof(pi->plugin_company), TEXT("Katayama Hirofumi MZ"));
    StringCbCopy(pi->plugin_copyright, sizeof(pi->plugin_copyright), TEXT("Copyright (C) 2019 Katayama Hirofumi MZ"));
    pi->plugin_instance = s_hinstDLL;
    pi->plugin_window = NULL;
    return TRUE;
}

// API Name: Plugin_Unload
// Purpose: The framework unloads the plugin component.
// TODO: Unload the plugin.
PLUGIN_API BOOL APIENTRY
Plugin_Unload(PLUGIN *pi, LPARAM lParam)
{
    return TRUE;
}

// API Name: Plugin_Act
// Purpose: Act something on the plugin.
// TODO: Act something on the plugin.
PLUGIN_API LRESULT APIENTRY
Plugin_Act(PLUGIN *pi, UINT uAct, WPARAM wParam, LPARAM lParam)
{
    switch (uAct)
    {
    case 1:
        printf("%d + %d = %d.\n", (int)wParam, (int)lParam, (int)wParam + (int)lParam);
        return (int)wParam + (int)lParam;
    case 2:
        printf("%d x %d = %d.\n", (int)wParam, (int)lParam, (int)wParam * (int)lParam);
        return (int)wParam * (int)lParam;
    }
    return 0;
}

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        s_hinstDLL = hinstDLL;
        DisableThreadLibraryCalls(hinstDLL);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
