#pragma once
#ifndef OBJECT_ORE_H
#define OBJECT_ORE_H
#include "Object_Scene.h"

class Object_ORE : public Object_Scene
{
private:
	int cur_ore = 99;
public:
	Object_ORE(int, any_enum::posicion_sprite);
	int Object_ORE::Get_Ore_num();
	virtual swich_node draw() override;// проиницилизировать ноду с объектами с одновременным выводом 
};
#endif