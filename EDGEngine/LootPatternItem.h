#pragma once
#include <string>
#include <vector>

class LootPatternItem
{
public:
	std::string item_name;
	//std::string item_class;
	std::string prophecy_name;

	int min_sockets;
	int max_sockets;

	int min_links;
	int max_links;

	int min_quality;
	int max_quality;

	int min_rarity;
	int max_rarity;

	int numeric_rarity = 0;

	bool is_legacy;

	int red_weight;
	int green_weight;
	int blue_weight;
	int white_weight;

	int height;
	int width;

	std::string base_class;

	std::string random_class;
	std::string random_subclass;
	std::string random_cost_group;

	int count = 1;

	int stack_size = 1;
};