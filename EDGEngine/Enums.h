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
		CUSTOM_ALERT_SOUND
	};
	enum GameColors {RED, GREEN,BLUE, BROWN, WHITE, YELLOW};
	enum IconShape {CIRCLE, DIAMOND,HEXAGON, SQUARE, STAR, TRIANGLE};
	enum IconSize {LARGE, MEDIUM, SMALL};
	enum ConditionSymbols {LEQUAL, LESS, EQUAL, BIGGER, BEQUAL};

	enum PositionMaster {WINDOW, FILTER_BLOCK, SCREEN};
	enum PositionMode {LEFT, MID, RIGHT, UP, DOWN};

	enum ButtonType
	{
		BUTTON_NONE,
		BUTTON_CORRUPTION,
		BUTTON_CONDITION_LINKS, BUTTON_LINKS,
		BUTTON_CONDITION_RARITY, BUTTON_RARITY,
		BUTTON_FONT_SIZE, BUTTON_TEXT_COLOR, BUTTON_BORDER_COLOR, BUTTON_BG_COLOR,
		BUTTON_SHAPER_ITEM,
		BUTTON_ELDER_ITEM,
		BUTTON_IDENTIFIED,
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

		BUTTON_OPEN_DEFAULT_DROP_SOUND_WINDOW,
		BUTTON_OPEN_CUSTOM_DROP_SOUND_WINDOW,

		BUTTON_REMOVE_EXPLICIT_GROUP,
		BUTTON_REMOVE_BASE_DATA
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
		DATA_SHAPER_ITEM			=15,		
		DATA_ELDER_ITEM				=16,		
		DATA_SYNTHESISED			=17,		
		DATA_FRACTURED				=18,		
		DATA_ENCHANTMENT			=19,	
		DATA_IDENTIFIED				=20
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

	enum TextSearchMode
	{
		ITEM,
		DEFAULT_DROP_SOUND,
		CUSTOM_DROP_SOUND
	};


};
