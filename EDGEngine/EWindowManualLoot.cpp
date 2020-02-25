#include "EWindowManualLoot.h"
#include "EButtonFilterItem.h"
#include "EButtonText.h"
#include "EButtonDropRarity.h"
#include "EButtonDropSocketColor.h"
#include "EButtonCheck.h"

EWindowManualLoot::EWindowManualLoot(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
{
	window_size_x = 900;
	window_size_y = 700;



	EButton* but = new EButtonExplicit(100, 100, 220, 20.0f, Enums::ButtonType::BUTTON_CLASS_FILTER_BLOCK_LIST);
	but->text = ""; link_to_class_button = but;
	add_complex("manual_loot_text_class", but);

	but = new EButtonDropRarity(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_RARITY);
	but->text = but->drop_text.at(0);
	add_complex("manual_loot_text_rarity", but);

	but = new EButtonText(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_ITEM_LEVEL);
	but->text = "68"; but->have_input_mode = true;
	add_complex("manual_loot_text_item_level", but);
	complex_y += 20.0f;

	but = new EButtonText(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_SOCKET_COUNT);
	but->text = "1"; but->have_input_mode = true;
	add_complex("manual_loot_text_sockets", but);

	but = new EButtonText(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_LINK);
	but->text = "0"; but->have_input_mode = true;
	add_complex("manual_loot_text_links", but);

	for (int i = 0; i < 6; i++)
	{
		but = new EButtonDropSocketColor(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_NONE);
		but->update_localisation();
		but->text = but->drop_text.at(0);
		but->data_id = i;
		add_complex("manual_loot_text_socket_color", but);

	}

	complex_y += 25.0f;

	but = new EButtonText(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_QUALITY);
	but->text = "0"; but->have_input_mode = true;
	add_complex("manual_loot_text_quality", but);

	but = new EButtonText(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_GEM_LEVEL);
	but->text = "0"; but->have_input_mode = true;
	add_complex("manual_loot_text_gem_level", but);
	
	complex_y += 25.0f;

	EButtonCheck* but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_ELDER_MAP);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_elder_map", but_check);

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_SHAPER_MAP);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_shaper_map", but_check);

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_BLIGHT_MAP);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_blighted_map", but_check);

	complex_x += 450.0f;
	complex_y = 125.0f;

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_IDENTIFIED);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_identified", but_check);

	but = new EButtonText(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_QUANTITY);
	but->text = "1"; but->have_input_mode = true;
	add_complex("manual_loot_text_quantity", but);

	complex_y += 25.0f;

	but = new EButtonText(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_HEIGHT);
	but->text = "2"; but->have_input_mode = true; link_to_height = but;
	add_complex("manual_loot_text_height", but);

	but = new EButtonText(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_WIDTH);
	but->text = "2"; but->have_input_mode = true; link_to_width = but;
	add_complex("manual_loot_text_width", but);

	complex_y += 25.0f;

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_CORRUPTED);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_corrupted", but_check);

	but = new EButtonText(100, 200, 120, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_CORRUPTION_COUNT);
	but->text = "0"; but->have_input_mode = true;
	add_complex("manual_loot_text_corruption_count", but);

	complex_y += 25.0f;

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_SHAPER_INFLUENCE);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_shaper_item", but_check);

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_ELDER_INFLUENCE);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_elder_item", but_check);

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_CRUSADER_INFLUENCE);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_crusader_item", but_check);

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_REDEEMER_INFLUENCE);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_redeemer_item", but_check);

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_HUNTER_INFLUENCE);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_hunter_item", but_check);

	complex_y += 25.0f;

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_FRACTURED);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_fractured_item", but_check);

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_SYNTHESISED);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_synthesised_item", but_check);

	complex_y += 25.0f;

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_ENCHANTMENT);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_enchanted_item", but_check);

	but_check = new EButtonCheck(100, 200, 20, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_MIRRORED);
	but_check->change_state(false);
	add_complex("manual_loot_text_is_mirrored_item", but_check);



	EButtonFilterItem* fi = new EButtonFilterItem(30, -40, 40, 40);
		fi->master_position = Enums::PositionMaster::WINDOW;
		fi->is_plus = false;
		fi->master_window = this;
		fi->gabarite = DefaultGabarite::gabarite_plus;
		fi->position_mode_y = Enums::PositionMode::UP;
		fi->can_be_removed = false;
		link_to_item_button = fi;
	button_list.push_back(fi);

	but = new EButtonText(20, 20, 200, 20.0f, Enums::ButtonType::BUTTON_MANUAL_LOOT_ADD_TO_LOOT_SIMULATOR);
		but->master_window = this;
		but->position_mode_x = Enums::LEFT;
		but->position_mode_y = Enums::DOWN;
		but->master_position = Enums::PositionMaster::WINDOW;
		but->update_localisation();
	button_list.push_back(but);
}

void EWindowManualLoot::button_event(EButton* _b)
{
}

void EWindowManualLoot::update_localisation()
{
	for (EButton* b : button_list)
	{
		b->update_localisation();
	}

	for (int i=0; i< complex_list.size(); i++)
	{
		complex_list.at(i).text = EString::localize_it(complex_list.at(i).localize);
	}
}

void EWindowManualLoot::text_pass(Batcher* _batch)
{
}

void EWindowManualLoot::manual_event()
{
}

void EWindowManualLoot::add_complex(std::string _s, EButton* _b)
{
	complex_list.push_back(complex());

	complex_list.at(complex_list.size() - 1).localize = _s;
	complex_list.at(complex_list.size() - 1).text = EString::localize_it(_s);
	complex_list.at(complex_list.size() - 1).button = _b;

	_b->master_window = this;
	button_list.push_back(_b);

	complex_list.at(complex_list.size() - 1).x = complex_x;
	complex_list.at(complex_list.size() - 1).y = complex_y;

	_b->text_align_x = Enums::PositionMode::LEFT;

	_b->input_only_numbers = false;
	_b->have_input_mode = true;

	_b->position_mode_x = Enums::PositionMode::LEFT;
	_b->position_mode_y = Enums::PositionMode::UP;


	_b->master_position = Enums::PositionMaster::WINDOW;
	_b->dynamic_input_width = false;

	_b->button_x = complex_x + 200.0f;
	_b->button_y = -complex_y;
	_b->input_auto_clear_text = true;

	complex_y += 25.0f;
	//complex_list.at(complex_list.size() - 1).button = _b;
}

void EWindowManualLoot::draw(Batcher* _batch, float _delta)
{


	for (complex c : complex_list)
	{
		_batch->setcolor(EColorCollection::LIGHT_GRAY);
		_batch->draw_rect_with_uv(pos_x + c.x, pos_y + window_size_y - c.y - 20.0f, 180.0f, 20.0f, DefaultGabarite::gabarite_white);

		_batch->setcolor(EColorCollection::BLACK);
		EFont::active_font->draw(_batch, c.text, pos_x + c.x + 3.0f,  pos_y + window_size_y - c.y - 18.0f);
	}
}
