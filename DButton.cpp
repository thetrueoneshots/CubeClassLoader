#include "DButton.h"

DButton::DButton(int diKey) {
	oldState = 0;
	currentState = 0;
	SetKey(diKey);
}

void DButton::Update(BYTE* diKeys) {
	oldState = currentState;
	currentState = diKeys[diKey];
}

bool DButton::Pressed() {
	return ((oldState & 0x80) == 0) && ((currentState & 0x80) != 0);
}

void DButton::SetKey(int dikey) {
	this->diKey = dikey;
}

const char* DButton::GetKeyName() {
	static const char* keys[] = {
		"KEY 0x00",
		"ESC",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"-",
		"=",
		"BACK",
		"TAB",
		"Q",
		"W",
		"E",
		"R",
		"T",
		"Y",
		"U",
		"I",
		"O",
		"P",
		"[",
		"]",
		"RETURN",
		"LCTRL",
		"A",
		"S",
		"D",
		"F",
		"G",
		"H",
		"J",
		"K",
		"L",
		";",
		"'",
		"`",
		"LSHIFT",
		"\\",
		"Z",
		"X",
		"C",
		"V",
		"B",
		"N",
		"M",
		",",
		".",
		"/",
		"RSHIFT",
		"MULTIPLY",
		"LMENU",
		"SPACE",
		"CAPITAL",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"NUMLOCK",
		"SCROLL",
		"NUM7",
		"NUM8",
		"NUM9",
		"SUBTRACT",
		"NUM4",
		"NUM5",
		"NUM6",
		"ADD",
		"NUM1",
		"NUM2",
		"NUM3",
		"NUM0",
		"DECIMAL",
		"KEY 0x54",
		"KEY 0x55",
		"OEM_102",
		"F11",
		"F12",
		"KEY 0x59",
		"KEY 0x5A",
		"KEY 0x5B",
		"KEY 0x5C",
		"KEY 0x5D",
		"KEY 0x5E",
		"KEY 0x5F",
		"KEY 0x60",
		"KEY 0x61",
		"KEY 0x62",
		"KEY 0x63",
		"F13",
		"F14",
		"F15",
		"KEY 0x67",
		"KEY 0x68",
		"KEY 0x69",
		"KEY 0x6A",
		"KEY 0x6B",
		"KEY 0x6C",
		"KEY 0x6D",
		"KEY 0x6E",
		"KEY 0x6F",
		"KANA",
		"KEY 0x71",
		"KEY 0x72",
		"ABNT_C1",
		"KEY 0x74",
		"KEY 0x75",
		"KEY 0x76",
		"KEY 0x77",
		"KEY 0x78",
		"CONVERT",
		"KEY 0x7A",
		"NOCONVERT",
		"KEY 0x7C",
		"YEN",
		"ABNT_C2",
		"KEY 0x7F",
		"KEY 0x80",
		"KEY 0x81",
		"KEY 0x82",
		"KEY 0x83",
		"KEY 0x84",
		"KEY 0x85",
		"KEY 0x86",
		"KEY 0x87",
		"KEY 0x88",
		"KEY 0x89",
		"KEY 0x8A",
		"KEY 0x8B",
		"KEY 0x8C",
		"NUMEQUALS",
		"KEY 0x8E",
		"KEY 0x8F",
		"PREVTRACK",
		"AT",
		":",
		"UNDERLINE",
		"KANJI",
		"STOP",
		"AX",
		"UNLABELED",
		"KEY 0x98",
		"NEXTTRACK",
		"KEY 0x9A",
		"KEY 0x9B",
		"NUMPADENTER",
		"RCTRL",
		"KEY 0x9E",
		"KEY 0x9F",
		"MUTE",
		"CALCULATOR",
		"PLAYPAUSE",
		"KEY 0xA3",
		"MEDIASTOP",
		"KEY 0xA5",
		"KEY 0xA6",
		"KEY 0xA7",
		"KEY 0xA8",
		"KEY 0xA9",
		"KEY 0xAA",
		"KEY 0xAB",
		"KEY 0xAC",
		"KEY 0xAD",
		"VOLDOWN",
		"KEY 0xAF",
		"VOLUP",
		"KEY 0xB1",
		"WEBHOME",
		"NUM,",
		"KEY 0xB4",
		"DIVIDE",
		"KEY 0xB6",
		"SYSRQ",
		"RMENU",
		"KEY 0xB9",
		"KEY 0xBA",
		"KEY 0xBB",
		"KEY 0xBC",
		"KEY 0xBD",
		"KEY 0xBE",
		"KEY 0xBF",
		"KEY 0xC0",
		"KEY 0xC1",
		"KEY 0xC2",
		"KEY 0xC3",
		"KEY 0xC4",
		"PAUSE",
		"KEY 0xC6",
		"HOME",
		"UP",
		"PRIOR",
		"KEY 0xCA",
		"LEFT",
		"KEY 0xCC",
		"RIGHT",
		"KEY 0xCE",
		"END",
		"DOWN",
		"NEXT",
		"INSERT",
		"DELETE",
		"KEY 0xD4",
		"KEY 0xD5",
		"KEY 0xD6",
		"KEY 0xD7",
		"KEY 0xD8",
		"KEY 0xD9",
		"KEY 0xDA",
		"LWIN",
		"RWIN",
		"APPS",
		"POWER",
		"SLEEP",
		"KEY 0xE0",
		"KEY 0xE1",
		"KEY 0xE2",
		"WAKE",
		"KEY 0xE4",
		"WEBSEARCH",
		"WEBFAVORITES",
		"WEBREFRESH",
		"WEBSTOP",
		"WEBFORWARD",
		"WEBBACK",
		"MYCOMPUTER",
		"MAIL",
		"MEDIASELECT",
		"KEY 0xEE",
		"KEY 0xEF",
		"KEY 0xF0",
		"KEY 0xF1",
		"KEY 0xF2",
		"KEY 0xF3",
		"KEY 0xF4",
		"KEY 0xF5",
		"KEY 0xF6",
		"KEY 0xF7",
		"KEY 0xF8",
		"KEY 0xF9",
		"KEY 0xFA",
		"KEY 0xFB",
		"KEY 0xFC",
		"KEY 0xFD",
		"KEY 0xFE",
		"KEY 0xFF" };
	return keys[diKey];
}