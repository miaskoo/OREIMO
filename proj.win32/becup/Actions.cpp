#include "Actions.h"

const int time_fade = 0.7f;
const int smeh_position = 50;

namespace Action_mixed
{
	void swish(void *next, Node *cur_old, Node *cur_new)// (next - функция циклично запускаюшая действия?)
	{

		cur_old->runAction(FadeOut::create(time_fade));
		cur_new->runAction(FadeIn::create(time_fade));
		Game_Mode->runAction(Sequence::create(DelayTime::create(time_fade), next, nullptr));

	}
}

namespace Action_scene
{
	void swich(void *next, Node *cur_old, Node *cur_new)
	{
		Action_mixed::swish(next, cur_old, cur_new);
	}
}

namespace Action_sprite
{
	bool swich(void* next, Node *cur_old, Node *cur_new, type_swich cur_swich, bool hide)
	{
		switch (cur_swich)
		{
		case LTR:
		{
					if (hide == false) //пропадает ли спарйт иначе - появляется и нужно сместить по координатам
					{
						cur_new->setPosition(cur_new->getPosition() - Vec2(smeh_position, 0));
						cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(smeh_position, 0)), FadeIn::create(0.7f)), DelayTime::create(0.7f), next, nullptr));
						cur_old->runAction(FadeOut::create(0.7f));
					}
					else
					{
						cur_new->runAction(FadeIn::create(0.7f));
						cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(smeh_position, 0)), FadeOut::create(0.7f)), DelayTime::create(0.7f), next, nullptr));
					}
					break;
		}
		case RTL:
		{
					if (hide == false)
					{
						cur_new->setPosition(cur_new->getPosition() + Vec2(smeh_position, 0));
						cur_new->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(-smeh_position, 0)), FadeIn::create(0.7f)), DelayTime::create(0.7f), next, nullptr));
						cur_old->runAction(FadeOut::create(0.7f));
					}
					else
					{
						cur_new->runAction(FadeIn::create(0.7f));
						cur_old->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(smeh_position, 0)), FadeOut::create(0.7f)), DelayTime::create(0.7f), next, nullptr));
					}
					break;
		}
		case SIMPLE:
		{
					   Action_mixed::swish(next, cur_old, cur_new);
		}
		default:
			return false;
		}
		return true;
	}

	bool action(void* next, Node *cur, type_action cur_action, bool hide)
	{
		switch (cur_action)
		{
		case MINIJUMP:
		{
						 cur->runAction(Sequence::create(MoveBy::create(0.15f, Vec2(0, 20)), DelayTime::create(0.15f), MoveBy::create(0.15f, Vec2(0, -20)), DelayTime::create(0.15f), next, nullptr));
						 break;
		}
		case JUMP:
		{
					 cur->runAction(Sequence::create(MoveBy::create(0.07f, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f),
						 MoveBy::create(0.07f, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f), next, nullptr));
					 break;
		}
		case DECREASE:
		{
						 float time = 0.25;
						 auto temp_pos = cur->getPosition();
						 cur->setAnchorPoint(Vec2(0.5f, 0.5f));
						 cur->setPosition(temp_pos + (Vec2(256, 256)*1.7f));

						 auto preendaction = CallFunc::create([=]()
						 {
							 auto temppos = (cur->getPosition() - (Vec2(256, 256)*1.7f));
							 cur->setAnchorPoint(Vec2(0.0f, 0.0f));
							 cur->setPosition(temppos);
						 });

						 cur->runAction(Sequence::create(ScaleTo::create(time, 1.7f, 1.7f), DelayTime::create(time), preendaction, next, nullptr));
		}
		case INCREASE:
		{
						 float time = 0.25;
						 auto temp_pos = cur->getPosition();
						 cur->setAnchorPoint(Vec2(0.5f, 0.5f));
						 cur->setPosition(temp_pos + (Vec2(256, 256)*1.7f));


						 auto preendaction = CallFunc::create([=]()
						 {
							 auto temppos = (cur->getPosition() - (Vec2(256, 256)*2.1f));
							 cur->setAnchorPoint(Vec2(0.0f, 0.0f));
							 cur->setPosition(temppos);
						 });

						 cur->runAction(Sequence::create(ScaleTo::create(time, 2.1f, 2.1f), DelayTime::create(time), preendaction, next, nullptr));
		}
		case MINI_INCREASE:
		{
							  float time = 0.25;
							  auto temp_pos = cur->getPosition();
							  cur->setAnchorPoint(Vec2(0.5f, 0.5f));
							  cur->setPosition(temp_pos + (Vec2(256, 256)*1.7f));


							  auto preendaction = CallFunc::create([=]()
							  {
								  auto temppos = (cur->getPosition() - (Vec2(256, 256)*1.9f));
								  cur->setAnchorPoint(Vec2(0.0f, 0.0f));
								  cur->setPosition(temppos);
							  });

							  cur->runAction(Sequence::create(ScaleTo::create(time, 1.9f, 1.9f), DelayTime::create(time), preendaction, next, nullptr));

		}
		default:
			return false;
		}
		return true;
	}
}
namespace Action_textbox
{
	void hide(void *next)
	{
		Text_Box->runAction(Sequence::create(MoveBy::create(0.5, Vec2(0, -206)), DelayTime::create(0.5f), next, nullptr));
	}

	void show(void *next)
	{
		Text_Box->runAction(Sequence::create(MoveBy::create(0.5, Vec2(0, 206)), DelayTime::create(0.5f), next, nullptr));
	}

}


