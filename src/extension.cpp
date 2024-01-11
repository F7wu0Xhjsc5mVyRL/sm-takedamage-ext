#include "extension.h"
#include "natives.h"

CExtension g_Extension;
SMEXT_LINK(&g_Extension);

IGameConfig *g_pGameConf = NULL;
IBinTools *g_pBinTools = NULL;

bool CExtension::SDK_OnLoad(char *error, size_t maxlength, bool late)
{
    char szError[255];
    if (!gameconfs->LoadGameConfigFile("takedamage.games", &g_pGameConf, szError, sizeof(szError)))
    {
        snprintf(error, maxlength, "Could not read takedamage.games: %s", szError);
        return false;
    }
    sharesys->AddNatives(myself, g_Natives);
    return true;
}

void CExtension::SDK_OnAllLoaded()
{
    SM_GET_LATE_IFACE(BINTOOLS, g_pBinTools);

    if (!g_pBinTools)
    {
        g_pSM->LogError(myself, "Could not find interface: "
        SMINTERFACE_BINTOOLS_NAME);
        return;
    }
}
