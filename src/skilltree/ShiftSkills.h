#pragma once

enum ShiftSkillType
{
	TELEPORT = 0,
	SMASH,
	SNEAK,
	SPRINT,
	SKILL_FLOAT,
	CYCLONE,
	FIRE_EXPLOSION,
	SHURIKEN,
	FLAME_RUSH,
	SHIFT_SKILL_TYPE_END,
};

static int SHIFT_SKILL_IDS[ShiftSkillType::SHIFT_SKILL_TYPE_END] =
{
	51,		//TELEPORT
	55,		//SMASH
	80,		//SNEAK
	81,		//SPRINT
	83,		//SKILL_FLOAT
	95,		//CYCLONE
	97,		//FIRE_EXPLOSION
	108,	//SHURIKEN
	146,	//FLAME_RUSH
};

// Todo: Assign costs
static int SHIFT_SKILL_COSTS[ShiftSkillType::SHIFT_SKILL_TYPE_END] =
{
	10,		//TELEPORT
	20,		//SMASH
	5,		//SNEAK
	1,		//SPRINT
	1,		//SKILL_FLOAT
	1,		//CYCLONE
	15,		//FIRE_EXPLOSION
	10,		//SHURIKEN
	5,		//FLAME_RUSH
};

static char* SHIFT_SKILL_NAMES[ShiftSkillType::SHIFT_SKILL_TYPE_END] =
{
	(char*)"TELEPORT",
	(char*)"SMASH",
	(char*)"SNEAK",
	(char*)"SPRINT",
	(char*)"FLOAT",
	(char*)"CYCLONE",
	(char*)"FIRE_EXPLOSION",
	(char*)"SHURIKEN",
	(char*)"FLAME_RUSH",
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