#pragma once
#include <string>
#include <vector>

class LootPatternItem
{
public:
	std::string item_name;
	std::string item_base_name;
	//std::string item_class;
	std::string prophecy_name;

	int min_sockets = 0;
	int max_sockets = 0;

	int min_links = 0;
	int max_links = 0;

	int min_quality = 0;
	int max_quality = 0;

	int min_gem_level = 0;
	int max_gem_level = 0;

	int min_item_level;
	int max_item_level;

	int min_rarity;
	int max_rarity;

	int numeric_rarity = 0;

	bool is_legacy;

	int red_weight = 100;
	int green_weight = 100;
	int blue_weight = 100;
	int white_weight = 0;

	int corruption_chance = 0;

	int shaper_item_weight = 0;
	int elder_item_weight = 0;
	int normal_item_weight = 100;


	int height;
	int width;
	
	int min_map_tier;
	int max_map_tier;

	std::string base_class;

	std::string random_class;
	std::string random_subclass;
	std::string random_cost_group;

	int count = 1;

	int stack_size = 1;
};