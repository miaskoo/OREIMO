#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Page;

extern Node *Game_Mode;
extern Node *Text_Box;
enum type_swich{ LTR, RTL, SIMPLE, POLOS };
enum type_action{ MINIJUMP, JUMP, SHAKE, PUNCH, Zzzzz, scale_lit, scale_mid, scale_big, SHOW_BOX, HIDE_BOX, UNLOCK_ORE, BLACK_IN, BLACK_OUT };


namespace Action_mixed
{
	void swish(Node*, Node*, bool, Page* = nullptr);

	void action(Node *, type_action, bool, Page * = nullptr);

}

namespace Action_scene
{
	void swich(Node *, Node *, type_swich, bool, Page * = nullptr);

	void action(Node *cur, type_action, bool, Page * = nullptr);
}

namespace Action_sprite
{
	bool swich(Node *, Node *, type_swich, bool, bool, Page * = nullptr);

	bool action(Node *, type_action, bool, bool, Page * = nullptr);
}


namespace Action_ore
{
	void action(Node *, type_action, bool, Page * = nullptr);
}

namespace Action_textbox
{
	void action(Node *, type_action, bool, Page * = nullptr);

}


