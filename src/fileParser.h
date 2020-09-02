#include <fstream>
#include <string>
#include "class.h"

/* Parses a class file into a Class object.
 * @param	{std::string} filePath. Path of the file from the cubeworld directory.
 * @return	{Class*}
*/
Class* ParseFile(std::string filePath) {
	static std::string separator("=");
	std::ifstream file(filePath);
	std::string line;

	if (!file.is_open()) {
		return nullptr;
	}

	Class* classInstance = new Class();

	std::getline(file, line);
	std::getline(file, line);

	auto index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	classInstance->id = std::stoi(line.substr(index + 1));

	std::getline(file, line);

	index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	std::string str = line.substr(index + 1);
	classInstance->name->replace(0, str.length(), str);

	std::getline(file, line);

	index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	classInstance->itemClass = std::stoi(line.substr(index + 1));

	std::getline(file, line);
	std::getline(file, line);

	index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	str = line.substr(index + 1);
	classInstance->specializations[0]->name->replace(0, str.length(), str);

	std::getline(file, line);

	index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	classInstance->specializations[0]->rAbility = std::stoi(line.substr(index + 1));

	std::getline(file, line);

	index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	int nr = std::stoi(line.substr(index + 1));
	classInstance->specializations[0]->cooldown = nr == -1 ? nr : 1000 * nr;

	std::getline(file, line);

	index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	classInstance->specializations[0]->shiftAbility = std::stoi(line.substr(index + 1));

	std::getline(file, line);
	std::getline(file, line);

	index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	str = line.substr(index + 1);
	classInstance->specializations[1]->name->replace(0, str.length(), str);

	std::getline(file, line);

	index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	classInstance->specializations[1]->rAbility = std::stoi(line.substr(index + 1));

	std::getline(file, line);

	index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	nr = std::stoi(line.substr(index + 1));
	classInstance->specializations[1]->cooldown = nr == -1 ? nr : 1000 * nr;

	std::getline(file, line);

	index = line.find(separator);
	if (index == std::string::npos) {
		delete classInstance;
		return nullptr;
	}
	classInstance->specializations[1]->shiftAbility = std::stoi(line.substr(index + 1));

	file.close();
	return classInstance;
}