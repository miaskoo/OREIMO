#include "Object_Scene.h"

extern Node *Game_mode;
extern Node *Scene1;
extern Node *Scene2;
extern Node *Sprite1;
extern Node *Sprite2;
extern Node *Sprite3;
extern Node *Sprite4;
extern Node *Sprite5;
extern Node *Sprite6;

map< Node**, any_enum::state_node> check_scene_for_state{ { &Scene1, any_enum::FREE }, { &Scene2, any_enum::FREE } };
//map< Node**, bool> unlock_parent{ { &Scene1, false }, { &Scene2, false }, { &Sprite1, false }, { &Sprite2, false }, { &Sprite3, false }, { &Sprite4, false }, { &Sprite5, false }, { &Sprite6, false } };
array<Node**, 8> all_nodes = { &Scene1, &Scene2, &Sprite1, &Sprite2, &Sprite3, &Sprite4, &Sprite5, &Sprite6 };


Node *Custom_Node = nullptr;
Node *Custom_Node_old = nullptr;
const int Custom_Tag = 34584;
const int Custom_Tag_old = 34585;



//
//Object_Scene::Object_Scene(string type_sprite)
//{
//	if (type_sprite.length() == 5 || type_sprite == "BGBLACK" || type_sprite == "BGHIDE")
//	{
//		dir_obj = BG_DIR[type_sprite];
//	}
//}

Object_Scene::Object_Scene(string type, int num)
{ 
	if (type == "CG")
	{
		if (num >= -1 && num < 168)
		{
			dir_obj = CG_DIR[num];
		}
	}
	else if (type == "BG")
	{
		if (num >= -1 && num < 83)
		{
			dir_obj = BG_DIR[num];
		}
	}
	
}

swich_node Object_Scene::draw()
{
	if (dir_obj != "empty")
	{
		if (check_scene_for_state[&Scene1] == any_enum::FREE)
		{
			this->my_node = Scene1;
			static_cast<Sprite*>(this->my_node->getChildByName("Sprite"))->setTexture(dir_obj);
			swich_node for_return{ Scene2, Scene1 };
			check_scene_for_state[&Scene1] = any_enum::BUSY;
			check_scene_for_state[&Scene2] = any_enum::FREE;
			return for_return;

		}
		else if (check_scene_for_state[&Scene2] == any_enum::FREE)
		{
			this->my_node = Scene2;
			static_cast<Sprite*>(this->my_node->getChildByName("Sprite"))->setTexture(dir_obj);
			swich_node for_return{ Scene1, Scene2 };
			check_scene_for_state[&Scene1] = any_enum::FREE;
			check_scene_for_state[&Scene2] = any_enum::BUSY;
			return for_return;

		}
	}
	else
	{
		this->my_node = check_scene_for_state[&Scene1] == any_enum::FREE ? Scene2 : Scene1;
	}
	return swich_node{ NULL, NULL };
}