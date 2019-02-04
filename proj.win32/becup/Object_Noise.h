#pragma once
#include "Object_Scene.h"

enum type_noise {music, sound};

class Object_Noise : public Object_Scene
{
private:
	type_noise my_type;
public:

	Object_Noise(string, type_noise);// ��������� ������ �����

	virtual swich_node draw() override;// ������������������ ����� �� ����

	~Object_Noise();
};
