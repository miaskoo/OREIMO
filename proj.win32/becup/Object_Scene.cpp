#include "Object_Scene.h"

extern Node *Game_mode;
Node *Scene1;
Node *Scene2;
Node *Sprite1;
Node *Sprite2;
Node *Sprite3;
Node *Sprite4;
Node *Sprite5;
Node *Sprite6;

map< Node**, state_node> check_scene_for_state{ { &Scene1, FREE }, { &Scene2, FREE } };
map< Node**, bool> unlock_parent{ { &Scene1, false }, { &Scene2, false }, { &Sprite1, false }, { &Sprite2, false }, { &Sprite3, false }, { &Sprite4, false }, { &Sprite5, false }, { &Sprite6, false } };
array<Node**, 8> all_nodes = { &Scene1, &Scene2, &Sprite1, &Sprite2, &Sprite3, &Sprite4, &Sprite5, &Sprite6 };


Node *Custom_Node = nullptr;
Node *Custom_Node_old = nullptr;
const int Custom_Tag = 34584;
const int Custom_Tag_old = 34585;




Object_Scene::Object_Scene(string type_sprite)
{
	dir_obj = BG_DIR[type_sprite];
}

Object_Scene::Object_Scene(int type_sprite)
{
	dir_obj = CG_DIR[type_sprite];
}

swich_node Object_Scene::draw()
{
	if (check_scene_for_state[&Scene1] == FREE)
	{
		this->my_node = Scene1;
		static_cast<Sprite*>(this->my_node->getChildByName("Sprite"))->setTexture(dir_obj);
		swich_node for_return{ Scene2, Scene1 };
		check_scene_for_state[&Scene1] = BUSY;
		check_scene_for_state[&Scene2] = FREE;
		return for_return;

	}
	else if (check_scene_for_state[&Scene2] == FREE)
	{
		this->my_node = Scene2;
		static_cast<Sprite*>(this->my_node->getChildByName("Sprite"))->setTexture(dir_obj);
		swich_node for_return{ Scene1, Scene2 };
		check_scene_for_state[&Scene1] = FREE;
		check_scene_for_state[&Scene2] = BUSY;
		return for_return;

	}
	return swich_node{ NULL, NULL };
}