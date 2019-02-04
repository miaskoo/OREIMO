/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "Main_Menu.h" // подключает головной файл 
#include "SampleLive2DSprite.h" // подключает класс LIVE2D
#include "cocostudio/CocoStudio.h" // Подключает библиотеку cocos

#include <ui/CocosGUI.h> // Использует label string
#include <chrono> // для работы со временем
#include <thread> // для работы с потоками 
#include <vector> // для работы с вектором
#include <fstream> // библиотека работы с файлом

#include "Game_Menu.h" // головной файл игрового процесса
#include "AudioEngine.h"// Подключает библиотеку использования аудио для кокоса

#include <string>

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;
using namespace std::chrono;





void search_dir(char *need, char *need_end, int size_need, vector<string> &out, const char *filename);
void background_smooth(bool on);
void GetSub(vector<string> *SubText, vector<int> *time, int *z, char *file); // преобразует субтитры из str в вектора
void needbeex(bool *x, int *po);
int Get_numcg(int num, char *CG_NUM);
void COM(cocos2d::ui::Text* Subtitle, char *subfile);
void wikiset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, vector<string> dir);
void albumset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, vector<string> setcomment, vector<string> setsub, vector<string> setCG);
void confset(Node *Setting_Menu, Layer *Button_Menu, Node *Back_Node);
void musset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node);
void mapset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, Game *way);
void Hide_Menu(Node *Game_Mode);
void Show_Menu(Node *Game_Mode);

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

void confget()
{
	char temp[1];
	ifstream file("..\\Resources\\Profile\\config.bin", ios::binary);
	if (file)
	{
		for (int x = 0; x < 16; x++)
		{
			file.read(temp, 1);
			switch (x)
			{
			case 0:
				if (temp[0] == 0x00)
					Skip_All = false;
				else
					Skip_All = true;
				break;
			case 1:
				if (temp[0] == 0x00)
					ORE_old = false;
				else
					ORE_old = true;
				break;
			case 2:
				if (temp[0] == 0x00)
					Com_twoshot = false;
				else
					Com_twoshot = true;
				break;
			case 3:
				if (temp[0] == 0x00)
					Tips_twoshot = false;
				else
					Tips_twoshot = true;
				break;
			case 4:
				if (temp[0] == 0x00)
					Text_old = false;
				else
					Text_old = true;
				break;
			case 5:
				if (temp[0] == 0x00)
					Autosave1 = false;
				else
					Autosave1 = true;
				break;
			case 6:
				if (temp[0] == 0x00)
					Autosave2 = false;
				else
					Autosave2 = true;
				break;
			case 7:
				if (temp[0] == 0x00)
					Musalb = false;
				else
					Musalb = true;
				break;
			case 8:
				All_Volume = float(temp[0])/100;
				break;
			case 9:
				Background_Volume = float(temp[0]) / 100;
				break;
			case 10:
				System_Volume = float(temp[0]) / 100;
				break;
			case 11:
				Game_Volume = float(temp[0]) / 100;
				break;
			case 12:
				Voice_Volume = float(temp[0]) / 100;
				break;
			case 13:
				Speed_Skip_Text = int(temp[0]);
				break;
			case 14:
				Speed_Text = int(temp[0]);
				break;
			case 15:
				Speed_Auto_Text = int(temp[0]);
				break;
			}
		}
	}
	else
	{
		ofstream newsetting("..\\Resources\\Profile\\config.bin", ios::binary);
		char standart[] = { 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01 , 0x32, 0x64, 0x64, 0x64, 0x64, 0x32, 0x32, 0x32}; // первые восемь - буловы значения, потом пять байтов громкостей, потом еще 3 скорости текста от 0 до 100 (0x00, 0x64)
		newsetting.write(standart, 16);
		newsetting.close();
		confget();
	}
	
}

void confset(Node *Setting_Menu, Layer *Button_Menu, Node *Back_Node, bool Background, bool hide_back_node)
{

	//Объявление кнопок Setting_Menu меню
	auto *System_Menu_Set = static_cast<cocos2d::ui::Button*>(Setting_Menu->getChildByName("System_Menu_Set"));
	auto *Text_Menu_Set = static_cast<cocos2d::ui::Button*>(Setting_Menu->getChildByName("Text_Menu_Set"));
	auto *Sound_Menu_Set = static_cast<cocos2d::ui::Button*>(Setting_Menu->getChildByName("Sound_Menu_Set"));
	auto Save_Setting = static_cast<ui::Button*>(Setting_Menu->getChildByTag(3614));


	auto *Back = static_cast<cocos2d::ui::Button*>(Back_Node->getChildByName("Back"));
	auto *White_Screen = Setting_Menu->getChildByTag(442); // Белый фон
	auto *Top_Line = Back_Node->getChildByName("Top_Line");
	auto Name_Layer = static_cast<ui::Text*>(Back_Node->getChildByName("Name_Layer")); /* имя слоев */
	auto *Back_Line = Back_Node->getChildByName("Back_Line");

	if (Background == true)
	{
		White_Screen->setVisible(true);
	}
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================

	//Объявление слоев настроек Setting_Menu
	auto *System_Menu = Setting_Menu->getChildByName("System_Menu");
	auto *Text_Menu = Setting_Menu->getChildByName("Text_Menu");
	auto *Sound_Menu = Setting_Menu->getChildByName("Sound_Menu");

	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//Sure слой
	auto Sure = Setting_Menu->getChildByTag(3334);
	auto Text_sure = static_cast<ui::Text*> (Sure->getChildByTag(3336));
	auto Sure_Yes = static_cast<ui::Button*>(Sure->getChildByTag(3338));
	auto Sure_No = static_cast<ui::Button*>(Sure->getChildByTag(3339));

	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	Setting_Menu->setVisible(true);
	Button_Menu->setVisible(false);
	Back_Node->setVisible(true);
	System_Menu_Set->setEnabled(false); ////////////////////////////////////////////////////////////////////////// ПРИ ПЕРЕХОДЕ В КАЖДОЕ МЕНЮ ВЫКЛЮЧАТЬ ВСЕ КНОПКИ
	Text_Menu_Set->setEnabled(true);
	Sound_Menu_Set->setEnabled(true);
	Text_Menu->setVisible(false);
	Sound_Menu->setVisible(false);
	System_Menu->setVisible(true);





	Node *temp_node;

	/// System menu
	auto *Skip_All_on = static_cast<ui::Button*>(System_Menu->getChildByName("Skip_All_on"));
	auto *Skip_All_off = static_cast<ui::Button*>(System_Menu->getChildByName("Skip_All_off"));
	auto *ORE_old_on = static_cast<ui::Button*>(System_Menu->getChildByName("ORE_old_on"));
	auto *ORE_old_off = static_cast<ui::Button*>(System_Menu->getChildByName("ORE_old_off"));
	auto *Com_twoshot_on = static_cast<ui::Button*>(System_Menu->getChildByName("Com_twoshot_on"));
	auto *Com_twoshot_off = static_cast<ui::Button*>(System_Menu->getChildByName("Com_twoshot_off"));
	auto *Tips_twoshot_on = static_cast<ui::Button*>(System_Menu->getChildByName("Tips_twoshot_on"));
	auto *Tips_twoshot_off = static_cast<ui::Button*>(System_Menu->getChildByName("Tips_twoshot_off"));
	auto *Text_old_on = static_cast<ui::Button*>(System_Menu->getChildByName("Text_old_on"));
	auto *Text_old_off = static_cast<ui::Button*>(System_Menu->getChildByName("Text_old_off"));
	auto *Autosave1_on = static_cast<ui::Button*>(System_Menu->getChildByName("Autosave1_on"));
	auto *Autosave1_off = static_cast<ui::Button*>(System_Menu->getChildByName("Autosave1_off"));
	auto *Autosave2_on = static_cast<ui::Button*>(System_Menu->getChildByName("Autosave2_on"));
	auto *Autosave2_off = static_cast<ui::Button*>(System_Menu->getChildByName("Autosave2_off"));
	auto *Musalb_on = static_cast<ui::Button*>(System_Menu->getChildByName("Musalb_on"));
	auto *Musalb_off = static_cast<ui::Button*>(System_Menu->getChildByName("Musalb_off"));

	temp_node = System_Menu->getChildByTag(640);
	auto *Speed_SkipMode_Text = static_cast<ui::Slider*>(temp_node->getChildByTag(182));
	auto *Speed_SkipMode_Text_plus = static_cast<ui::Button*>(temp_node->getChildByTag(1730));
	auto *Speed_SkipMode_Text_min = static_cast<ui::Button*>(temp_node->getChildByTag(1729));

	// Sound Menu
	temp_node = Sound_Menu->getChildByTag(2245);
	temp_node = temp_node->getChildByTag(640);

	auto *Set_All_Volume = static_cast<ui::Slider*>(temp_node->getChildByTag(182));
	auto *Set_All_Volume_plus = static_cast<ui::Button*>(temp_node->getChildByTag(1730));
	auto *Set_All_Volume_min = static_cast<ui::Button*>(temp_node->getChildByTag(1729));
	auto *Set_All_Volume_text = static_cast<ui::Text*>(Sound_Menu->getChildByTag(222));


	auto *Set_Background_Volume = static_cast<ui::Slider*>(temp_node->getChildByTag(1755));
	auto *Set_Background_Volume_plus = static_cast<ui::Button*>(temp_node->getChildByTag(1752));
	auto *Set_Background_Volume_min = static_cast<ui::Button*>(temp_node->getChildByTag(1751));
	auto *Set_Background_Volume_text = static_cast<ui::Text*>(Sound_Menu->getChildByTag(223));


	auto *Set_Game_Volume = static_cast<ui::Slider*>(temp_node->getChildByTag(1762));
	auto *Set_Game_Volume_plus = static_cast<ui::Button*>(temp_node->getChildByTag(1759));
	auto *Set_Game_Volume_min = static_cast<ui::Button*>(temp_node->getChildByTag(1758));
	auto *Set_Game_Volume_text = static_cast<ui::Text*>(Sound_Menu->getChildByTag(224));

	auto *Set_System_Volume = static_cast<ui::Slider*>(temp_node->getChildByTag(1213));
	auto *Set_System_Volume_plus = static_cast<ui::Button*>(temp_node->getChildByTag(1210));
	auto *Set_System_Volume_min = static_cast<ui::Button*>(temp_node->getChildByTag(1209));
	auto *Set_System_Volume_text = static_cast<ui::Text*>(Sound_Menu->getChildByTag(225));

	auto *Set_Voice_Volume = static_cast<ui::Slider*>(temp_node->getChildByTag(1220));
	auto *Set_Voice_Volume_plus = static_cast<ui::Button*>(temp_node->getChildByTag(1217));
	auto *Set_Voice_Volume_min = static_cast<ui::Button*>(temp_node->getChildByTag(1216));
	auto *Set_Voice_Volume_text = static_cast<ui::Text*>(Sound_Menu->getChildByTag(226));

	//Text Menu
	temp_node = Text_Menu->getChildByTag(640);

	auto *Set_Text = static_cast<ui::Slider*>(temp_node->getChildByTag(182));
	auto *Set_Text_plus = static_cast<ui::Button*>(temp_node->getChildByTag(1730));
	auto *Set_Text_min = static_cast<ui::Button*>(temp_node->getChildByTag(1729));

	auto *Set_Auto_Text = static_cast<ui::Slider*>(temp_node->getChildByTag(1755));
	auto *Set_Auto_Text_plus = static_cast<ui::Button*>(temp_node->getChildByTag(1752));
	auto *Set_Auto_Text_min = static_cast<ui::Button*>(temp_node->getChildByTag(1751));

	auto int_to_string([](int in)->string
	{
		stringstream ss;
		string temp;
		ss << in;
		ss >> temp;
		return (temp);
	});



	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//Кнопки Setting Menu
	if (System_Menu_Set)
	{
		System_Menu_Set->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			System_Menu_Set->setEnabled(false); ////////////////////////////////////////////////////////////////////////// ПРИ ПЕРЕХОДЕ В КАЖДОЕ МЕНЮ ВЫКЛЮЧАТЬ ВСЕ КНОПКИ
			Text_Menu_Set->setEnabled(true);
			Sound_Menu_Set->setEnabled(true);
			Text_Menu->setVisible(false);
			Sound_Menu->setVisible(false);
			System_Menu->setVisible(true);
		});
	}
	if (Text_Menu_Set)
	{
		Text_Menu_Set->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			Text_Menu_Set->setEnabled(false); ////////////////////////////////////////////////////////////////////////// ПРИ ПЕРЕХОДЕ В КАЖДОЕ МЕНЮ ВЫКЛЮЧАТЬ ВСЕ КНОПКИ
			Sound_Menu_Set->setEnabled(true);
			System_Menu_Set->setEnabled(true);
			System_Menu->setVisible(false);
			Sound_Menu->setVisible(false);
			Text_Menu->setVisible(true);
		});
	}
	if (Sound_Menu_Set)
	{
		Sound_Menu_Set->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			Sound_Menu_Set->setEnabled(false); ////////////////////////////////////////////////////////////////////////// ПРИ ПЕРЕХОДЕ В КАЖДОЕ МЕНЮ ВЫКЛЮЧАТЬ ВСЕ КНОПКИ
			Text_Menu_Set->setEnabled(true);
			System_Menu_Set->setEnabled(true);
			System_Menu->setVisible(false);
			Text_Menu->setVisible(false);
			Sound_Menu->setVisible(true);
		});
	}



	auto visget([=](bool &Skip_All, bool &ORE_old, bool &Com_twoshot, bool &Tips_twoshot, bool &Text_old, bool &Autosave1, bool &Autosave2, bool &Musalb)
	{
		Sprite* temp_vis;

		if (Skip_All == true)
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis1"));
			temp_vis->setVisible(true);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis2"));
			temp_vis->setVisible(false);
			Skip_All_on->setVisible(false);
			Skip_All_off->setVisible(true);
		}
		else
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis1"));
			temp_vis->setVisible(false);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis2"));
			temp_vis->setVisible(true);
			Skip_All_on->setVisible(true);
			Skip_All_off->setVisible(false);
		}

		if (ORE_old == true)
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis3"));
			temp_vis->setVisible(true);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis4"));
			temp_vis->setVisible(false);
			ORE_old_on->setVisible(false);
			ORE_old_off->setVisible(true);
		}
		else
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis3"));
			temp_vis->setVisible(false);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis4"));
			temp_vis->setVisible(true);
			ORE_old_on->setVisible(true);
			ORE_old_off->setVisible(false);
		}
		if (Com_twoshot == true)
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis5"));
			temp_vis->setVisible(true);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis6"));
			temp_vis->setVisible(false);
			Com_twoshot_on->setVisible(false);
			Com_twoshot_off->setVisible(true);
		}
		else
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis5"));
			temp_vis->setVisible(false);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis6"));
			temp_vis->setVisible(true);
			Com_twoshot_on->setVisible(true);
			Com_twoshot_off->setVisible(false);
		}
		if (Tips_twoshot == true)
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis7"));
			temp_vis->setVisible(true);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis8"));
			temp_vis->setVisible(false);
			Tips_twoshot_on->setVisible(false);
			Tips_twoshot_off->setVisible(true);
		}
		else
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis7"));
			temp_vis->setVisible(false);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis8"));
			temp_vis->setVisible(true);
			Tips_twoshot_on->setVisible(true);
			Tips_twoshot_off->setVisible(false);
		}
		if (Text_old == true)
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis9"));
			temp_vis->setVisible(true);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis10"));
			temp_vis->setVisible(false);
			Text_old_on->setVisible(false);
			Text_old_off->setVisible(true);
		}
		else
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis9"));
			temp_vis->setVisible(false);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis10"));
			temp_vis->setVisible(true);
			Text_old_on->setVisible(true);
			Text_old_off->setVisible(false);
		}
		if (Autosave1 == true)
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis11"));
			temp_vis->setVisible(true);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis12"));
			temp_vis->setVisible(false);
			Autosave1_on->setVisible(false);
			Autosave1_off->setVisible(true);
		}
		else
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis11"));
			temp_vis->setVisible(false);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis12"));
			temp_vis->setVisible(true);
			Autosave1_on->setVisible(true);
			Autosave1_off->setVisible(false);
		}
		if (Autosave2 == true)
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis13"));
			temp_vis->setVisible(true);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis14"));
			temp_vis->setVisible(false);
			Autosave2_on->setVisible(false);
			Autosave2_off->setVisible(true);
		}
		else
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis13"));
			temp_vis->setVisible(false);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis14"));
			temp_vis->setVisible(true);
			Autosave2_on->setVisible(true);
			Autosave2_off->setVisible(false);
		}
		if (Musalb == true)
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis15"));
			temp_vis->setVisible(true);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis16"));
			temp_vis->setVisible(false);
			Musalb_on->setVisible(false);
			Musalb_off->setVisible(true);
		}
		else
		{
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis15"));
			temp_vis->setVisible(false);
			temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis16"));
			temp_vis->setVisible(true);
			Musalb_on->setVisible(true);
			Musalb_off->setVisible(false);
		}
		Set_All_Volume->setPercent(All_Volume * 100);
		Set_Background_Volume->setPercent(Background_Volume * 100);
		Set_Game_Volume->setPercent(Game_Volume * 100);
		Set_System_Volume->setPercent(System_Volume * 100);
		Set_Voice_Volume->setPercent(Voice_Volume * 100);

		Set_All_Volume_text->setString(int_to_string(Set_All_Volume->getPercent()));
		Set_Background_Volume_text->setString(int_to_string(Set_Background_Volume->getPercent()));
		Set_Game_Volume_text->setString(int_to_string(Set_Game_Volume->getPercent()));
		Set_System_Volume_text->setString(int_to_string(Set_System_Volume->getPercent()));
		Set_Voice_Volume_text->setString(int_to_string(Set_Voice_Volume->getPercent()));

	});

	visget(Skip_All, ORE_old, Com_twoshot, Tips_twoshot, Text_old, Autosave1, Autosave2, Musalb);


	temp_sw = false;


	//Логика вся в кучу
	Skip_All_on->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Skip_All = true;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis1"));
		temp_vis->setVisible(true);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis2"));
		temp_vis->setVisible(false);
		Skip_All_on->setVisible(false);
		Skip_All_off->setVisible(true);
		temp_sw = true;
	});

	Skip_All_off->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Skip_All = false;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis1"));
		temp_vis->setVisible(false);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis2"));
		temp_vis->setVisible(true);
		Skip_All_on->setVisible(true);
		Skip_All_off->setVisible(false);
		temp_sw = true;
	});

	ORE_old_on->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		ORE_old = true;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis3"));
		temp_vis->setVisible(true);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis4"));
		temp_vis->setVisible(false);
		ORE_old_on->setVisible(false);
		ORE_old_off->setVisible(true);
		temp_sw = true;
	});

	ORE_old_off->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		ORE_old = false;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis3"));
		temp_vis->setVisible(false);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis4"));
		temp_vis->setVisible(true);
		ORE_old_on->setVisible(true);
		ORE_old_off->setVisible(false);
		temp_sw = true;
	});

	Com_twoshot_on->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Com_twoshot = true;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis5"));
		temp_vis->setVisible(true);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis6"));
		temp_vis->setVisible(false);
		Com_twoshot_on->setVisible(false);
		Com_twoshot_off->setVisible(true);
		temp_sw = true;
	});

	Com_twoshot_off->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Com_twoshot = false;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis5"));
		temp_vis->setVisible(false);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis6"));
		temp_vis->setVisible(true);
		Com_twoshot_on->setVisible(true);
		Com_twoshot_off->setVisible(false);
		temp_sw = true;
	});

	Tips_twoshot_on->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Tips_twoshot = true;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis7"));
		temp_vis->setVisible(true);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis8"));
		temp_vis->setVisible(false);
		Tips_twoshot_on->setVisible(false);
		Tips_twoshot_off->setVisible(true);
		temp_sw = true;
	});

	Tips_twoshot_off->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Tips_twoshot = false;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis7"));
		temp_vis->setVisible(false);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis8"));
		temp_vis->setVisible(true);
		Tips_twoshot_on->setVisible(true);
		Tips_twoshot_off->setVisible(false);
		temp_sw = true;
	});

	Text_old_on->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Text_old = true;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis9"));
		temp_vis->setVisible(true);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis10"));
		temp_vis->setVisible(false);
		Text_old_on->setVisible(false);
		Text_old_off->setVisible(true);
		temp_sw = true;
	});

	Text_old_off->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Text_old = false;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis9"));
		temp_vis->setVisible(false);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis10"));
		temp_vis->setVisible(true);
		Text_old_on->setVisible(true);
		Text_old_off->setVisible(false);
		temp_sw = true;
	});

	Autosave1_on->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Autosave1 = true;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis11"));
		temp_vis->setVisible(true);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis12"));
		temp_vis->setVisible(false);
		Autosave1_on->setVisible(false);
		Autosave1_off->setVisible(true);
		temp_sw = true;
	});

	Autosave1_off->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Autosave1 = false;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis11"));
		temp_vis->setVisible(false);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis12"));
		temp_vis->setVisible(true);
		Autosave1_on->setVisible(true);
		Autosave1_off->setVisible(false);
		temp_sw = true;
	});

	Autosave2_on->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Autosave2 = true;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis13"));
		temp_vis->setVisible(true);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis14"));
		temp_vis->setVisible(false);
		Autosave2_on->setVisible(false);
		Autosave2_off->setVisible(true);
		temp_sw = true;
	});

	Autosave2_off->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Autosave2 = false;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis13"));
		temp_vis->setVisible(false);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis14"));
		temp_vis->setVisible(true);
		Autosave2_on->setVisible(true);
		Autosave2_off->setVisible(false);
		temp_sw = true;
	});

	Musalb_on->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Musalb = true;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis15"));
		temp_vis->setVisible(true);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis16"));
		temp_vis->setVisible(false);
		Musalb_on->setVisible(false);
		Musalb_off->setVisible(true);
		temp_sw = true;
	});

	Musalb_off->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Musalb = false;
		Sprite* temp_vis;
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis15"));
		temp_vis->setVisible(false);
		temp_vis = static_cast<Sprite*>(System_Menu->getChildByName("vis16"));
		temp_vis->setVisible(true);
		Musalb_on->setVisible(true);
		Musalb_off->setVisible(false);
		temp_sw = true;
	});

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Set_All_Volume->addEventListener([=](Ref * sender, ui::Slider::EventType type)
	{
		auto slider = dynamic_cast<ui::Slider*>(sender);
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			All_Volume = float(Set_All_Volume->getPercent()) / 100;
			Set_All_Volume_text->setString(int_to_string(Set_All_Volume->getPercent()));
			cocos2d::experimental::AudioEngine::setVolume(Background_id, All_Volume*Background_Volume);
			temp_sw = true;
		}
	});

	Set_All_Volume_plus->addClickEventListener([=](Ref *)
	{
		if (Set_All_Volume->getPercent() > 99)
			return;
		Set_All_Volume->setPercent(Set_All_Volume->getPercent() + 1);
		Set_All_Volume_text->setString(int_to_string(Set_All_Volume->getPercent()));
		All_Volume = float(Set_All_Volume->getPercent()) / 100;
		cocos2d::experimental::AudioEngine::setVolume(Background_id, All_Volume*Background_Volume);
		temp_sw = true;
	});

	Set_All_Volume_min->addClickEventListener([=](Ref *)
	{
		if (Set_All_Volume->getPercent() < 1)
			return;
		Set_All_Volume->setPercent(Set_All_Volume->getPercent() - 1);
		Set_All_Volume_text->setString(int_to_string(Set_All_Volume->getPercent()));
		All_Volume = float(Set_All_Volume->getPercent()) / 100;
		cocos2d::experimental::AudioEngine::setVolume(Background_id, All_Volume*Background_Volume);
		temp_sw = true;
	});
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Set_Background_Volume->addEventListener([=](Ref * sender, ui::Slider::EventType type)
	{
		auto slider = dynamic_cast<ui::Slider*>(sender);
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			Background_Volume = float(Set_Background_Volume->getPercent()) / 100;
			Set_Background_Volume_text->setString(int_to_string(Set_Background_Volume->getPercent()));
			cocos2d::experimental::AudioEngine::setVolume(Background_id, All_Volume*Background_Volume);
			temp_sw = true;
		}
	});

	Set_Background_Volume_plus->addClickEventListener([=](Ref *)
	{
		if (Set_Background_Volume->getPercent() > 99)
			return;
		Set_Background_Volume->setPercent(Set_Background_Volume->getPercent() + 1);
		Set_Background_Volume_text->setString(int_to_string(Set_Background_Volume->getPercent()));
		Background_Volume = float(Set_Background_Volume->getPercent()) / 100;
		cocos2d::experimental::AudioEngine::setVolume(Background_id, All_Volume*Background_Volume);
		temp_sw = true;
	});

	Set_Background_Volume_min->addClickEventListener([=](Ref *)
	{
		if (Set_Background_Volume->getPercent() < 1)
			return;
		Set_Background_Volume->setPercent(Set_Background_Volume->getPercent() - 1);
		Set_Background_Volume_text->setString(int_to_string(Set_Background_Volume->getPercent()));
		Background_Volume = float(Set_Background_Volume->getPercent()) / 100;
		cocos2d::experimental::AudioEngine::setVolume(Background_id, All_Volume*Background_Volume);
		temp_sw = true;
	});
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Set_Game_Volume->addEventListener([=](Ref * sender, ui::Slider::EventType type)
	{
		auto slider = dynamic_cast<ui::Slider*>(sender);
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			Game_Volume = float(Set_Game_Volume->getPercent()) / 100;
			Set_Game_Volume_text->setString(int_to_string(Set_Game_Volume->getPercent()));
			temp_sw = true;
		}
	});

	Set_Game_Volume_plus->addClickEventListener([=](Ref *)
	{
		if (Set_Game_Volume->getPercent() > 99)
			return;
		Set_Game_Volume->setPercent(Set_Game_Volume->getPercent() + 1);
		Set_Game_Volume_text->setString(int_to_string(Set_Game_Volume->getPercent()));
		Game_Volume = float(Set_Game_Volume->getPercent()) / 100;
		temp_sw = true;
	});

	Set_Game_Volume_min->addClickEventListener([=](Ref *)
	{
		if (Set_Game_Volume->getPercent() < 1)
			return;
		Set_Game_Volume->setPercent(Set_Game_Volume->getPercent() - 1);
		Set_Game_Volume_text->setString(int_to_string(Set_Game_Volume->getPercent()));
		Game_Volume = float(Set_Game_Volume->getPercent()) / 100;
		temp_sw = true;
	});
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Set_System_Volume->addEventListener([=](Ref * sender, ui::Slider::EventType type)
	{
		auto slider = dynamic_cast<ui::Slider*>(sender);
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			System_Volume = float(Set_System_Volume->getPercent()) / 100;
			Set_System_Volume_text->setString(int_to_string(Set_System_Volume->getPercent()));
			temp_sw = true;
		}
	});


	Set_System_Volume_plus->addClickEventListener([=](Ref *)
	{
		if (Set_System_Volume->getPercent() > 99)
			return;
		Set_System_Volume->setPercent(Set_System_Volume->getPercent() + 1);
		Set_System_Volume_text->setString(int_to_string(Set_System_Volume->getPercent()));
		System_Volume = float(Set_System_Volume->getPercent()) / 100;
		temp_sw = true;
	});

	Set_System_Volume_min->addClickEventListener([=](Ref *)
	{
		if (Set_System_Volume->getPercent() < 1)
			return;
		Set_System_Volume->setPercent(Set_System_Volume->getPercent() - 1);
		Set_System_Volume_text->setString(int_to_string(Set_System_Volume->getPercent()));
		System_Volume = float(Set_System_Volume->getPercent()) / 100;
		temp_sw = true;
	});

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Set_Voice_Volume->addEventListener([=](Ref * sender, ui::Slider::EventType type)
	{
		auto slider = dynamic_cast<ui::Slider*>(sender);
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			Voice_Volume = float(Set_Voice_Volume->getPercent()) / 100;
			Set_Voice_Volume_text->setString(int_to_string(Set_Voice_Volume->getPercent()));
			temp_sw = true;
		}
	});

	Set_Voice_Volume_plus->addClickEventListener([=](Ref *)
	{
		if (Set_Voice_Volume->getPercent() > 99)
			return;
		Set_Voice_Volume->setPercent(Set_Voice_Volume->getPercent() + 1);
		Set_Voice_Volume_text->setString(int_to_string(Set_Voice_Volume->getPercent()));
		Voice_Volume = float(Set_Voice_Volume->getPercent()) / 100;
		temp_sw = true;
	});

	Set_Voice_Volume_min->addClickEventListener([=](Ref *)
	{
		if (Set_Voice_Volume->getPercent() < 1)
			return;
		Set_Voice_Volume->setPercent(Set_Voice_Volume->getPercent() - 1);
		Set_Voice_Volume_text->setString(int_to_string(Set_Voice_Volume->getPercent()));
		Voice_Volume = float(Set_Voice_Volume->getPercent()) / 100;
		temp_sw = true;
	});

	auto save_all([=]()
	{
		char zero[] = { 0x00 };
		char one[] = { 0x01 };
		ofstream file("..\\Resources\\Profile\\config.bin", ios::binary);
		if (Skip_All == true)
			file.write(one, 1);
		else
			file.write(zero, 1);
		if (ORE_old == true)
			file.write(one, 1);
		else
			file.write(zero, 1);
		if (Com_twoshot == true)
			file.write(one, 1);
		else
			file.write(zero, 1);
		if (Tips_twoshot == true)
			file.write(one, 1);
		else
			file.write(zero, 1);
		if (Text_old == true)
			file.write(one, 1);
		else
			file.write(zero, 1);
		if (Autosave1 == true)
			file.write(one, 1);
		else
			file.write(zero, 1);
		if (Autosave2 == true)
			file.write(one, 1);
		else
			file.write(zero, 1);
		if (Musalb == true)
			file.write(one, 1);
		else
			file.write(zero, 1);
		char temp[1];
		temp[0] = 0x00 + int(All_Volume * 100);
		file.write(temp, 1);

		temp[0] = 0x00 + int(Background_Volume * 100);
		file.write(temp, 1);

		temp[0] = 0x00 + int(System_Volume * 100);
		file.write(temp, 1);

		temp[0] = 0x00 + int(Game_Volume * 100);
		file.write(temp, 1);

		temp[0] = 0x00 + int(Voice_Volume * 100);
		file.write(temp, 1);

		temp[0] = 0x00 + Speed_Skip_Text;
		file.write(temp, 1);

		temp[0] = 0x00 + Speed_Text;
		file.write(temp, 1);

		temp[0] = 0x00 + Speed_Auto_Text;
		file.write(temp, 1);


		file.close();
	});

	Save_Setting->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Sure->setVisible(true);
		Text_sure->setString("РЎРѕС…СЂР°РЅРёС‚СЊ РґР°РЅРЅС‹Рµ РЅР°СЃС‚СЂРѕР№РєРё Рё РІС‹Р№С‚Рё?"); // Сохранить данные настройки и выйти?
		Sure_Yes->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			save_all();
			Sure->setVisible(false);
			Setting_Menu->setVisible(false);
			if (Background == true)
			{
				White_Screen->setVisible(false);
			}
			
			Back_Line->setVisible(true);
			Button_Menu->setVisible(true);
			if (hide_back_node == true)
			{
				Top_Line->setVisible(false);
				Name_Layer->setVisible(false);
				Back_Node->setVisible(false);
			}
			else
			{
				Name_Layer->setString("РњРµРЅСЋ");// меню
				Back->addClickEventListener([=](Ref *)
				{
					System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
					Back_Node->setVisible(false);
					Button_Menu->setVisible(false);
				});
			}
		});
		Sure_No->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
			Sure->setVisible(false);
		});
	});
	Back->addClickEventListener([=](Ref *)
	{
		if (temp_sw == true)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			Sure->setVisible(true);
			Text_sure->setString("РЎРѕС…СЂР°РЅРёС‚СЊ РґР°РЅРЅС‹Рµ РЅР°СЃС‚СЂРѕР№РєРё РїРµСЂРµРґ РІС‹С…РѕРґРѕРј?"); // Сохранить данные настройки перед выходом?
			Sure_Yes->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
				save_all();
				Sure->setVisible(false);
				Setting_Menu->setVisible(false);
				if (Background == true)
				{
					White_Screen->setVisible(false);
				}
				
				Back_Line->setVisible(true);
				Button_Menu->setVisible(true);
				if (hide_back_node == true)
				{
					Top_Line->setVisible(false);
					Name_Layer->setVisible(false);
					Back_Node->setVisible(false);
				}
				else
				{
					Name_Layer->setString("РњРµРЅСЋ");// меню
					Back->addClickEventListener([=](Ref *)
					{
						System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
						Back_Node->setVisible(false);
						Button_Menu->setVisible(false);
					});
				}
			});
			Sure_No->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
				confget();
				cocos2d::experimental::AudioEngine::setVolume(Background_id, All_Volume*Background_Volume);
				Sure->setVisible(false);
				Setting_Menu->setVisible(false);
				if (Background == true)
				{
					White_Screen->setVisible(false);
				}
				Back_Line->setVisible(true);				
				Button_Menu->setVisible(true);
				if (hide_back_node == true)
				{
					Top_Line->setVisible(false);
					Name_Layer->setVisible(false);
					Back_Node->setVisible(false);
				}
				else
				{
					Name_Layer->setString("РњРµРЅСЋ");// меню
					Back->addClickEventListener([=](Ref *)
					{
						System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
						Back_Node->setVisible(false);
						Button_Menu->setVisible(false);
					});
				}
			});
		}
		else
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
			Setting_Menu->setVisible(false);
			if (Background == true)
			{
				White_Screen->setVisible(false);
			}
			Back_Line->setVisible(true);			
			Button_Menu->setVisible(true);
			if (hide_back_node == true)
			{
				Top_Line->setVisible(false);
				Name_Layer->setVisible(false);
				Back_Node->setVisible(false);
			}
			else
			{
				Name_Layer->setString("РњРµРЅСЋ");// меню
				Back->addClickEventListener([=](Ref *)
				{
					System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
					Back_Node->setVisible(false);
					Button_Menu->setVisible(false);
				});
			}
		}
	});

}




void Game::gameset()
{
	
	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	this->removeAllComponents();
	auto Game_Mode = CSLoader::createNode("All_Scene_cocos\\Game_Scene\\Game_Menu.csb"); //Объявление и определение головного файла игрового процесса
	this->addChild(Game_Mode, 0);


	

	auto *Text_Box = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Text_Box"));
	auto *Button_click = static_cast<cocos2d::ui::Button*>(Game_Mode->getChildByName("Button_click"));  //прозрачный элемент кнопки для прокрутки скрипта
	auto *Game_Menu = static_cast<Layer*>(Game_Mode->getChildByTag(2773));

	//Buttons
	auto *Game_Menu_Button = static_cast<ui::Button*>(Game_Mode->getChildByTag(1834));
	auto *Auto_Mode_Button = static_cast<ui::Button*>(Game_Mode->getChildByTag(1835));
	auto Auto_Mode_Sprite = static_cast<Sprite*>(Game_Mode->getChildByTag(259));
	auto Skip_Mode_Button = static_cast<Sprite*>(Game_Mode->getChildByTag(1836));

	///Game_Menu///
	// Back //
	auto *Back_Node = (Game_Mode->getChildByTag(15177));
	auto *Back_Line = Back_Node->getChildByName("Back_Line");
	auto *Top_Line = Back_Node->getChildByName("Top_Line");
	auto Name_Layer = static_cast<ui::Text*>(Back_Node->getChildByName("Name_Layer")); /* имя слоев */ Name_Layer->enableShadow(ccc4(0, 0, 0, 255)); //включить тень имен слоев
	auto *Back = static_cast<cocos2d::ui::Button*>(Back_Node->getChildByName("Back"));
	// Button Node // 
	auto *Button_Node = static_cast<Layer*>(Game_Menu->getChildByTag(2993));
	auto *Setting_menu_Button = static_cast<ui::Button*>(Button_Node->getChildByTag(947));
	auto *Main_menu_Button = static_cast<ui::Button*>(Button_Node->getChildByTag(948));
	// Game_Menu_Layer //
	auto *Setting_menu = (Game_Mode->getChildByTag(16439));
	//Text_Box
	auto Show_Menu_Button = static_cast<ui::Button*>(Text_Box->getChildByTag(7022));
	auto Show_Menu_Sprite = static_cast<Sprite*>(Text_Box->getChildByTag(11188));

	Game_Menu_Button->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		cocos2d::experimental::AudioEngine::stop(Voice_id);
		Back_Node->setVisible(true);
		Button_click->setVisible(false);
		Game_Menu->setVisible(true);
		Name_Layer->setString("РњРµРЅСЋ");// меню
		Back->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
			Back_Node->setVisible(false);
			Game_Menu->setVisible(false);
		});
	});

	Setting_menu_Button->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Back_Line->setVisible(false);
		Name_Layer->setString("РќР°СЃС‚СЂРѕР№РєРё"); // Настройки
		confset(Setting_menu, Game_Menu, Back_Node, false, false);
	});

	Main_menu_Button->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		cocos2d::experimental::AudioEngine::stop(Background_id);
		GAME.Clear_Data();
		loadsetmain();
	});

	Auto_Mode_Button->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]
		{
			Auto_Mode_Sprite->setTexture("Buttons\\Game\\avto_on.png");
		});
		GAME.set_Auto_Mode(Game_Mode, true);
		thread setup(use_Auto_Mode, Game_Mode);
		setup.detach();
	});






	Show_Menu_Button->addClickEventListener([=](Ref *)
	{
		Show_Menu(Game_Mode);
	});

	Show_text_box(Text_Box);//Вызывает в начале сцены текст бокс на страндартную позицию
	GAME.Get_Script(Game_Mode); //Запускает прогруженный скрипт

}



void Game::mainset()
{
	
	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	this->removeAllComponents();
	//Объявление и определение головного файла главного меню
	auto rootNode = CSLoader::createNode("All_Scene_cocos\\Main_Menu.csb");
	this->addChild(rootNode, 0);

	//Объявление и определение Live2D объекта
	auto pLive2DSprite = SampleLive2DSprite::createDrawNode();
	rootNode->addChild(pLive2DSprite, 0);


	//Все бэкграундные звуки
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("systemse\\SE200.wav"); // Звук принять
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("systemse\\SE202.wav"); // Звук выделения
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("systemse\\SE203.wav"); // Звук назад
	
	//Вся бэкграундная музыка
	Background_id = cocos2d::experimental::AudioEngine::play2d("Music\\00000000.mp3", true, All_Volume*Background_Volume);
	

	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//=========================================================================ОБЪЯВЛЯЮТСЯ ВСЕ КНОПКИ=================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================


	//Объявление и определение слоев главного меню для правильного отоброжения слоев по значимости setLocalZOrder
	auto *Logo = static_cast<Layer*>(rootNode->getChildByName("Logo"));
	Logo->setLocalZOrder(1);

	auto *Button_Menu = static_cast<Layer*>(rootNode->getChildByName("Button_Menu"));
	Button_Menu->setLocalZOrder(1);

	auto *Black_line = static_cast<Layer*>(rootNode->getChildByName("Black_line"));
	Black_line->setLocalZOrder(1);

	auto *Bonus_Menu = rootNode->getChildByName("Bonus_Menu");
	Bonus_Menu->setLocalZOrder(2);

	auto *Setting_Menu = rootNode->getChildByName("Setting_Menu");
	Setting_Menu->setLocalZOrder(2);

	auto *Back_Node = rootNode->getChildByName("Back_Node");
	Back_Node->setLocalZOrder(2);

	auto *Back_Line = Back_Node->getChildByName("Back_Line");
	auto *Top_Line = Back_Node->getChildByName("Top_Line");
	auto Name_Layer = static_cast<ui::Text*>(Back_Node->getChildByName("Name_Layer")); /* имя слоев */ Name_Layer->enableShadow(ccc4(0, 0, 0, 255)); //включить тень имен слоев
	auto *Back = static_cast<cocos2d::ui::Button*>(Back_Node->getChildByName("Back"));
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================

	//Объявление кнопок главного меню
	auto *Bonus = static_cast<cocos2d::ui::Button*>(Button_Menu->getChildByName("Bonus"));
	auto *New_Game = static_cast<cocos2d::ui::Button*>(Button_Menu->getChildByName("New_Game"));
	auto *Continue = static_cast<cocos2d::ui::Button*>(Button_Menu->getChildByName("Continue"));
	auto *Config = static_cast<cocos2d::ui::Button*>(Button_Menu->getChildByName("Config"));

	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================

	//Объявление кнопок бонус меню
	auto *Alb = static_cast<cocos2d::ui::Button*>(Bonus_Menu->getChildByName("Alb"));
	auto *Mus = static_cast<cocos2d::ui::Button*>(Bonus_Menu->getChildByName("Mus"));
	auto *Map = static_cast<cocos2d::ui::Button*>(Bonus_Menu->getChildByName("Map"));
	auto *Wiki = static_cast<cocos2d::ui::Button*>(Bonus_Menu->getChildByName("Wiki"));

	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================

	//Объявление слоев Bonus_Menu
	auto *Album_menu = Bonus_Menu->getChildByName("Album_menu");
	auto *Music_Menu = Bonus_Menu->getChildByName("Music_menu");
	auto *Wiki_Menu = Bonus_Menu->getChildByName("Wiki_menu");
	auto *Map_Menu = Bonus_Menu->getChildByName("Map_menu");
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================



	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//=========================================================================ОПРЕДЕЛЯЕТСЯ ВСЯ ЛОГИКА================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================

	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//Кнопки главного меню

	if (Bonus)
	{
		Bonus->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			Bonus_Menu->setVisible(true);
			Button_Menu->setVisible(false);
			Back_Node->setVisible(true);
			Back->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
				Bonus_Menu->setVisible(false);
				Button_Menu->setVisible(true);
				Back_Node->setVisible(false);
			});
		});

	}

	if (New_Game)
	{

		New_Game->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			loadsetgame(0);
		});
	}

	if (Continue)
	{
		Continue->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		});
	}

	if (Config)
	{
		Config->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			Top_Line->setVisible(true);//и выводить фон и название слоя
			Back_Line->setVisible(false);
			Name_Layer->setVisible(true); Name_Layer->setString("РќР°СЃС‚СЂРѕР№РєРё"); // Настройки
			confset(Setting_Menu, Button_Menu, Back_Node, true, true);		
		});

	}

	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//================================================================================================================================================================================
	//Кнопки Bonus Menu
	

		Alb->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			Album_menu->setVisible(true); ////////////////////////////////////////////////////////////////////////// ПРИ ПЕРЕХОДЕ В КАЖДОЕ МЕНЮ ВЫКЛЮЧАТЬ ВСЕ КНОПКИ
			Mus->setTouchEnabled(false);
			Alb->setTouchEnabled(false);
			Map->setTouchEnabled(false);
			Wiki->setTouchEnabled(false);
			Top_Line->setVisible(true);//и выводить фон и название слоя
			Name_Layer->setVisible(true); Name_Layer->setString("РђР»СЊР±РѕРј"); // Альбом
			albumset(Bonus_Menu, Button_Menu, Back_Node, setcomment, setsub, setCG);
		});

	


		Mus->addClickEventListener([=](Ref *)
		{
			thread setup(background_smooth, false);
			setup.detach();
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);			
			Music_Menu->setVisible(true);
			Mus->setTouchEnabled(false);
			Alb->setTouchEnabled(false);
			Map->setTouchEnabled(false);
			Wiki->setTouchEnabled(false);
			Top_Line->setVisible(true);//и выводить фон и название слоя
			Name_Layer->setVisible(true); Name_Layer->setString("РњСѓР·С‹РєР°"); // Музыка
			musset(Bonus_Menu, Button_Menu, Back_Node);

		});

	
		Map->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			Map_Menu->setVisible(true);
			Mus->setTouchEnabled(false);
			Alb->setTouchEnabled(false);
			Map->setTouchEnabled(false);
			Wiki->setTouchEnabled(false);
			Top_Line->setVisible(true);//и выводить фон и название слоя
			Name_Layer->setVisible(true); Name_Layer->setString("Map"); // O.R.E. Лист
			mapset(Bonus_Menu, Button_Menu, Back_Node, this);
		});
		Wiki->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
			Wiki_Menu->setVisible(true);
			Mus->setTouchEnabled(false);
			Alb->setTouchEnabled(false);
			Map->setTouchEnabled(false);
			Wiki->setTouchEnabled(false);
			Top_Line->setVisible(true);//и выводить фон и название слоя
			Name_Layer->setVisible(true); Name_Layer->setString("O.R.E. Р›РёСЃС‚"); // O.R.E. Лист
			wikiset(Bonus_Menu, Button_Menu, Back_Node, setore);
		});

	




}

void configurategame(bool *task, int newgame)
{
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	*task = true;
	char zoto4[] = "[BETASCRIPTS]";
	char zoto4_end[] = "[/BETASCRIPTS]";
	search_dir(zoto4, zoto4_end, sizeof(zoto4), setscripts, "..\\Resources\\game.txt");

	char zoto5[] = "[SPRITES]";
	char zoto5_end[] = "[/SPRITES]";
	search_dir(zoto5, zoto5_end, sizeof(zoto5), setsprites, "..\\Resources\\game.txt");

	char zoto6[] = "[SCENE]";
	char zoto6_end[] = "[/SCENE]";
	search_dir(zoto6, zoto6_end, sizeof(zoto6), setscene, "..\\Resources\\game.txt");


	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//delete[] CG_NUM; // при создании объекта игрового процесса память выделенная для CG_NUM возвращается

	GAME.Set_Script(setscripts, setsprites, setscene, setmusic, newgame);
	//num = 0;
	*task = false;
}

void configuratemain()
{
	char zoto1[] = "[CG]";
	char zoto1_end[] = "[/CG]";
	search_dir(zoto1, zoto1_end, sizeof(zoto1), setCG, "..\\Resources\\dir.txt");


	char zoto2[] = "[COMMENTS]";
	char zoto2_end[] = "[/COMMENTS]";
	search_dir(zoto2, zoto2_end, sizeof(zoto2), setcomment, "..\\Resources\\dir.txt");


	char zoto3[] = "[BETASUB]";
	char zoto3_end[] = "[/BETASUB]";
	search_dir(zoto3, zoto3_end, sizeof(zoto3), setsub, "..\\Resources\\dir.txt");

	char zoto4[] = "[MUSIC]";
	char zoto4_end[] = "[/MUSIC]";
	search_dir(zoto4, zoto4_end, sizeof(zoto4), setmusic, "..\\Resources\\dir.txt");

	char zoto5[] = "[SYSTEMSE]";
	char zoto5_end[] = "[/SYSTEMSE]";
	search_dir(zoto5, zoto5_end, sizeof(zoto5), setsystemse, "..\\Resources\\dir.txt");

	char zoto8[] = "[ORE]";
	char zoto8_end[] = "[/ORE]";
	search_dir(zoto8, zoto8_end, sizeof(zoto8), setore, "..\\Resources\\dir.txt");

	confget(); // взятие настроек из файла по переменным
}

void Game::loadsetmain()
{
	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	this->removeAllComponents();
	auto rootNode = CSLoader::createNode("All_Scene_cocos\\Loading.csb");
	this->addChild(rootNode, 1);
	auto Star = static_cast<Sprite*>(rootNode->getChildByTag(1027));
	auto AllTime = CSLoader::createTimeline("All_Scene_cocos\\Loading.csb");
	AllTime->setTimeSpeed(1.0f);
	AllTime->gotoFrameAndPlay(0);
	Star->runAction(AllTime);

	configuratemain();
	auto swichscene = CallFunc::create(this, callfunc_selector(Game::mainset));
	auto delay_for_scene = Sequence::create( DelayTime::create(1.0), swichscene, NULL);
	this->runAction(delay_for_scene);
	
}

void Game::loadsetgame(int current_script)
{
	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	this->removeAllComponents();
	cocos2d::experimental::AudioEngine::stop(Background_id);
	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	auto rootNode = CSLoader::createNode("All_Scene_cocos\\Loading.csb");
	this->addChild(rootNode, 1);
	auto Star = static_cast<Sprite*>(rootNode->getChildByTag(1027));
	auto AllTime = CSLoader::createTimeline("All_Scene_cocos\\Loading.csb");
	AllTime->setTimeSpeed(1.0f);
	AllTime->gotoFrameAndPlay(0);
	Star->runAction(AllTime); // запускает звезву
	auto obj = this;
	bool *temp = &(this->task);

	thread setup(configurategame, temp, current_script); // паралельно поток прогрузки данных
	setup.detach();
	//
	//auto swichscene = CallFunc::create(this, callfunc_selector(Game::gameset));
	//this->runAction(Sequence::create(DelayTime::create(2.0f), swichscene, NULL));
	auto chekload([=]()
	{
		while (true)
		{
			if (*temp == false) // ждет загрузку и грузит сцену
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
					//auto swichscene = CallFunc::create(this, callfunc_selector(Game::gameset));
					//this->runAction(Sequence::create(DelayTime::create(0.0), swichscene, NULL));
					obj->gameset();
				});
				break;
			}
			else
			{
				Sleep(1000); // ждет секунду и выполняет новую проверку
				continue;
			}
	}
	});
	thread wait_setup(chekload);
	wait_setup.detach();

	
	

}

// on "init" you need to initialize your instance

bool Game::init()
{
	
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Head_Menu = this;
	loadsetmain();


	
	return true;
}

void mapset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, Game *way)
{
	auto *Map_Menu = Bonus_menu->getChildByName("Map_menu");
	auto *Map_Button = Map_Menu->getChildByTag(20025);
	auto AKYO_0000A = static_cast<ui::Button*>(Map_Button->getChildByName("AKYO_0000A"));
	auto AKYO_0010A = static_cast<ui::Button*>(Map_Button->getChildByName("AKYO_0010A"));

	AKYO_0000A->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		way->loadsetgame(0);
	});

	AKYO_0010A->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		way->loadsetgame(2);
	});

}
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------╔══╗╔══╗─╔╗╔╗╔══╗╔══╗-----------------------------------------------------------
//----------------------------------------------------------------║╔╗║║╔╗║─║║║║║╔═╝║╔═╝-----------------------------------------------------------
//----------------------------------------------------------------║╚╝║║╚╝╚╗║╚╝║║╚═╗║╚═╗-----------------------------------------------------------
//----------------------------------------------------------------║╔╗║║╔═╗║╚═╗║╚═╗║╚═╗║-----------------------------------------------------------
//----------------------------------------------------------------║║║║║╚═╝║─╔╝║╔═╝║╔═╝║-----------------------------------------------------------
//----------------------------------------------------------------╚╝╚╝╚═══╝─╚═╝╚══╝╚══╝-----------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------




void search_dir(char *need, char *need_end, int size_need, vector<string> &out, const char *filename) // берет дирректории из фала дирректорий dir.txt но в релизе исправь дирректорию
{
	out.clear();
	ifstream file;
	char *buff;
	buff = new char[size_need]; //буфер байтов файла - нужен для поиска коробки с дирректориями
	string tempdir; // просто временная дерриктория для копирования строк из файла в вектор
	int relese = 0; // считает совпадения байт
	file.open(filename, ios::binary);
	for (int i = 0; !file.eof(); i++)
	{
		file.seekg(i, ios::beg);
		file.read(buff, 1);

		if (need[0] == buff[0])
		{
			file.seekg(i, ios::beg);
			file.read(buff, size_need);
			for (int y = 0; y < size_need; y++)
			{
				if (need[relese] == buff[y])
				{
					relese++;
					if (relese == (size_need - 1))
					{
						break;
					}
				}
				else
				{
					relese = 0;
					break;
				}
			}
		}
		if (relese > 0)
		{
			file.seekg(i + size_need + 1, ios::beg);
			break;
		}
	}

	while (getline(file, tempdir))
	{
		if (tempdir.substr(0, tempdir.size() - 1) == string(need_end))
			break;
		tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ
		out.push_back(tempdir);
	}



	delete[] buff;
	//delete[] x;
}

void background_smooth(bool on)
{
	int n = 50;
	if (on == false)
	{
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.9);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.8);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.7);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.6);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.5);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.4);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.3);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.2);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.1);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.0);
		Sleep(n);
		cocos2d::experimental::AudioEngine::stop(Background_id);
	}
	else
	{
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.1);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.2);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.3);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.4);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.5);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.6);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.7);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.8);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*0.9);
		Sleep(n);
		cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*1.0);
		Sleep(n);
	}
}

void GetSub(vector<string> *SubText, vector<int> *time, int *z, char *file) // преобразует субтитры из str в вектора
{
	string buff; // строковой буфер
	vector<string> buffvec; // строковой буфер в векторе

	int min = NULL; //минуты
	int sec = NULL; //секунды
	int msec = NULL; //милисекунды

	ifstream SubFile;

	SubFile.open(file);
	while (getline(SubFile, buff))
		buffvec.push_back(buff);
	*z = NULL;
	while (*z < buffvec.size())
	{

		buff = buffvec[*z + 1];

		for (int n = 0; n < buff.length(); n++) // цикл для подсчета милисекунд начала и конца, и добавление их значений в вектор
		{
			if ((n > 2 && n < 5) || (n > 19 && n < 22))
			{
				if (n == 3 || n == 20)
				{
					min = (static_cast<int>(buff[n] - 0x30)) * 10;
				}
				if (n == 4 || n == 21)
				{
					min = min + (static_cast<int>(buff[n] - 0x30));
				}
			}
			if ((n > 5 && n < 8) || (n > 22 && n < 25))
			{
				if (n == 6 || n == 23)
				{
					sec = (static_cast<int>(buff[n] - 0x30)) * 10;
				}
				if (n == 7 || n == 24)
				{
					sec = sec + (static_cast<int>(buff[n] - 0x30));
				}
			}
			if ((n > 8 && n < 12) || (n > 25 && n < 29))
			{
				if (n == 9 || n == 26)
				{
					msec = (static_cast<int>(buff[n] - 0x30)) * 100;
				}
				if (n == 10 || n == 27)
				{
					msec = msec + ((static_cast<int>(buff[n] - 0x30)) * 10);
				}
				if (n == 11 || n == 28)
				{
					msec = msec + (static_cast<int>(buff[n] - 0x30));
				}
			}
			if ((n == 11) || (n == 28))
			{
				if (n == 11)
				{
					(*(time)).push_back(((min * 60 * 1000) + (sec * 1000) + (msec)));
					min = 0;
					sec = 0;
					msec = 0;

				}
				if (n == 28)
				{
					(*(time)).push_back(((min * 60 * 1000) + (sec * 1000) + (msec)));
					min = 0;
					sec = 0;
					msec = 0;
				}
			}
		}
		buff = buffvec[*z + 2]; // кидает в вектор текст субтитров
		if (buff.length() > 30) // создает пропуск строки если она большая
		{
			for (int z = 60; z < buff.length(); z++)
			{
				if (buff[z] == 0x20)
				{
					buff[z] = '\n';
					break;
				}
			}
		}
		//(*(SubText)).push_back(buffvec[*z + 2]);
		(*(SubText)).push_back(buff);
		*z = *z + 4;
	}
}

void needbeex(bool *x, int *po) // выполняет перелачу аргумента для закрытия старого потока при увелечинии потоков
{
	*x = false;
	while (true)
	{
		if ((*(po)) > 1)
		{
			(*(po))--;
			*x = true;
			break;
		}
		if ((*(po)) == 0)
		{
			*x = true;
			break;
		}
	}
}

int Get_numcg(int num, char *CG_NUM)
{
	int temp_z = 0;
	for (int n = 0, z = 0; n < num; n++)
	{
		if (CG_NUM[n] == '1')
			z++;
		if (CG_NUM[n] == '2')
			z = z + 2;
		if (CG_NUM[n] == '3')
			z = z + 3;
		if (CG_NUM[n] == '4')
			z = z + 4;
		if (CG_NUM[n] == '5')
			z = z + 5;
		temp_z = z;
	}
	return temp_z;
}

void COM(cocos2d::ui::Text* Subtitle, char *subfile) // выводит субтитры из векторов на экран 
{
	nump++;
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([Subtitle]{
		Subtitle->setString("");
	});
	auto start = steady_clock::now();
	auto end = steady_clock::now();
	vector<string> Text;
	vector<int> Time;
	int z;
	GetSub(&Text, &Time, &z, subfile);
	int n = NULL;
	int t = NULL;
	auto bufftime = milliseconds(0);
	bool exon; //переменная завершающая функцию
	std::thread needex(needbeex, &exon, &nump);
	needex.detach();
	while (n< z / 4)
	{
		int i = Time[t];
		string buff = Text[n];
		string name;
		for (int o = 0; o < 16; o++) // влом заниматься байтофичей из за кодировок
		{
			if (exon != false)
			{
				return;
			}
			name += buff[o];
			if (o > 6)
			{
				if (name == "РђСЏСЃСЌ") //Аясэ
					break;
				if (o > 8)
				{
					if (name == "РЎР°РѕСЂРё") // саори
						break;

					if (o > 10)
					{
						if (name == "РљС‘СЃСѓРєСЌ") // кёсукэ
							break;
						if (name == "РљРёСЂРёРЅРѕ") // кирино
							break;
						if (name == "РњР°РЅР°РјРё") // манами
							break;
						if (name == "РљР°РЅР°РєРѕ") // канако
							break;
						if (name == "РљСѓСЂРѕРЅСЌРєРѕ") // куронэко
							break;
					}
				}
			}
		}
		auto y = time_point_cast<milliseconds>(start)+(milliseconds(Time[t])) - bufftime;
		while (true)
		{
			if (exon != false)
			{
				return;
			}
			end = steady_clock::now();
			auto x = time_point_cast<milliseconds>(end);
			if (x > y)
			{
				if (exon != false)
				{
					return;
				}
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([Subtitle, buff, exon, name]{
					if (exon == false)
					{
						Subtitle->enableShadow(ccc4(0, 0, 0, 255));
						Subtitle->enableGlow(ccc4(255, 255, 255, 255));
						if (name == "РђСЏСЃСЌ") //Аясэ
							Subtitle->setColor(ccc3(25, 201, 250));
						if (name == "РЎР°РѕСЂРё") // саори
							Subtitle->setColor(ccc3(65, 130, 250));
						if (name == "РљС‘СЃСѓРєСЌ") // кёсукэ
							Subtitle->setColor(ccc3(255, 255, 255));
						if (name == "РљРёСЂРёРЅРѕ") // кирино
							Subtitle->setColor(ccc3(255, 201, 107));
						if (name == "РњР°РЅР°РјРё") // манами
							Subtitle->setColor(ccc3(255, 255, 255)); //Нет цвета
						if (name == "РљР°РЅР°РєРѕ") //Канако
							Subtitle->setColor(ccc3(255, 255, 255)); //Нет цвета
						if (name == "РљСѓСЂРѕРЅСЌРєРѕ") //куронэко
							Subtitle->setColor(ccc3(183, 123, 227));

						Subtitle->setTextHorizontalAlignment(TextHAlignment::CENTER);
						Subtitle->setTextVerticalAlignment(TextVAlignment::CENTER);
						Subtitle->setString(buff);
						//Subtitle->enableShadow(ccc4(0, 0, 0, 0));
					}
					else
					{
						return;
					}
				});
				std::this_thread::sleep_for(milliseconds(Time[t + 1]) - (milliseconds(Time[t])));
				if (exon != false)
				{
					return;
				}
				break;
				bufftime = milliseconds(Time[t + 1]);
				break;
			}
		}
		n++;
		t = t + 2;
	}
	if (exon != false)
	{
		return;
	}
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([Subtitle]{
		Subtitle->setString("");
	});
	nump--;
}

void wikiset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, vector<string> dir)
{
	auto *Alb = static_cast<cocos2d::ui::Button*>(Bonus_menu->getChildByName("Alb"));
	auto *Mus = static_cast<cocos2d::ui::Button*>(Bonus_menu->getChildByName("Mus"));
	auto *Wiki = static_cast<cocos2d::ui::Button*>(Bonus_menu->getChildByName("Wiki"));

	auto *Back = static_cast<cocos2d::ui::Button*>(Back_Node->getChildByName("Back"));
	auto Name_Layer = static_cast<ui::Text*>(Back_Node->getChildByName("Name_Layer")); /* имя слоев */
	auto *Top_Line = Back_Node->getChildByName("Top_Line");

	//================================================================================================================================================================================
	//=========================================================================Wiki===================================================================================================
	//================================================================================================================================================================================
	auto *Wiki_Menu = Bonus_menu->getChildByName("Wiki_menu");
	//auto *Wiki_to_Bonus_Menu = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Wiki_to_Bonus_Menu"));
	auto *Button1 = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Button1"));
	auto *Button2 = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Button2"));
	auto *Button3 = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Button3"));
	auto *Button4 = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Button4"));
	auto *Button5 = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Button5"));
	auto *Button6 = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Button6"));
	auto *Button7 = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Button7"));
	auto *Button8 = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Button8"));
	auto *Button9 = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Button9"));
	auto *Up_ch = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Up"));
	auto *Down_ch = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("Down"));
	auto *Set_head = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByName("Set_head"));
	auto *Set_body = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByName("Set_body"));


	auto *Text1 = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByTag(1846));
	auto *Text2 = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByTag(1847));
	auto *Text3 = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByTag(1848));
	auto *Text4 = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByTag(1849));
	auto *Text5 = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByTag(1850));
	auto *Text6 = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByTag(1851));
	auto *Text7 = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByTag(1852));
	auto *Text8 = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByTag(1853));
	auto *Text9 = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByTag(1854));

	auto *Current_page = static_cast<cocos2d::ui::Text*>(Wiki_Menu->getChildByName("Current_page"));
	auto *Sg_page = static_cast<cocos2d::Sprite*>(Wiki_Menu->getChildByName("Sg_page"));
	auto *Set_Sprite = static_cast<cocos2d::Sprite*>(Wiki_Menu->getChildByName("Set_Sprite"));
	auto *next = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("next"));
	auto *prev = static_cast<cocos2d::ui::Button*>(Wiki_Menu->getChildByName("prev"));

	int biteend = 0;
	char page[45452]; // поскольку статичный - удалится сам в конце функции
	ifstream temp;
	temp.open("..\\Resources\\Wiki.txt", ios::binary);
	temp.read(page, 45452);
	temp.close();
	vector<string> all_head; // хранит все заголовки
	vector<string> all_body; // хранит все страницы
	vector<int> num_pages; //указывает сколько в данной главе страниц
	cocos2d::ui::Button* Box_Button[] = { Button1, Button2, Button3, Button4, Button5, Button6, Button7, Button8, Button9 };

	for (int l = 0; l < 64; l++) // сохраняет всю информацию вики в переменные 
	{
		unsigned int leght_head; // определение размера загаловка
		char *head; //  захват заголовока
		unsigned int amount_page; // определение количества страниц 
		unsigned int leght_page1; // определение размера текста страницы 1 
		char *body1; //захват текста страницы 1
		unsigned int leght_page2; //	определение размера текста страницы 2
		char *body2; //захват текста страницы 2
		unsigned int leght_page3; //	определение размера текста страницы 3
		char *body3; //захват текста страницы 3

		char bracbeg = { 0x5b }; // Скобка [
		char bracend = { 0x5d }; // Скобка ]

		int n = 0;// временная переменная для начала строки
		int z = 0; // временная переменная для конца строки

		// далее иницилизировать все значения в ноль
		leght_head = 0;
		amount_page = 0;
		leght_page1 = 0;
		leght_page2 = 0;
		leght_page3 = 0;
		n = n + biteend;

		for (n; true; n++) // цикл для определения количества символов в head
		{
			if (page[n] == bracbeg)
			{
				for (n++, z = n; true; z++)
				{
					if (page[z] == bracend)
					{
						leght_head = (z - n);
						break;
					}
				}
			}
			if (leght_head > 0)
			{
				break;
			}
		}
		head = new char[leght_head + 1];

		for (int i = 0; i < leght_head; i++) // цикл для добавления побайтно загаловка страницы в head
		{
			head[i] = page[n]; //добавление побайтно загаловок в динамический массив head;
			n++;
			if (i + 1 == leght_head)
				head[i + 1] = '\0';
		}

		for (n; true; n++) // цикл для получения количества страниц
		{
			if (page[n] == bracbeg)
			{
				for (n++, z = n; true; z++)
				{
					amount_page = page[z] - 48;
					break;
				}

				if (amount_page > 3 || amount_page < 1)
				{
					//cout << "Error, amount page can't be >3 or <1, please try again." << endl;
					exit(0);
				}
			}
			if (amount_page > 0)
			{
				break;
			}
		}
		for (n; true; n++) // цикл для определения количества символов в body1
		{
			if (page[n] == bracbeg)
			{
				for (n++, z = n; true; z++)
				{
					if (page[z] == bracend)
					{
						leght_page1 = (z - n);
						break;
					}
				}
			}
			if (leght_page1 > 0)
			{
				break;
			}
		}

		body1 = new char[leght_page1 + 1];

		for (int i = 0; i < leght_page1; i++) // цикл для добавления побайтно загаловка страницы в body1
		{
			body1[i] = page[n]; //добавление побайтно загаловок в динамический массив body1;
			n++;
			if (i + 1 == leght_page1)
				body1[i + 1] = '\0';
		}
		if (amount_page == 1)
		{
			biteend = n++;
		}

		if (amount_page == 2 || amount_page == 3)
		{
			for (n; true; n++) // цикл для определения количества символов в body2
			{
				if (page[n] == bracbeg)
				{
					for (n++, z = n; true; z++)
					{
						if (page[z] == bracend)
						{
							leght_page2 = (z - n);
							break;
						}
					}
				}
				if (leght_page2 > 0)
				{
					break;
				}
			}

			body2 = new char[leght_page2 + 1];

			for (int i = 0; i < leght_page2; i++) // цикл для добавления побайтно загаловка страницы в body2
			{
				body2[i] = page[n]; //добавление побайтно загаловок в динамический массив body2;
				n++;
				if (i + 1 == leght_page2)
					body2[i + 1] = '\0';
			}
			if (amount_page == 2)
			{
				biteend = n++;
			}
			if (amount_page == 3)
			{
				for (n; true; n++) // цикл для определения количества символов в body3
				{
					if (page[n] == bracbeg)
					{
						for (n++, z = n; true; z++)
						{
							if (page[z] == bracend)
							{
								leght_page3 = (z - n);
								break;
							}
						}
					}
					if (leght_page3 > 0)
					{
						break;
					}
				}

				body3 = new char[leght_page3 + 1];

				for (int i = 0; i < leght_page3; i++) // цикл для добавления побайтно загаловка страницы в head
				{
					body3[i] = page[n]; //добавление побайтно загаловок в динамический массив head;
					n++;
					if (i + 1 == leght_page3)
						body3[i + 1] = '\0';
				}

				if (amount_page == 3)
					biteend = n++;

			}
		}
		// освобождение выделенной памяти и запись значений в вектора
		all_head.push_back(head);
		delete[] head;
		if (amount_page == 1 || amount_page == 2 || amount_page == 3)
		{
			all_body.push_back(body1);
			delete[] body1;
			if (amount_page == 2 || amount_page == 3)
			{
				all_body.push_back(body2);
				delete[] body2;
				if (amount_page == 3)
				{
					all_body.push_back(body3);
					delete[] body3;
				}
			}
		}
		num_pages.push_back(amount_page);
	}


	for (int l = 0; l < all_body.size(); l++)
	{
		string temp_text = all_body[l];
		int n;
		for (int l_k = 0; l_k < temp_text.length(); l_k++)
		{
			n = 0;
			if (l_k == 60 && temp_text.length()>80)//l_k % 60 == 0
			{
				while (true)
				{
					n++;
					l_k++;
					if (l_k + 1 == temp_text.length())
						break;
					if (temp_text[l_k] == 0x20)
					{
						temp_text[l_k] = '\n';
						break;
					}
					if (n == 20)
					{
						n = 0;
						l_k = l_k - 20;
						while (true)
						{
							n++;
							l_k--;
							if (temp_text[l_k] == 0x20)
							{
								temp_text[l_k] = '\n';
								l_k = 61;
								break;
							}
							if (n == 15)
							{
								l_k = 61;
								break;
							}
						}
						break;
					}
				}

			}
			if (l_k == 120 && temp_text.length()>140)//l_k % 60 == 0
			{
				while (true)
				{
					n++;
					l_k++;
					if (l_k + 1 == temp_text.length())
						break;
					if (temp_text[l_k] == 0x20)
					{
						temp_text[l_k] = '\n';
						break;
					}
					if (n == 20)
					{
						n = 0;
						l_k = l_k - 20;
						while (true)
						{
							n++;
							l_k--;
							if (temp_text[l_k] == 0x20)
							{
								temp_text[l_k] = '\n';
								l_k = 121;
								break;
							}
							if (n == 15)
							{
								l_k = 121;
								break;
							}
						}
						break;
					}
				}
			}
			if (l_k == 180 && temp_text.length()>200)//l_k % 60 == 0
			{
				while (true)
				{
					n++;
					l_k++;
					if (l_k + 1 == temp_text.length())
						break;
					if (temp_text[l_k] == 0x20)
					{
						temp_text[l_k] = '\n';
						break;
					}
					if (n == 20)
					{
						n = 0;
						l_k = l_k - 20;
						while (true)
						{
							n++;
							l_k--;
							if (temp_text[l_k] == 0x20)
							{
								temp_text[l_k] = '\n';
								l_k = 181;
								break;
							}
							if (n == 15)
							{
								l_k = 181;
								break;
							}
						}
						break;
					}
				}
			}
			if (l_k == 240 && temp_text.length()>260)//l_k % 60 == 0
			{
				while (true)
				{
					n++;
					l_k++;
					if (l_k + 1 == temp_text.length())
						break;
					if (temp_text[l_k] == 0x20)
					{
						temp_text[l_k] = '\n';
						break;
					}
					if (n == 20)
					{
						n = 0;
						l_k = l_k - 20;
						while (true)
						{
							n++;
							l_k--;
							if (temp_text[l_k] == 0x20)
							{
								temp_text[l_k] = '\n';
								l_k = 241;
								//l_k + n + 1;
								break;
							}
							if (n == 15)
							{
								l_k = 241;
								break;
							}
						}
						break;
					}
				}
			}
			if (l_k == 300 && temp_text.length()>320)//l_k % 60 == 0
			{
				while (true)
				{
					n++;
					l_k++;
					if (temp_text[l_k] == 0x20)
					{
						temp_text[l_k] = '\n';
						break;
					}
					if (n == 20)
					{
						n = 0;
						l_k = l_k - 20;
						while (true)
						{
							n++;
							l_k--;
							if (temp_text[l_k] == 0x20)
							{
								temp_text[l_k] = '\n';
								l_k = 301;
								//l_k + n + 1;
								break;
							}
							if (n == 15)
							{
								l_k = 301;
								break;
							}
						}
						break;
					}
				}
			}
			if (l_k == 380 && temp_text.length()>400)//l_k % 60 == 0
			{
				while (true)
				{
					n++;
					l_k++;
					if (temp_text[l_k] == 0x20)
					{
						temp_text[l_k] = '\n';
						break;
					}
					if (n == 20)
					{
						n = 0;
						l_k = l_k - 20;
						while (true)
						{
							n++;
							l_k--;
							if (temp_text[l_k] == 0x20)
							{
								temp_text[l_k] = '\n';
								l_k = 396;
								//l_k + n + 1;
								break;
							}
							if (n == 15)
							{
								l_k = 396;
								break;
							}
						}
						break;
					}
				}
			}
			if (l_k == 460 && temp_text.length()>480)//l_k % 60 == 0
			{
				while (true)
				{
					n++;
					l_k++;
					if (temp_text[l_k] == 0x20)
					{
						temp_text[l_k] = '\n';
						break;
					}
					if (n == 20)
					{
						n = 0;
						l_k = l_k - 20;
						while (true)
						{
							n++;
							l_k--;
							if (temp_text[l_k] == 0x20)
							{
								temp_text[l_k] = '\n';
								l_k = 476;
								//l_k + n + 1;
								break;
							}
							if (n == 15)
							{
								l_k = 476;
								break;
							}
						}
						break;
					}
				}
			}
			if (l_k == 540 && temp_text.length()>560)//l_k % 60 == 0
			{
				while (true)
				{
					n++;
					l_k++;
					if (temp_text[l_k] == 0x20)
					{
						temp_text[l_k] = '\n';
						break;
					}
					if (n == 20)
					{
						n = 0;
						l_k = l_k - 20;
						while (true)
						{
							n++;
							l_k--;
							if (temp_text[l_k] == 0x20)
							{
								temp_text[l_k] = '\n';
								l_k = 561;
								//l_k + n + 1;
								break;
							}
							if (n == 15)
							{
								l_k = 561;
								break;
							}
						}
						break;
					}
				}
			}


		}
		all_body[l] = temp_text;

	}


	Text1->setString(all_head[nump]);
	Text2->setString(all_head[nump + 1]);
	Text3->setString(all_head[nump + 2]);
	Text4->setString(all_head[nump + 3]);
	Text5->setString(all_head[nump + 4]);
	Text6->setString(all_head[nump + 5]);
	Text7->setString(all_head[nump + 6]);
	Text8->setString(all_head[nump + 7]);
	Text9->setString(all_head[nump + 8]);
	Set_head->enableShadow(ccc4(0, 0, 0, 255)); // включает тень

	static int bex[64];

	for (int x = 0; x < 64; x++) // расчет текущей страницы для каждой кнопки
	{
		if (x == 0)
		{
			bex[x] = num_pages[x];
		}
		else
			bex[x] = bex[x - 1] + num_pages[x];
	}

	for (int n = 0; n < 9; n++)
	{
		Box_Button[n]->addClickEventListener([=](Ref *)
		{
			Button1->setVisible(false);
			Button2->setVisible(false);
			Button3->setVisible(false);
			Button4->setVisible(false);
			Button5->setVisible(false);
			Button6->setVisible(false);
			Button7->setVisible(false);
			Button8->setVisible(false);
			Button9->setVisible(false);
			Text1->setVisible(false);
			Text2->setVisible(false);
			Text3->setVisible(false);
			Text4->setVisible(false);
			Text5->setVisible(false);
			Text6->setVisible(false);
			Text7->setVisible(false);
			Text8->setVisible(false);
			Text9->setVisible(false);

			Set_head->setVisible(true);
			Set_body->setVisible(true);
			Set_Sprite->setVisible(true);
			Sg_page->setVisible(true);
			Current_page->setVisible(true);
			Up_ch->setVisible(false);
			Down_ch->setVisible(false);

			if (num_pages[nump + n] == 1)
				bex[n + nump] = bex[n + nump] - 1;
			if (num_pages[nump + n] == 2)
				bex[n + nump] = bex[n + nump] - 2;
			if (num_pages[nump + n] == 3)
				bex[n + nump] = bex[n + nump] - 3;

			Set_head->setString(all_head[nump + n]); //текущий заголовок
			Set_body->setString(all_body[bex[n + nump]]); //текущая первая страница текста
			Current_page->setString("1");
			Set_Sprite->Sprite::setTexture(dir[n + nump]);
			if (num_pages[nump + n] > 1)
			{
				next->setVisible(true);
				if (next)
				{
					next->addClickEventListener([=](Ref *)
					{
						bex[n + nump]++;
						Set_body->setString(all_body[bex[n + nump]]);
						prev->setVisible(true);
						Current_page->setString("2");
						if (n == 0)
						{
							if (num_pages[nump + n] == 2 && num_pages[nump + n] - 1 == bex[n + nump])
							{
								next->setVisible(false);
							}
							if (num_pages[nump + n] == 3 && num_pages[nump + n] - 1 == bex[n + nump])
							{
								next->setVisible(false);
								Current_page->setString("3");
							}
						}
						else
						{
							if (num_pages[nump + n] == 2 && num_pages[nump + n] - 1 == bex[n + nump] - bex[n + nump - 1])
							{
								next->setVisible(false);
							}
							if (num_pages[nump + n] == 3 && num_pages[nump + n] - 1 == bex[n + nump] - bex[n + nump - 1])
							{
								next->setVisible(false);
								Current_page->setString("3");
							}
						}
					});
				}
				if (prev)
				{
					prev->addClickEventListener([=](Ref *)
					{
						bex[n + nump]--;
						Set_body->setString(all_body[bex[n + nump]]);
						next->setVisible(true);
						Current_page->setString("2");
						if (n == 0)
						{
							if (num_pages[nump + n] == 2 && num_pages[nump + n] - 2 == bex[n + nump])
							{
								Current_page->setString("1");
								prev->setVisible(false);
							}
							if (num_pages[nump + n] == 3 && num_pages[nump + n] - 3 == bex[n + nump])
							{
								Current_page->setString("1");
								prev->setVisible(false);
							}
						}
						else
						{
							if (num_pages[nump + n] == 2 && num_pages[nump + n] - 2 == bex[n + nump] - bex[n + nump - 1])
							{
								Current_page->setString("1");
								prev->setVisible(false);
							}
							if (num_pages[nump + n] == 3 && num_pages[nump + n] - 3 == bex[n + nump] - bex[n + nump - 1])
							{
								Current_page->setString("1");
								prev->setVisible(false);
							}
						}
					});
				}
			}
			Back->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
				Set_head->setVisible(false);
				Set_body->setVisible(false);
				Set_Sprite->setVisible(false);
				Sg_page->setVisible(false);
				Current_page->setVisible(false);
				next->setVisible(false);
				prev->setVisible(false);
				Button1->setVisible(true);
				Button2->setVisible(true);
				Button3->setVisible(true);
				Button4->setVisible(true);
				Button5->setVisible(true);
				Button6->setVisible(true);
				Button7->setVisible(true);
				Button8->setVisible(true);
				Button9->setVisible(true);
				Text1->setVisible(true);
				Text2->setVisible(true);
				Text3->setVisible(true);
				Text4->setVisible(true);
				Text5->setVisible(true);
				Text6->setVisible(true);
				Text7->setVisible(true);
				Text8->setVisible(true);
				Text9->setVisible(true);
				Up_ch->setVisible(true);
				Down_ch->setVisible(true);
				for (int x = 0; x < 64; x++) // расчет текущей страницы для каждой кнопки
				{
					if (x == 0)
					{
						bex[x] = num_pages[x];
					}
					else
						bex[x] = bex[x - 1] + num_pages[x];
				}
				Back->addClickEventListener([=](Ref *)
				{
					System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
					Wiki_Menu->setVisible(false);
					Top_Line->setVisible(false);//и убрать фон и название слоя
					Name_Layer->setVisible(false);
					Mus->setTouchEnabled(true);
					Alb->setTouchEnabled(true);
					Wiki->setTouchEnabled(true);
					nump = 0;
					Back->addClickEventListener([=](Ref *)
					{
						System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
						Back_Node->setVisible(false);
						Bonus_menu->setVisible(false);
						Button_Menu->setVisible(true);
					});
				});
			});

		});

	}

	if (Down_ch)
	{
		Down_ch->addClickEventListener([=](Ref *)
		{

			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[2], false, All_Volume*System_Volume);
			if (nump < 55)
			{
				nump++;
			}
			else
			{
				nump = 0;
			}
			Text1->setString(all_head[nump]);
			Text2->setString(all_head[nump + 1]);
			Text3->setString(all_head[nump + 2]);
			Text4->setString(all_head[nump + 3]);
			Text5->setString(all_head[nump + 4]);
			Text6->setString(all_head[nump + 5]);
			Text7->setString(all_head[nump + 6]);
			Text8->setString(all_head[nump + 7]);
			Text9->setString(all_head[nump + 8]);
		});
	}

	if (Up_ch)
	{
		Up_ch->addClickEventListener([=](Ref *)
		{

			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[2], false, All_Volume*System_Volume);
			if (nump > 0 || nump == 0)
			{
				nump--;
				if (nump < 0)
				{
					nump = 55;
				}
			}
			Text1->setString(all_head[nump]);
			Text2->setString(all_head[nump + 1]);
			Text3->setString(all_head[nump + 2]);
			Text4->setString(all_head[nump + 3]);
			Text5->setString(all_head[nump + 4]);
			Text6->setString(all_head[nump + 5]);
			Text7->setString(all_head[nump + 6]);
			Text8->setString(all_head[nump + 7]);
			Text9->setString(all_head[nump + 8]);
		});
	}

	Back->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
		Wiki_Menu->setVisible(false);
		Top_Line->setVisible(false);//и убрать фон и название слоя
		Name_Layer->setVisible(false);
		Mus->setTouchEnabled(true);
		Alb->setTouchEnabled(true);
		Wiki->setTouchEnabled(true);
		nump = 0;
		Back->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
			Bonus_menu->setVisible(false);
			Back_Node->setVisible(false);
			Button_Menu->setVisible(true);
		});
	});

}


void albumset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, vector<string> setcomment, vector<string> setsub, vector<string> setCG)
{
	if (Musalb == false) // надстройка при условии
	{
		thread smooth(background_smooth, false);
		smooth.detach();
	}

	auto *Alb = static_cast<cocos2d::ui::Button*>(Bonus_menu->getChildByName("Alb"));
	auto *Mus = static_cast<cocos2d::ui::Button*>(Bonus_menu->getChildByName("Mus"));
	auto *Wiki = static_cast<cocos2d::ui::Button*>(Bonus_menu->getChildByName("Wiki"));
	auto *Back = static_cast<cocos2d::ui::Button*>(Back_Node->getChildByName("Back"));
	auto Name_Layer = static_cast<ui::Text*>(Back_Node->getChildByName("Name_Layer")); /* имя слоев */
	auto *Back_Line = Back_Node->getChildByName("Back_Line");
	auto *Top_Line = Back_Node->getChildByName("Top_Line");
	//================================================================================================================================================================================
	//=========================================================================ALBUM==================================================================================================
	//================================================================================================================================================================================
	auto *Album_menu = Bonus_menu->getChildByName("Album_menu");
	//auto *Alb_name = static_cast<cocos2d::ui::Text*>(Album_menu->getChildByName("Alb_name"));
	//Alb_name->enableShadow(ccc4(0, 0, 0, 255)); // включает тень названия меню альбома

	//Объявление кнопок скрола Album_menu 
	auto *Scrol = Album_menu->getChildByName("Scrol"); // скрол
	auto *bg_1 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_1")); // пустой элемент используется как кнопка пустышка
	auto *bg_2 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_2")); // пустой элемент используется как кнопка пустышка
	auto *bg_3 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_3")); // пустой элемент используется как кнопка пустышка
	auto *bg_4 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_4")); // пустой элемент используется как кнопка пустышка
	auto *bg_5 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_5")); // пустой элемент используется как кнопка пустышка
	auto *bg_6 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_6")); // пустой элемент используется как кнопка пустышка
	auto *bg_7 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_7")); // пустой элемент используется как кнопка пустышка
	auto *bg_8 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_8")); // пустой элемент используется как кнопка пустышка
	auto *bg_9 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_9")); // пустой элемент используется как кнопка пустышка
	auto *bg_10 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_10")); // пустой элемент используется как кнопка пустышка
	auto *bg_11 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_11")); // пустой элемент используется как кнопка пустышка
	auto *bg_12 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_12")); // пустой элемент используется как кнопка пустышка
	auto *bg_13 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_13")); // пустой элемент используется как кнопка пустышка
	auto *bg_14 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_14")); // пустой элемент используется как кнопка пустышка
	auto *bg_15 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_15")); // пустой элемент используется как кнопка пустышка
	auto *bg_16 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_16")); // пустой элемент используется как кнопка пустышка
	auto *bg_17 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_17")); // пустой элемент используется как кнопка пустышка
	auto *bg_18 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_18")); // пустой элемент используется как кнопка пустышка
	auto *bg_19 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_19")); // пустой элемент используется как кнопка пустышка
	auto *bg_20 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_20")); // пустой элемент используется как кнопка пустышка
	auto *bg_21 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_21")); // пустой элемент используется как кнопка пустышка
	auto *bg_22 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_22")); // пустой элемент используется как кнопка пустышка
	auto *bg_23 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_23")); // пустой элемент используется как кнопка пустышка
	auto *bg_24 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_24")); // пустой элемент используется как кнопка пустышка
	auto *bg_25 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_25")); // пустой элемент используется как кнопка пустышка
	auto *bg_26 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_26")); // пустой элемент используется как кнопка пустышка
	auto *bg_27 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_27")); // пустой элемент используется как кнопка пустышка
	auto *bg_28 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_28")); // пустой элемент используется как кнопка пустышка
	auto *bg_29 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_29")); // пустой элемент используется как кнопка пустышка
	auto *bg_30 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_30")); // пустой элемент используется как кнопка пустышка
	auto *bg_31 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_31")); // пустой элемент используется как кнопка пустышка
	auto *bg_32 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_32")); // пустой элемент используется как кнопка пустышка
	auto *bg_33 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_33")); // пустой элемент используется как кнопка пустышка
	auto *bg_34 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_34")); // пустой элемент используется как кнопка пустышка
	auto *bg_35 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_35")); // пустой элемент используется как кнопка пустышка
	auto *bg_36 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_36")); // пустой элемент используется как кнопка пустышка
	auto *bg_37 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_37")); // пустой элемент используется как кнопка пустышка
	auto *bg_38 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_38")); // пустой элемент используется как кнопка пустышка
	auto *bg_39 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_39")); // пустой элемент используется как кнопка пустышка
	auto *bg_40 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_40")); // пустой элемент используется как кнопка пустышка
	auto *bg_41 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_41")); // пустой элемент используется как кнопка пустышка
	auto *bg_42 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_42")); // пустой элемент используется как кнопка пустышка
	auto *bg_43 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_43")); // пустой элемент используется как кнопка пустышка
	auto *bg_44 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_44")); // пустой элемент используется как кнопка пустышка
	auto *bg_45 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_45")); // пустой элемент используется как кнопка пустышка
	auto *bg_46 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_46")); // пустой элемент используется как кнопка пустышка
	auto *bg_47 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_47")); // пустой элемент используется как кнопка пустышка
	auto *bg_48 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_48")); // пустой элемент используется как кнопка пустышка
	auto *bg_49 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_49")); // пустой элемент используется как кнопка пустышка
	auto *bg_50 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_50")); // пустой элемент используется как кнопка пустышка
	auto *bg_51 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_51")); // пустой элемент используется как кнопка пустышка
	auto *bg_52 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_52")); // пустой элемент используется как кнопка пустышка
	auto *bg_53 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_53")); // пустой элемент используется как кнопка пустышка
	auto *bg_54 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_54")); // пустой элемент используется как кнопка пустышка
	auto *bg_55 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_55")); // пустой элемент используется как кнопка пустышка
	auto *bg_56 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_56")); // пустой элемент используется как кнопка пустышка
	auto *bg_57 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_57")); // пустой элемент используется как кнопка пустышка
	auto *bg_58 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_58")); // пустой элемент используется как кнопка пустышка
	auto *bg_59 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_59")); // пустой элемент используется как кнопка пустышка
	auto *bg_60 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_60")); // пустой элемент используется как кнопка пустышка
	auto *bg_61 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_61")); // пустой элемент используется как кнопка пустышка
	auto *bg_62 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_62")); // пустой элемент используется как кнопка пустышка
	auto *bg_63 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_63")); // пустой элемент используется как кнопка пустышка
	auto *bg_64 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_64")); // пустой элемент используется как кнопка пустышка
	auto *bg_65 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_65")); // пустой элемент используется как кнопка пустышка
	auto *bg_66 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_66")); // пустой элемент используется как кнопка пустышка
	auto *bg_67 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_67")); // пустой элемент используется как кнопка пустышка
	auto *bg_68 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_68")); // пустой элемент используется как кнопка пустышка
	auto *bg_69 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_69")); // пустой элемент используется как кнопка пустышка
	auto *bg_70 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_70")); // пустой элемент используется как кнопка пустышка
	auto *bg_71 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_71")); // пустой элемент используется как кнопка пустышка
	auto *bg_72 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_72")); // пустой элемент используется как кнопка пустышка
	auto *bg_73 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_73")); // пустой элемент используется как кнопка пустышка
	auto *bg_74 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_74")); // пустой элемент используется как кнопка пустышка
	auto *bg_75 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_75")); // пустой элемент используется как кнопка пустышка
	auto *bg_76 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_76")); // пустой элемент используется как кнопка пустышка
	auto *bg_77 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_77")); // пустой элемент используется как кнопка пустышка
	auto *bg_78 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_78")); // пустой элемент используется как кнопка пустышка
	auto *bg_79 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_79")); // пустой элемент используется как кнопка пустышка
	auto *bg_80 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_80")); // пустой элемент используется как кнопка пустышка
	auto *bg_81 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_81")); // пустой элемент используется как кнопка пустышка
	auto *bg_82 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_82")); // пустой элемент используется как кнопка пустышка
	auto *bg_83 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_83")); // пустой элемент используется как кнопка пустышка
	auto *bg_84 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_84")); // пустой элемент используется как кнопка пустышка
	auto *bg_85 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_85")); // пустой элемент используется как кнопка пустышка
	auto *bg_86 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_86")); // пустой элемент используется как кнопка пустышка
	auto *bg_87 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg_87")); // пустой элемент используется как кнопка пустышка
	//======================= для всех элементов задать логику появления
	auto *bg1 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg1")); // отображает миниатюру картинки если активна
	auto *bg2 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg2")); // отображает миниатюру картинки если активна
	auto *bg3 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg3")); // отображает миниатюру картинки если активна
	auto *bg4 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg4")); // отображает миниатюру картинки если активна
	auto *bg5 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg5")); // отображает миниатюру картинки если активна
	auto *bg6 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg6")); // отображает миниатюру картинки если активна
	auto *bg7 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg7")); // отображает миниатюру картинки если активна
	auto *bg8 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg8")); // отображает миниатюру картинки если активна
	auto *bg9 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg9")); // отображает миниатюру картинки если активна
	auto *bg10 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg10")); // отображает миниатюру картинки если активна
	auto *bg11 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg11")); // отображает миниатюру картинки если активна
	auto *bg12 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg12")); // отображает миниатюру картинки если активна
	auto *bg13 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg13")); // отображает миниатюру картинки если активна
	auto *bg14 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg14")); // отображает миниатюру картинки если активна
	auto *bg15 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg15")); // отображает миниатюру картинки если активна
	auto *bg16 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg16")); // отображает миниатюру картинки если активна
	auto *bg17 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg17")); // отображает миниатюру картинки если активна
	auto *bg18 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg18")); // отображает миниатюру картинки если активна
	auto *bg19 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg19")); // отображает миниатюру картинки если активна
	auto *bg20 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg20")); // отображает миниатюру картинки если активна
	auto *bg21 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg21")); // отображает миниатюру картинки если активна
	auto *bg22 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg22")); // отображает миниатюру картинки если активна
	auto *bg23 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg23")); // отображает миниатюру картинки если активна
	auto *bg24 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg24")); // отображает миниатюру картинки если активна
	auto *bg25 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg25")); // отображает миниатюру картинки если активна
	auto *bg26 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg26")); // отображает миниатюру картинки если активна
	auto *bg27 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg27")); // отображает миниатюру картинки если активна
	auto *bg28 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg28")); // отображает миниатюру картинки если активна
	auto *bg29 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg29")); // отображает миниатюру картинки если активна
	auto *bg30 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg30")); // отображает миниатюру картинки если активна
	auto *bg31 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg31")); // отображает миниатюру картинки если активна
	auto *bg32 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg32")); // отображает миниатюру картинки если активна
	auto *bg33 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg33")); // отображает миниатюру картинки если активна
	auto *bg34 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg34"));// отображает миниатюру картинки если активна
	auto *bg35 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg35")); // отображает миниатюру картинки если активна
	auto *bg36 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg36"));
	auto *bg37 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg37"));
	auto *bg38 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg38"));
	auto *bg39 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg39"));
	auto *bg40 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg40"));
	auto *bg41 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg41"));
	auto *bg42 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg42"));
	auto *bg43 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg43"));
	auto *bg44 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg44"));
	auto *bg45 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg45"));
	auto *bg46 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg46"));
	auto *bg47 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg47"));
	auto *bg48 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg48"));
	auto *bg49 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg49"));
	auto *bg50 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg50"));
	auto *bg51 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg51"));
	auto *bg52 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg52"));
	auto *bg53 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg53"));
	auto *bg54 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg54"));
	auto *bg55 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg55"));
	auto *bg56 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg56"));
	auto *bg57 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg57"));
	auto *bg58 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg58"));
	auto *bg59 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg59"));
	auto *bg60 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg60"));
	auto *bg61 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg61"));
	auto *bg62 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg62"));
	auto *bg63 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg63"));
	auto *bg64 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg64"));
	auto *bg65 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg65"));
	auto *bg66 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg66"));
	auto *bg67 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg67"));
	auto *bg68 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg68"));
	auto *bg69 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg69"));
	auto *bg70 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg70"));
	auto *bg71 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg71"));
	auto *bg72 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg72"));
	auto *bg73 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg73"));
	auto *bg74 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg74"));
	auto *bg75 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg75"));
	auto *bg76 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg76"));
	auto *bg77 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg77"));
	auto *bg78 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg78"));
	auto *bg79 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg79"));
	auto *bg80 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg80"));
	auto *bg81 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg81"));
	auto *bg82 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg82"));
	auto *bg83 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg83"));
	auto *bg84 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg84"));
	auto *bg85 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg85"));
	auto *bg86 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg86"));
	auto *bg87 = static_cast<cocos2d::ui::Button*>(Scrol->getChildByName("bg87")); // все 87 кнопак скрола


	//Объявление кнопок и спрайтов меню Album_CG(Это дочерний объект Album_menu)
	auto *Album_CG = Album_menu->getChildByName("Album_CG"); //меню CG
	//Album_CG->setLocalZOrder(3);

	auto *Image_set = static_cast<cocos2d::Sprite*>(Album_CG->getChildByName("Image_set")); // элемент картинки в меню Album CG
	auto *CGset = static_cast<cocos2d::Sprite*>(Album_CG->getChildByName("CGset")); // элемент кнопок в меню AlbumCG
	auto *Subtitle = static_cast<cocos2d::ui::Text*>(Album_CG->getChildByName("Subtitle")); // элемент субтитров в меню Album CG

	//button album CG
	auto *Comment1 = static_cast<cocos2d::ui::Button*>(Album_CG->getChildByName("Comment1"));
	auto *Comment2 = static_cast<cocos2d::ui::Button*>(Album_CG->getChildByName("Comment2"));
	auto *Hide = static_cast<cocos2d::ui::Button*>(Album_CG->getChildByName("Hide"));

	auto prev_CG = static_cast<cocos2d::ui::Button*>(Album_CG->getChildByName("Prev"));
	auto past_CG = static_cast<cocos2d::ui::Button*>(Album_CG->getChildByName("Past"));

	const int l = 87;//Количество мест для картинок в массиве

	cocos2d::ui::Button **bg_x[l] = { &bg_1, &bg_2, &bg_3, &bg_4, &bg_5, &bg_6, &bg_7, &bg_8, &bg_9, &bg_10,
		&bg_11, &bg_12, &bg_13, &bg_14, &bg_15, &bg_16, &bg_17, &bg_18, &bg_19, &bg_20,
		&bg_21, &bg_22, &bg_23, &bg_24, &bg_25, &bg_26, &bg_27, &bg_28, &bg_29, &bg_30,
		&bg_31, &bg_32, &bg_33, &bg_34, &bg_35, &bg_36, &bg_37, &bg_38, &bg_39, &bg_40,
		&bg_41, &bg_42, &bg_43, &bg_44, &bg_45, &bg_46, &bg_47, &bg_48, &bg_49, &bg_50,
		&bg_51, &bg_52, &bg_53, &bg_54, &bg_55, &bg_56, &bg_57, &bg_58, &bg_59, &bg_60,
		&bg_61, &bg_62, &bg_63, &bg_64, &bg_65, &bg_66, &bg_67, &bg_68, &bg_69, &bg_70,
		&bg_71, &bg_72, &bg_73, &bg_74, &bg_75, &bg_76, &bg_77, &bg_78, &bg_79, &bg_80,
		&bg_81, &bg_82, &bg_83, &bg_84, &bg_85, &bg_86, &bg_87 }; //нажимеая понель всех кнопок альбома - главная часть

	cocos2d::ui::Button **bgx[l] = { &bg1, &bg2, &bg3, &bg4, &bg5, &bg6, &bg7, &bg8, &bg9, &bg10,
		&bg11, &bg12, &bg13, &bg14, &bg15, &bg16, &bg17, &bg18, &bg19, &bg20,
		&bg21, &bg22, &bg23, &bg24, &bg25, &bg26, &bg27, &bg28, &bg29, &bg30,
		&bg31, &bg32, &bg33, &bg34, &bg35, &bg36, &bg37, &bg38, &bg39, &bg40,
		&bg41, &bg42, &bg43, &bg44, &bg45, &bg46, &bg47, &bg48, &bg49, &bg50,
		&bg51, &bg52, &bg53, &bg54, &bg55, &bg56, &bg57, &bg58, &bg59, &bg60,
		&bg61, &bg62, &bg63, &bg64, &bg65, &bg66, &bg67, &bg68, &bg69, &bg70,
		&bg71, &bg72, &bg73, &bg74, &bg75, &bg76, &bg77, &bg78, &bg79, &bg80,
		&bg81, &bg82, &bg83, &bg84, &bg85, &bg86, &bg87 }; // а эта штука содержит все картинки альбома


	//logic vision CG Album

	bool bgn[l]; // поумолчанию выключена, позже будет в файле профиля будет получать значение
	for (int n = 0; n < 87; n++)
		bgn[n] = true;


	//logic miniCG Album
	for (int n = 0; n < 87; n++)
	{
		if (*(bgn + n) == true)
			(**(bgx + n))->setVisible(true);
	}

	char *CG_NUM = new char[(setCG[setCG.size() - 1]).length() + 1]; // создает переменную по размеру string последнего элемента вектора, незабуть потом удалить переменную которой выделена память 
	strcpy(CG_NUM, string(setCG[setCG.size() - 1]).c_str()); //копирует все элементы последнего элемента вектора

	static bool num_a_get[167]; //смещение всех картинок, какие активны а какие просто есть и к которым можно попасть только через кнопки перемещения по слайдам

	static int num_z; // переменная для перемещения по картинкам
	static int num_a; // переменная для перемещения по комментариям

	for (int n = 0; n < 167; n++) // иницилизирует массив значений для понимания к какой картинки итерироваться, все значения по умолчанию должны быть равны false 
		num_a_get[n] = false;

	for (int n = 0, a = 0, z = 0; n < 87; n++, a = a + 2)
	{
		num_a_get[z] = true; // изменяет значения массива по индексу z который считает смещения с помощью последней строчки CG_NUM, все вычесления z в конце цикла
		if (**(bg_x + n) && *(bgn + n) == true) // привить логику только если твой фрейм активен
		{
			(**(bg_x + n))->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
				Scrol->setVisible(false);
				Back_Line->setVisible(false);
				Top_Line->setVisible(false);
				Name_Layer->setVisible(false);
				Album_CG->setVisible(true);
				Image_set->Sprite::setTexture(setCG[z]);
				char *buff1 = new char[setcomment[a].length() + 1];
				char *buff2 = new char[setcomment[a + 1].length() + 1];
				char *buff3 = new char[setsub[a].length() + 1];
				char *buff4 = new char[setsub[a + 1].length() + 1];
				strcpy(buff1, setcomment[a].c_str());
				strcpy(buff2, setcomment[a + 1].c_str());
				strcpy(buff3, setsub[a].c_str());
				strcpy(buff4, setsub[a + 1].c_str());
				Back->addClickEventListener([=](Ref *)
				{
					if (nump > 0)
					{
						nump--;
					}
					cocos2d::experimental::AudioEngine::stop(Voice_id);
					Subtitle->setString("");
					System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
					Album_CG->setVisible(false);
					Scrol->setVisible(true);
					Back_Line->setVisible(true);
					Top_Line->setVisible(true);
					Name_Layer->setVisible(true);
					Back->addClickEventListener([=](Ref *)
					{
						System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
						Album_menu->setVisible(false);
						Top_Line->setVisible(false);//и убрать фон и название слоя
						Name_Layer->setVisible(false);
						Mus->setTouchEnabled(true);
						Alb->setTouchEnabled(true);
						Wiki->setTouchEnabled(true);
						if (Musalb == false)
						{
							Background_id = cocos2d::experimental::AudioEngine::play2d("Music\\00000000.mp3", true, 0.0);
							thread smooth(background_smooth, true);
							smooth.detach();
						}
						Back->addClickEventListener([=](Ref *)
						{
							System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
							Bonus_menu->setVisible(false);
							Back_Node->setVisible(false);
							Button_Menu->setVisible(true);
						});
					});
				});

				if (Comment1)
				{
					Comment1->addClickEventListener([=](Ref *)
					{

						cocos2d::experimental::AudioEngine::stop(Voice_id);
						Voice_id = cocos2d::experimental::AudioEngine::play2d(buff1, false, All_Volume*Voice_Volume);
						std::thread thr(COM, Subtitle, buff3);
						thr.detach();
					});
				}
				if (Comment2)
				{
					Comment2->addClickEventListener([=](Ref *)
					{

						cocos2d::experimental::AudioEngine::stop(Voice_id);
						Voice_id = cocos2d::experimental::AudioEngine::play2d(buff2, false, All_Volume*Voice_Volume);

						std::thread thr(COM, Subtitle, buff4);
						thr.detach();
					});

				}
				// ----------------------------------------  кнопка предыдущего слайда
				if (prev_CG)
				{
					num_z = Get_numcg(n, CG_NUM); //идет определение текущей картинки
					num_a = a; // идет определение текущих субтитров
					prev_CG->addClickEventListener([=](Ref *)
					{


						num_z--; //каждое нажатие двигаться назад

						if (num_z == -1) //если ты вышел за границы картинок сзади
						{
							if (nump > 0)
							{
								nump--;
							}
							cocos2d::experimental::AudioEngine::stop(Voice_id);
							Subtitle->setString("");
							num_z = 167;
							num_a = 172; //переместиться в конец
						}





						if (num_a_get[num_z + 1] == true) //если следующий спрайт после итерации был активным прекратить воспроизведение текущего комментария и итерироваться к предыдущим
						{
							if (nump > 0)
							{
								nump--;
							}
							cocos2d::experimental::AudioEngine::stop(Voice_id);
							Subtitle->setString("");
							num_a = num_a - 2;
						}

						System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume); //далее повтор тех же иницилизаций что и сверху
						Image_set->Sprite::setTexture(setCG[num_z]);

						char *buff1 = new char[setcomment[num_a].length() + 1];
						char *buff2 = new char[setcomment[num_a + 1].length() + 1];
						char *buff3 = new char[setsub[num_a].length() + 1];
						char *buff4 = new char[setsub[num_a + 1].length() + 1];
						strcpy(buff1, setcomment[num_a].c_str());
						strcpy(buff2, setcomment[num_a + 1].c_str());
						strcpy(buff3, setsub[num_a].c_str());
						strcpy(buff4, setsub[num_a + 1].c_str());


						if (Comment1)
						{
							Comment1->addClickEventListener([=](Ref *)
							{

								cocos2d::experimental::AudioEngine::stop(Voice_id);
								Voice_id = cocos2d::experimental::AudioEngine::play2d(buff1, false, All_Volume*Voice_Volume);

								std::thread thr(COM, Subtitle, buff3);
								thr.detach();
							});
						}
						if (Comment2)
						{
							Comment2->addClickEventListener([=](Ref *)
							{

								cocos2d::experimental::AudioEngine::stop(Voice_id);
								Voice_id = cocos2d::experimental::AudioEngine::play2d(buff2, false, All_Volume*Voice_Volume);

								std::thread thr(COM, Subtitle, buff4);
								thr.detach();
							});

						}

					});

				}
				//-------------------------------------------------------------------кнопка следующего слайда -  сделана по анологии с кнопкой предыдущего, кроме итерации по субтитрам
				if (past_CG)
				{
					num_z = Get_numcg(n, CG_NUM);
					num_a = a;
					past_CG->addClickEventListener([=](Ref *)
					{

						num_z++;

						if (num_a_get[num_z] == true)
						{
							if (nump > 0)
							{
								nump--;
							}
							cocos2d::experimental::AudioEngine::stop(Voice_id);
							Subtitle->setString("");
							num_a = num_a + 2;
						}

						if (num_z == 168)
						{
							if (nump > 0)
							{
								nump--;
							}
							cocos2d::experimental::AudioEngine::stop(Voice_id);
							Subtitle->setString("");
							num_z = 0;
							num_a = 0;
						}

						System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
						Image_set->Sprite::setTexture(setCG[num_z]);

						char *buff1 = new char[setcomment[num_a].length() + 1];
						char *buff2 = new char[setcomment[num_a + 1].length() + 1];
						char *buff3 = new char[setsub[num_a].length() + 1];
						char *buff4 = new char[setsub[num_a + 1].length() + 1];
						strcpy(buff1, setcomment[num_a].c_str());
						strcpy(buff2, setcomment[num_a + 1].c_str());
						strcpy(buff3, setsub[num_a].c_str());
						strcpy(buff4, setsub[num_a + 1].c_str());

						if (Comment1)
						{
							Comment1->addClickEventListener([=](Ref *)
							{

								cocos2d::experimental::AudioEngine::stop(Voice_id);
								Voice_id = cocos2d::experimental::AudioEngine::play2d(buff1, false, All_Volume*Voice_Volume);

								std::thread thr(COM, Subtitle, buff3);
								thr.detach();
							});
						}
						if (Comment2)
						{
							Comment2->addClickEventListener([=](Ref *)
							{

								cocos2d::experimental::AudioEngine::stop(Voice_id);
								Voice_id = cocos2d::experimental::AudioEngine::play2d(buff2, false, All_Volume*Voice_Volume);

								std::thread thr(COM, Subtitle, buff4);
								thr.detach();
							});

						}

					});

				}

			});

		}
		switch (CG_NUM[n])//расчет z по значению CG_NUM
		{
		case '1':
			z++;
			break;
		case '2':
			z = z + 2;
			break;
		case '3':
			z = z + 3;
			break;
		case '4':
			z = z + 4;
			break;
		case '5':
			z = z + 5;
			break;
		}
		Back->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
			Album_menu->setVisible(false);
			Top_Line->setVisible(false);//и убрать фон и название слоя
			Name_Layer->setVisible(false);
			Mus->setTouchEnabled(true);
			Alb->setTouchEnabled(true);
			Wiki->setTouchEnabled(true);
			if (Musalb == false)
			{
				Background_id = cocos2d::experimental::AudioEngine::play2d("Music\\00000000.mp3", true, 0);
				thread smooth(background_smooth, true);
				smooth.detach();
			}
			Back->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
				Bonus_menu->setVisible(false);
				Back_Node->setVisible(false);
				Button_Menu->setVisible(true);
			});
		});
	}



	//if (Hide) //прячет нижнию полосу меню(комментарии и все все, должна оживать при повтолрном нажатии)
	//{
	//	Hide->addClickEventListener([=](Ref *)
	//	{
	//		CGset->setVisible(false);
	//		Hide->setVisible(false);
	//		Comment1->setVisible(false);
	//		Comment2->setVisible(false);
	//		Back_to_scroll->setVisible(false);

	//	});
	//}
}

void musset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node) // функция передачи текста кнопкам
{
	auto *Alb = static_cast<cocos2d::ui::Button*>(Bonus_menu->getChildByName("Alb"));
	auto *Mus = static_cast<cocos2d::ui::Button*>(Bonus_menu->getChildByName("Mus"));
	auto *Wiki = static_cast<cocos2d::ui::Button*>(Bonus_menu->getChildByName("Wiki"));
	auto *Back = static_cast<cocos2d::ui::Button*>(Back_Node->getChildByName("Back"));
	auto *Top_Line = Back_Node->getChildByName("Top_Line");
	auto Name_Layer = static_cast<ui::Text*>(Back_Node->getChildByName("Name_Layer"));
	//================================================================================================================================================================================
	//=========================================================================MUSIC==================================================================================================
	//================================================================================================================================================================================
	auto *Music_Menu = Bonus_menu->getChildByName("Music_menu");
	auto *Mus1 = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Mus1"));
	auto *Mus2 = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Mus2"));
	auto *Mus3 = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Mus3"));
	auto *Mus4 = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Mus4"));
	auto *Mus5 = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Mus5"));
	auto *Mus6 = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Mus6"));
	auto *Mus7 = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Mus7"));
	auto *Mus8 = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Mus8"));
	auto *Mus9 = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Mus9"));
	auto *Up = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Up"));
	auto *Down = static_cast<cocos2d::ui::Button*>(Music_Menu->getChildByName("Down"));









	auto update_button_info([=]()
	{
		string mus[] = {
			"01 - oRE No IMoUTo.                 0:59",
			"02 - GOOD MORNiNG                   1:34",
			"03 - Immediate Approach             1:51",
			"04 - SOFT BREEZEEEEE                1:31",
			"05 - Merry Go Round                 2:02",
			"06 - Roller Coaster                 1:23",
			"07 - downpour                       1:33",
			"08 - Ferris wheel                   1:33",
			"09 - STONiSHMENT HOUSE              1:46",
			"10 - After a storm comes a calm     2:07",
			"11 - street performer               1:32",
			"12 - Real Substantiality            2:19",
			"13 - rendezvous                     2:10",
			"14 - AKiHABARA,CHiYODA-KU           1:37",
			"15 - Super Approach!!               1:35",
			"16 - DESTROY GAME STORY             2:05",
			"17 - SECRETx2                       3:48" };

		char *Mus_Directory[] = { "Music\\00000000.mp3", "Music\\00000001.mp3", "Music\\00000002.mp3", "Music\\00000003.mp3",
			"Music\\00000004.mp3", "Music\\00000005.mp3", "Music\\00000006.mp3", "Music\\00000007.mp3", "Music\\00000008.mp3",
			"Music\\00000009.mp3", "Music\\0000000a.mp3", "Music\\0000000b.mp3", "Music\\0000000c.mp3", "Music\\0000000d.mp3",
			"Music\\0000000e.mp3", "Music\\0000000f.mp3", "Music\\00000010.mp3", };

		Mus1->setTitleText(mus[nump]);
		Mus2->setTitleText(mus[nump + 1]);
		Mus3->setTitleText(mus[nump + 2]);
		Mus4->setTitleText(mus[nump + 3]);
		Mus5->setTitleText(mus[nump + 4]);
		Mus6->setTitleText(mus[nump + 5]);
		Mus7->setTitleText(mus[nump + 6]);
		Mus8->setTitleText(mus[nump + 7]);
		Mus9->setTitleText(mus[nump + 8]);

		if (Mus1)
		{
			char *temp = Mus_Directory[nump];
			Mus1->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(temp, true, All_Volume*Background_Volume);
			});
		}

		if (Mus2)
		{
			char *temp = Mus_Directory[nump + 1];
			Mus2->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(temp, true, All_Volume*Background_Volume);
			});
		}

		if (Mus3)
		{
			char *temp = Mus_Directory[nump + 2];
			Mus3->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(temp, true, All_Volume*Background_Volume);
			});
		}

		if (Mus4)
		{
			char *temp = Mus_Directory[nump + 3];
			Mus4->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(temp, true, All_Volume*Background_Volume);
			});
		}

		if (Mus5)
		{
			char *temp = Mus_Directory[nump + 4];
			Mus5->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(temp, true, All_Volume*Background_Volume);
			});
		}

		if (Mus6)
		{
			char *temp = Mus_Directory[nump + 5];
			Mus6->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(temp, true, All_Volume*Background_Volume);
			});
		}

		if (Mus7)
		{
			char *temp = Mus_Directory[nump + 6];
			Mus7->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(temp, true, All_Volume*Background_Volume);
			});
		}

		if (Mus8)
		{
			char *temp = Mus_Directory[nump + 7];
			Mus8->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(temp, true, All_Volume*Background_Volume);
			});
		}

		if (Mus9)
		{
			char *temp = Mus_Directory[nump + 8];
			Mus9->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(temp, true, All_Volume*Background_Volume);
			});
		}

	});

	

	if (Down)
	{
		Down->addClickEventListener([=](Ref *)
		{

			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[2], false, All_Volume*System_Volume);
			if (nump < 8)
			{
				nump++;
				update_button_info();
			}

		});
	}

	if (Up)
	{
		Up->addClickEventListener([=](Ref *)
		{

			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[2], false, All_Volume*System_Volume);
			if (nump > 0 && nump != 0)
			{
				nump--;
				update_button_info();
			}
		});
	}

	Back->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
		cocos2d::experimental::AudioEngine::stop(Background_id);
		Background_id = cocos2d::experimental::AudioEngine::play2d("Music\\00000000.mp3", true, All_Volume*Background_Volume);// включение музыки при выходе из музыкального меню
		nump = 0;
		Music_Menu->setVisible(false);
		Top_Line->setVisible(false);//и убрать фон и название слоя
		Name_Layer->setVisible(false);
		Mus->setTouchEnabled(true);
		Alb->setTouchEnabled(true);
		Wiki->setTouchEnabled(true);
		Back->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[3], false, All_Volume*System_Volume);
			Bonus_menu->setVisible(false);
			Back_Node->setVisible(false);
			Button_Menu->setVisible(true);
		});
	});
	update_button_info();
}
void Show_Menu(Node *Game_Mode)
{
	//Buttons
	auto *Game_Menu_Button = static_cast<ui::Button*>(Game_Mode->getChildByTag(1834));
	auto *Auto_Mode_Button = static_cast<ui::Button*>(Game_Mode->getChildByTag(1835));
	auto Auto_Mode_Sprite = static_cast<Sprite*>(Game_Mode->getChildByTag(259));
	auto Skip_Mode_Button = static_cast<Sprite*>(Game_Mode->getChildByTag(1836));
	//Text_Box
	auto *Text_Box = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Text_Box"));
	auto Show_Menu_Button = static_cast<ui::Button*>(Text_Box->getChildByTag(7022));
	auto Show_Menu_Sprite = static_cast<Sprite*>(Text_Box->getChildByTag(11188));

	Show_Menu_Sprite->setTexture("Buttons\\Game\\strelochkav.png");
	Auto_Mode_Button->setVisible(true);
	Auto_Mode_Sprite->setVisible(true);
	Game_Menu_Button->setVisible(true);
	Skip_Mode_Button->setVisible(true);
	Show_Menu_Button->addClickEventListener([=](Ref *)
	{
		Hide_Menu(Game_Mode);
	});
}

void Hide_Menu(Node *Game_Mode)
{
	//Buttons
	auto *Game_Menu_Button = static_cast<ui::Button*>(Game_Mode->getChildByTag(1834));
	auto *Auto_Mode_Button = static_cast<ui::Button*>(Game_Mode->getChildByTag(1835));
	auto Auto_Mode_Sprite = static_cast<Sprite*>(Game_Mode->getChildByTag(259));
	auto Skip_Mode_Button = static_cast<Sprite*>(Game_Mode->getChildByTag(1836));
	//Text_Box
	auto *Text_Box = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Text_Box"));
	auto Show_Menu_Button = static_cast<ui::Button*>(Text_Box->getChildByTag(7022));
	auto Show_Menu_Sprite = static_cast<Sprite*>(Text_Box->getChildByTag(11188));

	Show_Menu_Sprite->setTexture("Buttons\\Game\\strelochka.png");
	Auto_Mode_Button->setVisible(false);
	Auto_Mode_Sprite->setVisible(false);
	Game_Menu_Button->setVisible(false);
	Skip_Mode_Button->setVisible(false);
	Show_Menu_Button->addClickEventListener([=](Ref *)
	{
		Show_Menu(Game_Mode);
	});
}