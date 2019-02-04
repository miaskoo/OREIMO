#include "Object_ORE.h"
#include "ui/UiButton.h"
extern Node* OREL;
extern Node* ORER;
extern Node* OREU;
namespace pre_save
{
	extern bool ORE_LEFT_VIS;
	extern bool ORE_RIGHT_VIS;
	extern bool ORE_LEFT_PREUSE;// эту херню заменить и убрать на место нее должна меняться текстура
	extern bool ORE_RIGHT_PREUSE;
	extern bool ORE_LEFT_USE;
	extern bool ORE_RIGHT_USE;
}

Object_ORE::Object_ORE(int cur_ore, any_enum::posicion_sprite cur_pos)
{
	if (cur_pos == any_enum::posicion_sprite::left)
	{
		this->my_node = OREL;
		static_cast<ui::Button*>(this->my_node->getChildByTag(2))->addClickEventListener([=](Ref*)
		{
			if (pre_save::ORE_LEFT_PREUSE == true)
			{
					pre_save::ORE_LEFT_USE = true;
			}
			else
			{
				if (pre_save::ORE_RIGHT_USE == false)
				{
					pre_save::ORE_LEFT_PREUSE = true;
					if (pre_save::ORE_RIGHT_PREUSE == true)
						pre_save::ORE_RIGHT_PREUSE = false;
				}
			}
		});
	}
	else if (cur_pos == any_enum::posicion_sprite::right)
	{
		this->my_node = ORER;
		static_cast<ui::Button*>(this->my_node->getChildByTag(2))->addClickEventListener([=](Ref*)
		{
			if (pre_save::ORE_RIGHT_PREUSE == true)
			{
				pre_save::ORE_RIGHT_USE = true;
			}
			else
			{
				if (pre_save::ORE_LEFT_USE == false)
				{
					pre_save::ORE_RIGHT_PREUSE = true;
					if (pre_save::ORE_LEFT_PREUSE == true)
						pre_save::ORE_LEFT_PREUSE = false;

				}
			}
		});
	}
	else if (cur_pos == any_enum::posicion_sprite::custom)
	{
		this->my_node = OREU;
	}
	else
		return;

	this->cur_ore = cur_ore;
	static_cast<Sprite*>(this->my_node->getChildByTag(1))->setTexture(ORE_DIR[this->cur_ore]);

}

swich_node Object_ORE::draw()
{
	return{ this->my_node, nullptr };
}

int Object_ORE::Get_Ore_num()
{
	return this->cur_ore;
}