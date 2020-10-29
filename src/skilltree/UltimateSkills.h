#pragma once
// Todo: Add cooldown to burrow
enum UltimateType
{
	FIRE_MISSLES = 0,
	BURROW,
	LAVA_PUDDLE,
	MULTI_SLAM,
	CAMOUFLAGE,
	NINJUTSU,
	QUICKSAND_TRAP,
	SHADOW_SHOOTER,
	WATER_BUBBLES,
	ROCK_FIST,
	HEROIC_SHOUT,
	POISION_VIAL,
	ULTIMATE_SKILL_TYPE_END,
};

static int ULTIMATE_IDS[UltimateType::ULTIMATE_SKILL_TYPE_END] =
{
	47,		//FIRE_MISSLES
	130,	//BURROW
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
		
static int ULTIMATE_COSTS[UltimateType::ULTIMATE_SKILL_TYPE_END] =
{
	10,		//FIRE_MISSLES
	15,		//BURROW
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

static char* ULTIMATE_NAMES[UltimateType::ULTIMATE_SKILL_TYPE_END] =
{
	(char*)"FIRE_MISSLES",
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

class UltimateSkills
{
private:
	UltimateType selectedSkill = UltimateType::ULTIMATE_SKILL_TYPE_END;
	int unlocks[UltimateType::ULTIMATE_SKILL_TYPE_END] = { 0 };
public:
	void UnlockSkill(UltimateType type, int availablePoints);
	bool IsSkillUnlocked(UltimateType type);
	UltimateType GetSelectedSkill();
	void SelectSkill(UltimateType type);
	void ResetSkills();
	char* ToString();
	void Parse(char* source);
	int CountSkillPoints();
};