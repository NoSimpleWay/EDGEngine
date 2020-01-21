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
		PROPHECY,
		CUSTOM_ALERT_SOUND,
		HAS_ENCHANTMENT,
		C_SEPARATOR,
		C_AUTOGEN,
		IS_BLIGHTED_MAP,
		IS_HAVE_INFLUENCE_OR,
		IS_HAVE_INFLUENCE_AND
	};
	enum GameColors {RED, GREEN, BLUE, BROWN, WHITE, YELLOW};
	enum IconShape {CIRCLE, DIAMOND, HEXAGON, SQUARE, STAR, TRIANGLE};
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
		BUTTON_SOCKET_GROUP,
		BUTTON_CONDITION_STACK_SIZE, BUTTON_STACK_SIZE,
		BUTTON_CONDITION_GEM_LEVEL, BUTTON_GEM_LEVEL,
		BUTTON_ELDER_MAP,
		BUTTON_SHAPER_MAP,
		BUTTON_CONDITION_MAP_TIER, BUTTON_MAP_TIER,
		BUTTON_FILTER_BLOCK_TO_CONSOLE,
		BUTTON_SOCKET_RED,
		BUTTON_SOCKET_GREEN,
		BUTTON_SOCKET_BLUE,
		BUTTON_SOCKET_WHITE,

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
		BUTTON_SEARCH_PROPHECY,
		BUTTON_SEARCH_LOOT_FILTER,
		BUTTON_SEARCH_LOOT_SIMULATOR_PATTERN,

		BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW,
		BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW,

		BUTTON_REMOVE_EXPLICIT_GROUP,
		BUTTON_REMOVE_BASE_CLASS,
		BUTTON_REMOVE_BASE_DATA,
		BUTTON_REMOVE_PROPHECY,
		BUTTON_REMOVE_ENCHANTEMENT,

		BUTTON_OPEN_BASE_DATA_WINDOW,
		BUTTON_OPEN_BASE_CLASS_WINDOW,
		BUTTON_ADD_EXPLICIT_GROUP,
		BUTTON_ACTIVE_BASE_CLASS_LIST,
		BUTTON_ACTIVE_PROPHECY_LIST,
		BUTTON_ACTIVE_ENCHANTEMENT_LIST,
		BUTTON_OPEN_EXPLICIT_PROPHECY_CLASS_WINDOW,
		BUTTON_ADD_EXPLICIT_ELEMENT,
		BUTTON_ADD_BASE_CLASS,
		BUTTON_EXPLICIT_FILTER_BLOCK_LIST,
		BUTTON_CLASS_FILTER_BLOCK_LIST,
		BUTTON_ENCHANTMENT_FILTER_BLOCK_LIST,
		BUTTON_PROPHECY_FILTER_BLOCK_LIST,

		BUTTON_MINIMAP_ICON_SELECT_SHAPE,
		BUTTON_MINIMAP_ICON_SELECT_COLOR,
		BUTTON_MINIMAP_ICON_SELECT_SIZE,

		BUTTON_CHECKER_MINIMAP_ICON,

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
		BUTTON_FILTER_BLOCK_TAB,
		BUTTON_OPEN_PATTERN_WINDOW,

		BUTTON_REFRESH_LOOT_SIMULATOR,
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

		BUTTON_SELECT_LOOT_PATTERN
	};

	enum BaseDataOrder
	{
		DATA_RARITY					=0,	
		DATA_ITEM_LEVEL				=1,
		DATA_REQUIRED_LEVEL			=2,		
		DATA_SOCKETS				=3,		
		DATA_LINKS					=4,		
		DATA_SOCKET_GROUP			=5,		
		DATA_QUALITY				=6,		
		DATA_GEM_LEVEL				=7,		
		DATA_MAP_TIER				=8,		
		DATA_SHAPER_MAP				=9,		
		DATA_ELDER_MAP				=10,		
		DATA_WIDTH					=11,		
		DATA_HEIGHT					=12,		
		DATA_STACK_SIZE				=13,		
		DATA_CORRUPTED				=14,

		DATA_AND_SHAPER				=15,
		DATA_OR_SHAPER				=16,

		DATA_AND_ELDER				=17,
		DATA_OR_ELDER				=18,

		DATA_AND_CRUSADER			=19,
		DATA_OR_CRUSADER			=20,

		DATA_AND_REDEEMER			=21,
		DATA_OR_REDEEMER			=22,

		DATA_AND_HUNTER				=23,
		DATA_OR_HUNTER				=24,

		DATA_AND_WARLORD			=25,
		DATA_OR_WARLORD				=26,

		DATA_SYNTHESISED			=27,		
		DATA_FRACTURED				=28,		
		DATA_ENCHANTMENT			=29,	
		DATA_IDENTIFIED				=30,
		DATA_BLIGHTED				=31,
		DATA_SHAPER					=32,
		DATA_ELDER					=33,

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
		EXPLICIT_PROPHECY_CLASS_VERTICAL_LIST,
		BASE_CLASS_SEARCH_LIST,
		PROPHECY_SEARCH_LIST,
		ENCHANTMENT_SEARCH_LIST,
		OPEN_LOOT_FILTER_SEARCH_LIST,
		LOOT_SIMULATOR_PATTERN
	};

	enum WindowAcceptCancelMode
	{
		AC_unsave_open,
		AC_exit_program,
		AC_new_loot_filter,
		AC_remove_separator,
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
		BOOL_AND_CRUSADER = 19,
		BOOL_OR_CRUSADER = 20,
		BOOL_AND_REDEEMER = 21,
		BOOL_OR_REDEEMER = 22,
		BOOL_AND_HUNTER = 23,
		BOOL_OR_HUNTER = 24,
		BOOL_AND_WARLORD = 25,
		BOOL_OR_WARLORD = 26,

		BOOL_SYNTHESISED,
		BOOL_FRACTURED,
		BOOL_ANY_ENCHANTMENT,
		BOOL_IDENTIFIED,
		BOOL_BLIGHTED,
		BOOL_SHAPER,
		BOOL_ELDER

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


};
