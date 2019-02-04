#include "Actions.h"
#include "Page.h"
const float time_fade = 0.7f;
const float smeh_position = 50;
extern Node* OREL;
extern Node* ORER;
namespace Action_mixed
{
	void swish(Node *cur_old, Node *cur_new, bool wait, Page *next)// (next - функция циклично запускаюшая действия?)
	{
		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});
		if (cur_old != nullptr)
			cur_old->runAction(FadeOut::create(time_fade));
		if (cur_new != nullptr)
			cur_new->runAction(FadeIn::create(time_fade));

		if (wait == false)
			Game_Mode->runAction(choise);
		else
			Game_Mode->runAction(Sequence::create(DelayTime::create(time_fade), choise, nullptr));

	}


	void action(Node *cur, type_action cur_action, bool wait, Page *next)
	{
		float speed = 0.03;

		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});
		switch (cur_action)
		{
		case SHAKE:
		{
					  if (wait == false)
					  {
						  cur->runAction(Sequence::create(
							  MoveBy::create(speed, Vec2(206, 100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(-206, -100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(-206, -100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(206, 100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(106, 100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(-106, -100)), DelayTime::create(speed),
							  nullptr));
						  Game_Mode->runAction(choise);

					  }
					  else
					  {
						  cur->runAction(Sequence::create(
							  MoveBy::create(speed, Vec2(206, 100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(-206, -100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(-206, -100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(206, 100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(106, 100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(-106, -100)), DelayTime::create(speed), choise,
							  nullptr));
					  }
					  break;
		}
		case PUNCH:
		{
					  if (wait == false)
					  {
						  auto White_screen = Game_Mode->getChildByName("White_screen");
						  White_screen->runAction(Sequence::create(FadeIn::create(0.05f), DelayTime::create(0.05f), FadeOut::create(0.05f), nullptr));
						  cur->runAction(Sequence::create(
							  DelayTime::create(0.2f),
							  MoveBy::create(speed, Vec2(0, 150)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(0, -150)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(0, 100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(0, -100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(0, 50)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(0, -50)), DelayTime::create(speed),
							  nullptr));
						  Game_Mode->runAction(choise);
					  }
					  else
					  {
						  auto White_screen = Game_Mode->getChildByName("White_screen");
						  White_screen->runAction(Sequence::create(FadeIn::create(0.05f), DelayTime::create(0.05f), FadeOut::create(0.05f), nullptr));
						  cur->runAction(Sequence::create(
							  DelayTime::create(0.2f),
							  MoveBy::create(speed, Vec2(0, 150)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(0, -150)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(0, 100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(0, -100)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(0, 50)), DelayTime::create(speed),
							  MoveBy::create(speed, Vec2(0, -50)), DelayTime::create(speed), choise,
							  nullptr));
					  }

					  break;
		}
		default:
			break;
		}
	}
}

namespace Action_scene
{
	void swich(Node *cur_old, Node *cur_new, type_swich cur_swich, bool wait, Page *next)
	{
		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});
		switch (cur_swich)
		{
		case POLOS:
		{



					  auto Polos_screen = Game_Mode->getChildByName("Polos_screen");
					  auto Polos_simple = Polos_screen->getChildByTag(0);
					  auto Polos_reverse = Polos_screen->getChildByTag(1);
					  Polos_screen->setVisible(true);
					  Polos_simple->setVisible(true); 
					  const int size_polos = 8;

					  for (int n = 0; n < size_polos; n++)
					  {
						  Polos_simple->getChildByTag(n)->runAction(ScaleTo::create(1, 1.0, 1.0));
					  }

					  auto swich_scene = CallFunc::create([=]()
					  {
						  cur_old->setOpacity(0);
						  cur_new->setOpacity(255);
						  Polos_reverse->setVisible(true);
						  Polos_simple->setVisible(false);
						  for (int n = 0; n < size_polos; n++)
						  {
							  Polos_simple->getChildByTag(n)->setScaleX(0.01);
							  Polos_reverse->getChildByTag(n)->runAction(ScaleTo::create(1, 0.01, 100));
						  }
					  });

					  auto swich_end = CallFunc::create([=]()
					  {
						  Polos_reverse->setVisible(false);
						  Polos_screen->setVisible(false);
						  for (int n = 0; n < size_polos; n++)
						  {
							  Polos_reverse->getChildByTag(n)->setScaleX(1.0f);
						  }


					  });

					  if (wait == false)
					  {
						  Game_Mode->runAction(Sequence::create(choise, DelayTime::create(1.5), swich_scene, DelayTime::create(1.1), swich_end, nullptr));
					  }
					  else
					  {
						  Game_Mode->runAction(Sequence::create(DelayTime::create(1.5), swich_scene, DelayTime::create(1.1), swich_end, choise, nullptr));
					  }
					  
					  break;
		}
			
		case SIMPLE:
			Action_mixed::swish(cur_old, cur_new, wait, next);
		default:
			break;
		}
		
	}

	void action(Node *cur, type_action cur_action, bool wait, Page *next)
	{
		Action_mixed::action(cur, cur_action, wait, next);
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

		switch (cur_swich)
		{
		case LTR:
		{
					if (hide == false) //пропадает ли спарйт иначе - появляется и нужно сместить по координатам
					{
						cur_new->setPosition(cur_new->getPosition() - Vec2(smeh_position, 0));
						if (wait == false)
						{
							cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(smeh_position, 0)), FadeIn::create(0.7f)), DelayTime::create(0.7f), nullptr));
							Game_Mode->runAction(choise);
						}
						else
						{
							cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(smeh_position, 0)), FadeIn::create(0.7f)), DelayTime::create(0.7f), choise, nullptr));
						}
						if (cur_old != nullptr)
							cur_old->runAction(FadeOut::create(0.7f));
					}
					else
					{
						if (wait == false)
						{
							cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(smeh_position, 0)), FadeOut::create(0.7f)), DelayTime::create(0.7f), nullptr));
							Game_Mode->runAction(choise);
						}
						else
						{
							cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(smeh_position, 0)), FadeOut::create(0.7f)), DelayTime::create(0.7f), choise, nullptr));
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
							cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(-smeh_position, 0)), FadeIn::create(0.7f)), DelayTime::create(0.7f), nullptr));
							Game_Mode->runAction(choise);
						}
						else
						{
							cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(-smeh_position, 0)), FadeIn::create(0.7f)), DelayTime::create(0.7f), choise, nullptr));
						}
						
						if (cur_old != nullptr)
							cur_old->runAction(FadeOut::create(0.7f));
					}
					else
					{
						if (wait == false)
						{
							cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(-smeh_position, 0)), FadeOut::create(0.7f)), DelayTime::create(0.7f), nullptr));
							Game_Mode->runAction(choise);
						}
						else
						{
							cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(-smeh_position, 0)), FadeOut::create(0.7f)), DelayTime::create(0.7f), choise, nullptr));
						}
						
					}
					break;
		}
		case SIMPLE:
		{
					   Action_mixed::swish(cur_old, cur_new, wait, next);
					   break;
		}
		default:
			return false;
		}
		return true;
	}

	bool action(Node *cur, type_action cur_action, bool hide, bool wait, Page *next)
	{
		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});
		float time = 0.25;
		switch (cur_action)
		{
		case MINIJUMP:
		{
						 cur->runAction(Sequence::create(MoveBy::create(0.15f, Vec2(0, 20)), DelayTime::create(0.15f), MoveBy::create(0.15f, Vec2(0, -20)), DelayTime::create(0.15f), choise, nullptr));
						 break;
		}
		case JUMP:
		{
					 cur->runAction(Sequence::create(MoveBy::create(0.07f, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f),
						 MoveBy::create(0.07f, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f), choise , nullptr));
					 break;
		}
		case scale_lit:
		{
						 
						 cur->runAction(Sequence::create(ScaleTo::create(time, 1.7f, 1.7f), DelayTime::create(time), choise, nullptr));
						 break;
		}
		case scale_big:
		{
						 cur->runAction(Sequence::create(ScaleTo::create(time, 2.1f, 2.1f), DelayTime::create(time), choise, nullptr));
						 break;
		}
		case scale_mid:
		{
						  cur->runAction(Sequence::create(ScaleTo::create(time, 1.9f, 1.9f), DelayTime::create(time), choise, nullptr));
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
	void action(Node *cur, type_action cur_action, bool wait, Page *next)
	{
		auto choise = CallFunc::create([=]()
		{
			if (next != nullptr)
				next->draw();
		});


		auto end = CallFunc::create([=]()
		{
			if (cur != nullptr)
			{
				cur->setPosition(Vec2(0, 0));
			}
		});


		auto unlock_ore_action = CallFunc::create([=]()
		{
			if (cur != nullptr)
			{
				cur->runAction(Sequence::create(MoveBy::create(0.5, Vec2(-600, 0)), DelayTime::create(0.5), MoveBy::create(0.5, Vec2(-750, 0)), nullptr));
			}
		});

		switch (cur_action)
		{
		case HIDE_BOX:
			if (wait == true)
				cur->runAction(Sequence::create(MoveTo::create(0.5, OREL == cur ? Vec2(60, 0) : Vec2(924,0)), choise, nullptr));
			else
				cur->runAction(Sequence::create(choise, MoveTo::create(0.5, OREL == cur ? Vec2(60, 0) : Vec2(924, 0)), nullptr));
			break;
		case SHOW_BOX:
			if (wait == true)
				cur->runAction(Sequence::create(MoveTo::create(0.5, OREL == cur ? Vec2(60, -235) : Vec2(924, -235)), choise, nullptr));
			else
				cur->runAction(Sequence::create(choise, MoveTo::create(0.5, OREL == cur ? Vec2(60, -235) : Vec2(924, -235)), nullptr));
			break;
		case UNLOCK_ORE:
			if (wait == true)
				cur->getParent()->runAction(Sequence::create(FadeIn::create(0.5), unlock_ore_action, DelayTime::create(1.5), FadeOut::create(0.5), end, choise, nullptr));
			else
				cur->getParent()->runAction(Sequence::create(choise, FadeIn::create(0.5), unlock_ore_action, DelayTime::create(1.5), FadeOut::create(0.5), end, nullptr));
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
				cur->runAction(Sequence::create(MoveBy::create(0.5, Vec2(0, -206)), choise, nullptr));
			else
				cur->runAction(Sequence::create(choise, MoveBy::create(0.5, Vec2(0,-206)), nullptr));
			break;
		case SHOW_BOX:
			if (wait == true)
				cur->runAction(Sequence::create(MoveBy::create(0.5, Vec2(0, 206)), choise, nullptr));
			else
				cur->runAction(Sequence::create(choise, MoveBy::create(0.5, Vec2(0, 206)), nullptr));
			break;
		default:
			break;
		}


		


		
	}



}


