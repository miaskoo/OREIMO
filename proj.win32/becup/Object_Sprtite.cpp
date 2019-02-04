#include "Object_Sprtite.h"


static const int cout_anim = 3; //количество позиций спрайт - глаза - рот
static const int cout_sprite = 6; // максимальное количество используемых спрайтов


map <int, Node** > index_sprite{ { 1, &Sprite1 }, { 2, &Sprite2 }, { 3, &Sprite3 }, { 4, &Sprite4 }, { 5, &Sprite5 }, { 6, &Sprite6 } };
map< Node**, state_node> check_sprite_for_state{ { &Sprite1, FREE }, { &Sprite2, FREE }, { &Sprite3, FREE }, { &Sprite4, FREE }, { &Sprite5, FREE }, { &Sprite6, FREE }, }; // свободен ли спрайт
map<name_sprite, Node**> name_for_node{ { KI, NULL }, { AY, NULL }, { DA, NULL } }; //имя закрепленное за нодой спрайте



static map<string, std::array<positions, 3>> POS_KI{
	{ "C", { { { 0, 0 }, { 204, 373 }, { 235, 358 } } } },
	{ "L", { { { 0, 0 }, { 214, 367 }, { 247, 358 } } } },
	{ "R", { { { 0, 0 }, { 213, 359 }, { 237, 356 } } } },
};

map<string, std::array<positions, 3>> POS_AY{
	{ "C", { { { 0, 0 }, { 69, 378 }, { 107, 361 } } } },
	{ "L", { { { 0, 0 }, { 44, 374 }, { 87, 363 } } } },
	{ "R", { { { 0, 0 }, { 73, 372 }, { 108, 366 } } } },
};

map<string, std::array<positions, 3>> POS_DA{
	{ "C", { { { 0, 0 }, { 108, 406 }, { 129, 348 } } } }
};


Object_Sprtite::Object_Sprtite(name_sprite chapter_name, string type_sprite, int num_sprite, int num_face) : Object_Scene()// сгенерить данные спрайта и его координаты
{
	this->my_name = chapter_name;
	switch (this->my_name)
	{
	case AY:
	{
			   dir_obj = SPRITE_DIR["AY"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
			   face_dir = SPRITE_DIR["AY"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
			   this->pos = POS_AY["" + type_sprite[0]];
			   break;
	}
	case DA:
	{
			   dir_obj = SPRITE_DIR["DA"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
			   face_dir = SPRITE_DIR["DA"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
			   this->pos = POS_DA["" + type_sprite[0]];
			   break;
	}
	case KI:
	{
			   dir_obj = SPRITE_DIR["KI"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
			   face_dir = SPRITE_DIR["KI"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
			   this->pos = POS_KI["" + type_sprite[0]];
			   break;
	}
	default:
		break;
	}
}

swich_node Object_Sprtite::draw()
{
	for (int n = 0; n < cout_sprite; n++)
	{
		if (check_sprite_for_state[index_sprite[n]] == FREE)
		{
			this->my_node = *index_sprite[n];
			static_cast<Sprite*>(this->my_node->getChildByName("Sprite"))->setTexture(dir_obj);
			auto for_return = swich_node{ *name_for_node[this->my_name], this->my_node }; // старый нод по имени - а новый по закрепленному...
			check_sprite_for_state[&this->my_node] = BUSY; // ставим наш рабочим
			check_sprite_for_state[name_for_node[this->my_name]] = FREE; //а тот теперь свободен
			*name_for_node[this->my_name] = this->my_node; // заменяем ноду на свою в именах
			return for_return;
		}
	}
	return swich_node{ NULL, NULL };
}