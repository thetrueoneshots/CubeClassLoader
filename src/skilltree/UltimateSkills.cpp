#include "UltimateSkills.h"

void UltimateSkills::UnlockSkill(UltimateType type, int availablePoints)
{
	if (type < 0 || type >= UltimateType::ULTIMATE_SKILL_TYPE_END) return;
	if (availablePoints < ULTIMATE_COSTS[type]) return;
	unlocks[type] = 1;
}

bool UltimateSkills::IsSkillUnlocked(UltimateType type)
{
	if (type < 0 || type >= UltimateType::ULTIMATE_SKILL_TYPE_END) return false;
	return unlocks[type] == 1;
}

UltimateType UltimateSkills::GetSelectedSkill()
{
	return selectedSkill;
}

void UltimateSkills::SelectSkill(UltimateType type)
{
	if (type < 0 || type >= UltimateType::ULTIMATE_SKILL_TYPE_END) return;
	if (unlocks[type] != 1) return;
	selectedSkill = type;
}

void UltimateSkills::ResetSkills()
{
	for (int i = 0; i < UltimateType::ULTIMATE_SKILL_TYPE_END; i++)
	{
		unlocks[i] = 0;
	}
}

// Todo: Implement
char* UltimateSkills::ToString()
{
	return nullptr;
}

// Todo: Implement
void UltimateSkills::Parse(char* source)
{
	return;
}

int UltimateSkills::CountSkillPoints()
{
	int cnt = 0;
	for (int i = 0; i < UltimateType::ULTIMATE_SKILL_TYPE_END; i++)
	{
		if (unlocks[i] == 1)
		{
			cnt += ULTIMATE_COSTS[i];
		}
	}
	return cnt;
}
