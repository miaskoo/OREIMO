#include "Object_Condition.h"

namespace pre_save
{
	extern bool ORE_LEFT_USE;
	extern bool ORE_RIGHT_USE;
	extern any_enum::open_resurce pre_ore_data[64];
	extern int POINTS[3];
}
extern Node *Game_Mode;

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
		if ((this->CUR_USE == any_enum::OREL && pre_save::ORE_LEFT_USE == false) || (this->CUR_USE == any_enum::ORER && pre_save::ORE_RIGHT_USE == false)) //если оно не выполнено 
			cheking = false;
		else//если выполнено обнуляем
		{
			if (this->CUR_USE == any_enum::OREL)
				pre_save::ORE_LEFT_USE = false;
			else if (this->CUR_USE == any_enum::ORER)
				pre_save::ORE_RIGHT_USE = false;
		}
	}

	if (this->POINT != 0)//проверка на очки
	{
		if (pre_save::POINTS[static_cast<int>(this->CHAPTER)] < this->POINT)
			cheking = false;
	}

	for (int n = 0; n < 64; n++)
	{
		if (this->ore_data[n] != any_enum::lock && pre_save::pre_ore_data[n] == any_enum::lock)
			cheking = false;
	}

	if (cheking == false)
		return{ nullptr, nullptr };
	else
		return{ Game_Mode, nullptr };
}

