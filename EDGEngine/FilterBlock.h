#pragma once

//#include "EButton.h"
#include "Enums.h"
#include "Batcher.h"
#include "EFont.h"
#include "Helper.h"
#include <vector>

#include "EButton.h"
#include "BaseClass.h"
#include "LabEnchantment.h"

#include "ProphecyList.h"
#include "EUtils.h"

//#include "ExplicitGroup.h"




//#include "EButton.cpp"
//class FilterBLockSeparator;

class ExplicitGroup;
class EButton;
class EButtonFilterItem;
class EButtonDropCondition;
class EButtonInputBaseData;
class EButtonDropRarity;
class EButtonService;
class EButtonCheck;
class EButtonRemove;
class EButtonPlusWide;
class EButtonSocketGroup;

class EButtonExplicit;



class FilterBlock
{
public:
	float x = 10;
	float y = 0;
	float size_x = 300;
	float size_y = 100;

	std::vector<int> socket_count = { 0,0,0,0,0 };
	
	bool is_socket_active = false;			std::string socket_condition = "=";
	std::vector<int> red_sockets = { 0,0,0,0,0 };
	std::vector<int> green_sockets = { 0,0,0,0,0 };
	std::vector<int> blue_sockets = { 0,0,0,0,0 };
	std::vector<int> white_sockets = { 0,0,0,0,0 };
	std::vector<int> abyss_sockets = { 0,0,0,0,0 };
	std::vector<int> delve_sockets = { 0,0,0,0,0 };

	int links_count = 0;		bool is_links_active = false;			std::string links_condition = "=";

	int item_level = 0;			bool is_item_level_active = false;		std::string item_level_condition = "=";
	int required_level = 0;		bool is_required_level_active = false;	std::string required_level_condition = "=";

	int item_width = 0;			bool is_item_width_active = false;		std::string item_width_condition = "=";
	int item_height = 0;		bool is_item_height_active = false;		std::string item_height_condition = "=";

	int item_quality = 0;		bool is_item_quality_active = false;	std::string item_quality_condition = "=";
	int item_stack_size = 0;	bool is_stack_size_active = false;		std::string item_stack_size_condition = "=";
	int gem_level = 0;			bool is_gem_level_active = false;		std::string gem_level_condition = "=";

	int map_tier = 0;			bool is_map_tier_active = false;		std::string map_tier_condition = "=";


	bool is_socket_group_active = false;	std::string socket_group_condition = "=";
	bool is_area_level_active = false;		std::string area_level_condition = "=";	int area_level = 0;
	bool is_corrupted_mods_active = false;		std::string corrupted_mods_condition = "=";	int corrupted_mods_count = 0;

	std::vector<int> socket_group_links = { 0,0,0,0,0 };
	std::vector<int> red_sockets_group = { 0,0,0,0,0 };
	std::vector<int> green_sockets_group = { 0,0,0,0,0 };
	std::vector<int> blue_sockets_group = { 0,0,0,0,0 };
	std::vector<int> white_sockets_group = { 0,0,0,0,0 };
	std::vector<int> abyss_sockets_group = { 0,0,0,0,0 };
	std::vector<int> delve_sockets_group = { 0,0,0,0,0 };

	bool is_prophecy_active = false;
	bool is_enchantment_active = false;
	bool is_cluster_enchantment_active = false;

	std::string	item_rarity = "Rare";				bool is_item_rarity_active = false;	 std::string rarity_condition = "=";

	bool		is_corrupted = false;		bool is_corrupted_active = false;

	//Enums::YNE		is_corrupted		= Enums::YNE::EITHER;		bool is_corrupted_active = false;
	bool		is_shaper_item = false;		bool is_shaper_item_active = false;
	bool		is_elder_item = false;		bool is_elder_item_active = false;
	bool		is_fractured_item = false;		bool is_fractured_item_active = false;
	bool		is_synthesised_item = false;		bool is_synthesised_item_active = false;
	bool		is_enchantment_item = false;		bool is_enchantment_item_active = false;

	bool		is_elder_map = false;				bool is_elder_map_active = false;
	bool		is_shaper_map = false;				bool is_shaper_map_active = false;

	bool is_font_size_active = false;
	int font_size = 30;

	bool is_text_color_active = false;
	int text_color_red = 255;
	int text_color_green = 255;
	int text_color_blue = 255;
	int text_color_alpha = 255;
	//
	double text_color_hue = 0;
	double text_color_saturation = 1;
	double text_color_value = 1;

	bool is_bg_color_active = false;
	int bg_red = 128;
	int bg_green = 128;
	int bg_blue = 128;
	int bg_alpha = 255;
	//
	double bg_hue = 0;
	double bg_saturation = 1;
	double bg_value = 1;

	bool is_rama_color_active = false;
	int rama_red = 0;
	int rama_green = 0;
	int rama_blue = 0;
	int rama_alpha = 255;
	//
	double rama_hue = 0;
	double rama_saturation = 1;
	double rama_value = 1;

	int debug_text_y = 0;
	int debug_text_x = 0;

	bool is_alert_sound = false;
	bool is_custom_alert_sound = false;

	string alert_sound_name = "";
	Enums::DefaultAlertSound alert_sound_id = Enums::DefaultAlertSound::SOUND_NONE;
	int alert_sound_volume = 300;

	string custom_alert_sound_name = "";

	bool is_ray = false;
	Enums::GameColors ray_color = Enums::GameColors::RAY_WHITE;
	bool ray_is_temp=false;

	bool is_minimap_icon = false;
	Enums::IconColor minimap_icon_color = Enums::IconColor::WHITE;
	Enums::IconShape minimap_icon_shape = Enums::IconShape::CIRCLE;
	Enums::IconSize minimap_icon_size = Enums::IconSize::SMALL;

	bool is_identified = false;
	bool is_identified_active = false;

	float random_bg_offset_x;
	float random_bg_offset_y;


	std::vector<string*> class_list;
	std::vector<string*> base_type_list;
	std::vector<string*> explicit_mod_list;
	std::vector<EButtonExplicit*> prophecy_list;

	bool is_explicit = false;

	string YNE_value[3] = { "yes", "no", "either" };


	bool is_show = true;
	bool is_continue = false;
	bool disable_drop_sound = false;

	//EButton* idiot=NULL;
	//EButton* zzz=NULL;
	//std::vector<EButton*> filter_flock_button_list;

	std::vector<EButton*> filter_block_items_button_list;

	

	//std::vector<EButton*> filter_block_button_list;

	static int rarity_text_to_id(string _text);

	static string bool_to_string(bool _b);

	void add_base_buttons(string _text, Enums::ButtonType _condition_type, Enums::ButtonType _button_type, bool _sep, int _id);

	//void add_base_buttons(string _text, Enums::ButtonType _condition_type, Enums::ButtonType _button_type, bool _sep);

	FilterBlock();

	~FilterBlock();

	void remove_button_from_list(std::vector<EButton*> _v);

	void update(float _d);


	void draw(Batcher* _batch);

	void add_debug(bool _if, string _text, EFont* _font, Batcher* _batch);

	void text_pass(Batcher* _batch);

	EButtonFilterItem* button_plus;
	EButtonFilterItem* button_plus_equal;
	EButtonService* button_service;
	EButtonPlusWide* button_add_new_base_data;
	EButtonPlusWide* button_add_new_EPC;

	float max_h = 200;
	float button_h_max = 0;
	float max_h_top = 200;

	
	std::vector<string> base_filter_data_name;
	std::vector<EButtonDropCondition*> base_filter_condition_list;
	std::vector<EButton*> base_filter_buttons;

	std::vector<bool> base_filter_separator;
	std::vector<bool> base_filter_data_active;
	std::vector<bool> base_filter_data_bool;

	std::vector<EButton*> base_filter_data_remove_buttons;


	std::vector<EButton*> button_list;

	const float _data_y_offset = 25;

	void init();
	void data_change();

	static void change_color_consume(FilterBlock* _fb);
	static void change_color_extract(FilterBlock* _fb);

	void update_localisation();

	EButton* sound_button_link;
	EButton* custom_sound_button_link;

	EButtonExplicit* plus_class_button_link;
	EButton* remove_base_class_button;

	EButtonExplicit* plus_enchantment_button_link;
	EButton* remove_enchantment_button;

	EButtonExplicit* plus_cluster_enchantment_button_link;
	EButton* remove_cluster_enchantment_button;

	EButtonExplicit* plus_prophecy_button_link;
	EButton* remove_prophecy_button;

	vector <ExplicitGroup*> explicit_list;
	vector <EButtonExplicit*> base_class_list;
	vector <EButtonExplicit*> enchantment_list;
	vector <EButtonExplicit*> cluster_enchantment_list;



	bool is_base_class_active=false;
	
	float highlight_time = 0.0f;

	float right_side_buttons_offset = 25.0f;

	bool is_deactivated = false;

	bool ray_semitransarent = false;

	float ray_cooldown = 0.5f;

	bool constant_highlight = false;

	float remove_timer = -100.0f;
	bool need_remove = false;

	EButton* link_to_cancel_remove_button;
	EButton* link_to_header_separator;
	EButton* link_to_header_collapse_separator;
	EButton* link_to_header_destroy_separator;

	int order_id;

	bool is_positional_sound = false;

	//FilterBlockSeparator* separator_link = NULL;

	bool have_separator = false;
	bool hided_by_separator = false;

	bool contain_start_separator = false;
	bool contain_end_separator = false;

	std::vector <bool> autogen_include = { true, true, true, true, true, true };

	std::vector <EButtonCheck*> autogen_button_link;

	std::vector <EButton*> header_button_list;

	float start_position_draw_x = 370.0f + 95.0f + 75.0f;

	EButton* link_to_continue_button;

	bool disabled = false;
	bool force_enabled = false;


	struct base_data_buttons_struct
	{
		std::vector<EButton*> button_operator;
		std::vector<EButton*> button_checkbox;
		std::vector<EButton*> button_delete;
		std::vector<EButton*> button_input;
		std::vector<EButton*> button_drop_list;

		std::vector<EButton*> button_add_new_element;

		int order = 0;
		int element_count = 0;
	};

	std::vector< base_data_buttons_struct* > base_data_button_list;

	struct filter_block_data_attribute_struct
	{
		std::string* data_name		= new std::string("");

		std::string* name_RU			= new std::string("");
		std::string* name_EN			= new std::string("");

		std::string* description_RU		= new std::string("");
		std::string* description_EN		= new std::string("");

		bool* have_operator		= new bool(false);
		bool* have_input_field	= new bool(false);
		bool* have_rarity		= new bool(false);
		bool* have_checkbox		= new bool(false);
		bool* force_split		= new bool(false);

		int* id					= new int(-1);

		int* button_type		= new int(-1);
	};

	struct base_data_button_collection_struct
	{
		EButton* condition_button	= NULL;
		EButton* main_button		= NULL;
		EButton* remove_button		= NULL;

		int target_id = -1;

		bool need_remove = false;
	};

	std::vector <base_data_button_collection_struct*> base_data_button_collection_list;

	static std::vector<filter_block_data_attribute_struct*> filter_block_data_attribute_registerer;

	std::vector <EButton*> influences_button_list;
	std::vector <EButton*> special_status_button_list;

	EButton* link_to_all_or_oneof;

	enum InfluenceList
	{
		IL_SHAPER,
		IL_ELDER,

		IL_CRUSADER,
		IL_REDEEMER,
		
		IL_WARLORD,
		IL_HUNTER,
	};

	enum SpecialStatusList
	{
		SSL_CORRUPTED,
		SSL_IDENTIFIED,
		SSL_ENCHANTED,

		SSL_SYNTHESISED,
		SSL_FRACTURED,
		SSL_BLIGHTED,

		SSL_ALTERNATE_QUALITY,
		SSL_REPLICA,
		SSL_MIRRORED
	};

	enum SpecialStatusMode
	{
		SSM_ON,
		SSM_OFF,
		SSM_DEACTIVATED
	};

	std::vector <bool> vector_influence =
	{
		false,	//shaper
		false,	//elder

		false,	//crusader
		false,	//redeemer
		false,	//warlord
		false	//hunter
	};

	std::vector <int> vector_special_status =
	{
		SpecialStatusMode::SSM_DEACTIVATED,	//corrupted
		SpecialStatusMode::SSM_DEACTIVATED,	//identified
		SpecialStatusMode::SSM_DEACTIVATED,	//enchant

		SpecialStatusMode::SSM_DEACTIVATED,	//synthesised
		SpecialStatusMode::SSM_DEACTIVATED,	//fractured
		SpecialStatusMode::SSM_DEACTIVATED,	//blighted

		SpecialStatusMode::SSM_DEACTIVATED,	//alternate_quality
		SpecialStatusMode::SSM_DEACTIVATED,	//replica
		SpecialStatusMode::SSM_DEACTIVATED	//mirrored
	};

	enum InfluenceMode
	{
		IM_ALL,
		IM_ONE_OF,
		IM_NONE,
		IM_IGNORE
	};

	int influence_mode = InfluenceMode::IM_IGNORE;

	static base_data_button_collection_struct* add_new_base_attribute(std::string _text, FilterBlock* _filter_block);

	EButton* link_to_switch_exact_match;

	bool is_exact_match = false;
	/*int swithed_data_shaper_influence			= Enums::SwitcherState::SWITCHER_STATE_DEACTIVATE;
	int swithed_data_elder_influence			= Enums::SwitcherState::SWITCHER_STATE_DEACTIVATE;

	int swithed_data_redeemer_influence			= Enums::SwitcherState::SWITCHER_STATE_DEACTIVATE;
	int swithed_data_warlord_influence			= Enums::SwitcherState::SWITCHER_STATE_DEACTIVATE;
	int swithed_data_crusader_influence			= Enums::SwitcherState::SWITCHER_STATE_DEACTIVATE;
	int swithed_data_hunter_influence			= Enums::SwitcherState::SWITCHER_STATE_DEACTIVATE;*/
};