#pragma once
#include <vector>

class SkillTree {
	std::vector<std::pair<int, int>> skills;
	int selected;
public:
	SkillTree() {
		selected == -1;
	}

	void AddSkill(int skill, int cost) {
		skills.push_back(std::pair<int, int>(skill, cost));
	}

	int GetSize() {
		return skills.size();
	}

	int GetSelectedSkill() {
		if (selected == -1 || selected >= skills.size()) return -1;
		return skills.at(selected).first;
	}

	int GetSkillType(int i) {
		if (i < 0 || i >= skills.size()) return -1;
		return skills.at(i).first;
	}

	void SelectSkill(int i) {
		if (i < 0 || i >= skills.size()) return;
		selected = i;
	}
};