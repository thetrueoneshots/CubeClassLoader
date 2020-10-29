#include "SkillTree.h"

// Todo: Implement
char* SkillTree::ToString()
{
	return nullptr;
}

// Todo: Implement
void SkillTree::Parse(char* source)
{
}

// Todo: Complete
void SkillTree::Reset(cube::Creature* creature)
{
	if (creature->gold < SKILL_TREE_RESET_COST) return;
	creature->gold -= SKILL_TREE_RESET_COST;
 	this->stats.ResetStats();
	this->ultimateSkills.ResetSkills();
}

// Todo: Implement
int SkillTree::GetUsedSkillPoints()
{
	int cnt = 0;
	cnt += this->stats.CountSkillPoints();
	cnt += this->ultimateSkills.CountSkillPoints();
	return cnt;
}
