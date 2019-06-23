#pragma once
#include "Object_Scene.h"



extern const int cout_anim; //количество позиций спрайт - глаза - рот
extern const int cout_sprite; // максимальное количество используемых спрайтов

extern std::array <Node**, 6> index_sprite;//адреса нод спрайтов
extern map< Node**, any_enum::state_node> check_sprite_for_state; // свободен ли спрайт
extern map<any_enum::name_sprite, Node**> name_for_node; //имя закрепленное за нодой спрайте
extern string dir_home_sprite; // оригинальная дира
void relese_old_state(Node *);
void clear_mapani(Sprite*);
std::string Get_name_from_enum(any_enum::name_sprite my_name);//получает имя в string из enum
std::array<positions, 3> search_pos(std::string name, std::string pos);//ищет в векторе пар нужную позицию нужного спрайтика для каждого элементика 

class Object_Sprite : public Object_Scene
{
protected:
	any_enum::name_sprite my_name; // его имя

	string face_dir; //дирректория лица


	std::array<positions,3> pos; //координаты по  положение спрайта - лица - рот по порядку в кваде нода

	any_enum::posicion_sprite my_pos = any_enum::centr; // позиция фиксированная за персонажем

	bool hide = false;
public:

	Object_Sprite(any_enum::name_sprite, string, int, int);// сгенерить данные спрайта и его координаты

	Object_Sprite(any_enum::name_sprite); // для удадения(скрытия) спрайта по имени

	bool Get_hide() { return this->hide; } // говорит скрыт ли

	any_enum::name_sprite Get_name(){ return this->my_name; }

	void Set_pos(any_enum::posicion_sprite cur_pos) { my_pos = cur_pos; }

	virtual swich_node draw() override;// проиницилизировать спайт на айдишку замены и проиницилизировать ресурс на какой нибудь Sprite

	//~Object_Sprite(); 

};

std::array<positions, 3> search_pos(std::string name, std::string pos);
extern map<any_enum::posicion_sprite, positions> POS_HEAD;