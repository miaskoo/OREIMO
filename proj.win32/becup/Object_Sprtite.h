#pragma once
#include "Object_Scene.h"

enum posicion_sprite{ left, left_centr, centr, right_centr , right };
enum name_sprite { KI, AY, DA };

struct positions
{
	int x;
	int y;
};



extern const int cout_anim; //количество позиций спрайт - глаза - рот
extern const int cout_sprite; // максимальное количество используемых спрайтов

extern map <int, Node** > index_sprite;
extern map< Node**, state_node> check_sprite_for_state; // свободен ли спрайт
extern map<name_sprite, Node**> name_for_node; //имя закрепленное за нодой спрайте

extern map<string, std::array<positions, 3>> POS_KI;
extern map<string, std::array<positions, 3>> POS_AY;
extern map<string, std::array<positions, 3>> POS_DA;

class Object_Sprtite : public Object_Scene
{
private:
	name_sprite my_name; // его имя

	string face_dir; //дирректория лица
	
	std::array<positions,3> pos; //координаты по  положение спрайта - лица - рот по порядку в кваде нода

	posicion_sprite my_pos = centr; // позиция фиксированная за персонажем

public:

	Object_Sprtite(name_sprite, string, int, int);// сгенерить данные спрайта и его координаты

	void Set_pos(posicion_sprite cur_pos) { my_pos = cur_pos; }

	virtual swich_node draw() override;// проиницилизировать спайт на айдишку замены и проиницилизировать ресурс на какой нибудь Sprite

	~Object_Sprtite();
};

