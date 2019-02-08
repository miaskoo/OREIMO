#pragma once
#include "Object_Scene.h"
#include "Object_Sprite.h"
#include"Object_Noise.h"
#include "Object_Box.h"
#include "Object_ORE.h"
#include "Object_Text.h"
#include "Object_Condition.h"
#include "Actions.h"
#include <vector>
#include <array>




struct voice_box
{
	string dir = "";
	int index_animate = NULL;
};

namespace type_struct
{
	enum type_object{ scene, sprite, text, ore, condition, audio, none };
}

enum type_interactions{ swich, action, unknown };

class Page
{
private:
	vector<Object_Scene*> objects;
	map<Object_Scene*, type_struct::type_object> objects_type;
	map<Object_Scene*, type_interactions> objects_intreractions;
	map<Object_Scene*, type_swich> objects_swich;
	map<Object_Scene*, type_action> objects_action;
	int cur_obj = 0; //счетчик объектов
public:
	
	Page();
	~Page();
	
	Page(vector<Object_Scene*>, vector<type_struct::type_object>, vector <type_interactions>, vector<type_swich>, vector<type_action>);

	bool draw(); //проиграет одно действие по допустимому индексу и будет их проигрывыть последовательно!




};
