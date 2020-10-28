#pragma once
#include "../public.h"
#include "../class.h"
#include "cwsdk.h"

void InitializeMenuHook();

GETTER_VAR(void*, ASMSetMenuClassName_retn);
GETTER_VAR(void*, ASMSetClassName_1_ret);
GETTER_VAR(void*, ASMSetClassName_2_ret);
GETTER_VAR(void*, OverwriteClassIdIncrease_ret);
GETTER_VAR(void*, OverwriteClassIdDecrease_ret);
GETTER_VAR(void*, AddCreatureStarterWeapons_ret);

const char roguename_0[] = "Rogue";
char custom_class_char[16];

wchar_t roguename_L[] = L"Rogue";
wchar_t custom_class_wchar[16];

extern "C" wchar_t* get_customclass_name_L(int id) {
	Class* classInstance = GetClassByFileId(id);
	if (classInstance == nullptr) return (wchar_t*)&roguename_L;
	std::string* name = classInstance->name;
	std::wstring wsTmp(name->begin(), name->end());
	int j = 0;
	for (; j < name->size() && j < 15; j++) {
		custom_class_wchar[j] = wsTmp[j];
	}
	for (; j < 16; j++) {
		custom_class_wchar[j] = 0;
	}
	return custom_class_wchar;
}

extern "C" wchar_t* get_rogue_name_L() {
	return (wchar_t*)&roguename_L;
}

extern "C" char* get_customclass_name(int id) {
	Class* classInstance = GetClassByFileId(id);
	if (classInstance == nullptr) return (char*)&roguename_0;
	std::string* name = classInstance->name;
	int j = 0;
	for (; j < name->size() && j < 15; j++) {
		custom_class_char[j] = name->at(j);
	}
	for (; j < 16; j++) {
		custom_class_char[j] = 0;
	}
	return custom_class_char;
}

extern "C" char* get_rogue_name() {
	return (char*)&roguename_0;
}

extern "C" void get_character_menu_id_increase(cube::CharacterStyleWidget* widget) {
	//Popup("Debug", "Increase");
	widget->class_type = GetNextClassId(widget->class_type);
}

extern "C" void get_character_menu_id_decrease(cube::CharacterStyleWidget * widget) {
	//Popup("Debug", "Decrease");
	widget->class_type = GetPreviousClassId(widget->class_type);
}

extern "C" char generate_random_creature_info(cube::Game* game) {
	//Popup("Debug", "Generate");
	cube::Creature* player = game->GetPlayer();
	int classType = player->entity_data.classType;
	if (classType > 4) {
		Class* classInstance = GetClassByGameId(classType);
		if (classInstance != nullptr) {
			int newClassType = classInstance->itemClass;
			if (newClassType == 0) {
				player->entity_data.classType = 1;
			}
			else {
				player->entity_data.classType = newClassType;
			}
		}
	}
	char ret = ((char (*)(cube::Game*))CWOffset(0x913B0))(game);
	player->entity_data.classType = classType;
	return ret;
}

void ASMSetMenuClassName() asm_naked {
	asm(".intel_syntax \n"
		"sub ecx,01 \n"
		"je asm_set_class_name_lbl \n"
		"push rax \n"
		"call get_customclass_name_L \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetMenuClassName_retn)

		"asm_set_class_name_lbl: \n"
		"push rax \n"
		"call get_rogue_name_L \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetMenuClassName_retn)
		".att_syntax \n"
	);
}

void ASMSetClassName_1() asm_naked {
	asm(".intel_syntax \n"
		"sub ecx,01 \n"
		"je asm_set_class_name_lbl_1 \n"
		"push rax \n"
		"call get_customclass_name \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetClassName_1_ret)

		"asm_set_class_name_lbl_1: \n"
		"push rax \n"
		"call get_rogue_name \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetClassName_1_ret)
		".att_syntax \n"
	);
}

void ASMSetClassName_2() asm_naked {
	asm(".intel_syntax \n"
		"sub ecx,01 \n"
		"je asm_set_class_name_lbl_2 \n"
		"push rax \n"
		"call get_customclass_name \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetClassName_2_ret)

		"asm_set_class_name_lbl_2: \n"
		"push rax \n"
		"call get_rogue_name \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetClassName_2_ret)
		".att_syntax \n"
	);
}

void ASMMenuClassIdIncrease() asm_naked {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rcx, rbx \n"
		PREPARE_STACK
		"call get_character_menu_id_increase \n"
		RESTORE_STACK
		POP_ALL
		// Old code
		"xor edx, edx \n"
		"mov rcx, rbx \n"
		DEREF_JMP(OverwriteClassIdIncrease_ret)
		".att_syntax \n"
	);
}

void ASMMenuClassIdDecrease() asm_naked {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rcx, rbx \n"
		PREPARE_STACK
		"call get_character_menu_id_decrease \n"
		RESTORE_STACK
		POP_ALL
		// Old code
		"xor edx, edx \n"
		"mov rcx, rbx \n"
		DEREF_JMP(OverwriteClassIdDecrease_ret)
		".att_syntax \n"
	);
}

void ASMAddCreatureStarterWeapons() asm_naked {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rcx, [rdi + 0x1E8] \n"
		PREPARE_STACK
		"call generate_random_creature_info \n"
		RESTORE_STACK
		POP_ALL
		"mov rcx, [rdi + 0x1E8] \n"
		"mov rcx, [rcx + 0x08] \n"
		DEREF_JMP(AddCreatureStarterWeapons_ret)
		".att_syntax \n"
	);
}

void AddMenuClassNames() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x2714CF, (void*)&ASMSetMenuClassName);
	ASMSetMenuClassName_retn = (base + 0x2714F6);
}

void AddClassNames() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x27405A, (void*)&ASMSetClassName_1);
	ASMSetClassName_1_ret = (base + 0x274081);
	WriteFarJMP(base + 0x26F5D2, (void*)&ASMSetClassName_2);
	ASMSetClassName_2_ret = (base + 0x26F5F9);
}

void OverwriteClassIdIncrease() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x27243A, (void*)&ASMMenuClassIdIncrease);
	OverwriteClassIdIncrease_ret = (base + 0x272459);
}

void OverwriteClassIdDecrease() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x2723EA, (void*)&ASMMenuClassIdDecrease);
	OverwriteClassIdDecrease_ret = (base + 0x27240A);
}

void AddCreatureStarterWeapons() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x273176, (void*)&ASMAddCreatureStarterWeapons);
	AddCreatureStarterWeapons_ret = (base + 0x27318D);
}

void InitializeMenuHook() {
	AddMenuClassNames();
	AddClassNames();
	OverwriteClassIdIncrease();
	OverwriteClassIdDecrease();
	AddCreatureStarterWeapons();
}