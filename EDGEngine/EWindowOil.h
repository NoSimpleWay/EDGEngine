#pragma once
#include "EWindow.h"
#include "Enums.h"

class EWindowOil : public EWindow
{
public:

	EButton* link_to_search_button;
	std::string cached_text_search;

	std::vector <int> oil_count = std::vector<int>(12, 0);

	EWindowOil(int _id, bool _can_be_closed);

	void create_oil_button(int _oil_id, std::string _name);

	void update_passives_button();

	std::vector <EButton*> passive_button_list;
	std::vector <EButton*> oil_button_list;

	virtual void update(float _d);

	virtual void draw(Batcher* _batch, float _delta);

	virtual void update_localisation();

	virtual void input_event(EButton* _b);



};