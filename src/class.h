#pragma once
#include <iostream>
#include <windows.h>
#include <vector>

class Class
{
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

		~Specialization() {
			delete name;
		}

		std::string ToString();
	};

	int id;
	std::string* name;
	int itemClass;
	std::vector<Specialization*> specializations;

	Class() {
		id = 0;
		itemClass = 1;
		name = new std::string();
		specializations.push_back(new Specialization());
		specializations.push_back(new Specialization());
	}

	~Class() {
		delete name;
		for (auto i = 0; i < specializations.size(); i++) {
			delete specializations.at(i);
		}
	}

	std::string ToString();
};