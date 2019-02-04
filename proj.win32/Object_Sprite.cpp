#include "Object_Sprite.h"


static const int cout_anim = 3; //количество позиций спрайт - глаза - рот
static const int cout_sprite = 6; // максимальное количество используемых спрайтов


map <int, Node** > index_sprite{ 
	{ 0, &Sprite1 }, { 1, &Sprite2 }, { 2, &Sprite3 },
	{ 3, &Sprite4 }, { 4, &Sprite5 }, { 5, &Sprite6 } 
};

map< Node**, any_enum::state_node> check_sprite_for_state{ // свободен ли спрайт
	{ index_sprite[0], any_enum::FREE }, { index_sprite[1], any_enum::FREE }, { index_sprite[2], any_enum::FREE },
	{ index_sprite[3], any_enum::FREE }, { index_sprite[4], any_enum::FREE }, { index_sprite[5], any_enum::FREE } 
}; 

map<any_enum::name_sprite, Node**> name_for_node{  //имя закрепленное за нодой спрайте ****************** потом когда будешь делать проверки на тип текстуры  - можно будет проверять по местомоложение текстуры если одинаково - свич мгновенный, если нет, ну значит нет
	{ any_enum::KI, nullptr }, { any_enum::AY, nullptr }, { any_enum::DA, nullptr },
	{ any_enum::AK, nullptr }, { any_enum::KA, nullptr }, { any_enum::KU, nullptr },
	{ any_enum::MA, nullptr }, { any_enum::RO, nullptr }, { any_enum::SA, nullptr },
	{ any_enum::SE, nullptr }, { any_enum::YO, nullptr } };


static map<any_enum::name_sprite, int> POS_HEIGHT{
	{ any_enum::AY, 166 },
	{ any_enum::DA, 175 },
	{ any_enum::KI, 165 },
	{ any_enum::AK, 177 },
	{ any_enum::KA, 148 },
	{ any_enum::KU, 160 },
	{ any_enum::MA, 160 },
	{ any_enum::RO, 163 },
	{ any_enum::SA, 180 },
	{ any_enum::SE, 163 },
	{ any_enum::YO, 160 }
};

map<string, std::array<positions, 3>> POS_AY{
	{ "C", { { { 0, 0 }, { 69 + 134, 378 }, { 107+134, 361 } } } },
	{ "L", { { { 0, 0 }, { 191, 374 }, { 234, 363 } } } },
	{ "R", { { { 0, 0 }, { 217, 372 }, { 252, 366 } } } }
};

map<string, std::array<positions, 3>> POS_DA{
	{ "C", { { { 0, 0 }, { 108 , 406 }, { 129 , 348 } } } }
};

map<string, std::array<positions, 3>> POS_KI{
	{ "C", { { { 0, 0 }, { 204 , 373 }, { 235 , 358 } } } },
	{ "L", { { { 0, 0 }, { 214 , 367 }, { 247 , 358 } } } },
	{ "R", { { { 0, 0 }, { 213 , 359 }, { 237 , 356 } } } },
};


map<string, std::array<positions, 3>> POS_AK{
	{ "C", { { { 0, 0 }, { 138 + 81, 397 }, { 162 + 81, 361 } } } },
	{ "L", { { { 0, 0 }, { 128 + 91, 393 }, { 153 + 91, 357 } } } }
};

map<string, std::array<positions, 3>> POS_KA{
	{ "C", { { { 0, 0 }, { 206, 356 }, { 246, 348 } } } },
	{ "R", { { { 0, 0 }, { 89 + 127, 355 }, { 114 + 127, 343 } } } }
};

map<string, std::array<positions, 3>> POS_KU{
	{ "C", { { { 0, 0 }, { 105 + 101, 369 }, { 146 + 101, 345 } } } },
	{ "L", { { { 0, 0 }, { 91 + 116, 353 }, { 134 + 116, 347 } } } },
	{ "R", { { { 0, 0 }, { 140 + 91, 355 }, { 173 + 91, 337 } } } }
};

map<string, std::array<positions, 3>> POS_MA{
	{ "C", { { { 0, 0 }, { 85 + 115, 381 }, { 126 + 115, 376 } } } },
	{ "L", { { { 0, 0 }, { 71 + 116, 380 }, { 110 + 116, 370 } } } },
	{ "R", { { { 0, 0 }, { 85 + 120, 380 }, { 117 + 120, 363 } } } }
};

map<string, std::array<positions, 3>> POS_RO{
	{ "C", { { { 0, 0 }, { 64 + 134, 396 }, { 101 + 134, 382 } } } },
	{ "L", { { { 0, 0 }, { 75 + 134, 392 }, { 118 + 134, 385 } } } }
};

map<string, std::array<positions, 3>> POS_SA{
	{ "C", { { { 0, 0 }, { 159 + 52, 359 }, { 196 + 52, 357 } } } },
	{ "L", { { { 0, 0 }, { 75 + 129, 353 }, { 113 + 129, 350 } } } },
	{ "R", { { { 0, 0 }, { 101 + 116, 374 }, { 139 + 116, 356 } } } }
};

map<string, std::array<positions, 3>> POS_SE{
	{ "C", { { { 0, 0 }, { 185, 365 }, { 222, 354 } } } },
	{ "L", { { { 0, 0 }, { 170, 380 }, { 212, 367 } } } },
	{ "R", { { { 0, 0 }, { 194, 349 }, { 243, 352 } } } }
};

map<string, std::array<positions, 3>> POS_YO{
	{ "C", { { { 0, 0 }, { 73 + 151, 407 }, { 97 + 151, 367 } } } }
};

static map<any_enum::posicion_sprite, positions> POS_HEAD{
	{ any_enum::centr, { 0, 0 } },
	{ any_enum::left, { -426, 0 } },
	{ any_enum::left_centr, { -213, 0 } },
	{ any_enum::right, { 426, 0 } },
	{ any_enum::right_centr, { 213, 0 } }
};

Object_Sprtite::Object_Sprtite(any_enum::name_sprite chapter_name, string type_sprite, int num_sprite, int num_face) : Object_Scene()// сгенерить данные спрайта и его координаты
{
	this->my_name = chapter_name;
	if (num_face != NULL)
	{
		switch (this->my_name)
		{
		case any_enum::AY:
		{
								 dir_obj = SPRITE_DIR["AY"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
								 face_dir = SPRITE_DIR["AY"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
								 this->pos = POS_AY[string("") + type_sprite[0]];
								 break;
		}
		case any_enum::DA:
		{
								 dir_obj = SPRITE_DIR["DA"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
								 face_dir = SPRITE_DIR["DA"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
								 this->pos = POS_DA[string("") + type_sprite[0]];
								 break;
		}
		case any_enum::KI:
		{
								 dir_obj = SPRITE_DIR["KI"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
								 face_dir = SPRITE_DIR["KI"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
								 this->pos = POS_KI[string("") + type_sprite[0]];
								 break;
		}
		case any_enum::AK:
		{
							 dir_obj = SPRITE_DIR["AK"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
							 face_dir = SPRITE_DIR["AK"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
							 this->pos = POS_AK[string("") + type_sprite[0]];
							 break;
		}
		case any_enum::KA:
		{
							 dir_obj = SPRITE_DIR["KA"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
							 face_dir = SPRITE_DIR["KA"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
							 this->pos = POS_KA[string("") + type_sprite[0]];
							 break;
		}
		case any_enum::KU:
		{
							 dir_obj = SPRITE_DIR["KU"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
							 face_dir = SPRITE_DIR["KU"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
							 this->pos = POS_KU[string("") + type_sprite[0]];
							 break;
		}
		case any_enum::MA:
		{
							 dir_obj = SPRITE_DIR["MA"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
							 face_dir = SPRITE_DIR["MA"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
							 this->pos = POS_MA[string("") + type_sprite[0]];
							 break;
		}
		case any_enum::RO:
		{
							 dir_obj = SPRITE_DIR["RO"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
							 face_dir = SPRITE_DIR["RO"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
							 this->pos = POS_RO[string("") + type_sprite[0]];
							 break;
		}
		case any_enum::SA:
		{
							 dir_obj = SPRITE_DIR["SA"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
							 face_dir = SPRITE_DIR["SA"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
							 this->pos = POS_SA[string("") + type_sprite[0]];
							 break;
		}
		case any_enum::SE:
		{
							 dir_obj = SPRITE_DIR["SE"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
							 face_dir = SPRITE_DIR["SE"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
							 this->pos = POS_SE[string("") + type_sprite[0]];
							 break;
		}
		case any_enum::YO:
		{
							 dir_obj = SPRITE_DIR["YO"][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
							 face_dir = SPRITE_DIR["YO"][type_sprite][NAME_MAP_FACE][to_string(num_face)];
							 this->pos = POS_YO[string("") + type_sprite[0]];
							 break;
		}
		default:
			break;
		}
	}
}

Object_Sprtite::Object_Sprtite(any_enum::name_sprite chapter_name)
{
	this->my_name = chapter_name;
	this->hide = true;
}



swich_node Object_Sprtite::draw()
{
	if (this->dir_obj != "empty")
	{
		if (this->hide == false)
		{
			for (int n = 0; n < cout_sprite; n++)
			{
				if (check_sprite_for_state[index_sprite[n]] == any_enum::FREE)
				{
					this->my_node = *index_sprite[n];
					auto sprite = static_cast<Sprite*>(this->my_node->getChildByName("Sprite"));
					auto blink = static_cast<Sprite*>(this->my_node->getChildByName("Blink"));
					auto speak = static_cast<Sprite*>(this->my_node->getChildByName("Speak"));


					sprite->setTexture(home_dir + dir_obj);
					blink->setTexture(home_dir + face_dir + SPRITE_BLINK_DIR + SPRITE_BLINK_ANIM_DIR[0]);
					speak->setTexture(home_dir + face_dir + SPRITE_SPEAK_DIR + SPRITE_SPEAK_ANIM_DIR[0]);

					sprite->setPosition(pos[0].x, pos[0].y + POS_HEIGHT[this->my_name]);
					blink->setPosition(pos[1].x, pos[1].y + POS_HEIGHT[this->my_name]);
					speak->setPosition(pos[2].x, pos[2].y + POS_HEIGHT[this->my_name]);
					this->my_node->setPosition(POS_HEAD[my_pos].x, POS_HEAD[my_pos].y);
					auto for_return = swich_node{ name_for_node[this->my_name] == nullptr ? nullptr : *name_for_node[this->my_name], this->my_node }; // старый нод по имени - а новый по закрепленному...
					check_sprite_for_state[index_sprite[n]] = any_enum::BUSY; // ставим наш рабочим
					if (name_for_node[this->my_name] != nullptr)
						check_sprite_for_state[name_for_node[this->my_name]] = any_enum::FREE; //а тот теперь свободен
					name_for_node[this->my_name] = index_sprite[n]; // заменяем ноду на свою в именах
					return for_return;
				}
			}
		}
		else // если прячем
		{
			if (name_for_node[this->my_name] != nullptr)// если есть занятая нода по имени
			{
				this->my_node = *name_for_node[this->my_name]; //ставим себе эту ноду
				check_sprite_for_state[name_for_node[this->my_name]] = any_enum::FREE; //а тот теперь свободен
			}
			name_for_node[this->my_name] = nullptr; // обнуляем указатель на ноду по имени
			auto for_return = swich_node{ this->my_node, nullptr }; //данные возврата для свича
			return for_return;


		}
	}
	else // простая иницилизация экшона
	{
		if (name_for_node[this->my_name] != nullptr) // если есть занятый нод спрайта по имени возвращаем адрес спрайта для применения экшонов
		{
			my_node = *name_for_node[this->my_name];
			return swich_node{ this->my_node, nullptr };
		}
		//else
		//{
		//	for (int n = 0; n < cout_sprite; n++)
		//	{
		//		if (check_sprite_for_state[index_sprite[n]] == FREE)
		//		{
		//			this->my_node = *index_sprite[n];
		//			return swich_node{ this->my_node, nullptr };
		//		}
		//	}
		//}
	}
	return swich_node{ nullptr, nullptr };

}