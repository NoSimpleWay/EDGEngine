#include "EButtonText.h"



EButtonText::EButtonText(float _x, float _y, float _sx, float _sy)
{
	have_text = true;
	have_rama = true;
	rama_thikness = 2;
	rama_color->set(.2f, .3f, .4f, .5f);
}

void EButtonText::click_event()
{
}
