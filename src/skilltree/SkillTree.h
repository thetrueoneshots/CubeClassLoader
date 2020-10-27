#pragma once
#include "stdlib.h"
#include "string.h"
#include "cwsdk.h"

#include "Stats.h"
class PassiveSkills
{

};
class ShiftSkills
{

};
class UltimateSkills 
{

};

enum SkillTreeType
{
	PASSIVES = 0,
	STATS,
	SHIFT_SKILLS,
	ULTIMATE_SKILLS,
};

static int SKILL_TREE_RESET_COST = 100;

class SkillTree
{
private:
	char* name;
public:
	PassiveSkills passives;
	Stats stats;
	ShiftSkills shiftSkills;
	UltimateSkills ultimateSkills;

	SkillTree(char* name) {
		//this->name = (char*) new char[((strlen(name) + 1) * sizeof(char))];
		//strncpy_s(this->name, strlen(name), name, strlen(name));
		//passives = PassiveSkills();
		//stats = Stats();
		//shiftSkills = ShiftSkills();
		//ultimateSkills = UltimateSkills();
	}

	~SkillTree() {
		delete name;
	}
	
	char* ToString();
	
	void Parse(char* source);
	
	void Reset(cube::Creature* creature);

	int GetUsedSkillPoints();
};