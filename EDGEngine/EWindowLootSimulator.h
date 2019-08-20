#pragma once
#include <vector>
#include "LootItem.h"
#include "EWindow.h"

#include "LootPatternItem.h"

class EWindowLootSimulator : public EWindow
{
public:
	std::vector<LootItem*> main_loot_item_list;

	bool free_space[200][100];

	EWindowLootSimulator(int _id, bool _can_be_closed);

	void fill_random_pool(std::string _class, std::string _subclass, std::string _cost);

	virtual void update(float _d);


	virtual void draw(Batcher* _batch, float _delta);

	virtual void update_localisation();
	bool check_condition(std::string _condition, int _num_a, int num_b);
	void find_filter_block(LootItem* _l);
	void place(LootItem* _l);
	//void find_filter_block();
	virtual void manual_event();

	float drop_cooldown=1.0f;
	int drop_count = 50;

	std::vector <LootPatternItem*> pattern_item_list;

	int loot_vector_id = 0;

	std::vector <LootPatternItem*> prepared_pattern_list;


	std::vector <DADItem*> random_loot_pool;

};