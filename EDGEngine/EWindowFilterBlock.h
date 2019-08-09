#pragma once
#include "EWindow.h"
#include "Enums.h"

class EWindowFilterBlock : public EWindow
{
public:
	std::vector<FilterBlock*> filter_block_list;

	bool need_remove_last_element = false;

	float sound_volume = 0.5f;
	EButton* link_to_slider;

	EWindowFilterBlock(int _id, bool _can_be_closed);
	~EWindowFilterBlock();

	int get_id_of_filter_block(FilterBlock* _fb);
	virtual void draw(Batcher* _batch, float _delta);
	virtual void text_pass(Batcher* _batch);
};