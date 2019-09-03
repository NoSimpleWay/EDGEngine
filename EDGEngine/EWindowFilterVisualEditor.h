#pragma once
#include "EWindow.h"


class EWindowFilterVisualEditor : public EWindow
{
public:

	std::string cached_text_border_color;
	std::string cached_text_color;
	std::string cached_text_bg_color;
	std::string cached_text_size;
	//std::vector<FilterBlock*> filter_block_list;
	FilterBlock* master_block;

	float default_position_x = 15.0;
	float default_position_y = 315.0;

	float distance_between_x = 200.0;
	float distance_between_y = 20.0f;

	float button_size_x = 150.0f;

	float icon_button_base_x = 625.0f;
	float icon_button_base_y = 5.0f;

	std::vector<EButton*> link_to_sliders;

	std::vector<EButton*> link_to_icon_shape;
	std::vector<EButton*> link_to_icon_color;
	std::vector<EButton*> link_to_icon_size;

	std::vector<EButton*> link_to_ray_color;
	std::vector<EButton*> link_to_ray_type;

	EButton* link_to_icon_checker;
	EButton* link_to_ray_checker;

	EButton* link_to_ray_constant;
	EButton* link_to_ray_tempotary;



	void set_button_data(EButton* _b);

	EWindowFilterVisualEditor(int _id, bool _can_be_closed);

	void update_ray_button();

	void update_minimap_button();
	

	void deactivate_minimap_button();

	virtual void draw(Batcher* _batch, float _delta);

	virtual void text_pass(Batcher* _batch);


	virtual void button_event(EButton* _b);

	virtual void update_localisation();

	virtual void close_action();

};