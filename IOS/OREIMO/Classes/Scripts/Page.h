#pragma once

#include "Classes\Objects\Object_Scene.h"
#include "Classes\Objects\Object_Sprite.h"
#include"Classes\Objects\Object_Noise.h"
#include "Classes\Objects\Object_Box.h"
#include "Classes\Objects\Object_ORE.h"
#include "Classes\Objects\Object_Text.h"
#include "Classes\Objects\Object_Condition.h"
#include "Classes\Objects\Object_Teleport.h"
#include "Classes\Objects\Object_LIVE2D.h"
#include "Classes\Actions\Actions.h"
#include <vector>
#include <array>




struct voice_box
{
	string dir = "";
	int index_animate = NULL;
};

namespace type_struct
{
	enum type_object{ scene, sprite, text, ore, condition, audio, teleport, live2d, world, none };
}

enum type_interactions{ swich, action, unknown };

class Page
{
private:
	any_enum::global_filtr state = any_enum::morning;
	vector<Object_Scene*> objects;
	map<Object_Scene*, type_struct::type_object> objects_type;
	map<Object_Scene*, type_interactions> objects_intreractions;
	map<Object_Scene*, type_swich> objects_swich;
	map<Object_Scene*, type_action> objects_action;
	int cur_obj = 0; //������� ��������
//	bool fast = false;
	
public:
	

	~Page();
	
	Page(vector<Object_Scene*>, vector<type_struct::type_object>, vector <type_interactions>, vector<type_swich>, vector<type_action>);

	bool draw(); //��������� ���� �������� �� ����������� ������� � ����� �� ����������� ���������������!
	
	bool isFinish();//�������� �� ��������� ���������
	void FastFinish();

};
