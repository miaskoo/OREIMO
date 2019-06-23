#pragma once
#include "Object_Sprite.h"

namespace LIVE2D_CREATE
{


	extern void scep_live2d(Node* parent);

	bool check_model_settings(int model, int tex);

	bool check_live_model();

	void init_model(int model, int tex);

	void init_expression(vector<string> expressions);
	void relese_model();

}
void Get_model_from_name(any_enum::name_sprite my_name, int &index_model, int &index_tex);//позволяет получить номер модели по имени и проверить существование текстурки у этой модельки 
vector<string> Get_ex_vector_from_string(std::string _expressions);//конвертирует строчку агрументов надстроек для модельки в вектор иницилизации


class Object_LIVE2D : public Object_Scene
{

public:

	any_enum::name_sprite name = any_enum::NONE;//имя - какая модель
	int model = -1;
	int tex = -1;//номер текстуры
	std::string args = "";//агрументы для подстройки модельки - это либо название motions либо названия exoression

	bool hide = false;
	bool anim = false;//для анимаций
	any_enum::posicion_sprite my_pos = any_enum::centr; // позиция фиксированная за персонажем

	Object_LIVE2D(any_enum::name_sprite, int, std::string = "");// сгенерить данные спрайта и его координаты

	Object_LIVE2D(any_enum::name_sprite); // для удадения спрайта по имени

	Object_LIVE2D(any_enum::name_sprite, std::string motion_name);

	bool Get_hide() { return this->hide; }

	any_enum::name_sprite Get_name() { return this->name; }

	void Set_pos(any_enum::posicion_sprite cur_pos) { my_pos = cur_pos; }

	std::string Get_motion_name()
	{
		return this->args;
	}

	virtual swich_node draw() override;
	// иницилизирует модель
	//уничтожает модель
	
							

};

