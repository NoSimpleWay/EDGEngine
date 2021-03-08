#pragma once
#include <vector>
#include "LootItem.h"
#include "EWindow.h"

#include "LootPatternItem.h"

class EWindowLootSimulator : public EWindow
{
public:
	std::vector<LootItem*> main_loot_item_list;

	bool free_space[125][87];

	EWindowLootSimulator(int _id, bool _can_be_closed);

	void fill_random_pool(std::string _class, std::string _subclass, std::string _cost, std::string _category);

	virtual void update(float _d);

	void put_loot(LootItem*& loot);


	virtual void draw(Batcher* _batch, float _delta);


	int rarity_to_number(std::string _rarity);
	virtual void update_localisation();
	bool check_condition(std::string _condition, int _num_a, int num_b);

	void find_filter_block(LootItem* _l, EWindowFilterBlock* _w, bool _default);

	void place(LootItem* _l);
	//void find_filter_block();
	virtual void manual_event();

	float drop_cooldown = 1.0f;
	int drop_count = 0;

	std::vector <LootPatternItem*> pattern_item_list;

	int loot_vector_id = 0;

	std::vector <LootPatternItem*> prepared_pattern_list;


	std::vector <DADItem*> random_item_pool;

	bool is_bright_bg = true;

	virtual void close_action();

	float font_scale_factor = 1.0f;

	EButton* link_to_autogen_drop_button;

	std::string cached_quality_text;
	std::string cached_gem_level;
	std::string cached_item_level;
	std::string cached_map_tier;
	std::string cached_corrupted;
	std::string cached_corrupted_mods_count;
	std::string cached_mirrored;
	std::string cached_replica;
	std::string cached_alternate_quality;
	std::string cached_cluster_passives;

	int area_level = 68;

	std::string convert_to_condition(std::string _text);
	int convert_to_number(std::string _text);

};