#pragma once
#include <vector>
#include <string>
#include <map>
#include "class.h"

std::vector<Class*> classVector;
std::vector<int>* cooldownMap;

void Popup(const char* title, const char* msg) {
	MessageBoxA(0, msg, title, MB_OK | MB_ICONINFORMATION);
}

void SetCooldown(std::vector<int> ids, int cooldown) {
	for (auto i = 0; i < ids.size(); i++) {
		cooldownMap->at(ids[i]) = cooldown;
	}
}

// Todo: Read the strings as char* and create std::strings out of that.
// [Note: j should probably increase with strlen(char*)]
void LoadClasses() {
	char* blocks;
	std::streampos fsize;

	char fileName[256] = { 0 };
	const char* folderName = "Mods\\Classes";

	CreateDirectory(folderName, NULL);
	sprintf(fileName, "%s\\save.cwb", folderName);
	std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()) {
		//File exists, read it
		fsize = file.tellg();
		blocks = new char[fsize];
		file.seekg(0, std::ios::beg);
		file.read(blocks, fsize);
		file.close();

		int stepSize = sizeof(Class) + 2 * sizeof(Class::Specialization) + 3 * sizeof(std::string);
		for (int i = 0; i < fsize; i += stepSize) {
			int j = i;
			Class* temp = (Class*)&blocks[j];
			j += sizeof(Class);
			std::string* name = (std::string*)&blocks[j];
			j += sizeof(*name);
			Class::Specialization* spec1 = (Class::Specialization*)&blocks[j];
			j += sizeof(Class::Specialization);
			std::string* spec1Name = (std::string*)&blocks[j];
			j += sizeof(*spec1Name);
			Class::Specialization* spec2 = (Class::Specialization*)&blocks[j];
			j += sizeof(Class::Specialization);
			std::string* spec2Name = (std::string*)&blocks[j];
			j += sizeof(*spec2Name);
			Class* classInstance = new Class(temp, name);
			classInstance->specializations[0] = new Class::Specialization(spec1, spec1Name);
			classInstance->specializations[1] = new Class::Specialization(spec2, spec2Name);
			classVector.push_back(classInstance);
		}

		delete[] blocks;
	}
}

// Todo: Look at 108 and 50.
void SetupCooldowns() {
	SetCooldown(std::vector<int>({ 51, 55, 115 }), 16000);
	SetCooldown(std::vector<int>({ 47, 109, 112, 113, 114, 142, 144, 146, 165 }), 40000);
	SetCooldown(std::vector<int>({ 95, 98, 136, 149 }), 30000);
	SetCooldown(std::vector<int>({ 22, 52, 97 }), 12000);
	SetCooldown(std::vector<int>({ 111 }), 4000);
	SetCooldown(std::vector<int>({ 73 }), 15000);
	SetCooldown(std::vector<int>({ 140, 141, 143 }), 60000);
	SetCooldown(std::vector<int>({ 148 }), 20000);
	SetCooldown(std::vector<int>({ 50, 108 }), 16000);
}

/* Gets the class that is assigned to the selected id.
 * The in-game id also has the four already existing classes prepended.
 * @param {int} id The id as in the game.
 * @return {Class*}
 */
Class* GetClassByGameId(int id) {
	if (id <= 4) return nullptr;
	for (auto i = 0; i < classVector.size(); i++) {
		if (classVector.at(i)->id + 4 == id) {
			return classVector.at(i);
		}
	}
	return nullptr;
}

/* Gets the class that is assigned to the selected id.
 * @param {int} id The id as in the file.
 * @return {Class*}
 */
Class* GetClassByFileId(int id) {
	for (auto i = 0; i < classVector.size(); i++) {
		if (classVector.at(i)->id == id) {
			return classVector.at(i);
		}
	}
	return nullptr;
}

/* Returns the next class id in the list. 
 * This is mainly used for the character creation menu.
 * @param {int} id The in game id of the class.
 * @return {int}
*/
int GetNextClassId(int id) {
	if (id < 3) return ++id;

	int next = 32;

	for (auto i = 0; i < classVector.size(); i++) {
		int curr_id = classVector.at(i)->id + 3;
		if (curr_id > id && curr_id < next) {
			next = curr_id;
		}
	}

	if (next >= 32) return 0;
	return next;
}

/* Returns the previous class id in the list.
 * This is mainly used for the character creation menu.
 * @param {int} id The in-game id of the currently selected character.
 * @return {int}
*/
int GetPreviousClassId(int id) {
	if (id == 0) return GetPreviousClassId(32);
	if (id <= 3) return --id;

	int previous = 3;
	for (auto i = 0; i < classVector.size(); i++) {
		int curr_id = classVector.at(i)->id + 3;

		if (curr_id > previous && curr_id < id) {
			previous = curr_id;
		}
	}
	return previous;
}

#define no_optimize __attribute__((optimize("O0")))
#define asm_naked __attribute__((naked))

#define PUSH_ALL "push rax\npush rbx\npush rcx\npush rdx\npush rsi\npush rdi\npush rbp\npush r8\npush r9\npush r10\npush r11\npush r12\npush r13\npush r14\npush r15\n"
#define POP_ALL "pop r15\npop r14\npop r13\npop r12\npop r11\npop r10\npop r9\npop r8\npop rbp\npop rdi\npop rsi\npop rdx\npop rcx\npop rbx\npop rax\n"

#define PREPARE_STACK "mov rax, rsp \n and rsp, 0xFFFFFFFFFFFFFFF0 \n push rax \n sub rsp, 0x28 \n"
#define RESTORE_STACK "add rsp, 0x28 \n pop rsp \n"



// These macros exist because "jmp [var]" or "jmp ds:[var]" and any other variants I have tried do not properly compile
#define GETTER_VAR(vartype, varname)\
	static __attribute__((used)) vartype varname;\
	extern "C" vartype Get_##varname(){return varname;}
#define DEREF_JMP(varname)\
	"sub rsp, 8 \n"\
	"push rax \n"\
	"call Get_"#varname" \n"\
	"mov [rsp+8], rax \n"\
	"pop rax \n"\
	"ret \n"