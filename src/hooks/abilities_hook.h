#pragma once
#include "../public.h"
#include "../class.h"
#include "cwsdk.h"

GETTER_VAR(void*, ASMUltimateActionInsert_jmpback);
GETTER_VAR(void*, ASMUltimateActionInsert_oldCode_jmp);
GETTER_VAR(void*, ASMUltimateActionInsert_zero_return_jmp);
GETTER_VAR(void*, ASMCooldownOverwrite_jmpback);

// Todo: Check for out of bounds with vector
extern "C" int get_ultimate_id(cube::Creature* player) {
	Class* classInstance = GetClassByGameId(player->entity_data.classType);
	if (classInstance == nullptr) return 0;
	int spec = player->entity_data.specialization;
	if (spec > 1) return 0;
	return classInstance->specializations[spec]->rAbility;
}


// Todo: Check for out of bounds with vector
extern "C" int get_ability_cooldown(cube::Creature * creature, int abilityID) {
	if (abilityID > 255) return 0;
	int classType = creature->entity_data.classType;
	int spec = creature->entity_data.specialization;
	if (classType > 4 && spec < 2) {
		Class* classInstance = GetClassByGameId(classType);
		if (classInstance == nullptr) return cooldownMap->at(abilityID);
		int cooldown = classInstance->specializations[spec]->cooldown;
		if (cooldown != -1) {
			return cooldown;
		}
	}
	return cooldownMap->at(abilityID);
}

asm_naked void ASMUltimateActionInsert() {
	asm(".intel_syntax \n"
		"jz ASMUltimateActionInsert_oldCode_lbl \n"
		"sub edx, 1 \n"
		"jz ASMUltimateActionInsert_rogue_lbl \n"
		// Class 5+
		PUSH_ALL
		PREPARE_STACK
		"call get_ultimate_id \n"
		RESTORE_STACK
		"mov [rsp + 0x70], rax \n"
		POP_ALL
		//"mov eax, 0x6D \n"
		"ret \n"

		"ASMUltimateActionInsert_zero_return_lbl: \n"
		DEREF_JMP(ASMUltimateActionInsert_zero_return_jmp)

		"ASMUltimateActionInsert_rogue_lbl: \n"
		"cmp [rcx+0x14D], r8b \n"
		"mov eax, 0x8D \n"
		"mov edx, 0x6D \n"
		"cmovz eax, edx \n"
		DEREF_JMP(ASMUltimateActionInsert_jmpback)

		"ASMUltimateActionInsert_oldCode_lbl: \n"
		DEREF_JMP(ASMUltimateActionInsert_oldCode_jmp)
		".att_syntax \n"
	);
}

asm_naked void ASMCooldownOverwrite() {
	asm(".intel_syntax \n"
		PUSH_ALL
		PREPARE_STACK
		"call get_ability_cooldown \n"
		RESTORE_STACK
		"mov [rsp + 0x70], rax \n"
		POP_ALL
		DEREF_JMP(ASMCooldownOverwrite_jmpback)
		".att_syntax \n"
	);
}

void customclass_ultimate_insert() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x656F7, (void*)&ASMUltimateActionInsert);
	ASMUltimateActionInsert_jmpback = (base + 0x65712);
	ASMUltimateActionInsert_oldCode_jmp = (base + 0x65717);
	ASMUltimateActionInsert_zero_return_jmp = (base + 0x65713);
}

/* If the ability does not have an cooldown assigned (non ultimates),
 * then it does not get executed. This NOPs out a jump that checks that.
 * This way, a random cooldown for each ability is used (consistent per
 * specific ability).
*/
void patch_ultimate_cooldown() {
	char* base = (char*)CWBase();
	int offset = 0x50856;
	WriteByte(base + offset, 0x90);
	WriteByte(base + offset + 1, 0x90);
}

void overwrite_ability_cooldowns() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x50BD0, (void*)&ASMCooldownOverwrite);
	ASMCooldownOverwrite_jmpback = (base + 0x50C80);
}

void InitializeAbilityHook() {
	customclass_ultimate_insert();
	patch_ultimate_cooldown();
	overwrite_ability_cooldowns();
}