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


	virtual void draw(Batcher* _batch, float _delta);


	int rarity_to_number(std::string _rarity);
	virtual void update_localisation();
	bool check_condition(std::string _condition, int _num_a, int num_b);

	void find_filter_block(LootItem* _l, EWindowFilterBlock* _w, bool _default);

	void place(LootItem* _l);
	//void find_filter_block();
	virtual void manual_event();

	float drop_cooldown = 1.0f;
	int drop_count = 50;

	std::vector <LootPatternItem*> pattern_item_list;

	int loot_vector_id = 0;

	std::vector <LootPatternItem*> prepared_pattern_list;


	std::vector <DADItem*> random_item_pool;

	bool is_bright_bg = true;

	virtual void close_action();

	float font_scale_factor = 1.0f;

	EButton* link_to_autogen_drop_button;

};