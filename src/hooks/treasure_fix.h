#pragma once
#include "../public.h"
#include "../class.h"
#include "cwsdk.h"

#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

void InitializeTreasureHook();

GETTER_VAR(void*, ASMTreasure_ret_1);
GETTER_VAR(void*, ASMTreasure_ret_2);
GETTER_VAR(void*, ASMTreasure_ret_3);
GETTER_VAR(void*, ASMTreasure_ret_4);
GETTER_VAR(void*, ASMTreasure_jmpback);

extern "C" int GetItemClass2(int classType) {
	if (classType <= 4) return classType;

	Class* classInstance = GetClassByGameId(classType);
	if (classInstance == nullptr) return 1;

	return classInstance->itemClass;
}

__attribute__((naked)) void ASMRandomTreasure() {
	asm(".intel_syntax \n"
		PUSH_ALL
		PREPARE_STACK

		"call GetItemClass2 \n"

		RESTORE_STACK

		"mov [rsp+0x60], rax \n"

		POP_ALL

		"monk_treasure_lbl: \n"
		"sub ecx, 1 \n"
		"jz treasure_ret_1_lbl \n"
		"sub ecx, 1 \n"
		"jz treasure_ret_2_lbl \n"
		DEREF_JMP(ASMTreasure_jmpback)

		"treasure_ret_1_lbl: \n"
		DEREF_JMP(ASMTreasure_ret_1)

		"treasure_ret_2_lbl: \n"
		DEREF_JMP(ASMTreasure_ret_2)

		".att_syntax \n"
	);
}


void InitializeTreasureHook() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x10A7FE, (void*)&ASMRandomTreasure);
	ASMTreasure_jmpback = (base + 0x10A810);
	ASMTreasure_ret_1 = (base + 0x10AB70);
	ASMTreasure_ret_2 = (base + 0x10AA60);
	ASMTreasure_ret_3 = (base + 0x10A933);
	ASMTreasure_ret_4 = (base + 0x10AD17);
}