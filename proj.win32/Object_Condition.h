#pragma once
#ifndef OBJECT_CON_H
#define OBJECT_CON_H
#include "Object_Scene.h"

class Object_Condition : public Object_Scene
{
private:
	//�������� �� �������� ��� ������� ������� ������ � �� ����������
	any_enum::open_resurce ore_data[64];

	//�������� �� ����
	int POINT = 0;
	any_enum::name_sprite CHAPTER = any_enum::NONE;

	//�������� �� ������ � ���������� ������� ������������ ���
	any_enum::use_ore CUR_USE = any_enum::nonuse; 

public:
	Object_Condition(any_enum::open_resurce *ore_data, any_enum::name_sprite = any_enum::NONE, int = 0, any_enum::use_ore = any_enum::nonuse);

	virtual swich_node draw() override;
};
#endif