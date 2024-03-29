#pragma once
class Enums
{
public:
	enum rarity { NORMAL=0, MAGIC, RARE, UNIQUE };
	enum YNE { YES, NO, EITHER};

	enum ParserMode
	{
		NOTHING,
		IS_CORRUPTED,
		CORRUPTED_MODS,
		LINKED_SOCKETS,
		RARITY,
		CLASS,
		FONT_SIZE,
		TEXT_COLOR,
		BORDER_COLOR,
		BACKGROUND_COLOR,
		PLAY_ALERT_SOUND,
		ALERT_SOUND,
		RAY,
		MINIMAP_ICON,
		SHOW,
		HIDE,
		BASETYPE,
		BASETYPE_EQUAL,
		IS_SHAPER_ITEM,
		ITEM_LEVEL,
		EXPLICIT_MOD,
		IDENTIFIED,
		IS_ELDER_ITEM,
		DROP_LEVEL,
		SOCKETS,
		IS_FRACTURED_ITEM,
		WIDTH,
		HEIGHT,
		IS_SYNTHESISED_ITEM,
		IS_ANY_ENCHANTMENT,
		QUALITY,
		SOCKET_GROUP,
		STACK_SIZE,
		GEM_LEVEL,
		IS_ELDER_MAP,
		IS_SHAPER_MAP,
		MAP_TIER,
		DISABLE_DROP_SOUND,
		DISABLE_DROP_SOUND_IF_ALERT_SOUND,
		ENABLE_DROP_SOUND_IF_ALERT_SOUND,
		ARCHNEMESIS,
		CUSTOM_ALERT_SOUND,
		HAS_ENCHANTMENT,
		C_SEPARATOR,
		C_AUTOGEN,
		IS_BLIGHTED_MAP,
		IS_HAVE_INFLUENCE_OR,
		IS_HAVE_INFLUENCE_AND,
		AREA_LEVEL,
		IS_MIRRORED,
		CONTINUE,
		CLUSTER_ENCHANTMENT,
		ALTERNATIVE_QUALITY,
		IS_REPLICA,
		CLUSTER_PASSIVES_COUNT,
		ALTERNATE_QUALITY_TYPE,
		IS_SCOURGED,
		BASE_DEFENCE_PERCENTILE,
		IS_UBER_BLIGHT_MAP,
		SEARING_EXARCH,
		EATER_OF_THE_WORLD
	};
	enum GameColors {RAY_RED, RAY_GREEN, RAY_BLUE, RAY_BROWN, RAY_WHITE, RAY_YELLOW, RAY_CYAN, RAY_GREY, RAY_ORANGE, RAY_PINK, RAY_PURPLE};
	
	enum IconColor {RED, GREEN, BLUE, YELLOW, WHITE, CYAN, GREY, ORANGE, PINK, PURPLE};
	enum IconShape {CIRCLE, DIAMOND, HEXAGON, SQUARE, STAR, TRIANGLE, CROSS, MOON, RAINDROP, KITE, PENTAGON, UPSIDEDOWNHOUSE};
	enum IconSize {LARGE, MEDIUM, SMALL};

	enum ConditionSymbols {LEQUAL, LESS, EQUAL, BIGGER, BEQUAL};

	enum PositionMaster {WINDOW, FILTER_BLOCK, SCREEN, SEPARATOR};
	enum PositionMode {LEFT, MID, RIGHT, UP, DOWN};

	enum ButtonType
	{
		BUTTON_NONE,
		BUTTON_CORRUPTION,
		BUTTON_CONDITION_LINKS, BUTTON_LINKS,
		BUTTON_CONDITION_RARITY, BUTTON_RARITY,
		BUTTON_FONT_SIZE, BUTTON_TEXT_COLOR, BUTTON_BORDER_COLOR, BUTTON_BG_COLOR,
		BUTTON_SHAPER_ITEM,

		BUTTON_AND_SHAPER_ITEM,
		BUTTON_OR_SHAPER_ITEM,

		BUTTON_AND_ELDER_ITEM,
		BUTTON_OR_ELDER_ITEM,

		BUTTON_AND_CRUSADER_ITEM,
		BUTTON_OR_CRUSADER_ITEM,

		BUTTON_AND_HUNTER_ITEM,
		BUTTON_OR_HUNTER_ITEM,

		BUTTON_AND_WARLORD_ITEM,
		BUTTON_OR_WARLORD_ITEM,

		BUTTON_AND_REDEEMER_ITEM,
		BUTTON_OR_REDEEMER_ITEM,

		BUTTON_AND_NO_INFLUENCE,
		BUTTON_OR_NO_INFLUENCE,

		BUTTON_ELDER_ITEM,
		BUTTON_IDENTIFIED,
		BUTTON_BLIGHTED,
		BUTTON_CONDITION_SOCKETS, BUTTON_SOCKETS,
		BUTTON_FRACTURED,
		BUTTON_SYNTHESISED,
		BUTTON_CONDITION_DROP_LEVEL, BUTTON_DROP_LEVEL,
		BUTTON_CONDITION_ITEM_LEVEL, BUTTON_ITEM_LEVEL,
		BUTTON_CONDITION_WIDTH, BUTTON_WIDTH,
		BUTTON_CONDITION_HEIGHT, BUTTON_HEIGHT,
		BUTTON_ANY_ENCHANTMENT,
		BUTTON_CONDITION_QUALITY, BUTTON_QUALITY,

		BUTTON_CONDITION_SOCKET_GROUP,
		BUTTON_SOCKET_GROUP,

		BUTTON_CONDITION_STACK_SIZE, BUTTON_STACK_SIZE,
		BUTTON_CONDITION_GEM_LEVEL, BUTTON_GEM_LEVEL,
		BUTTON_ELDER_MAP,
		BUTTON_SHAPER_MAP,
		BUTTON_CONDITION_MAP_TIER, BUTTON_MAP_TIER,
		BUTTON_FILTER_BLOCK_TO_CONSOLE,

		BUTTON_SOCKET_LINKED,
		BUTTON_SOCKET_COUNT,

		BUTTON_SOCKET_GROUP_RED,
		BUTTON_SOCKET_GROUP_GREEN,
		BUTTON_SOCKET_GROUP_BLUE,
		BUTTON_SOCKET_GROUP_WHITE,
		BUTTON_SOCKET_GROUP_ABYSS,
		BUTTON_SOCKET_GROUP_DELVE,

		BUTTON_SOCKET_RED,
		BUTTON_SOCKET_GREEN,
		BUTTON_SOCKET_BLUE,
		BUTTON_SOCKET_WHITE,
		BUTTON_SOCKET_ABYSS,
		BUTTON_SOCKET_DELVE,

		BUTTON_BG_H,
		BUTTON_BG_S,
		BUTTON_BG_V,
		BUTTON_BG_ALPHA,

		BUTTON_TEXT_H,
		BUTTON_TEXT_S,
		BUTTON_TEXT_V,
		BUTTON_TEXT_ALPHA,

		BUTTON_RAMA_H,
		BUTTON_RAMA_S,
		BUTTON_RAMA_V,
		BUTTON_RAMA_ALPHA,

		BUTTON_SYS_VISUAL_MODE,
		BUTTON_SYS_PLAY_SOUND,

		BUTTON_SEARCH_ITEM,
		BUTTON_SEARCH_DEFAULT_SOUND,
		BUTTON_SEARCH_CUSTOM_SOUND,
		BUTTON_SEARCH_BASE_CLASS,
		BUTTON_SEARCH_ENCHANTMENT,
		BUTTON_SEARCH_CLUSTER_ENCHANTMENT,
		BUTTON_SEARCH_ARCHNEMESIS,
		BUTTON_SEARCH_LOOT_FILTER,
		BUTTON_SEARCH_LOOT_SIMULATOR_PATTERN,

		BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW,
		BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW,

		BUTTON_REMOVE_EXPLICIT_GROUP,
		BUTTON_REMOVE_BASE_CLASS,
		BUTTON_REMOVE_BASE_DATA,
		BUTTON_REMOVE_ARCHNEMESIS,
		BUTTON_REMOVE_ENCHANTEMENT,
		BUTTON_REMOVE_CLUSTER_ENCHANTEMENT,

		BUTTON_OPEN_BASE_DATA_WINDOW,
		BUTTON_OPEN_BASE_CLASS_WINDOW,
		BUTTON_ADD_EXPLICIT_GROUP,
		BUTTON_ACTIVE_BASE_CLASS_LIST,
		BUTTON_ACTIVE_ARCHNEMESIS_LIST,
		BUTTON_ACTIVE_ENCHANTEMENT_LIST,
		BUTTON_ACTIVE_CLUSTER_ENCHANTEMENT_LIST,
		BUTTON_OPEN_EXPLICIT_ARCHNEMESIS_CLASS_WINDOW,
		BUTTON_ADD_EXPLICIT_ELEMENT,
		BUTTON_ADD_BASE_CLASS,
		BUTTON_EXPLICIT_FILTER_BLOCK_LIST,
		BUTTON_CLASS_FILTER_BLOCK_LIST,
		BUTTON_ENCHANTMENT_FILTER_BLOCK_LIST,
		BUTTON_CLUSTER_ENCHANTMENT_FILTER_BLOCK_LIST,
		BUTTON_ARCHNEMESIS_FILTER_BLOCK_LIST,

		BUTTON_MINIMAP_ICON_SELECT_SHAPE,
		BUTTON_MINIMAP_ICON_SELECT_COLOR,
		BUTTON_MINIMAP_ICON_SELECT_SIZE,

		BUTTON_CHECKER_MINIMAP_ICON,
		BUTTON_CHECKER_DISABLE_DROP_SOUND,
		BUTTON_CHECKER_DISABLE_DROP_SOUND_IF_ALERT_SOUND,
		BUTTON_CHECKER_ENABLE_DROP_SOUND_IF_ALERT_SOUND,

		BUTTON_SAVE_LOOT_FILTER,
		BUTTON_AUTOGEN_SAVE_LOOT_FILTER,
		BUTTON_OPEN_LOOT_FILTER,
		BUTTON_NEW_LOOT_FILTER_WINDOW,
		BUTTON_NEW_LOOT_FILTER_NAME,
		BUTTON_NEW_LOOT_FILTER_OK,

		BUTTON_SLIDER_FONT_SIZE,
		BUTTON_SELECT_RAY_COLOR,

		BUTTON_PLUS_NEW_FILTER_BLOCK,
		BUTTON_MOVE_FILTER_BLOCK_UP,
		BUTTON_MOVE_FILTER_BLOCK_DOWN,
		BUTTON_CUT_FILTER_BLOCK,
		BUTTON_CLONE_FILTER_BLOCK,
		BUTTON_ADD_SEPARATOR_TO_FILTER_BLOCK,
		BUTTON_SET_BLOCK_CONTINUE,

		BUTTON_REMOVE_BLOCK,
		BUTTON_SHOW_HIDE,

		BUTTON_SEARCH_INPUT_FOR_ITEM,
		BUTTON_SEARCH_INPUT_FOR_FILTER_BLOCK,
		BUTTON_SEARCH_INPUT_FOR_PASSIVES,

		BUTTON_GLOBAL_DROP_SOUND_VOLUME,
		BUTTON_SET_RAY_IS_TEMPOTARY,
		BUTTON_SET_RAY_IS_CONSTANT,
		BUTTON_FILTER_BLOCK_SCROLL,
		BUTTON_CANCEL_REMOVE_FILTER_BLOCK,

		BUTTON_LOCALISATION_EN,
		BUTTON_LOCALISATION_RU,

		BUTTON_OPEN_SIMULATOR,
		BUTTON_SELECT_FONT,
		BUTTON_CONFIGUE_FONT,
		BUTTON_CONFIGUE_LANGUAGE,
		BUTTON_REMOVE_ALL_SOUND,
		BUTTON_FILTER_BLOCK_TAB,
		BUTTON_OPEN_PATTERN_WINDOW,

		BUTTON_REFRESH_LOOT_SIMULATOR,
		BUTTON_REMOVE_LOOT_FROM_SIMULATOR,
		BUTTON_CHANGE_BG_BRIGHT,
		BUTTON_CHANGE_BG_DARK,
		BUTTON_ACCEPT,
		BUTTON_CANCEL,
		BUTTON_SEPARATOR_COLLAPSE,
		BUTTON_REMOVE_SEPARATOR,
		BUTTON_SEPARATOR_CAPTION_TEXT,
		BUTTON_PASSIVE,
		BUTTON_CHECK_OIL,
		BUTTON_CHANGE_OIL_COUNT,
		BUTTON_OPEN_OIL_WINDOW,

		BUTTON_CHECK_AUTOGEN,

		SLIDER_LOOT_DROP_SIZE,

		BUTTON_CONDITION_AUTOGEN_LOOT_SIMULATOR,

		BUTTON_SELECT_LOOT_PATTERN,

		BUTTON_SOCKETS_GROUP_COLORS_AND_LINKS,
		BUTTON_SOCKETS_COLORS_AND_COUNT,
		BUTTON_CONDITION_AREA_LEVEL,
		BUTTON_CONDITION_CORRUPTION_IMPLICITES,
		BUTTON_CONDITION_ALTERNATE_QUALITY,
		BUTTON_CONDITION_REPLICA,
		BUTTON_AREA_LEVEL,
		BUTTON_CORRUPTION_IMPLICITES,
		BUTTON_ALTERNATE_QUALITY,
		BUTTON_REPLICA,

		BUTTON_AREA_LEVEL_FOR_LOOT_SIMULATOR,
		BUTTON_MIRRORED_ITEM,

		BUTTON_MANUAL_LOOT_CLASS,
		BUTTON_MANUAL_LOOT_ADD_TO_LOOT_SIMULATOR,
		BUTTON_OPEN_MANUAL_LOOT_WINDOW,
		BUTTON_MANUAL_LOOT_RARITY,
		BUTTON_MANUAL_LOOT_ALTERNATE_QUALITY_TYPE,
		BUTTON_MANUAL_LOOT_ITEM_LEVEL,
		BUTTON_MANUAL_LOOT_SOCKET_COUNT,
		BUTTON_MANUAL_LOOT_LINK,
		BUTTON_MANUAL_LOOT_COLOR,
		BUTTON_MANUAL_LOOT_QUALITY,
		BUTTON_MANUAL_LOOT_GEM_LEVEL,
		BUTTON_MANUAL_LOOT_MAP_TIER,
		BUTTON_MANUAL_LOOT_ELDER_MAP,
		BUTTON_MANUAL_LOOT_SHAPER_MAP,
		BUTTON_MANUAL_LOOT_BLIGHT_MAP,
		BUTTON_MANUAL_LOOT_IDENTIFIED,
		BUTTON_MANUAL_LOOT_QUANTITY,
		BUTTON_MANUAL_LOOT_HEIGHT,
		BUTTON_MANUAL_LOOT_WIDTH,
		BUTTON_MANUAL_LOOT_CORRUPTED,
		BUTTON_MANUAL_LOOT_CORRUPTION_COUNT,
		BUTTON_MANUAL_LOOT_CLUSTER_PASSIVES_COUNT,
		BUTTON_MANUAL_LOOT_ELDER_INFLUENCE,
		BUTTON_MANUAL_LOOT_SHAPER_INFLUENCE,
		BUTTON_MANUAL_LOOT_CRUSADER_INFLUENCE,
		BUTTON_MANUAL_LOOT_REDEEMER_INFLUENCE,
		BUTTON_MANUAL_LOOT_HUNTER_INFLUENCE,
		BUTTON_MANUAL_LOOT_WARLORD_INFLUENCE,
		BUTTON_MANUAL_LOOT_SYNTHESISED,
		BUTTON_MANUAL_LOOT_FRACTURED,
		BUTTON_MANUAL_LOOT_ENCHANTMENT,
		BUTTON_MANUAL_LOOT_MIRRORED,
		BUTTON_HEADER_SEPARATOR,
		BUTTON_DEACTIVATE_HEADER_SEPARATOR,
		BUTTON_DISABLE_FILTER_BLOCK,
		BUTTON_ENABLE_FILTER_BLOCK,

		BUTTON_SWITCHER_VAALED,
		BUTTON_SWITCHER_IDENTIFIED,
		BUTTON_SWITCHER_ENCHANT,
		BUTTON_SWITCHER_ALTERNATE_GEM,
		BUTTON_SWITCHER_MIRRORED,

		BUTTON_SWITCHER_INFLUENCE_SHAPER,
		BUTTON_SWITCHER_INFLUENCE_ELDER,
		BUTTON_SWITCHER_INFLUENCE_CRUSADER,
		BUTTON_SWITCHER_INFLUENCE_REDEEMER,
		BUTTON_SWITCHER_INFLUENCE_WARLORD,
		BUTTON_SWITCHER_INFLUENCE_HUNTER,

		BUTTON_SWITCHER_INFLUENCE,
		BUTTON_SWITCHER_SPECIAL_STATUS,

		BUTTON_SWITCHER_BLIGHTED,
		BUTTON_SWITCHER_REPLICA,
		BUTTON_SWITCHER_FRACTURED,
		BUTTON_SWITCHER_SYNTHESISED,

		BUTTON_INFLUENCE_ALL_OR_ONEOF,

		BUTTON_BASE_DATA_CONDITION_REGULAR,
		BUTTON_BASE_DATA_INPUT_REGULAR,
		BUTTON_BASE_DATA_RARITY_REGULAR,
		BUTTON_KIND_OF_ALTERNATE_QUALITY,
		BUTTON_EXACT_MATCH


	};

	enum BaseDataOrder
	{
		DATA_RARITY					=0,	
		DATA_ITEM_LEVEL				=1,
		DATA_REQUIRED_LEVEL			=2,
		DATA_AREA_LEVEL				=3,
		DATA_SOCKETS				=4,		
		DATA_LINKS					=5,		
		DATA_SOCKET_GROUP			=6,		
		DATA_QUALITY				=7,		
		DATA_GEM_LEVEL				=8,		
		DATA_MAP_TIER				=9,		
		DATA_SHAPER_MAP				=10,		
		DATA_ELDER_MAP				=11,		
		DATA_WIDTH					=12,		
		DATA_HEIGHT					=13,		
		DATA_STACK_SIZE				=14,		
		DATA_CORRUPTED				=15,

		DATA_AND_SHAPER				=16,
		DATA_OR_SHAPER				=17,

		DATA_AND_ELDER				=18,
		DATA_OR_ELDER				=19,

		DATA_AND_CRUSADER			=20,
		DATA_OR_CRUSADER			=21,

		DATA_AND_REDEEMER			=22,
		DATA_OR_REDEEMER			=23,

		DATA_AND_HUNTER				=24,
		DATA_OR_HUNTER				=25,

		DATA_AND_WARLORD			=26,
		DATA_OR_WARLORD				=27,

		DATA_SYNTHESISED			=28,		
		DATA_FRACTURED				=29,		
		DATA_ENCHANTMENT			=30,	
		DATA_IDENTIFIED				=31,
		DATA_BLIGHTED				=32,
		DATA_SHAPER					=33,
		DATA_ELDER					=34,
		DATA_CORRUPTION_MODS		=35,
		DATA_MIRRORED_ITEM			=36,
		DATA_NO_INFLUENCE_OR		=37,
		DATA_NO_INFLUENCE_AND		=38,
		DATA_ALTERNATE_QUALITY		=39,
		DATA_IS_REPLICA				=40,


	};

	enum DefaultAlertSound
	{
		SOUND_NONE = 0,
		SOUND_01,
		SOUND_02,
		SOUND_03,
		SOUND_04,
		SOUND_05,
		SOUND_06,
		SOUND_07,
		SOUND_08,
		SOUND_09,
		SOUND_10,
		SOUND_11,
		SOUND_12,
		SOUND_13,
		SOUND_14,
		SOUND_15,
		SOUND_16,
		SOUND_SHAPER_ALCHEMY,
		SOUND_SHAPER_BLESSED,
		SOUND_SHAPER_CHAOS,
		SOUND_SHAPER_DIVINE,
		SOUND_SHAPER_EXALTED,
		SOUND_SHAPER_FUSING,
		SOUND_SHAPER_GENERAL,
		SOUND_SHAPER_MIRROR,
		SOUND_SHAPER_REGAL,
		SOUND_SHAPER_VAAL
	};

	enum WindowSearchMode
	{
		ITEM,
		DEFAULT_DROP_SOUND,
		CUSTOM_DROP_SOUND,
		BASE_DATA_VERTICAL_LIST,
		EXPLICIT_ARCHNEMESIS_CLASS_VERTICAL_LIST,
		BASE_CLASS_SEARCH_LIST,
		ARCHNEMESIS_LIST,
		ENCHANTMENT_SEARCH_LIST,
		CLUSTER_ENCHANTMENT_SEARCH_LIST,
		OPEN_LOOT_FILTER_SEARCH_LIST,
		LOOT_SIMULATOR_PATTERN
	};

	enum WindowAcceptCancelMode
	{
		AC_unsave_open,
		AC_exit_program,
		AC_new_loot_filter,
		AC_remove_separator,
		AC_remove_all_sound
	};

	enum WindowSocketsColorMode
	{
		WINDOW_MODE_SOCKET_GROUP,
		WINDOW_MODE_SOCKET
	};

	enum CostList
	{
		TRASH,
		LOW_COST,
		MID_COST,
		HIGH_COST,
		TOP_COST,
		UNDISPUTED_BEST_AXE_IN_THE_GAME
	};

	enum BoolData
	{
		BOOL_RARITY,
		BOOL_ITEM_LEVEL,
		BOOL_DROP_LEVEL,
		BOOL_AREA_LEVEL,
		BOOL_SOCKETS,
		BOOL_LINKS,
		BOOL_SOCKET_GROUP,
		
		BOOL_QUALITY,
		BOOL_GEM_LEVEL,
		
		BOOL_MAP_TIER,
		BOOL_SHAPER_MAP,
		BOOL_ELDER_MAP,
		
		BOOL_WIDTH,
		BOOL_HEIGHT,
		BOOL_STACK_SIZE,
		
		BOOL_CORRUPTION,

		BOOL_AND_SHAPER,
		BOOL_OR_SHAPER,
		BOOL_AND_ELDER,
		BOOL_OR_ELDER,
		BOOL_AND_CRUSADER,
		BOOL_OR_CRUSADER,
		BOOL_AND_REDEEMER,
		BOOL_OR_REDEEMER,
		BOOL_AND_HUNTER,
		BOOL_OR_HUNTER,
		BOOL_AND_WARLORD,
		BOOL_OR_WARLORD,

		BOOL_SYNTHESISED,
		BOOL_FRACTURED,
		BOOL_ANY_ENCHANTMENT,
		BOOL_IDENTIFIED,
		BOOL_BLIGHTED,
		BOOL_SHAPER,
		BOOL_ELDER,
		BOOL_CORRUPTION_IMPLICITES,
		BOOL_MIRRORED_ITEM,
		BOOL_NO_INFLUENCE_OR,
		BOOL_NO_INFLUENCE_AND,
		BOOL_ALTERNATE_QUALITY,
		BOOL_REPLICA

	};

	enum LocalisationList
	{
		EN,
		RU
	};

	enum OilId
	{
		CLEAR,
		SEPIA,
		AMBER,
		VERDANT,
		TEAL,
		AZURE,
		VIOLET,
		CRIMSON,
		BLACK,
		OPALESCENT,
		SILVER,
		GOLDEN
	};

	enum AutogenSaveMode
	{
		VERY_LOW,
		LOW,
		DEFAULT,
		RICH,
		VERY_RICH,
		SOURCE
	};

	enum FilterBlockButtonType
	{
		FBBT_INPUT_FIELD,
		FBBT_CHECKBOX,
		FBBT_DROP_LIST_RARITY,
		FBBT_SOCKET_GROUP,
		FBBT_INPUT_FIELD_ANY,
		FBBT_DROP_LIST_ALTERNATE_QUALITY
	};

	enum SwitcherState
	{
		SWITCHER_STATE_DEACTIVATE,
		SWITCHER_STATE_ACTIVATE,
		SWITCHER_STATE_OFF
	};

	enum AlternateQualityType
	{
		AQT_NONE,
		AQT_DIVERGENT,
		AQT_PHANTASMAL,
		AQT_ANOMALOUS
	};


};
