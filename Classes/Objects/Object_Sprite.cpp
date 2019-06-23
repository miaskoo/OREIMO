#include "Object_Sprite.h"
#include <fstream>

static const int cout_anim = 3; //количество позиций спрайт - глаза - рот
static const int cout_sprite = 6; // максимальное количество используемых спрайтов
extern int string_to_int(std::string temp);


std::array <Node**, 6> index_sprite{ &Sprite1, &Sprite2 , &Sprite3 , &Sprite4 ,  &Sprite5,  &Sprite6 };

map< Node**, any_enum::state_node> check_sprite_for_state{ // свободен ли спрайт
	{ index_sprite[0], any_enum::FREE }, { index_sprite[1], any_enum::FREE }, { index_sprite[2], any_enum::FREE },
	{ index_sprite[3], any_enum::FREE }, { index_sprite[4], any_enum::FREE }, { index_sprite[5], any_enum::FREE } 
}; 

map<any_enum::name_sprite, Node**> name_for_node{  //им€ закрепленное за нодой спрайте ****************** потом когда будешь делать проверки на тип текстуры  - можно будет провер€ть по местомоложение текстуры если одинаково - свич мгновенный, если нет, ну значит нет
	{ any_enum::KI, nullptr }, { any_enum::AY, nullptr }, { any_enum::DA, nullptr },
	{ any_enum::AK, nullptr }, { any_enum::KA, nullptr }, { any_enum::KU, nullptr },
	{ any_enum::MA, nullptr }, { any_enum::RO, nullptr }, { any_enum::SA, nullptr },
	{ any_enum::SE, nullptr }, { any_enum::YO, nullptr } };


const int smeh_creator = 200;
map<any_enum::posicion_sprite, positions> POS_HEAD{
	{ any_enum::centr,{ 0 + smeh_creator, 0 } },
{ any_enum::left,{ -426 + smeh_creator, 0 } },
{ any_enum::left_centr,{ -213 + smeh_creator, 0 } },
{ any_enum::right,{ 426 + smeh_creator, 0 } },
{ any_enum::right_centr,{ 213 + smeh_creator, 0 } }
};



static map<any_enum::name_sprite, int> POS_HEIGHT{
	{ any_enum::AY, 166 +100},
	{ any_enum::DA, 175 + 100 },
	{ any_enum::KI, 165 + 100 },
	{ any_enum::AK, 177 + 100 },
	{ any_enum::KA, 148 + 100 },
	{ any_enum::KU, 160 + 100 },
	{ any_enum::MA, 160 + 100 },
	{ any_enum::RO, 163 + 100 },
	{ any_enum::SA, 180 + 100 },
	{ any_enum::SE, 163 + 100 },
	{ any_enum::YO, 160 + 100 }
};


//const int size_chapters = 11;
std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::array<positions, 3>>>>> POS
{
	std::make_pair
	(
		std::string("AY"),std::vector<std::pair<std::string, std::array<positions, 3>>>
		{
			{ std::make_pair(std::string("C"), std::array<positions, 3>{ { { 0, 0 },{ 203, 378 },{ 241, 361 }}}) } ,
			{ std::make_pair(std::string("C_COSP"), std::array<positions, 3>{ { { 0, 0 },{ 203, 378 },{ 241, 361 }}}) } ,
			{ std::make_pair(std::string("L"),std::array<positions, 3>{ { { 0, 0 },{ 191, 374 },{ 234, 363 } } })},
			{ std::make_pair(std::string("L_COSP"),std::array<positions, 3>{ { { 0, 0 },{ 191, 374 },{ 234, 363 } } }) },
			{ std::make_pair(std::string("R"),std::array<positions, 3>{ { { 0, 0 },{ 217, 372 },{ 252, 366 } } }) },
			{ std::make_pair(std::string("R_COSP"),std::array<positions, 3>{ { { 0, 0 },{ 217, 372 },{ 252, 366 } } }) }
		}
   ),
	std::make_pair
	(
		"DA", std::vector<std::pair<std::string, std::array<positions, 3>>>
	{
		{ std::make_pair("C", std::array<positions, 3>{ { { 0, 0 }, { 198 , 406 }, { 219 , 348 }}}) }
	}
	),
	std::make_pair
	(
		"KI", std::vector<std::pair<std::string, std::array<positions, 3>>>
	{
		{ std::make_pair("C", std::array<positions, 3>{ { { 0, 0 }, { 204 , 373 }, { 235 , 358 }}}) },
		{ std::make_pair("L",std::array<positions, 3>{ { { 0, 0 },{ 214 , 367 },{ 247 , 358 } } }) },
		{ std::make_pair("R",std::array<positions, 3>{ { { 0, 0 },{ 213 , 359 },{ 237 , 356 } } }) }
	}
	),
	std::make_pair
	(
		"AK", std::vector<std::pair<std::string, std::array<positions, 3>>>
	{
		{ std::make_pair("C", std::array<positions, 3>{ { { 0, 0 }, { 138 + 81, 397 }, { 162 + 81, 361 }}}) },
		{ std::make_pair("L",std::array<positions, 3>{ { { 0, 0 },{ 128 + 91, 393 },{ 153 + 91, 357 }  } }) }
	}
	),
	std::make_pair
	(
		"KA", std::vector<std::pair<std::string, std::array<positions, 3>>>
	{
		{ std::make_pair("C", std::array<positions, 3>{ { { 0, 0 }, { 206, 356 }, { 246, 348 }}}) },
		{ std::make_pair("C_COSP", std::array<positions, 3>{ { { 0, 0 },{ 206, 356 },{ 246, 348 }}}) },
		{ std::make_pair("R",std::array<positions, 3>{ { { 0, 0 },{ 89 + 127, 355 },{ 114 + 127, 343 }  } }) },
		{ std::make_pair("R_COSP",std::array<positions, 3>{ { { 0, 0 },{ 89 + 127, 352 },{ 114 + 127, 345 }  } }) }
	}
	),
	std::make_pair
	(
		"KU", std::vector<std::pair<std::string, std::array<positions, 3>>>
	{
		{ std::make_pair("C", std::array<positions, 3>{ { { 0, 0 }, { 105 + 101, 369 }, { 146 + 101, 345 }}}) },
		{ std::make_pair("C_COSP", std::array<positions, 3>{ { { 0, 0 },{ 105 + 101, 369 },{ 146 + 101, 345 }}}) },
		{ std::make_pair("L",std::array<positions, 3>{ { { 0, 0 },{ 91 + 116, 353 },{ 134 + 116, 347 }  } }) },
		{ std::make_pair("L_COSP",std::array<positions, 3>{ { { 0, 0 },{ 91 + 116, 353 },{ 134 + 116, 347 }  } }) },
		{ std::make_pair("R",std::array<positions, 3>{ { { 0, 0 },{ 140 + 91, 355 },{ 173 + 91, 337 }  } }) },
		{ std::make_pair("R_COSP",std::array<positions, 3>{ { { 0, 0 },{ 140 + 91, 355 },{ 173 + 91, 337 }  } }) }
	}
	),
	std::make_pair
	(
		"MA", std::vector<std::pair<std::string, std::array<positions, 3>>>
	{
		{ std::make_pair("C", std::array<positions, 3>{ { { 0, 0 }, { 85 + 115, 381 }, { 126 + 115, 376 }}}) },
		{ std::make_pair("L",std::array<positions, 3>{ { { 0, 0 },{ 71 + 116, 380 },{ 110 + 116, 370 } } }) },
		{ std::make_pair("R",std::array<positions, 3>{ { { 0, 0 },{ 85 + 120, 380 },{ 117 + 120, 363 }  } }) }
	}
	),
	std::make_pair
	(
		"RO", std::vector<std::pair<std::string, std::array<positions, 3>>>
	{
		{ std::make_pair("C", std::array<positions, 3>{ { { 0, 0 }, { 64 + 134, 396 }, { 101 + 134, 382 }}}) },
		{ std::make_pair("R",std::array<positions, 3>{ { { 0, 0 },{ 75 + 134, 392 },{ 118 + 134, 385 } } }) }
	}
	),
	std::make_pair
	(
		"SA", std::vector<std::pair<std::string, std::array<positions, 3>>>
	{
		{ std::make_pair("C", std::array<positions, 3>{ { { 0, 0 }, { 159 + 52, 359 }, { 196 + 52, 357 }}}) },
		{ std::make_pair("L",std::array<positions, 3>{ { { 0, 0 },{ 75 + 129, 353 },{ 113 + 129, 350 } } }) },
		{ std::make_pair("R",std::array<positions, 3>{ { { 0, 0 },{ 101 + 116, 374 },{ 139 + 116, 356 } } }) }
	}
	),
	std::make_pair
	(
		"SE", std::vector<std::pair<std::string, std::array<positions, 3>>>
	{
		{ std::make_pair("C", std::array<positions, 3>{ { { 0, 0 }, { 185, 365 }, { 222, 354 }}}) },
		{ std::make_pair("L",std::array<positions, 3>{ { { 0, 0 },{ 170, 380 },{ 212, 367 } } }) },
		{ std::make_pair("R",std::array<positions, 3>{ { { 0, 0 },{ 194, 349 },{ 243, 352 } } }) }
	}
	),
	std::make_pair
	(
		"YO", std::vector<std::pair<std::string, std::array<positions, 3>>>
	{
		{ std::make_pair("C", std::array<positions, 3>{ { { 0, 0 }, { 73 + 151, 407 }, { 97 + 151, 367 }}}) }
	}
	)
};

std::array<positions, 3> search_pos(std::string name, std::string pos)
{
	for (int n = 0; n < POS.size(); n++)
	{
		if (POS[n].first == name)
		{
			for (int i = 0; i < POS[n].second.size(); i++)
			{
				if (POS[n].second[i].first == pos)
				{
					return POS[n].second[i].second;
				}
			}
		}
	}
	return { 0,0,0 };
}

std::map <Sprite*, int> action_tag;

void relese_old_state(Node *old_node)//отчищает старое состо€ние зан€того спрайта на свободное
{
	auto cur_iter = check_sprite_for_state.begin();

	while (cur_iter != check_sprite_for_state.end())
	{
		if ((*cur_iter->first) == old_node)
		{
			cur_iter->second = any_enum::FREE;
		}
		cur_iter++;
	}
}

void clear_mapani(Sprite* blink)//чистит аргументы экшонов в мапе
{
	auto cur_iter = action_tag.begin();
	while (cur_iter != action_tag.end())
	{
		if (cur_iter->first == blink)
		{
			action_tag.erase(cur_iter);
			break;
		}
		cur_iter++;
	}
}

std::string Get_name_from_enum(any_enum::name_sprite my_name)
{
	std::string cur_name;
	switch (my_name)
	{
	case any_enum::AY:
	{
		cur_name = "AY";
		break;
	}
	case any_enum::DA:
	{
		cur_name = "DA";
		break;
	}
	case any_enum::KI:
	{
		cur_name = "KI";
		break;
	}
	case any_enum::AK:
	{
		cur_name = "AK";
		break;
	}
	case any_enum::KA:
	{
		cur_name = "KA";
		break;
	}
	case any_enum::KU:
	{
		cur_name = "KU";
		break;
	}
	case any_enum::MA:
	{
		cur_name = "MA";
		break;
	}
	case any_enum::RO:
	{
		cur_name = "RO";
		break;
	}
	case any_enum::SA:
	{
		cur_name = "SA";
		break;
	}
	case any_enum::SE:
	{
		cur_name = "SE";
		break;
	}
	case any_enum::YO:
	{
		cur_name = "YO";
		break;
	}
	default:
		MessageBox("Ќеизвестное им€!", "ќЎ»Ѕ ј");
		cur_name ="";
	}
	return cur_name;
}
any_enum::name_sprite Get_enum_from_name(std::string my_name)
{
	any_enum::name_sprite cur_name;

	if (my_name == "AY")
		cur_name = any_enum::AY;
	else if (my_name == "DA")
		cur_name = any_enum::DA;
	else if (my_name == "KI")
		cur_name = any_enum::KI;
	else if (my_name == "AK")
		cur_name = any_enum::AK;
	else if (my_name == "KA")
		cur_name = any_enum::KA;
	else if (my_name == "KU")
		cur_name = any_enum::KU;
	else if (my_name == "MA")
		cur_name = any_enum::MA;
	else if (my_name == "RO")
		cur_name = any_enum::RO;
	else if (my_name == "SA")
		cur_name = any_enum::SA;
	else if (my_name == "SE")
		cur_name = any_enum::SE;
	else if (my_name == "YO")
		cur_name = any_enum::YO;
	else
		cur_name = any_enum::NONE;

	return cur_name;
}

Object_Sprite::Object_Sprite(any_enum::name_sprite chapter_name, string type_sprite, int num_sprite, int num_face) : Object_Scene()// сгенерить данные спрайта и его координаты
{
	this->my_name = chapter_name;
	std::string cur_name = "";
	if (num_face != NULL)
	{
		cur_name = Get_name_from_enum(chapter_name);
	}
	if (cur_name.length() != 0)
	{
		dir_obj = SPRITE_DIR[cur_name][type_sprite][NAME_MAP_SPRITE][to_string(num_sprite)];
		face_dir = SPRITE_DIR[cur_name][type_sprite][NAME_MAP_FACE][to_string(num_face)];
		this->pos = search_pos(cur_name, type_sprite);
	}
	else
	{
		dir_obj = "empty";
	}
	this->hide = false;
}



Object_Sprite::Object_Sprite(any_enum::name_sprite chapter_name)
{
	this->my_name = chapter_name;
	this->hide = true;
}

#include "ui\UIScale9Sprite.h"
#include "ui\shaders\UIShaders.h"


//переделал CCSprite draw чтобы измен€л opacity шейдера на спрайте


swich_node Object_Sprite::draw()
{
	if (this->dir_obj != "empty")
	{
		for (int n = 0; n < cout_sprite; n++)
		{
			if (check_sprite_for_state[index_sprite[n]] == any_enum::FREE && (*index_sprite[n])->getOpacity() == 0)
			{
				this->my_node = *index_sprite[n];

				auto sprite = static_cast<Sprite*>(this->my_node->getChildByName("Sprite"));
				auto blink = static_cast<Sprite*>(sprite->getChildByName("Blink"));
				auto speak = static_cast<Sprite*>(sprite->getChildByName("Speak"));

				this->my_node->stopAllActions();
				blink->stopAllActions();
				speak->stopAllActions();
				sprite->stopAllActions();

				clear_mapani(blink);

				

				sprite->setTexture(dir_home_sprite + dir_obj);
				blink->setTexture(dir_home_sprite + face_dir + SPRITE_BLINK_DIR + SPRITE_BLINK_ANIM_DIR[0]);
				speak->setTexture(dir_home_sprite + face_dir + SPRITE_SPEAK_DIR + SPRITE_SPEAK_ANIM_DIR[0]);

			
				GLProgramState* state = GetShader(this->state);

				
				if (state != nullptr)
				{			
					sprite->setGLProgramState(state);
					blink->setGLProgramState(state);
					speak->setGLProgramState(state);
				}
				else
				{
					MessageBox("ќшибка создани€ шейдера!", "ќшибка!");
					std::terminate();
				}

				float speed_ani_blink = 0.05f;


				auto func = CallFunc::create([=]()
				{
					if (action_tag.find(blink) == action_tag.end())
					{
						auto cur_action = (Sequence::create(
							DelayTime::create(rand() % 8 + 3),
							Repeat::create(
								Sequence::create(
									CallFunc::create([=]()
						{
							blink->setTexture(dir_home_sprite + face_dir + SPRITE_BLINK_DIR + SPRITE_BLINK_ANIM_DIR[1]);
						}),
									DelayTime::create(speed_ani_blink),
							CallFunc::create([=]()
						{
							blink->setTexture(dir_home_sprite + face_dir + SPRITE_BLINK_DIR + SPRITE_BLINK_ANIM_DIR[2]);
						}),
							DelayTime::create(speed_ani_blink),
							CallFunc::create([=]()
						{
							blink->setTexture(dir_home_sprite + face_dir + SPRITE_BLINK_DIR + SPRITE_BLINK_ANIM_DIR[1]);
						}),
							DelayTime::create(speed_ani_blink),
							CallFunc::create([=]()
						{
							blink->setTexture(dir_home_sprite + face_dir + SPRITE_BLINK_DIR + SPRITE_BLINK_ANIM_DIR[0]);
						}),
							DelayTime::create(speed_ani_blink), nullptr), rand() % 2 + 1), nullptr));
						blink->runAction(cur_action);
						action_tag[blink] = cur_action->getTag();
					}
					else
					{
						if (blink->getActionByTag(action_tag[blink]) != nullptr)
						{
							return;
						}
						else
						{
							clear_mapani(blink);
						}
					}


				});

				//функци€ мограци€ .. TODO в деле€х и репите не работает рандом - нада думать
				sprite->runAction(RepeatForever::create(Sequence::create(func, DelayTime::create(0.5f), nullptr)));//rand()%2+1),



				Vec2 temp = sprite->getTexture()->getContentSize();//поскольку теперь спрайт смещен - нужно смещать и координаты
				sprite->setPosition(pos[0].x + temp.x / 2, pos[0].y + temp.y);
				blink->setPosition(pos[1].x, pos[1].y);
				speak->setPosition(pos[2].x, pos[2].y);
				this->my_node->setPosition(POS_HEAD[my_pos].x, POS_HEAD[my_pos].y + POS_HEIGHT[this->my_name]);
				auto for_return = swich_node{ name_for_node[this->my_name] == nullptr ? nullptr : *name_for_node[this->my_name], this->my_node }; // старый нод по имени - а новый по закрепленному...
				check_sprite_for_state[index_sprite[n]] = any_enum::BUSY; // ставим наш рабочим
				if (name_for_node[this->my_name] != nullptr)
				{
					auto old_node = (*name_for_node[this->my_name]);

					auto old_sprite = old_node->getChildByName("Sprite");
					auto old_blink = static_cast<Sprite*>(old_sprite->getChildByName("Blink"));
					auto old_speak = static_cast<Sprite*>(old_sprite->getChildByName("Speak"));

					old_node->stopAllActions();
					old_sprite->stopAllActions();
					old_blink->stopAllActions();
					old_speak->stopAllActions();

					clear_mapani(old_blink);//чистим старый аргумент
				
					check_sprite_for_state[name_for_node[this->my_name]] = any_enum::FREE; //а тот теперь свободен

				}
				name_for_node[this->my_name] = index_sprite[n]; // замен€ем ноду на свою в именах
				return for_return;
			}
		}
	}
	else
	{
		if (this->hide == true)
		{
			if (name_for_node[this->my_name] != nullptr)// если есть зан€та€ нода по имени
			{
				this->my_node = *name_for_node[this->my_name]; //ставим себе эту ноду

				auto sprite = static_cast<Sprite*>(this->my_node->getChildByName("Sprite"));
				auto blink = static_cast<Sprite*>(sprite->getChildByName("Blink"));
				auto speak = static_cast<Sprite*>(sprite->getChildByName("Speak"));

				this->my_node->stopAllActions();
				blink->stopAllActions();
				speak->stopAllActions();
				sprite->stopAllActions();

				clear_mapani(blink);
				auto old_sprite_node = &check_sprite_for_state[name_for_node[this->my_name]];
				check_sprite_for_state[name_for_node[this->my_name]] = any_enum::FREE; //а тот теперь свободен
			}
			name_for_node[this->my_name] = nullptr; // обнул€ем указатель на ноду по имени
			auto for_return = swich_node{ this->my_node, nullptr }; //данные возврата дл€ свича
			return for_return;
		}
		else // проста€ иницилизаци€ экшона
		{
			if (name_for_node[this->my_name] != nullptr) // если есть зан€тый нод спрайта по имени возвращаем адрес спрайта дл€ применени€ экшонов
			{
				my_node = *name_for_node[this->my_name];
				return swich_node{ this->my_node, nullptr };
			}
		}
	}
	
	return swich_node{ nullptr, nullptr };

}