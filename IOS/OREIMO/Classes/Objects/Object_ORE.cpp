#include "Object_ORE.h"
#include "ui/UiButton.h"
extern Node* OREL;
extern Node* ORER;
extern Node* OREU;

std::string green_tex = ".\\Resources\\Buttons\\Game\\ore_step1.png";
std::string yelow_tex = ".\\Resources\\Buttons\\Game\\ore_step2.png";
std::string red1_tex = ".\\Resources\\Buttons\\Game\\ore_step3_1.png";
std::string red2_tex = ".\\Resources\\Buttons\\Game\\ore_step3_2.png";

namespace pre_save
{
	extern bool ORE_LEFT_VIS;
	extern bool ORE_RIGHT_VIS;
	extern bool ORE_LEFT_PREUSE;// эту херню заменить и убрать на место нее должна меняться текстура
	extern bool ORE_RIGHT_PREUSE;
	extern bool ORE_LEFT_USE;
	extern bool ORE_RIGHT_USE;
}

void unselect_ore(ui::Button* ore_button)
{
	ore_button->loadTextureNormal(green_tex);
	ore_button->loadTexturePressed(green_tex);
}

void select_ore(ui::Button* ore_button)
{
	ore_button->loadTextureNormal(yelow_tex);
	ore_button->loadTexturePressed(yelow_tex);
}

void select_ore_twice(ui::Button* ore_button)
{
	auto swich_1 = CallFunc::create([=]()
	{
		ore_button->loadTextureNormal(red1_tex);
	});
	auto swich_2 = CallFunc::create([=]()
	{
		ore_button->loadTextureNormal(red2_tex);
	});

	ore_button->runAction(RepeatForever::create(Sequence::create(swich_1, DelayTime::create(0.5f), swich_2, DelayTime::create(0.5f), nullptr)));
	ore_button->setTouchEnabled(false);
}

Object_ORE::Object_ORE(int cur_ore, any_enum::posicion_sprite cur_pos)
{


	if (cur_pos == any_enum::posicion_sprite::left)
	{
		this->my_node = OREL;
		auto my_button = static_cast<ui::Button*>(OREL->getChildByTag(2));
		auto smeh_button = static_cast<ui::Button*>(ORER->getChildByTag(2));
		my_button->setTouchEnabled(true);
		
		my_button->addClickEventListener([=](Ref*)
		{
			if (pre_save::ORE_LEFT_PREUSE == true)
			{
					pre_save::ORE_LEFT_USE = true;
					select_ore_twice(my_button);
					
			}
			else
			{
				if (pre_save::ORE_RIGHT_USE == false)
				{
					pre_save::ORE_LEFT_PREUSE = true;
					select_ore(my_button);
					if (pre_save::ORE_RIGHT_PREUSE == true)
					{
						pre_save::ORE_RIGHT_PREUSE = false;
						unselect_ore(smeh_button);
					}
				}
			}
		});
	}
	else if (cur_pos == any_enum::posicion_sprite::right)
	{
		this->my_node = ORER;
		auto my_button = static_cast<ui::Button*>(ORER->getChildByTag(2));
		auto smeh_button = static_cast<ui::Button*>(OREL->getChildByTag(2));
		my_button->setTouchEnabled(true);
		

		my_button->addClickEventListener([=](Ref*)
		{
			if (pre_save::ORE_RIGHT_PREUSE == true)
			{
				pre_save::ORE_RIGHT_USE = true;
				select_ore_twice(my_button);

			}
			else
			{
				if (pre_save::ORE_LEFT_USE == false)
				{
					pre_save::ORE_RIGHT_PREUSE = true;
					select_ore(my_button);

					if (pre_save::ORE_LEFT_PREUSE == true)
					{
						pre_save::ORE_LEFT_PREUSE = false;
						unselect_ore(smeh_button);
					}

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