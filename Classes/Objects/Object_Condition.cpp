#include "Object_Condition.h"
#include "ui/UiButton.h"

extern Node *Game_Mode;
extern Node *OREL;
extern Node *ORER;

extern bool check_point(any_enum::name_sprite name, int point);
bool check_all_ore(any_enum::open_resurce *ore_data, int size);
extern bool get_vis_ore(Node *ore);

Object_Condition::Object_Condition(any_enum::open_resurce *ore_data, any_enum::name_sprite name, int point, any_enum::use_ore use)
{
	for (int n = 0; n < 64; n++)
	{
		this->ore_data[n] = ore_data[n];
	}
	this->CHAPTER = name;
	this->POINT = point;
	this->CUR_USE = use;
}


swich_node Object_Condition::draw() //если не проходит проверки возвращает нулевой указатель - а если проходит указатель игры
{
	bool cheking = true;

	if (this->CUR_USE != any_enum::nonuse) // если есть условие юзание прового или левого стика
	{
		if ((this->CUR_USE == any_enum::OREL && get_vis_ore(OREL) == false) || (this->CUR_USE == any_enum::ORER && get_vis_ore(ORER) == false)) //если оно не выполнено 
		{
			cheking = false;
		}
	}

	if (this->POINT != 0)//проверка на очки
	{
		if (check_point(this->CHAPTER, this->POINT) == false)
		{
			cheking = false;
		}
	}

	if (check_all_ore(this->ore_data, any_enum::size_ore) == false)
	{
		cheking = false;
	}


	if (cheking == false)
		return{ nullptr, nullptr };
	else
		return{ Game_Mode, nullptr };
}

