#pragma once
#include "../public.h"
#include "../class.h"
#include "cwsdk.h"

void InitializeOnCreatureUpdateHook();

GETTER_VAR(void*, ASMUpdate_jmpback);

extern "C" void OnCreatureUpdate(cube::Creature* creature, cube::World* world) {
	if (creature == world->local_creature)
		creature->entity_data.speed *= 1 + skillTree->stats.GetStatLevel(StatType::MOVEMENT_SPEED) * STAT_MODIFIERS[StatType::MOVEMENT_SPEED] / 1000.0f;
}

extern "C" void IncreaseMSOnRoad(cube::Creature * creature) {
	creature->entity_data.speed *= 1.1f;
}

__attribute__((naked)) void ASMOnCreatureUpdate() {
	asm(".intel_syntax \n"
		PUSH_ALL

		"mov rcx, r13 \n"
		"mov rdx, r15 \n"

		PREPARE_STACK

		"call OnCreatureUpdate \n"

		RESTORE_STACK

		POP_ALL

		"test [r13 + 0x5C], ebx \n"
		"jz 1f \n"

		PUSH_ALL

		"mov rcx, r13 \n"

		PREPARE_STACK

		"call IncreaseMSOnRoad \n"

		RESTORE_STACK

		POP_ALL

		"1: \n"
		DEREF_JMP(ASMUpdate_jmpback)

		".att_syntax \n"
	
	);
}


void InitializeOnCreatureUpdateHook() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x2BBD80, (void*)&ASMOnCreatureUpdate);
	ASMUpdate_jmpback = (base + 0x2BBDA0);
}