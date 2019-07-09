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
		PROPHECY
	};
	enum GameColors {RED, GREEN,BLUE, BROWN, WHITE, YELLOW};
	enum IconShape {CIRCLE, DIAMOND,HEXAGON, SQUARE, STAR, TRIANGLE};
	enum IconSize {LARGE, MEDIUM, SMALL};
	enum ConditionSymbols {LEQUAL, LESS, EQUAL, BIGGER, BEQUAL};

	enum PositionMaster {WINDOW, FILTER_BLOCK, SCREEN};
	enum PositionMode {LEFT, MID, RIGHT, UP, DOWN};

};
