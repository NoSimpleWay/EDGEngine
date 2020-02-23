#pragma once
#include "EWindow.h"
#include "Enums.h"
#include "EUtils.h"


class EWindowManualLoot : public EWindow
{
public:

	std::string cached_text_search;

	EWindowManualLoot(int _id, bool _can_be_closed);
	virtual void button_event(EButton* _b);

	//Enums::WindowAcceptCancelMode window_mode = Enums::WindowAcceptCancelMode::AC_unsave_open;
	virtual void update_localisation();

	std::string window_text;
	virtual void text_pass(Batcher* _batch);
	virtual void manual_event();

	FilterBlockSeparator* master_separator = NULL;

	float complex_x = 10.0f;
	float complex_y = 100.0f;

	void add_complex(std::string _s, EButton* _b);
	virtual void draw(Batcher* _batch, float _delta);

	struct complex
	{
		std::string localize;
		std::string text;
		EButton* button;
		float x;
		float y;
	};

	std::vector<complex> complex_list;
	std::vector<std::string> text;

	std::string item_class;
	std::string rarity;

	int item_level = 68;
	int sockets = 1;
	int links = 0;
	

	std::vector<int> socket_color = { 0,0,0,0,0,0 };

	int quality;
	int gem_level;

	int map_tier;
	
	bool elder_map = false;
	bool shaper_map = false;
	bool blighted_map = false;

	bool identified = false;
	int quantity;
	int item_height;

	int item_width;

	bool is_corrupted = false;
	int corruption_count;

	bool elder_influence = false;
	bool shaper_influence = false;
	bool crusader_influence = false;
	bool redeemer_influence = false;
	bool hunter_influence = false;
	bool warlord_influence = false;

	bool is_fractured = false;
	bool is_synthesised = false;
	bool is_enchanted = false;
	bool is_mirrored = false;

	EButton* link_to_class_button;
	EButton* link_to_item_button;

	EButton* link_to_height;
	EButton* link_to_width;
};