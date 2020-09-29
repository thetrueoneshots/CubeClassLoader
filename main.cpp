#include "main.h"
#include <fstream>
#include <map>
#include <utility>

void PrintLoadedClasses() {
	std::string mods("Classed Loaded:\n");
	for (Class* classObject : classVector) {
		mods += *classObject->name;
		mods += "\n";
	}
	if (classVector.size() == 0) {
		mods += "<No Classes>\n";
	}
	Popup("Loaded Classes", mods.c_str());
}

bool InGUI(cube::Game* game) {
	cube::GUI* gui = &game->gui;
	plasma::Node* nodes[] = {
		gui->startmenu_node,
		gui->character_selection_node,
		gui->character_creation_node,
		gui->world_selection_node,
		gui->world_creation_node,
		gui->equipment_inventory_widget->node,
		gui->crafting_inventory_widget->node,
		gui->multiplayer_widget->node,
		gui->vendor_inventory_widget->node,
		gui->adaption_widget->node,
		gui->voxel_widget->node,
		gui->enchant_widget->node,
		gui->question_widget->node,
		gui->system_widget->node,
		gui->controls_widget->node,
		gui->options_widget->node
	};

	for (plasma::Node* node : nodes) {
		if (!node) continue;
		auto data = &node->display->visibility.data;
		auto frame = node->display->visibility.current_frame;

		if (data->at(frame)) {
			return true;
		}
	}

	if (gui->chat_widget->typebox_active) return true;
	if (gui->map_open) return true;
	if (gui->esc_menu_displayed) return true;

	return false;
}

bool InCraftingGUI(cube::Game* game) {
	cube::GUI* gui = &game->gui;
	auto data = &gui->crafting_inventory_widget->node->display->visibility.data;
	auto frame = gui->crafting_inventory_widget->node->display->visibility.current_frame;
	return data->at(frame) ? true : false;
}


/* Mod class containing all the functions for the mod.
*/
class Mod : GenericMod {

	ClassWindow* classWindow;
	/* Hook for the chat function. Triggers when a user sends something in the chat.
	 * @param	{std::wstring*} message
	 * @return	{int}
	*/
	int OnChat(std::wstring* message) {
		/*const wchar_t* msg = message->c_str();
		int ability;

		cube::Creature* player = cube::GetGame()->GetPlayer();
		int classType = player->entity_data.classType;
		if (classType <= 4) return 0;

		Class* classInstance = GetClassByGameId(classType);
		if (classInstance == nullptr) return 0;

		if (swscanf(msg, L"/setr %d", &ability) == 1) {
			classInstance->specializations.at(player->entity_data.specialization)->rAbility = ability;
		}
		if (swscanf(msg, L"/setshift %d", &ability) == 1) {
			classInstance->specializations.at(player->entity_data.specialization)->shiftAbility = ability;
		}
		if (swscanf(msg, L"/setcooldown %d", &ability) == 1) {
			classInstance->specializations.at(player->entity_data.specialization)->cooldown = ability == -1 ? ability : 1000 * ability;
		}*/

		return 0;
	}

	/* Function hook that gets called every game tick.
	 * @param	{cube::Game*} game
	 * @return	{void}
	*/
	void OnGameTick(cube::Game* game) {
		static bool firstTickInitialize = false;
		if (!firstTickInitialize) {
			firstTickInitialize = true;

			// Fix characters chrashing the game. 
			for (auto i = 0; i < game->saved_characters.size(); i++) {
				cube::Creature* character = game->saved_characters.at(i);
				if (character->entity_data.classType > classVector.size() + 4) {
					// Set character to warrior of its class file does not exist.
					character->entity_data.classType = 1;
				}
			}

			// Initialize specialization names.
			for (auto i = 0; i < classVector.size(); i++) {
				for (auto j = 0; j < classVector.at(i)->specializations.size(); j++) {
					std::pair<uint32_t, uint32_t> def;
					def.first = 4 + classVector.at(i)->id;
					def.second = j;
					std::string* spec = classVector.at(i)->specializations.at(j)->name;
					std::wstring specName(spec->begin(), spec->end());
					game->speech.specialization_type_id_map.insert_or_assign(def, specName);
				}
			}

			// Initialize ability names.
			for (auto i = 1; i <= 255; i++) {
				if (!game->speech.skill_type_id_map.count(i)) {
					game->speech.skill_type_id_map.insert_or_assign(i, std::wstring(L"SkillAttack"));
				}
			}
		}

		if (InCraftingGUI(game)) {
			std::vector<cube::ItemStack>* itemStacks = &game->crafting_menu_tabs.at(5);
			int classType = game->GetPlayer()->entity_data.classType;
			if (itemStacks->size() <= 6 && classType >= 4) {
				Class* classInstance = GetClassByGameId(classType);
				if (classInstance->itemClass != 1) {
					for (int i = 0; i < 3; i++) {
						cube::Item item = cube::Item(11, 9);
						item.material = 26 + i;
						item.rarity = 0;
						item.formula_category = 0;
						cube::ItemStack itemStack = cube::ItemStack(0, item);
						itemStacks->push_back(itemStack);
					}
				}
			}
		}

		return;
	}

	/* Function hook that gets called on intialization of cubeworld.
	 * [Note]:	cube::GetGame() is not yet available here!!
	 * @return	{void}
	*/
	void Initialize() {

		cooldownMap = new std::vector<int>(256, 0);

		LoadClasses();

		// Initialise class loader hooks.
		InitializeMenuHook();
		InitializeItemRestrictionsHook();
		InitializeAbilityHook();
		InitializeCraftingHook();
		InitializeTreasureHook();
		// Initialise hooks of all class dll's
		SetupCooldowns();

		classWindow = new ClassWindow(&classVector);

		return;
	}

	void OnGetKeyboardState(BYTE* diKeys) {
		classWindow->OnGetKeyboardState(diKeys);
		static DButton lShiftKey(42);
		static DButton rKey(19);
		lShiftKey.Update(diKeys);
		rKey.Update(diKeys);
		cube::Game* game = cube::GetGame();
		cube::Creature* player = game->GetPlayer();
		auto classType = player->entity_data.classType;
		auto specType = player->entity_data.specialization;
		if (classType <= 4 || InGUI(game)) return;
		
		if (lShiftKey.Pressed()) {
			Class* classInstance = GetClassByGameId(classType);
			if (classInstance != nullptr) {
				player->entity_data.time_since_ability = 0.0;
				player->entity_data.current_ability = classInstance->specializations[specType]->shiftAbility;
			}
		}
		return;
	}

	void OnGetMouseState(DIMOUSESTATE* diMouse) {
		classWindow->OnGetMouseState(diMouse);
	}


	void OnPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags) {
		classWindow->Present();
	}


	int OnWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return classWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
};

// Export of the mod created in this file, so that the modloader can see and use it.
EXPORT Mod* MakeMod() {
	return new Mod();
}