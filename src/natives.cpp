#include "extension.h"
#include "natives.h"
#include "takedamageinfohack.h"
#include <IBinTools.h>

class CBaseEntity;

cell_t Native_TakeDamage(IPluginContext *pContext, const cell_t *params)
{
    CBaseEntity *pVictim = gamehelpers->ReferenceToEntity(params[1]);
    if (!pVictim)
        return pContext->ThrowNativeError("Invalid entity index %d for victim", params[1]);

    CBaseEntity *pInflictor = gamehelpers->ReferenceToEntity(params[2]);
    if (!pInflictor)
        return pContext->ThrowNativeError("Invalid entity index %d for inflictor", params[2]);

    CBaseEntity *pAttacker;
    if (params[3] != -1)
    {
        pAttacker = gamehelpers->ReferenceToEntity(params[3]);
        if (!pAttacker)
        {
            return pContext->ThrowNativeError("Invalid entity index %d for attackerr", params[3]);
        }
    }
    else
    {
        pAttacker = NULL;
    }

    float flDamage = sp_ctof(params[4]);
    int iDamageType = params[5];

    CBaseEntity *pWeapon;
    if (params[6] != -1)
    {
        pWeapon = gamehelpers->ReferenceToEntity(params[6]);
        if (!pWeapon)
        {
            return pContext->ThrowNativeError("Invalid entity index %d for weapon", params[6]);
        }
    }
    else
    {
        pWeapon = NULL;
    }

    cell_t *addr;
    int err;
    if ((err = pContext->LocalToPhysAddr(params[7], &addr)) != SP_ERROR_NONE)
    {
        return pContext->ThrowNativeError("Could not read damageForce vector");
    }

    Vector vecDamageForce;
    if (addr != pContext->GetNullRef(SP_NULL_VECTOR))
    {
        vecDamageForce.Init(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));
    }
    else
    {
        vecDamageForce.Init();
    }

    if ((err = pContext->LocalToPhysAddr(params[8], &addr)) != SP_ERROR_NONE)
    {
        return pContext->ThrowNativeError("Could not read damagePosition vector");
    }

    Vector vecDamagePosition;
    if (addr != pContext->GetNullRef(SP_NULL_VECTOR))
    {
        vecDamagePosition.Init(sp_ctof(addr[0]), sp_ctof(addr[1]), sp_ctof(addr[2]));
    }
    else
    {
        vecDamagePosition = vec3_origin;
    }

    static ICallWrapper *pCall = NULL;
    if (!pCall)
    {
        int offset;
        if (!g_pGameConf->GetOffset("OnTakeDamage", &offset))
        {
            return pContext->ThrowNativeError("Could not find OnTakeDamage offset");
        }

        PassInfo pass[2];
        pass[0].type = PassType_Object;
        pass[0].size = sizeof(CTakeDamageInfoHack &);
        pass[0].flags = PASSFLAG_BYREF | PASSFLAG_OCTOR;
        pass[1].type = PassType_Basic;
        pass[1].size = sizeof(int);
        pass[1].flags = PASSFLAG_BYVAL;

        pCall = g_pBinTools->CreateVCall(offset, 0, 0, &pass[1], &pass[0], 1);
    }

    CTakeDamageInfoHack info(pInflictor, pAttacker, flDamage, iDamageType, pWeapon, vecDamageForce, vecDamagePosition);

    // Can't ArgBuffer here until we upgrade our Clang version on the Linux builder
    unsigned char vstk[sizeof(CBaseEntity *) + sizeof(CTakeDamageInfoHack &)];
    unsigned char *vptr = vstk;

    *(CBaseEntity **) vptr = pVictim;
    vptr += sizeof(CBaseEntity *);
    *(CTakeDamageInfoHack *&) vptr = info;

    int ret;
    pCall->Execute(vstk, &ret);

    return 0;
}

const sp_nativeinfo_t g_Natives[] =
        {
                {"CS_TakeDamage", Native_TakeDamage},
                {NULL,            NULL},
        };
