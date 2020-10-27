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
}

// Todo: Implement
int SkillTree::GetUsedSkillPoints()
{
	return 0;
}
