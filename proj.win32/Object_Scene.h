#pragma once
#include <vector>
#include <string>
#include <array>
#include "cocos2d.h"
#include "Resourse.h"
using namespace std;
using namespace cocos2d;

namespace any_enum
{
	enum scale_sprite{ little, standart, big };
	enum open_resurce{ lock, unlock, old };
	enum use_ore{ ORER, OREL, nonuse };
	enum state_node { FREE, BUSY };
	enum posicion_sprite{ left, left_centr, centr, right_centr, right, custom };
	enum name_sprite { KI, AY, DA, AK, KA, KU, MA, RO, SA, SE, YO, NONE };
}

struct swich_node
{
	Node* old_ptr;
	Node* new_ptr;
};

struct positions
{
	int x;
	int y;
};


extern Node *Scene1;
extern Node *Scene2;
extern Node *Sprite1;
extern Node *Sprite2;
extern Node *Sprite3;
extern Node *Sprite4;
extern Node *Sprite5;
extern Node *Sprite6;

extern map< Node**, any_enum::state_node> check_scene_for_state;
extern map< Node**, bool> unlock_parent;
extern  array<Node**, 8> all_nodes;


extern Node *Custom_Node;
extern Node *Custom_Node_old;
extern const int Custom_Tag;
extern const int Custom_Tag_old;

class Object_Scene
{
protected:
	Node *my_node = nullptr;//дирректория закрепленной ноды
	string dir_obj = "empty"; // дирректория объекта основы
public:
	Object_Scene(){}; // по умолчанию
	Object_Scene(string, int);// обычный конструтор для файлом сцен
	bool wait = false;
	virtual swich_node draw();
	Node *Get_Node(){ return this->my_node; }
	void Set_wait(bool x){ this->wait = std::move(x); }
	bool Get_wait(){ return this->wait; };

};

