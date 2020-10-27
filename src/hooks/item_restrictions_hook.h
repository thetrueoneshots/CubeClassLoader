#pragma once
#include "../public.h"
#include "../class.h"
#include "cwsdk.h"

void InitializeItemRestrictionsHook();

GETTER_VAR(void*, ASMCustomClassItemRestriction_jmpOne);
GETTER_VAR(void*, ASMCustomClassItemRestriction_jmpTwo);
GETTER_VAR(void*, ASMCustomClassItemRestriction_jmpThree);
GETTER_VAR(void*, ASMCustomClassItemRestriction_retn);

// Todo: Check for out of bounds with vector
extern "C" int get_class_type(int id) {
	if (id <= 4) return id;
	Class* classInstance = GetClassByGameId(id);
	if (classInstance == nullptr) return 1;
	return classInstance->itemClass;
}

asm_naked void ASMCustomClassItemRestriction() {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rcx, rdx \n"
		PREPARE_STACK
		"call get_class_type \n"
		RESTORE_STACK
		"mov [rsp + 0x58], rax \n"
		POP_ALL

		// Old code
		"mov r9, rcx \n"
		"cmp al, 2 \n"
		"jz ASMCustomClassItemRestriction_lbl1 \n"
		"cmp al, 3 \n"
		"jz ASMCustomClassItemRestriction_lbl2 \n"
		"jbe ASMCustomClassItemRestriction_lbl3 \n"
		DEREF_JMP(ASMCustomClassItemRestriction_retn)

		"ASMCustomClassItemRestriction_lbl1: \n"
		DEREF_JMP(ASMCustomClassItemRestriction_jmpOne)

		"ASMCustomClassItemRestriction_lbl2: \n"
		DEREF_JMP(ASMCustomClassItemRestriction_jmpTwo)

		"ASMCustomClassItemRestriction_lbl3: \n"
		DEREF_JMP(ASMCustomClassItemRestriction_jmpThree)
		".att_syntax \n"
	);
}

void CustomClassItemRestrictions() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x1094EC, (void*)&ASMCustomClassItemRestriction);
	ASMCustomClassItemRestriction_jmpOne = (base + 0x1095CF);
	ASMCustomClassItemRestriction_jmpTwo = (base + 0x109555);
	ASMCustomClassItemRestriction_jmpThree = (base + 0x109677);
	ASMCustomClassItemRestriction_retn = (base + 0x1094FB);
}


void InitializeItemRestrictionsHook() {
	CustomClassItemRestrictions();
}