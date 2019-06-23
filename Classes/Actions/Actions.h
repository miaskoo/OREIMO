#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Page;

extern Node *Game_Mode;
extern Node *Text_Box;
enum type_swich{ LTR, RTL, SIMPLE, NULL_TIME, DTT };
enum type_action{ UNKNOWN_ACTION, MINIJUMP, JUMP, SHAKE, PUNCH,  scale_lit, scale_mid, scale_big, LIVE2D_MOTION, POS_C, POS_L, POS_LC, POS_R, POS_RC, SHOW_BOX, HIDE_BOX, UNLOCK_ORE, 
	BLACK_IN, BLACK_OUT, POLOS_IN, POLOS_OUT, SLASH_WS_IN, SLASH_WS_OUT, SLASH_AD_IN, SLASH_AD_OUT,
	MBLACK_IN, MBLACK_OUT, MPOLOS_IN, MPOLOS_OUT, MSLASH_WS_IN, MSLASH_WS_OUT, MSLASH_AD_IN, MSLASH_AD_OUT
};


namespace Action_mixed
{
	bool swish(Node*, Node*, bool, Page* = nullptr, bool = false);

}

namespace Action_scene
{
	bool swich(Node *, Node *, type_swich, bool, Page * = nullptr);

	bool action(Node *cur, type_action, bool, Page * = nullptr);
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



namespace Action_model
{
	bool action(Node *, type_action, bool, Page * = nullptr);
}

namespace Action_textbox
{
	void action(Node *, type_action, bool, Page * = nullptr);

}

