#pragma once
#ifndef PAGE_H
#define PAGE_H
#include "Object_Scene.h"
#include "Object_Sprtite.h"
#include"Object_Noise.h"
#include "Object_Box.h"
#include "Actions.h"
#include <vector>
#include <array>

struct voice_box
{
	string dir;
	int index_animate;
};

struct text_box
{
	string text;
	voice_box cur_voice;
};



enum type_object{ scene, sprite, texbox, mixed, none };
enum type_interactions{ swich, action };

class Page
{
private:
	vector<shared_ptr<Object_Scene>> objects;
	map<shared_ptr<Object_Scene>*, type_object> objects_type;
	map<shared_ptr<Object_Scene>*, type_interactions> objects_intreractions;
	map<shared_ptr<Object_Scene>*, type_swich> objects_swich;
	map<shared_ptr<Object_Scene>*, type_action> objects_action;
	text_box *page_text;
	int cur_obj = 0; //счетчик действий
public:
	
	//Page(text_box*);

	//Page(vector<Object_Scene*>, vector<type_object>, text_box*);

	Page(vector<Object_Scene*>, vector<type_object>, vector <type_interactions>, vector<type_swich>, text_box*);

	Page(vector<Object_Scene*>, vector<type_object>, vector <type_interactions>, vector<type_swich>, vector<type_action>, text_box*);

	bool update();//проверит принадлежность объектов отцу, и экшоны к ним.

	bool draw(); //проиграет одно действие по допустимому индексу

};

#endif