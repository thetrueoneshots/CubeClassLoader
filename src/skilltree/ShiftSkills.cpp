#include "ShiftSkills.h"

void ShiftSkills::UnlockSkill(ShiftSkillType type, int availablePoints)
{
	if (type < 0 || type >= ShiftSkillType::SHIFT_SKILL_TYPE_END) return;
	if (availablePoints < SHIFT_SKILL_COSTS[type]) return;
	unlocks[type] = 1;
}

bool ShiftSkills::IsSkillUnlocked(ShiftSkillType type)
{
	if (type < 0 || type >= ShiftSkillType::SHIFT_SKILL_TYPE_END) return false;
	return unlocks[type] == 1;
}

ShiftSkillType ShiftSkills::GetSelectedSkill()
{
	return selectedSkill;
}

void ShiftSkills::SelectSkill(ShiftSkillType type)
{
	if (type < 0 || type >= ShiftSkillType::SHIFT_SKILL_TYPE_END) return;
	if (unlocks[type] != 1) return;
	selectedSkill = type;
}

void ShiftSkills::ResetSkills()
{
	for (int i = 0; i < ShiftSkillType::SHIFT_SKILL_TYPE_END; i++)
	{
		unlocks[i] = 0;
	}
}

// Todo: Implement
char* ShiftSkills::ToString()
{
	return nullptr;
}

// Todo: Implement
void ShiftSkills::Parse(char* source)
{
	return;
}

int ShiftSkills::CountSkillPoints()
{
	int cnt = 0;
	for (int i = 0; i < ShiftSkillType::SHIFT_SKILL_TYPE_END; i++)
	{
		if (unlocks[i] == 1)
		{
			cnt += SHIFT_SKILL_COSTS[i];
		}
	}
	return cnt;
}
