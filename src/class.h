#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include "skillTree.h"

class Class
{
	void Initialize() {
		specializations.push_back(new Specialization());
		specializations.push_back(new Specialization());
		skillTree = SkillTree();
		skillTree.AddSkill(148, 1);
		skillTree.AddSkill(47, 2);
	}
public:

	class Specialization 
	{
	public:
		std::string* name;
		int rAbility;
		int cooldown;
		int shiftAbility;

		Specialization() {
			name = new std::string();
			rAbility = 100;
			cooldown = 5000;
			shiftAbility = 100;
		}

		// Todo: Rewrite to receive char*
		Specialization(Specialization* temp, std::string* tempName) {
			name = new std::string(tempName->begin(), tempName->end());
			rAbility = temp->rAbility;
			cooldown = temp->cooldown;
			shiftAbility = temp->shiftAbility;
		}

		~Specialization() {
			delete name;
		}

		std::string ToString();
	};

	int id;
	std::string* name;
	int itemClass;
	std::vector<Specialization*> specializations;
	SkillTree skillTree;

	Class() {
		id = 0;
		itemClass = 1;
		name = new std::string();
		Initialize();
	}

	// Todo: Rewrite to receive char*
	Class(Class* temp, std::string* tempName) {
		id = temp->id;
		itemClass = temp->itemClass;
		name = new std::string(tempName->begin(), tempName->end());
		Initialize();
	}

	~Class() {
		delete name;
		for (auto i = 0; i < specializations.size(); i++) {
			delete specializations.at(i);
		}
	}

	std::string ToString();
};

/* Gets a new unique id, not assigned to a class yet.
 * Returns -1 if no id is found.
 * @param {std::vector<Class*>} classVector All the already existing custom classes.
 * @return {int}
 */
static int GetUniqueClassId(std::vector<Class*> classVector) {
	int id = -1;
	for (int i = 1; i <= 28; i++) {
		bool found = false;
		for (Class* classInstance : classVector) {
			if (classInstance->id != i) continue;
			found = true;
		}

		if (found) continue;

		id = i;
		break;
	}
	return id;
}