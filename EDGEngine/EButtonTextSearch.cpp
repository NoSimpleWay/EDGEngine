#include "EButtonTextSearch.h"

EButtonTextSearch::EButtonTextSearch(float _x, float _y, float _sx, float _sy, Enums::ButtonType _type):EButton(_x,_y,_sx,_sy)
{
	button_type = _type;

	have_rama = true;
	have_text = true;

	have_icon = false;


}

void EButtonTextSearch::click_event()
{

}

void EButtonTextSearch::right_click_event()
{

}

void EButtonTextSearch::update_localisation()
{
}
