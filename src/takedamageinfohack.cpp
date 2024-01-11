#include "takedamageinfohack.h"

CTakeDamageInfo::CTakeDamageInfo()
{}

CTakeDamageInfoHack::CTakeDamageInfoHack(CBaseEntity *pInflictor, CBaseEntity *pAttacker, float flDamage,
                                         int bitsDamageType, CBaseEntity *pWeapon, Vector vecDamageForce,
                                         Vector vecDamagePosition)
{
    m_hInflictor = pInflictor;
    if (pAttacker)
    {
        m_hAttacker = pAttacker;
    }
    else
    {
        m_hAttacker = pInflictor;
    }

#if SOURCE_ENGINE >= SE_ORANGEBOX && SOURCE_ENGINE != SE_LEFT4DEAD
    m_hWeapon = pWeapon;
#endif

    m_flDamage = flDamage;

    m_flBaseDamage = BASEDAMAGE_NOT_SPECIFIED;

    m_bitsDamageType = bitsDamageType;

    m_flMaxDamage = flDamage;
    m_vecDamageForce = vec3_origin;
    m_vecDamagePosition = vec3_origin;
    m_vecReportedPosition = vec3_origin;
    m_iAmmoType = -1;

#if SOURCE_ENGINE < SE_ORANGEBOX
    m_iCustomKillType = 0;
#else
    m_iDamageCustom = 0;
#endif

#if SOURCE_ENGINE == SE_CSS || SOURCE_ENGINE == SE_HL2DM || SOURCE_ENGINE == SE_DODS || SOURCE_ENGINE == SE_SDK2013 || SOURCE_ENGINE == SE_TF2
    m_iDamagedOtherPlayers = 0;
    m_iPlayerPenetrationCount = 0;
    m_flDamageBonus = 0.0f;
    m_bForceFriendlyFire = false;
#endif

#if SOURCE_ENGINE >= SE_ALIENSWARM
    m_flRadius = 0.0f;
#endif

#if SOURCE_ENGINE == SE_INSURGENCY || SOURCE_ENGINE == SE_CSGO
    m_iDamagedOtherPlayers = 0;
    m_iObjectsPenetrated = 0;
    m_uiBulletID = 0;
    m_uiRecoilIndex = 0;
#endif
}
