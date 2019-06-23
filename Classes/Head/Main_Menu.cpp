/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once



#include <string>
#include <chrono> // для работы со временем
#include <thread> // для работы с потоками 
#include <vector> // для работы с вектором
#include <fstream> // библиотека работы с файлом

#include "cocos2d.h"//кокос он и есть кокос
#include "cocostudio/CocoStudio.h" // Подключает библиотеку кокос студии для загрузки сцен из csb файлов
#include <ui/CocosGUI.h> // Использует label string
#include "AudioEngine.h"// Подключает библиотеку использования аудио для кокоса

#include "Live2D/LAppView.h"//для иницилизации облости куда помещается модель - поскольку ее надо иницилизировать в сомом начале , потом можно перенести в APP delegate такие штуки



#include "Main_Menu.h" // подключает головной файл 

#include "Classes\Dirs\Resourse.h"//все дирректории ресурсов засунутые в код
#include "Classes\Scripts\Page.h"//обработчик всех страничек
#include "Classes\Scripts\Script.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;
using namespace std::chrono;
using namespace cocos2d;

namespace profile_player
{
	extern bool Skip_All, ORE_old, Com_twoshot, Tips_twoshot, Text_old, Autosave1, Autosave2, Musalb; // Все настройки типа bool

	extern float All_Volume, Background_Volume, System_Volume, Game_Volume, Voice_Volume; // Вся громкость

	extern int Speed_Skip_Text, Speed_Text, Speed_Auto_Text; // Скорость режима пропуска текста, текста, и режима авто чтения

	extern int Background_id, System_id, Game_id, Voice_id; // id потоков аудио будет здесь
}



#define Skip_All profile_player::Skip_All
#define ORE_old profile_player::ORE_old
#define Com_twoshot profile_player::Com_twoshot
#define Tips_twoshot profile_player::Tips_twoshot
#define Text_old profile_player::Text_old
#define Autosave1 profile_player::Autosave1
#define Autosave2 profile_player::Autosave2
#define Musalb profile_player::Musalb

#define All_Volume profile_player::All_Volume
#define Background_Volume profile_player::Background_Volume
#define System_Volume profile_player::System_Volume
#define Game_Volume profile_player::Game_Volume
#define Voice_Volume profile_player::Voice_Volume

#define Speed_Skip_Text profile_player::Speed_Skip_Text
#define Speed_Text profile_player::Speed_Text
#define Speed_Auto_Text profile_player::Speed_Auto_Text

#define Background_id profile_player::Background_id
#define System_id profile_player::System_id
#define Game_id profile_player::Game_id
#define Voice_id profile_player::Voice_id

static bool temp_sw = false; // Переменная которая указывает были ли изменения в настройках по умолчанию false

int nump = 0; // управляет выходом из потока субтитров


#define COMPILE
TCHAR main_dir[MAX_PATH];

#ifdef COMPILE
string dir_setting = ".\\OREIMO\\Resources\\Profile\\config.bin";
string dir_save_script = ".\\OREIMO\\Resources\\Scripts\\";
string dir_load_script = ".\\OREIMO\\Resources\\Scripts\\";
string dir_home_sprite = ".\\Resources\\Sprites";
string dir_home_creator_tex = ".\\Resources\\Creator_resource";
#else
string dir_setting = ".\\Resources\\Profile\\config.bin";
string dir_save_script = ".\\Resources\\Scripts\\";
string dir_load_script = ".\\Resources\\Scripts\\";
string dir_home_sprite = ".\\Resources\\Sprites";
string dir_home_creator_tex = ".\\Resources\\Creator_resource";
#endif


void background_smooth(Node *Game_Mode, float volume);
void GetSub(vector<string> *SubText, vector<int> *time, int *z, string file); // преобразует субтитры из str в вектора
void needbeex(bool *x, int *po);
int Get_numcg(int num, string &CG_NUM);
void COM(cocos2d::ui::Text* Subtitle, string subfile);
void wikiset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, vector<string> dir);
void albumset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, vector<string> setcomment, vector<string> setsub, vector<string> setCG);
void musset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node);
void mapset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, MAINBOX *way);
void Hide_Menu(Node *Game_Mode);
void Show_Menu(Node *Game_Mode);
void confget();
void confset(Node *Setting_Menu, Layer *Button_Menu, Node *Back_Node, bool Background, bool hide_back_node);

bool is_int(std::string buff)
{
	for (int n = 0; n < buff.length(); n++)
	{
		if (isdigit(buff[n]) == 0)
			return false;
	}
	return true;
}

Scene* MAINBOX::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MAINBOX::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}


void MAINBOX::gameset()
{
	
	

}


void MAINBOX::mainset()
{
	GetCurrentDirectory(sizeof(main_dir), main_dir);


	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	this->removeAllComponents();
	loadsetcreator();
	return;//пока что разместил мгновенный запуск креатора


	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	this->removeAllComponents();
	
	//Объявление и определение головного файла главного меню
	auto rootNode = CSLoader::createNode("Resources\\All_Scene_cocos\\Main_Menu.csb");
	this->addChild(rootNode, 0);

	// add "Live2DModel"
	srand(time(0));
	int model = rand() % 6;
	int texture = rand();
	//switch (model)
	//{
	//case INDEX_MODEL_AYASE:
	//	texture = texture % INDEX_MODEL_AYASE_MAX;
	//	break;
	//case 	INDEX_MODEL_KANAKO:
	//	texture = texture % INDEX_MODEL_KANAKO_MAX;
	//	break;
	//case 	INDEX_MODEL_KIRINO:
	//	texture = texture % INDEX_MODEL_KIRINO_MAX;
	//	break;
	//case 	INDEX_MODEL_KURONEKO:
	//	texture = texture % INDEX_MODEL_KURONEKO_MAX;
	//	break;
	//case 	INDEX_MODEL_MANAMI:
	//	texture = texture % INDEX_MODEL_MANAMI_MAX;
	//	break;
	//case 	INDEX_MODEL_SAORI:
	//	texture = texture % INDEX_MODEL_SAORI_MAX;
	//	break;
	//}
	//LAppLive2DManager* Live2DMgr = LAppLive2DManager::getInstance(model, texture); // загрузка модели
	//vector<string> expression_main;
	//string temp1 = "face03" ;
	//string temp2 = "hand01";
	//string temp3 = "brow03";
	//expression_main.push_back(temp1);
	//expression_main.push_back(temp2);
	//expression_main.push_back(temp3);
	//Live2DMgr->changeExpression(expression_main);

	//auto* pLive2DSprite = LAppView::createDrawNode(Live2DMgr); //создание объекта модельки
	
	//rootNode->addChild(pLive2DSprite, 0);// крепление модели к запернтуы
	
	//бэкграундная музыка
	Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR["oRE No IMoUTo"], true, All_Volume*Background_Volume);
	

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
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
			Bonus_Menu->setVisible(true);
			Button_Menu->setVisible(false);
			Back_Node->setVisible(true);
			Back->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
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
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
			this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
			this->removeAllComponents();
			cocos2d::experimental::AudioEngine::stop(Background_id);
			loadsetcreator();
		});
	}

	if (Continue)
	{
		Continue->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
		});
	}

	if (Config)
	{
		Config->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
	albumset(Bonus_Menu, Button_Menu, Back_Node, CGCOMMP3_DIR, CGCOMTEXT_DIR, CG_DIR);// тестовая прогрузка могут быть неверны переходы
		Alb->addClickEventListener([=](Ref *)
		{
			if (Musalb == false) // надстройка при условии
			{
				background_smooth(Back_Node, 1);
			}
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
			Album_menu->setVisible(true); ////////////////////////////////////////////////////////////////////////// ПРИ ПЕРЕХОДЕ В КАЖДОЕ МЕНЮ ВЫКЛЮЧАТЬ ВСЕ КНОПКИ
			Mus->setTouchEnabled(false);
			Alb->setTouchEnabled(false);
			Map->setTouchEnabled(false);
			Wiki->setTouchEnabled(false);
			Top_Line->setVisible(true);//и выводить фон и название слоя
			Name_Layer->setVisible(true); Name_Layer->setString("РђР»СЊР±РѕРј"); // Альбом
			Back->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
				Album_menu->setVisible(false);
				Top_Line->setVisible(false);//и убрать фон и название слоя
				Name_Layer->setVisible(false);
				Mus->setTouchEnabled(true);
				Alb->setTouchEnabled(true);
				Wiki->setTouchEnabled(true);
				if (Musalb == false)
				{
					Back_Node->stopAllActions();
					cocos2d::experimental::AudioEngine::stop(Background_id);
					Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR["oRE No IMoUTo"], true, All_Volume*Background_Volume);

				}
				Back->addClickEventListener([=](Ref *)
				{
					System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
					Bonus_Menu->setVisible(false);
					Back_Node->setVisible(false);
					Button_Menu->setVisible(true);
				});
			});
		});
		
	


		Mus->addClickEventListener([=](Ref *)
		{
			background_smooth(Back_Node, 1);
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
			Wiki_Menu->setVisible(true);
			Mus->setTouchEnabled(false);
			Alb->setTouchEnabled(false);
			Map->setTouchEnabled(false);
			Wiki->setTouchEnabled(false);
			Top_Line->setVisible(true);//и выводить фон и название слоя
			Name_Layer->setVisible(true); Name_Layer->setString("O.R.E. Р›РёСЃС‚"); // O.R.E. Лист
			wikiset(Bonus_Menu, Button_Menu, Back_Node, ORE_DIR);
		});

	




}

void configurategame(bool *task, int newgame)
{
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	*task = true;

	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//delete[] CG_NUM; // при создании объекта игрового процесса память выделенная для CG_NUM возвращается

	//GAME.Set_Script(setscripts, setsprites, setscene, setmusic, newgame);
	//num = 0;
	*task = false;
}



void configuratemain()
{
	confget(); // взятие настроек из файла по переменным

}

void MAINBOX::loadsetmain()
{
	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	this->removeAllComponents();
	auto rootNode = CSLoader::createNode("Resources\\All_Scene_cocos\\Loading.csb");
	this->addChild(rootNode, 1);
	auto Star = static_cast<Sprite*>(rootNode->getChildByTag(1027));
	auto AllTime = CSLoader::createTimeline("Resources\\All_Scene_cocos\\Loading.csb");
	AllTime->setTimeSpeed(1.0f);
	AllTime->gotoFrameAndPlay(0);
	Star->runAction(AllTime);

	configuratemain();

	auto swichscene = CallFunc::create(this, callfunc_selector(MAINBOX::mainset));
	auto delay_for_scene = Sequence::create( DelayTime::create(1.0), swichscene, NULL);
	this->runAction(delay_for_scene);
	
}

void MAINBOX::loadsetgame(int current_script)
{
	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	this->removeAllComponents();
	cocos2d::experimental::AudioEngine::stop(Background_id);
	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	auto rootNode = CSLoader::createNode("Resources\\All_Scene_cocos\\Loading.csb");
	this->addChild(rootNode, 1);
	auto Star = static_cast<Sprite*>(rootNode->getChildByTag(1027));
	auto AllTime = CSLoader::createTimeline("Resources\\All_Scene_cocos\\Loading.csb");
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


void MAINBOX::loadsetcreator()
{
	auto rootNode = CSLoader::createNode("Resources\\All_Scene_cocos\\Loading.csb");
	this->addChild(rootNode, 1);
	auto Star = static_cast<Sprite*>(rootNode->getChildByTag(1027));
	auto AllTime = CSLoader::createTimeline("Resources\\All_Scene_cocos\\Loading.csb");
	AllTime->setTimeSpeed(1.0f);
	AllTime->gotoFrameAndPlay(0);
	Star->runAction(AllTime); // запускает звезву
	auto swichscene = CallFunc::create(this, callfunc_selector(MAINBOX::creatorset));
	auto delay_for_scene = Sequence::create(DelayTime::create(1.0), swichscene, NULL);
	this->runAction(delay_for_scene);
}
// on "init" you need to initialize your instance

bool MAINBOX::init()
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
	
	//Head_Menu = this;
	loadsetmain();


	
	return true;
}

void mapset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, MAINBOX *way)
{
	auto *Map_Menu = Bonus_menu->getChildByName("Map_menu");
	auto *Map_Button = Map_Menu->getChildByTag(20025);
	auto AKYO_0000A = static_cast<ui::Button*>(Map_Button->getChildByName("AKYO_0000A"));
	auto AKYO_0010A = static_cast<ui::Button*>(Map_Button->getChildByName("AKYO_0010A"));
	auto AKYO_0020T = static_cast<ui::Button*>(Map_Button->getChildByName("AKYO_0020T"));

	//AKYO_0000A->addClickEventListener([=](Ref *)
	//{
	//	System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
	//	way->loadsetgame(0);
	//});

	//AKYO_0010A->addClickEventListener([=](Ref *)
	//{
	//	System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
	//	way->loadsetgame(1);
	//});

	//AKYO_0020T->addClickEventListener([=](Ref *)
	//{
	//	System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
	//	way->loadsetgame(2);
	//});

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



void background_smooth(Node *Game_Mode, float volume)
{
	if (volume == 1)
		Game_Mode->stopAllActions();
	cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*(volume - 0.1));
	if (volume - 0.1f < 0)
	{
		cocos2d::experimental::AudioEngine::stop(Background_id);
		return;
	}
	else
	{
		Game_Mode->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([=](){
			background_smooth(Game_Mode, volume - 0.1f); }), nullptr));
	}
		
	
}

void background_smooth(Node *Game_Mode, float volume, string dir_next_music)
{
	if (volume == 1)
		Game_Mode->stopAllActions();
	cocos2d::experimental::AudioEngine::setVolume(Background_id, (All_Volume*Background_Volume)*(volume - 0.1f));
	if (volume - 0.1f < 0)
	{
		cocos2d::experimental::AudioEngine::stop(Background_id);
		Background_id = cocos2d::experimental::AudioEngine::play2d(dir_next_music, true, All_Volume*Background_Volume);
		return;
	}
	else
	{
		Game_Mode->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([=](){
			background_smooth(Game_Mode, volume - 0.1f, dir_next_music); }), nullptr));
	}


}

void GetSub(vector<string> *SubText, vector<int> *time, int *z, string file) // преобразует субтитры из str в вектора
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

		buff = buffvec[*z + 1]; // кидает во временную переменную строчку с таймингом для его разбора

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
		buff = buffvec[*z + 2];// кидает во временную переменную строчку с текстом субтитра для его редактирования
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
		(*(SubText)).push_back(buff); // кидает в вектор блок субтитров
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

int Get_numcg(int num, string &CG_NUM)
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

void COM(cocos2d::ui::Text* Subtitle, string subfile) // выводит субтитры из векторов на экран 
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
	temp.open("./Resources/Wiki.txt", ios::binary);
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
				System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
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
					System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
					Wiki_Menu->setVisible(false);
					Top_Line->setVisible(false);//и убрать фон и название слоя
					Name_Layer->setVisible(false);
					Mus->setTouchEnabled(true);
					Alb->setTouchEnabled(true);
					Wiki->setTouchEnabled(true);
					nump = 0;
					Back->addClickEventListener([=](Ref *)
					{
						System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
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

			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Swich2"], false, All_Volume*System_Volume);
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

			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Swich2"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
		Wiki_Menu->setVisible(false);
		Top_Line->setVisible(false);//и убрать фон и название слоя
		Name_Layer->setVisible(false);
		Mus->setTouchEnabled(true);
		Alb->setTouchEnabled(true);
		Wiki->setTouchEnabled(true);
		nump = 0;
		Back->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
			Bonus_menu->setVisible(false);
			Back_Node->setVisible(false);
			Button_Menu->setVisible(true);
		});
	});

}


void albumset(Node *Bonus_menu, Layer *Button_Menu, Node *Back_Node, vector<string> setcomment, vector<string> setsub, vector<string> setCG)
{


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

	//char *CG_NUM = new char[(setCG[setCG.size() - 1]).length() + 1]; // создает переменную по размеру string последнего элемента вектора, незабуть потом удалить переменную которой выделена память 
	//strcpy(CG_NUM, string(setCG[setCG.size() - 1]).c_str()); //копирует все элементы последнего элемента вектора

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
				System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
				Scrol->setVisible(false);
				Back_Line->setVisible(false);
				Top_Line->setVisible(false);
				Name_Layer->setVisible(false);
				Album_CG->setVisible(true);
				Image_set->Sprite::setTexture(setCG[z]);
				//char *buff1 = new char[setcomment[a].length() + 1];
				//char *buff2 = new char[setcomment[a + 1].length() + 1];
				//char *buff3 = new char[setsub[a].length() + 1];
				//char *buff4 = new char[setsub[a + 1].length() + 1];
				//strcpy(buff1, setcomment[a].c_str());
				//strcpy(buff2, setcomment[a + 1].c_str());
				//strcpy(buff3, setsub[a].c_str());
				//strcpy(buff4, setsub[a + 1].c_str());

				string buff1 = setcomment[a];
				string buff2 = setcomment[a + 1];
				string buff3 = setsub[a];
				string buff4 = setsub[a + 1];


				Back->addClickEventListener([=](Ref *)
				{
					if (nump > 0)
					{
						nump--;
					}
					cocos2d::experimental::AudioEngine::stop(Voice_id);
					Subtitle->setString("");
					System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
					Album_CG->setVisible(false);
					Scrol->setVisible(true);
					Back_Line->setVisible(true);
					Top_Line->setVisible(true);
					Name_Layer->setVisible(true);
					Back->addClickEventListener([=](Ref *)
					{
						System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
						Album_menu->setVisible(false);
						Top_Line->setVisible(false);//и убрать фон и название слоя
						Name_Layer->setVisible(false);
						Mus->setTouchEnabled(true);
						Alb->setTouchEnabled(true);
						Wiki->setTouchEnabled(true);
						if (Musalb == false)
						{
							Back_Node->stopAllActions();
							cocos2d::experimental::AudioEngine::stop(Background_id);
							Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR["oRE No IMoUTo"], true, All_Volume*Background_Volume);
							
						}
						Back->addClickEventListener([=](Ref *)
						{
							System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
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
					num_z = Get_numcg(n, INDEX_CG); //идет определение текущей картинки
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

						System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume); //далее повтор тех же иницилизаций что и сверху
						Image_set->Sprite::setTexture(setCG[num_z]);

						//char *buff1 = new char[setcomment[num_a].length() + 1];
						//char *buff2 = new char[setcomment[num_a + 1].length() + 1];
						//char *buff3 = new char[setsub[num_a].length() + 1];
						//char *buff4 = new char[setsub[num_a + 1].length() + 1];
						//strcpy(buff1, setcomment[num_a].c_str());
						//strcpy(buff2, setcomment[num_a + 1].c_str());
						//strcpy(buff3, setsub[num_a].c_str());
						//strcpy(buff4, setsub[num_a + 1].c_str());
						string buff1 = setcomment[a];
						string buff2 = setcomment[a + 1];
						string buff3 = setsub[a];
						string buff4 = setsub[a + 1];

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
					num_z = Get_numcg(n, INDEX_CG);
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

						System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
						Image_set->Sprite::setTexture(setCG[num_z]);

						//char *buff1 = new char[setcomment[num_a].length() + 1];
						//char *buff2 = new char[setcomment[num_a + 1].length() + 1];
						//char *buff3 = new char[setsub[num_a].length() + 1];
						//char *buff4 = new char[setsub[num_a + 1].length() + 1];
						//strcpy(buff1, setcomment[num_a].c_str());
						//strcpy(buff2, setcomment[num_a + 1].c_str());
						//strcpy(buff3, setsub[num_a].c_str());
						//strcpy(buff4, setsub[num_a + 1].c_str());
						string buff1 = setcomment[a];
						string buff2 = setcomment[a + 1];
						string buff3 = setsub[a];
						string buff4 = setsub[a + 1];
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
		switch (INDEX_CG[n])//расчет z по значению CG_NUM
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
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
			Album_menu->setVisible(false);
			Top_Line->setVisible(false);//и убрать фон и название слоя
			Name_Layer->setVisible(false);
			Mus->setTouchEnabled(true);
			Alb->setTouchEnabled(true);
			Wiki->setTouchEnabled(true);
			if (Musalb == false)
			{
				Back_Node->stopAllActions();
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR["oRE No IMoUTo"], true, All_Volume*Background_Volume);
			}
			Back->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
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


		char *Mus_Directory[] = { "oRE No IMoUTo", "GOOD MORNiNG", "Immediate Approach", "SOFT BREEZEEEEE",
			"Merry Go Round", "Roller Coaster", "downpour", "Ferris wheel", "STONiSHMENT HOUSE",
			"After a storm comes a calm", "street performer", "Real Substantiality", "rendezvous", "AKiHABARA,CHiYODA-KU",
			"Super Approach!!", "DESTROY GAME STORY", "SECRET x 2", };

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
				Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR[temp], true, All_Volume*Background_Volume);
			});
		}

		if (Mus2)
		{
			char *temp = Mus_Directory[nump + 1];
			Mus2->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR[temp], true, All_Volume*Background_Volume);
			});
		}

		if (Mus3)
		{
			char *temp = Mus_Directory[nump + 2];
			Mus3->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR[temp], true, All_Volume*Background_Volume);
			});
		}

		if (Mus4)
		{
			char *temp = Mus_Directory[nump + 3];
			Mus4->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR[temp], true, All_Volume*Background_Volume);
			});
		}

		if (Mus5)
		{
			char *temp = Mus_Directory[nump + 4];
			Mus5->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR[temp], true, All_Volume*Background_Volume);
			});
		}

		if (Mus6)
		{
			char *temp = Mus_Directory[nump + 5];
			Mus6->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR[temp], true, All_Volume*Background_Volume);
			});
		}

		if (Mus7)
		{
			char *temp = Mus_Directory[nump + 6];
			Mus7->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR[temp], true, All_Volume*Background_Volume);
			});
		}

		if (Mus8)
		{
			char *temp = Mus_Directory[nump + 7];
			Mus8->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR[temp], true, All_Volume*Background_Volume);
			});
		}

		if (Mus9)
		{
			char *temp = Mus_Directory[nump + 8];
			Mus9->addClickEventListener([=](Ref *)
			{
				cocos2d::experimental::AudioEngine::stop(Background_id);
				Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR[temp], true, All_Volume*Background_Volume);
			});
		}

	});

	

	if (Down)
	{
		Down->addClickEventListener([=](Ref *)
		{

			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Swich2"], false, All_Volume*System_Volume);
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

			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Swich2"], false, All_Volume*System_Volume);
			if (nump > 0 && nump != 0)
			{
				nump--;
				update_button_info();
			}
		});
	}

	Back->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
		Back_Node->stopAllActions();
		cocos2d::experimental::AudioEngine::stop(Background_id);
		Background_id = cocos2d::experimental::AudioEngine::play2d(MUSIC_DIR["oRE No IMoUTo"], true, All_Volume*Background_Volume);// включение музыки при выходе из музыкального меню
		nump = 0;
		Music_Menu->setVisible(false);
		Top_Line->setVisible(false);//и убрать фон и название слоя
		Name_Layer->setVisible(false);
		Mus->setTouchEnabled(true);
		Alb->setTouchEnabled(true);
		Wiki->setTouchEnabled(true);
		Back->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
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

	Show_Menu_Sprite->setTexture("Resource\\Buttons\\Game\\strelochkav.png");
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

	Show_Menu_Sprite->setTexture("Resource\\Buttons\\Game\\strelochka.png");
	Auto_Mode_Button->setVisible(false);
	Auto_Mode_Sprite->setVisible(false);
	Game_Menu_Button->setVisible(false);
	Skip_Mode_Button->setVisible(false);
	Show_Menu_Button->addClickEventListener([=](Ref *)
	{
		Show_Menu(Game_Mode);
	});
}


// CREATOR
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




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
Node *OREL = nullptr;
Node *ORER = nullptr;
Node *OREU = nullptr;
Node *AUDIONODE = nullptr;
ui::Button *SWICHMODE = nullptr;
ui::Button *BUTTONCLICK = nullptr;
Sprite *BLACK_SORITE_MODE = nullptr;

ui::Text *Label_text = nullptr;
ui::Text *Label_name = nullptr;

//Node *LIVE2D_NODE_COCOS = nullptr;//созданная нода в кокос сцене
Node *LIVE2D_NODE_CREATE = nullptr;//созданная нода в LIVE2d объекте
Node *Black_screen = nullptr;
Node *Polos_screen = nullptr;


/// текущее  - решил звуки как и озвучку сделать в режими автовставки
//////////// сделать объекты звуков - осталось добавить простой выбор музыки и директории всех звуков в массив
//////////// подготовить игровую облость в поностаящему игровую - переход в нее из креатора и обратно
////////////  функцию воспроизведения страничек в игровой облости
///мограние и голос в такты 
//функция скипа(проигрыш всего без задержек) функция журнала функция авточтения функция прочитанного текста и нового текста
//добавить создание тушот сцен в креатор (это функции облочков и функции работы с модельками LIVE2d)
///функции вставки по середине действий, боксов, и страниц


namespace pre_save
{
	

	any_enum::open_resurce pre_ore_data[any_enum::size_ore];
	int POINTS[any_enum::size_chapter];

	bool ORE_LEFT_VIS = false;// видивость /// TODO - настроить изменение видимостей в оре или экшонах - пока что не изменяема false
	bool ORE_RIGHT_VIS = false;
	bool ORE_LEFT_PREUSE = false;//навели глянули что это
	bool ORE_RIGHT_PREUSE = false;
	bool ORE_LEFT_USE = false;//приняли - заюзали больше выбор отменить нельзя(только загрузкой через меню или бек лог)
	bool ORE_RIGHT_USE = false;
	
	void clear_vis_ore() //*** если пригодится сброс не только после загрузки скрипта но и по середине скрипта - можно сделать внешную обертку сброса всего
	{
		ORE_LEFT_VIS = false;// видивость
		ORE_RIGHT_VIS = false;
		ORE_LEFT_PREUSE = false;//навели глянули что это
		ORE_RIGHT_PREUSE = false;
		ORE_LEFT_USE = false;//приняли - заюзали больше выбор отменить нельзя(только загрузкой через меню или бек лог)
		ORE_RIGHT_USE = false;
	}

	void clear_new_game()//нужно для начала новой игры - данные из основного сейва по разблокированным оре здесь не учитываются
	{
		clear_vis_ore();
		memset(POINTS, NULL, any_enum::size_chapter);
		for (int n = 0; n < any_enum::size_ore; n++)
		{
			pre_ore_data[n] = any_enum::lock;
		}
	}
}

void chek_ore_lock(int cur_ore)//изменяет закрытость на оре данных
{
	if (cur_ore < any_enum::size_ore)
	{
		if (pre_save::pre_ore_data[cur_ore] == any_enum::lock)
			pre_save::pre_ore_data[cur_ore] = any_enum::unlock;
	}
	else
	{
		MessageBox("Неизвестный номер ORE chek_ore_lock", "Ошибка");
	}
}

void action_ore(any_enum::posicion_sprite cur_pos, type_action cur_action)
{

	if (cur_pos == any_enum::left)
	{
		if (cur_action == SHOW_BOX)
			pre_save::ORE_LEFT_VIS = true;
		else if (cur_action == HIDE_BOX)
		{
			pre_save::ORE_LEFT_VIS = false;
			pre_save::ORE_LEFT_PREUSE = false;
		}
	}

	if (cur_pos == any_enum::right)
	{
		if (cur_action == SHOW_BOX)
			pre_save::ORE_RIGHT_VIS = true;
		else if (cur_action == HIDE_BOX)
		{
			pre_save::ORE_RIGHT_VIS = false;
			pre_save::ORE_RIGHT_PREUSE = false;
		}
	}
}

bool get_vis_ore(Node *ore)//получает данные нажата ли была оре
{
	if (ore == OREL)
	{
		return pre_save::ORE_LEFT_USE;
	}
	else if (ore == ORER)
	{
		return pre_save::ORE_RIGHT_USE;
	}
	else
	{
		MessageBox("Неизвестное ORE! get_vis_ore", "Ошибка");
	}
}

void clear_vis_ore(Node *ore)// чистит нажатия на правые или левые оре
{
	if (ore == OREL)
	{
		pre_save::ORE_LEFT_USE = false;
	}
	else if (ore == ORER)
	{
		pre_save::ORE_RIGHT_USE = false;
	}
	else
	{
		MessageBox("Неизвестное ORE! clear_vis_ore", "Ошибка");
	}
}



bool check_point(any_enum::name_sprite name, int point)
{
	int cur_index = static_cast<int>(name);
	
	if (cur_index < any_enum::size_chapter)
	{
		if (pre_save::POINTS[cur_index])
			return true;
	}
	else
	{
		MessageBox("Неизвестный персонаж! check_point", "Ошибка");
	}
	
	return false;
}

bool check_all_ore(any_enum::open_resurce *ore_data, int size)
{
	if (size < any_enum::size_ore)
		return false;

	for (int n = 0; n < any_enum::size_ore; n++)
	{
		if (ore_data[n] == any_enum::unlock && pre_save::pre_ore_data[n] == any_enum::lock)
		{
			return false;
		}
	}
	return true;
}


int string_to_int(std::string temp)
{
	std::stringstream buff;
	buff << temp;
	int complete;
	buff >> complete;
	return complete;
}

struct data_obj
{
	type_struct::type_object my_type = type_struct::none;
	type_interactions my_inter = unknown;
	type_swich my_swich = SIMPLE;
	type_action my_action = UNKNOWN_ACTION;
	any_enum::name_sprite my_name = any_enum::NONE;
	any_enum::posicion_sprite my_position = any_enum::centr;
	string data1 = "";
	string data2 = "";
	string data3 = "";
	bool hide = false;

};

struct page_obj
{
	int cur_box_count = NULL;// количество боксов
	map<int, int> cur_row_count; //количество дейсвий по номеру бокса

	int cur_box_smeh = NULL; //смещает данные бокса по их количеству сейчас все настроено на смещение влево на один при добовлении более 3 коробок передвижение по ним нет
	map<int, int> cur_row_smeh; //относительно текущего бокса говорит какое сейчас будет смещение в рядах

	array<bool, 3> visable_id_box = { { false, false, false } };// Видимость боксов 

	///////////BOX//////ROW////VISIBLE/////
	map <int, map<int, bool>> visable_id_button; //получение по номеру бокса и номеру ряда информацию о видимости кнопок в полях

	///////////BOX//////ROW////DATA/////
	map<int, map<int, data_obj>> intedex_data; //получение по номеру бокса и номеру ряда информацию текущей ячейки
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
//vector<Page*> all_pages; //сюда пихаю все страницы
Page* selected_page = nullptr;

int cur_page = NULL; //текущая страница
int cur_page_count = NULL; //количество страниц
int cur_page_smeh = NULL; //смещение для перехода по страничкам

map<int, page_obj*> cur_page_data;  // хранит разобранную инфу страниц

static data_obj *creator_obj = nullptr;//текущий выбранный объект

bool lock_creator_action = false; //при тру блочит ВСЕ взаимодействия с интерфейсом редактора
bool swap_mode = false; //при тру заменият перемещение по ячейкам на свап

Vec2 ANCHOR_POINT_SPRITE_NODE(Vec2::ANCHOR_MIDDLE);//позиция ноды спрайтов
Vec2 ANCHOR_POINT_SPRITE_ELEMENT(Vec2::ANCHOR_MIDDLE_TOP);//позиции элементов

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
////////////////////////////////////////////////


//ПОДРОБНЕЙ РАСПИСАТЬ СПРАЙТЫ НА БАЙТЫ - при нуле будут ошибки в лоаде
//ПРИ СЕЙВЕ СДЕЛАТЬ ЛОГ А ТАКЖЕ СДЕЛАТЬ ВЫХОДНОЙ ФАЙЛ ДЛЯ ВСТАВКИ ТЕКСТА
#define LOG_SAVE
#define LOG_LOAD



void init_game_mode(Node *Creator_Mode);
void init_creator_mode(Node *Creator_Mode);

int save_script();
int load_script(std::string custom_dir);
bool load_script_exept(std::string dir = "");
bool file_winapi(wchar_t *file_dir, size_t size, bool load = false);

void init_creator_mode(Node *Creator_Mode)
{
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

	OREL = Game_Mode->getChildByTag(516);
	ORER = Game_Mode->getChildByTag(517);
	OREU = Game_Mode->getChildByTag(518)->getChildByTag(111);
	AUDIONODE = Game_Mode->getChildByTag(854);
	Label_text = static_cast<ui::Text*>(Game_Mode->getChildByTag(4534));
	Label_name = static_cast<ui::Text*>(Game_Mode->getChildByTag(4533));
	
	Sprite1->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);
	Sprite2->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);
	Sprite3->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);
	Sprite4->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);
	Sprite5->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);
	Sprite6->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);

	auto axis([=](Node *sprite_h) 
	{
		auto image_s = static_cast<Sprite*>(sprite_h->getChildByName("Sprite"));
		image_s->setAnchorPoint(ANCHOR_POINT_SPRITE_ELEMENT);
		//image_s = static_cast<Sprite*>(sprite_h->getChildByName("Blink"));
		//image_s->setAnchorPoint(ANCHOR_POINT_SPRITE_ELEMENT);
		//image_s = static_cast<Sprite*>(sprite_h->getChildByName("Speak"));
		//image_s->setAnchorPoint(ANCHOR_POINT_SPRITE_ELEMENT);
	});
	axis(Sprite1);
	axis(Sprite2);
	axis(Sprite3);
	axis(Sprite4);
	axis(Sprite5);
	axis(Sprite6);
	

	//COCOS
	//LIVE2D_NODE_COCOS = Game_Mode;// не работает с втсроеной ну - создал такуюже как спрайт
	//LIVE2D_NODE_COCOS
	Black_screen = Game_Mode->getChildByName("Black_screen");
	Polos_screen = Game_Mode->getChildByName("Polos_screen");
	//LIVE2D_NODE_COCOS->setLocalZOrder(Sprite1->getLocalZOrder());

	

	//LIVE2D MODEL NODE INIT PRESET
	LIVE2D_NODE_CREATE = LAppView::createDrawNode();

	SWICHMODE->setTitleText("GAMEMODE");
	SWICHMODE->addClickEventListener([=](Ref*)
	{
		init_game_mode(Creator_Mode);
	});


	LIVE2D_NODE_CREATE->setLocalZOrder(1);
	Sprite1->setLocalZOrder(1);
	Sprite2->setLocalZOrder(1);
	Sprite3->setLocalZOrder(1);
	Sprite4->setLocalZOrder(1);
	Sprite5->setLocalZOrder(1);
	Sprite6->setLocalZOrder(1);

	Polos_screen->setLocalZOrder(4);
	Black_screen->setLocalZOrder(4);
	Text_Box->setLocalZOrder(5);
	
}

void MAINBOX::creatorset()
{
	this->removeAllChildrenWithCleanup(true); //удаление всей логики головного файла
	this->removeAllComponents();
	
	Node *Creator_Mode = CSLoader::createNode("Resources\\All_Scene_cocos\\Creator_scene\\Creator_scene.csb");
	this->addChild(Creator_Mode, 0);




	pre_save::clear_new_game();//нужно для начала новой игры

	SWICHMODE = static_cast<ui::Button*>(Creator_Mode->getChildByTag(1530));//управляет текущем состоянием креатора - создание страниц или игровой проигрышь
	BLACK_SORITE_MODE = static_cast<Sprite*>(Creator_Mode->getChildByTag(7238));
	BUTTONCLICK = static_cast<ui::Button*>(Creator_Mode->getChildByTag(3028)->getChildByTag(2647));
	

	init_creator_mode(Creator_Mode);


	static Sprite *Selector_page = static_cast<Sprite*>(Creator_Mode->getChildByTag(1331));//квадратики выбора объектов для удобства
	static Sprite *Selector_box = static_cast<Sprite*>(Creator_Mode->getChildByTag(2111));
	static Sprite *Selector_row = static_cast<Sprite*>(Creator_Mode->getChildByTag(1173));
	static ui::Button* SWAPMODE = static_cast<ui::Button*>(Creator_Mode->getChildByTag(2112));

	static ui::Button *PAGES[3] =
	{
		static_cast<ui::Button*>(Creator_Mode->getChildByTag(2122)),
		static_cast<ui::Button*>(Creator_Mode->getChildByTag(2123)),
		static_cast<ui::Button*>(Creator_Mode->getChildByTag(2124))
	};

	static bool visable_id_page[3] = { false, false, false };

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

	ui::Button *id_button_box_next = static_cast<ui::Button*>(Creator_Mode->getChildByTag(181)); //прокрутка по страничкам вперед
	ui::Button *id_button_box_prev = static_cast<ui::Button*>(Creator_Mode->getChildByTag(180)); //прокрутка по боксам назад

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

	static ui::Button *id_button_row_swich[3][2]
	{
		{
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(1)->getChildByTag(101)),//вниз ряды
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(1)->getChildByTag(100))//вверх ряды
		},
		{
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(2)->getChildByTag(101)),//вниз ряды
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(2)->getChildByTag(100))//вверх ряды
		},
		{
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(3)->getChildByTag(101)),//вниз ряды
			static_cast<ui::Button*>(Creator_Mode->getChildByTag(3)->getChildByTag(100))//вверх ряды
		}
	};

	static map <ui::Button*, data_obj*> data_obj_id_button //привязка стуктур для созданий объектов к кнопкам
	{
		{ id_button[0][0], nullptr }, { id_button[0][1], nullptr }, { id_button[0][2], nullptr }, { id_button[0][3], nullptr },
		{ id_button[1][0], nullptr }, { id_button[1][1], nullptr }, { id_button[1][2], nullptr }, { id_button[1][3], nullptr },
		{ id_button[2][0], nullptr }, { id_button[2][1], nullptr }, { id_button[2][2], nullptr }, { id_button[2][3], nullptr },
	};

	static ui::Button *play_page = static_cast<ui::Button*>(Creator_Mode->getChildByTag(14758));
	static ui::Button *SAVE_ALL_PAGE = static_cast<ui::Button*>(Creator_Mode->getChildByTag(159753)); // Сохранение скрипта
	static ui::Button *LOAD_ALL_PAGE = static_cast<ui::Button*>(Creator_Mode->getChildByTag(138)); //Загрузка скрипта
	static ui::Button *CLEAR_PAGE = static_cast<ui::Button*>(Creator_Mode->getChildByTag(99989)); // отчистка сцены
	static const int predel_choise = 16;
	static Node *choises[predel_choise]//ноды выборов и настроек
	{
		Creator_Mode->getChildByTag(90), // choise type BOX (sprite, scene, text.....)
			Creator_Mode->getChildByTag(91),
			Creator_Mode->getChildByTag(92),
			Creator_Mode->getChildByTag(93),
			Creator_Mode->getChildByTag(94),
			Creator_Mode->getChildByTag(95), //interact text
			Creator_Mode->getChildByTag(96), // action text(textbox)
			Creator_Mode->getChildByTag(97), // swich text
			Creator_Mode->getChildByTag(98), // action ore
			Creator_Mode->getChildByTag(99), // открытие окна выбора оре, выбор из 64 оре в качестве вызова
			Creator_Mode->getChildByTag(100), // выбор позиции вызываемого оре
			Creator_Mode->getChildByTag(101), // выбор условия выполнения бокса, скипает при провале проверки
			Creator_Mode->getChildByTag(102), // выбор звук это или музыка
			Creator_Mode->getChildByTag(103), //список музыки
			Creator_Mode->getChildByTag(104),// inter teleport
			Creator_Mode->getChildByTag(105) //inter live2d
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//HEAD (Scene, Sprite)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static ui::Button *type_obj_choise[]//тип объекта
	{
		static_cast<ui::Button*>(choises[0]->getChildByTag(1)), //SCENE
			static_cast<ui::Button*>(choises[0]->getChildByTag(2)), //SPRTITE
			static_cast<ui::Button*>(choises[0]->getChildByTag(4)), //TEXT
			static_cast<ui::Button*>(choises[0]->getChildByTag(5)), //ORE
			static_cast<ui::Button*>(choises[0]->getChildByTag(7)), //CONDITION
			static_cast<ui::Button*>(choises[0]->getChildByTag(3)), //AUDIO
			static_cast<ui::Button*>(choises[0]->getChildByTag(6)), //TELEPORT
			static_cast<ui::Button*>(choises[0]->getChildByTag(8)) // MODEL LIVE2D
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
	static ui::Button *swich_scene_choise[2]// надстройки свича сцены
	{
		static_cast<ui::Button*>(choises[2]->getChildByTag(1)), //кнопка выбора BG
		static_cast<ui::Button*>(choises[2]->getChildByTag(2)) //кнопка выбора CG
	};

	static ui::Button *swich_scene_type_swich[2]
	{
		static_cast<ui::Button*>(choises[2]->getChildByTag(4)),// обычный свич
		static_cast<ui::Button*>(choises[2]->getChildByTag(6))// жалюзи свич
	};

	static auto swich_scene_resource = static_cast<ui::Text*>(choises[2]->getChildByTag(99896));// данные о выбранной картинки объекта сцецы

	static auto Selection_BG = Creator_Mode->getChildByTag(1728); //нода со всеми BG
	static auto Selection_CG = Creator_Mode->getChildByTag(1811); //нода со всеми CG
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ACTION
	static ui::Button *action_scene_choise[11]// надстройки свича сцены
	{
			static_cast<ui::Button*>(choises[3]->getChildByTag(1)), //тряска
			static_cast<ui::Button*>(choises[3]->getChildByTag(2)), //One punch
			static_cast<ui::Button*>(choises[3]->getChildByTag(3)), // Чернота IN
			static_cast<ui::Button*>(choises[3]->getChildByTag(4)), //Чернота OUT
			static_cast<ui::Button*>(choises[3]->getChildByTag(5)), // Жалюзи IN
			static_cast<ui::Button*>(choises[3]->getChildByTag(6)), // Жалюзи OUT
			static_cast<ui::Button*>(choises[3]->getChildByTag(7)), //Горизонтальный IN
			static_cast<ui::Button*>(choises[3]->getChildByTag(8)), //Горизонтальный OUT
			static_cast<ui::Button*>(choises[3]->getChildByTag(9)), //Вертикальный IN
			static_cast<ui::Button*>(choises[3]->getChildByTag(10)),	//Вертикальный OUT
			static_cast<ui::Button*>(choises[3]->getChildByTag(11))//convert max prior
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SPRITE BOX

	static auto Selection_SP = Creator_Mode->getChildByTag(37881);//нода созлания спрайта и его превью

	static auto swich_sprite_creator_srite_button = static_cast<ui::Button*>(choises[4]->getChildByTag(1));//кнопка вызова Selection_SP

	static ui::Button *swich_sprite_choise_chater[11]// выбор персонажа (типа) спрайта
	{
		static_cast<ui::Button*>(Selection_SP->getChildByTag(1)), // AY
			static_cast<ui::Button*>(Selection_SP->getChildByTag(2)), // DA
			static_cast<ui::Button*>(Selection_SP->getChildByTag(3)), // KI
			static_cast<ui::Button*>(Selection_SP->getChildByTag(4)), // AK
			static_cast<ui::Button*>(Selection_SP->getChildByTag(5)), // KA
			static_cast<ui::Button*>(Selection_SP->getChildByTag(6)), // KU
			static_cast<ui::Button*>(Selection_SP->getChildByTag(7)), // MA
			static_cast<ui::Button*>(Selection_SP->getChildByTag(8)), // RO
			static_cast<ui::Button*>(Selection_SP->getChildByTag(9)), // SA
			static_cast<ui::Button*>(Selection_SP->getChildByTag(10)), // SE
			static_cast<ui::Button*>(Selection_SP->getChildByTag(11)), // YO

	};

	static auto Sprite_swich_box = static_cast<ui::ScrollView*>(choises[4]->getChildByTag(376)); //скрол надстроек свича
	Sprite_swich_box->setClippingEnabled(true);
	Sprite_swich_box->setClippingType(static_cast<ui::ScrollView::ClippingType>(1));

	static auto Sprite_action_box = static_cast<Node*>(choises[4]->getChildByTag(95)); //нода надстроек экшонов

	//SWICH

	static auto swich_sprite_creator_node = Selection_SP->getChildByTag(36583); // нода создаваемого спрайта (превью спрайта)

	static auto swich_sprite_hide = static_cast<ui::CheckBox*>(Selection_SP->getChildByTag(99999)); //прячется ли спрайт /////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////Пометка, нужна функция обновления состояние с вызовом из смены кнопки

	static ui::Button *swich_sprite_choise_type[]// надстройки свича спрайта
	{
			static_cast<ui::Button*>(Sprite_swich_box->getChildByTag(6)), // Обычный
			static_cast<ui::Button*>(Sprite_swich_box->getChildByTag(7)), // RTL
			static_cast<ui::Button*>(Sprite_swich_box->getChildByTag(8)), // LTR
			static_cast<ui::Button*>(Sprite_swich_box->getChildByTag(9)), // Мгновенно
			static_cast<ui::Button*>(Sprite_swich_box->getChildByTag(10)) // DTT Снизу вверх
	};

	static auto sprite_swich_create_node = Sprite_swich_box->getChildByTag(526); // нода для надстроек позиций и информации о выводимом спрайте если не пропадает а создается новый
	
	static auto sprite_swich_creator_select_type = Selection_SP->getChildByTag(36619);// содержит кнопки вобора типа текстурок
	static auto sprite_swich_creator_select_emotion = Selection_SP->getChildByTag(36618);// содержит кнопки вобора типа эмоций

	static ui::Button * swich_sprite_resource_texture_type[18];

	for (int n = 0; n < 18; n++)
	{
		swich_sprite_resource_texture_type[n] = static_cast<ui::Button*>(sprite_swich_creator_select_type->getChildByTag(n+1));
	}

	static ui::Button * swich_sprite_resource_emotion[19];//все 19 типов эмоций

	for (int n = 0; n < 19; n++)
	{
		swich_sprite_resource_emotion[n] = static_cast<ui::Button*>(sprite_swich_creator_select_emotion->getChildByTag(n + 1));
	}

	static auto swich_sprite_resource_save = static_cast<ui::Button*>(Selection_SP->getChildByTag(37250)); //сохранить данные о спрайте и выйти из окна создания спрайта

	static ui::Button *swich_sprite_choise_position[5]// надстройки положение спрайта
	{
			static_cast<ui::Button*>(sprite_swich_create_node->getChildByTag(9)), // centr
			static_cast<ui::Button*>(sprite_swich_create_node->getChildByTag(10)), // left
			static_cast<ui::Button*>(sprite_swich_create_node->getChildByTag(11)), // left/centr
			static_cast<ui::Button*>(sprite_swich_create_node->getChildByTag(12)), // right
			static_cast<ui::Button*>(sprite_swich_create_node->getChildByTag(13)), // right/centr
	};

	//ACTION

	static ui::Button *action_sprite_choise[]
	{
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(1)), // JUMP
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(2)), // DOUBLE JUMP
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(3)), // Маленький
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(4)), // Средний
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(5)), // Большой
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(6)), //Позиция смещается в центр
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(7)), //влево
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(8)), //влево-ценрт
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(9)), //вправо
			static_cast<ui::Button*>(Sprite_action_box->getChildByTag(10)) //вправо-центр
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//ORE BOX

	static ui::Button *action_ore_choise[3]
	{
		static_cast<ui::Button*>(choises[8]->getChildByTag(1)), // SHOW
			static_cast<ui::Button*>(choises[8]->getChildByTag(2)), // HIDE
			static_cast<ui::Button*>(choises[8]->getChildByTag(3)) // UNLOCK
	};

	static ui::Button *selected_ore_button = static_cast<ui::Button*>(choises[9]->getChildByTag(1)); //выбор картинки оре
	static ui::Text *selected_ore_text = static_cast<ui::Text*>(choises[9]->getChildByTag(2)); //текст который говорит что было выбрано


	static ui::Button *position_ore_choise[2]
	{
		static_cast<ui::Button*>(choises[10]->getChildByTag(1)), // LEFT
			static_cast<ui::Button*>(choises[10]->getChildByTag(2)), // RIGHT
	};

	static Node* Selected_Ore_Node = Creator_Mode->getChildByTag(1878);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CONDITION BOX
	static ui::Button *use_ore_choise[3]
	{
		static_cast<ui::Button*>(choises[11]->getChildByTag(1)), // Правое
			static_cast<ui::Button*>(choises[11]->getChildByTag(2)), // Левое
			static_cast<ui::Button*>(choises[11]->getChildByTag(3)) // Никакое
	};

	static ui::Button *condition_ore_button = static_cast<ui::Button*>(choises[11]->getChildByTag(4));


	static ui::Button *chapter_condition_choise[11]
	{
			static_cast<ui::Button*>(choises[11]->getChildByTag(5)), // KI
			static_cast<ui::Button*>(choises[11]->getChildByTag(6)), // AY
			static_cast<ui::Button*>(choises[11]->getChildByTag(7)), // DA
			static_cast<ui::Button*>(choises[11]->getChildByTag(8)), // AK
			static_cast<ui::Button*>(choises[11]->getChildByTag(9)), // KA
			static_cast<ui::Button*>(choises[11]->getChildByTag(10)), // KU
			static_cast<ui::Button*>(choises[11]->getChildByTag(11)), // MA
			static_cast<ui::Button*>(choises[11]->getChildByTag(12)), // SA
			static_cast<ui::Button*>(choises[11]->getChildByTag(13)), // SE
			static_cast<ui::Button*>(choises[11]->getChildByTag(14)), // YO
			static_cast<ui::Button*>(choises[11]->getChildByTag(15)) // NONE
	};


	static ui::Button *chapter_condition_point = static_cast<ui::Button*>(choises[11]->getChildByTag(324));
	static auto *chapter_condition_point_label = static_cast<ui::TextField*>(choises[11]->getChildByTag(323));

	static Node* Condition_Ore_Node = Creator_Mode->getChildByTag(463);

	static ui::Button *Condition_Ore_Button = static_cast<ui::Button*>(Condition_Ore_Node->getChildByTag(3882));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//TEXT BOX

	static ui::Button *intr_text_choise[2]//тип взаимодействия с текстом(управляем фоном текста или самим текстом)
	{
		static_cast<ui::Button*>(choises[5]->getChildByTag(1)), //TEXTBOX
			static_cast<ui::Button*>(choises[5]->getChildByTag(2))  //TEXT
	};

	//ACTION

	static ui::Button *action_text_choise[2]
	{
		static_cast<ui::Button*>(choises[6]->getChildByTag(1)), // SHOW
			static_cast<ui::Button*>(choises[6]->getChildByTag(2)) // HIDE
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//AUDIO BOX

	static ui::Button *choise_audio_music = static_cast<ui::Button*>(choises[12]->getChildByTag(1));
	static ui::Button *choise_audio_sound = static_cast<ui::Button*>(choises[12]->getChildByTag(2));

	static ui::ListView *choise_music_dirs = static_cast<ui::ListView*>(choises[13]->getChildByTag(1153));
	choise_music_dirs->setClippingEnabled(true);
	choise_music_dirs->setClippingType(static_cast<ui::ListView::ClippingType>(1));

	//static ui::TextField *text_audio_dir = static_cast<ui::TextField*>(choises[13]->getChildByTag(1));
	//static ui::Button *get_audio_dir = static_cast<ui::Button*>(choises[13]->getChildByTag(2));
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//TELEPORT BOX
	static ui::Button *choise_teleport_page = static_cast<ui::Button*>(choises[14]->getChildByTag(1));
	static ui::Button *choise_teleport_script = static_cast<ui::Button*>(choises[14]->getChildByTag(2));


	static auto *choise_teleport_page_node = (choises[14]->getChildByTag(3));
	static ui::Button *choise_teleport_page_button = static_cast<ui::Button*>(choise_teleport_page_node->getChildByTag(1));
	static ui::TextField *choise_teleport_page_edit = static_cast<ui::TextField*>(choise_teleport_page_node->getChildByTag(2));

	static auto *choise_teleport_script_node = (choises[14]->getChildByTag(4));
	static ui::Button *choise_teleport_script_button = static_cast<ui::Button*>(choise_teleport_script_node->getChildByTag(1));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// LIVE2D BOX


	//TEXT BOX
	static ui::Button *intr_live2d_choise[2]//тип взаимодействия с моднлькой(изменяем модельку или делаем какие то взаимодействия)
	{
		static_cast<ui::Button*>(choises[15]->getChildByTag(1)), //Swich
		static_cast<ui::Button*>(choises[15]->getChildByTag(2))  //Action
	};


	//Swich
	static ui::Button *intr_live2d_choise_switch = static_cast<ui::Button*>(choises[15]->getChildByTag(3));


	static auto Selection_LIVE2D = Creator_Mode->getChildByTag(34312);//нода созлания LIVE2D модели и его превью

	auto LIVE2D_HOME = ([=]()
	{
		LIVE2D_CREATE::scep_live2d(Game_Mode);
	});

	LIVE2D_HOME();
	//LIVE2D_CREATE::init_model(1, 1);


	static ui::Button *live2d_choise_chater[]// выбор персонажа (модель) 
	{
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(1)), // AY
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2)), // KI
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(3)), // KA
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(4)), // KU
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(5)), // MA
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(6)), // SA
	};

	static ui::Button *live2d_choise_texture[]// выбор текстуры модели
	{
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2415)->getChildByTag(1)), // 1
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2415)->getChildByTag(2)), // 2
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2415)->getChildByTag(3)), // 3
	};


	//кнопки отвечающие за настройку конкретного expression
	static ui::Button* live2d_expressions_select[]
	{ 
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2394)->getChildByTag(1)),//_body
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2394)->getChildByTag(2)),//_brow
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2394)->getChildByTag(3)),//_face
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2394)->getChildByTag(4)),//_hands
		static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2394)->getChildByTag(5))//_head
	};

	static ui::Button *live2d_expressions_choise[17];//все возможные варианты одной надстройки(нужно корректировать видимость при каждой)

	for (int n = 0; n < 17; n++)
	{
		live2d_expressions_choise[n] = static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2394)->getChildByTag(2510)->getChildByTag(n+1));
	}

	static ui::Button *live2d_create_ok = static_cast<ui::Button*>(Selection_LIVE2D->getChildByTag(2388));

	static ui::CheckBox *live2d_model_hide = static_cast<ui::CheckBox*>(Selection_LIVE2D->getChildByTag(2386));

	//Live2d Action
	static ui::Button *intr_live2d_choise_action = static_cast<ui::Button*>(choises[15]->getChildByTag(4));

	static ui::Button *live2d_action_choise[] =
	{
		static_cast<ui::Button*>(intr_live2d_choise_action->getChildByTag(1)), // выбор MOTION по имени - ошибку если не выбрали имя
		static_cast<ui::Button*>(intr_live2d_choise_action->getChildByTag(2)), // BIG SCALE
		static_cast<ui::Button*>(intr_live2d_choise_action->getChildByTag(3)), // MID SCALE
		static_cast<ui::Button*>(intr_live2d_choise_action->getChildByTag(4)), // LIT SCALE
	};
	
	static ui::Button *live2d_action_select_chapter[] =
	{
		static_cast<ui::Button*>(intr_live2d_choise_action->getChildByTag(5)),// SA 
		static_cast<ui::Button*>(intr_live2d_choise_action->getChildByTag(6)),// MA
		static_cast<ui::Button*>(intr_live2d_choise_action->getChildByTag(7)),// KU
		static_cast<ui::Button*>(intr_live2d_choise_action->getChildByTag(8)),// KA
		static_cast<ui::Button*>(intr_live2d_choise_action->getChildByTag(9)),// AY
		static_cast<ui::Button*>(intr_live2d_choise_action->getChildByTag(10))// KI
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	auto gpi([=]()
	{
		return cur_page_data[cur_page];
	});

	auto update_ind2([=]()// обновляем лишь специфическую инфу которую нужно сбрасывать между ячейками
	{
		swich_sprite_hide->setSelectedState(false);
		swich_scene_resource->setString("РљР°СЂС‚РёРЅРєР° РЅРµ РІС‹Р±СЂР°РЅР°");
		chapter_condition_point_label->setString("");
		choise_teleport_page_edit->setString("");
		if (creator_obj != nullptr)
		if ((creator_obj->hide == true && creator_obj->my_type == type_struct::sprite) || (creator_obj->hide == true && creator_obj->my_inter == swich))
			swich_sprite_hide->setSelectedState(true);
	}
	);
	auto update_inf([=]() //обновляет все везде где можно
	{
		bool search_obj = false;//выбран какой нить объект
		bool search_page = false; //выбран какая нить страничка

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
			if (cur_page_count != NULL && (cur_page - cur_page_smeh <3) && (cur_page - cur_page_smeh >-1))
			{
				Selector_page->setPosition(PAGES[cur_page - cur_page_smeh]->getPosition() + Vec2{ -10, 0 });
				search_page = true;
			}

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
					BOXS_NAME[n]->setText(to_string(n + gpi()->cur_box_smeh + 1));

					for (int i = 0; i < 4; i++)
					{
						data_obj_id_button[id_button[n][i]] =
							gpi()->intedex_data[n + gpi()->cur_box_smeh].find(i + gpi()->cur_row_smeh[n + gpi()->cur_box_smeh]) !=
							gpi()->intedex_data[n + gpi()->cur_box_smeh].cend() ?
							&gpi()->intedex_data[n + gpi()->cur_box_smeh][i + gpi()->cur_row_smeh[n + gpi()->cur_box_smeh]] : nullptr;//привязываем  (по боксу со смещением бокса)

						if (gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] == false)
						{
							id_button[n][i]->setVisible(false);
						}
						else
						{
							if (creator_obj != nullptr)
							{
								if (creator_obj == (data_obj_id_button[id_button[n][i]]))
								{
									Selector_box->setPosition(BOXS[n]->getPosition() + Vec2{ 30, 100 });
									Selector_row->setPosition(id_button[n][i]->getPosition() + BOXS[n]->getPosition() + Vec2{ -50, 0 });
									search_obj = true;
								}
							}
							id_button[n][i]->setVisible(true);
							string message = "";
							message += to_string(i + gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] + 1); // вывод номера текущего поля
							std::string green_tex = dir_home_creator_tex + "\\But_sli_g.png";
							std::string red_tex = dir_home_creator_tex + "\\But_sli_b.png";
							if (data_obj_id_button[id_button[n][i]] != nullptr)
							{
								switch (data_obj_id_button[id_button[n][i]]->my_type)//много условий на проверку законченности объекта для пользователей красный - недоделан зеленый - готовый
								{
								case type_struct::scene:
									message += " Scene";
									//switch (data_obj_id_button[id_button[n][i]]->my_inter)
									//{
									//case swich:
									//	if (data_obj_id_button[id_button[n][i]]->data1 != "" &&
									//		data_obj_id_button[id_button[n][i]]->data2 != "")
									//		id_button[n][i]->loadTextureNormal(green_tex);
									//	else
									//		id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//case action:
									//	if (data_obj_id_button[id_button[n][i]]->my_action != UNKNOWN_ACTION)
									//		id_button[n][i]->loadTextureNormal(green_tex);
									//	else
									//		id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//default:
									//	id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//}
									break;
								case type_struct::sprite:
									message += " Sprite";
									//switch (data_obj_id_button[id_button[n][i]]->my_inter)
									//{
									//case swich:
									//	if ((data_obj_id_button[id_button[n][i]]->data1 != "" &&
									//		data_obj_id_button[id_button[n][i]]->data2 != "" &&
									//		data_obj_id_button[id_button[n][i]]->data3 != "") || data_obj_id_button[id_button[n][i]]->hide == true)
									//		id_button[n][i]->loadTextureNormal(green_tex);
									//	else
									//		id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//case action:
									//	if (data_obj_id_button[id_button[n][i]]->my_action != UNKNOWN_ACTION)
									//		id_button[n][i]->loadTextureNormal(green_tex);
									//	else
									//		id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//default:
									//	id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//}
									break;
								case type_struct::ore:
									message += " ORE";
									break;
								case type_struct::condition:
									message += " Condi";
									break;
								case type_struct::audio:
									message += " Audio";
									//switch (data_obj_id_button[id_button[n][i]]->my_inter)
									//{
									//case action:
									//	if (data_obj_id_button[id_button[n][i]]->data1 != "" &&
									//		data_obj_id_button[id_button[n][i]]->data2 != "")
									//		id_button[n][i]->loadTextureNormal(green_tex);
									//	else
									//		id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//default:
									//	id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//}
									break;
								case type_struct::text:
									message += " Text";
									//switch (data_obj_id_button[id_button[n][i]]->my_inter)
									//{
									//case swich:
									//	if (data_obj_id_button[id_button[n][i]]->data1 != "")
									//		id_button[n][i]->loadTextureNormal(green_tex);
									//	else
									//		id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//case action:
									//	if (data_obj_id_button[id_button[n][i]]->my_action != UNKNOWN_ACTION)
									//		id_button[n][i]->loadTextureNormal(green_tex);
									//	else
									//		id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//default:
									//	id_button[n][i]->loadTextureNormal(red_tex);
									//	break;
									//}
									break;
								case type_struct::teleport:
									message += " Teleport";

									//if (data_obj_id_button[id_button[n][i]]->data1 != "")
									//	id_button[n][i]->loadTextureNormal(green_tex);
									//else
									//	id_button[n][i]->loadTextureNormal(red_tex);
									//break;
								case type_struct::live2d:
									message += " Live2D";

									//if (data_obj_id_button[id_button[n][i]]->data1 != "" && data_obj_id_button[id_button[n][i]]->data2 != "" && data_obj_id_button[id_button[n][i]]->data3 != "")
									//	id_button[n][i]->loadTextureNormal(green_tex);
									//else
									//	id_button[n][i]->loadTextureNormal(red_tex);
									//break;
								default:
									message += " None";
									//id_button[n][i]->loadTextureNormal(red_tex);
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
									//id_button[n][i]->loadTextureNormal(red_tex);
									break;
								}
								id_button[n][i]->setTitleText(message);
							}
							
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

			auto sprite_creator_off_buttons = ([=]() 
			{
				sprite_swich_creator_select_type->setVisible(false);//нода типа спрайта
				sprite_swich_creator_select_emotion->setVisible(false);//нода типа эмоции
				for (int n = 0; n < 18; n++)
				{
					swich_sprite_resource_texture_type[n]->setVisible(false);//кнопка типа текстурки
				}
				for (int n = 0; n < 19; n++)
				{
					swich_sprite_resource_emotion[n]->setVisible(false);//кнопка типа эмоции
				}
			});

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

						sprite_creator_off_buttons();
						if (creator_obj->my_name != any_enum::NONE)
						{
							Sprite_swich_box->setVisible(true);
							swich_sprite_creator_node->setVisible(false);
							if (creator_obj->hide == false)
							{
								swich_sprite_creator_node->setVisible(true);
								sprite_swich_create_node->setVisible(true);
								sprite_swich_creator_select_type->setVisible(true);//нода типа спрайта
								sprite_swich_creator_select_emotion->setVisible(true);//нода типа эмоции

								auto sprite = static_cast<Sprite*>(swich_sprite_creator_node->getChildByName("Sprite"));
								auto blink = static_cast<Sprite*>(sprite->getChildByName("Blink"));
								auto speak = static_cast<Sprite*>(sprite->getChildByName("Speak"));


								auto init_sprite_obj([=](string cur_capter)
								{
									if (creator_obj->data1 != "" && creator_obj->data2 != "")
									{
										if (SPRITE_DIR[cur_capter].find(creator_obj->data1) != SPRITE_DIR[cur_capter].cend())
										{
											if (SPRITE_DIR[cur_capter][creator_obj->data1][NAME_MAP_SPRITE].find(creator_obj->data2) != SPRITE_DIR[cur_capter][creator_obj->data1][NAME_MAP_SPRITE].cend())
											{
												
												string home_dir = ".\\Resources\\Sprites";												
												string dir_obj = SPRITE_DIR[cur_capter][creator_obj->data1][NAME_MAP_SPRITE][creator_obj->data2];
												sprite->setTexture(home_dir + dir_obj);

												std::array<positions, 3> pos;
												std::string cur_name = Get_name_from_enum(creator_obj->my_name);
												
												pos = search_pos(cur_name, creator_obj->data1);
												Vec2 temp = sprite->getTexture()->getContentSize();//поскольку теперь спрайт смещен - нужно смещать и координаты
												sprite->setPosition(pos[0].x + temp.x/2, pos[0].y + temp.y/2);

												sprite->setVisible(true);

												if (creator_obj->data3 != "" &&//не появилось при возврате к обжу... глянь потом в отладчике
													SPRITE_DIR[cur_capter][creator_obj->data1][NAME_MAP_FACE].find(creator_obj->data3) != SPRITE_DIR[cur_capter][creator_obj->data1][NAME_MAP_FACE].cend())
												{


													string face_dir = SPRITE_DIR[cur_capter][creator_obj->data1][NAME_MAP_FACE][creator_obj->data3];
													blink->setTexture(home_dir + face_dir + SPRITE_BLINK_DIR + SPRITE_BLINK_ANIM_DIR[0]);
													speak->setTexture(home_dir + face_dir + SPRITE_SPEAK_DIR + SPRITE_SPEAK_ANIM_DIR[0]);

													blink->setPosition(pos[1].x, pos[1].y);
													speak->setPosition(pos[2].x, pos[2].y);

													blink->setVisible(true);
													speak->setVisible(true);
												}
												else
												{
													blink->setVisible(false);
													speak->setVisible(false);
												}
											}
										}
									}
									else
									{
										sprite->setVisible(false);
										blink->setVisible(false);
										speak->setVisible(false);
									}
								});

								auto init_emotion_buttons([=](string chapter)
								{
									for (int n = 0; n < 19; n++)
									{
										swich_sprite_resource_emotion[n]->setVisible(false);//нода типа эмоции
										if (SPRITE_DIR[chapter][creator_obj->data1][NAME_MAP_FACE].find(std::to_string(n + 1)) != SPRITE_DIR[chapter][creator_obj->data1][NAME_MAP_FACE].cend())
										{
											swich_sprite_resource_emotion[n]->setVisible(true);//нода типа эмоции
											swich_sprite_resource_emotion[n]->addClickEventListener([=](Ref*)
											{
												creator_obj->data3 = std::to_string(n + 1);
												init_sprite_obj(chapter);
											});
										}
									}
								});



								string cur_capter = Get_name_from_enum(creator_obj->my_name);
								

								init_sprite_obj(cur_capter);

								if (SPRITE_DIR.find(cur_capter) != SPRITE_DIR.cend())
								{
									auto cur_iter = SPRITE_DIR[cur_capter].cbegin();
									for (int n = 0; cur_iter != SPRITE_DIR[cur_capter].cend(); cur_iter++)
									{
										if (n > 17)
											break;
										auto temp = cur_iter->second;
										auto cur_iter2 = temp[NAME_MAP_SPRITE].cbegin();
										for (cur_iter2; cur_iter2 != temp[NAME_MAP_SPRITE].cend(); cur_iter2++, n++)
										{
											if (n > 17)
												break;
											swich_sprite_resource_texture_type[n]->setVisible(true);//кнопка типа текстурки
											swich_sprite_resource_texture_type[n]->setTitleText(cur_iter->first + " " + cur_iter2->first);
											auto cur_num = cur_iter2->first;
											swich_sprite_resource_texture_type[n]->addClickEventListener([=](Ref*)
											{
												creator_obj->data1 = cur_iter->first;
												creator_obj->data2 = cur_num;
												creator_obj->data3 = "";
												init_sprite_obj(cur_capter);
												init_emotion_buttons(cur_capter);
											});
										}
									}
								}
								if (creator_obj->data1 != "" && creator_obj->data2 != "")
								{
									if (SPRITE_DIR[cur_capter].find(creator_obj->data1) != SPRITE_DIR[cur_capter].cend())
									{
										if (SPRITE_DIR[cur_capter][creator_obj->data1][NAME_MAP_SPRITE].find(creator_obj->data2) != SPRITE_DIR[cur_capter][creator_obj->data1][NAME_MAP_SPRITE].cend())
										{
											init_emotion_buttons(cur_capter);
										}
									}
								}
							}
						}
					}
					else if (creator_obj->my_type == type_struct::sprite && creator_obj->my_inter == action)
					{
						choises[4]->setVisible(true);
						sprite_creator_off_buttons();
						if (creator_obj->my_name != any_enum::NONE)
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
				else if (creator_obj->my_type == type_struct::ore)
				{
					choises[8]->setVisible(true);
					if (creator_obj->my_action == SHOW_BOX || creator_obj->my_action == HIDE_BOX)
					{
						choises[9]->setVisible(true);
						if (creator_obj->data1 != "")
							choises[10]->setVisible(true);
					}
					else if (creator_obj->my_action == UNLOCK_ORE)
					{
						choises[9]->setVisible(true);
					}

				}
				else if (creator_obj->my_type == type_struct::condition)
				{
					choises[11]->setVisible(true);
				}
				else if (creator_obj->my_type == type_struct::audio)
				{
					choises[12]->setVisible(true);
					if (creator_obj->data1 != "")
						choises[13]->setVisible(true);
				}
				else if (creator_obj->my_type == type_struct::teleport)
				{
					choises[14]->setVisible(true);
					if (creator_obj->my_inter == swich)
					{
						choise_teleport_page_node->setVisible(true);
						choise_teleport_script_node->setVisible(false);
					}
					else if (creator_obj->my_inter == action)
					{
						choise_teleport_script_node->setVisible(true);
						choise_teleport_page_node->setVisible(false);
					}
					else
					{
						choise_teleport_script_node->setVisible(false);
						choise_teleport_page_node->setVisible(false);
					}
				}
				else if (creator_obj->my_type == type_struct::live2d)
				{
					choises[15]->setVisible(true);
					intr_live2d_choise_switch->setVisible(false);
					intr_live2d_choise_action->setVisible(false);
					if (creator_obj->my_inter == swich)
						intr_live2d_choise_switch->setVisible(true);
					if (creator_obj->my_inter == action)
						intr_live2d_choise_action->setVisible(true);

					if (Selection_LIVE2D->isVisible() == true)
					{
						if (creator_obj->my_name != any_enum::NONE && creator_obj->hide == false)
						{

							int index_model = -1;
							int index_tex = 0;

							switch (string_to_int(creator_obj->data1))
							{
							case 0:
								index_tex = 0;
								break;
							case 1:
								index_tex = 1;
								break;
							case 2:
								index_tex = 2;
								break;
							}

							Get_model_from_name(creator_obj->my_name, index_model, index_tex);

							if (index_model != -1)
							{
								if (LIVE2D_CREATE::check_model_settings(index_model, index_tex) == true)
								{
									LIVE2D_CREATE::init_model(index_model, index_tex);
								}
							}

							if (creator_obj->data3.length() > 0)
							{
								auto arg_vec = Get_ex_vector_from_string(creator_obj->data3);
								if (arg_vec.size() > 0)
									LIVE2D_CREATE::init_expression(arg_vec);

							}
						}
						else
						{
							LIVE2D_CREATE::relese_model();
						}
					}
				}
			}

		}
		if (search_obj == false)
		{
			Selector_row->setPosition(-20, -20);
			if (creator_obj == nullptr)
				Selector_box->setPosition(-20,-20);
		}
		if (search_page == false)
		{
			Selector_page->setPosition(-20, -20);
		}
		if (swap_mode == true)
		{
			SWAPMODE->setTitleText("R");
		}
		else
		{
			SWAPMODE->setTitleText("S");
		}
	});


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// настроел отчитку страниц и боксов - нужна еще отчистка объекта 



	SWICHMODE->addClickEventListener([=](Ref*)
	{
		//init_game_mode(Creator_Mode);
	});




	auto release_cur_page([=](CallFunc *func)
	{
		if (func != nullptr)
		{
			if (selected_page != nullptr)
			{
				static int tag_action = -1;
				Game_Mode->stopAllActions();
				Game_Mode->runAction(RepeatForever::create(Sequence::create(func, DelayTime::create(0.3f), nullptr)));
			}
			else
			{
				return true;
			}
		}
		return false;
	});

	auto StopActionDisplay = ([=]()//не прерывает GAMEMODE - его ручками ручками
	{
	
		Scene1->stopAllActions();
		Scene2->stopAllActions();

		OREL->stopAllActions();// TODO вернуть их на позиции(функция скипа - быстрые экшоны и свичи) тут можно сделать сброс позиций на изначальные того что двигается
		ORER->stopAllActions();
		OREU->stopAllActions();
		OREU->getParent()->stopAllActions();
		ORER->getChildByTag(2)->stopAllActions();
		OREL->getChildByTag(2)->stopAllActions();

		Text_Box->stopAllActions();


		OREU->getParent()->setOpacity(0);//начальное состояние


		Sprite1->stopAllActions();
		Sprite2->stopAllActions();
		Sprite3->stopAllActions();
		Sprite4->stopAllActions();
		Sprite5->stopAllActions();
		Sprite6->stopAllActions();

		auto stop_node_sprite([=](Node* &sprite)
		{
			auto temp_spr = static_cast<Sprite*>(sprite->getChildByName("Sprite"));
			auto temp_bli = static_cast<Sprite*>(temp_spr->getChildByName("Blink"));
			auto temp_spe = static_cast<Sprite*>(temp_spr->getChildByName("Speak"));

			


			if (check_sprite_for_state.find(&sprite) != check_sprite_for_state.end())
			{
				if (check_sprite_for_state[&sprite] == any_enum::FREE && sprite->getOpacity() != 0)
				{
					temp_spr->stopAllActions();
					temp_bli->stopAllActions();
					temp_spe->stopAllActions();
					sprite->setOpacity(0);
					clear_mapani(temp_bli);
					relese_old_state(sprite);
				}
			}
		});


		stop_node_sprite(Sprite1);
		stop_node_sprite(Sprite2);
		stop_node_sprite(Sprite3);
		stop_node_sprite(Sprite4);
		stop_node_sprite(Sprite5);
		stop_node_sprite(Sprite6);
	});


	auto ClearDisplay = ([=]() 
	{
		StopActionDisplay();

		const int x_0_R = 872;//копипаста action ore
		const int y_0 = 43;
		const int x_0_L = 62;




		OREL->setPosition(Vec2(x_0_L, y_0));
		ORER->setPosition(Vec2(x_0_R, y_0));
		pre_save::clear_vis_ore();


		


		static_cast<Sprite*>(Scene1->getChildByName("Sprite"))->setTexture("");
		static_cast<Sprite*>(Scene2->getChildByName("Sprite"))->setTexture("");

		auto clear_node_sprite([=](Node* sprite)
		{
			auto temp_spr = static_cast<Sprite*>(sprite->getChildByName("Sprite"));
			auto temp_bli = static_cast<Sprite*>(temp_spr->getChildByName("Blink"));
			auto temp_spe = static_cast<Sprite*>(temp_spr->getChildByName("Speak"));

			temp_spr->setTexture("");
			temp_bli->setTexture("");
			temp_spe->setTexture("");

			clear_mapani(temp_bli);
			relese_old_state(sprite);

			sprite->setOpacity(0);
		});

		clear_node_sprite(Sprite1);
		clear_node_sprite(Sprite2);
		clear_node_sprite(Sprite3);
		clear_node_sprite(Sprite4);
		clear_node_sprite(Sprite5);
		clear_node_sprite(Sprite6);

		Text_Box->setPosition(Vec2(-380, -60));
	});


	CLEAR_PAGE->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			release_cur_page(
				CallFunc::create([=]()
			{
				if (selected_page->isFinish() == true)
				{
					ClearDisplay();

					delete selected_page;
					selected_page = nullptr;
					Game_Mode->stopAllActions();
				}
			}));
		}
	});

	SAVE_ALL_PAGE->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			switch (save_script())
			{
			case 0:
			{
				MessageBoxA(nullptr, "Сохранение успешно!", "Уведомление", MB_OK);
				break;
			}
			case 1:
			{
				MessageBoxA(nullptr, "Ошибка сохранения!", "Ошибка", MB_OK | MB_ICONERROR);
				break;
			}
			case 2:
			{
				MessageBoxA(nullptr, "Ошибка создания файла!", "Ошибка", MB_OK | MB_ICONERROR);
				break;
			}
			default:
				break;
			}
		}
	});

	auto load_update([=]() 
	{
		visable_id_page[0] = cur_page_count > 0 ? true : false;
		visable_id_page[1] = cur_page_count > 1 ? true : false;
		visable_id_page[2] = cur_page_count > 2 ? true : false;
		
		pre_save::clear_vis_ore();

		ClearDisplay();

		delete selected_page;
		selected_page = nullptr;

		if (cur_page_count > 3)
			cur_page_smeh = cur_page_count - 3;
		else
			cur_page_smeh = 0;

		update_inf();
		update_ind2();
	});

	LOAD_ALL_PAGE->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
				if (load_script_exept() == true)
				{
					load_update();
				}		
		}
	});

	SWAPMODE->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			swap_mode = swap_mode == true ? false : true;
			update_inf();
		}
	});

	id_button_page_plus->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			cur_page_count++;
			cur_page = cur_page_count - 1;
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
		}

	});

	id_button_page_min->addClickEventListener([=](Ref*) 
	{
		if (lock_creator_action == false)
		{
			if (cur_page_count != NULL) // если есть страничка
			{
				cur_page = cur_page_count;
				cur_page_count--;
				if (cur_page_data.find(cur_page) != cur_page_data.cend())
				{
					delete cur_page_data[cur_page]; //удаляет из памяти страницу
					cur_page_data.erase(cur_page_data.find(cur_page));//удаляем ее из мапы
				}
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
		}
	});

	for (int n = 0; n < 3; n++)// для выбора страничек
	{
		PAGES[n]->addClickEventListener([=](Ref*)
		{
			if (lock_creator_action == false)
			{
				cur_page = n + cur_page_smeh; // переход на выбранную страницу
				creator_obj = nullptr; //сброс закрепленной инфы 
				update_inf(); //сброс 
				update_ind2();//фулл сброс
			}
		});
	}

	id_button_page_down->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (cur_page_count != NULL)
			{
				if (swap_mode == true && cur_page_count > 1 && cur_page > 0)
				{
					auto cur_citer = cur_page_data.find(cur_page);
					auto cur_iter2 = cur_page_data.find(cur_page - 1);
					if (cur_citer != cur_page_data.cend() && cur_iter2 != cur_page_data.cend())
					{
						std::swap(cur_citer->second, cur_iter2->second);
						cur_page--;
					}
				}
				if (cur_page_smeh - 1 > -1)
					cur_page_smeh--;
				update_inf(); //сброс 
			}
		}
	});

	id_button_page_up->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (cur_page_count != NULL)
			{
				if (swap_mode == true && cur_page_count > 1 && cur_page + 1 < cur_page_count)
				{
					auto cur_citer = cur_page_data.find(cur_page);
					auto cur_iter2 = cur_page_data.find(cur_page + 1);
					if (cur_citer != cur_page_data.cend() && cur_iter2 != cur_page_data.cend())
					{
						std::swap(cur_citer->second, cur_iter2->second);
						cur_page++;
					}
				}
				if (cur_page_smeh + 3 < cur_page_count)
					cur_page_smeh++;
				update_inf(); //сброс 
			}
		}
	});

	id_button_box_next->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (cur_page_count != NULL)
			{
				//ТЕстовый свап боксов ифой между собой
				if (swap_mode == true && cur_page_count > 0 && cur_page < cur_page_count)
				{
					for (int n = 0; n < gpi()->cur_box_count; n++)//по всем боксам
					{
						auto cur_iter = gpi()->cur_row_count.find(n);//ищем есть ли такой бокс
						if (cur_iter != gpi()->cur_row_count.cend())//если есть
						{
							auto cur_iter2 = gpi()->intedex_data.find(n);//ищем список инфы объектов по боксу
							if (cur_iter2 != gpi()->intedex_data.cend())//елси есть
							{
								auto cur_iter3 = cur_iter2;//делаем копию
								cur_iter3++;//переходим на след бокс
								if (cur_iter3 != gpi()->intedex_data.cend())//чекаем существование следуешего бокса ДЛЯ ОБМЕНА ИНФОРМАЦИЕЙ ЭТИХ БОКСОВ
								{
									auto i = cur_iter2->second.begin();//сохраняем первую инфу объекта во временную переменную
									while (i != cur_iter2->second.cend())//если эта переменная существует
									{
										if (&i->second == creator_obj)//если эта переменная наш выбранный объект
										{//если будут ошибки наставить проверок на конец мап
											swap(cur_iter3->second, cur_iter2->second);//обмениваем инфу в боксах
											swap(cur_iter->second, gpi()->cur_row_count.find(cur_iter3->first)->second);//обмениваем инфу количества объектов в боксах
											swap(gpi()->visable_id_button.find(n)->second, gpi()->visable_id_button.find(cur_iter3->first)->second); //обмениваем инфу видимости кнопочек объектов боксов
											swap(gpi()->cur_row_smeh.find(n)->second, gpi()->cur_row_smeh.find(cur_iter3->first)->second);//обмениваем инфу смещений
											n = gpi()->cur_box_count;//конец цикла
											break;
										}
										i++;
									}
								}
							}
						}
					}
				}
				if (gpi()->cur_box_smeh + 3 < gpi()->cur_box_count)//смещаемся по боксам
					gpi()->cur_box_smeh++;
				update_inf(); //сброс 
			}
		}
	});

	id_button_box_prev->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			//ТЕстовый свап боксов ифой между собой
			if (swap_mode == true && cur_page_count > 0 && cur_page < cur_page_count)
			{
				for (int n = 0; n < gpi()->cur_box_count; n++)//по всем боксам
				{
					auto cur_iter = gpi()->cur_row_count.find(n);//ищем есть ли такой бокс
					if (cur_iter != gpi()->cur_row_count.cend())//если есть
					{
						auto cur_iter2 = gpi()->intedex_data.find(n);//ищем список инфы объектов по боксу
						if (cur_iter2 != gpi()->intedex_data.cend() && cur_iter2 != gpi()->intedex_data.cbegin())//елси есть и не первый
						{
							auto cur_iter3 = cur_iter2;//делаем копию
							cur_iter3--;//переходим на предыдущий бокс
							if (cur_iter3 != gpi()->intedex_data.cend())//чекаем существование следуешего бокса ДЛЯ ОБМЕНА ИНФОРМАЦИЕЙ ЭТИХ БОКСОВ
							{
								auto i = cur_iter2->second.begin();//сохраняем первую инфу объекта во временную переменную
								while (i != cur_iter2->second.cend())//если эта переменная существует
								{
									if (&i->second == creator_obj)//если эта переменная наш выбранный объект
									{//если будут ошибки наставить проверок на конец мап
										swap(cur_iter3->second, cur_iter2->second);//обмениваем инфу в боксах
										swap(cur_iter->second, gpi()->cur_row_count.find(cur_iter3->first)->second);//обмениваем инфу количества объектов в боксах
										swap(gpi()->visable_id_button.find(n)->second, gpi()->visable_id_button.find(cur_iter3->first)->second); //обмениваем инфу видимости кнопочек объектов боксов
										swap(gpi()->cur_row_smeh.find(n)->second, gpi()->cur_row_smeh.find(cur_iter3->first)->second);//обмениваем инфу смещений
										n = gpi()->cur_box_count;//конец цикла
										break;
									}
									i++;
								}
							}
						}
					}
				}
			}

			if (cur_page_count != NULL)
			{
				if (gpi()->cur_box_smeh - 1 > -1)
					gpi()->cur_box_smeh--;
				update_inf(); //сброс
			}
		}
		 
	});

	id_button_box_plus->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (cur_page_count != NULL) // если есть страничка
			{
				if (gpi()->cur_box_count > 2) //если боксов три и больше только смещаем инфу боксов и добавляем новый 
				{
					gpi()->cur_box_count++; //увеличили количество боксов
					gpi()->cur_row_count[gpi()->cur_box_smeh + 3] = NULL; //по смещению иницим колво ячеек
					//for (int i = 0; i < 4; i++)// TODO не знаю но после закоменчивония пропал баг - смотри в бекапы!
					//{
					//	gpi()->visable_id_button[3 + gpi()->cur_box_smeh][i] = false;//обнуляем видимость действий текущего бокса
					//}
					if (gpi()->cur_box_count > 3)
						gpi()->cur_box_smeh = gpi()->cur_box_count - 3;
					else
						gpi()->cur_box_smeh = 0;
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
							if (gpi()->cur_box_count > 3)
								gpi()->cur_box_smeh = gpi()->cur_box_count - 3;
							else
								gpi()->cur_box_smeh = 0;
							update_inf();
							break;
						}
					}
				}

			}
		}
	});

	id_button_box_min->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (cur_page_count != NULL) // если есть страничка
			{
				if (gpi()->cur_box_count > 3) //если боксов больше 3 удаляем только инфу
				{

					auto cur_citer = gpi()->intedex_data.find(3 + gpi()->cur_box_smeh);// отчистка всех действий у бокса 
					if (cur_citer != gpi()->intedex_data.cend())
					{
						gpi()->intedex_data.erase(cur_citer);
					}

					auto cur_citer2 = gpi()->cur_row_count.find(gpi()->cur_box_smeh + 3);
					if (cur_citer2 != gpi()->cur_row_count.cend())
					{
						gpi()->cur_row_count.erase(cur_citer2);
					}
					gpi()->cur_box_count--;

					if (gpi()->cur_box_count > 3)
						gpi()->cur_box_smeh = gpi()->cur_box_count - 3;
					else
						gpi()->cur_box_smeh = 0;
					update_inf();
				}
				else//иначе все тоже самое + видимость бокса
				{
					for (int n = 2; n > -1; n--)// проход по всем боксам обратно
					{
						if (gpi()->visable_id_box[n] == true)
						{
							gpi()->visable_id_box[n] = false;

							auto cur_citer = gpi()->intedex_data.find(n);
							if (cur_citer != gpi()->intedex_data.cend())
							{
								gpi()->intedex_data.erase(cur_citer);
							}
							auto cur_citer2 = gpi()->cur_row_count.find(n);
							if (cur_citer2 != gpi()->cur_row_count.cend())
							{
								gpi()->cur_row_count.erase(cur_citer2);
							}
							gpi()->cur_box_count--;

							if (gpi()->cur_box_count > 3)
								gpi()->cur_box_smeh = gpi()->cur_box_count - 3;
							else
								gpi()->cur_box_smeh = 0;
							update_inf();
							break;
						}
					}

				}

			}
		}

	});


	for (int n = 0; n < 3; n++)// для добавления и удаления кнопок проход по всем боксам (n - ноды BOX с рядами действий) // ПП все настроено на смещения бокса мапе, т.е Cur_box_smeh вроде робит
	{
		id_button_pam[n][0]->addClickEventListener([=](Ref*)// ПЛЮС ОБЪЕКТ БЛОКА
		{
			if (lock_creator_action == false)
			{
				if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 3)
				{

					gpi()->intedex_data[n + gpi()->cur_box_smeh][gpi()->cur_row_count[n + gpi()->cur_box_smeh]] = data_obj{};

					gpi()->cur_row_count[n + gpi()->cur_box_smeh]++;

					if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 4)
						gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] = gpi()->cur_row_count[n + gpi()->cur_box_smeh] - 4;
					else
						gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] = 0;



					update_inf();
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{

						if (gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] == false)
						{

							gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] = true;

							gpi()->intedex_data[n + gpi()->cur_box_smeh][gpi()->cur_row_count[n + gpi()->cur_box_smeh]] = data_obj{};

							gpi()->cur_row_count[n + gpi()->cur_box_smeh]++;

							if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 4)
								gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] = gpi()->cur_row_count[n + gpi()->cur_box_smeh] - 4;
							else
								gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] = 0;

							update_inf();
							break;
						}
					}
				}
			}
		});
		id_button_pam[n][1]->addClickEventListener([=](Ref*)// МИНУС ОБЪЕКТ БЛОКА
		{
			if (lock_creator_action == false)
			{
				if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 4)
				{
					auto cur_iter = gpi()->intedex_data[n + gpi()->cur_box_smeh].find(gpi()->cur_row_count[n + gpi()->cur_box_smeh] - 1);// ищем объект ряда

					if (cur_iter != gpi()->intedex_data[n + gpi()->cur_box_smeh].cend())
					{
						gpi()->intedex_data[n + gpi()->cur_box_smeh].erase(cur_iter);
					}


					gpi()->cur_row_count[n + gpi()->cur_box_smeh]--; //уменьшаем текущее количество ячеек

					if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 4)
						gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] = gpi()->cur_row_count[n + gpi()->cur_box_smeh] - 4;
					else
						gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] = 0;



					update_inf();
				}
				else
				{
					for (int i = 3; i > -1; i--)
					{
						if (gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] == true)
						{
							gpi()->visable_id_button[n + gpi()->cur_box_smeh][i] = false; //видимость ячейки

							auto cur_iter = gpi()->intedex_data[n + gpi()->cur_box_smeh].find(i + gpi()->cur_row_smeh[n + gpi()->cur_box_smeh]);// ищем объект ряда

							if (cur_iter != gpi()->intedex_data[n + gpi()->cur_box_smeh].cend())
							{
								gpi()->intedex_data[n + gpi()->cur_box_smeh].erase(cur_iter);
							}

							if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 0) //на всякий тупая проверка
								gpi()->cur_row_count[n + gpi()->cur_box_smeh]--; //уменьшаем колво ячеек
							creator_obj = nullptr; //текущий объект - неизвестен

							if (gpi()->cur_row_count[n + gpi()->cur_box_smeh] > 4)
								gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] = gpi()->cur_row_count[n + gpi()->cur_box_smeh] - 4;
							else
								gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] = 0;

							update_inf(); //аптейтим
							break;
						}
					}
				}
			}
		});
		for (int i = 0; i < 4; i++)
		{
			id_button[n][i]->addClickEventListener([=](Ref*)// ОБЪЕКЬЫ БЛОКОВ
			{
				if (lock_creator_action == false)
				{
					creator_obj = data_obj_id_button[id_button[n][i]]; //тупой выбор кнопки по закрепленной инфе
					update_inf(); //сброс 
					update_ind2();//фулл сброс
				}
			});
		}

		id_button_row_swich[n][0]->addClickEventListener([=](Ref*)//предыдущий объект
		{
			if (lock_creator_action == false)
			{
				//ТЕстовый свап объектов в боксе
				if (swap_mode == true && creator_obj != nullptr)
				{
					for (int n = 0; n < gpi()->cur_box_count; n++)//по всем боксам
					{
						auto cur_iter = gpi()->cur_row_count.find(n);//ищем есть ли такой бокс
						if (cur_iter != gpi()->cur_row_count.cend())//если есть
						{
							auto cur_iter2 = gpi()->intedex_data.find(n);//ищем список инфы объектов по боксу
							if (cur_iter2 != gpi()->intedex_data.cend())//елси есть 
							{
								auto i = cur_iter2->second.begin();//сохраняем первую инфу объекта во временную переменную
								while (i != cur_iter2->second.cend())//если эта переменная существует
								{
									if (&i->second == creator_obj)//если эта переменная наш выбранный объект
									{//если будут ошибки наставить проверок на конец мап
										auto i_next = i;//делаем копию итератора
										i_next--;//идем назад
										if (i_next != cur_iter2->second.cend())//если есть кто
										{
											swap(i->second, i_next->second);//свапаем
											creator_obj = &i_next->second;
										}
										n = gpi()->cur_box_count;//конец цикла
										break;
									}
									i++;
								}
							}
						}
					}
				}

				if (gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] - 1 > -1)
					gpi()->cur_row_smeh[n + gpi()->cur_box_smeh]--;
				update_inf(); //сброс 
			}
		});


		id_button_row_swich[n][1]->addClickEventListener([=](Ref*)//следующий объект
		{
			if (lock_creator_action == false)
			{
				if (swap_mode == true && creator_obj != nullptr)
				{
					for (int n = 0; n < gpi()->cur_box_count; n++)//по всем боксам
					{
						auto cur_iter = gpi()->cur_row_count.find(n);//ищем есть ли такой бокс
						if (cur_iter != gpi()->cur_row_count.cend())//если есть
						{
							auto cur_iter2 = gpi()->intedex_data.find(n);//ищем список инфы объектов по боксу
							if (cur_iter2 != gpi()->intedex_data.cend())//елси есть 
							{
								auto i = cur_iter2->second.begin();//сохраняем первую инфу объекта во временную переменную
								while (i != cur_iter2->second.cend())//если эта переменная существует
								{
									if (&i->second == creator_obj)//если эта переменная наш выбранный объект
									{//если будут ошибки наставить проверок на конец мап
										auto i_next = i;//делаем копию итератора
										i_next++;//идем назад
										if (i_next != cur_iter2->second.cend())//если есть кто
										{
											swap(i->second, i_next->second);//свапаем
											creator_obj = &i_next->second;
										}
										n = gpi()->cur_box_count;//конец цикла
										break;
									}
									i++;
								}
							}
						}
					}
				}

				if (gpi()->cur_row_smeh[n + gpi()->cur_box_smeh] + 4 < gpi()->cur_row_count[n + gpi()->cur_box_smeh])
					gpi()->cur_row_smeh[n + gpi()->cur_box_smeh]++;
				update_inf(); //сброс 
			}
		});

	}

	type_obj_choise[0]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (creator_obj->my_type != type_struct::scene)
			{
				*creator_obj = data_obj{};
				creator_obj->my_inter = unknown;
				creator_obj->my_type = type_struct::scene;
				update_inf();
			}
		}
	});

	type_obj_choise[1]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (creator_obj->my_type != type_struct::sprite)
			{
				*creator_obj = data_obj{};
				creator_obj->my_inter = unknown;
				creator_obj->my_type = type_struct::sprite;
				update_inf();
			}
		}
	});

	type_obj_choise[2]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (creator_obj->my_type != type_struct::text)
			{
				*creator_obj = data_obj{};
				creator_obj->my_inter = unknown;
				creator_obj->my_type = type_struct::text;
				creator_obj->data1 = "";
				creator_obj->data2 = "";
				update_inf();
			}
		}
	});

	type_obj_choise[3]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (creator_obj->my_type != type_struct::ore)
			{
				*creator_obj = data_obj{};
				creator_obj->my_inter = action;
				creator_obj->my_type = type_struct::ore;
				update_inf();
			}
		}
	});

	type_obj_choise[4]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (creator_obj->my_type != type_struct::condition)
			{
				*creator_obj = data_obj{};
				creator_obj->my_inter = action;
				creator_obj->my_type = type_struct::condition;
				update_inf();
			}
		}
	});

	type_obj_choise[5]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (creator_obj->my_type != type_struct::audio)
			{
				*creator_obj = data_obj{};
				creator_obj->my_inter = action;
				creator_obj->my_type = type_struct::audio;
				update_inf();
			}
		}
	});

	type_obj_choise[6]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (creator_obj->my_type != type_struct::teleport)
			{
				*creator_obj = data_obj{};
				creator_obj->my_inter = unknown;
				creator_obj->my_type = type_struct::teleport;
				update_inf();
			}
		}
	});

	type_obj_choise[7]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			if (creator_obj->my_type != type_struct::live2d)
			{
				*creator_obj = data_obj{};
				creator_obj->my_inter = unknown;
				creator_obj->my_type = type_struct::live2d;
				update_inf();
			}
		}
	});
	
	intr_live2d_choise[0]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_inter = swich;
			creator_obj->my_name = any_enum::NONE;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
		//	creator_obj->data3 = "";
			creator_obj->data3 = "body99|brow99|face99|hand99|head99|";
			update_inf();
		}
	});

	intr_live2d_choise[1]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_inter = action;
			creator_obj->my_name = any_enum::NONE;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
			creator_obj->data3 = "";
			creator_obj->my_action = UNKNOWN_ACTION;
			update_inf();
		}
	});


	intr_obj_choise[0]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_inter = swich;
			creator_obj->my_name = any_enum::NONE;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
			creator_obj->data3 = "";
			update_inf();
		}
	});

	intr_obj_choise[1]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_inter = action;
			creator_obj->my_name = any_enum::NONE;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
			creator_obj->data3 = "";
			update_inf();
		}
	});

	intr_text_choise[0]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_inter = action;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
			update_inf();
		}
	});

	intr_text_choise[1]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_inter = swich;
			creator_obj->data1 = "name";
			creator_obj->data2 = "text";
			update_inf();
		}
	});

	////////////////////////////////////////////////////////
	//SWICH SCENE
	swich_scene_choise[0]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			lock_creator_action = true;
			Selection_BG->setVisible(true);
			update_inf();
		}
	});

	swich_scene_choise[1]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			lock_creator_action = true;
			Selection_CG->setVisible(true);
			update_inf();
		}
	});

	for (int n = 0; n < 83; n++)
	{
		static_cast<ui::Button*>(Selection_BG->getChildByTag(123123)->getChildByTag(n + 1))->addClickEventListener([=](Ref*)
		{
			lock_creator_action = false;
			creator_obj->data1 = "BG";
			creator_obj->data2 = std::to_string(n);
			Selection_BG->setVisible(false);
			update_inf();
		});
	}

	for (int n = 0; n < 168; n++)
	{
		static_cast<ui::Button*>(Selection_CG->getChildByTag(123123)->getChildByTag(n + 1))->addClickEventListener([=](Ref*)
		{
			lock_creator_action = false;
			creator_obj->data1 = "CG";
			creator_obj->data2 = std::to_string(n);
			Selection_CG->setVisible(false);
			update_inf();
		});
	} 

	swich_scene_type_swich[0]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_swich = SIMPLE;
			update_inf();
		}
	});

	swich_scene_type_swich[1]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_swich = NULL_TIME;
			update_inf();
		}
	});

	////////////////////////////////////////////////////////
	//ACTION SCENE
	action_scene_choise[0]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = SHAKE;
			update_inf();
		}
	});

	action_scene_choise[1]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = PUNCH;
			update_inf();
		}
	});

	action_scene_choise[2]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = BLACK_IN;
			update_inf();
		}
	});

	action_scene_choise[3]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = BLACK_OUT;
			update_inf();
		}
	});

	action_scene_choise[4]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = POLOS_IN;
			update_inf();
		}
	});

	action_scene_choise[5]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = POLOS_OUT;
			update_inf();
		}
	});

	action_scene_choise[6]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = SLASH_WS_IN;
			update_inf();
		}
	});

	action_scene_choise[7]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = SLASH_WS_OUT;
			update_inf();
		}
	});

	action_scene_choise[8]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = SLASH_AD_IN;
			update_inf();
		}
	});

	action_scene_choise[9]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = SLASH_AD_OUT;
			update_inf();
		}
	});

	action_scene_choise[10]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			switch (creator_obj->my_action)
			{
			case BLACK_IN:
				creator_obj->my_action = MBLACK_IN;
				break;
			case BLACK_OUT:
				creator_obj->my_action = MBLACK_OUT;
				break;
			case POLOS_IN:
				creator_obj->my_action = MPOLOS_IN;
				break;
			case POLOS_OUT:
				creator_obj->my_action = MPOLOS_OUT;
				break;
			case SLASH_WS_IN:
				creator_obj->my_action = MSLASH_WS_IN;
				break;
			case SLASH_WS_OUT:
				creator_obj->my_action = MSLASH_WS_OUT;
				break;
			case SLASH_AD_IN:
				creator_obj->my_action = MSLASH_AD_IN;
				break;
			case SLASH_AD_OUT:
				creator_obj->my_action = MSLASH_AD_OUT;
				break;
			default:
				MessageBox("Не выбранна анимация для конверта", "Ошибка");
			}
			update_inf();
		}
	});

	////////////////////////////////////////////////////////
	//SWICH SPRITE

	swich_sprite_creator_srite_button->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			lock_creator_action = true;
			Selection_SP->setVisible(true);
			update_inf();
		}
	});

	swich_sprite_resource_save->addClickEventListener([=](Ref*)
	{
		auto exit = ([=]()
		{
			lock_creator_action = false;
			Selection_SP->setVisible(false);
			update_inf();
		});
		if (creator_obj->my_inter == swich)
		{
			if (creator_obj->my_name != any_enum::NONE)
			{
				if (creator_obj->hide == true)
				{
					exit();
				}
				else
				{
					if (creator_obj->data1 != "" && creator_obj->data2 != "" && creator_obj->data3 != "")
					{
						exit();
					}
				}
			}
		}
		else if (creator_obj->my_inter == action)
		{
			if (creator_obj->my_name != any_enum::NONE)
			{
				exit();
			}
		}


	});




	swich_sprite_choise_chater[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::AY;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});

	swich_sprite_choise_chater[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::DA;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});


	swich_sprite_choise_chater[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::KI;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});

	swich_sprite_choise_chater[3]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::AK;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});

	swich_sprite_choise_chater[4]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::KA;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});
	
	swich_sprite_choise_chater[5]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::KU;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});

	swich_sprite_choise_chater[6]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::MA;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});

	swich_sprite_choise_chater[7]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::RO;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});

	swich_sprite_choise_chater[8]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::SA;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});

	swich_sprite_choise_chater[9]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::SE;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});

	swich_sprite_choise_chater[10]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::YO;
		creator_obj->data1 = "";
		creator_obj->data2 = "";
		creator_obj->data3 = "";
		update_inf();
	});


	swich_sprite_choise_type[0]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_swich = SIMPLE;
			update_inf();
		}
	});

	swich_sprite_choise_type[1]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_swich = RTL;
			update_inf();
		}
	});

	swich_sprite_choise_type[2]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_swich = LTR;
			update_inf();
		}
	});

	swich_sprite_choise_type[3]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_swich = NULL_TIME;
			update_inf();
		}
	});

	swich_sprite_choise_type[4]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_swich = DTT;
			update_inf();
		}
	});

	swich_sprite_choise_position[0]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_position = any_enum::centr;
			update_inf();
		}
	});

	swich_sprite_choise_position[1]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_position = any_enum::left;
			update_inf();
		}
	});

	swich_sprite_choise_position[2]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_position = any_enum::left_centr;
			update_inf();
		}
	});

	swich_sprite_choise_position[3]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_position = any_enum::right;
			update_inf();
		}
	});

	swich_sprite_choise_position[4]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_position = any_enum::right_centr;
			update_inf();
		}
	});

	swich_sprite_hide->addClickEventListener([=](Ref*)
	{
		if (swich_sprite_hide->getSelectedState() == false)
		{
			creator_obj->hide = true;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
			creator_obj->data3 = "";
		}
		else
		{
			creator_obj->hide = false;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
			creator_obj->data3 = "";
		}
		update_inf();
	});

	//ACTION SPRITE
	action_sprite_choise[0]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = MINIJUMP;
		}
	});

	action_sprite_choise[1]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = JUMP;
		}
	});

	action_sprite_choise[2]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = scale_lit;
		}
	});

	action_sprite_choise[3]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = scale_mid;
		}
	});

	action_sprite_choise[4]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = scale_big;
		}
	});

	action_sprite_choise[5]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = POS_C;
		}
	});

	action_sprite_choise[6]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = POS_L;
		}
	});

	action_sprite_choise[7]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = POS_LC;
		}
	});

	action_sprite_choise[8]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = POS_R;
		}
	});

	action_sprite_choise[9]->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_action = POS_RC;
		}
	});

	//ACTION TEXT
	action_text_choise[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = SHOW_BOX;
		update_inf();
	});


	action_text_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = HIDE_BOX;
		update_inf();
	});

	//ACTION ORE

	action_ore_choise[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = SHOW_BOX;
		update_inf();
	});

	action_ore_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = HIDE_BOX;
		update_inf();
	});

	action_ore_choise[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = UNLOCK_ORE;
		creator_obj->my_position = any_enum::custom;
		update_inf();
	});

	position_ore_choise[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_position = any_enum::left;
		update_inf();
	});

	position_ore_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_position = any_enum::right;
		update_inf();
	});

	selected_ore_button->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			Selected_Ore_Node->setVisible(true);
			lock_creator_action = true;
		}
	});

	for (int n = 0; n < 63; n++)
	{
		static_cast<ui::Button*>(Selected_Ore_Node->getChildByTag(1643)->getChildByTag(n))->addClickEventListener([=](Ref*)
		{
			lock_creator_action = false;
			Selected_Ore_Node->setVisible(false);
			creator_obj->data1 = to_string(n);
			selected_ore_text->setText("ORE " + creator_obj->data1); // отправить это в апдейт и там обновлять надпись при этом обже
			update_inf();
		});
	}


	//ACTION CONDITION

	use_ore_choise[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_position = any_enum::right;
	});

	use_ore_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_position = any_enum::left;
	});

	use_ore_choise[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_position = any_enum::centr;
	});

	condition_ore_button->addClickEventListener([=](Ref*)
	{
		if (creator_obj->data1.length() == 64)
		{
			for (int n = 0; n < 64; n++)
			{
				if (creator_obj->data1[n] == '1')
					static_cast<ui::CheckBox*>(Condition_Ore_Node->getChildByTag(434)->getChildByTag(n))->setSelectedState(true);
				else if (creator_obj->data1[n] == '0')
					static_cast<ui::CheckBox*>(Condition_Ore_Node->getChildByTag(434)->getChildByTag(n))->setSelectedState(false);
				else
					MessageBoxA(nullptr, "Ошибка, в буфере данных оказался мусор!", "Ошибка", MB_OK | MB_ICONERROR);
			}
		}
		lock_creator_action = true;
		Condition_Ore_Node->setVisible(true);
	});

	Condition_Ore_Button->addClickEventListener([=](Ref*)
	{
		std::string buff = "";//сюда мы запишен все значения ore (0 - не нужно чтобы был разблакирован) (1 - нужно чтобы был разблокирован)
							  //для этого нужно получить данные о каждой из 64 галочек
		for (int n = 0; n < 64; n++)
		{
			bool state = static_cast<ui::CheckBox*>(Condition_Ore_Node->getChildByTag(434)->getChildByTag(n))->getSelectedState();
			static_cast<ui::CheckBox*>(Condition_Ore_Node->getChildByTag(434)->getChildByTag(n))->setSelectedState(false);
			if (state == true)
				buff += '1';
			else
				buff += '0';
		}
		creator_obj->data1 = buff;
		lock_creator_action = false;
		Condition_Ore_Node->setVisible(false);
	});


	for (int n = 0; n < 11; n++)//сделал порядок в массиве такойже как и перечесления в any_enum::name_sprite так что запихал в цикл
	{
		chapter_condition_choise[n]->addClickEventListener([=](Ref*)
		{
			creator_obj->my_name = static_cast<any_enum::name_sprite>(n);
			update_inf();
		});
	}

	chapter_condition_choise[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::NONE;
		update_inf();
	});

	chapter_condition_point->addClickEventListener([=](Ref*)
	{
		creator_obj->data2 = chapter_condition_point_label->getString();

		if (is_int(creator_obj->data2) == false)
		{
			creator_obj->data1 = "";
			MessageBox("В поле ввода должна быть всегда цифра", "Уведомление");
		}

		update_inf();
		update_ind2();
	});



	//ACTION AUDIO 
	choise_audio_music->addClickEventListener([=](Ref*)
	{
		creator_obj->data1 = "0";
		creator_obj->data2 = "";
		update_inf();
	});

	choise_audio_sound->addClickEventListener([=](Ref*)
	{
		creator_obj->data1 = "1";
		creator_obj->data2 = "";
		update_inf();
	});


	for (int n = 0; n < 18; n++)
	{
		static_cast<ui::Button*>(choise_music_dirs->getChildByTag(n + 1))->addClickEventListener([=](Ref*)
		{
			creator_obj->data2 = to_string(n + 1);
			update_inf();
		});
	}

	//TELEPORT
	choise_teleport_page->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_inter = swich;
			creator_obj->my_name = any_enum::NONE;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
			creator_obj->data3 = "";
			update_inf();
			update_ind2();
		}
	});

	choise_teleport_script->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->my_inter = action;
			creator_obj->my_name = any_enum::NONE;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
			creator_obj->data3 = "";
			update_inf();
			update_ind2();
		}
	});

	choise_teleport_page_button->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{

			creator_obj->data1 = choise_teleport_page_edit->getString();
			if (is_int(creator_obj->data1) == false)
			{
				creator_obj->data1 = "";
				MessageBox("В поле ввода должна быть всегда цифра", "Уведомление");
			}
			
			update_inf();
			update_ind2();
		}
	});

	choise_teleport_script_button->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			creator_obj->data1 = "";
			const size_t size_dir = 260;
			wchar_t file_dir[size_dir];
			
			memset(file_dir, NULL, size_dir);

			if (file_winapi(file_dir, size_dir, true) == true)
			{
				for (int n = 0; n < sizeof(file_dir); n++)
				{
					if (file_dir[n] == '\0')
						break;
					creator_obj->data1 += file_dir[n];
				}
				int index_dat = creator_obj->data1.find(".dat");
				for (int n = index_dat; n > -1; n--)
				{
					if (creator_obj->data1[n] == '\\')
					{
						index_dat = n;
						break;
					}
				}
				index_dat++;
				std::string temp = "";

				for (int n = index_dat; n < creator_obj->data1.length(); n++)
				{
					temp += creator_obj->data1[n];
				}
				creator_obj->data1 = temp;
			}
			update_inf();
		}
	});

	//LIVE2D BOX
	//SWITCH
	//по имени определяется вывод какой модели нужно производить
	//в data1 храню номер текстуры для модельки - если текстуры не сущетсвует поставит самую последнюю
	//в data2 храню временную инфу - ее можно не сохранять
	//в data3 храню инфу пресета
	
	//const std::string presetModel_data3 =;
	intr_live2d_choise_switch->addClickEventListener([=](Ref*)
	{
		if (lock_creator_action == false)
		{
			Selection_LIVE2D->setVisible(true);
			lock_creator_action = true;
			LIVE2D_CREATE::scep_live2d(Selection_LIVE2D->getChildByTag(2447));//цифры ноды в которую помещу соззданную ноду live2d
			//if (creator_obj->data3.length() != presetModel_data3.length())//условие при котором копируется строчка для иницилизаций
			//{
			//	creator_obj->data3 = presetModel_data3;
			//	//LIVE2D_CREATE::init_model()
			//}
			
			update_inf();
		}
	});

	live2d_create_ok->addClickEventListener([=](Ref*)
	{
			Selection_LIVE2D->setVisible(false);
			lock_creator_action = false;
			LIVE2D_HOME();
			//LIVE2D_CREATE::scep_live2d(Selection_LIVE2D->getChildByTag(2447));//цифры ноды в которую помещу соззданную ноду live2d
	});

	live2d_choise_chater[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::AY;
		update_inf();
	});

	live2d_choise_chater[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::KI;
		update_inf();
	});

	live2d_choise_chater[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::KA;
		update_inf();
	});

	live2d_choise_chater[3]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::KU;
		update_inf();
	});

	live2d_choise_chater[4]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::MA;
		update_inf();
	});

	live2d_choise_chater[5]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::SA;
		update_inf();
	});

	for (int n = 0; n < 3; n++)
	{
		live2d_choise_texture[n]->addClickEventListener([=](Ref*)
		{
			creator_obj->data1 = std::to_string(n);
			update_inf();
		});
	}

	for (int n = 0; n < 5; n++)
	{
		live2d_expressions_select[n]->addClickEventListener([=](Ref*)
		{
			creator_obj->data2 = "000000";
			creator_obj->data2[n] = '1';
			update_inf();
		});
	}

	for (int n = 0; n < 17; n++)
	{
		live2d_expressions_choise[n]->addClickEventListener([=](Ref*)
		{
			if (creator_obj->data2.find('1') != std::string::npos)
			{
				int index = creator_obj->data2.find('1');
				std::string buff = std::to_string(n);
				if (buff.length() == 1)
				{
					buff = ("0" + buff);
				}
				std::string type;

				switch (index)
				{
				case 0:
					type = "body";
					break;
				case 1:
					type = "brow";
					break;
				case 2:
					type = "face";
					break;
				case 3:
					type = "hand";
					break;
				case 4:
					type = "head";
					break;
				default:
					MessageBoxA(nullptr, "Неизвестный элемент модели", "ERROR", MB_OK | MB_ICONERROR);
					break;
				}

				auto index_type = creator_obj->data3.find(type);

				const auto smeh_command = type.length() + buff.length();

				if (index_type != std::string::npos && index_type + smeh_command < creator_obj->data3.length())
				{
					creator_obj->data3[index_type + smeh_command - 2] = buff[0];
					creator_obj->data3[index_type + smeh_command - 1] = buff[1];
				}
				else
				{
					MessageBoxA(nullptr, "Неудалось обновить пресет expression", "ERROR", MB_OK | MB_ICONERROR);
				}
				update_inf();
			}

		});
	}
	
	live2d_model_hide->addClickEventListener([=](Ref*)
	{
		if (live2d_model_hide->getSelectedState() == false)
		{
			creator_obj->hide = true;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
			creator_obj->data3 = "";
		}
		else
		{
			creator_obj->hide = false;
			creator_obj->data1 = "";
			creator_obj->data2 = "";
			creator_obj->data3 = "";
		}
		update_inf();
	});

	//ACTION LIVE2D

	live2d_action_choise[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = scale_big;
		creator_obj->data1 = "0";
	});

	live2d_action_choise[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = scale_mid;
		creator_obj->data1 = "0";
	});

	live2d_action_choise[3]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_action = scale_lit;
		creator_obj->data1 = "0";
	});

	live2d_action_select_chapter[0]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::SA;
	});

	live2d_action_select_chapter[1]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::MA;
	});

	live2d_action_select_chapter[2]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::KU;
	});

	live2d_action_select_chapter[3]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::KA;
	});

	live2d_action_select_chapter[4]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::AY;
	});

	live2d_action_select_chapter[5]->addClickEventListener([=](Ref*)
	{
		creator_obj->my_name = any_enum::KI;
	});

	///////////////////////////////////////////////////////
	auto sign = ([=](int &x, int &y){
		return &gpi()->intedex_data[x][y];
	});


	auto create_page([=]() 
	{

		vector<Object_Scene*> objs;
		vector<type_struct::type_object> objs_type;
		vector <type_interactions> intrs;
		vector<type_swich> swichs;
		vector<type_action> actions;


		Label_text->setString("");
		Label_name->setString("");
		for (int n = 0; n < gpi()->cur_box_count; n++)
		{
			for (int i = 0; i < gpi()->cur_row_count[n]; i++)
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
							objs.push_back(new Object_Scene(sign(n, i)->data1, string_to_int(sign(n, i)->data2)));
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
								auto sprite = new Object_Sprite(sign(n, i)->my_name);
								objs.push_back(sprite);
								objs_type.push_back(sign(n, i)->my_type);
								intrs.push_back(sign(n, i)->my_inter);
								swichs.push_back(sign(n, i)->my_swich);
							}
							else
							{
								auto sprite = new Object_Sprite(
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
							auto sprite = new Object_Sprite(
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
						break;
					}
					case type_struct::ore:
					{
						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
							break;
						}
						case action:
						{// куча проверок тупых на то чтоб не вызывал левый пока он заюзан и т.д.
							int cur_sprite = string_to_int(sign(n, i)->data1);
							auto cur_pos = sign(n, i)->my_position;


							if (cur_sprite <0 || cur_sprite>63)
								break;
							if (cur_pos == any_enum::centr)
								break;

							if (((pre_save::ORE_LEFT_VIS == true && cur_pos == any_enum::left) || (pre_save::ORE_RIGHT_VIS == true && cur_pos == any_enum::right))
								&& sign(n, i)->my_action == SHOW_BOX)
								break;
							if (((pre_save::ORE_LEFT_VIS == false && cur_pos == any_enum::left) || (pre_save::ORE_RIGHT_VIS == false && cur_pos == any_enum::right))
								&& sign(n, i)->my_action == HIDE_BOX)
								break;

							auto data = new Object_ORE(cur_sprite, cur_pos);
							objs.push_back(data);
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
					case type_struct::condition:
					{

						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
							break;
						}
						case action:
						{
							if (sign(n, i)->data1.length() < 64)
								break;

							int cur_point = string_to_int(sign(n, i)->data2);
							int need_point = sign(n, i)->my_name == any_enum::NONE ? 0 : cur_point < 0 || cur_point >100 ? 0 : cur_point;
							auto use_ore = sign(n, i)->my_position == any_enum::left ? any_enum::OREL : sign(n, i)->my_position == any_enum::right ? any_enum::ORER : any_enum::nonuse;

							any_enum::open_resurce need_open[any_enum::size_ore];
							for (int z = 0; z < any_enum::size_ore; z++)
							{
								if (sign(n, i)->data1[z] == '1')
								{
									need_open[z] = any_enum::unlock;
								}
								else
								{
									need_open[z] = any_enum::lock;
								}
							}

							auto data = new Object_Condition(need_open,
								sign(n, i)->my_name == any_enum::NONE ? any_enum::NONE : sign(n, i)->my_name,
								need_point,
								use_ore);
							objs.push_back(data);
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
					case type_struct::audio:
					{
						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
							break;
						}
						case action:
						{

							int cur_type = string_to_int(sign(n, i)->data1);
							string cur_dir = sign(n, i)->data2;
							if (cur_type <0 || cur_type>1)
								break;

							auto data = new Object_Noise(static_cast<type_noise>(cur_type), cur_dir);
							objs.push_back(data);
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
					case type_struct::text:
					{

						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
							auto data = new Object_Text(sign(n, i)->data1, sign(n, i)->data2);
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
						break;
					}
					case type_struct::teleport:
					{
						switch (sign(n, i)->my_inter)
						{
						case swich://перешли на другую страничку
						{
							auto smeh_page([=](std::string buff)
							{

								int index_page = string_to_int(buff) - 1;
								if (index_page < 0)//странички не могут быть меньше нуля
									return;
								if (cur_page_data.size() > index_page)
								{
									cur_page = index_page;
									creator_obj = nullptr;
									update_inf();
								}

							});
							auto data = new Object_Teleport(smeh_page, sign(n, i)->data1, true);
							objs.push_back(data);
							objs_type.push_back(sign(n, i)->my_type);
							intrs.push_back(sign(n, i)->my_inter);
							swichs.push_back(sign(n, i)->my_swich);
							break;
						}
						case action://перешли на другой скрипт
						{
							auto data = new Object_Teleport(load_update, sign(n, i)->data1);
							objs.push_back(data);
							objs_type.push_back(sign(n, i)->my_type);
							intrs.push_back(sign(n, i)->my_inter);
							actions.push_back(sign(n, i)->my_action);
							break;
						}
						default:
							break;
						}
						break;
					}
					case  type_struct::live2d:
					{
						if (sign(n, i)->my_name != any_enum::NONE)
						{
							switch (sign(n, i)->my_inter)
							{
							case swich://перешли на другую страничку
							{
								Object_LIVE2D* model = nullptr;

								if (sign(n, i)->hide == false)
								{
									model = new Object_LIVE2D(sign(n, i)->my_name, string_to_int(sign(n, i)->data1), sign(n, i)->data3);
								}
								else
								{
									model = new Object_LIVE2D(sign(n, i)->my_name);
								}


								objs.push_back(model);
								objs_type.push_back(sign(n, i)->my_type);
								intrs.push_back(sign(n, i)->my_inter);
								swichs.push_back(sign(n, i)->my_swich);
								break;
							}
							case action:
							{
								Object_LIVE2D* model = new Object_LIVE2D(sign(n, i)->my_name, sign(n, i)->data1);
								objs.push_back(model);
								objs_type.push_back(sign(n, i)->my_type);
								intrs.push_back(sign(n, i)->my_inter);
								actions.push_back(sign(n, i)->my_action);
								break;
							}
							}
						}
						else
						{
							MessageBox("Ошибка у модельки не было выбрано имя", "Ошибка");
						}
						break;
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
			selected_page = new Page(objs, objs_type, intrs, swichs, actions);
			selected_page->draw();
		}

		update_inf();
	});

	play_page->addClickEventListener([=](Ref*)// сохранялка страницы текущей по cur_page и ее проигрыш
	{
		if (lock_creator_action == false)
		{
			if (selected_page != nullptr)
			{
				StopActionDisplay();
				if (selected_page->isFinish() == false)
				{
					//ClearDisplay();//TODO FIX ME рисует через раз 
					Game_Mode->stopAllActions();
					selected_page->FastFinish();

					return;
				}
				else
				{
					Game_Mode->stopAllActions();
					delete selected_page;
					selected_page = nullptr;
				}

			}

			create_page();
		}
		
	});
	

	

}



void music_play(Node *cur_node, string dir)
{
	if (dir == "")
	{
		background_smooth(cur_node, Background_Volume);
		return;
	}
	background_smooth(cur_node, Background_Volume, dir);

}


void sound_play(string dir)
{
	if (dir == "")
	{
		return;
	}
	cocos2d::experimental::AudioEngine::stop(Game_id);
	Game_id = cocos2d::experimental::AudioEngine::play2d(dir, true, All_Volume*Game_Volume);
}


void confget()
{

	char temp[1];
	ifstream file(dir_setting, ios::binary);
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
				All_Volume = float(temp[0]) / 100;
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
		ofstream newsetting(dir_setting, ios::binary);
		char standart[] = { 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01 , 0x32, 0x64, 0x64, 0x64, 0x64, 0x32, 0x32, 0x32 }; // первые восемь - буловы значения, потом пять байтов громкостей, потом еще 3 скорости текста от 0 до 100 (0x00, 0x64)
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
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
			Sound_Menu_Set->setEnabled(false); ////////////////////////////////////////////////////////////////////////// ПРИ ПЕРЕХОДЕ В КАЖДОЕ МЕНЮ ВЫКЛЮЧАТЬ ВСЕ КНОПКИ
			Text_Menu_Set->setEnabled(true);
			System_Menu_Set->setEnabled(true);
			System_Menu->setVisible(false);
			Text_Menu->setVisible(false);
			Sound_Menu->setVisible(true);
		});
	}



	auto visget([=](bool &cur_Skip_All, bool &cur_ORE_old, bool &cur_Com_twoshot, bool &cur_Tips_twoshot, bool &cur_Text_old, bool &cur_Autosave1, bool &cur_Autosave2, bool &cur_Musalb)
	{
		Sprite* temp_vis;

		if (cur_Skip_All == true)
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

		if (cur_ORE_old == true)
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
		if (cur_Com_twoshot == true)
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
		if (cur_Tips_twoshot == true)
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
		if (cur_Text_old == true)
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
		if (cur_Autosave1 == true)
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
		if (cur_Autosave2 == true)
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
		if (cur_Musalb == true)
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
		System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
		Sure->setVisible(true);
		Text_sure->setString("РЎРѕС…СЂР°РЅРёС‚СЊ РґР°РЅРЅС‹Рµ РЅР°СЃС‚СЂРѕР№РєРё Рё РІС‹Р№С‚Рё?"); // Сохранить данные настройки и выйти?
		Sure_Yes->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
					System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
					Back_Node->setVisible(false);
					Button_Menu->setVisible(false);
				});
			}
		});
		Sure_No->addClickEventListener([=](Ref *)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
			Sure->setVisible(false);
		});
	});
	Back->addClickEventListener([=](Ref *)
	{
		if (temp_sw == true)
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
			Sure->setVisible(true);
			Text_sure->setString("РЎРѕС…СЂР°РЅРёС‚СЊ РґР°РЅРЅС‹Рµ РЅР°СЃС‚СЂРѕР№РєРё РїРµСЂРµРґ РІС‹С…РѕРґРѕРј?"); // Сохранить данные настройки перед выходом?
			Sure_Yes->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Click"], false, All_Volume*System_Volume);
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
						System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
						Back_Node->setVisible(false);
						Button_Menu->setVisible(false);
					});
				}
			});
			Sure_No->addClickEventListener([=](Ref *)
			{
				System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
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
						System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
						Back_Node->setVisible(false);
						Button_Menu->setVisible(false);
					});
				}
			});
		}
		else
		{
			System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
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
					System_id = cocos2d::experimental::AudioEngine::play2d(SYSTEMSE_DIR["Cancel"], false, All_Volume*System_Volume);
					Back_Node->setVisible(false);
					Button_Menu->setVisible(false);
				});
			}
		}
	});

}

bool file_winapi(wchar_t *file_dir, size_t size, bool load)
{
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"OREIMO Files (*.dat)\0*.dat\0All Files (*.*)\0*.*\0";
	ofn.lpstrDefExt = (LPCWSTR)L"dat";
	ofn.lpstrFile = file_dir;
	ofn.nMaxFile = size;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;

	if (load == true)
	{
		if (GetOpenFileName(&ofn) == TRUE)
			return true;
		else
			return false;
	}
	else
	{
		if (GetSaveFileName(&ofn) == TRUE)
			return true;
		else
			return false;
	}
}

int save_script()// возвращает ноль если все хорошо
{
	const size_t size_dir = 260;
	wchar_t file_dir[size_dir];

	memset(file_dir, NULL, sizeof(file_dir));
	if (file_winapi(file_dir, size_dir) == false)
	{
		SetCurrentDirectory(main_dir);
		return 3;
	}
	else
	{
		SetCurrentDirectory(main_dir);
	}

	string cur_name_script = "";//dir_save_script + "cus_script " + to_string(time(0));


	for (int n = 0; n < sizeof(file_dir); n++)
	{
		if (file_dir[n] == '\0')
			break;
		cur_name_script += file_dir[n];
	}
	if (cur_name_script.length() == 0)
		return 3;

	ofstream file(cur_name_script, ios::binary);
	vector<unsigned char>buff;

	if (!file)
		return 2;

#ifdef LOG_SAVE
	//log_dir += ".log" + '"';
	ofstream log(cur_name_script + ".log", ios::binary);
	vector<string>buff_log;
	string snos = string({ 0x0A }) + string({ 0x0D });
#endif

	auto filed_exept = [&]() {
#ifdef LOG_SAVE
		buff_log.push_back(snos);
		buff_log.push_back("Неудача");
		for (int _n = 0; _n < buff_log.size(); _n++)
		{
			log << buff_log[_n];
		}
		file.close();
		log.close();
#endif
	};


	int n = 0;
	int i = 0;
	int p = 0;
	for (p = 0; p < cur_page_count; p++)
	{
		auto gpi([=]()
		{
			return cur_page_data[p];
		});
		auto sign = ([=](int &x, int &y) {
			return &gpi()->intedex_data[x][y];
		});


		buff.push_back(0x00);//создаем байт размерности страницы
		int bite_page = buff.size() - 1;
#ifdef LOG_SAVE
		buff_log.push_back(snos);
		buff_log.push_back("Начата запись страницы " + to_string(p + 1) + " по байту " + to_string(bite_page));
#endif
		int size_page = 1;//размер странички увеличивает каждый бокс своей размерностью
		for (n = 0; n < gpi()->cur_box_count; n++)
		{

			buff.push_back(0x00);//создаем байт размерности бокса
			int bite_box = buff.size() - 1;
			int size_box = 1;//размер бокса увеличивает каждый объект своей размерностью
#ifdef LOG_SAVE
			buff_log.push_back(snos);
			buff_log.push_back("Начата запись бокса " + to_string(n + 1) + " по байту " + to_string(bite_box));
#endif
			for (i = 0; i < gpi()->cur_row_count[n]; i++)
			{

				buff.push_back(0x00);//создаем байт размерности объекта бокса
				int bite_obj = buff.size() - 1;//номер байта в котором хранится информация о размере объекта
				int size_obj = 1;//размер объекта увеличивается от каждого байта
#ifdef LOG_SAVE
				buff_log.push_back(snos);
				buff_log.push_back("Начата запись объекта " + to_string(i + 1) + " по байту " + to_string(bite_obj));
#endif
				if (sign(n, i)->my_type != type_struct::none)
				{

					switch (sign(n, i)->my_type)
					{
					case type_struct::scene:
					{
#ifdef LOG_SAVE
						buff_log.push_back(snos);
						buff_log.push_back("Сцена");
#endif
						buff.push_back(0x01);//байт типа объекта
						size_obj++;

						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Свич");
#endif
							buff.push_back(0x01);//байт типа взаимодействия

							if (sign(n, i)->my_swich == SIMPLE)//байт подтипа взаимодействия
								buff.push_back(0x01);
							else if (sign(n, i)->my_swich == NULL_TIME)
								buff.push_back(0x02);
							else
							{
#ifdef LOG_SAVE
								buff_log.push_back(string({ 0x0A }) + string({ 0x0D }));
								buff_log.push_back("Ошибка сохранения, неизвестный свич сцены");
								filed_exept();
								return 1;
#endif
							}


							if (sign(n, i)->data1 == "BG")//байт дирректории
								buff.push_back(0x01);
							else if (sign(n, i)->data1 == "CG")
								buff.push_back(0x02);
							else
							{
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, неизвестная ключевая дирректория сцены");
								filed_exept();
#endif
								return 1;
							}

							if (sign(n, i)->data2 != "")//и байт номера картинки
								buff.push_back(string_to_int(sign(n, i)->data2)); //БУДЕТ РАБОТАТЬ ТОЛЬКО С ЦИФРАМИ
							else
							{
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, нет данных для создания сцены");
								filed_exept();
#endif
								return 1;
							}

							size_obj += 4;//на 4 у свича
							break;
						}
						case action:
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Экшон");
#endif
							buff.push_back(0x02);//байт типа взаимодействия


							switch (sign(n, i)->my_action)
							{
							case type_action::SHAKE:
							{
								buff.push_back(0x01);//байт подтипа взаимодействия
								break;
							}
							case type_action::PUNCH:
							{
								buff.push_back(0x02);
								break;
							}
							case type_action::BLACK_IN:
							{
								buff.push_back(0x03);
								break;
							}
							case type_action::BLACK_OUT:
							{
								buff.push_back(0x04);
								break;
							}
							case type_action::POLOS_IN:
							{
								buff.push_back(0x05);
								break;
							}
							case type_action::POLOS_OUT:
							{
								buff.push_back(0x06);
								break;
							}
							case type_action::SLASH_WS_IN:
							{
								buff.push_back(0x07);
								break;
							}
							case type_action::SLASH_WS_OUT:
							{
								buff.push_back(0x08);
								break;
							}
							case type_action::SLASH_AD_IN:
							{
								buff.push_back(0x09);
								break;
							}
							case type_action::SLASH_AD_OUT:
							{
								buff.push_back(0x10);
								break;
							}
							case type_action::MBLACK_IN:
							{
								buff.push_back(0x11);
								break;
							}
							case type_action::MBLACK_OUT:
							{
								buff.push_back(0x12);
								break;
							}
							case type_action::MPOLOS_IN:
							{
								buff.push_back(0x13);
								break;
							}
							case type_action::MPOLOS_OUT:
							{
								buff.push_back(0x14);
								break;
							}
							case type_action::MSLASH_WS_IN:
							{
								buff.push_back(0x15);
								break;
							}
							case type_action::MSLASH_WS_OUT:
							{
								buff.push_back(0x16);
								break;
							}
							case type_action::MSLASH_AD_IN:
							{
								buff.push_back(0x17);
								break;
							}
							case type_action::MSLASH_AD_OUT:
							{
								buff.push_back(0x18);
								break;
							}
							default:
							{
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, неизвестный экшон сцены");
								filed_exept();
#endif
								return 1;
								break;
							}
							}

							size_obj += 2;//на 2 у экшона
							break;
						}
						default:
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Ошибка сохранения, неизвестное взаимодейсвие с объектом");
#endif
							break;
						}
						break;
					}
					case type_struct::sprite:
					{
#ifdef LOG_SAVE
						buff_log.push_back(snos);
						buff_log.push_back("Спрайт");
#endif
						buff.push_back(0x02);//байт типа объекта
						size_obj++;


						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Свич");
#endif
							buff.push_back(0x01);//байт типа взаимодействия

							if (sign(n, i)->my_name != any_enum::NONE)
							{
								switch (sign(n, i)->my_name)// имя спрайта как цифра
								{
								case any_enum::AY:
									buff.push_back(0x01);
									break;
								case any_enum::KI:
									buff.push_back(0x02);
									break;
								case any_enum::DA:
									buff.push_back(0x03);
									break;
								case any_enum::AK:
									buff.push_back(0x04);
									break;
								case any_enum::KA:
									buff.push_back(0x05);
									break;
								case any_enum::KU:
									buff.push_back(0x06);
									break;
								case any_enum::MA:
									buff.push_back(0x07);
									break;
								case any_enum::RO:
									buff.push_back(0x08);
									break;
								case any_enum::SA:
									buff.push_back(0x09);
									break;
								case any_enum::SE:
									buff.push_back(0x10);
									break;
								case any_enum::YO:
									buff.push_back(0x11);
									break;
								default:
#ifdef LOG_SAVE
									buff_log.push_back(snos);
									buff_log.push_back("Ошибка сохранения, неизвестное имя спрайта");
									filed_exept();
#endif
									return 1;
									break;
								}
							}

							if (sign(n, i)->data1 != "" && sign(n, i)->data2 != "" && sign(n, i)->data3 != "" && sign(n, i)->hide == false)
							{
								//текущий тип запись цифрой
								if (sign(n, i)->data1 == "C")
								{
									buff.push_back(0x01);
								}
								else if (sign(n, i)->data1 == "L")
								{
									buff.push_back(0x02);
								}
								else if (sign(n, i)->data1 == "R")
								{
									buff.push_back(0x03);
								}
								else if (sign(n, i)->data1 == "C_COSP")
								{
									buff.push_back(0x11);
								}
								else if (sign(n, i)->data1 == "L_COSP")
								{
									buff.push_back(0x12);
								}
								else if (sign(n, i)->data1 == "R_COSP")
								{
									buff.push_back(0x13);
								}
								else if (sign(n, i)->data1 == "C_OLD")
								{
									buff.push_back(0x21);
								}
								else if (sign(n, i)->data1 == "L_OLD")
								{
									buff.push_back(0x22);
								}
								else if (sign(n, i)->data1 == "R_OLD")
								{
									buff.push_back(0x23);
								}
								else
								{
#ifdef LOG_SAVE
									buff_log.push_back(snos);
									buff_log.push_back("Ошибка сохранения, неизвестный тип текстуры спрайта");
									filed_exept();
#endif
									return 1;
								}


								if (is_int(sign(n, i)->data2) == false || is_int(sign(n, i)->data3) == false)
								{
#ifdef LOG_SAVE
									buff_log.push_back(snos);
									buff_log.push_back("Ошибка сохранения, неизвестный номер текстуры или номер эмоции");
									filed_exept();
#endif
								}

								buff.push_back(string_to_int(sign(n, i)->data2)); //номер текстурки этого типа 
								buff.push_back(string_to_int(sign(n, i)->data3)); //номер эмоции типа


								switch (sign(n, i)->my_position)//его позиция
								{
								case any_enum::left:
									buff.push_back(0x01);
									break;
								case any_enum::left_centr:
									buff.push_back(0x02);
									break;
								case any_enum::centr:
									buff.push_back(0x03);
									break;
								case any_enum::right_centr:
									buff.push_back(0x04);
									break;
								case any_enum::right:
									buff.push_back(0x05);
									break;
								default:
#ifdef LOG_SAVE
									buff_log.push_back(snos);
									buff_log.push_back("Ошибка сохранения, неизвестная позиция спрайта");
									filed_exept();
#endif
									return 1;
									break;
								}

//								switch (sign(n, i)->my_swich)//его свич
//								{//LTR, RTL, SIMPLE
//								case SIMPLE:
//									buff.push_back(0x01);
//									break;
//								case LTR:
//									buff.push_back(0x02);
//									break;
//								case RTL:
//									buff.push_back(0x03);
//									break;
//								case NULL_TIME:
//									buff.push_back(0x04);
//									break;
//								case DTT:
//									buff.push_back(0x05);
//									break;
//								default:
//#ifdef LOG_SAVE
//									buff_log.push_back(snos);
//									buff_log.push_back("Ошибка сохранения, неизвестный тип свича спрайта");
//#endif
//									return 1;
//									break;
//								}
								//ALERT - перенес ниже

							}
							else if (sign(n, i)->hide == true)
							{
								buff.push_back(0x88);
								buff.push_back(0xFF);
								buff.push_back(0xFF);
								buff.push_back(0xFF);
								buff.push_back(0xFF);
							//	buff.push_back(0xFF);
							}
							else
							{
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, недостаточно данных для создания спрайта");
								filed_exept();
#endif
								return 1;
							}

							switch (sign(n, i)->my_swich)//его свич
							{//LTR, RTL, SIMPLE
							case SIMPLE:
								buff.push_back(0x01);
								break;
							case LTR:
								buff.push_back(0x02);
								break;
							case RTL:
								buff.push_back(0x03);
								break;
							case NULL_TIME:
								buff.push_back(0x04);
								break;
							case DTT:
								buff.push_back(0x05);
								break;
							default:
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, неизвестный тип свича спрайта");
#endif
								return 1;
								break;
							}

							size_obj += 7;//на 7 у свича
							break;
						}
						case action:
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Экшон");
#endif
							buff.push_back(0x02);;//байт типа взаимодействия
							size_obj++;

							switch (sign(n, i)->my_name)// имя спрайта как цифра
							{
							case any_enum::AY:
								buff.push_back(0x01);
								break;
							case any_enum::KI:
								buff.push_back(0x02);
								break;
							case any_enum::DA:
								buff.push_back(0x03);
								break;
							case any_enum::AK:
								buff.push_back(0x04);
								break;
							case any_enum::KA:
								buff.push_back(0x05);
								break;
							case any_enum::KU:
								buff.push_back(0x06);
								break;
							case any_enum::MA:
								buff.push_back(0x07);
								break;
							case any_enum::RO:
								buff.push_back(0x08);
								break;
							case any_enum::SA:
								buff.push_back(0x09);
								break;
							case any_enum::SE:
								buff.push_back(0x10);
								break;
							case any_enum::YO:
								buff.push_back(0x11);
								break;
							default:
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, неизвестное имя спрайта");
								filed_exept();
#endif
								return 1;
								break;
							}
							size_obj++;

							switch (sign(n, i)->my_action)//байт подтипа взаимодействия
							{
							case MINIJUMP:
								buff.push_back(0x01);
								break;
							case JUMP:
								buff.push_back(0x02);
								break;
							case scale_lit:
								buff.push_back(0x03);
								break;
							case scale_mid:
								buff.push_back(0x04);
								break;
							case scale_big:
								buff.push_back(0x05);
								break;
							case POS_C:
								buff.push_back(0x06);
								break;
							case POS_R:
								buff.push_back(0x07);
								break;
							case POS_RC:
								buff.push_back(0x08);
								break;
							case POS_L:
								buff.push_back(0x09);
								break;
							case POS_LC:
								buff.push_back(0x10);
								break;
							default:
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, неизвестное дейсвие спрайта");
								filed_exept();
#endif
								return 1;
								break;
							}

							size_obj++;
							//на 3 у экшона
							break;
						}
						default:
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Ошибка сохранения, неизвестное взаимодейсвие с объектом");
							filed_exept();
#endif							
							return 1;
							break;
						}
						break;
					}
					case type_struct::text:
					{
#ifdef LOG_SAVE
						buff_log.push_back(snos);
						buff_log.push_back("Текст");
#endif
						buff.push_back(0x03);//байт типа объекта
						size_obj++;

						switch (sign(n, i)->my_inter)
						{
						case swich://ПОКА ЧТО ТЕСТОВОЕ ИБО БРАТИЕ ТЕКСТА НЕ НАСТРОЕНО
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Свич");
#endif
							buff.push_back(0x01);//байт типа взаимодействия			
							int size_name = 1; //байты имени
							int size_text = 1; //байты текста
							buff.push_back(size_name);
							buff.push_back(size_text);
							size_obj += 3;
							break;
						}
						case action:
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Экшон");
#endif
							buff.push_back(0x02);//байт типа взаимодействия

							if (sign(n, i)->my_action == SHOW_BOX)//байт подтипа взаимодействия
								buff.push_back(0x01);
							else if (sign(n, i)->my_action == HIDE_BOX)
								buff.push_back(0x02);
							else
							{

#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, неизвестный экшон фона текста");
								filed_exept();
#endif		
								return 1;
							}

							size_obj += 2;//на 2 у экшона
							break;
						}
						default:
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Ошибка сохранения, неизвестное взаимодейсвие с объектом");
							filed_exept();
#endif
							return 1;
							break;
						}
						break;
					}
					case type_struct::ore:
					{
						break;
					}
					case type_struct::condition:
					{
						break;
					}
					case type_struct::audio:
					{
#ifdef LOG_SAVE
						buff_log.push_back(snos);
						buff_log.push_back("Аудио");
#endif
						buff.push_back(0x06);//байт типа объекта
						size_obj++;
						if (sign(n, i)->my_inter == action)
						{
							buff.push_back(0x02);//байт типа взаимодействия
							size_obj++;

							if (sign(n, i)->data1 != "" && sign(n, i)->data2 != "")
							{
								buff.push_back(string_to_int(sign(n, i)->data1) + 1); //байт подтипа объекта
								buff.push_back(string_to_int(sign(n, i)->data2) + 1); //байт номера аудишки
								size_obj += 2;
							}
							else
							{
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, нет данных файла");
								filed_exept();
#endif
								return 1;
							}
						}
						else
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Ошибка сохранения, неизвестное взаимодейсвие с объектом");
							filed_exept();
#endif
							return 1;
						}
						break;
					}
					case type_struct::teleport:
					{
#ifdef LOG_SAVE
						buff_log.push_back(snos);
						buff_log.push_back("Смещение");
#endif

						buff.push_back(0x07);//байт типа объекта
						size_obj++;

						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("На страницу");
#endif
							buff.push_back(0x01);//байт типа взаимодействия			
							size_obj++;

							int num_page = string_to_int(sign(n, i)->data1);

							int size_big = num_page / 255;
							int size_min = num_page % 255;

							buff.push_back(char(size_big));
							buff.push_back(char(size_min));
							size_obj += 2;


							break;
						}
						case action:
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("На скрипт");
#endif
							buff.push_back(0x02);//байт типа взаимодействия
							size_obj++;

							int size_buff = sign(n, i)->data1.length();

							buff.push_back(size_buff);
							size_obj++;

							for (int z = 0; z < size_buff; z++)
							{
								buff.push_back(sign(n, i)->data1[z]);
								size_obj++;
							}


							break;
						}
						default:
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Ошибка сохранения, неизвестное взаимодейсвие с объектом");
							filed_exept();
#endif
							return 1;
							break;
						}
						break;
					}
					case type_struct::live2d:
					{
#ifdef LOG_SAVE
						buff_log.push_back(snos);
						buff_log.push_back("Модель Live2D");
#endif

						buff.push_back(0x08);//байт типа объекта
						size_obj++;


						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("SWICH");
#endif

							buff.push_back(0x01);//байт типа взаимодействия			
							size_obj++;

							switch (sign(n, i)->my_name)// имя спрайта как цифра
							{
							case any_enum::AY:
								buff.push_back(0x01);
								break;
							case any_enum::KI:
								buff.push_back(0x02);
								break;
							case any_enum::KA:
								buff.push_back(0x05);
								break;
							case any_enum::KU:
								buff.push_back(0x06);
								break;
							case any_enum::MA:
								buff.push_back(0x07);
								break;
							case any_enum::SA:
								buff.push_back(0x09);
								break;
							default:
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, неизвестное имя модели");
								filed_exept();
#endif
								return 1;
								break;
							}
							size_obj++;

							if (sign(n, i)->data1.length() != 1 || is_int(sign(n, i)->data1) == false)
							{
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, данные текстуры модели повреждены");
								filed_exept();
#endif
								return 1;
							}

							buff.push_back(sign(n, i)->data1[0]);
							size_obj++;

							if (sign(n, i)->data3.length() != any_enum::size_agr_model - 1)
							{
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, данные аргументов модели повреждены");
								filed_exept();
							}

							for (int z = 0; z < sign(n, i)->data3.length(); z++)
							{
								buff.push_back(sign(n, i)->data3[z]);
								size_obj++;
							
							}
						//	size_obj+= any_enum::size_agr_model-1;

							break;
						}
						case action:
						{
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("ACTION");
#endif

							buff.push_back(0x02);//байт типа взаимодействия			
							size_obj++;

							switch (sign(n, i)->my_name)// имя спрайта как цифра
							{
							case any_enum::AY:
								buff.push_back(0x01);
								break;
							case any_enum::KI:
								buff.push_back(0x02);
								break;
							case any_enum::KA:
								buff.push_back(0x05);
								break;
							case any_enum::KU:
								buff.push_back(0x06);
								break;
							case any_enum::MA:
								buff.push_back(0x07);
								break;
							case any_enum::SA:
								buff.push_back(0x09);
								break;
							default:
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, неизвестное имя модели");
								filed_exept();
#endif
								return 1;
								break;
							}
							size_obj++;

							switch (sign(n, i)->my_action)
							{
							case type_action::scale_lit:
							{
								buff.push_back(0x01);
								break;
							}
							case type_action::scale_mid:
							{
								buff.push_back(0x02);
								break;
							}
							case type_action::scale_big:
							{
								buff.push_back(0x03);
								break;
							}
							case type_action::LIVE2D_MOTION:
							{
								buff.push_back(0x04);
								break;
							}
							default:
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, неизвестный ACTION модели");
								filed_exept();
#endif
								return 1;
								break;
							}
							size_obj++;

							if (sign(n, i)->data1.length() != 1 || is_int(sign(n, i)->data1) == false)
							{
#ifdef LOG_SAVE
								buff_log.push_back(snos);
								buff_log.push_back("Ошибка сохранения, данные ACTION модели повреждены");
								filed_exept();
#endif
								return 1;
							}

							buff.push_back(sign(n, i)->data1[0]);
							size_obj++;

							break; 
						}
						default:
#ifdef LOG_SAVE
							buff_log.push_back(snos);
							buff_log.push_back("Ошибка сохранения, неизвестное взаимодейсвие с объектом");
							filed_exept();
#endif
							return 1;
							break;
						}
						break;
					}
					default:
#ifdef LOG_SAVE
						buff_log.push_back(snos);
						buff_log.push_back("Ошибка сохранения, неизвестный тип объекта");
						filed_exept();
#endif
						return 1;
						break;
					}


				}
				buff[bite_obj] = size_obj;
				size_box += size_obj;

			}
#ifdef LOG_SAVE
			buff_log.push_back(snos);
			buff_log.push_back("Успешная запись бокса");
#endif

			buff[bite_box] = size_box;
			size_page += size_box;

		}
		buff[bite_page] = size_page;

#ifdef LOG_SAVE
		buff_log.push_back(snos);
		buff_log.push_back("Успешная запись страницы");
#endif

	}
#ifdef LOG_SAVE
	buff_log.push_back(snos);
	buff_log.push_back("Запись в файл");
#endif
	for (int _n = 0; _n < buff.size(); _n++)
	{
		file << buff[_n];
	}
#ifdef LOG_SAVE
	buff_log.push_back(snos);
	buff_log.push_back("Успешно");
	for (int _n = 0; _n < buff_log.size(); _n++)
	{
		log << buff_log[_n];
	}
#endif
	file.close();
	log.close();
	return 0;
}

int load_script(std::string custom_dir)
{
	const size_t size_dir = 260;
	wchar_t file_dir[size_dir];
	string cur_name_script = "";
	memset(file_dir, NULL, size_dir);

	creator_obj = nullptr;
	map<int, page_obj*> ::const_iterator cur_iter = cur_page_data.cbegin();
	while (cur_iter != cur_page_data.cend())
	{
		delete cur_iter->second;
		cur_iter++;
	}
	cur_page_data.clear();
	cur_page_count = 0;//отчищаем что возможно
	cur_page = 0;
	if (custom_dir.length() == 0)
	{
		if (file_winapi(file_dir, size_dir, true) == false)
		{
			SetCurrentDirectory(main_dir);
			return 3;
		}
		else
		{
			SetCurrentDirectory(main_dir);
		}


		for (int n = 0; n < sizeof(file_dir); n++)
		{
			if (file_dir[n] == '\0')
				break;
			cur_name_script += file_dir[n];
		}
	}
	else//если грузим из скрипта - пытаемся загрузить из файла в папке скриптов
	{
		cur_name_script = dir_load_script + custom_dir;
	}

	if (cur_name_script.length() == 0)
		return 3;

	ifstream file(cur_name_script, ios::binary);

	if (!file)
		return 2;

#ifdef LOG_LOAD
	ofstream log(cur_name_script + ".log", ios::binary);
	vector<string>buff_log;
	string snos = string({ 0x0A }) + string({ 0x0D });
#endif


	unsigned char cur_bite;//байт для буфера взаимодействуем только с ним
	int n = 0;

	auto Get_cur_bite([&]()->int {
		char temp;
		file.read(&temp, 1);
		cur_bite = static_cast<unsigned char>(temp);
		n++;
		if (file.eof())
		{
#ifdef LOG_LOAD
			buff_log.push_back(snos);
			buff_log.push_back("Конец файла");
#endif
			return 1;
		}//недолжны приходить в конец
		return 0;
	});

	//auto HEX_TO_DEC([=](unsigned char hx)
	//{
	//	int s = 0;

	//	while (hx != 0x00)
	//	{
	//		hx -= 0x01;
	//		s++;
	//	}

	//	return s;
	//});

	auto filed_exept = [&]() {
#ifdef LOG_LOAD
		buff_log.push_back(snos);
		buff_log.push_back("Неудача");
		for (int _n = 0; _n < buff_log.size(); _n++)
		{
			log << buff_log[_n];
		}
		file.close();
		log.close();
#endif
	};

	while (Get_cur_bite() != 1)
	{
		page_obj cur_load_page = page_obj{};

		int size_page = cur_bite;//размер странички увеличивает каждый бокс своей размерностью
#ifdef LOG_LOAD
		buff_log.push_back(snos);
		buff_log.push_back("Начата загрузка страницы " + to_string(cur_page_count) + " по байту " + to_string(file.tellg()));
#endif
		for (n = 0; n < size_page; n++)
		{
			if (Get_cur_bite() == 1)
			{
				filed_exept();
				return 1;
			}
			int size_box = cur_bite;
			cur_load_page.cur_row_count[cur_load_page.cur_box_count] = 0;
			cur_load_page.cur_row_smeh[cur_load_page.cur_box_count] = 0;
			cur_load_page.visable_id_button[cur_load_page.cur_box_count][0] = false;
			cur_load_page.visable_id_button[cur_load_page.cur_box_count][1] = false;
			cur_load_page.visable_id_button[cur_load_page.cur_box_count][2] = false;
			cur_load_page.visable_id_button[cur_load_page.cur_box_count][3] = false;
#ifdef LOG_LOAD
			buff_log.push_back(snos);
			buff_log.push_back("Начата загрузка бокса " + to_string(cur_load_page.cur_box_count) + " по байту " + to_string(file.tellg()));
#endif
			for (int _n = 0; _n < size_box; _n++)
			{
				if (Get_cur_bite() == 1)
				{
					filed_exept();
					return 1;
				}
				int size_obj = cur_bite;//получаем размерность обжа
										//далее попробуем получить преданные для обжа(его тип и его взаимодействие)
				data_obj cur_obj = data_obj{};

#ifdef LOG_LOAD
				buff_log.push_back(snos);
				buff_log.push_back("Начата загрузка объекта " + to_string(cur_load_page.cur_row_count[cur_load_page.cur_box_count]) + " по байту " + to_string(file.tellg()));
#endif

				if (Get_cur_bite() == 1)
				{
					filed_exept();
					return 1;
				}

				switch (cur_bite)
				{
				case 0x01:
					cur_obj.my_type = type_struct::scene;
#ifdef LOG_LOAD
					buff_log.push_back(snos);
					buff_log.push_back("Объект scene");
#endif
					break;
				case 0x02:
					cur_obj.my_type = type_struct::sprite;
#ifdef LOG_LOAD
					buff_log.push_back(snos);
					buff_log.push_back("Объект sprite");
#endif
					break;
				case 0x03:
					cur_obj.my_type = type_struct::text;
#ifdef LOG_LOAD
					buff_log.push_back(snos);
					buff_log.push_back("Объект text");
#endif
					break;
				case 0x06:
					cur_obj.my_type = type_struct::audio;
#ifdef LOG_LOAD
					buff_log.push_back(snos);
					buff_log.push_back("Объект audio");
#endif
					break;
				case 0x07:
					cur_obj.my_type = type_struct::teleport;
#ifdef LOG_LOAD
					buff_log.push_back(snos);
					buff_log.push_back("Объект teleport");
#endif
					break;
				case 0x08:
					cur_obj.my_type = type_struct::live2d;
#ifdef LOG_LOAD
					buff_log.push_back(snos);
					buff_log.push_back("Объект Live2d Model");
#endif
					break;
				default:
#ifdef LOG_LOAD
					buff_log.push_back(snos);
					buff_log.push_back("Неизвестный объект по байту " + to_string(file.tellg()));
#endif

					filed_exept();
					return 1;

					break;
				}

				if (Get_cur_bite() == 1)
				{
					filed_exept();
					return 1;
				}

				if (cur_bite == 0x01)
				{
					cur_obj.my_inter = type_interactions::swich;
#ifdef LOG_LOAD
					buff_log.push_back(snos);
					buff_log.push_back("Взаимодействие swich");
#endif
				}
				else if (cur_bite == 0x02)
				{
					cur_obj.my_inter = type_interactions::action;
#ifdef LOG_LOAD
					buff_log.push_back(snos);
					buff_log.push_back("Взаимодействие action");
#endif
				}
				else
				{
#ifdef LOG_LOAD
					buff_log.push_back(snos);
					buff_log.push_back("Неизвестное взаимодействия по байту " + to_string(file.tellg()));
#endif

					filed_exept();
					return 1;

				}

				int size_cur_type = 0;//размерность которая должна быть
				switch (cur_obj.my_type)//здесь читаем какая она должна быть
				{
				case type_struct::scene:
				{
					switch (cur_obj.my_inter)
					{
					case type_interactions::swich:
					{
						size_cur_type = 6;
						break;
					}
					case type_interactions::action:
					{

						size_cur_type = 4;
						break;
					}
					default:
						filed_exept();
						return 1;
						break;
					}
					break;
				}
				case type_struct::sprite:
				{
					switch (cur_obj.my_inter)
					{
					case type_interactions::swich:
					{
						size_cur_type = 9;
						break;
					}
					case type_interactions::action:
					{

						size_cur_type = 5;
						break;
					}
					default:
						filed_exept();
						return 1;
						break;
					}
					break;
				}
				case type_struct::text:
				{
					switch (cur_obj.my_inter)
					{
					case type_interactions::swich:
					{
						size_cur_type = 5;
						break;
					}
					case type_interactions::action:
					{

						size_cur_type = 4;
						break;
					}
					default:
						filed_exept();
						return 1;
						break;
					}
					break;
				}
				case type_struct::audio:
				{
					switch (cur_obj.my_inter)
					{
					case type_interactions::action:
					{

						size_cur_type = 5;
						break;
					}
					default:
						filed_exept();
						return 1;
						break;
					}
					break;
				}
				case type_struct::teleport:
				{
					switch (cur_obj.my_inter)
					{
					case type_interactions::swich:
					{
						size_cur_type = 5;//всегда байт ровно 5 (3 описания 2 номер страницы)
						break;
					}
					case type_interactions::action://в смещениях на скрипт неизвестное количество байтов
					{
						size_cur_type = 4;//минимум байт 4 (3 описания 1 количество символов
						break;
					}
					default:
						filed_exept();
						return 1;
						break;
					}
					break;
				}
				case  type_struct::live2d:
				{
					switch (cur_obj.my_inter)
					{
					case type_interactions::swich:
					{
						size_cur_type = 40;//всегда байт ровно (3 описания, 1 имя, 1 текстура, 35 аргументы модели)
						break;
					}
					case type_interactions::action://в смещениях на скрипт неизвестное количество байтов
					{
						size_cur_type = 6;//всегда байт ровно (3 описания, 1 имя, 1 тип действия, и 1 номер motion)
						break;
					}
					default:
						filed_exept();
						return 1;
						break;
					}
					break;
				}
				default:
					filed_exept();
					return 1;
					break;
				}
				if (cur_obj.my_type == type_struct::teleport)//идет проверка хоть кокаято для текста и смещения
				{
					if (cur_obj.my_inter == type_interactions::action)
					{
						if (size_obj < size_cur_type)// должно быть минимальное количество байт для объекта
						{
#ifdef LOG_LOAD

							buff_log.push_back(snos);
							buff_log.push_back("Ошибка - нехватка байтов описания " + to_string(file.tellg()));
#endif
							filed_exept();
							return 1;
						}
					}
					else
					{
						if (size_obj != size_cur_type)
						{
#ifdef LOG_LOAD

							buff_log.push_back(snos);
							if (size_obj > size_cur_type)
								buff_log.push_back("Ошибка - переполнение байтов описания " + to_string(file.tellg()));
							else
								buff_log.push_back("Ошибка - нехватка байтов описания " + to_string(file.tellg()));
#endif
							filed_exept();
							return 1;
						}
					}
				}
				else
				{
					if (size_obj != size_cur_type)
					{
#ifdef LOG_LOAD

						buff_log.push_back(snos);
						if (size_obj > size_cur_type)
							buff_log.push_back("Ошибка - переполнение байтов описания " + to_string(file.tellg()));
						else
							buff_log.push_back("Ошибка - нехватка байтов описания " + to_string(file.tellg()));
#endif
						filed_exept();
						return 1;
					}
				}


				_n += size_obj; //size_cur_type - поменял что прибовлять РАСПИСАТЬ - смещает байты для понимания когда закончится бокс, по правилу цикла
								//для текста и смещения нужно будет добовлять побайтово вручную

				switch (cur_obj.my_type)//здесь дозаполняем объектик после всех проверок
				{
				case type_struct::scene:
				{
					switch (cur_obj.my_inter)
					{
					case type_interactions::swich:
					{
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						if (cur_bite == 0x01)
						{
							cur_obj.my_swich = SIMPLE;
						}
						else if (cur_bite == 0x02)
						{
							cur_obj.my_swich = NULL_TIME;
						}
						else
						{
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Неизвестный тип свича по байту " + to_string(file.tellg()));
							filed_exept();
#endif
							return 1;//неизвестный байт подтипа
						}


						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						if (cur_bite == 0x01)
						{
							cur_obj.data1 = "BG";
						}
						else if (cur_bite == 0x02)
						{
							cur_obj.data1 = "CG";
						}
						else
						{
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Неизвестный тип дирректории по байту " + to_string(file.tellg()));
							filed_exept();
#endif
							return 1;//неизвестный тип
						}


						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						cur_obj.data2 = std::to_string(static_cast<int>(cur_bite));//нужна проверка на предел картинок



						break;
					}
					case type_interactions::action:
					{
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						switch (cur_bite)
						{
						case 0x01:
						{
							cur_obj.my_action = type_action::SHAKE;
							break;
						}
						case 0x02:
						{
							cur_obj.my_action = type_action::PUNCH;
							break;
						}
						case 0x03:
						{
							cur_obj.my_action = type_action::BLACK_IN;
							break;
						}
						case 0x04:
						{
							cur_obj.my_action = type_action::BLACK_OUT;
							break;
						}
						case 0x05:
						{
							cur_obj.my_action = type_action::POLOS_OUT;
							break;
						}
						case 0x06:
						{
							cur_obj.my_action = type_action::POLOS_OUT;
							break;
						}
						case 0x07:
						{
							cur_obj.my_action = type_action::SLASH_WS_IN;
							break;
						}
						case 0x08:
						{
							cur_obj.my_action = type_action::SLASH_WS_OUT;
							break;
						}
						case 0x09:
						{
							cur_obj.my_action = type_action::SLASH_AD_IN;
							break;
						}
						case 0x10:
						{
							cur_obj.my_action = type_action::SLASH_AD_OUT;
							break;
						}
						case 0x11:
						{
							cur_obj.my_action = type_action::MBLACK_IN;
							break;
						}
						case 0x12:
						{
							cur_obj.my_action = type_action::MBLACK_OUT;
							break;
						}
						case 0x13:
						{
							cur_obj.my_action = type_action::MPOLOS_OUT;
							break;
						}
						case 0x14:
						{
							cur_obj.my_action = type_action::MPOLOS_OUT;
							break;
						}
						case 0x15:
						{
							cur_obj.my_action = type_action::MSLASH_WS_IN;
							break;
						}
						case 0x16:
						{
							cur_obj.my_action = type_action::MSLASH_WS_OUT;
							break;
						}
						case 0x17:
						{
							cur_obj.my_action = type_action::MSLASH_AD_IN;
							break;
						}
						case 0x18:
						{
							cur_obj.my_action = type_action::MSLASH_AD_OUT;
							break;
						}
						default:
						{
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Неизвестный тип экшона по байту" + to_string(file.tellg()));
#endif
							filed_exept();
							return 1;//неизвестный байт подтипа
							break;
						}
						}



						break;
					}
					default:
						filed_exept();
						return 1;
						break;
					}
					break;
				}
				case type_struct::sprite:
				{

					auto Get_name_bite([&]() {//функция для определения имени
						switch (cur_bite)
						{
						case 0x01:
							cur_obj.my_name = any_enum::AY;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - AY " + cur_obj.data2);
#endif
							break;
						case 0x02:
							cur_obj.my_name = any_enum::KI;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - KI " + cur_obj.data2);
#endif
							break;
						case 0x03:
							cur_obj.my_name = any_enum::DA;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - DA " + cur_obj.data2);
#endif
							break;
						case 0x04:
							cur_obj.my_name = any_enum::AK;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - AK " + cur_obj.data2);
#endif
							break;
						case 0x05:
							cur_obj.my_name = any_enum::KA;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - KA " + cur_obj.data2);
#endif
							break;
						case 0x06:
							cur_obj.my_name = any_enum::KU;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - KU " + cur_obj.data2);
#endif
							break;
						case 0x07:
							cur_obj.my_name = any_enum::MA;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - MA " + cur_obj.data2);
#endif
							break;
						case 0x08:
							cur_obj.my_name = any_enum::RO;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - RO " + cur_obj.data2);
#endif
							break;
						case 0x09:
							cur_obj.my_name = any_enum::SA;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - SA " + cur_obj.data2);
#endif
							break;
						case 0x10:
							cur_obj.my_name = any_enum::SE;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - SE " + cur_obj.data2);
#endif
							break;
						case 0x11:
							cur_obj.my_name = any_enum::YO;
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Персонаж - YO " + cur_obj.data2);
#endif
							break;
						default:
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Неизвестный тип персонажа по байту " + to_string(file.tellg()));
#endif
							filed_exept();
							return 1;
							break;
						}
						return 0;
					});
					switch (cur_obj.my_inter)
					{
					case type_interactions::swich:
					{
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}

						if (Get_name_bite() == 1)// имя спрайта как цифра
						{
							filed_exept();
							return 1;
						}



						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}

						switch (cur_bite)
						{
						case 0x01:
						{
							cur_obj.data1 = "C";
							break;
						}
						case  0x02:
						{
							cur_obj.data1 = "L";
							break;
						}
						case  0x03:
						{
							cur_obj.data1 = "R";
							break;
						}
						case 0x11:
						{
							cur_obj.data1 = "C_COSP";
							break;
						}
						case 0x12:
						{
							cur_obj.data1 = "L_COSP";
							break;
						}
						case 0x13:
						{
							cur_obj.data1 = "R_COSP";
							break;
						}
						case 0x21:
						{
							cur_obj.data1 = "C_OLD";
							break;
						}
						case  0x22:
						{
							cur_obj.data1 = "L_OLD";
							break;
						}
						case 0x23:
						{
							cur_obj.data1 = "R_OLD";
							break;
						}
						case 0x88:
						{
							cur_obj.hide = true;
							break;
						}
						default:
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Неизвестный тип текстуры спрайта по байту " + to_string(file.tellg()));
#endif
							filed_exept();
							return 1;
							break;
						}

						if (cur_obj.hide == false)
						{
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Появляется");
							buff_log.push_back(snos);
							buff_log.push_back("Тип текстуры " + cur_obj.data1);
#endif
							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}

							if (cur_bite > 0x03 || cur_bite < 0x01)
							{
#ifdef LOG_LOAD
								buff_log.push_back(snos);
								buff_log.push_back("Неизвестный номер текстуры по байту " + to_string(file.tellg()));
#endif
								filed_exept();
								return 1;//нет такой текстуры																				 
							}


							cur_obj.data2 = std::to_string(int(cur_bite)); //номер текстурки этого типа 
#ifdef LOG_LOAD
							buff_log.push_back(" Текстура " + cur_obj.data2);
#endif


							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}
							cur_obj.data3 = std::to_string(int(cur_bite)); //номер эмоции типа
#ifdef LOG_LOAD
							buff_log.push_back(" Эмоция " + cur_obj.data3);
#endif
							if (cur_bite > 0x14 || cur_bite < 0x01)
							{
#ifdef LOG_LOAD
								buff_log.push_back(snos);
								buff_log.push_back(" Неизвестная эмоция по байту " + to_string(file.tellg()));
#endif
								filed_exept();
								return 1;//нет такой текстуры
							}

							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}

							switch (cur_bite)
							{
							case 0x01:
								cur_obj.my_position = any_enum::left;
#ifdef LOG_LOAD
								buff_log.push_back(snos);
								buff_log.push_back("Позиция left");
#endif
								break;
							case 0x02:
								cur_obj.my_position = any_enum::left_centr;
#ifdef LOG_LOAD
								buff_log.push_back(snos);
								buff_log.push_back("Позиция left_centr");
#endif
								break;
							case 0x03:
								cur_obj.my_position = any_enum::centr;
#ifdef LOG_LOAD
								buff_log.push_back(snos);
								buff_log.push_back("Позиция centr");
#endif
								break;
							case 0x04:
								cur_obj.my_position = any_enum::right_centr;
#ifdef LOG_LOAD
								buff_log.push_back(snos);
								buff_log.push_back("Позиция right_centr");
#endif
								break;
							case 0x05:
								cur_obj.my_position = any_enum::right;
#ifdef LOG_LOAD
								buff_log.push_back(snos);
								buff_log.push_back("Позиция right");
#endif
								break;
							default:
#ifdef LOG_LOAD
								buff_log.push_back(snos);
								buff_log.push_back("Неизвестная позиция по байту " + to_string(file.tellg()));
#endif
								filed_exept();
								return 1;
								break;
							}

							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}

							switch (cur_bite)//его свич
							{//LTR, RTL, SIMPLE, NULL_TIME
							case 0x01:
								cur_obj.my_swich = SIMPLE;
								break;
							case 0x02:
								cur_obj.my_swich = LTR;
								break;
							case 0x03:
								cur_obj.my_swich = RTL;
								break;
							case 0x04:
								cur_obj.my_swich = NULL_TIME;
								break;
							case 0x05:
								cur_obj.my_swich = DTT;
								break;
							default:
#ifdef LOG_LOAD
								buff_log.push_back(snos);
								buff_log.push_back("Неизвестный тип свича по байту " + to_string(file.tellg()));
#endif
								filed_exept();
								return 1;
								break;
							}
						}
						else
						{
#ifdef LOG_LOAD
							buff_log.push_back(snos);
							buff_log.push_back("Пропадает");
#endif
							//пропуск пустых байтов - ибо спрайт пропадает
							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}
							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}
							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}
							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}
							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}

							switch (cur_bite)//его свич
							{//LTR, RTL, SIMPLE, NULL_TIME
							case 0x01:
								cur_obj.my_swich = SIMPLE;
								break;
							case 0x02:
								cur_obj.my_swich = LTR;
								break;
							case 0x03:
								cur_obj.my_swich = RTL;
								break;
							case 0x04:
								cur_obj.my_swich = NULL_TIME;
								break;
							case 0x05:
								cur_obj.my_swich = DTT;
								break;
							default:
#ifdef LOG_LOAD
								buff_log.push_back(snos);
								buff_log.push_back("Неизвестный тип свича по байту " + to_string(file.tellg()));
#endif
								filed_exept();
								return 1;
								break;
							}

						}


						break;
					}
					case type_interactions::action:
					{
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						if (Get_name_bite() == 1)// имя спрайта как цифра
						{
							filed_exept();
							return 1;
						}

						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						switch (cur_bite)//байт подтипа взаимодействия
						{
						case 0x01:
							cur_obj.my_action = MINIJUMP;
							break;
						case 0x02:
							cur_obj.my_action = JUMP;
							break;
						case 0x03:
							cur_obj.my_action = scale_lit;
							break;
						case 0x04:
							cur_obj.my_action = scale_mid;
							break;
						case 0x05:
							cur_obj.my_action = scale_big;
							break;
						case 0x06:
							cur_obj.my_action = POS_C;
							break;
						case 0x07:
							cur_obj.my_action = POS_R;
							break;
						case 0x08:
							cur_obj.my_action = POS_RC;
							break;
						case 0x09:
							cur_obj.my_action = POS_L;
							break;
						case 0x10:
							cur_obj.my_action = POS_LC;
							break;
						default:
							filed_exept();
							return 1;
							break;
						}

						break;
					}
					default:
						filed_exept();
						return 1;
						break;
					}
					break;
				}
				case type_struct::text:
				{
					switch (cur_obj.my_inter)
					{
					case type_interactions::swich://ПОКА НЕ ПРОВЕРЕНЫЙ ВАРИАНТ ВЗЯТИЯ ТЕКСТА ИЗ СКРИПТА
					{
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						int size_name = cur_bite;
						for (int n = 1; n < size_name; n++)
						{
							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}
							cur_obj.data1 += cur_bite;
						}

						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						int size_text = cur_bite;
						for (int n = 1; n < size_text; n++)
						{
							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}
							cur_obj.data2 += cur_bite;
						}

						break;
					}
					case type_interactions::action:
					{
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						if (cur_bite == 0x01)
						{
							cur_obj.my_action = SHOW_BOX;
						}
						else if (cur_bite == 0x02)
						{
							cur_obj.my_action = HIDE_BOX;
						}

						else
						{
							filed_exept();
							return 1;
						}

						break;
					}
					default:
						filed_exept();
						return 1;
						break;
					}
					break;
				}
				case type_struct::audio:
				{
					switch (cur_obj.my_inter)
					{
					case type_interactions::action:
					{
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						cur_obj.data1 = to_string(int(cur_bite) - 1);//байт подтипа объекта НЕТ ПРОВЕРКИ


						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						cur_obj.data2 = to_string(int(cur_bite) - 1);//байт номера аудишки НЕТ ПРОВЕРКИ																			 
						break;
					}
					default:
					{
						filed_exept();
						return 1;
					}
					break;
					}
					break;
				}
				case type_struct::teleport://обработчик для телепорта един
				{
					switch (cur_obj.my_inter)
					{
					case type_interactions::swich:// у свича (свич это смещение на страницу) выделено 2 байта на описание номера странички
					{
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						int size_buff = int(cur_bite) * 255;
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						size_buff += int(cur_bite);

						cur_obj.data1 = std::to_string(size_buff);


						break;
					}
					case type_interactions::action:
					{
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						int size_buff = int(cur_bite);

						for (int z = 0; z < size_buff; z++)
						{
							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}
							cur_obj.data1 += cur_bite;
						}

						break;
					}
					default:
					{
						filed_exept();
						return 1;
						break;
					}
					}
					break;
				}
				case type_struct::live2d:
				{
					if (Get_cur_bite() == 1)
					{
						filed_exept();
						return 1;
					}

					switch (cur_bite)// имя спрайта как цифра
					{
					case 0x01:
						cur_obj.my_name = any_enum::AY;
						break;
					case 0x02:
						cur_obj.my_name = any_enum::KI;
						break;
					case 0x05:
						cur_obj.my_name = any_enum::KA;
						break;
					case 0x06:
						cur_obj.my_name = any_enum::KU;
						break;
					case 0x07:
						cur_obj.my_name = any_enum::MA;
						break;
					case 0x09:
						cur_obj.my_name = any_enum::SA;
						break;
					default:
						filed_exept();
						return 1;
						break;
					}

					switch (cur_obj.my_inter)
					{
					case type_interactions::swich:// у свича (свич это смещение на страницу) выделено 2 байта на описание номера странички
					{

						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}

						cur_obj.data1 = int(cur_bite);
						if (is_int(cur_obj.data1) == false)
						{
							filed_exept();
							return 1;
						}

						for (int z = 0; z < any_enum::size_agr_model-1; z++)
						{
							if (Get_cur_bite() == 1)
							{
								filed_exept();
								return 1;
							}
							cur_obj.data3 += int(cur_bite);
						}

						break;
					}
					case type_interactions::action:
					{
						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}
						

						switch (cur_bite)
						{
						case 0x01:
						{
							cur_obj.my_action = type_action::scale_lit;
							break;
						}
						case 0x02:
						{
							cur_obj.my_action = type_action::scale_mid;
							break;
						}
						case 0x03:
						{
							cur_obj.my_action = type_action::scale_big;
							break;
						}
						case 0x04:
						{
							cur_obj.my_action = type_action::LIVE2D_MOTION;
							break;
						}
						default:
							filed_exept();
							return 1;
							break;
						}

						if (Get_cur_bite() == 1)
						{
							filed_exept();
							return 1;
						}

						cur_obj.data1 = int(cur_bite);

						if (is_int(cur_obj.data1) == false)
						{
							filed_exept();
							return 1;
						}

						break;
					}
					default:
					{
						filed_exept();
						return 1;
						break;
					}
					}

					break;
				}
				default:
					filed_exept();
					return 1;
					break;
				}


				cur_load_page.intedex_data[cur_load_page.cur_box_count][cur_load_page.cur_row_count[cur_load_page.cur_box_count]] = cur_obj;
				cur_load_page.visable_id_button[cur_load_page.cur_box_count][cur_load_page.cur_row_count[cur_load_page.cur_box_count]] = true;//не уверен что работает правильно
				cur_load_page.cur_row_count[cur_load_page.cur_box_count]++;
			}
			cur_load_page.cur_box_count++;
		}

		cur_load_page.visable_id_box[0] = cur_load_page.cur_box_count > 0 ? true : false;
		cur_load_page.visable_id_box[1] = cur_load_page.cur_box_count > 1 ? true : false;
		cur_load_page.visable_id_box[2] = cur_load_page.cur_box_count > 2 ? true : false;




		cur_page_data[cur_page_count] = new page_obj(cur_load_page);
		cur_page_count++;

	}
#ifdef LOG_LOAD
	if (buff_log.size() == 0)
	{
		filed_exept();
		return 1;
	}
	buff_log.push_back(string({ 0x0A }) + string({ 0x0D }));
	buff_log.push_back("Успешно");
	for (int _n = 0; _n < buff_log.size(); _n++)
	{
		log << buff_log[_n];
	}
#endif
	return 0;
}

bool load_script_exept(std::string dir)
{
	switch (load_script(dir))
	{
	case 0:
	{
		MessageBoxA(nullptr, "Загрузка успешна!", "Уведомление", MB_OK);
		return true;
		break;
	}
	case 1:
	{
		MessageBoxA(nullptr, "Ошибка загрузки!", "Ошибка", MB_OK | MB_ICONERROR);
		return false;
		break;
	}
	case 2:
	{
		MessageBoxA(nullptr, "Ошибка открытия файла!", "Ошибка", MB_OK | MB_ICONERROR);
		return false;
		break;
	}
	default:
		return false;
		break;
	}
}



void init_game_mode(Node *Creator_Mode)
{
	Game_Mode = Creator_Mode->getChildByTag(3028);
	Scene1 = Game_Mode->getChildByTag(1);
	Scene2 = Game_Mode->getChildByTag(2);
	Sprite1 = Game_Mode->getChildByTag(3);
	Sprite2 = Game_Mode->getChildByTag(4);
	Sprite3 = Game_Mode->getChildByTag(5);
	Sprite4 = Game_Mode->getChildByTag(6);
	Sprite5 = Game_Mode->getChildByTag(7);
	Sprite6 = Game_Mode->getChildByTag(8);
	Text_Box = Game_Mode->getChildByTag(4535);
	OREL = Game_Mode->getChildByTag(2637);
	ORER = Game_Mode->getChildByTag(2634);
	OREU = Game_Mode->getChildByTag(2628)->getChildByTag(111);
	AUDIONODE = Game_Mode->getChildByTag(2627);
	Label_text = static_cast<ui::Text*>(Game_Mode->getChildByTag(2642));
	Label_name = static_cast<ui::Text*>(Game_Mode->getChildByTag(2642));
	Sprite1->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);
	Sprite2->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);
	Sprite3->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);
	Sprite4->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);
	Sprite5->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);
	Sprite6->setAnchorPoint(ANCHOR_POINT_SPRITE_NODE);


	SWICHMODE->setTitleText("CREATORMODE");

	BLACK_SORITE_MODE->setVisible(true);
	Game_Mode->setVisible(true);

	cur_page = 0;


	for (int n = 0; n < cur_page_count; n++)
	{
		auto gpi([=]()
		{
			return cur_page_data[n];
		});
		auto sign = ([=](int &x, int &y) {
			return &gpi()->intedex_data[x][y];
		});
		vector<Object_Scene*> objs;
		vector<type_struct::type_object> objs_type;
		vector <type_interactions> intrs;
		vector<type_swich> swichs;
		vector<type_action> actions;

		for (int n = 0; n < gpi()->cur_box_count; n++)
		{
			for (int i = 0; i < gpi()->cur_row_count[n]; i++)
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
							objs.push_back(new Object_Scene(sign(n, i)->data1, string_to_int(sign(n, i)->data2)));
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
								auto sprite = new Object_Sprite(sign(n, i)->my_name);
								objs.push_back(sprite);
								objs_type.push_back(sign(n, i)->my_type);
								intrs.push_back(sign(n, i)->my_inter);
								swichs.push_back(sign(n, i)->my_swich);
							}
							else
							{
								auto sprite = new Object_Sprite(
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
							auto sprite = new Object_Sprite(
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
						break;
					}
					case type_struct::ore:
					{
						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
							break;
						}
						case action:
						{// куча проверок тупых на то чтоб не вызывал левый пока он заюзан и т.д.
							int cur_sprite = string_to_int(sign(n, i)->data1);
							auto cur_pos = sign(n, i)->my_position;


							if (cur_sprite <0 || cur_sprite>63)
								break;
							if (cur_pos == any_enum::centr)
								break;

							if (((pre_save::ORE_LEFT_VIS == true && cur_pos == any_enum::left) || (pre_save::ORE_RIGHT_VIS == true && cur_pos == any_enum::right))
								&& sign(n, i)->my_action == SHOW_BOX)
								break;
							if (((pre_save::ORE_LEFT_VIS == false && cur_pos == any_enum::left) || (pre_save::ORE_RIGHT_VIS == false && cur_pos == any_enum::right))
								&& sign(n, i)->my_action == HIDE_BOX)
								break;

							auto data = new Object_ORE(cur_sprite, cur_pos);
							objs.push_back(data);
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
					case type_struct::condition:
					{

						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
							break;
						}
						case action:
						{
							int cur_point = string_to_int(sign(n, i)->data1);
							int use_point = sign(n, i)->my_name == any_enum::NONE ? 0 : cur_point < 0 || cur_point >100 ? 0 : cur_point;
							auto use_ore = sign(n, i)->my_position == any_enum::left ? any_enum::OREL : sign(n, i)->my_position == any_enum::right ? any_enum::ORER : any_enum::nonuse;
							auto data = new Object_Condition(pre_save::pre_ore_data,
								sign(n, i)->my_name == any_enum::NONE ? any_enum::NONE : sign(n, i)->my_name,
								use_point,
								use_ore);
							objs.push_back(data);
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
					case type_struct::audio:
					{
						switch (sign(n, i)->my_inter)
						{
						case swich:
						{
							break;
						}
						case action:
						{

							int cur_type = string_to_int(sign(n, i)->data1);
							auto cur_dir = sign(n, i)->data2;
							if (cur_type <0 || cur_type>1)
								break;

							auto data = new Object_Noise(static_cast<type_noise>(cur_type), cur_dir);
							objs.push_back(data);
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
						break;
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
			selected_page = new Page(objs, objs_type, intrs, swichs, actions);
		}
	}


	SWICHMODE->addClickEventListener([=](Ref*)
	{

		cur_page = 0;

		BLACK_SORITE_MODE->setVisible(false);
		Game_Mode->setVisible(false);
		init_creator_mode(Creator_Mode);
	});
	//cur_page = -1;
	//BUTTONCLICK->addClickEventListener([=](Ref*)
	//{
	//	if (int(all_pages.size()) > cur_page+1)
	//	{
	//		cur_page++;

	//		Game_Mode->stopAllActions();
	//		Scene1->stopAllActions();
	//		Scene2->stopAllActions();
	//		Sprite1->stopAllActions();
	//		Sprite2->stopAllActions();
	//		Sprite3->stopAllActions();
	//		Sprite4->stopAllActions();
	//		Sprite5->stopAllActions();
	//		Sprite6->stopAllActions();
	//		OREL->stopAllActions();// вернуть их на позиции(функция скипа - быстрые экшоны и свичи) тут можно сделать сброс позиций на изначальные того что двигается
	//		ORER->stopAllActions();
	//		OREU->stopAllActions();
	//		OREU->getParent()->stopAllActions();
	//		Text_Box->stopAllActions();

	//		Label_text->setString("");
	//		Label_name->setString("");


	//		all_pages[cur_page]->draw();
	//		
	//	}
	//	else
	//	{
	//		Game_Mode->stopAllActions();
	//		Scene1->stopAllActions();
	//		Scene2->stopAllActions();
	//		Sprite1->stopAllActions();
	//		Sprite2->stopAllActions();
	//		Sprite3->stopAllActions();
	//		Sprite4->stopAllActions();
	//		Sprite5->stopAllActions();
	//		Sprite6->stopAllActions();
	//		OREL->stopAllActions();// вернуть их на позиции(функция скипа - быстрые экшоны и свичи) тут можно сделать сброс позиций на изначальные того что двигается
	//		ORER->stopAllActions();
	//		OREU->stopAllActions();
	//		OREU->getParent()->stopAllActions();
	//		Text_Box->stopAllActions();

	//		Label_text->setString("");
	//		Label_name->setString("");


	//		all_pages.clear();
	//		cur_page = 0;

	//		BLACK_SORITE_MODE->setVisible(false);
	//		Game_Mode->setVisible(false);
	//		init_creator_mode(Creator_Mode);
	//	}
	//});
}
