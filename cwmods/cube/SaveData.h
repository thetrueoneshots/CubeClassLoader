#pragma once
#include "../IDA/types.h"
#include "../common/RGBA.h"
#include <map>

namespace cube {
	class SaveData {
	public:
		class UnkStruct {
		public:
			class UnkStruct2 {
			public:
				UnkStruct2* left;
				UnkStruct2* parent;
				UnkStruct2* right;
				//_BYTE gap18[0x01];
				//char var_19; // Can be bool;
				__int16 red_or_black; // Often only 19 is checked.
				_BYTE gap1A[0x02];
				__int32 var_1C; // Can be __int64;
				_BYTE gap20[0x04]; // Can be variable;
				__int32 var_24;
			};
			UnkStruct2* ptr_0;
			UnkStruct2* ptr_8;
		};
		int race;
		int gender;
		int face;
		int hair;
		ByteRGBA hair_color;
		_BYTE gap0[0x94];
		std::map<void*, void*> map_A8;
		_BYTE gap[0x10];
		//UnkStruct* ptr_C8; // This is a std::map
		//_BYTE gapD0[0x08]; // Might be size
		std::map<void*, void*> map_C8;
		UnkStruct* ptr_D8;
		_BYTE gapE0[0x08]; // Might be size
		UnkStruct* ptr_E8;
		_BYTE gapF0[0x08]; // Might be size
		UnkStruct* ptr_F8;
		_BYTE gap100[0x188];
		int var_288; //Used to output to ostream<wchar_t>
		_BYTE gap290[0x60];
		__int64 var_2F0;
		__int32 var_2F8;
	};
}

static_assert(sizeof(cube::SaveData::UnkStruct::UnkStruct2) == 0x28, "cube::SaveData::UnkStruct::UnkStruct2 is not the correct size.");
static_assert(sizeof(cube::SaveData::UnkStruct) == 0x10, "cube::SaveData::UnkStruct is not the correct size.");
static_assert(sizeof(cube::SaveData) == 0x300, "cube::SaveData::UnkStruct is not the correct size.");
