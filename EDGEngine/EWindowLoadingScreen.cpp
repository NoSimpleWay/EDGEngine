#include "EWindow.h"
#include "EControl.h"
#include "Enums.h"

class EWindowLoadingScreen : public EWindow
{
public:
	int load_progress = 0;
	int item_count = 0;

	EWindowLoadingScreen(int _id, bool _can_be_closed) :EWindow(_id, _can_be_closed)
	{
		align_x = Enums::PositionMode::MID;
		align_y = Enums::PositionMode::MID;

		window_size_x = 1100.0f;
		window_size_y = 150.0f;

		bg_color->set(0.2f, 0.1f, 0.0f, 0.8f);

		is_active = true;
	}

	virtual void update(float _d)
	{

	}

	virtual void draw(Batcher* _batch, float _delta)
	{
		for (int i = 0; i < 100; i++)
		{
			if ( load_progress >= i / 100.0f * item_count )
			{_batch->setcolor(EColorCollection::GREEN);}
			else
			{_batch->setcolor(EColorCollection::RED);}

			_batch->draw_rect_with_uv (pos_x + 50.0f + 10.0f * i, pos_y + 70.0f, 8.0f, 8.0f, DefaultGabarite::gabarite_white);
		}


	}
};