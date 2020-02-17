#pragma once
#include "Object_Scene.h"

enum type_noise {music, sound};

class Object_Noise : public Object_Scene
{
private:
	type_noise my_type;
public:

	Object_Noise(type_noise, string);// сгенерить данные музла

	virtual swich_node draw() override;// проиницилизировать музло на ноду

};
