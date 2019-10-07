#pragma once
#include <string>
#include "FilterBlock.h"
class LootItem
{
public:
	LootItem();
	~LootItem();

	std::string data_name;
	std::string name;

	std::string base_class;

	int id;

	int quality;
	int sockets;
	int links;

	int corruption_chance = 0;

	int numeric_rarity;

	std::string rarity = "normal";
	int item_level;
	int req_level;

	int red_socket;
	int green_socket;
	int blue_socket;
	int white_socket;

	int gem_level;

	int map_tier;

	bool is_shaper_map;
	bool is_elder_map;

	int height;
	int width;

	int quantity = 1;

	bool corrupted = false;

	bool shaper_item = false;
	bool elder_item = false;

	bool synthesised_item = false;
	bool fractured_item = false;
	bool any_enchantment = false;
	bool identified = false;


	FilterBlock* filter_block_link;
	FilterBlock* default_filter_block_link;

	float pos_x;
	float pos_y;

	std::vector <std::string> explicit_list;

	std::string enchantment;

};