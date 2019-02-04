#pragma once
#include "Object_Scene.h"



extern const int cout_anim; //количество позиций спрайт - глаза - рот
extern const int cout_sprite; // максимальное количество используемых спрайтов

extern map <int, Node** > index_sprite;
extern map< Node**, any_enum::state_node> check_sprite_for_state; // свободен ли спрайт
extern map<any_enum::name_sprite, Node**> name_for_node; //имя закрепленное за нодой спрайте

extern map<string, std::array<positions, 3>> POS_KI;
extern map<string, std::array<positions, 3>> POS_AY;
extern map<string, std::array<positions, 3>> POS_DA;

class Object_Sprtite : public Object_Scene
{
private:
	any_enum::name_sprite my_name; // его имя
	
	string face_dir; //дирректория лица
	string home_dir = ".\\Resources\\Sprites";
	std::array<positions,3> pos; //координаты по  положение спрайта - лица - рот по порядку в кваде нода

	any_enum::posicion_sprite my_pos = any_enum::centr; // позиция фиксированная за персонажем
	bool hide = false;
public:

	Object_Sprtite(any_enum::name_sprite, string, int, int);// сгенерить данные спрайта и его координаты

	Object_Sprtite(any_enum::name_sprite); // для удадения спрайта по имени

	bool Get_hide() { return this->hide; }

	any_enum::name_sprite Get_name(){ return this->my_name; }

	void Set_pos(any_enum::posicion_sprite cur_pos) { my_pos = cur_pos; }

	virtual swich_node draw() override;// проиницилизировать спайт на айдишку замены и проиницилизировать ресурс на какой нибудь Sprite

	~Object_Sprtite();
};



extern map<string, std::array<positions, 3>> POS_AY;
extern map<string, std::array<positions, 3>> POS_DA;
extern map<string, std::array<positions, 3>> POS_KI;
extern map<string, std::array<positions, 3>> POS_AK;
extern map<string, std::array<positions, 3>> POS_KA;
extern map<string, std::array<positions, 3>> POS_KU;
extern map<string, std::array<positions, 3>> POS_MA;
extern map<string, std::array<positions, 3>> POS_RO;
extern map<string, std::array<positions, 3>> POS_SA;
extern map<string, std::array<positions, 3>> POS_SE;
extern map<string, std::array<positions, 3>> POS_YO;

