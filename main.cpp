#include "main.h"
#include <fstream>
#include <map>
#include <utility>

void PrintLoadedClasses();
bool InGUI(cube::Game* game);
bool InCraftingGUI(cube::Game* game);
void HandleKeyboardState(BYTE* diKeys);
void HandleInCraftingGUI(cube::Game* game);
void HandleFirstTickInitialize(cube::Game* game);
void Init();
void UpdateStat(cube::Creature* creature, float* stat, StatType type1, StatType type2, float factor1 = 1.0f, float factor2 = 1.0f);

/* Mod class containing all the functions for the mod.
*/
class Mod : GenericMod {

	WindowRenderer* windowRenderer;
	/* Hook for the chat function. Triggers when a user sends something in the chat.
	 * @param	{std::wstring*} message
	 * @return	{int}
	*/
	int OnChat(std::wstring* message) {
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

			HandleFirstTickInitialize(game);
		}

		if (InCraftingGUI(game))
			HandleInCraftingGUI(game);

		return;
	}

	/* Function hook that gets called on intialization of cubeworld.
	 * [Note]:	cube::GetGame() is not yet available here!!
	 * @return	{void}
	*/
	void Initialize() {
		Init();

		// Create ClassWindow object
		windowRenderer = new WindowRenderer(&classVector, skillTree);
		return;
	}

	void OnGetKeyboardState(BYTE* diKeys) {
		windowRenderer->OnGetKeyboardState(diKeys);
		HandleKeyboardState(diKeys);
	}

	void OnGetMouseState(DIMOUSESTATE* diMouse) {
		windowRenderer->OnGetMouseState(diMouse);
	}


	void OnPresent(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags) {
		windowRenderer->Present();
	}


	int OnWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return windowRenderer->WindowProc(hwnd, uMsg, wParam, lParam);
	}

	void OnCreatureArmorCalculated(cube::Creature* creature, float* armor) 
	{
		UpdateStat(creature, armor, StatType::SCALING_ARMOR, StatType::FLAT_ARMOR);
	}

	void OnCreatureCriticalCalculated(cube::Creature* creature, float* critical) 
	{
		UpdateStat(creature, critical, StatType::SCALING_CRIT, StatType::FLAT_CRIT, 1.0f, 200.0f);
	}

	void OnCreatureAttackPowerCalculated(cube::Creature* creature, float* power) 
	{
		UpdateStat(creature, power, StatType::SCALING_DAMAGE, StatType::FLAT_DAMAGE);
	}

	void OnCreatureSpellPowerCalculated(cube::Creature* creature, float* power) 
	{
		UpdateStat(creature, power, StatType::SCALING_SPELL_POWER, StatType::FLAT_SPELL_POWER);
	}

	void OnCreatureHasteCalculated(cube::Creature* creature, float* haste) 
	{
		UpdateStat(creature, haste, StatType::SCALING_HASTE, StatType::FLAT_HASTE, 100.0f, 100.0f);
	}

	void OnCreatureHPCalculated(cube::Creature* creature, float* hp) 
	{
		UpdateStat(creature, hp, StatType::SCALING_HEALTH, StatType::FLAT_HEALTH);
	}

	void OnCreatureResistanceCalculated(cube::Creature* creature, float* resistance) 
	{
		UpdateStat(creature, resistance, StatType::SCALING_RESISTANCE, StatType::FLAT_RESISTANCE);
	}

	void OnCreatureRegenerationCalculated(cube::Creature* creature, float* regeneration) 
	{
		UpdateStat(creature, regeneration, StatType::STAMINA_REGEN, StatType::STAT_TYPE_END);
	}

	void OnCreatureManaGenerationCalculated(cube::Creature* creature, float* manaGeneration) 
	{
		UpdateStat(creature, manaGeneration, StatType::MANA_REGEN, StatType::STAT_TYPE_END);
		/*
		cube::Game* game = cube::GetGame();
		if (!game) return;
		cube::World* world = game->world;
		if (!world) return;
		if (cube::GetGame()->world->local_creature == creature) {
			*manaGeneration *= 1 + ((skillTree->stats.GetStatLevel(StatType::MANA_REGEN) * STAT_MODIFIERS[StatType::MANA_REGEN]) / 100.0);
		}*/
	}
};

// Export of the mod created in this file, so that the modloader can see and use it.
EXPORT Mod* MakeMod() {
	return new Mod();
}

void UpdateStat(cube::Creature* creature, float* stat, StatType type1, StatType type2, float factor1, float factor2) {
	cube::Game* game = cube::GetGame();
	if (!game) return;
	cube::World* world = game->world;
	if (!world) return;
	if (cube::GetGame()->world->local_creature == creature) {
		if (type1 < StatType::STAT_TYPE_END && type1 >= 0)
			*stat *= 1 + ((skillTree->stats.GetStatLevel(type1) * STAT_MODIFIERS[type1]) / (100.0 * factor1));
		if (type2 < StatType::STAT_TYPE_END && type2 >= 0)
			*stat += skillTree->stats.GetStatLevel(type2) * STAT_MODIFIERS[type2] / factor2;
	}
}

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

bool InGUI(cube::Game* game) 
{
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

bool InCraftingGUI(cube::Game* game) 
{
	cube::GUI* gui = &game->gui;
	auto data = &gui->crafting_inventory_widget->node->display->visibility.data;
	auto frame = gui->crafting_inventory_widget->node->display->visibility.current_frame;
	return data->at(frame) ? true : false;
}

void HandleKeyboardState(BYTE* diKeys) 
{
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

void HandleInCraftingGUI(cube::Game* game)
{
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

void HandleFirstTickInitialize(cube::Game* game) 
{
	// Fix characters chrashing the game. Todo: Remove
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


void Init()
{
	//Setup cooldowns
	cooldownMap = new std::vector<int>(256, 0);
	SetupCooldowns();

	// Load stored classes
	LoadClasses();
	LoadSkillTrees();

	// Initialise class loader hooks.
	InitializeMenuHook();
	InitializeItemRestrictionsHook();
	InitializeAbilityHook();
	InitializeCraftingHook();
	InitializeTreasureHook();
}
