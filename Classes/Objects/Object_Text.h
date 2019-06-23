#pragma once
#ifndef OBJECT_TEXT_H
#define OBJECT_TEXT_H
#include "Object_Scene.h"


class Object_Text : public Object_Scene
{
private:
	string my_text;
	string my_name;
public:
	Object_Text(string text = "", string name = "");

	virtual swich_node draw() override;// проиницилизировать ноду с объектами с одновременным выводом 
};
#endif