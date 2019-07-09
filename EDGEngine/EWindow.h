#pragma once
#include "Batcher.h"
#include "EButton.h"




class EButton;
class EWindow
{
	
public:
	

	float pos_x;
	float pos_y;

	float size_x=100;
	float size_y=200;

	bool is_active = true;

	bool have_bg=true;
	EColor* bg_color = new EColor(1, 1, 1, 1);

	EWindow();
	~EWindow();

	void update(float _d);
	void defaul_draw(Batcher* _batch);

	string name;

	virtual void draw(Batcher* _batch, float _delta);
	virtual void button_event(EButton* _b);
	virtual void input_event(EButton* _b);

	static int SCR_WIDTH;
	static int SCR_HEIGHT;
	static int top_layer_id;

	static GLFWwindow* main_window;
};

