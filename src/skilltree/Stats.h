#pragma once
#include <limits.h>

/*
 * An enum for the different types of stats available.
 * Note: STAT_TYPE_END is not a valid StatType, but an indicator for the size and end of the amount of StatTypes.
*/
enum StatType
{
	FLAT_ARMOR = 0,
	SCALING_ARMOR,
	FLAT_RESISTANCE,
	SCALING_RESISTANCE,
	FLAT_HEALTH,
	SCALING_HEALTH,
	FLAT_DAMAGE,
	SCALING_DAMAGE,
	FLAT_SPELL_POWER,
	SCALING_SPELL_POWER,
	FLAT_CRIT,
	SCALING_CRIT,
	FLAT_HASTE,
	SCALING_HASTE,
	MANA_REGEN,
	STAMINA_REGEN,
	HEALTH_REGEN,
	MOVEMENT_SPEED,
	STAT_TYPE_END,
};

static char* STAT_NAMES[StatType::STAT_TYPE_END] =
{
	(char*)"FLAT_ARMOR",
	(char*)"SCALING_ARMOR",
	(char*)"FLAT_RESISTANCE",
	(char*)"SCALING_RESISTANCE",
	(char*)"FLAT_HEALTH",
	(char*)"SCALING_HEALTH",
	(char*)"FLAT_DAMAGE",
	(char*)"SCALING_DAMAGE",
	(char*)"FLAT_SPELL_POWER",
	(char*)"SCALING_SPELL_POWER",
	(char*)"FLAT_CRIT",
	(char*)"SCALING_CRIT",
	(char*)"FLAT_HASTE",
	(char*)"SCALING_HASTE",
	(char*)"MANA_REGEN",
	(char*)"STAMINA_REGEN",
	(char*)"HEALTH_REGEN",
	(char*)"MOVEMENT_SPEED",
};

/*
 * The modifiers of the stats. Done like this to maybe allow others to modify them.
 * Note: The 1 at position StatType::HEALTH_REGEN denotes 0.1%.
*/
static int STAT_MODIFIERS[StatType::STAT_TYPE_END] =
{
	1,	//  FLAT_ARMOR 
	3,	//  SCALING_ARMOR [%]
	1,	//  FLAT_RESISTANCE
	3,	//	SCALING_RESISTANCE [%]
	10,	//	FLAT_HEALTH
	1,	//	SCALING_HEALTH [%]
	2,	//	FLAT_DAMAGE
	4,	//	SCALING_DAMAGE [%]
	2,	//	FLAT_SPELL_POWER
	4,	//	SCALING_SPELL_POWER [%]
	1,	//	FLAT_CRIT [0.025]
	5,	//	SCALING_CRIT [%]
	1,	//	FLAT_HASTE
	5,	//	SCALING_HASTE [%]
	5,	//	MANA_REGEN [%]
	5,	//	STAMINA_REGEN [%]
	1,	//	HEALTH_REGEN [0.01 % (per game tick)]
	100	//	MOVEMENT_SPEED [%]
};			

/*
 * The maximum levels that a stat can reach.
*/
static int STAT_MAX_LEVELS[StatType::STAT_TYPE_END] =
{
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX,
	INT_MAX, // Todo: Reconsider changing Mana Regen max level
	INT_MAX, // Todo: Reconsider changing Stamina Regen max level
	20,
	15,
};

/*
 * Class that contains all the stat levels of the skill tree.
*/
class Stats
{
private:
	int levels[StatType::STAT_TYPE_END] = { 0 };

public:
	int GetStatLevel(StatType type);
	void IncreaseStat(StatType type);
	void ResetStats();
	char* ToString();
	void Parse(char* source);
	int CountSkillPoints();
}; 