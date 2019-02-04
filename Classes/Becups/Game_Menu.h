#include <2d\CCSprite.h>
//Определяем классы для текста и для спрайта. А также объявляем их методы.

#include <memory> // для использования smart_pointer
#include <vector>
#include "AudioEngine.h"
#include "Viewconsole.h"
using namespace std;
using namespace std::chrono;
using namespace cocos2d;



int nump = 0; // управляет выходом из потока субтитров
vector<string> setscripts; // взятие деррикторий скриптов
vector<string> setsprites; // взятие деррикторий спрайтов
vector<string> setscene; // взятие деррикторий сцен
vector<string> setmusic; // взятие деррикторий музыки
vector<string> setsystemse; // взятие деррикторий музыки
vector<string> setCG; // взятие деррикторий CG
vector<string> setcomment; // взятие деррикторий комментариев
vector<string> setsub; // взятие деррикторий субтитров комментариев
vector<string> setore; // взятие дирректорий картинок ORE

static bool Skip_All, ORE_old, Com_twoshot, Tips_twoshot, Text_old, Autosave1, Autosave2, Musalb; // Все настройки типа bool

static float All_Volume, Background_Volume, System_Volume, Game_Volume, Voice_Volume; // Вся громкость

static int Speed_Skip_Text, Speed_Text, Speed_Auto_Text; // Скорость режима пропуска текста, текста, и режима авто чтения

static int Background_id = NULL, System_id = NULL, Game_id = NULL, Voice_id = NULL; // id потоков аудио будет здесь

static bool temp_sw = false; // Переменная которая указывает были ли изменения в настройках по умолчанию false

class SPRITEBOX;


bool nump_nf[3] = { false, false, false }; //отвечает за потоки морганий спрайтов

Game *Head_Menu;


//vector<thread*> p_exon; // должен хранить адрес потоков exon

void background_smooth(bool on);
void needbeex(bool *x, int *po); // выполняет перелачу аргумента для закрытия старого потока при увелечинии потоков, описана в Main_Menu
void black(cocos2d::Sprite* scene, int n, Node *Game_Mode); //ввергает экран во тьму
void un_black(cocos2d::Sprite* scene, int n, Node *Game_Mode); // убирает тьму
void Show_and_Hide(cocos2d::Node *Game_Mode, string dir, vector<SPRITEBOX> sprite, vector<bool*> task_oldblink, bool ignore_scene, bool ignore_sprite, bool *task);
void Show_text_box(cocos2d::Sprite* Text_Box); // показывает текст бокс
void Hide_text_box(cocos2d::Sprite* Text_Box); // прячет текст бокс
void search_voice(vector<string> *out, const char *filename, string num_voice); // ищет файл озвучки из дирректории озвучек
void Switch_scene(cocos2d::Node *Game_Mode, string dir, vector<SPRITEBOX> sprite, vector<bool*> task_oldblink, bool ignore_scene, bool ignore_sprite, bool *task, int preload);
void Swich_Sprite(cocos2d::Node *image, cocos2d::Node *swichimage, int n, string custom_swich, bool hide_mode, bool *task);
//создает эффект перехода между сменяемыми сценами

void Get_sprite(Node *Game_Mode, vector<SPRITEBOX> sprite, vector<bool*> task_oldblink, vector<bool> simple, bool *task); // осуществляет выбор между выводом спрайта или упрощенного вывода спрайта
void Get_blink(Node *Box_scene, SPRITEBOX sprite, bool *task); // создает моргание для конкретного спрайта
void Get_Speak(Node *Box_Sprites, SPRITEBOX sprite, vector<bool> speak, bool *task, bool *stop_task); //создает движение рта для конкретного спрайта
static mutex lockthread;

void letter(cocos2d::ui::Text* set_text, shared_ptr<char> p_buff, bool *task, Node *Game_Mode); // выводит по буквенно текст из buff
 
void shake(Node *scene);
void use_Auto_Mode(Node *Game_Mode); // отдельная функция под поток авто режима


struct chek_id
{
	string id1 = "empty";
	string id2 = "empty";
	string id3 = "empty";
};

chek_id active_sprite;

class SPRITEBOX
{
private:

	int id;
	int name;
	vector<string> blink; // глаза

	vector<string> speak; // рот

	//SPRITE
	string sprite; 
	//SPRITE

	//SAMPLE
	string sprite_sample = "Sprites\\Samples\\Sample_Sprite.png";
	string blink_samle = "Sprites\\Samples\\Sample_Blink.png";
	string speak_sample = "Sprites\\Samples\\Sample_Speak.png";
	//SAMPLE
	
	string action = "None";
	bool hide = false; //отвечает за скрытие спрайта
	bool inf = false;
	
	vector<int> pos_x; //координаты по x
	vector<int> pos_y; //координаты по y
	char LCR = 'C'; //координаты по основному x по умолчанию центр  D - между левым и средним P - между правым и средним

	
	string custom_swich = "0"; // Переменная отвечающая за управление эффектом появления спрайта - если по умолчанию должна быть равна нулю есть два состаяния - движение слева на право - 1 и справа налево - 2
	
	
public:
	
	int Set_id(string chapter, bool hide)
	{
		if (chapter == active_sprite.id1)
		{
			if (hide == false)
				active_sprite.id1 = chapter;
			else
				active_sprite.id1 = "empty";

			return 1;
		}
		else if (chapter == active_sprite.id2)
		{
			if (hide == false)
				active_sprite.id2 = chapter;
			else
				active_sprite.id2 = "empty";

			return 2;
		}
		else if (chapter == active_sprite.id3)
		{
			if (hide == false)
				active_sprite.id3 = chapter;
			else
				active_sprite.id3 = "empty";

			return 3;
		}
		else if (active_sprite.id1 == "empty")
		{
			active_sprite.id1 = chapter;
			return 1;
		}
		else if (active_sprite.id2 == "empty")
		{
			active_sprite.id2 = chapter;
			return 2;
		}
		else if (active_sprite.id3 == "empty")
		{
			active_sprite.id3 = chapter;
			return 3;
		}
	}
	
	int Set_Sprite(vector<string> dir, vector<string> command) //Получает вектор дирректорий всех спрайтов и команды определяющие спрайт а также id
	{
		if (command[0] == "HIDE")
		{			
			this->id = Set_id(command[1], true);// ----------------------------------------------Сделать выход из спрайта по имени------------------------------------------ 
			this->hide = true;
			if (command.size() > 2)
			{
				if (command[2] == "<actionsprite>")
				{
					command.erase(command.begin() + 2);
					action = command[2];
					command.erase(command.begin() + 2);
				}
				if (command.size() > 2)
				{
					custom_swich = string(command[2]);
				}
			}
			this->inf = true;
			return this->id;
		}

		this->id = Set_id(command[0], false); // определение id спрайта

		if (command[1] == "<actionsprite>")
		{
			command.erase(command.begin()+1);
			action = command[1];
			command.erase(command.begin() + 1);
			if (command.size() < 2)
				return this->id;
		}


		for (int i = 0; i < dir.size(); i++)
		{
			if (string(dir[i]) == string("{" + command[0] + "}"))
			{
				while (string(dir[i]) != string("{/" + command[0] + "}"))
				{
					i++;
					if (string(dir[i]) == string("|" + command[1] + "|"))
					{
						i++;
						sprite = dir[i];
						while (string(dir[i]) != string("|/" + command[1] + "|"))
						{
							i++;
							if (string(dir[i]) == string(command[2]))
							{
								while (string(dir[i + 4]) != string("/" + command[2]))
								{
									i++;
									blink.push_back(dir[i]);
									speak.push_back(dir[i + 3]);
								}

							}
						}
					}
				}
			}
		}
		this->inf = true;
		if (command.size() > 3) // если есть - определить положение
		{
			LCR = string(command[3])[0];
			if (command.size() > 4)
			{
					custom_swich = string(command[4]);
			}
		}
/*
		const char AY[] = { 'A', 'Y' };
		const char KY[] = { 'K', 'Y' };
		const char KU[] = { 'K', 'U' };
		const char MA[] = { 'M', 'A' };
		const char KI[] = { 'K', 'I' };
		const char DA[] = { 'D', 'A' };
		const char SA[] = { 'S', 'A' };
		const char SI[] = { 'S', 'I' };*/

		if (command[0] == "AY")
			name = 0;
		if (command[0] == "KY")
			name = 1;
		if (command[0] == "KU")
			name = 2;
		if (command[0] == "MA")
			name = 3;
		if (command[0] == "KI")
			name = 4;
		if (command[0] == "DA")
			name = 5;
		if (command[0] == "SA")
			name = 6;
		if (command[0] == "SI")
			name = 7;

		if (command[0] == "KI") //-------------------------------KIRINO-------------------------------//
		{
			if (command[1] == "1C" || command[1] == "2C" || command[1] == "3C" || command[1] == "1C_OLD" || command[1] == "3C_OLD")
			{
				//SPRITE//
				pos_x.push_back(0);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(204);
				pos_y.push_back(373);
				//BLINK//

				//SPEAK//
				pos_x.push_back(235);
				pos_y.push_back(358);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(115 - (pos_x[0] * 1.77));
					pos_y.push_back(-288);
					break;
				case 'L':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 285);
					pos_y.push_back(-288);
					break;
				case 'R':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 285);
					pos_y.push_back(-288);
					break;
				case 'D':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 140);
					pos_y.push_back(-288);
					break;
				case 'P':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 140);
					pos_y.push_back(-288);
					break;
				}
				//POSITION

			}
			if (command[1] == "1L" || command[1] == "2L" || command[1] == "3L" || command[1] == "1L_OLD")
			{
				//SPRITE//
				pos_x.push_back(0);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(214);
				pos_y.push_back(367);
				//BLINK//

				//SPEAK//
				pos_x.push_back(247);
				pos_y.push_back(358);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(115 - (pos_x[0] * 1.77));
					pos_y.push_back(-288);
					break;
				case 'L':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 285);
					pos_y.push_back(-288);
					break;
				case 'R':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 285);
					pos_y.push_back(-288);
					break;
				case 'D':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 140);
					pos_y.push_back(-288);
					break;
				case 'P':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 140);
					pos_y.push_back(-288);
					break;
				}
				//POSITION

			}
			if (command[1] == "1R" || command[1] == "2R" || command[1] == "3R" || command[1] == "2R_OLD" || command[1] == "3R_OLD")
			{
				//SPRITE//
				pos_x.push_back(0);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(213);
				pos_y.push_back(359);
				//BLINK//

				//SPEAK//
				pos_x.push_back(237);
				pos_y.push_back(356);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(115 - (pos_x[0] * 1.77));
					pos_y.push_back(-288);
					break;
				case 'L':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 285);
					pos_y.push_back(-288);
					break;
				case 'R':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 285);
					pos_y.push_back(-288);
					break;
				case 'D':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 140);
					pos_y.push_back(-288);
					break;
				case 'P':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 140);
					pos_y.push_back(-288);
					break;
				}
				//POSITION
			}

		}
		//if (chapter == "SA") //-------------------------------SAORI-------------------------------//
		//{
		//	switch (LCR)
		//	{
		//	case 'L':
		//		pos_x.push_back(-230);
		//		pos_y.push_back(-220);
		//		break;
		//	case 'C':
		//		pos_x.push_back(120);// не проверено
		//		pos_y.push_back(-220);
		//		break;
		//	case 'R':
		//		pos_x.push_back(720);// не проверено
		//		pos_y.push_back(-220);
		//		break;
		//	}
		//}
		//if (chapter == "KU") //-------------------------------KURONEKO-------------------------------//
		//{
		//	switch (LCR)
		//	{
		//	case 'L':
		//		pos_x.push_back(-230);// не проверено
		//		pos_y.push_back(-360);
		//		break;
		//	case 'C':
		//		pos_x.push_back(120);// не проверено
		//		pos_y.push_back(-360);
		//		break;
		//	case 'R':
		//		pos_x.push_back(720);
		//		pos_y.push_back(-360);
		//		break;
		//	}
		//}
		if (command[0] == "AY") //-------------------------------AYASE-------------------------------//
		{
			if (command[1] == "1C" || command[1] == "2C" || command[1] == "1C_YAN" || command[1] == "2C_YAN")
			{
				//SPRITE//
				pos_x.push_back(252);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(69 + pos_x[0]);
				pos_y.push_back(378);
				//BLINK//

				//SPEAK//
				pos_x.push_back(107 + pos_x[0]);
				pos_y.push_back(361);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(345 - (pos_x[0] * 1.77));
					pos_y.push_back(-288);
					break;
				case 'L':
					pos_x.push_back(345 - (pos_x[0] * 1.77) - 285);
					pos_y.push_back(-288);
					break;
				case 'R':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 285);
					pos_y.push_back(-288);
					break;
				case 'D':
					pos_x.push_back(345 - (pos_x[0] * 1.77) - 140);
					pos_y.push_back(-288);
					break;
				case 'P':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 140);
					pos_y.push_back(-288);
					break;
				}
				//POSITION
			}
			if (command[1] == "1L" || command[1] == "2L" || command[1] == "1L_YAN" || command[1] == "2L_YAN" || command[1] == "2L_OLD")
			{
				//SPRITE//
				pos_x.push_back(212);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(44 + pos_x[0]);
				pos_y.push_back(374);
				//BLINK//

				//SPEAK//
				pos_x.push_back(87 + pos_x[0]);
				pos_y.push_back(363);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 36);
					pos_y.push_back(-290);
					break;
				case 'L':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 36 - 285);
					pos_y.push_back(-290);
					break;
				case 'R':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 36 + 285);
					pos_y.push_back(-290);
					break;
				case 'D':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 36 - 140);
					pos_y.push_back(-290);
					break;
				case 'P':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 36 + 140);
					pos_y.push_back(-290);
					break;
				}
				//POSITION

			}
			if (command[1] == "1R" || command[1] == "2R" || command[1] == "1R_YAN" || command[1] == "2R_YAN" || command[1] == "1R_OLD")
			{
				//SPRITE//
				pos_x.push_back(252);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(73 + pos_x[0]);
				pos_y.push_back(372);
				//BLINK//

				//SPEAK//
				pos_x.push_back(108 + pos_x[0]);
				pos_y.push_back(366);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(345 - (pos_x[0] * 1.77));
					pos_y.push_back(-288);
					break;
				case 'L':
					pos_x.push_back(345 - (pos_x[0] * 1.77) - 285);
					pos_y.push_back(-288);
					break;
				case 'R':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 285);
					pos_y.push_back(-288);
					break;
				case 'D':
					pos_x.push_back(345 - (pos_x[0] * 1.77) - 140);
					pos_y.push_back(-288);
					break;
				case 'P':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 140);
					pos_y.push_back(-288);
					break;
				}
				//POSITION
			}

		}
		if (command[0] == "DA") //-------------------------------DAISUKE-------------------------------//
		{
			if (command[1] == "1C" || command[1] == "1C_OLD")
			{
				//SPRITE//
				pos_x.push_back(0);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(108);
				pos_y.push_back(406);
				//BLINK//

				//SPEAK//
				pos_x.push_back(129);
				pos_y.push_back(348);
				//SPEAK//
			}
			switch (LCR)
			{
			case 'L':
				pos_x.push_back(-230);
				pos_y.push_back(-360); // не проверено
				break;
			case 'C':
				pos_x.push_back(280);
				pos_y.push_back(-200);
				break;
			case 'R':
				pos_x.push_back(720); // не проверено
				pos_y.push_back(-360);
				break;
			}
		}
		return this->id;
	}

	void Blink_Create(Node *Box_Sprites, bool *task) //есть ошибки сделай возвращающийся таск в тех местах где создаются блоинки и жди в бесконечном цикли завершения блинка НЕ СОЗДАВАТЬ НОВЫЙ ПОТОК ДО ЗОВЕРШЕНИЯ СТАРОГО
	{
		*task = true;
		string blink1 = blink[0];
		string blink2 = blink[1];
		string blink3 = blink[2];
		Node *Set_Sprite;
		cocos2d::Sprite *Set_Blink;

		switch (id)
		{
		case(1) :
			Set_Sprite = Box_Sprites->getChildByName("Sprite_1");
			srand(id);
			break;
		case(2) :
			Set_Sprite = Box_Sprites->getChildByName("Sprite_2");
			srand(id);
			break;
		case(3) :
			Set_Sprite = Box_Sprites->getChildByName("Sprite_3");
			srand(id);
			break;
		}

		nump_nf[id-1] = true;

		Set_Blink = static_cast<cocos2d::Sprite*>(Set_Sprite->getChildByName("Blink"));


		auto start = steady_clock::now();
		auto end = steady_clock::now();
		rand();
		while (true)
		{
			start = steady_clock::now();
			int needwait = ((rand() % 4000) + 4000);
			int x = 0;
			while (x == 0)
				x = rand() % 3;
			if (Get_name() == 5)
				x = 1;
			while (true)
			{
				if (nump_nf[id - 1] == false)
				{
					*task = false;
					return;
				}
				end = steady_clock::now();
				auto z = time_point_cast<milliseconds>(end);
				auto b = time_point_cast<milliseconds>(start)+milliseconds(needwait);
				if (z > b)
				{
					for (int p = 0; p < x; p++)
					{
						Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Blink, blink2]{
							Set_Blink->Sprite::setTexture(blink2);
						});
						Sleep(50);
						Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Blink, blink3]{
							Set_Blink->Sprite::setTexture(blink3);
						});
						Sleep(50);
						Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Blink, blink2]{
							Set_Blink->Sprite::setTexture(blink2);
						});
						Sleep(50);
						Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Blink, blink1]{
							Set_Blink->Sprite::setTexture(blink1);
						});
						Sleep(50);
					}
					break;
				}	
				
			}
			
		}
		
	} 

	//void Speak_Create(Node *Box_Sprites, vector<bool> open_mouth, bool *task, bool *stop_that_task)
	//{
	//	//, bool *open_mouth, int size_open_mouth, bool *task

	//	*task = true;
	//	*stop_that_task = false;

	//	string speak1 = speak[0];
	//	string speak2 = speak[1];
	//	string speak3 = speak[2];
	//	Node *Set_Sprite;
	//	cocos2d::Sprite *Set_Speak;

	//	switch (id)
	//	{
	//	case(1) :
	//		Set_Sprite = Box_Sprites->getChildByName("Sprite_1");
	//		srand(id);
	//		break;
	//	case(2) :
	//		Set_Sprite = Box_Sprites->getChildByName("Sprite_2");
	//		srand(id);
	//		break;
	//	case(3) :
	//		Set_Sprite = Box_Sprites->getChildByName("Sprite_3");
	//		srand(id);
	//		break;
	//	}

	//	Set_Speak = static_cast<cocos2d::Sprite*>(Set_Sprite->getChildByName("Speak"));

	//	for (int n = 0; n < open_mouth.size(); n++)
	//	{
	//		if (open_mouth[n] == true && *stop_that_task == false)
	//		{
	//			Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Speak, speak2]{
	//				Set_Speak->Sprite::setTexture(speak2);
	//			});
	//			Sleep(80);
	//			n++;
	//			if (open_mouth[n] == true && *stop_that_task == false)
	//			{
	//				Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Speak, speak3]{
	//					Set_Speak->Sprite::setTexture(speak3);
	//				});
	//				Sleep(80);
	//				n++;
	//				if (open_mouth[n] == true && *stop_that_task == false)
	//				{
	//					Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Speak, speak2]{
	//						Set_Speak->Sprite::setTexture(speak2);
	//					});
	//					Sleep(80);
	//					n++;
	//					if (open_mouth[n] == true && *stop_that_task == false)
	//					{
	//						Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Speak, speak1]{
	//							Set_Speak->Sprite::setTexture(speak1);
	//						});
	//						Sleep(80);
	//					}
	//					else if (*stop_that_task == false)
	//					{
	//						if (hide == false)
	//						{
	//							Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Speak, speak1]{
	//								Set_Speak->Sprite::setTexture(speak1);
	//							});
	//						}
	//						Sleep(80);
	//					}
	//				}
	//				else if (*stop_that_task == false)
	//				{
	//					if (hide == false)
	//					{
	//						Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Speak, speak1]{
	//							Set_Speak->Sprite::setTexture(speak1);
	//						});
	//					}
	//					Sleep(80);
	//				}
	//			}
	//			else if (*stop_that_task == false)
	//			{
	//				if (hide == false)
	//				{
	//					Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Speak, speak1]{
	//						Set_Speak->Sprite::setTexture(speak1);
	//					});
	//				}
	//				Sleep(80);
	//			}
	//		}
	//		else if (*stop_that_task == false)
	//		{
	//			if (hide == false)
	//			{
	//				Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Speak, speak1]{
	//					Set_Speak->Sprite::setTexture(speak1);
	//				});
	//			}
	//			Sleep(80);
	//		}
	//		else
	//		{
	//			*task = false;
	//			return;
	//		}
	//	}
	//	*task = false;

	//}
	//	

	void Get_Sprite(Node *Game_Mode, bool *task)
	{
		*task = true;
		Node *Box_scene = Game_Mode->getChildByName("Box_scene");
		Node *Box_unscene = Game_Mode->getChildByName("Box_unscene");

		Node *Box_Sprites = Box_scene->getChildByName("Box_Sprites");

		Node *Sprite_und;
		Node *Sprite_swich;

		switch (id)
		{
		case 1:
			Sprite_und = Box_Sprites->getChildByName("Sprite_1");
			Sprite_swich = Box_unscene->getChildByName("Sprite_1_switch");
			break;
		case 2:
			Sprite_und = Box_Sprites->getChildByName("Sprite_2");
			Sprite_swich = Box_unscene->getChildByName("Sprite_2_switch");
			break;
		case 3:
			Sprite_und = Box_Sprites->getChildByName("Sprite_3");
			Sprite_swich = Box_unscene->getChildByName("Sprite_3_switch");
			break;
		}

		auto *Set_Sprite_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Sprite"));
		auto *Set_Blink_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Blink"));
		auto *Set_Speak_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Speak"));
		auto *Set_unscene = static_cast<cocos2d::Sprite*>(Box_unscene->getChildByName("Set_unscene"));

		auto *Set_Sprite = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Sprite"));
		auto *Set_Blink = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Blink"));
		auto *Set_Speak = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Speak"));
		


		if (hide == true)
		{

				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
					Set_Sprite_Swich->setTexture("Sprites\\Samples\\Sample_Sprite.png");
					Set_Blink_Swich->setTexture("Sprites\\Samples\\Sample_Blink.png");
					Set_Speak_Swich->setTexture("Sprites\\Samples\\Sample_Speak.png");
					Set_unscene->setTexture("Scene\\Sample_Scene.png");
					*task = false;
				});

			return;
		}
		else
		{

			Set_Sprite_Swich->setPosition(Vec2(pos_x[0], pos_y[0]));
			Set_Blink_Swich->setPosition(Vec2(pos_x[1], pos_y[1]));
			Set_Speak_Swich->setPosition(Vec2(pos_x[2], pos_y[2]));
			Sprite_swich->setPosition(Vec2(pos_x[3], pos_y[3]));


			string tempsprite = sprite;
			string tempblink = blink[0];
			string tempspeak = speak[0];


				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
					Set_Sprite_Swich->setTexture(tempsprite);
					Set_Blink_Swich->setTexture(tempblink);
					Set_Speak_Swich->setTexture(tempspeak);
					Set_unscene->setTexture("Scene\\Sample_Scene.png");
					*task = false;
				});


			return;
		}
	}
	void Get_Sprite(Node *Game_Mode, bool *task, Vec2 custom_position)
	{
		*task = true;
		Node *Box_scene = Game_Mode->getChildByName("Box_scene");
		Node *Box_unscene = Game_Mode->getChildByName("Box_unscene");

		Node *Box_Sprites = Box_scene->getChildByName("Box_Sprites");

		Node *Sprite_und;
		Node *Sprite_swich;

		switch (id)
		{
		case 1:
			Sprite_und = Box_Sprites->getChildByName("Sprite_1");
			Sprite_swich = Box_unscene->getChildByName("Sprite_1_switch");
			break;
		case 2:
			Sprite_und = Box_Sprites->getChildByName("Sprite_2");
			Sprite_swich = Box_unscene->getChildByName("Sprite_2_switch");
			break;
		case 3:
			Sprite_und = Box_Sprites->getChildByName("Sprite_3");
			Sprite_swich = Box_unscene->getChildByName("Sprite_3_switch");
			break;
		}

		auto *Set_Sprite_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Sprite"));
		auto *Set_Blink_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Blink"));
		auto *Set_Speak_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Speak"));
		auto *Set_unscene = static_cast<cocos2d::Sprite*>(Box_unscene->getChildByName("Set_unscene"));

		auto *Set_Sprite = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Sprite"));
		auto *Set_Blink = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Blink"));
		auto *Set_Speak = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Speak"));



		if (hide == true)
		{

			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
				Set_Sprite_Swich->setTexture("Sprites\\Samples\\Sample_Sprite.png");
				Set_Blink_Swich->setTexture("Sprites\\Samples\\Sample_Blink.png");
				Set_Speak_Swich->setTexture("Sprites\\Samples\\Sample_Speak.png");
				Set_unscene->setTexture("Scene\\Sample_Scene.png");
				*task = false;
			});

			return;
		}
		else
		{

			Set_Sprite_Swich->setPosition(Vec2(pos_x[0], pos_y[0]));
			Set_Blink_Swich->setPosition(Vec2(pos_x[1], pos_y[1]));
			Set_Speak_Swich->setPosition(Vec2(pos_x[2], pos_y[2]));
			Sprite_swich->setPosition(custom_position);


			string tempsprite = sprite;
			string tempblink = blink[0];
			string tempspeak = speak[0];


			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
				Set_Sprite_Swich->setTexture(tempsprite);
				Set_Blink_Swich->setTexture(tempblink);
				Set_Speak_Swich->setTexture(tempspeak);
				Set_unscene->setTexture("Scene\\Sample_Scene.png");
				*task = false;
			});


			return;
		}
	}
	void Get_Sprite_complete(cocos2d::Node *Game_Mode, bool swich_scene, bool *task)
	{
		*task = true;
		Node *Box_scene = Game_Mode->getChildByName("Box_scene");
		Node *Box_unscene = Game_Mode->getChildByName("Box_unscene");

		Node *Box_Sprites = Box_scene->getChildByName("Box_Sprites");

		Node *Sprite_und;
		Node *Sprite_swich;

		switch (id)
		{
		case 1:
			Sprite_und = Box_Sprites->getChildByName("Sprite_1");
			Sprite_swich = Box_unscene->getChildByName("Sprite_1_switch");
			break;
		case 2:
			Sprite_und = Box_Sprites->getChildByName("Sprite_2");
			Sprite_swich = Box_unscene->getChildByName("Sprite_2_switch");
			break;
		case 3:
			Sprite_und = Box_Sprites->getChildByName("Sprite_3");
			Sprite_swich = Box_unscene->getChildByName("Sprite_3_switch");
			break;
		}

		auto *Set_Sprite_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Sprite"));
		auto *Set_Blink_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Blink"));
		auto *Set_Speak_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Speak"));

		auto *Set_Sprite = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Sprite"));
		auto *Set_Blink = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Blink"));
		auto *Set_Speak = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Speak"));



		string tempsprite;
		string tempblink;
		string tempspeak;

		if (hide == true)
		{
			tempsprite = "Sprites\\Samples\\Sample_Sprite.png";
			tempblink = "Sprites\\Samples\\Sample_Blink.png";
			tempspeak = "Sprites\\Samples\\Sample_Speak.png";
		}
		else
		{
			tempsprite = sprite;
			tempblink = blink[0];
			tempspeak = speak[0];
			Set_Sprite->setPosition(Vec2(pos_x[0], pos_y[0]));
			Set_Blink->setPosition(Vec2(pos_x[1], pos_y[1]));
			Set_Speak->setPosition(Vec2(pos_x[2], pos_y[2]));
			Sprite_und->setPosition(Vec2(pos_x[3], pos_y[3]));
		}


		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{		
			Set_Speak->setTexture(tempspeak);
		
			Set_Blink->setTexture(tempblink);
	
			Set_Sprite->setTexture(tempsprite);
		
			Box_Sprites->setOpacity(255);
			Sprite_und->setOpacity(255);

			if (swich_scene == false)
			{
				Box_unscene->setOpacity(0);

				Set_Sprite_Swich->setTexture("Sprites\\Samples\\Sample_Sprite.png");
				Set_Blink_Swich->setTexture("Sprites\\Samples\\Sample_Blink.png");
				Set_Speak_Swich->setTexture("Sprites\\Samples\\Sample_Speak.png");
			}
			*task = false;
		});
	}
	void Get_Sprite_complete(cocos2d::Node *Game_Mode, bool *task, Vec2 custom_position)
	{
		*task = true;
		Node *Box_scene = Game_Mode->getChildByName("Box_scene");
		Node *Box_unscene = Game_Mode->getChildByName("Box_unscene");

		Node *Box_Sprites = Box_scene->getChildByName("Box_Sprites");

		Node *Sprite_und;
		Node *Sprite_swich;

		switch (id)
		{
		case 1:
			Sprite_und = Box_Sprites->getChildByName("Sprite_1");
			Sprite_swich = Box_unscene->getChildByName("Sprite_1_switch");
			break;
		case 2:
			Sprite_und = Box_Sprites->getChildByName("Sprite_2");
			Sprite_swich = Box_unscene->getChildByName("Sprite_2_switch");
			break;
		case 3:
			Sprite_und = Box_Sprites->getChildByName("Sprite_3");
			Sprite_swich = Box_unscene->getChildByName("Sprite_3_switch");
			break;
		}

		auto *Set_Sprite_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Sprite"));
		auto *Set_Blink_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Blink"));
		auto *Set_Speak_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Speak"));

		auto *Set_Sprite = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Sprite"));
		auto *Set_Blink = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Blink"));
		auto *Set_Speak = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Speak"));



		string tempsprite;
		string tempblink;
		string tempspeak;

		if (hide == true)
		{
			tempsprite = "Sprites\\Samples\\Sample_Sprite.png";
			tempblink = "Sprites\\Samples\\Sample_Blink.png";
			tempspeak = "Sprites\\Samples\\Sample_Speak.png";
		}
		else
		{
			tempsprite = sprite;
			tempblink = blink[0];
			tempspeak = speak[0];
			Set_Sprite->setPosition(Vec2(pos_x[0], pos_y[0]));
			Set_Blink->setPosition(Vec2(pos_x[1], pos_y[1]));
			Set_Speak->setPosition(Vec2(pos_x[2], pos_y[2]));
			Sprite_und->setPosition(custom_position);
		}


		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			Set_Speak->setTexture(tempspeak);

			Set_Blink->setTexture(tempblink);

			Set_Sprite->setTexture(tempsprite);

			Box_Sprites->setOpacity(255);
			Sprite_und->setOpacity(255);
			Box_unscene->setOpacity(0);

			Set_Sprite_Swich->setTexture("Sprites\\Samples\\Sample_Sprite.png");
			Set_Blink_Swich->setTexture("Sprites\\Samples\\Sample_Blink.png");
			Set_Speak_Swich->setTexture("Sprites\\Samples\\Sample_Speak.png");
			*task = false;
		});


	}
	Vec2 Get_position()
	{
		return Vec2(this->pos_x[3], this->pos_y[3]);
	}

	void Get_Sprite_simple(cocos2d::Node *Game_Mode, bool ignore) //получает настройки для спрайта, такие как:
	{				//3 файла моргания, три файла разговора, и файл основного спрайта 
		Node *Box_scene = Game_Mode->getChildByName("Box_scene");
		Node *Box_unscene = Game_Mode->getChildByName("Box_unscene");

		Node *Box_Sprites = Box_scene->getChildByName("Box_Sprites");

		

		Node *Sprite_und, *Sprite_swich;
		
		string temp_sprite, temp_blink, temp_speak;

		switch (id)
		{
		case 1:
			Sprite_und = Box_Sprites->getChildByName("Sprite_1");
			Sprite_swich = Box_unscene->getChildByName("Sprite_1_switch");
			break;
		case 2:
			Sprite_und = Box_Sprites->getChildByName("Sprite_2");
			Sprite_swich = Box_unscene->getChildByName("Sprite_2_switch");
			break;
		case 3:
			Sprite_und = Box_Sprites->getChildByName("Sprite_3");
			Sprite_swich = Box_unscene->getChildByName("Sprite_3_switch");
			break;
		}

		if (ignore == true)
		{
			auto *Set_Sprite_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Sprite"));
			auto *Set_Blink_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Blink"));
			auto *Set_Speak_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Speak"));

			if (hide == true) // иначе нет данных о координатах для ключа hide = ошибка обращения к данным которых нет
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Sprite_Swich, Set_Blink_Swich, Set_Speak_Swich]{
					Set_Sprite_Swich->setTexture("Sprites\\Samples\\Sample_Sprite.png");
					Set_Blink_Swich->setTexture("Sprites\\Samples\\Sample_Blink.png");
					Set_Speak_Swich->setTexture("Sprites\\Samples\\Sample_Speak.png");
				});
			}
			else
			{

				Set_Sprite_Swich->setPosition(Vec2(pos_x[0], pos_y[0]));
				Set_Blink_Swich->setPosition(Vec2(pos_x[1], pos_y[1]));
				Set_Speak_Swich->setPosition(Vec2(pos_x[2], pos_y[2]));
				Sprite_swich->setPosition(Vec2(pos_x[3], pos_y[3]));

				temp_sprite = sprite;
				temp_blink = blink[0];
				temp_speak = speak[0];

				Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Sprite_Swich, Set_Blink_Swich, Set_Speak_Swich, temp_sprite, temp_blink, temp_speak]{
					Set_Sprite_Swich->setTexture(temp_sprite);
					Set_Blink_Swich->setTexture(temp_blink);
					Set_Speak_Swich->setTexture(temp_speak);
				});
			}

		}
		else
		{
			auto *Set_Sprite = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Sprite"));
			auto *Set_Blink = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Blink"));
			auto *Set_Speak = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Speak"));

			auto *Set_Sprite_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Sprite"));
			auto *Set_Blink_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Blink"));
			auto *Set_Speak_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Speak"));

			string temp_sprite, temp_blink, temp_speak;

			if (hide == true) // иначе нет данных о координатах для ключа hide = ошибка обращения к данным которых нет
			{

				Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Sprite, Set_Blink, Set_Speak, Set_Sprite_Swich, Set_Blink_Swich, Set_Speak_Swich]{
					Set_Sprite->setTexture("Sprites\\Samples\\Sample_Sprite.png");
					Set_Blink->setTexture("Sprites\\Samples\\Sample_Blink.png");
					Set_Speak->setTexture("Sprites\\Samples\\Sample_Speak.png");
					Set_Sprite_Swich->setTexture("Sprites\\Samples\\Sample_Sprite.png");
					Set_Blink_Swich->setTexture("Sprites\\Samples\\Sample_Blink.png");
					Set_Speak_Swich->setTexture("Sprites\\Samples\\Sample_Speak.png");
				});
			}
			else
			{
				Set_Sprite->setPosition(Vec2(pos_x[0], pos_y[0]));
				Set_Blink->setPosition(Vec2(pos_x[1], pos_y[1]));
				Set_Speak->setPosition(Vec2(pos_x[2], pos_y[2]));
				Sprite_und->setPosition(Vec2(pos_x[3], pos_y[3]));

				temp_sprite = sprite;
				temp_blink = blink[0];
				temp_speak = speak[0];

				Director::getInstance()->getScheduler()->performFunctionInCocosThread([Set_Sprite_Swich, Set_Blink_Swich, Set_Speak_Swich, Set_Sprite, Set_Blink, Set_Speak, temp_sprite, temp_blink, temp_speak]{
					Set_Sprite_Swich->setTexture("Sprites\\Samples\\Sample_Sprite.png");
					Set_Blink_Swich->setTexture("Sprites\\Samples\\Sample_Blink.png");
					Set_Speak_Swich->setTexture("Sprites\\Samples\\Sample_Speak.png");
					Set_Sprite->setTexture(temp_sprite);
					Set_Blink->setTexture(temp_blink);
					Set_Speak->setTexture(temp_speak);
				});
			}
		}
	}

	int Get_id()
	{
		return (id);
	}

	string Get_Sprite_Box(int x)
	{
		switch (x)
		{
		case 1:
			return (sprite);
			break;
		case 2:
			return (blink[0]);
			break;
		case 3:
			return (blink[1]);
			break;
		case 4:
			return (blink[2]);
			break;
		case 5:
			return (speak[0]);
			break;
		case 6:
			if (hide == true)
			{
				return ("true");
				break;
			}
			else
			{
				return("false");
				break;
			}
		case 7:
			switch (name)
			{
			case 0:
				return ("РђСЏСЃСЌ");
			case 2:
				return ("РљСѓСЂРѕРЅСЌРєРѕ");
				break;
			case 3:
				return ("РњР°РЅР°РјРё");
				break;
			case 4:
				return ("РљРёСЂРёРЅРѕ");
				break;
			case 5:
				return ("Р”Р°Р№СЃСѓРєСЌ");
				break;
			case 6:
				return ("РЎР°РѕСЂРё");
				break;
			}
		}
		return (NULL);
	}

	int Get_name()
	{
		return(this->name);
	}

	string Get_custom_swich()
	{
		return this->custom_swich;
	}

	bool Get_hide()
	{
		return this->hide;
	}

	string Get_action()
	{
		return this->action;
	}



	void operator=(const SPRITEBOX& x)
	{
		sprite = x.sprite;
		blink.assign(x.blink.begin(), x.blink.end());
		speak.assign( x.speak.begin(), x.speak.end());
		pos_x.assign(x.pos_x.begin(), x.pos_x.end());
		pos_y.assign(x.pos_y.begin(), x.pos_y.end());
		LCR = x.LCR;
	}

	bool operator==(const SPRITEBOX& x)
	{
		if (sprite == x.sprite)
			return(true);
		else
			return(false);
	}

};





class GAMEBOX/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
private:

	//ЗАМЕТКА
	// подпригивание спрайта, увеличение -  вызывается командой <actionsprite> в теле [getsprite] JUMP MINIJUMP DECREASE INCREASE
	
	
	//СЕЙЧАС
	//управления переходом на скрипты через скрипт
	//скип определенного количества текста и команд через скрипт
	//кастонмый свич сцен
	//вызов оре
	//облака

	//ПОТОМ
	// оптимизация появления текста через управляющую переменную  task_for_text (глобальная задача)
	//управление скипом
	//создавать ноду активных спрайтов - а нужно ли?
	//создание анимаций для live2d прямо в скрипте
	//сохранение 
	//загрузка
	//данные профиля
	vector<string> name; // вектор который хранит все имена
	vector<string> text; // вектор который хранит весь текст
	vector<string> voice;// вектор который хранит все дерриктории озвучки
	vector<string> command_music; // вектор который хранит команды вызовы музыки
	vector<string> command_sprite; // вектор который хранит команды вызовы спрайтов ***пометка - в отличии от остальных является лишь временным хранилещем по своей сути, после выполнения Set_script остается пустым, настаящие хранилище спрайтов в векторе sprite
	vector<SPRITEBOX> sprite; // вектор который хранит объекты созданных спрайтов
	vector<string> command_swich_scene; //вектор который хранит команды вызовы сцен
	vector<string> command_shake; // вектор который хранит команды тряски экрана
	vector<string> command_sound; // вектор который хранит команды вызовов игровых звуков
	vector<string> command_nextscript;
	string command_sprite_start = "[getsprite]";
	string command_sprite_end = "[/getsprite]";
	string command_swich_scene_start = "[getscene]";
	string command_swich_scene_end = "[/getscene]";
	string command_music_start = "[getmusic]";
	string command_music_end = "[/getmusic]";
	string command_shake_start = "[getshake]";
	string command_shake_end = "[/getshake]";
	string command_gamesound_start = "[getsound]";
	string command_gamesound_end = "[/getsound]";
	string command_nextscript_start = "[getscript]";
	string command_nextscript_end = "[/getscript]";

	struct commands // структура для вызовов // также нужно создать сборку порядка вызовов
	{
		bool name = false;
		bool mus = false;
		bool scn = false;
		bool shake = false;
		bool sound = false;
		bool spr1 = false;
		bool spr2 = false;
		bool spr3 = false;
		bool nextscript = false;
		int id_name = NULL;
		int id_mus = NULL;
		int id_scn = NULL;
		int id_shake = NULL;
		int id_sound = NULL;
		int id_spr1 = NULL;
		int id_spr2 = NULL;
		int id_spr3 = NULL;
		int id_nextscript = NULL;
	};

	struct speak
	{
		vector<vector<bool>> ch_speak;
		int x;
	};

	vector<bool*> task_oldblink; //должен хранить переменную завершения потока для потоков мограний при изменении значения прошлый поток закрывается
	bool blink_task1 = false;  //состояние потоков морганий - по умолчанию нективны при создании объекта находятся в task_oldblink адреса этих переменных
	bool blink_task2 = false;
	bool blink_task3 = false;

	struct active_sprite //структура для активных спрайтов
	{
		SPRITEBOX id1;
		SPRITEBOX id2;
		SPRITEBOX id3;
		bool use_id1 = false;
		bool use_id2 = false;
		bool use_id3 = false;
	};



	bool speak_task = false; // состояние потока разговора - по умолчанию неактивен
	bool stop_speak_task = false;

	vector<commands> command_script; // хранит вектор структур всех команд


	Vec2 temp_pos_increase; // хранит временную позицию увеличенного скрипта
	int id_temp_pos_increase = NULL; //и его id


	active_sprite usesprite; //хранит значения какой спрайт активен и под каким id

	bool old_text = false; // переменная хранит закончился ли поток прошлого текста

	speak get_speak[8]; // хранит все анимации рта для всех возможных спрайтов

	

	bool Auto_Mode = false;

	bool *task_for_text = new bool{ false }; // переменная хранящая значение допуска к тексту - пока true выполняются другие действия и не вызывается текст

	int num = 0;

	Game *p_obj; // Ссылка на главный безымянный объект

public:

	GAMEBOX()
	{
		task_oldblink.push_back(&blink_task1); //иницилизация адресов потоков мограний
		task_oldblink.push_back(&blink_task2);
		task_oldblink.push_back(&blink_task3);
	}

	void set_Auto_Mode(cocos2d::Node *Game_Mode, bool current)
	{
		Auto_Mode = current;
	}

	bool get_Auto_Mode()
	{
		return Auto_Mode;
	}
	
	void Clear_Data()
	{
		num = 0;
		name.clear();
		text.clear(); // вектор который хранит весь текст
		voice.clear();// вектор который хранит все дерриктории озвучки
		command_music.clear(); // вектор который хранит команды вызовы музыки
		command_sprite.clear(); // вектор который хранит команды вызовы спрайтов
		command_swich_scene.clear(); //вектор который хранит команды вызовы сцен
		command_shake.clear(); // вектор который хранит команды тряски экрана
		command_sound.clear(); // вектор который хранит команды вызовов игровых звуков		
		task_oldblink.clear();
		command_script.clear();
		sprite.clear();
		nump_nf[0] = false;
		nump_nf[1] = false;
		nump_nf[2] = false;
	}

	void Set_Music(vector<string> &dir, commands *temp) //создает вектор вызовов музыки
	{
		if (command_music.back() == string(""))
			return;
		if (command_music.back() == string("stop"))
		{
			(*temp).mus = true;
			(*temp).id_mus = command_music.size() - 1;
			return;
		}
		for (int i = 0; i < dir.size(); i++)
		{
			if (string(dir[i]) == string("{" + command_music.back() + "}"))
			{
				command_music[command_music.size() - 1] = dir[i + 1];
				(*temp).mus = true;
				(*temp).id_mus = command_music.size() - 1;
				break;
			}
		}
	}

	void Set_Scene(vector<string> &dir, commands *temp) //создает вектор вызовов сцен
	{
		if (command_swich_scene.back() == string(""))
			return;
		if (command_swich_scene.back() == string("ALLBLACK") || command_swich_scene.back() == string("SHOWBOX") || command_swich_scene.back() == string("HIDEBOX") )
		{

			if (command_swich_scene.back() == string("ALLBLACK"))
			{
				(*temp).scn = true;
				(*temp).id_scn = command_swich_scene.size() - 1;
				return;
			}

			else if (command_swich_scene[command_swich_scene.size() - 3] == string("HIDEBOX") && command_swich_scene.back() == string("SHOWBOX")) // Это может вызывать ошибки
			{

				(*temp).scn = true;
				(*temp).id_scn = command_swich_scene.size() - 3;
				for (int i = 0; i < dir.size(); i++)  // ищет дирректории сцен для скрипта для SHOWBOX
				{
					if (string(dir[i]) == string("{" + command_swich_scene[command_swich_scene.size() - 2] + "}"))
					{
						command_swich_scene[command_swich_scene.size() - 2] = dir[i + 1];
						return;
					}
				}
				return;
			}

		}
		for (int i = 0; i < dir.size(); i++) // ищет дирректории сцен для скрипта
		{
			if (string(dir[i]) == string("{" + command_swich_scene.back() + "}"))
			{
				command_swich_scene[command_swich_scene.size() - 1] = dir[i + 1];
				(*temp).scn = true;
				(*temp).id_scn = command_swich_scene.size() - 1;
				return;
			}
		}
	}

	void Set_Speak(string buff)
	{
		ifstream file(buff);
		buff.erase(buff.length() - 7, 7);
		char z[3];
		char temp[14];
		const char AY[] = { 'A', 'Y' };
		const char KY[] = { 'K', 'Y' };
		const char KU[] = { 'K', 'U' };
		const char MA[] = { 'M', 'A' };
		const char KI[] = { 'K', 'I' };
		const char DA[] = { 'D', 'A' };
		const char SA[] = { 'S', 'A' };
		const char SI[] = { 'S', 'I' };
		const char name_box[8][2] = { { AY[0], AY[1] }, { KY[0], KY[1] }, { KU[0], KU[1] }, { MA[0], MA[1] }, { KI[0], KI[1] }, { DA[0], DA[1] }, { SA[0], SA[1] }, { SI[0], SI[1] } };
		file.read(z, 2);
		while (!file.eof())
		{
			file.seekg(-2, ios::cur);
			for (int n = 0, y = 0; n < 8; n++)
			{
				if (z[0] == name_box[n][y] && z[1] == name_box[n][y + 1])
				{
					while (!file.eof())
					{
						file.read(z, 2);
						z[2] = '\0';
						if (z[0] == name_box[n][y] && z[1] == name_box[n][y + 1])
						{
							file.read(temp, 14);
							temp[13] = '\0';
							string bo_file = buff + string(z) + string(temp);
							ifstream bo_find(bo_file);
							for (int l = 0; true; l++)
							{
								char zz[2];
								bo_find.read(zz, 1);
								zz[1] = '\0';
								if (zz[0] == ',')
								{
									vector<bool> b_vbool;
									while (!bo_find.eof())
									{
										bo_find.read(zz, 1);
										bool b_temp = false;
										if (zz[0] == 0x31)
											b_temp = true;
										b_vbool.push_back(b_temp);
									}
									get_speak[n].ch_speak.push_back(b_vbool);
									break;
								}
							}
						}
						else
						{
							n = 0;
							break;
						}



					}
					break;
				}
			}
		}
	}


	void Get_nextscript(cocos2d::Node *Game_Mode, int current)
	{
		auto *set_text = static_cast<cocos2d::ui::Text*>(Game_Mode->getChildByName("Set_text")); // элемент текста в игровом меню
		auto *set_name = static_cast<cocos2d::ui::Text*>(Game_Mode->getChildByName("Set_name")); // элемент имени в игровом меню
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			set_name->setString("");
			set_text->setString("");
		});
		auto *Text_Box = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Text_Box"));
		cocos2d::experimental::AudioEngine::stop(Voice_id);
		stringstream tempstring;
		tempstring << string(command_nextscript[current]);
		int script = 0;
		tempstring >> script;
		auto setup([=](){
			Hide_text_box(Text_Box);
			for (;;)
			{
				Sleep(100);
				if (*task_for_text == false)
					break;
			}
			Clear_Data();
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
				Head_Menu->loadsetgame(script);
			});
		});
		thread get(setup);
		get.detach();
	}



	string Set_Text()
	{
		if (text[num].length() > 110 && text[num].length() < 200) // создает пропуск строки если она большая
		{
			shared_ptr<char> buff(new char[text[num].length() + 1], default_delete<char[]>());
			strcpy(&(*buff), text[num].c_str());
			int z = 90;
			while (true) // искать пробел после 90-того знака
			{
				z++;
				if ((&(*buff))[z] == 0x20)
				{
					(&(*buff))[z] = '\n';
					break;
				}
				if (z > 105) //если не нашел - до 100-го знака
				{
					z = 90;
					while (true)
					{
						z--;
						if ((&(*buff))[z] == 0x20)
						{
							(&(*buff))[z] = '\n';
							break;
						}
					}
					break;
				}
			}
			string text(&*buff);
			return text;
		}
		else if (text[num].length() > 200)
		{
			shared_ptr<char> buff(new char[text[num].length() + 1], default_delete<char[]>());
			strcpy(&(*buff), text[num].c_str());
			int z = 90;
			while (true)
			{
				z++;
				if ((&(*buff))[z] == 0x20)
				{
					(&(*buff))[z] = '\n';
					z = 180;
					while (true)
					{
						z++;
						if ((&(*buff))[z] == 0x20)
						{
							(&(*buff))[z] = '\n';
							break;
						}
						if (z > 200)  //если не нашел - до 200-го знака
						{
							z = 180;
							while (true)
							{
								z--;
								if ((&(*buff))[z] == 0x20)
								{
									(&(*buff))[z] = '\n';
									break;
								}
							}
							break;
						}
					}
					break;
				}
				if (z > 105) //если не нашел - до 110-го знака
				{
					z = 90;
					while (true)
					{
						z--;
						if ((&(*buff))[z] == 0x20)
						{
							(&(*buff))[z] = '\n';
							z = 180;
							while (true)
							{
								z++;
								if ((&(*buff))[z] == 0x20)
								{
									(&(*buff))[z] = '\n';
									break;
								}
								if (z > 200)  //если не нашел - до 200-го знака
								{
									z = 180;
									while (true)
									{
										z--;
										if ((&(*buff))[z] == 0x20)
										{
											(&(*buff))[z] = '\n';
											break;
										}
									}
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}
			string text(&*buff);
			return text;
		}
		else
		{
			shared_ptr<char> buff(new char[text[num].length() + 1], default_delete<char[]>());
			strcpy(&(*buff), text[num].c_str());
			string text(&*buff);
			return text;
		}
		
	}


	void New_command(commands *temp)
	{
		(*(temp)).name = false;
		(*(temp)).mus = false;
		(*(temp)).scn = false;
		(*(temp)).shake = false;
		(*(temp)).sound = false;
		(*(temp)).spr1 = false;
		(*(temp)).spr2 = false;
		(*(temp)).spr3 = false;
		(*(temp)).nextscript = false;
		(*(temp)).id_name = NULL;
		(*(temp)).id_mus = NULL;
		(*(temp)).id_scn = NULL;
		(*(temp)).id_shake = NULL;
		(*(temp)).id_sound = NULL;
		(*(temp)).id_spr1 = NULL;
		(*(temp)).id_spr2 = NULL;
		(*(temp)).id_spr3 = NULL;
		(*(temp)).id_nextscript = NULL;
	}

	void Set_Script(const vector<string> dirscripts, vector<string> &dirsprites, vector<string> &dirscene, vector<string> &dirmusic, int script) //получает текст из файла скрипта
	{
		
		ifstream buff; //поток файла
		string tempdir; // просто временная дерриктория для копирования строк из файла в вектор
		commands buff_command; // создает буфер который хранит в себе значения нужна ли музыка спрайт или смена картинки на данной строчке скрипта, должна после каждого прохода текста отчищаться New_command
		//active_sprite s;

		Set_Speak(dirscripts[script+1]);
		buff.open(dirscripts[script], ios::binary); // номер скрипта

		while (getline(buff, tempdir))
		{

			//====================================================================================================================================
			//																START
			//====================================================================================================================================
			tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
			//====================================================================================================================================
			//																SPRITE
			//====================================================================================================================================
			if (tempdir == command_sprite_start) //если команда вызова спрайта
			{
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_sprite_end) //если дошел до конца команды 
					{

						sprite.push_back(SPRITEBOX());

						int id = sprite[sprite.size() - 1].Set_Sprite(dirsprites, command_sprite);
						if (id == 1)
						{
							buff_command.spr1 = true;
							buff_command.id_spr1 = sprite.size() - 1;
						}
						else if (id == 2)
						{
							buff_command.spr2 = true;
							buff_command.id_spr2 = sprite.size() - 1;
						}
						else if (id == 3)
						{
							buff_command.spr3 = true;
							buff_command.id_spr3 = sprite.size() - 1;
						}
						command_sprite.clear(); // отчистка вектора для комманд cпрайта
						break;// и выход
					}
					command_sprite.push_back(tempdir); //копирование в вектор команд спрайта, команды пока не дошел до конца команды
				}
				continue;
			}
			//====================================================================================================================================
			//															   SCENE
			//====================================================================================================================================
			if (tempdir == command_swich_scene_start) //если команда вызова фона
			{
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_swich_scene_end) //если дошел до конца команды 
					{
						Set_Scene(dirscene, &buff_command);
						break; // и выход
					}
					command_swich_scene.push_back(tempdir);
				}
				continue;
			}
			//====================================================================================================================================
			//															   MUSIC
			//====================================================================================================================================
			if (tempdir == command_music_start) //если команда вызова музыки
			{
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_music_end) //если дошел до конца команды 
					{
						Set_Music(dirmusic, &buff_command);
						break; // и выход
					}
					command_music.push_back(tempdir);
				}
				continue;
			}
			//====================================================================================================================================
			//															   SHAKE
			//====================================================================================================================================
			if (tempdir == command_shake_start) //если команда вызова тряски
			{
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_shake_end) //если дошел до конца команды 
					{
						buff_command.shake = true;
						buff_command.id_shake = command_shake.size() - 1;
						break; // и выход
					}
					command_shake.push_back(tempdir);
				}
				continue;
			}
			//====================================================================================================================================
			//															  GAME SOUND
			//====================================================================================================================================
			if (tempdir == command_gamesound_start) //если команда вызова звука
			{
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_gamesound_end) //если дошел до конца команды 
					{
						buff_command.sound = true;
						buff_command.id_sound = command_sound.size() - 1;
						break; // и выход
					}
					command_sound.push_back(tempdir);
				}
				continue;
			}
			//====================================================================================================================================
			//															  SCRIPT
			//====================================================================================================================================
			if (tempdir == command_nextscript_start)
			{
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_nextscript_end) //если дошел до конца команды 
					{
						buff_command.nextscript = true;
						buff_command.id_nextscript = command_nextscript.size() - 1;
						break; // и выход
					}
					command_nextscript.push_back(tempdir);
				}
				command_script.push_back(buff_command);
				New_command(&buff_command);// сброс команд
				continue;
			}
			//====================================================================================================================================
			//															   ------
			//====================================================================================================================================
			if (tempdir == "")// если пустота пропуск
			{
				continue;
			}
			//====================================================================================================================================
			//																TEXT
			//====================================================================================================================================
			if (tempdir.size() < 19) //если имя
			{
				if (tempdir == "РђСЏСЃСЌ") // аясэ
				{
					name.push_back("РђСЏСЃСЌ");
				}
				else if (tempdir == "РЎРёРѕСЂРё") // сиори -  имя появляется в первой сцене мейн рута в игре кирино
				{
					name.push_back("РЎРёРѕСЂРё");
				}
				else if (tempdir == "Р”Р°Р№СЃСѓРєСЌ") // дайсукэ
				{
					name.push_back("Р”Р°Р№СЃСѓРєСЌ");
				}
				else if (tempdir == "РЎР°РѕСЂРё") // саори
				{
					name.push_back("РЎР°РѕСЂРё");
				}
				else if (tempdir == "РљС‘СЃСѓРєСЌ") // кёсукэ
				{
					name.push_back("РљС‘СЃСѓРєСЌ");
				}
				else if (tempdir == "РљРёСЂРёРЅРѕ") // кирино
				{
					name.push_back("РљРёСЂРёРЅРѕ");
				}
				else if (tempdir == "РњР°РЅР°РјРё") // манами
				{
					name.push_back("РњР°РЅР°РјРё");
				}
				else if (tempdir == "РљР°РЅР°РєРѕ") // канако
				{
					name.push_back("РљР°РЅР°РєРѕ");
				}
				else if (tempdir == "РљСѓСЂРѕРЅСЌРєРѕ") // куронэко
				{
					name.push_back("РљСѓСЂРѕРЅСЌРєРѕ");
				}
				else // если имени нет
				{
					text.push_back(tempdir); // скопировать текст в вектор

					getline(buff, tempdir);
					search_voice(&voice, "..\\Resources\\voice.txt", tempdir); // получение деррикторий для указанного файла voice

					command_script.push_back(buff_command);
					New_command(&buff_command); // сброс команд
					continue;
				}

				buff_command.name = true;
				buff_command.id_name = name.size() - 1;
				getline(buff, tempdir); // на след строку

				text.push_back(tempdir); // скопировать текст в вектор

				getline(buff, tempdir);
				search_voice(&voice, "..\\Resources\\voice.txt", tempdir); // получение деррикторий для указанного файла voice

				command_script.push_back(buff_command);
				New_command(&buff_command);// сброс команд
				continue;
			}

			else //если текст без имени
			{
				text.push_back(tempdir); // скопировать текст в вектор

				getline(buff, tempdir);
				search_voice(&voice, "..\\Resources\\voice.txt", tempdir);

				command_script.push_back(buff_command);
				New_command(&buff_command);// сброс команд

			}
			//====================================================================================================================================
			//																END
			//====================================================================================================================================
		}
	}

	int Get_id_Position()
	{
		return this->id_temp_pos_increase;
	}
	
	Vec2 Get_Position()
	{
		return this->temp_pos_increase;
	}


	void Get_Music(int &id)
	{
		if (command_music[id] == string(""))
			return;
		if (command_music[id] == string("stop"))
		{
			background_smooth (false);
		}
		if (cocos2d::experimental::AudioEngine::getVolume(Background_id) != 0)
		{
			background_smooth(false);
		}
		Background_id = cocos2d::experimental::AudioEngine::play2d(command_music[id].c_str(), true, All_Volume*Background_Volume);
	}

	void Get_Scene(cocos2d::Node *Game_Mode, commands &temp) //осталось при вызове просто спрайта без смены сцены и смены спрайта со сценой добавить созранение адреса в структуру как было сделано в sprite_swich
	{
		*task_for_text = true;
		auto Box_scene = Game_Mode->getChildByName("Box_scene");
		auto Box_unscene = Game_Mode->getChildByName("Box_unscene");
		auto *set_scene = static_cast<cocos2d::Sprite*>(Box_scene->getChildByName("Set_scene"));
		auto *set_unscene = static_cast<cocos2d::Sprite*>(Box_unscene->getChildByName("Set_unscene"));// определение верхней и нижней сцены

		vector<SPRITEBOX> temp_sprite; //хранит все спрайты данной строки num 
		bool ignore_sprite = true; // хранит значения есть ли игнор команды вызова спрайта или нет
		bool ignore_scene = false; // хранит значения есть ли игнор команды вызова сцены или нет

		if (temp.spr1 == true || temp.spr2 == true || temp.spr3 == true) // проверяет какие спрайты вызываются и вызываются ли вообще в данной num
		{
			ignore_sprite = false;
			if (temp.spr1 == true)
				temp_sprite.push_back(sprite[temp.id_spr1]);
			if (temp.spr2 == true)
				temp_sprite.push_back(sprite[temp.id_spr2]);
			if (temp.spr3 == true)
				temp_sprite.push_back(sprite[temp.id_spr3]);
		}

		if (command_swich_scene[temp.id_scn] == string("ALLBLACK")) // теперь работает ошибок быть не должно, использует Get_sprite с ключом true
		{			
			static auto *Black_screen_sprite = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Black_screen"));
			auto wait([=](){
				Black_screen_sprite->runAction(FadeIn::create(1.0f));
				for (;;)
				{
					Sleep(100);
					if (Black_screen_sprite->getOpacity() == 255)
						break;
				}
				Get_Sprite(Game_Mode, true, false); // В ALLBLACK может вызываться в виде исключения ключ true - нужел для использования функции Get_Sprite с мгновенным вызовом спрайта без дополнения функцианала swich_scene 	
			});
			thread setup(wait);
			setup.detach();
			return;
		}
		else if (temp.id_scn + 2 < command_swich_scene.size() && command_swich_scene[temp.id_scn] == string("HIDEBOX")) // только если есть место под данное количество комманд
		{
			if (command_swich_scene[temp.id_scn + 2] == string("SHOWBOX")) //идет проверка этих самых команд
			{
				temp.id_scn++;

				Show_and_Hide (Game_Mode, command_swich_scene[temp.id_scn], temp_sprite, task_oldblink, ignore_scene, ignore_sprite, task_for_text); //скрывает и показывает текст бокс а также сменяет сцену
				return;
			}
		}
		else
		{
			auto wait([=]()
			{
			Switch_scene(Game_Mode, command_swich_scene[temp.id_scn], temp_sprite, task_oldblink, ignore_scene, ignore_sprite, task_for_text, 0); //вызывает команду перехода
			});
			thread setup(wait);
			setup.detach();

		}

	}
	
	void Get_Sprite(cocos2d::Node *Game_Mode, bool simleuse, bool igor_command) //ключ simleuse используются в виде исключения ТОЛЬКО в ALLBLACK swichscene, ignorecommand осущевствляет выбор между вызовом спрайта с помощью этой функции или просто записать адреса
	{
		*task_for_text = true;
		vector<SPRITEBOX> temp_sprite_box;
		vector<bool> simple;
		
		if (command_script[num].spr1 == true)
		{
			temp_sprite_box.push_back(sprite[command_script[num].id_spr1]); // сохраняем во временный вектор вызова спрайт бокса спрайт
			if (usesprite.use_id1 == false) // если спрайт под этим id еще не вызван
			{ //  в дальнейшем помогает определить вызывать ли simple(смена только лица) вызов или нет (полная смена спрайта)
				usesprite.use_id1 = true; // сохраняется значение bool в структуру usesprite что под данным id спрайт вызван 
				usesprite.id1 = sprite[command_script[num].id_spr1]; // сохраняет в структуру сам вызванный спрайт
				simple.push_back(false); // указывает значение простой ли будет вызов или нет
			}
			else //если уже вызван
			{
				if (sprite[command_script[num].id_spr1] == usesprite.id1 && sprite[command_script[num].id_spr1].Get_Sprite_Box(6) == "false") //проверка нужен ли сложный вызов или нет
					simple.push_back(true); // если простой вызываем простой
				else
				{
					simple.push_back(false); // или же сложный
					if (sprite[command_script[num].id_spr1].Get_Sprite_Box(6) == "true") // идет проверка пропадает ли спрайт
						usesprite.use_id1 = false; // если пропадает то спрайт под этим id перестает быть активным
					else // и если он не пропадает сохраняем его новое значение в структуру активных спрайтов
						usesprite.id1 = sprite[command_script[num].id_spr1];
				}
			}

		}

		if (command_script[num].spr2 == true)
		{
			temp_sprite_box.push_back(sprite[command_script[num].id_spr2]);
			if (usesprite.use_id2 == false)
			{
				usesprite.use_id2 = true;
				usesprite.id2 = sprite[command_script[num].id_spr2];
				simple.push_back(false);
			}
			else
			{
				if (sprite[command_script[num].id_spr2] == usesprite.id2 && sprite[command_script[num].id_spr2].Get_Sprite_Box(6) == "false")
					simple.push_back(true);
				else
				{
					simple.push_back(false); // или же сложный
					if (sprite[command_script[num].id_spr2].Get_Sprite_Box(6) == "true") // идет проверка пропадает ли спрайт
						usesprite.use_id2 = false; // если пропадает то спрайт под этим id перестает быть активным
					else
						usesprite.id2 = sprite[command_script[num].id_spr2];
				}
			}
		}

		if (command_script[num].spr3 == true)
		{
			temp_sprite_box.push_back(sprite[command_script[num].id_spr3]);
			if (usesprite.use_id3 == false)
			{
				usesprite.use_id3 = true;
				usesprite.id3 = sprite[command_script[num].id_spr3];
				simple.push_back(false);
			}
			else
			{
				if (sprite[command_script[num].id_spr3] == usesprite.id3 && sprite[command_script[num].id_spr3].Get_Sprite_Box(6) == "false")
					simple.push_back(true);
				else
				{
					simple.push_back(false); // или же сложный
					if (sprite[command_script[num].id_spr3].Get_Sprite_Box(6) == "true") // идет проверка пропадает ли спрайт
						usesprite.use_id3 = false; // если пропадает то спрайт под этим id перестает быть активным
					else
						usesprite.id3 = sprite[command_script[num].id_spr3];
				}
			}
		}

		if (simleuse == true)
		{
			for (int n = 0; n < simple.size(); n++)
				simple[n] = true; // простой вывод - надстройка
		}

		if (igor_command == false)
		{
			auto setup([=](bool *task)->void{
				bool *podtask = new bool{ true };
				shared_ptr <bool> p_podtask(podtask);
				Get_sprite(Game_Mode, temp_sprite_box, task_oldblink, simple, podtask);
				for (;;)
				{
					Sleep(100);
					if (*podtask == false)
						break;
				}
				if (simleuse == true)
				{

					auto *Black_screen_sprite = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Black_screen"));
					for (;;)
					{
						Sleep(100);
						if (Black_screen_sprite->getOpacity() == 255)
							break;
					}
					Black_screen_sprite->runAction(FadeOut::create(1.0f));
					auto wait([=](){
						for (;;)
						{
							Sleep(100);
							if (Black_screen_sprite->getOpacity() == 0)
								break;
						}
						*task = false;
					});
					thread setup(wait);
					setup.detach();
					

				}
				else
					*task = false;
			});
			thread unb(setup, task_for_text); // как это сделать иначе - не имею представления использование Sequence крашит нахрен
			unb.detach();

		}


	}

	void Get_Voice()
	{
	cocos2d::experimental::AudioEngine::stop(Voice_id);
	Voice_id = cocos2d::experimental::AudioEngine::play2d(voice[num], false, All_Volume*Voice_Volume);
	}

	void Get_Speak_sp(cocos2d::Node *Game_Mode)
	{
		Node *Box_scene = Game_Mode->getChildByName("Box_scene");
		Node *Box_Sprites = Box_scene->getChildByName("Box_Sprites");

		if (command_script[num].spr1 == true || command_script[num].spr2 == true || command_script[num].spr3 == true) //проверка на вызов спрайтов
		{
			if (command_script[num].spr1 == true && string(name[command_script[num].id_name]) == sprite[command_script[num].id_spr1].Get_Sprite_Box(7))
			{
				thread woo(Get_Speak, Box_Sprites, sprite[command_script[num].id_spr1], get_speak[(sprite[command_script[num].id_spr1].Get_name())].ch_speak[get_speak[(sprite[command_script[num].id_spr1].Get_name())].x], &speak_task, &stop_speak_task);
				woo.detach();
			}
			else if (command_script[num].spr2 == true && string(name[command_script[num].id_name]) == sprite[command_script[num].id_spr2].Get_Sprite_Box(7))
			{
				thread woo(Get_Speak, Box_Sprites, sprite[command_script[num].id_spr2], get_speak[(sprite[command_script[num].id_spr2].Get_name())].ch_speak[get_speak[(sprite[command_script[num].id_spr2].Get_name())].x], &speak_task, &stop_speak_task);
				woo.detach();
			}
			else if (command_script[num].spr3 == true && string(name[command_script[num].id_name]) == sprite[command_script[num].id_spr3].Get_Sprite_Box(7))
			{
				thread woo(Get_Speak, Box_Sprites, sprite[command_script[num].id_spr3], get_speak[(sprite[command_script[num].id_spr3].Get_name())].ch_speak[get_speak[(sprite[command_script[num].id_spr3].Get_name())].x], &speak_task, &stop_speak_task);
				woo.detach();
			}
		}
		if (string(name[command_script[num].id_name]) == "РђСЏСЃСЌ") // аясэ
		{
			get_speak[0].x++;
		}
		else if (string(name[command_script[num].id_name]) == "Р”Р°Р№СЃСѓРєСЌ") // дайсукэ
		{
			get_speak[5].x++;
		}
		else if (string(name[command_script[num].id_name]) == "РЎР°РѕСЂРё") // саори
		{
			get_speak[6].x++;
		}
		else if (string(name[command_script[num].id_name]) == "РљРёСЂРёРЅРѕ") // кирино
		{
			get_speak[4].x++;
		}
		else if (string(name[command_script[num].id_name]) == "РњР°РЅР°РјРё") // манами
		{
			get_speak[3].x++;
		}
		else if (string(name[command_script[num].id_name]) == "РљСѓСЂРѕРЅСЌРєРѕ") // куронэко
		{
			get_speak[2].x++;
		}
	}

	void Get_Text(cocos2d::Node *Game_Mode)
	{
		//stop_speak_task = true;
		//while (true) // идет проверка пока старый поток вывода текста не завершится - ждать его
		//if (old_text == false && speak_task == false)
		//		break;
		auto wait([=](bool *task) // идет проверка пока старый поток вывода текста не завершится - ждать его
		{
			lockthread.lock();
			for (;;)
			{
				Sleep(100);
				if (*task == false)
					break;
			}
			auto *set_text = static_cast<cocos2d::ui::Text*>(Game_Mode->getChildByName("Set_text")); // элемент текста в игровом меню
			auto *set_name = static_cast<cocos2d::ui::Text*>(Game_Mode->getChildByName("Set_name")); // элемент имени в игровом меню

			set_text->enableShadow(ccc4(0, 0, 0, 150));
			set_name->enableShadow(ccc4(0, 0, 0, 150));
			set_text->setTextHorizontalAlignment(TextHAlignment::LEFT);
			set_text->setTextVerticalAlignment(TextVAlignment::TOP);
			if (command_script[num].name == true)
			{
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
				set_name->setString(string(name[command_script[num].id_name]));
				});
				//Get_Speak_sp(Game_Mode); //выводит анимацию лица
			}
			else
				Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
				set_name->setString("");
			});
			//thread get_world(letter, set_text, Set_Text(), &old_text, Game_Mode);
			//get_world.detach();

			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
				set_text->setString(string(Set_Text()));
			});
			auto *Button_click = static_cast<cocos2d::ui::Button*>(Game_Mode->getChildByName("Button_click"));

			Get_Voice();
			
			Button_click->addClickEventListener([=](Ref *)
			{			
				lockthread.lock();
				Button_click->setTouchEnabled(false);
				num++; // существует баг при большом количестве нажатий
				Get_Script(Game_Mode);
				lockthread.unlock();
			});
			Sleep(100);
			Button_click->setTouchEnabled(true);
			lockthread.unlock();
		});
		thread setup(wait, task_for_text);
		setup.detach();
	
		



	}

	void Get_Shake(Node *Game_Mode, commands &temp)
	{
		if (command_shake[temp.id_shake] == "1") // трясется экран во все стороны
		{
			auto scene = Game_Mode->getChildByName("Box_scene");
			scene = scene->getChildByName("Set_scene");
			thread woow(shake, scene);
			woow.detach();
			//shake (scene);

		}
		else if (command_shake[temp.id_shake] == "2") // трясется только текстбокс
		{
			auto textbox = Game_Mode->getChildByName("Text_Box");
			thread woow(shake, textbox);
			woow.detach();
			//shake(textbox);
		}
		else if (command_shake[temp.id_shake] == "3") // вверх вниз + белая вспышка
		{

		}
	}

	void Get_Sound(Node *Game_Mode, commands &temp)
	{
		//Game_id = cocos2d::experimental::AudioEngine::play2d(command_sound[temp.id_sound], false, All_Volume*Game_Volume);
	}


	void Run_star(cocos2d::Node *Game_Mode)
	{
		//auto *Star = Game_Mode->getChildByName("Star");
		//cocostudio::timeline::ActionTimeline *AllTime = CSLoader::createTimeline("All_Scene_cocos\\Game_Scene\\Game_Menu.csb");
		//AllTime->setTimeSpeed(1.0f);
		//AllTime->gotoFrameAndPlay(0);
		//Star->setVisible(true);
		//Star->runAction(AllTime);
	}

	void Get_Script(cocos2d::Node *Game_Mode)
	{
		auto *Button_click = static_cast<cocos2d::ui::Button*>(Game_Mode->getChildByName("Button_click"));
		auto *set_star = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Set_Star")); // элемент звездочки в игровом меню
		auto *Restart = static_cast<cocos2d::ui::Button*>(Game_Mode->getChildByName("Restart"));
		auto *Star = Game_Mode->getChildByName("Star");
		Star->stopAllActions();
		Star->setVisible(false);
		

		//Restart->addClickEventListener([=](Ref *)
		//{
		//	num = 0;
		//	for (int n = 0; n < 8; n++)
		//		get_speak[n].x = 0;
		//	this->Get_Script(Game_Mode);
		//});



		if (command_script[num].mus == true)
		{
			//Get_Music(command_script[num].id_mus);
		}
		if (command_script[num].scn == true)
		{
			Get_Scene(Game_Mode, command_script[num]);
			if (command_script[num].nextscript == true)
			{
				Get_nextscript(Game_Mode, command_script[num].id_nextscript);
				return;
			}
			else
			{
				Get_Text(Game_Mode);
			}
		}
		else  //если сцена не менялась
		{
			if (command_script[num].spr1 == true || command_script[num].spr2 == true || command_script[num].spr3 == true) //проверка на вызов спрайтов
			{
				Get_Sprite(Game_Mode, false, false);
				Get_Text(Game_Mode);
			}
			else
			{
				Get_Text(Game_Mode);
			}
		}
		if (command_script[num].sound == true)
		{
			//Get_Sound(Game_Mode, command_script[num]);
		}
		if (command_script[num].shake == true)
		{
		//	Get_Shake(Game_Mode, command_script[num]);
		}

	}
};

static GAMEBOX GAME; // СОЗДАНИЕ ОБЪЕКТА ИГРОВОЙ ЛОГИКИ

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


void Clear_Old_sprite(Node *Game_Mode, bool *task)
{
	*task = true;
	Node *Box_scene = Game_Mode->getChildByName("Box_scene");
	Node *Box_unscene = Game_Mode->getChildByName("Box_unscene");

	Node *Box_Sprites = Box_scene->getChildByName("Box_Sprites");

	auto Sprite_und1 = Box_Sprites->getChildByName("Sprite_1");
	auto Sprite_swich1 = Box_unscene->getChildByName("Sprite_1_switch");

	auto Sprite_und2 = Box_Sprites->getChildByName("Sprite_2");
	auto Sprite_swich2 = Box_unscene->getChildByName("Sprite_2_switch");

	auto Sprite_und3 = Box_Sprites->getChildByName("Sprite_3");
	auto Sprite_swich3 = Box_unscene->getChildByName("Sprite_3_switch");


	auto *Set_Sprite_Swich1 = static_cast<cocos2d::Sprite*>(Sprite_swich1->getChildByName("Sprite"));
	auto *Set_Blink_Swich1 = static_cast<cocos2d::Sprite*>(Sprite_swich1->getChildByName("Blink"));
	auto *Set_Speak_Swich1 = static_cast<cocos2d::Sprite*>(Sprite_swich1->getChildByName("Speak"));
	auto *Set_Sprite_Swich2 = static_cast<cocos2d::Sprite*>(Sprite_swich2->getChildByName("Sprite"));
	auto *Set_Blink_Swich2 = static_cast<cocos2d::Sprite*>(Sprite_swich2->getChildByName("Blink"));
	auto *Set_Speak_Swich2 = static_cast<cocos2d::Sprite*>(Sprite_swich2->getChildByName("Speak"));
	auto *Set_Sprite_Swich3 = static_cast<cocos2d::Sprite*>(Sprite_swich3->getChildByName("Sprite"));
	auto *Set_Blink_Swich3 = static_cast<cocos2d::Sprite*>(Sprite_swich3->getChildByName("Blink"));
	auto *Set_Speak_Swich3 = static_cast<cocos2d::Sprite*>(Sprite_swich3->getChildByName("Speak"));

	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
		Set_Sprite_Swich1->setTexture("Sprites\\Samples\\Sample_Sprite.png");
		Set_Blink_Swich1->setTexture("Sprites\\Samples\\Sample_Blink.png");
		Set_Speak_Swich1->setTexture("Sprites\\Samples\\Sample_Speak.png");
		Set_Sprite_Swich2->setTexture("Sprites\\Samples\\Sample_Sprite.png");
		Set_Blink_Swich2->setTexture("Sprites\\Samples\\Sample_Blink.png");
		Set_Speak_Swich2->setTexture("Sprites\\Samples\\Sample_Speak.png");
		Set_Sprite_Swich3->setTexture("Sprites\\Samples\\Sample_Sprite.png");
		Set_Blink_Swich3->setTexture("Sprites\\Samples\\Sample_Blink.png");
		Set_Speak_Swich3->setTexture("Sprites\\Samples\\Sample_Speak.png");
		Box_unscene->setOpacity(0);
		*task = false;
	});


}


void search_voice(vector<string> *out, const char *filename, string num_voice)
{
	lockthread.lock();
	ifstream file;
	string buff = "    ";//буфер байтов файла - нужен для поиска коробки с дирректориями
	string tempdir; // просто временная дерриктория для копирования строк из файла в вектор
	int relese = 0; // считает совпадения байт
	file.open(filename, ios::binary);
	for (int x = 0; x < 4; x++)
		buff[x] = num_voice[x];
	
	string finder = string("Voice\\0000" + buff + ".mp3");
	while (getline(file, tempdir))
	{
		tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ
		if (tempdir == finder)
		{
			(*(out)).push_back(tempdir);
			break;
		}
	}
	lockthread.unlock();
}

void Show_and_Hide(cocos2d::Node *Game_Mode, string dir, vector<SPRITEBOX> sprite, vector<bool*> task_oldblink, bool ignore_scene, bool ignore_sprite, bool *task) // только после полного завершения блока начинать вывод текста
{

	auto setup([=](bool *task)
	{
		*task = true; //ключевое значение
		auto *Text_Box = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Text_Box"));
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			auto *set_name = static_cast<cocos2d::ui::Text*>(Game_Mode->getChildByName("Set_name"));
			auto *set_text = static_cast<cocos2d::ui::Text*>(Game_Mode->getChildByName("Set_text"));
			set_name->setString(" ");
			set_text->setString(" ");
			Hide_text_box(Text_Box); //анимация скрытия
		});
		bool *temp = new bool{ true };
		shared_ptr<bool> task_swich(temp);
		Switch_scene (Game_Mode, dir, sprite, task_oldblink, ignore_scene, ignore_sprite, temp, 800); // 800 - //ждет
		for (;;)
		{
			Sleep(100);
			if (*temp == false)
				break;
		}
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
		Show_text_box(Text_Box);
		});
		Sleep(800);
		*task = false; //если все выполнил
	});
	thread get(setup, task);
	get.detach();
}

void Switch_scene(cocos2d::Node *Game_Mode, string dir, vector<SPRITEBOX> sprite, vector<bool*> task_oldblink,  bool ignore_scene, bool ignore_sprite, bool *task, int preload)
{
	lockthread.lock();
	Sleep(preload);
	*task = true;
	Node *Box_scene = Game_Mode->getChildByName("Box_scene");
	auto set_scene = static_cast<Sprite*>(Box_scene->getChildByName("Set_scene"));
	Node *Box_unscene = Game_Mode->getChildByName("Box_unscene");
	auto set_unscene = static_cast<Sprite*>(Box_unscene->getChildByName("Set_unscene"));
	Node *Box_Sprites = Box_scene->getChildByName("Box_Sprites");
	Node *Temp_Box_Sprites;
	string temp_sprite, temp_blink, temp_speak;

	if (ignore_sprite == false && ignore_scene == false) // если спрайт есть и сцена тоже .................................................. все тоже самое что и в swich sprite с ключем true НО без swich sprite
	{// нужно дописать с новыми bool



		GAME.Get_Sprite(Game_Mode, false, true); // записываем только адреса без вызова спрайта через get_sprite

		bool custom_swich = false;
		bool old_sprite[] = { false, false, false };
		for (int n = 0; n < sprite.size(); n++)
		{
			if (sprite[n].Get_custom_swich() == "0")
			{
				continue;
			}
			else
			{
				custom_swich = true;
			}
		}

		for (int l = 0; l < sprite.size(); l++) //цикл для всех спрайтов
		{			
			if (nump_nf[sprite[l].Get_id()-1] == true) // если существует поток с активным морганием - убиваем
			{
				old_sprite[l] = true;
				nump_nf[sprite[l].Get_id()-1] = false;
				while (true) // идет проверка завершился ли прошлый поток моргания до его завершения
				{
					if (*task_oldblink[sprite[l].Get_id() - 1] == false)
						break;
				}
			}
			if (custom_swich == false)
			{
				bool *podtask = new bool{ true };
				shared_ptr <bool> p_podpodtask(podtask);
				if (GAME.Get_id_Position() == sprite[l].Get_id())
					sprite[l].Get_Sprite(Game_Mode, podtask, GAME.Get_Position());
				else
					sprite[l].Get_Sprite(Game_Mode, podtask);

				for (;;)
				{
					Sleep(100);
					if (*podtask == false)
						break;
				}
			}
		}

		for (int n = 0; n < sprite.size(); n++) // отвечает за вывод действия на спрайт
		{
			if (sprite[n].Get_action() != "None")
			{
				bool *podtask = new bool{ true };
				shared_ptr <bool> p_podtask(podtask);
				GAME.Get_ActionSprite(Game_Mode, sprite[n], old_sprite[n], podtask);
				for (;;)
				{
					Sleep(100);
					if (*podtask == false)
						break;
				}
			}
		}

		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			set_unscene->setVisible(true);
			set_unscene->Sprite::setTexture(dir);
		});
		auto set_texture = CallFunc::create([=]()
		{
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			set_scene->Sprite::setTexture(dir);
			});
		});
		if (custom_swich == false)
		{
			Box_unscene->runAction(FadeIn::create(0.7f));
		}
		else
		{
			Box_unscene->runAction(Sequence::create(FadeIn::create(0.7f), FadeOut::create(0.0f), nullptr));
		}

		set_scene->runAction(Sequence::create(DelayTime::create(0.7f), set_texture, nullptr));



		auto wait([=](bool *task, vector <SPRITEBOX> sprite)
		{
			for (;;)
			{
				Sleep(100);
				if ((Box_unscene->getOpacity() == 0 && custom_swich == true) || (Box_unscene->getOpacity() == 255 && custom_swich == false))
					break;
			}
			if (custom_swich == false)
			{
				for (int x = 0; x < sprite.size(); x++) //изменяет значения для потоков мограния и возобновляет потоки
				{
					bool *podtask = new bool{ true };
					shared_ptr <bool> p_podpodtask(podtask);
					sprite[x].Get_Sprite_complete(Game_Mode, true, podtask);
					for (;;)
					{
						Sleep(100);
						if (*podtask == false)
							break;
					}
					if (sprite[x].Get_Sprite_Box(6) == "false") //проверка не ушел ли спрайт только что
					{ // тогда создается поток моргания для спрайта

						thread blink(Get_blink, Box_Sprites, sprite[x], task_oldblink[x]);
						blink.detach();

					}
				}
				bool *podtask = new bool{ true };
				shared_ptr <bool> p_podpodtask(podtask);
				Clear_Old_sprite(Game_Mode, podtask);
				for (;;)
				{
					Sleep(100);
					if (*podtask == false)
						break;
				}
			}
			else if (custom_swich == true)
			{
				vector<bool> simple;
				simple.push_back(false);
				simple.push_back(false);
				simple.push_back(false);

				bool *podpodtask = new bool{ true };
				shared_ptr <bool> p_podpodtask(podpodtask);
				Get_sprite(Game_Mode, sprite, task_oldblink, simple, podpodtask);
				for (;;)
				{
					Sleep(100);
					if (*podpodtask == false)
						break;
				}
			}

			*task = false;
		});
		thread setup(wait, task, sprite);
		setup.detach();

		
	}	
	else if (ignore_sprite == true && ignore_scene == false)//если cпрайта нет но сцена есть
	{
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			set_unscene->setVisible(true);
			set_unscene->Sprite::setTexture(dir);
		});
		auto set_texture = CallFunc::create([=]()
		{
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			set_scene->Sprite::setTexture(dir);
			});
		});
		Box_unscene->runAction(Sequence::create(FadeIn::create(0.7f), FadeOut::create(0.0f), nullptr));
		set_scene->runAction(Sequence::create(DelayTime::create(0.7f), set_texture, nullptr));

		auto wait([=](bool *task)
		{
			for (;;)
			{
				Sleep(100);
				if (Box_unscene->getOpacity() == 0)
					break;
			}
			*task = false;
		});
		thread setup(wait, task);
		setup.detach();
	}
	lockthread.unlock();
}

void Swich_Sprite(cocos2d::Node *image, cocos2d::Node *swichimage, int n, string custom_swich, bool hide_mode, bool *task)
{
	*task = true;
	bool use_custom = false;
	float z = 0;
	int smeh_position = 50;
	Node *temp_node;
	if (custom_swich != "0")
	{
		use_custom = true;
		if (hide_mode == true)
			temp_node = image;
		else
			temp_node = swichimage;
	}

	if (use_custom == true) // Идет определение кастомное ли появление спрайта
	{
		if (custom_swich == "LTR")
		{
			if (hide_mode == false) //пропадает ли спарйт иначе - появляется и нужно сместить по координатам
			{
				temp_node->setPosition(swichimage->getPosition() - Vec2(50, 0));
			}
			temp_node->runAction(MoveBy::create(0.7f, Vec2(smeh_position, 0)));
		}
		else if (custom_swich == "RTL")
		{
			if (hide_mode == false)
			{
				temp_node->setPosition(swichimage->getPosition() + Vec2(50, 0));
			}
			temp_node->runAction(MoveBy::create(0.7f, Vec2(-smeh_position, 0)));
		}
	}
	swichimage->runAction(Sequence::create(FadeIn::create(0.7f), nullptr));
	image->runAction(Sequence::create(FadeOut::create(0.7f), nullptr));
	auto wait([=](bool *task)
	{
		for (;;)
		{
			Sleep(100);
			if (image->getOpacity() == 0)
				break;
		}
		*task = false;
	});
	thread setup(wait, task);
	setup.detach();
}




void Get_sprite(Node *Game_Mode, vector<SPRITEBOX> sprite, vector<bool*> task_oldblink, vector<bool> simple, bool *task)
{
	*task = true;

	Node *Box_scene = Game_Mode->getChildByName("Box_scene");
	Node *Box_unscene = Game_Mode->getChildByName("Box_unscene");
	Node *Box_Sprites = Box_scene->getChildByName("Box_Sprites");
	Node *Temp_Box_Sprites;

	vector<thread*> p_blink;

	bool old_sprite[] = { false, false, false };
	for (int n = 0; n < sprite.size(); n++) // закрываются любые прошлые потоки мограний спрайтов под тем же id что и вызываются
	{
		if (sprite[n].Check_inf() == true) // Данная проверка появилась как следствие создания actionsprite - проверяет есть ли вообще информация в текущем объекте спрайта
		{
			if (nump_nf[sprite[n].Get_id() - 1] == true)
			{
				old_sprite[n] = true;
				nump_nf[sprite[n].Get_id() - 1] = false;
				while (true) // идет проверка завершился ли прошлый поток моргания до его завершения
				if (*task_oldblink[sprite[n].Get_id() - 1] == false)
					break;
			}
			bool *podtask = new bool{ true };
			shared_ptr <bool> p_podpodtask(podtask);
			if (GAME.Get_id_Position() == sprite[n].Get_id())
				sprite[n].Get_Sprite(Game_Mode, podtask, GAME.Get_Position());
			else
				sprite[n].Get_Sprite(Game_Mode, podtask);

			for (;;)
			{
				Sleep(100);
				if (*podtask == false)
					break;
			}
		}
	}


	for (int n = 0; n < sprite.size(); n++) // отвечает за вывод действия на спрайт
	{
		if (sprite[n].Get_action() != "None")
		{
			bool *podtask = new bool{ true };
			shared_ptr <bool> p_podtask(podtask);
			GAME.Get_ActionSprite(Game_Mode, sprite[n], old_sprite[n], podtask);
			for (;;)
			{
				Sleep(100);
				if (*podtask == false)
					break;
			}
		}
	}

	bool custom_swich = false;
	for (int n = 0; n < sprite.size(); n++)
	{
		if (sprite[n].Get_custom_swich() == "0")
		{
			continue;
		}
		else
		{
			custom_swich = true;
		}
	}

	if (custom_swich == true) // проверка есть ли катсомный свич - если есть хоть один - все переходы по очереди
	{
		for (int n = 0; n < sprite.size(); n++)
		{
			if (sprite[n].Check_inf() == true) // Данная проверка появилась как следствие создания actionsprite - проверяет есть ли вообще информация в текущем объекте спрайта
			{
				if (simple[n] == false) //проверка на простой вызов или сложный 
				{
					switch (sprite[n].Get_id())
					{
					case (1) :
						Temp_Box_Sprites = Box_Sprites->getChildByName("Sprite_1");
						break;
					case (2) :
						Temp_Box_Sprites = Box_Sprites->getChildByName("Sprite_2");
						break;
					case (3) :
						Temp_Box_Sprites = Box_Sprites->getChildByName("Sprite_3");
						break;
					}

					//Temp_Box_UnSprites->setPosition(GAME.Get_Position());
					bool *podtask = new bool{ true };
					shared_ptr <bool> p_podtask(podtask);
					Swich_Sprite(Temp_Box_Sprites, Box_unscene, 40, sprite[n].Get_custom_swich(), sprite[n].Get_hide(), podtask);

					for (;;) //ожидание под функций
					{
						Sleep(100);
						if (*podtask == false)
							break;
					}
				}
			}
		}
	}
	else if (sprite.size() == 1)
	{
		for (int n = 0; n < sprite.size(); n++)
		{
			if (sprite[n].Check_inf() == true) // Данная проверка появилась как следствие создания actionsprite - проверяет есть ли вообще информация в текущем объекте спрайта
			{
				if (simple[n] == false) //проверка на простой вызов или сложный 
				{
					Node *Temp_Box_Sprites2;
					switch (sprite[n].Get_id())
					{
					case (1) :
						Temp_Box_Sprites = Box_Sprites->getChildByName("Sprite_1");
						Temp_Box_Sprites2 = Box_unscene->getChildByName("Sprite_1_switch");
						break;
					case (2) :
						Temp_Box_Sprites = Box_Sprites->getChildByName("Sprite_2");
						Temp_Box_Sprites2 = Box_unscene->getChildByName("Sprite_2_switch");
						break;
					case (3) :
						Temp_Box_Sprites = Box_Sprites->getChildByName("Sprite_3");
						Temp_Box_Sprites2 = Box_unscene->getChildByName("Sprite_3_switch");
						break;
					}
					if (GAME.Get_id_Position() == sprite[n].Get_id())
					{
						Temp_Box_Sprites2->setPosition(GAME.Get_Position());
					}
					bool *podtask = new bool{ true };
					shared_ptr <bool> p_podtask(podtask);
					Swich_Sprite(Temp_Box_Sprites, Box_unscene, 40, sprite[n].Get_custom_swich(), sprite[n].Get_hide(), podtask);
					for (;;) //ожидание под функций
					{
						Sleep(100);
						if (*podtask == false)
							break;
					}
				}
			}
		}
	}
	else
	{
		bool *podtask = new bool{ true };
		shared_ptr <bool> p_podtask(podtask);
		Swich_Sprite(Box_Sprites, Box_unscene, 40, "0", false, podtask);
		for (;;) //ожидание под функций
		{
			Sleep(100);
			if (*podtask == false)
				break;
		}
	}





	// если вдруг ВДРУГ будет одновременный вызов двух смен и третей обычный(только лица) будет немного другой эффект и придется дописывать


	for (int n = 0; n < sprite.size(); n++) //завершающий вызов спрайта
	{
		if (sprite[n].Check_inf() == true)
		{
			bool *podtask = new bool{ true };
			shared_ptr <bool> p_podpodtask(podtask);
			if (GAME.Get_id_Position() == sprite[n].Get_id())
				sprite[n].Get_Sprite_complete(Game_Mode, podtask, GAME.Get_Position());
			else
				sprite[n].Get_Sprite_complete(Game_Mode, false, podtask);
			for (;;)
			{
				Sleep(100);
				if (*podtask == false)
					break;
			}
		}
	}

	for (int n = 0; n < sprite.size(); n++) // здесь идет создание морганий для каждого спрайта что существует
	{
		if (sprite[n].Check_inf() == true)
		{
			if (sprite[n].Get_Sprite_Box(6) == "false") //проверка не ушел ли спрайт только что
			{ // тогда создается поток моргания для спрайта
				thread blink(Get_blink, Box_Sprites, sprite[n], task_oldblink[n]);
				blink.detach();
			}
		}
	}

	*task = false; //указание завершение главного потока для вывода текста

}

//void Get_Speak(Node *Box_Sprites, SPRITEBOX sprite, vector<bool> speak, bool *task, bool *stop_task) ///////////////////////////////////////////////////////////////////////////////////// ДОПИСАТЬ
//{
//	sprite.Speak_Create(Box_Sprites, speak, task, stop_task);
//}

void Get_blink(Node *Box_Sprites, SPRITEBOX sprite, bool *task)
{
	sprite.Blink_Create(Box_Sprites, task);
}

void letter(cocos2d::ui::Text* set_text, shared_ptr<char> p_buff, bool *task, Node *Game_Mode) // выводит текст буква за буквой
{
	*task = true;
	auto *Button_click = static_cast<cocos2d::ui::Button*>(Game_Mode->getChildByName("Button_click"));
	string text = "";
	//auto buff = (&*p_buff);
	shared_ptr<bool> stoptask(new bool{false});
	
	Button_click->setVisible(true);
	if (Button_click)
	{
		Button_click->addClickEventListener([=](Ref *)
		{
			*stoptask = true;
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
				set_text->setString((&*p_buff));
			});
		});
	}
	for (int n = 0; n < string((&*p_buff)).length(); n++)
	{
		text += (&*p_buff)[n];
		Sleep(30); // поместить переменную - потом будет настраиваться скорость текста через настройки
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			if (*stoptask == false)
			{				
				set_text->setString(text);			
			}
			else
			{
				GAME.Run_star(Game_Mode);
				Button_click->addClickEventListener([=](Ref *)
				{
					//num++;
					Button_click->setVisible(false);
					GAME.Get_Script(Game_Mode);
				});
			}
		});
		if (*stoptask == true)
		{
			
			*task = false;
			return;
		}
	}
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
	if (*stoptask == false)
	{
		GAME.Run_star(Game_Mode);
		if (Button_click)
		{
			Button_click->addClickEventListener([=](Ref *)
			{
				auto *Star = Game_Mode->getChildByName("Star");
				Star->stopAllActions();
				Button_click->setVisible(false);
				//num++;
				GAME.Get_Script(Game_Mode);
			});
		}
		*task = false;
		if (GAME.get_Auto_Mode() == true)
		{
			thread setup(use_Auto_Mode, Game_Mode);
			setup.detach();
		}
	}
	});
}


void use_Auto_Mode(Node *Game_Mode)
{
	auto *Auto_Mode_Button = static_cast<ui::Button*>(Game_Mode->getChildByTag(1835));
	auto Auto_Mode_Sprite = static_cast<Sprite*>(Game_Mode->getChildByTag(259));
	Auto_Mode_Button->addClickEventListener([=](Ref *)
	{
		System_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[0], false, All_Volume*System_Volume);
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]
		{
			Auto_Mode_Sprite->setTexture("Buttons\\Game\\avto_off.png");
		});
		GAME.set_Auto_Mode(Game_Mode, false);
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
	});
	auto *Button_click = static_cast<cocos2d::ui::Button*>(Game_Mode->getChildByName("Button_click"));
	bool task = true;
	bool *p_task = &task;
	auto start = steady_clock::now();
	auto end = steady_clock::now();
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
		Button_click->addClickEventListener([=](Ref *)
		{
			auto *Star = Game_Mode->getChildByName("Star");
			Star->stopAllActions();
			//num++;
			GAME.Get_Script(Game_Mode);
			*p_task = false;
		});
	});
	auto y = time_point_cast<milliseconds>(start)+(milliseconds(Speed_Auto_Text*100));
	while (true)
	{
		end = steady_clock::now();
		auto x = time_point_cast<milliseconds>(end);

		if (GAME.get_Auto_Mode() == false || p_task == false)
		{
			return;
		}
		if (x > y)
		{
			//num++;
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
				GAME.Get_Script(Game_Mode);
			});
			return;
		}
	}
}