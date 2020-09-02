#include "class.h"
#include <string>

std::string Class::ToString()
{
	std::string str = std::string("Id: ");
	str += std::to_string(this->id);
	str += ", Name: ";
	str += *this->name;
	str += "\n";
	for (auto i = 0; i < this->specializations.size(); i++) {
		str += this->specializations.at(i)->ToString();
		str += "\n";
	}
	str += "\n";
	return str;
}

std::string Class::Specialization::ToString()
{
	std::string str("Specialization: \n Name: ");
	str += *this->name;
	str += ", R: ";
	str += std::to_string(this->rAbility);
	str += ", SHIFT: ";
	str += std::to_string(this->shiftAbility);
	return str;
}
