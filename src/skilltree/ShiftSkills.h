#pragma once

enum ShiftSkillType
{
	SHIFT_FIRE_MISSLES = 0,
	SHIFT_TELEPORT,
	SHIFT_BURROW,
	SHIFT_LAVA_PUDDLE,
	SHIFT_MULTI_SLAM,
	SHIFT_CAMOUFLAGE,
	SHIFT_NINJUTSU,
	SHIFT_QUICKSAND_TRAP,
	SHIFT_SHADOW_SHOOTER,
	SHIFT_WATER_BUBBLES,
	SHIFT_ROCK_FIST,
	SHIFT_HEROIC_SHOUT,
	SHIFT_POISION_VIAL,
	SHIFT_SKILL_TYPE_END,
};

static int SHIFT_SKILL_IDS[ShiftSkillType::SHIFT_SKILL_TYPE_END] =
{
	47,		//FIRE_MISSLES
	51,		//TELEPORT
	72,		//BURROW
	98,		//LAVA_PUDDLE
	100,	//MULTI_SLAM
	109,	//CAMOUFLAGE
	141,	//NINJUTSU		
	142,	//QUICKSAND_TRAP
	143,	//SHADOW_SHOOTER
	144,	//WATER_BUBBLES
	148,	//ROCK_FIST
	149,	//HEROIC_SHOUT
	160,	//POISION_VIAL
};

static int SHIFT_SKILL_COSTS[ShiftSkillType::SHIFT_SKILL_TYPE_END] =
{
	10,		//FIRE_MISSLES
	1,		//TELEPORT
	5,		//BURROW
	5,		//LAVA_PUDDLE
	10,		//MULTI_SLAM
	5,		//CAMOUFLAGE
	5,		//NINJUTSU
	5,		//QUICKSAND_TRAP
	5,		//SHADOW_SHOOTER
	1,		//WATER_BUBBLES
	10,		//ROCK_FIST
	5,		//HEROIC_SHOUT
	1,		//POISION_VIAL
};

static char* SHIFT_SKILL_NAMES[ShiftSkillType::SHIFT_SKILL_TYPE_END] =
{
	(char*)"FIRE_MISSLES",
	(char*)"TELEPORT",
	(char*)"BURROW",
	(char*)"LAVA_PUDDLE",
	(char*)"MULTI_SLAM",
	(char*)"CAMOUFLAGE",
	(char*)"NINJUTSU",
	(char*)"QUICKSAND_TRAP",
	(char*)"SHADOW_SHOOTER",
	(char*)"WATER_BUBBLES",
	(char*)"ROCK_FIST",
	(char*)"HEROIC_SHOUT",
	(char*)"POISION_VIAL",
};

class ShiftSkills
{
private:
	ShiftSkillType selectedSkill = ShiftSkillType::SHIFT_SKILL_TYPE_END;
	int unlocks[ShiftSkillType::SHIFT_SKILL_TYPE_END] = { 0 };
public:
	void UnlockSkill(ShiftSkillType type, int availablePoints);
	bool IsSkillUnlocked(ShiftSkillType type);
	ShiftSkillType GetSelectedSkill();
	void SelectSkill(ShiftSkillType type);
	void ResetSkills();
	char* ToString();
	void Parse(char* source);
	int CountSkillPoints();
};