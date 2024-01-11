#if defined _takedamage_included
  #endinput
#endif
#define _takedamage_included

#include <sdkhooks>

/**
 * @brief Applies damage to an entity
 *
 * @note Force application is dependent on game and damage type(s)
 *
 * @param    entity         Entity index taking damage
 * @param    inflictor      Inflictor entity index
 * @param    attacker       Attacker entity index
 * @param    damage         Amount of damage
 * @param    damageType     Bitfield of damage types
 * @param    weapon         Weapon index (orangebox and later) or -1 for unspecified
 * @param    damageForce    Velocity of damage force
 * @param    damagePosition Origin of damage
 * @noreturn
 */
native CS_TakeDamage(entity, inflictor, attacker, Float:damage, damageType=DMG_GENERIC, weapon=-1, const Float:damageForce[3]=NULL_VECTOR, const Float:damagePosition[3]=NULL_VECTOR);

/**
 * Do not edit below this line!
 */
public Extension:__ext_takedamage = 
{
	name = "TakeDamage",
	file = "takedamage.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};
