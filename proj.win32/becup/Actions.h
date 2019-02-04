#pragma once
#include "cocos2d.h"

using namespace cocos2d;



extern Node *Game_Mode;
extern Node *Text_Box;
enum type_swich{ LTR, RTL, SIMPLE };
enum type_action{ MINIJUMP, JUMP, DECREASE, INCREASE, MINI_INCREASE, MINI_DECREASE };


namespace Action_mixed
{
	void swish(void *next, Node *cur_old, Node *cur_new);
}

namespace Action_scene
{
	void swich(void *next, Node *cur_old, Node *cur_new);
}

namespace Action_sprite
{
	bool swich(void* next, Node *cur_old, Node *cur_new, type_swich cur_swich, bool hide);

	bool action(void* next, Node *cur, type_action cur_action, bool hide);
}
namespace Action_textbox
{
	void hide(void *next);

	void show(void *next);

}


