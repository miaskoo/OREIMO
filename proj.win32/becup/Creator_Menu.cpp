﻿#include "cocos2d.h"
#include "cocostudio/CocoStudio.h" // Подключает библиотеку кокос студии для загрузки сцен из csb файлов
#include "Main_Menu.h"
#include "Page.h"
#include "Script.h"
using namespace cocos2d;
using namespace std;


Node *Game_Mode = nullptr;
Node *Text_Box = nullptr;
Node *Scene1 = nullptr;
Node *Scene2 = nullptr;
Node *Sprite1 = nullptr;
Node *Sprite2 = nullptr;
Node *Sprite3 = nullptr;
Node *Sprite4 = nullptr;
Node *Sprite5 = nullptr;
Node *Sprite6 = nullptr;
ui::Text *Label_text = nullptr;
ui::Text *Label_name = nullptr;
///////////////////////////////////////////////////////////// спецификатор на типы 0x01 - сцена , 0x02 - спрайт
//////////////////////////////////////////////// спрайт/сцена
//////////////////////////////////////////////// 00 - размер блока x16 0x01
////////////////////////////////////////////////00 - тип объекта 0x02
////////////////////////////////////////////////00 - тип взаимодействия 0x03   // 0x01 swich 0x02 action
//////////////////////////////////////////////// 00 - тип появления/тип экшона 0x04
//////////////////////////////////////////////// 00 - если сцена CG или BG?			0x05		
////////////////////////////////////////////////    - если спрайт - указатель на чаптера 
//////////////////////////////////////////////// 00 - указатель на дирректорию (BG/CG) 0x06
////////////////////////////////////////////////    - если спрайт указатель на тип L C R
////////////////////////////////////////////////00 - если спрайт указатель на номер текстуры 0x07
////////////////////////////////////////////////00 - если спрайт указатель на номер лица 0x08
//////////////////////////////////////////////// 00 00 00 00 00 00 00 00 -9 0a 0b 0c 0d 0e 0xf
//////////////////////////////////////////////// микс
//////////////////////////////////////////////// размер блока , тип объекта, тип взаимодействия, тип появления, количество объектов в объекте mix
//////////////////////////////////////////////// далее как обычно - описание каждого блока по количеству указанному в mix, ВСЕ количество в mix будет добавлятся и иницится как mix
////////////////////////////////////////////////




int string_to_int(std::string temp)
{
	std::stringstream buff;
	buff << temp;
	int complete;
	buff >> complete;
	return complete;
}


// int node
// node - buttons
// node + button - data_obj

struct data_obj
{
	type_struct::type_object my_type = type_struct::none;
	type_interactions my_inter = unknown;
	type_swich my_swich = SIMPLE;
	type_action my_action = Zzzzz;
	sprite_sruct::name_sprite my_name = sprite_sruct::NONE;
	sprite_sruct::posicion_sprite my_position = sprite_sruct::centr;
	string data1 = "";
	string data2 = "";
	string data3 = "";
	bool hide = false;

};



string current_type = "None";//название объекта

string scene_type = "РЎС†РµРЅР°";
string sprite_type = "РЎРїСЂР°Р№С‚";
string music_type = "РњСѓР·С‹РєР°";
string gamese_type = "РРіСЂРѕРІС‹Рµ Р·РІСѓРєРё";
string systemse_type = "РЎРёСЃС‚РµРјРЅС‹Рµ Р·РІСѓРєРё";
string text_type = "РўРµРєСЃС‚";
string textbox_type = "РўРµРєСЃС‚Р±РѕРєСЃ";

//пока не используется
Script *cur_script = nullptr; 
//пока не используется
vector<Page*> all_pages; //сюда пихаю все страницы



char *curobj = nullptr; //адрес выбранного редактируемого объекта


struct page_obj
{
	int cur_box_count = NULL;// количество боксов
	map<int, int> cur_row_count; //количество дейсвий по номеру бокса

	int cur_box_smeh = NULL; //смещает данные бокса по их количеству сейчас все настроено на смещение влево на один при добовлении более 3 коробок передвижение по ним нет
	map<int, int> cur_row_smeh; //относительно текущего бокса говорит какое сейчас будет смещение в рядах

	array<bool, 3> visable_id_box = { { false ,  false ,  false } };// Видимость боксов 

	///////////BOX//////ROW////VISIBLE/////
	map <int, map<int, bool>> visable_id_button; //получение по номеру бокса и номеру ряда информацию о видимости кнопок в полях

	///////////BOX//////ROW////DATA/////
	map<int, map<int, data_obj>> intedex_data; //получение по номеру бокса и номеру ряда информацию текущей ячейки
};

int cur_page = NULL; //текущая страница
int cur_page_count = NULL;
int cur_page_smeh = NULL;

map<int, page_obj*> cur_page_data;  // хранит разобранную инфу страниц






static data_obj *creator_obj = nullptr;//текущий выбранный объект

void MAINBOX::creatorset()
{
	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	this->removeAllComponents();
	auto Creator_Mode = CSLoader::createNode("Resources\\All_Scene_cocos\\Creator_scene\\Creator_scene.csb");
	this->addChild(Creator_Mode, 0);

	Game_Mode = Creator_Mode->getChildByTag(15465);
	Scene1 = Game_Mode->getChildByTag(1);
	Scene2 = Game_Mode->getChildByTag(2);
	Sprite1 = Game_Mode->getChildByTag(3);
	Sprite2 = Game_Mode->getChildByTag(4);
	Sprite3 = Game_Mode->getChildByTag(5);
	Sprite4 = Game_Mode->getChildByTag(6);
	Sprite5 = Game_Mode->getChildByTag(7);
	Sprite6 = Game_Mode->getChildByTag(8);
	Text_Box = Game_Mode->getChildByTag(4535);
	
	Label_text = static_cast<ui::Text*>(Game_Mode->getChildByTag(4534));
	Label_name = static_cast<ui::Text*>(Game_Mode->getChildByTag(4533));


	Sprite1->setAnchorPoint(Vec2(0.5f, 0.5f));
	Sprite2->setAnchorPoint(Vec2(0.5f, 0.5f));
	Sprite3->setAnchorPoint(Vec2(0.5f, 0.5f));
	Sprite4->setAnchorPoint(Vec2(0.5f, 0.5f));
	Sprite5->setAnchorPoint(Vec2(0.5f, 0.5f));
	Sprite6->setAnchorPoint(Vec2(0.5f, 0.5f));

	static ui::Button *PAGES[3] = 
	{
		static_cast<ui::Button*>(Creator_Mode->getChildByTag(2122)),
		static_cast<ui::Button*>(Creator_Mode->getChildByTag(2123)),
		static_cast<ui::Button*>(Creator_Mode->getChildByTag(2124)) 
	};

	static bool visable_id_page[3] = {false, false, false};
	
	ui::Button *id_button_page_plus = static_cast<ui::Button*>(Creator_Mode->getChildByTag(186)); // прибавляет страничку
	ui::Button *id_button_page_min = static_cast<ui::Button*>(Creator_Mode->getChildByTag(187)); //удаляет страничку

	ui::Button *id_button_page_up = static_cast<ui::Button*>(Creator_Mode->getChildByTag(188)); //прокрутка по страничкам вниз
	ui::Button *id_button_page_down = static_cast<ui::Button*>(Creator_Mode->getChildByTag(189)); //прокрутка по страничкам вверх

	// ноды боксов одновременных действий для последовательного вызова неопределенного количесва действий на одну страницу
	static Node* BOXS[3] = 
	{ 
		Creator_Mode->getChildByTag(1),
		Creator_Mode->getChildByTag(2), 
		Creator_Mode->getChildByTag(3)
	};

	//поле текста где отображается текущий номер действия
	static ui::Text* BOXS_NAME[3] = 
	{ 
		static_cast<ui::Text*>(BOXS[0]->getChildByTag(504)),
		static_cast<ui::Text*>(BOXS[1]->getChildByTag(504)),
		static_cast<ui::Text*>(BOXS[2]->getChildByTag(504)) 
	};



	ui::Button *id_button_box_plus = static_cast<ui::Button*>(Creator_Mode->getChildByTag(150)); // прибавляет бокс
	ui::Button *id_button_box_min = static_cast<ui::Button*>(Creator_Mode->getChildByTag(151)); //удаляет бокс

	static ui::Button *id_button[3][4]//объекты кнопки в полях
	{
		{
			static_cast<ui::Button*>(BOXS[0]->getChildByTag(1)),
			static_cast<ui::Button*>(BOXS[0]->getChildByTag(2)),
			static_cast<ui::Button*>(BOXS[0]->getChildByTag(3)),
			static_cast<ui::Button*>(BOXS[0]->getChildByTag(4))
		},
		{
			static_cast<ui::Button*>(BOXS[1]->getChildByTag(1)),
			static_cast<ui::Button*>(BOXS[1]->getChildByTag(2)),
			static_cast<ui::Button*>(BOXS[1]->getChildByTag(3)),
			static_cast<ui::Button*>(BOXS[1]->getChildByTag(4))
		},
		{
			static_cast<ui::Button*>(BOXS[2]->getChildByTag(1)),
			static_cast<ui::Button*>(BOXS[2]->getChildByTag(2)),
			static_cast<ui::Button*>(BOXS[2]->getChildByTag(3)),
			static_cast<ui::Button*>(BOXS[2]->getChildByTag(4))
		}
	};

	static ui::Button *id_button_pam[3][2]// плюс/минус
	{
		{
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(1)->getChildByTag(98)),//прибавляет ряд
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(1)->getChildByTag(99))//уменьшает ряд
		},
		{
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(2)->getChildByTag(98)),
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(2)->getChildByTag(99))
		},
		{
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(3)->getChildByTag(98)),
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(3)->getChildByTag(99))
		}
	};

	static map <ui::Button*, data_obj*> data_obj_id_button //привязка стуктур для созданий объектов к кнопкам
	{
		{ id_button[0][0], nullptr }, { id_button[0][1], nullptr }, { id_button[0][2], nullptr }, { id_button[0][3], nullptr },
		{ id_button[1][0], nullptr }, { id_button[1][1], nullptr }, { id_button[1][2], nullptr }, { id_button[1][3], nullptr }, 
		{ id_button[2][0], nullptr }, { id_button[2][1], nullptr }, { id_button[2][2], nullptr }, { id_button[2][3], nullptr }, 
	};

	//static ui::Button *Save_obj = static_cast<ui::Button*>(Game_Mode->getChildByTag(159753)); 
	static ui::Button *play_page = static_cast<ui::Button*>(Creator_Mode->getChildByTag(14758));

	static const int predel_choise = 8;
	static Node *choises[predel_choise]//ноды выборов и настроек
	{
			Creator_Mode->getChildByTag(90), // choise type BOX (sprite, scene, text.....)
			Creator_Mode->getChildByTag(91),
			Creator_Mode->getChildByTag(92),
			Creator_Mode->getChildByTag(93),
			Creator_Mode->getChildByTag(94),
			Creator_Mode->getChildByTag(95), //interact text
			Creator_Mode->getChildByTag(96), // action text(textbox)
			Creator_Mode->getChildByTag(97) // swich text
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//HEAD (Scene, Sprite)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static ui::Button *type_obj_choise[3]//тип объекта
	{
		static_cast<ui::Button*>(choises[0]->getChildByTag(1)), //SCENE
		static_cast<ui::Button*>(choises[0]->getChildByTag(2)), //SPRTITE
		static_cast<ui::Button*>(choises[0]->getChildByTag(4)) //TEXT
	};

	static ui::Button *intr_obj_choise[2]//тип взаимодействия с объектом(только для сцен и спрайтов)
	{
		static_cast<ui::Button*>(choises[1]->getChildByTag(1)), //SWICH
			static_cast<ui::Button*>(choises[1]->getChildByTag(2))  //ACTION
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//SCENE BOX
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SWICH
	static ui::Button *swich_scene_choise[5]// надстройки свича сцены
	{
			static_cast<ui::Button*>(choises[2]->getChildByTag(1)),
			static_cast<ui::Button*>(choises[2]->getChildByTag(2)),
			static_cast<ui::Button*>(choises[2]->getChildByTag(3)),
			static_cast<ui::Button*>(choises[2]->getChildByTag(4)),
			static_cast<ui::Button*>(choises[2]->getChildByTag(6))
	};

	static auto swich_scene_resource = static_cast<ui::TextField*>(choises[2]->getChildByTag(5)); //поле ввода для номера картинки сцены
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ACTION
	static ui::Button *action_scene_choise[2]// надстройки свича сцены
	{
			static_cast<ui::Button*>(choises[3]->getChildByTag(1)), //тряска
			static_cast<ui::Button*>(choises[3]->getChildByTag(2)) //One punch
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SPRITE BOX
	static ui::Button *swich_sprite_choise_chater[3]// выбор персонажа спрайта
	{
			static_cast<ui::Button*>(choises[4]->getChildByTag(1)), // AY
			static_cast<ui::Button*>(choises[4]->getChildByTag(2)), // KI
			static_cast<ui::Button*>(choises[4]->getChildByTag(3)), // DA
	};

	static auto Sprite_swich_box = static_cast<ui::ScrollView*>(choises[4]->getChildByTag(376)); //скрол надстроек свича
	Sprite_swich_box->setClippingEnabled(true);
	Sprite_swich_box->setClippingType(static_cast<ui::ScrollView::ClippingType>(1));

	static auto Sprite_action_box = static_cast<Node*>(choises[4]->getChildByTag(95)); //нода надстроек экшонов
	
	//SWICH

	static auto swich_sprite_hide = static_cast<ui::CheckBox*>(Sprite_swich_box->getChildByTag(99999)); //прячется ли спрайт /////////////////////////////////////////////////////////////////////////////////////////////////////
																																/////////Пометка, нужна функция обновления состояние с вызовом из смены кнопки

	static ui::Button *swich_sprite_choise_type[3]// надстройки свича спрайта
	{
		static_cast<ui::Button*>(Sprite_swich_box->getChildByTag(6)), // Centr
			static_cast<ui::Button*>(Sprite_swich_box->getChildByTag(7)), // RTL
			static_cast<ui::Button*>(Sprite_swich_box->getChildByTag(8)), // LTR
	};

	static auto sprite_swich_create_node = Sprite_swich_box->getChildByTag(526); // нода для надстроек позиций и информации о выводимом спрайте если нод не пропадает а создается новый

	static auto swich_sprite_resource_texture_type = static_cast<ui::TextField*>(sprite_swich_create_node->getChildByTag(15)); //поле ввода типа текстуры
	static auto swich_sprite_resource_texture_num = static_cast<ui::TextField*>(sprite_swich_create_node->getChildByTag(4)); //поле ввода номера текстуры персонажа
	static auto swich_sprite_resource_emotion = static_cast<ui::TextField*>(sprite_swich_create_node->getChildByTag(5)); //поле ввода номера эмоции

	static auto swich_sprite_resource_save = static_cast<ui::TextField*>(sprite_swich_create_node->getChildByTag(14)); //сохранить данные о текстурах

	static ui::Button *swich_sprite_choise_position[5]// надстройки положение спрайта
	{
			static_cast<ui::Button*>(sprite_swich_create_node->getChildByTag(9)), // centr
			static_cast<ui::Button*>(sprite_swich_create_node->getChildByTag(10)), // left
			static_cast<ui::Button*>(sprite_swich_create_node->getChildByTag(11)), // left/centr
			static_cast<ui::Button*>(sprite_swich_create_node->getChildByTag(12)), // right
			static_cast<ui::Button*>(sprite_swich_create_node->getChildByTag(13)), // right/centr
	};

	//ACTION

	static ui::Button *action_sprite_choise[5]
	{
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(1)), // JUMP
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(2)), // DOUBLE JUMP
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(3)), // MINICREASE
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(4)), // INCREASE
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(5)), // DECREASE
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//TEXT BOX

	static ui::Button *intr_text_choise[2]//тип взаимодействия с текстом(управляем фоном текста или самим текстом)
	{
		static_cast<ui::Button*>(choises[5]->getChildByTag(1)), //TEXTBOX
		static_cast<ui::Button*>(choises[5]->getChildByTag(2))  //TEXT
	};

	//SWICH
	////////

	//ACTION

	static ui::Button *action_text_choise[2]
	{
		static_cast<ui::Button*>(choises[6]->getChildByTag(1)), // SHOW
			static_cast<ui::Button*>(choises[6]->getChildByTag(2)) // HIDE
	};

	auto update_ind2([=]()// обновляем лишь специфическую инфу которую нужно сбрасывать между ячейками
	{
		swich_sprite_hide->setSelectedState(false);
		swich_scene_resource->setString("");
		swich_sprite_resource_texture_type->setString("");
		swich_sprite_resource_texture_num->setString("");
		swich_sprite_resource_emotion->setString("");
		if (creator_obj != nullptr)
			if ((creator_obj->hide == true && creator_obj->my_type == type_struct::sprite) || (creator_obj->hide == true && creator_obj->my_inter == swich))
				swich_sprite_hide->setSelectedState(true);
	}
	);

	auto gpi([=]()
	{
		return cur_page_data[cur_page];
	});
	
	auto update_inf([=]() //обновляет все везде где можно
	{


		for (int n = 0; n < 3; n++)
		{
			if (visable_id_page[n] == true)
			{
				PAGES[n]->setVisible(true);
				PAGES[n]->setTitleText(to_string(n + cur_page_smeh + 1));
			}
			else
				PAGES[n]->setVisible(false);
		}

		if (cur_page_count != NULL) // если есть страничка
		{

			if (gpi()->cur_box_count > 3) 
				gpi()->cur_box_smeh = gpi()->cur_box_count - 3;
			else
				gpi()->cur_box_smeh = 0;
			for (int n = 0; n < 3; n++) //обновляем боксы
			{
				if (gpi()->visable_id_box[n] == false)
				{
					BOXS[n]->setVisible(false);
					BOXS_NAME[n]->setText("");
					gpi()->cur_row_smeh[n + gpi()->cur_box_count] = 0;
					for (int i = 0; i < 4; i++)
					{
						data_obj_id_button[id_button[n][i]] = nullptr;
						gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] = false;
						id_button[n][i]->setVisible(false);
					}
					continue;
				}
				else
				{
					BOXS[n]->setVisible(true);
					BOXS_NAME[n]->setText(to_string(n + gpi()->cur_box_smeh));
					if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 4)
						gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] = gpi()->cur_row_count[n + gpi()->cur_box_smeh] - 4;
					else
						gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] = 0;


					for (int i = 0; i < 4; i++)
					{

						data_obj_id_button[id_button[n][i]] = &gpi()->intedex_data[n + gpi()->cur_box_smeh][i + gpi()->cur_row_smeh[n + gpi()->cur_box_smeh]];//привязываем  (по боксу со смещением бокса)
						if (gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] == false)
						{
							id_button[n][i]->setVisible(false);
						}
						else
						{
							id_button[n][i]->setVisible(true);
							string message = "";
							message += to_string(i + gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] + 1); // вывод номера текущего поля
							if (data_obj_id_button[id_button[n][i]]->my_type == type_struct::none)
							{
								message += " None";
							}
							else
							{
								switch (data_obj_id_button[id_button[n][i]]->my_type)
								{
								case type_struct::scene:
									message += " Scene";
									break;
								case type_struct::sprite:
									message += " Sprite";
									break;
								case type_struct::text:
									message += " Text";
									break;
								default:
									break;
								}
								switch (data_obj_id_button[id_button[n][i]]->my_inter)
								{
								case swich:
									message += " (swich)";
									break;
								case action:
									message += " (action)";
									break;
								default:
									break;
								}
							}
							id_button[n][i]->setTitleText(message);
						}
					}
				}
			}
			// изменение видимости всего на стандартные значения
			for (int n = 0; n < predel_choise; n++)
			{
				choises[n]->setVisible(false);
			}
			Sprite_swich_box->setVisible(false);
			Sprite_action_box->setVisible(false);
			sprite_swich_create_node->setVisible(false);
			if (creator_obj != nullptr)
			{
				choises[0]->setVisible(true);
				if (creator_obj->my_type == type_struct::scene || creator_obj->my_type == type_struct::sprite)
				{
					choises[1]->setVisible(true);

					if (creator_obj->my_type == type_struct::scene && creator_obj->my_inter == swich)
					{
						choises[2]->setVisible(true);
					}
					else if (creator_obj->my_type == type_struct::scene && creator_obj->my_inter == action)
					{
						choises[3]->setVisible(true);
					}
					else if (creator_obj->my_type == type_struct::sprite && creator_obj->my_inter == swich)
					{
						choises[4]->setVisible(true);
						if (creator_obj->my_name != sprite_sruct::NONE)
						{
							Sprite_swich_box->setVisible(true);
							if (creator_obj->hide == false)
							{
								sprite_swich_create_node->setVisible(true);
							}
						}
					}
					else if (creator_obj->my_type == type_struct::sprite && creator_obj->my_inter == action)
					{
						choises[4]->setVisible(true);
						if (creator_obj->my_name != sprite_sruct::NONE)
						{
							Sprite_action_box->setVisible(true);
						}
					}
				}
				else if (creator_obj->my_type == type_struct::text)
				{
					choises[5]->setVisible(true);
					if (creator_obj->my_inter == action)
						choises[6]->setVisible(true);
					else if (creator_obj->my_inter == swich)
						choises[7]->setVisible(true);
				}
			}
		}
	});

	id_button_page_plus->addClickEventListener([=](Ref*)
	{
		cur_page_count++;
		cur_page = cur_page_count-1;
		cur_page_data[cur_page] = new page_obj;
		if (cur_page_count < 4)
			visable_id_page[cur_page_count - 1] = true;

		if (cur_page_count > 3)
			cur_page_smeh = cur_page_count - 3;
		else
			cur_page_smeh = 0;

		creator_obj = nullptr; //сброс закрепленной инфы 

		update_inf();
		update_ind2();//фулл сброс

	});

	id_button_page_min->addClickEventListener([=](Ref*)
	{
		if (cur_page_count != NULL) // если есть страничка
		{
			cur_page = cur_page_count;
			cur_page_count--;
			delete cur_page_data[cur_page];
			cur_page_data[cur_page] = nullptr; // это нужно отчищать а не обнулять
			cur_page = cur_page_count - 1;


			if (cur_page_count < 3)
				visable_id_page[cur_page_count] = false;

			if (cur_page_count > 3)
				cur_page_smeh = cur_page_count - 3;
			else
				cur_page_smeh = 0;

			creator_obj = nullptr; //сброс закрепленной инфы 

			update_inf();
			update_ind2();//фулл сброс
		}
	});

	for (int n = 0; n < 3; n++)// для выбора страничек
	{
		PAGES[n]->addClickEventListener([=](Ref*)
		{
			cur_page = n + cur_page_smeh; // переход на выбранную страницу
			creator_obj = nullptr; //сброс закрепленной инфы 
			update_inf(); //сброс 
			update_ind2();//фулл сброс
		});
	}

	id_button_page_down->addClickEventListener([=](Ref*)
	{
		if (cur_page_smeh - 1 > -1)
			cur_page_smeh--;
		update_inf(); //сброс 
	});

	id_button_page_up->addClickEventListener([=](Ref*)
	{
		if (cur_page_smeh + 3 < cur_page_count)
			cur_page_smeh++;
		update_inf(); //сброс 
	});


	id_button_box_plus->addClickEventListener([=](Ref*)
	{
		if (cur_page_count != NULL) // если есть страничка
		{
			if (gpi()->cur_box_count > 2) //если боксов три и больше только смещаем инфу боксов и добавляем новый 
			{
				gpi()->cur_box_count++; //увеличили количество боксов
				gpi()->cur_row_count[gpi()->cur_box_smeh + 3] = NULL; //по смещению иницим колво ячеек
				for (int i = 0; i < 4; i++)
				{
					gpi()->visable_id_button[3 + gpi()->cur_box_smeh][i] = false;//обнуляем видимость действий текущего бокса
				}
				update_inf();
			}
			else //иначе все тоже самое + видимость бокса
			{
				for (int n = 0; n < 3; n++)// проход по всем боксам 
				{
					if (gpi()->visable_id_box[n] == false)
					{
						gpi()->visable_id_box[n] = true;
						gpi()->cur_box_count++;
						gpi()->cur_row_count[n] = NULL; //иницим число ячеек
						for (int i = 0; i < 4; i++)
						{
							gpi()->visable_id_button[n][i] = false; //обнуляем видимость действий текущего бокса
						}
						update_inf();
						break;
					}
				}
			}
		}
	});

	id_button_box_min->addClickEventListener([=](Ref*)
	{
		if (cur_page_count != NULL) // если есть страничка
		{
			if (gpi()->cur_box_count > 3) //если боксов больше 3 удаляем только инфу
			{
				for (int i = 0; i < gpi()->cur_row_count[gpi()->cur_box_smeh + 3]; i++) // отчистка всех действий у бокса /// если не влом потом добавь удалялку из мамы для чистки памяти
				{
					gpi()->intedex_data[3 + gpi()->cur_box_smeh][i] = data_obj{};
				}
				gpi()->cur_row_count[gpi()->cur_box_smeh + 3] = NULL; //тут тоже
				gpi()->cur_box_count--;
				update_inf();
			}
			else//иначе все тоже самое + видимость бокса
			{
				for (int n = 3; n > -1; n--)// проход по всем боксам обратно
				{
					if (gpi()->visable_id_box[n] == true)
					{
						gpi()->visable_id_box[n] = false;
						for (int i = 0; i < gpi()->cur_row_count[n]; i++) // отчистка всех действий у бокса /// если не влом потом добавь удалялку из мамы для чистки памяти
						{
							gpi()->intedex_data[n][i] = data_obj{}; // обнулябися инфа
						}
						gpi()->cur_row_count[n] = NULL; //обнуляется количество ячеек )
						gpi()->cur_box_count--;
						update_inf();
						break;
					}
				}

			}
		}

	});


	for (int n = 0; n < 3; n++)// для добавления и удаления кнопок проход по всем боксам (n - ноды BOX с рядами действий) // ПП все настроено на смещения бокса мапе, т.е Cur_box_smeh вроде робит
	{
		id_button_pam[n][0]->addClickEventListener([=](Ref*)// ПЛЮС ОБЪЕКТ БЛОКА
		{
			if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 3)
			{
				gpi()->cur_row_count[n + gpi()->cur_box_smeh]++;
				update_inf();
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{

					if (gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] == false)
					{
						gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] = true;
						gpi()->cur_row_count[n + gpi()->cur_box_smeh]++;
						update_inf();
						break;
					}
				}
			}

		});
		id_button_pam[n][1]->addClickEventListener([=](Ref*)// МИНУС ОБЪЕКТ БЛОКА
		{
			if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 4)
			{
				gpi()->cur_row_count[n + gpi()->cur_box_smeh]--; //уменьшаем текущее количество ячеек
				update_inf();
			}
			else
			{
				for (int i = 3; i > -1; i--)
				{
					if (gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] == true)
					{
						gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] = false; //видимость ячейки
						gpi()->intedex_data[n + gpi()->cur_box_smeh][i + gpi()->cur_row_smeh[n + gpi()->cur_box_smeh]] = data_obj{}; //обнуляем инфу
						if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 0) //на всякий тупая проверка
							gpi()->cur_row_count[n + gpi()->cur_box_smeh]--; //уменьшаем колво ячеек
						creator_obj = nullptr; //текущий объект - неизвестен
						update_inf(); //аптейтим
						break;
					}
				}
			}
		});
		for (int i = 0; i < 4; i++)
		{
			id_button[n][i]->addClickEventListener([=](Ref*)// ОБЪЕКЬЫ БЛОКОВ
			{
				creator_obj = data_obj_id_button[id_button[n][i]]; //тупой выбор кнопки по закрепленной инфе
				update_inf(); //сброс 
				update_ind2();//фулл сброс
			});
		}
	}

	type_obj_choise[0]->addClickEventListener([=](Ref*)
	{
		if (creator_obj->my_type != type_struct::scene)
		{
			creator_obj->my_inter = unknown;
			creator_obj->my_type = type_struct::scene;
			update_inf();
		}
	});

	type_obj_choise[1]->addClickEventListener([=](Ref*)
	{
		if (creator_obj->my_type != type_struct::sprite)
		{
			creator_obj->my_inter = unknown;
			creator_obj->my_type = type_struct::sprite;
			update_inf();
		}
	});

	type_obj_choise[2]->addClickEventListener([=](Ref*)
	{
		if (creator_obj->my_type != type_struct::text)
		{
			creator_obj->my_inter = unknown;
			creator_obj->my_type = type_struct::text;
			update_inf();
		}
	});

	intr_obj_choise[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_inter = swich;
		update_inf();
	});

	intr_obj_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_inter = action;
		update_inf();
	});

	intr_text_choise[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_inter = action;
		update_inf();
	});

	intr_text_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_inter = swich;
		update_inf();
	});

	////////////////////////////////////////////////////////
	//SWICH SCENE
	swich_scene_choise[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->data1 = "BG";
		update_inf();
	});

	swich_scene_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->data1 = "CG";
		update_inf();
	});


	swich_scene_choise[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->data2 = swich_scene_resource->getString();
		swich_scene_resource->setString("");
		update_inf();
	});

	swich_scene_choise[3]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_swich = SIMPLE;
		update_inf();
	});

	swich_scene_choise[4]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_swich = POLOS;
		update_inf();
	});

	////////////////////////////////////////////////////////
	//ACTION SCENE
	action_scene_choise[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = SHAKE;
		update_inf();
	});

	action_scene_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = PUNCH;
		update_inf();
	});
	////////////////////////////////////////////////////////
	//SWICH SPRITE
	swich_sprite_choise_chater[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = sprite_sruct::AY;
		update_inf();
	});

	swich_sprite_choise_chater[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = sprite_sruct::KI;
		update_inf();
	});

	swich_sprite_choise_chater[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = sprite_sruct::DA;
		update_inf();
	});

	swich_sprite_resource_save->addClickEventListener([=](Ref*)
	{
		creator_obj->data1 = swich_sprite_resource_texture_type->getString();
		creator_obj->data2 = swich_sprite_resource_texture_num->getString();
		creator_obj->data3 = swich_sprite_resource_emotion->getString();
		swich_sprite_resource_texture_type->setString("");
		swich_sprite_resource_texture_num->setString("");
		swich_sprite_resource_emotion->setString("");
		update_inf();
	});

	swich_sprite_choise_type[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_swich = SIMPLE;
		update_inf();
	});

	swich_sprite_choise_type[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_swich = RTL;
		update_inf();
	});

	swich_sprite_choise_type[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_swich = LTR;
		update_inf();
	});

	swich_sprite_choise_position[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_position = sprite_sruct::centr;
		update_inf();
	});

	swich_sprite_choise_position[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_position = sprite_sruct::left;
		update_inf();
	});

	swich_sprite_choise_position[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_position = sprite_sruct::left_centr;
		update_inf();
	});

	swich_sprite_choise_position[3]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_position = sprite_sruct::right;
		update_inf();
	});

	swich_sprite_choise_position[4]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_position = sprite_sruct::right_centr;
		update_inf();
	});

	swich_sprite_hide->addClickEventListener([=](Ref*)
	{
		if (swich_sprite_hide->getSelectedState() == false)
		{
			creator_obj->hide = true;
		}
		else
		{
			creator_obj->hide = false;
		}
		update_inf();
	});

	//ACTION SPRITE
	action_sprite_choise[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = MINIJUMP;
	});

	action_sprite_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = JUMP;
	});

	action_sprite_choise[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = scale_lit;
	});

	action_sprite_choise[3]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = scale_mid;
	});

	action_sprite_choise[4]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = scale_big;
	});
	
	//ACTION TEXT
	action_text_choise[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = SHOW_BOX;
	});


	action_text_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = HIDE_BOX;
	});

	auto sign = ([=](int &x, int &y){ 
		return data_obj_id_button[id_button[x][y]];
	});


	play_page->addClickEventListener([=](Ref*)// сохранялка страницы текущей по cur_page
	{
		if (all_pages[cur_page] != nullptr)
		{
			Game_Mode->stopAllActions();
			Scene1->stopAllActions();
			Scene2->stopAllActions();
			Sprite1->stopAllActions();
			Sprite2->stopAllActions();
			Sprite3->stopAllActions();
			Sprite4->stopAllActions();
			Sprite5->stopAllActions();
			Sprite6->stopAllActions();
			delete all_pages[cur_page];
		}
		vector<Object_Scene*> objs;
		vector<type_struct::type_object> objs_type;
		vector <type_interactions> intrs;
		vector<type_swich> swichs;
		vector<type_action> actions;
		text_box* text{};

		Label_text->setString("");
		Label_name->setString("");
		for (int n = 0; n < 3; n++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (sign(n, i)->my_type != type_struct::none)
				{
					switch (sign(n, i)->my_type)
					{
					case type_struct::scene:
					{
								  switch (sign(n, i)->my_inter)
								  {
								  case swich:
								  {
												if (sign(n, i)->data1 == "BG")
												{
													objs.push_back(new Object_Scene("BG" + sign(n, i)->data2));
												}
												else if (sign(n, i)->data1 == "CG")
												{
													objs.push_back(new Object_Scene(string_to_int(sign(n, i)->data2)));
												}

												objs_type.push_back(sign(n, i)->my_type);
												intrs.push_back(sign(n, i)->my_inter);
												swichs.push_back(sign(n, i)->my_swich);
												break;
								  }
								  case action:
								  {
												 objs.push_back(new Object_Scene());
												 objs_type.push_back(sign(n, i)->my_type);
												 intrs.push_back(sign(n, i)->my_inter);
												 actions.push_back(sign(n, i)->my_action);
												 break;
								  }
								  default:
								  {
											 break;
								  }
								  }
								  break;
					}
					case type_struct::sprite:
					{
								   switch (sign(n, i)->my_inter)
								   {
								   case swich:
								   {
												 if (sign(n, i)->hide == true)
												 {
													 auto sprite = new Object_Sprtite(sign(n, i)->my_name);
													 objs.push_back(sprite);
													 objs_type.push_back(sign(n, i)->my_type);
													 intrs.push_back(sign(n, i)->my_inter);
													 swichs.push_back(sign(n, i)->my_swich);
												 }
												 else
												 {
													 auto sprite = new Object_Sprtite( 
														 sign(n, i)->my_name, sign(n, i)->data1,
														 string_to_int(sign(n, i)->data2), string_to_int(sign(n, i)->data3));
													 sprite->Set_pos(sign(n, i)->my_position);
													 objs.push_back(sprite);
													 objs_type.push_back(sign(n, i)->my_type);
													 intrs.push_back(sign(n, i)->my_inter);
													 swichs.push_back(sign(n, i)->my_swich);
												 }
												 break;
								   }
								   case action:
								   {
												  auto sprite = new Object_Sprtite(
													  sign(n, i)->my_name, "empty",
													  0, 0);
												  objs.push_back(sprite);
												  objs_type.push_back(sign(n, i)->my_type);
												  intrs.push_back(sign(n, i)->my_inter);
												  actions.push_back(sign(n, i)->my_action);
												  break;
								   }  
								   default:
								   {
											  break;
								   }

								   }
					}
					case type_struct::text:
					{

											  switch (sign(n, i)->my_inter)
											  {
											  case swich:
											  {
															auto data = new Object_Text("name", "text");
															objs.push_back(data);
															objs_type.push_back(sign(n, i)->my_type);
															intrs.push_back(sign(n, i)->my_inter);
															swichs.push_back(sign(n, i)->my_swich);
															break;
											  }
											  case action:
											  {
															 auto data = new Object_Text();
															 objs.push_back(data);
															 objs_type.push_back(sign(n, i)->my_type);
															 intrs.push_back(sign(n, i)->my_inter);
															 actions.push_back(sign(n, i)->my_action);
															 break;
											  }
											  default:
												  break;
											  }
					}
					default:
					{
							   break;
					}
					}
				}
			}
			if (objs.size() != 0)
			{
				objs.back()->Set_wait(true);
			}
		}



		if (objs.size() != 0)
		{
			all_pages[cur_page] = new Page(objs, objs_type, intrs, swichs, actions, text);
			//all_pages[cur_page]->draw();
		}
	});


	update_inf();
	
}