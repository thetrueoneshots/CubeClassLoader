#pragma once
#include "../public.h"
#include "../class.h"
#include "cwsdk.h"

GETTER_VAR(void*, ASMSetCraftingItemType_retn);
GETTER_VAR(void*, ASMSetCraftingItemType2_retn);
GETTER_VAR(void*, ASMSetCraftingItemType3_retn);

extern "C" int GetItemClass(cube::World* world) {
	int classType = world->local_creature->entity_data.classType;
	if (classType <= 4) return classType;

	Class* classInstance = GetClassByGameId(classType);
	if (classInstance == nullptr) return 1;

	return classInstance->itemClass;
}

// Todo: Rename to item crafting function
void ASMSetCraftingItemType() asm_naked {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rcx, rdx \n"
		PREPARE_STACK
		"call GetItemClass \n"
		RESTORE_STACK
		// Mov rax to rcx on the stack
		"mov [rsp + 0x60], rax \n"
		POP_ALL
		DEREF_JMP(ASMSetCraftingItemType_retn)
		".att_syntax \n"
	);
}

// Todo: Rename to gear crafting function
void ASMSetCraftingItemType2() asm_naked {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rcx, rax \n"
		PREPARE_STACK
		"call GetItemClass \n"
		RESTORE_STACK
		// Mov rax to rdx on the stack
		"mov [rsp + 0x58], rax \n"
		POP_ALL
		DEREF_JMP(ASMSetCraftingItemType2_retn)
		".att_syntax \n"
	);
}

// Todo: Rename to gear crafting function
void ASMSetCraftingItemType3() asm_naked {
	asm(".intel_syntax \n"
		PUSH_ALL
		PREPARE_STACK
		"call GetItemClass \n"
		RESTORE_STACK
		// Mov rax to rcx on the stack
		"mov [rsp + 0x60], rax \n"
		POP_ALL
		DEREF_JMP(ASMSetCraftingItemType3_retn)
		".att_syntax \n"
	);
}

void WeaponCrafting() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0xB24EE, (void*)&ASMSetCraftingItemType);
	ASMSetCraftingItemType_retn = (base + 0xB24FC);
}

void GearCrafting() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0xB2795, (void*)&ASMSetCraftingItemType2);
	ASMSetCraftingItemType2_retn = (base + 0xB27A3);
}

void CraftingTabs() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x1076EB, (void*)&ASMSetCraftingItemType3);
	ASMSetCraftingItemType3_retn = (base + 0x1076F9);
}

void InitializeCraftingHook() {
	WeaponCrafting();
	GearCrafting();
	CraftingTabs();
}