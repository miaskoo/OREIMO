#include "Actions.h"
#include "Classes\Scripts\Page.h"
#include "ui/UiButton.h"


extern void unselect_ore(ui::Button* ore_button);
extern void clear_vis_ore(Node *ore);

const float time_fade = 0.7f;
const float smeh_position = 50;

const int TEXTBOX_X = -380;
const int TEXTBOX_Y = -60;

const int BLACKSCRIN_WIDTH = 1280;
const int BLACKSCRIN_HEIGHT = 720;

extern Node* OREL;
extern Node* ORER;
extern Node* Black_screen;
extern Node* Polos_screen;
extern Vec2 ANCHOR_POINT_SPRITE_ELEMENT;

inline float need_null(bool x, float y)
{return x == true ? 0.f : y;}
inline bool check_null(void *ptr) { return ptr != nullptr; }

extern map<any_enum::posicion_sprite, positions> POS_HEAD;

extern void relese_old_state(Node *old_node);

bool All_fast = false;

namespace Action_mixed
{
	bool swish(Node *cur_old, Node *cur_new, bool wait, Page *next, bool fast)// (next - функция циклично запускаюшая действия?)
	{
		
		auto choise = CallFunc::create([=]()
		{
			if (check_null(next))
				next->draw();
		});

		auto end_fadeout = CallFunc::create([=]()
		{
			//relese_old_state(cur_old);//отчищаем старое состояние
		});

		bool cur_fast = fast;

		if (All_fast == true)
		{
			cur_fast = true;
		}
		float cur_tine_fade = need_null(cur_fast, time_fade);

		if (cur_old != nullptr)
		{
			cur_old->runAction(Sequence::create(FadeOut::create(cur_tine_fade), end_fadeout, nullptr));
		}
		if (cur_new != nullptr)
		{
			cur_new->runAction(FadeIn::create(cur_tine_fade));
		}

		if (wait == false)
			Game_Mode->runAction(choise);
		else
			Game_Mode->runAction(Sequence::create(DelayTime::create(cur_tine_fade), choise, nullptr));

		return true;
	}
}

namespace Action_scene
{
	float speed = 0.03;

	bool swich(Node *cur_old, Node *cur_new, type_swich cur_swich, bool wait, Page *next)
	{
		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});
		switch (cur_swich)
		{
		case NULL_TIME:
		{
			Action_mixed::swish(cur_old, cur_new, wait, next, true);
			break;
		}
		case SIMPLE:
			Action_mixed::swish(cur_old, cur_new, wait, next);
		default:
			return false;
			break;
		}
		return true;
	}

	bool action(Node *cur, type_action _cur_action, bool wait, Page *next)
	{

		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});

		type_action cur_action = _cur_action;//для того чтобы мы могли выводить черный экран и над текст боксом
		int cur_order = 6;
		switch (cur_action)
		{
		case MBLACK_IN:
			cur_action = BLACK_IN;
			break;
		case MBLACK_OUT:
			cur_action = BLACK_OUT;
			break;
		case MPOLOS_IN:
			cur_action = POLOS_IN;
			break;
		case MPOLOS_OUT:
			cur_action = POLOS_OUT;
			break;
		case MSLASH_WS_IN:
			cur_action = SLASH_WS_IN;
			break;
		case MSLASH_WS_OUT:
			cur_action = SLASH_WS_OUT;
			break;
		case MSLASH_AD_IN:
			cur_action = SLASH_AD_IN;
			break;
		case MSLASH_AD_OUT:
			cur_action = SLASH_AD_OUT;
			break;
		default:
			cur_order = 4;
		}

		Black_screen->setLocalZOrder(cur_order);
		Polos_screen->setLocalZOrder(cur_order);

		switch (cur_action)
		{
		case POLOS_IN:
		{
			//auto Polos_screen = Game_Mode->getChildByName("Polos_screen");
			auto Polos_simple = Polos_screen->getChildByTag(0);
			auto Polos_reverse = Polos_screen->getChildByTag(1);

			Polos_screen->setVisible(true);
			Polos_simple->setVisible(true);
			Polos_reverse->setVisible(false);

			const int size_polos = 8;

			auto swich_scene = CallFunc::create([=]()
			{
				for (int n = 0; n < size_polos; n++)
				{
					Polos_simple->getChildByTag(n)->setScaleX(0.01f);
					Polos_simple->getChildByTag(n)->runAction(ScaleTo::create(need_null(All_fast, 1.f), 1.f, 1.f));
				}
			});

			if (wait == false)
			{
				Game_Mode->runAction(Sequence::create(choise, swich_scene, nullptr));
			}
			else
			{
				Game_Mode->runAction(Sequence::create(swich_scene, DelayTime::create(need_null(All_fast, 1.f)), choise,  nullptr));
			}

			break;
		}
		case POLOS_OUT:
		{
			//auto Polos_screen = Game_Mode->getChildByName("Polos_screen");
			auto Polos_simple = Polos_screen->getChildByTag(0);
			auto Polos_reverse = Polos_screen->getChildByTag(1);
			Polos_screen->setVisible(true);
			Polos_reverse->setVisible(true);
			Polos_simple->setVisible(false);
			const int size_polos = 8;


			

			auto swich_scene = CallFunc::create([=]()
			{
				Polos_reverse->setVisible(true);
				for (int n = 0; n < size_polos; n++)
				{
					Polos_reverse->getChildByTag(n)->setScaleX(1.f);
					Polos_reverse->getChildByTag(n)->runAction(ScaleTo::create(need_null(All_fast, 1.f), 0.01, 100));
				}
			});

			auto swich_end = CallFunc::create([=]()
			{
				Polos_reverse->setVisible(false);
			});


			if (wait == false)
			{
				Game_Mode->runAction(Sequence::create(choise, swich_scene, DelayTime::create(need_null(All_fast, 1.f)), swich_end, nullptr));
			}
			else
			{
				Game_Mode->runAction(Sequence::create(swich_scene, DelayTime::create(need_null(All_fast, 1.f)), swich_end, choise, nullptr));
			}


			break;
		}
		case BLACK_IN://темный экран появляется
		{
			//auto Black_screen = Game_Mode->getChildByName("Black_screen");
			Black_screen->setPosition(0, 0);
			Black_screen->setOpacity(0);
			
			if (wait == false)
			{
				Black_screen->runAction(Sequence::create((FadeIn::create(need_null(All_fast, 1.f))), nullptr));
				Game_Mode->runAction(choise);
			}
			else
			{
				Black_screen->runAction(Sequence::create((FadeIn::create(need_null(All_fast, 1.f))), choise, nullptr));
			}
			break;
		}
		case BLACK_OUT://темный экран пропадает
		{
			//auto Black_screen = Game_Mode->getChildByName("Black_screen");
			Black_screen->setPosition(0, 0);
			Black_screen->setOpacity(255);
			if (wait == false)
			{
				Black_screen->runAction(Sequence::create((FadeOut::create(need_null(All_fast, 1.f))), nullptr));
				Game_Mode->runAction(choise);
			}
			else
			{
				Black_screen->runAction(Sequence::create((FadeOut::create(need_null(All_fast, 1.f))), choise, nullptr));
			}
			break;
		}
		case SLASH_WS_IN:
		{
		//	auto Black_screen = Game_Mode->getChildByName("Black_screen");
			Black_screen->setPosition(0, -(BLACKSCRIN_HEIGHT * 2));
			Black_screen->setOpacity(255);

			if (wait == false)
			{
				Black_screen->runAction(Sequence::create(MoveTo::create(need_null(All_fast, 1.f), Vec2(0, 0)), nullptr));
				Game_Mode->runAction(choise);
			}
			else
			{
				Black_screen->runAction(Sequence::create(MoveTo::create(need_null(All_fast, 1.f), Vec2(0, 0)), choise, nullptr));
			}
			
			break;
		}
		case SLASH_WS_OUT:
		{
		//	auto Black_screen = Game_Mode->getChildByName("Black_screen");
			Black_screen->setPosition(0, 0);
			Black_screen->setOpacity(255);

			if (wait == false)
			{
				Black_screen->runAction(Sequence::create(MoveTo::create(need_null(All_fast, 1.f), Vec2(0, (BLACKSCRIN_HEIGHT * 2))), nullptr));
				Game_Mode->runAction(choise);
			}
			else
			{
				Black_screen->runAction(Sequence::create(MoveTo::create(need_null(All_fast, 1.f), Vec2(0, (BLACKSCRIN_HEIGHT * 2))), choise, nullptr));
			}

			break;
		}
		case SLASH_AD_IN:
		{
		//	auto Black_screen = Game_Mode->getChildByName("Black_screen");
			Black_screen->setPosition(-(BLACKSCRIN_WIDTH * 2), 0);
			Black_screen->setOpacity(255);

			if (wait == false)
			{
				Black_screen->runAction(Sequence::create(MoveTo::create(need_null(All_fast, 1.f), Vec2(0, 0)), nullptr));
				Game_Mode->runAction(choise);
			}
			else
			{
				Black_screen->runAction(Sequence::create(MoveTo::create(need_null(All_fast, 1.f), Vec2(0, 0)), choise, nullptr));
			}

			break;
		}
		case SLASH_AD_OUT:
		{

		//	auto Black_screen = Game_Mode->getChildByName("Black_screen");
			Black_screen->setPosition(0, 0);
			Black_screen->setOpacity(255);

			if (wait == false)
			{
				Black_screen->runAction(Sequence::create(MoveTo::create(need_null(All_fast, 1.f), Vec2((BLACKSCRIN_WIDTH * 2), 0)), nullptr));
				Game_Mode->runAction(choise);
			}
			else
			{
				Black_screen->runAction(Sequence::create(MoveTo::create(need_null(All_fast, 1.f), Vec2((BLACKSCRIN_WIDTH * 2), 0)), choise, nullptr));
			}

			break;
		}
		case SHAKE:
		{
			if (All_fast == true)
			{
				Game_Mode->runAction(choise);
				return true;
			}

			float cur_speed = need_null(All_fast, speed);

			if (wait == false)
			{
				cur->runAction(Sequence::create(
					MoveBy::create(cur_speed, Vec2(206, 100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(-206, -100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(-206, -100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(206, 100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(106, 100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(-106, -100)), DelayTime::create(cur_speed),
					nullptr));
				Game_Mode->runAction(choise);

			}
			else
			{
				cur->runAction(Sequence::create(
					MoveBy::create(cur_speed, Vec2(206, 100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(-206, -100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(-206, -100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(206, 100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(106, 100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(-106, -100)), DelayTime::create(cur_speed), choise,
					nullptr));
			}
			break;
		}
		case PUNCH://тряска и белый экран
		{
			if (All_fast == true)
			{
				Game_Mode->runAction(choise);
				return true;
			}
			auto White_screen = Game_Mode->getChildByName("White_screen");

			float cur_speed = need_null(All_fast, speed);

			if (wait == false)
			{
				White_screen->runAction(Sequence::create(FadeIn::create(need_null(All_fast, 0.05f)), DelayTime::create(need_null(All_fast, 0.05f)), FadeOut::create(need_null(All_fast, 0.05f)), nullptr));
				cur->runAction(Sequence::create(
					DelayTime::create(need_null(All_fast, 0.2f)),
					MoveBy::create(cur_speed, Vec2(0, 150)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(0, -150)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(0, 100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(0, -100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(0, 50)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(0, -50)), DelayTime::create(cur_speed),
					nullptr));
				Game_Mode->runAction(choise);
			}
			else
			{
				White_screen->runAction(Sequence::create(FadeIn::create(need_null(All_fast, 0.05f)), DelayTime::create(need_null(All_fast, 0.05f)), FadeOut::create(need_null(All_fast, 0.05f)), nullptr));
				cur->runAction(Sequence::create(
					DelayTime::create(need_null(All_fast, 0.2f)),
					MoveBy::create(cur_speed, Vec2(0, 150)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(0, -150)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(0, 100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(0, -100)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(0, 50)), DelayTime::create(cur_speed),
					MoveBy::create(cur_speed, Vec2(0, -50)), DelayTime::create(cur_speed), choise,
					nullptr));
			}

			break;
		}
		default:
		{
			return false;
			break;
		}
		}
		return true;
	}

}

namespace Action_sprite
{
	bool swich(Node *cur_old, Node *cur_new, type_swich cur_swich, bool hide, bool wait, Page *next)
	{
		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});

		if (cur_old != nullptr && cur_new != nullptr)
		{
			cur_old->setLocalZOrder(1);
			cur_new->setLocalZOrder(2);
		}

		auto end_fadeout = CallFunc::create([=]()
		{
			//relese_old_state(cur_old);//отчищаем старое состояние
		});

		float fade_sprite_prite = need_null(All_fast, time_fade);

		switch (cur_swich)
		{
		case LTR:
		{
					if (hide == false) //пропадает ли спарйт иначе - появляется и нужно сместить по координатам
					{
						cur_new->setPosition(cur_new->getPosition() - Vec2(smeh_position, 0));
						if (wait == false)
						{
							cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(smeh_position, 0)), FadeIn::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), nullptr));
							Game_Mode->runAction(choise);
						}
						else
						{
							cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(smeh_position, 0)), FadeIn::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), choise, nullptr));
						}
						if (cur_old != nullptr)
							cur_old->runAction(Sequence::create(FadeOut::create(fade_sprite_prite), end_fadeout, nullptr));//TODO ??? что за условие, непонятно что происхотит тип старый спрайт пропадает на месте при появлении нового...
					}
					else
					{
						if (wait == false)
						{
							cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(smeh_position, 0)), FadeOut::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), end_fadeout, nullptr));
							Game_Mode->runAction(choise);
						}
						else
						{
						if (cur_old != nullptr)
							cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(smeh_position, 0)), FadeOut::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), end_fadeout, choise, nullptr));
						}
						
					}
					break;
		}
		case RTL:
		{
					if (hide == false)
					{
						cur_new->setPosition(cur_new->getPosition() + Vec2(smeh_position, 0));
						if (wait == false)
						{
							cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(-smeh_position, 0)), FadeIn::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), nullptr));
							Game_Mode->runAction(choise);
						}
						else
						{
							cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(-smeh_position, 0)), FadeIn::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), choise, nullptr));
						}
						
						if (cur_old != nullptr)
							cur_old->runAction(Sequence::create(FadeOut::create(fade_sprite_prite), end_fadeout, nullptr));
					}
					else
					{
						if (wait == false)
						{
							cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(-smeh_position, 0)), FadeOut::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), end_fadeout, nullptr));
							Game_Mode->runAction(choise);
						}
						else
						{
						if (cur_old != nullptr)
							cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(-smeh_position, 0)), FadeOut::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), end_fadeout, choise, nullptr));
						}
						
					}
					break;
		}
		case DTT: 
		{
			if (hide == false)
			{
				cur_new->setPosition(cur_new->getPosition() + Vec2(0, -smeh_position));
				if (wait == false)
				{
					cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(0, smeh_position)), FadeIn::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), nullptr));
					Game_Mode->runAction(choise);
				}
				else
				{
					cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(0, smeh_position)), FadeIn::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), choise, nullptr));
				}

				if (cur_old != nullptr)
					cur_old->runAction(Sequence::create(FadeOut::create(fade_sprite_prite), end_fadeout, nullptr));
			}
			else
			{
				if (wait == false)
				{
					cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(0, smeh_position)), FadeOut::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), end_fadeout, nullptr));
					Game_Mode->runAction(choise);
				}
				else
				{
					if (cur_old != nullptr)
						cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(fade_sprite_prite, Vec2(0, smeh_position)), FadeOut::create(fade_sprite_prite)), DelayTime::create(fade_sprite_prite), end_fadeout, choise, nullptr));
				}

			}
			break;
		}
		case NULL_TIME:
		{
			Action_mixed::swish(cur_old, cur_new, wait, next, true);
			break;
		}
		case SIMPLE:
		{
			Action_mixed::swish(cur_old, cur_new, wait, next);
			break;
		}
		default:
			return false;
			break;
		}
		return true;
	}

	bool action(Node *cur, type_action cur_action, bool hide, bool wait, Page *next)//ALERT вызвать в одном блоке можно только прыжок и двойной прыжок
	{
		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});
		auto sprite = static_cast<Sprite*>(cur->getChildByName("Sprite"));
		float time = 0.25f;
		switch (cur_action)
		{
		case MINIJUMP:
		{
			if (All_fast == true)
			{
				Game_Mode->runAction(choise);
				return true;
			}
			if (wait == false)
			{
				cur->runAction(Sequence::create(MoveBy::create(0.15f, Vec2(0, 20)), DelayTime::create(0.15f), MoveBy::create(0.15f, Vec2(0, -20)), nullptr));
				Game_Mode->runAction(choise);
			}
			else
			{
				cur->runAction(Sequence::create(MoveBy::create(0.15f, Vec2(0, 20)), DelayTime::create(0.15f), MoveBy::create(0.15f, Vec2(0, -20)), DelayTime::create(0.15f), choise, nullptr));
			}	 
			break;
		}
		case JUMP:
		{
			if (All_fast == true)
			{
				Game_Mode->runAction(choise);
				return true;
			}
			if (wait == false)
			{
				cur->runAction(Sequence::create(MoveBy::create(0.07f, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f),
					MoveBy::create(0.07f, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), nullptr));
				Game_Mode->runAction(choise);
			}
			else
			{
				cur->runAction(Sequence::create(MoveBy::create(0.07f, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f),
					MoveBy::create(0.07f, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f), choise, nullptr));
			}
					
			break;
		}
		case scale_lit:
		{

			float cur_scale = 1.0f;

			//auto sprite = static_cast<Sprite*>(cur->getChildByName("Sprite"));

			if (All_fast == true)
			{
				sprite->setScale(cur_scale);
				Game_Mode->runAction(choise);
				return true;
			}

			sprite->runAction(Sequence::create(ScaleTo::create(time, cur_scale, cur_scale), DelayTime::create(time), choise, nullptr));
			break;
		}
		case scale_mid:
		{
			float cur_scale = 1.5f;
			//auto sprite = static_cast<Sprite*>(cur->getChildByName("Sprite"));


			if (All_fast == true)
			{
				sprite->setScale(cur_scale);
				Game_Mode->runAction(choise);
				return true;
			}

			sprite->runAction(Sequence::create(ScaleTo::create(time, cur_scale, cur_scale), DelayTime::create(time), choise, nullptr));
			break;
		}
		case scale_big:
		{
			float cur_scale = 2.0f;
			


			if (All_fast == true)
			{
				sprite->setScale(cur_scale);
				Game_Mode->runAction(choise);
				return true;
			}

			sprite->runAction(Sequence::create(ScaleTo::create(time, cur_scale, cur_scale), DelayTime::create(time), choise, nullptr));
			break;
		}
		case POS_C:
		{
			Vec2 cur_pos = Vec2(POS_HEAD[any_enum::centr].x, cur->getPosition().y);

			if (All_fast == true)
			{
				cur->setPosition(cur_pos);
				Game_Mode->runAction(choise);
				return true;
			}

			cur->runAction(Sequence::create(MoveTo::create(time, cur_pos), DelayTime::create(time), choise, nullptr));
			break;
		}
		case POS_R:
		{
			Vec2 cur_pos = Vec2(POS_HEAD[any_enum::right].x, cur->getPosition().y);

			if (All_fast == true)
			{
				cur->setPosition(cur_pos);
				Game_Mode->runAction(choise);
				return true;
			}

			cur->runAction(Sequence::create(MoveTo::create(time, cur_pos), DelayTime::create(time), choise, nullptr));
			break;
		}
		case POS_L:
		{
			Vec2 cur_pos = Vec2(POS_HEAD[any_enum::left].x, cur->getPosition().y);

			if (All_fast == true)
			{
				cur->setPosition(cur_pos);
				Game_Mode->runAction(choise);
				return true;
			}

			cur->runAction(Sequence::create(MoveTo::create(time, cur_pos), DelayTime::create(time), choise, nullptr));
			break;
		}
		case POS_RC:
		{
			Vec2 cur_pos = Vec2(POS_HEAD[any_enum::right_centr].x, cur->getPosition().y);

			if (All_fast == true)
			{
				cur->setPosition(cur_pos);
				Game_Mode->runAction(choise);
				return true;
			}

			cur->runAction(Sequence::create(MoveTo::create(time, cur_pos), DelayTime::create(time), choise, nullptr));
			break;
		}
		case POS_LC:
		{
			Vec2 cur_pos = Vec2(POS_HEAD[any_enum::left_centr].x, cur->getPosition().y);

			if (All_fast == true)
			{
				cur->setPosition(cur_pos);
				Game_Mode->runAction(choise);
				return true;
			}

			cur->runAction(Sequence::create(MoveTo::create(time, cur_pos), DelayTime::create(time), choise, nullptr));
			break;
		}
		default:
			cur->runAction(choise);
			return false;
			break;
		}
		return true;
	}
}



namespace Action_ore
{
	const int x_0_R = 872;
	const int y_0 = 43;
	const int x_0_L = 62;

	const int smeh_pos = -235;

	void action(Node *cur, type_action cur_action, bool wait, Page *next)
	{
		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});


		//auto end = CallFunc::create([=]()
		//{
		//	if (cur != nullptr)
		//	{
		//		cur->setPosition(Vec2(0, 0));
		//	}
		//});


		auto unlock_ore_action = CallFunc::create([=]()
		{
			if (cur != nullptr)
			{
				cur->setPosition(Vec2(0, 0));
				cur->runAction(Sequence::create(MoveBy::create(0.5, Vec2(-600, 0)), DelayTime::create(0.5), MoveBy::create(0.5, Vec2(-750, 0)), nullptr));
			}
		});


		switch (cur_action)
		{
		case HIDE_BOX:
			if (wait == true)
			{
				cur->runAction(Sequence::create(MoveTo::create(0.5, OREL == cur ? Vec2(x_0_L, y_0) : Vec2(x_0_R, y_0)),
					CallFunc::create([=]() 
				{ 
					auto button = static_cast<ui::Button*>(cur->getChildByTag(2));
					button->stopAllActions(); 
					unselect_ore(button);
				}),	choise, nullptr));
			}
			else
			{
				cur->runAction(Sequence::create(MoveTo::create(0.5, OREL == cur ? Vec2(x_0_L, y_0) : Vec2(x_0_R, y_0)),
					CallFunc::create([=]() 
				{
					auto button = static_cast<ui::Button*>(cur->getChildByTag(2));
					button->stopAllActions();
					unselect_ore(button);
				}), nullptr));
				Game_Mode->runAction(choise);
			}
			break;
		case SHOW_BOX:
			if (wait == true)
			{
				cur->runAction(Sequence::create(MoveTo::create(0.5, OREL == cur ? Vec2(x_0_L, smeh_pos) : Vec2(x_0_R, smeh_pos)),
					CallFunc::create([=]()
				{
					clear_vis_ore(cur);
				}), choise, nullptr));
			}
			else
			{
				cur->runAction(Sequence::create(MoveTo::create(0.5, OREL == cur ? Vec2(x_0_L, smeh_pos) : Vec2(x_0_R, smeh_pos)),
					CallFunc::create([=]()
				{
					clear_vis_ore(cur);
				}), nullptr));
				Game_Mode->runAction(choise);
			}
			break;
		case UNLOCK_ORE:
			if (wait == true)
			{
				cur->getParent()->runAction(Sequence::create(FadeIn::create(0.5), unlock_ore_action, DelayTime::create(1.5), FadeOut::create(0.5), choise, nullptr));
			}
			else
			{
				cur->getParent()->runAction(Sequence::create(FadeIn::create(0.5), unlock_ore_action, DelayTime::create(1.5), FadeOut::create(0.5), nullptr));
				Game_Mode->runAction(choise);
			}
		default:
			break;
		}
	
	
	}
}


namespace Action_model
{
	bool action(Node *cur, type_action cur_action, bool wait, Page *next)
	{
		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});
		float time = 0.25f;
		auto sprite = cur;
		switch (cur_action)
		{
		case scale_lit:
		{

			float cur_scale = 1.0f;
		
			

			if (All_fast == true)
			{
				sprite->setScale(cur_scale);
				Game_Mode->runAction(choise);
				return true;
			}

			sprite->runAction(Sequence::create(ScaleTo::create(time, cur_scale, cur_scale), DelayTime::create(time), choise, nullptr));
			break;
		}
		case scale_mid:
		{
			float cur_scale = 1.5f;
		//	auto sprite = static_cast<Sprite*>(cur->getChildByName("Sprite"));


			if (All_fast == true)
			{
				sprite->setScale(cur_scale);
				Game_Mode->runAction(choise);
				return true;
			}

			sprite->runAction(Sequence::create(ScaleTo::create(time, cur_scale, cur_scale), DelayTime::create(time), choise, nullptr));
			break;
		}
		case scale_big:
		{
			float cur_scale = 2.0f;
		//	auto sprite = static_cast<Sprite*>(cur->getChildByName("Sprite"));


			if (All_fast == true)
			{
				sprite->setScale(cur_scale);
				Game_Mode->runAction(choise);
				return true;
			}

			sprite->runAction(Sequence::create(ScaleTo::create(time, cur_scale, cur_scale), DelayTime::create(time), choise, nullptr));
			break;
		}
		default:
			break;
		}
	}
}


namespace Action_textbox
{

	void action(Node *cur, type_action cur_action, bool wait, Page *next)
	{
		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});
		switch (cur_action)
		{
		case HIDE_BOX:
			if (wait == true)//был DelayTime::create(0.5f), после действия но как оказалось он не нужне???????
			{
				cur->runAction(Sequence::create(MoveTo::create(0.5, Vec2(0 + TEXTBOX_X, -206 + TEXTBOX_Y)), choise, nullptr));
			}
			else
			{
				cur->runAction(Sequence::create(MoveTo::create(0.5, Vec2(0 + TEXTBOX_X, -206 + TEXTBOX_Y)), nullptr));
				Game_Mode->runAction(choise);
			}
			break;
		case SHOW_BOX:
			if (wait == true)
			{
				cur->runAction(Sequence::create(MoveTo::create(0.5, Vec2(0 + TEXTBOX_X, 206 + TEXTBOX_Y)), choise, nullptr));
			}
			else
			{
				cur->runAction(Sequence::create(MoveTo::create(0.5, Vec2(0 + TEXTBOX_X, 206 + TEXTBOX_Y)), nullptr));
				Game_Mode->runAction(choise);
			}
			break;
		default:
			break;
		}		
	}

}


