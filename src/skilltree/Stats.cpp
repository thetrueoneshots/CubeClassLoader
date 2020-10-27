#include "Stats.h"

/*
 * Returns the stat level of the respective stat type.
 * @param   {StatType} type The type to get the level from.
 * @return  {int}
*/
int Stats::GetStatLevel(StatType type)
{
	if (type < 0 || type > StatType::STAT_TYPE_END) return -1;
	return levels[type];
}

/*
 * Increases the level of one stat.
 * @param	{StatType}	type The type of the stat to increase.
*/
void Stats::IncreaseStat(StatType type)
{
	if (type < 0 || type >= StatType::STAT_TYPE_END) return;
    if (levels[type] >= STAT_MAX_LEVELS[type]) return;
	levels[type] += 1;
}

/*
 * Resets the levels of all stats, allowing one to spend their levels again.
 * @return	{void}
*/
void Stats::ResetStats()
{
	for (int i = 0; i < StatType::STAT_TYPE_END; i++)
		levels[i] = 0;
}

/*
 * Converts the stats to a char* for file storage.
 * @return	{char*}
*/
char* Stats::ToString()
{
	return nullptr;
}

// Todo: Implement
/*
 * Sets the levels of the stats based on the data parsed from the source.
 * @param	{char*}	source The levels incoded in a string.
 * @return	{void}	
*/
void Stats::Parse(char* source)
{
	return;
}

/*
 * Counts the amount of skill points used on stats.
 * @return	{int}
*/
int Stats::CountSkillPoints()
{
	int cnt = 0;
	for (int i = 0; i < StatType::STAT_TYPE_END; i++)
		cnt += levels[i];
	return cnt;
}

