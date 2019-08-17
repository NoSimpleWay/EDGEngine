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

	int id;

	int quality;
	int sockets;
	int links;

	std::string rarity;
	int item_level;
	int req_level;
	
	int red_socket;
	int green_socket;
	int blue_socket;
	int alpha_socket;

	int gem_level;

	int map_tier;

	bool is_shaper_map;
	bool is_elder_map;

	int height;
	int width;

	int quantity;

	bool corrupted;

	bool shaper_item;
	bool elder_item;

	bool synthesised_item;
	bool fractured_item;
	bool any_enchantment;
	bool identified;


	FilterBlock* filter_block_link;

	float pos_x;
	float pos_y;

};