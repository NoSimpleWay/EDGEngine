#pragma once
#include "Batcher.h"
#include "EButton.h"
#include "EGabarite.h"




class EButton;
class EWindow
{
	
public:
	

	float pos_x;
	float pos_y;

	float relative_x;
	float relative_y;

	float window_size_x=100;
	float window_size_y=200;

	bool is_active = true;

	bool have_bg=true;
	EColor* bg_color = new EColor(1, 1, 1, 1);

	int id;

	EWindow(int _id);
	EWindow(int _id, bool _can_be_closed);
	~EWindow();

	virtual void update(float _d);
	void default_update(float _d);
	void defaul_draw(Batcher* _batch);
	void default_text_pass(Batcher* _batch);

	string name;

	bool is_overlap();

	
	

	virtual void draw(Batcher* _batch, float _delta);
	virtual void button_event(EButton* _b);
	virtual void input_event(EButton* _b);
	virtual void text_pass(Batcher* _batch);

	static int SCR_WIDTH;
	static int SCR_HEIGHT;
	static int top_layer_id;

	static GLFWwindow* main_window;

	Enums::PositionMode align_x = Enums::PositionMode::MID;
	Enums::PositionMode align_y = Enums::PositionMode::MID;

	std::vector<EButton*> button_list;
	std::vector<EButton*> default_button_list;

	bool have_rama = true;
	EColor* rama_color = new EColor(1.0f, 1.0f, 1.0f, 1.0f);

	bool have_shadow = true;
	bool can_be_closed = true;

	virtual void manual_event();

	virtual void close_action();
};

