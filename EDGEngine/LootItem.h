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
	int abyss_socket;
	int delve_socket;

	int linked_red_socket;
	int linked_green_socket;
	int linked_blue_socket;
	int linked_white_socket;

	std::vector<EColor*> socket_color;

	int gem_level;

	int map_tier;

	bool is_shaper_map = false;
	bool is_elder_map = false;
	bool is_blighted_map = false;
	bool is_mirrored = false;

	int height;
	int width;

	int quantity = 1;

	bool corrupted = false;
	int corrupted_mods = 0;

	bool shaper_item = false;
	bool elder_item = false;
	bool crusader_item = false;
	bool redeemer_item = false;
	bool hunter_item = false;
	bool warlord_item = false;

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
	std::string cluster_enchantment;
	std::string prophecy;

	bool is_replica;
	bool is_alternate_quality;

};