
#include <2d\CCSprite.h>
//Определяем классы для текста и для спрайта. А также объявляем их методы.
//#include "SampleLive2DSprite.h" 


////////////////////////////////
////////////////////////////////
////////////////////////////////

#include <memory> // для использования smart_pointer
#include <vector>
#include "AudioEngine.h"
#include <SpriteBox.h>
#include <Viewconsole.h>
#include <fstream> // библиотека работы с файлом

#include "Live2D/LAppView.h"
#include "Live2D/LAppLive2DManager.h"
#include "Live2D/LAppDefine.h"
#include "Live2DFramework.h"


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
//vector<string> setmotion; //взятие диреекторий motion
static bool Skip_All, ORE_old, Com_twoshot, Tips_twoshot, Text_old, Autosave1, Autosave2, Musalb; // Все настройки типа bool

static float All_Volume, Background_Volume, System_Volume, Game_Volume, Voice_Volume; // Вся громкость

static int Speed_Skip_Text, Speed_Text, Speed_Auto_Text; // Скорость режима пропуска текста, текста, и режима авто чтения

static int Background_id = NULL, System_id = NULL, Game_id = NULL, Voice_id = NULL; // id потоков аудио будет здесь

static bool temp_sw = false; // Переменная которая указывает были ли изменения в настройках по умолчанию false

bool nump_nf[3] = { false, false, false }; //отвечает за потоки морганий спрайтов

void background_smooth(Node *Game_Mode, float volume, string dir_next_music);
MAINBOX *Head_Menu;

class GAMEBOX/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
private:


	struct modelbox
	{
		int INDEX_MODEL;
		int INDEX_TEXTURE;
		float x;
		float y;
		float z = 1;
	};

	struct command_modelbox
	{
		vector<string> EXPRESSION_BOX;
		vector<string> EXPRESSION_BOX_ACTION;
		int num_idle;
		int num_action;
		bool action = false;
	};

	struct cloudbox
	{
		int arg;// 1 или 0
		string text;
		int skip;
		float duration;
	};


	vector<modelbox> command_model_create;
	vector<command_modelbox> command_model_commands;

	string command_model_create_start = "[create_model]";
	string command_model_create_end = "[/create_model]";
	string command_model_commands_start = "[commands_model]";
	string command_model_commands_end = "[/commands_model]";

	//ЗАМЕТКА
	// подпригивание спрайта, увеличение -  вызывается командой <actionsprite> в теле [getsprite] JUMP MINIJUMP DECREASE INCREASE


	//СЕЙЧАС
	//управления переходом на скрипты через скрипт
	//скип определенного количества текста и команд через скрипт
	//вызов оре
	//облака

	//ПОТОМ
	//управление авто
	//управление скипом
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
	vector<vector<bool>> command_voice_model;
	vector<cloudbox> command_cloud;
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
	string command_custom_order_start = "[getorders]";
	string command_custom_order_end = "[/getorders]";
	string command_clouds_start = "[getclouds]";
	string command_clouds_end = "[/getclouds]";
	string command_skip_start = "[getskip]";
	string command_skip_end = "[/getskip]";
	string command_voice_start = "[getvoice]";
	string command_voice_end = "[/getvoice]";
	string command_endnum = "[endnum]";
	struct commands // структура для вызовов // порядок вызовов через orders
	{
		bool name = false;
		bool mus = false;
		bool scn = false;
		bool shake = false;
		bool sound = false;
		bool create_model = false;
		bool command_model = false;
		bool voice_model = false;
		bool cloud = false;
		bool skip = false;
		bool spr[3];
		bool nextscript = false;
		bool end = false;
		int id_name = NULL;
		int id_mus = NULL;
		int id_scn = NULL;
		int id_shake = NULL;
		int id_sound = NULL;
		int id_create_model = NULL;
		int id_command_model = NULL;
		//int id_model = NULL;
		int id_voice_model = NULL;
		int id_cloud = NULL;
		int skip_count = NULL;
		int id_spr[3];
		int id_nextscript = NULL;
		vector<string> orders; // 1 - музыка 2 - сцена 3 - спрайт 4 - звук 5 - тряска 6 - текст 
	};

	vector<commands> command_script; // хранит вектор структур всех команд


	bool Auto_Mode = false;

	int num = 0;
	int skip = 0;


	struct active_sprite //структура для активных спрайтов
	{
		SPRITEBOX id[3];
		bool use_id[3];
	};


	active_sprite usesprite; //хранит значения какой спрайт активен и под каким id

public:

	GAMEBOX()
	{
		usesprite.use_id[0] = false;
		usesprite.use_id[1] = false;
		usesprite.use_id[2] = false;
	}

	bool get_Auto_Mode()
	{
		return Auto_Mode;
	}

	void Clear_Data()
	{
		num = 0;
		name.clear(); // вектор который хранит все имена
		text.clear(); // вектор который хранит весь текст
		voice.clear();// вектор который хранит все дерриктории озвучки
		command_music.clear(); // вектор который хранит команды вызовы музыки
		command_sprite.clear(); // вектор который хранит команды вызовы спрайтов ***пометка - в отличии от остальных является лишь временным хранилещем по своей сути, после выполнения Set_script остается пустым, настаящие хранилище спрайтов в векторе sprite
		sprite.clear(); // вектор который хранит объекты созданных спрайтов
		command_swich_scene.clear(); //вектор который хранит команды вызовы сцен
		command_shake.clear(); // вектор который хранит команды тряски экрана
		command_sound.clear(); // вектор который хранит команды вызовов игровых звуков
		command_nextscript.clear();
		command_script.clear();
		//command_model.clear();
		nump_nf[0] = false;
		nump_nf[1] = false;
		nump_nf[2] = false;
	}

	int string_to_int(string text)
	{
		stringstream temp;
		temp << text;
		int x;
		temp >> x;
		return x;
	}

	float string_to_float(string text)
	{
		stringstream temp;
		temp << text;
		float x;
		temp >> x;
		return x;
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
		if (command_swich_scene.size()>1)
		{

			if (command_swich_scene.back() == string("ALLBLACK"))
			{
				(*temp).scn = true;
				(*temp).id_scn = command_swich_scene.size() - 1;
				return;
			}

			else if (command_swich_scene[command_swich_scene.size() - 2] == string("HIDEBOX") || command_swich_scene[command_swich_scene.size() - 2] == string("SHOWBOX") || command_swich_scene[command_swich_scene.size() - 2] == string("S&H")) // Это может вызывать ошибки
			{

				(*temp).scn = true;
				(*temp).id_scn = command_swich_scene.size() - 2;
				for (int i = 0; i < dir.size(); i++)  // ищет дирректории сцен для скрипта для SHOWBOX
				{
					if (string(dir[i]) == string("{" + command_swich_scene[command_swich_scene.size() - 1] + "}"))
					{
						command_swich_scene[command_swich_scene.size() - 1] = dir[i + 1];
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

	void Set_Create_Model(vector<string> command, commands *temp)
	{
		if (command.size()<3)
			throw string("ERROR_MISSING_COMMAND_MODEL");
		modelbox temp_modelbox;
		temp_modelbox.INDEX_MODEL = string_to_int(command[0]);
		temp_modelbox.INDEX_TEXTURE = string_to_int(command[1]);
		temp_modelbox.x = string_to_float(command[2]);
		temp_modelbox.y = string_to_float(command[3]);
		if (command.size()>3)
			temp_modelbox.z = string_to_float(command[4]);
		command_model_create.push_back(temp_modelbox);
		(*temp).create_model = true;
		(*temp).id_create_model = command_model_create.size() - 1;
	}

	void Set_Commands_Model(vector<string> command, commands *temp)
	{
		if (command.size()<2)
			throw string("ERROR_MISSING_COMMAND_MODEL");
		string expression = "{expression}";
		string end_expression = "{/expression}";
		string action_expression =  "{expression_action}" ;
		string end_action_expression = "{/expression_action}" ;
		string end_idle = "{/idle}";
		string end_action = "{/action}";
		command_modelbox temp_modelbox;
		for (int n = 0; n < command.size(); n++)
		{
			if (command[n] == expression)
			{
				n++;
				while (command[n] != end_expression)
				{
					temp_modelbox.EXPRESSION_BOX.push_back(command[n]);
					n++;
				}
			}
			if (command[n] == action_expression)
			{
				n++;
				while (command[n] != end_action_expression)
				{
					temp_modelbox.EXPRESSION_BOX_ACTION.push_back(command[n]);
					n++;
				}
			}
			if (command[n] == end_idle)
				temp_modelbox.num_idle = string_to_int(command[n - 1]);
			if (command[n] == end_action)
			{
				temp_modelbox.action = true;
				temp_modelbox.num_action = string_to_int(command[n - 1]);
			}

		}
		command_model_commands.push_back(temp_modelbox);
		(*temp).command_model = true;
		(*temp).id_command_model = command_model_commands.size() - 1;
	}
	
	void Set_Voice(vector<string> command, commands *temp)
	{
		auto string_to_bool([](char current)->bool
		{
			if (current == '1')
				return true;
			else
				return false;
		});

		vector<bool> temp_bool;
		string temp_inf;
		if (command[0] == "model")
		{
			temp_inf = command[1];
			for (int n = 0; n < temp_inf.length(); n++)
			{
				temp_bool.push_back(string_to_bool(temp_inf[n]));
			}
			command_voice_model.push_back(temp_bool);
			(*temp).voice_model = true;
			(*temp).id_voice_model = command_voice_model.size() - 1;
		}
	}

	void Set_Cloud(vector<string> command, commands *temp)
	{
		if (command.size()<4)
			throw string("ERROR_MISSING_CLOUDS_COMMANDS");
		cloudbox temp_cloud;
		temp_cloud.arg = string_to_int(command[0]);
		temp_cloud.text = command[1];
		temp_cloud.skip = string_to_int(command[2]);
		temp_cloud.duration = string_to_float(command[3])/1000;
		command_cloud.push_back(temp_cloud);
		(*temp).cloud = true;
		(*temp).id_cloud = command_cloud.size() - 1;
	}

	string Correct_Text()
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
		(*(temp)).create_model = false;
		(*(temp)).command_model = false;
		(*(temp)).voice_model = false;
		(*(temp)).cloud = false;
		(*(temp)).spr[0] = false;
		(*(temp)).spr[1] = false;
		(*(temp)).spr[2] = false;
		(*(temp)).nextscript = false;
		(*(temp)).skip = false;
		(*(temp)).id_name = NULL;
		(*(temp)).id_mus = NULL;
		(*(temp)).id_scn = NULL;
		(*(temp)).id_shake = NULL;
		(*(temp)).id_sound = NULL;
		(*(temp)).id_create_model = NULL;
		(*(temp)).id_command_model = NULL;
		(*(temp)).id_voice_model = NULL;
		(*(temp)).id_cloud = NULL;
		(*(temp)).id_spr[0] = NULL;
		(*(temp)).id_spr[1] = NULL;
		(*(temp)).id_spr[2] = NULL;
		(*(temp)).id_nextscript = NULL;
		(*(temp)).skip_count = NULL;
		(*(temp)).orders.clear();
	}

	void Set_Script(const vector<string> dirscripts, vector<string> &dirsprites, vector<string> &dirscene, vector<string> &dirmusic, int script) //получает текст из файла скрипта
	{

		ifstream buff; //поток файла
		string tempdir; // просто временная дерриктория для копирования строк из файла в вектор
		commands buff_command; // создает буфер который хранит в себе значения нужна ли музыка спрайт или смена картинки на данной строчке скрипта, должна после каждого прохода текста отчищаться New_command
		New_command(&buff_command);
		//active_sprite s;

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
						switch (id)
						{
						case 1:
							buff_command.spr[0] = true;
							buff_command.id_spr[0] = sprite.size() - 1;
							break;
						case 2:
							buff_command.spr[1] = true;
							buff_command.id_spr[1] = sprite.size() - 1;
							break;
						case 3:
							buff_command.spr[2] = true;
							buff_command.id_spr[2] = sprite.size() - 1;
							break;
						}
						command_sprite.clear(); // отчистка вектора для комманд cпрайта
						break;// и выход
					}
					command_sprite.push_back(tempdir); //копирование в вектор команд спрайта, команды пока не дошел до конца команды
					if (command_sprite.size() > 10)
						throw string("ERROR_MISSING_END_COMMAND"); // исключение
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
			//															CREATE LIVE2D MODEL
			//====================================================================================================================================
			if (tempdir == command_model_create_start)
			{
				vector<string> temp_comands;
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_model_create_end) //если дошел до конца команды 
					{
						Set_Create_Model(temp_comands, &buff_command);
						break; // и выход
					}
					temp_comands.push_back(tempdir);
				}
				continue;
			}
			//====================================================================================================================================
			//															COMMANDS LIVE2D MODEL
			//====================================================================================================================================
			if (tempdir == command_model_commands_start)
			{
				vector<string> temp_comands;
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_model_commands_end) //если дошел до конца команды 
					{
						Set_Commands_Model(temp_comands, &buff_command);
						break; // и выход
					}
					temp_comands.push_back(tempdir);
				}
				continue;
			}
			//====================================================================================================================================
			//															 LIVE2D VOICE
			//====================================================================================================================================
			if (tempdir == command_voice_start)
			{
				vector<string> temp_comands;
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_voice_end) //если дошел до конца команды 
					{
						Set_Voice(temp_comands, &buff_command);
						break; // и выход
					}
					temp_comands.push_back(tempdir);
				}
				continue;
			}
			//====================================================================================================================================
			//																 CLOUD
			//====================================================================================================================================
			if (tempdir == command_clouds_start)
			{
				vector<string> temp_comands;
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_clouds_end) //если дошел до конца команды 
					{
						Set_Cloud(temp_comands, &buff_command);
						break; // и выход
					}
					temp_comands.push_back(tempdir);
				}
				continue;
			}
			//====================================================================================================================================
			//																 SKIP
			//====================================================================================================================================
			if (tempdir == command_skip_start)
			{
				vector<string> temp_comands;
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_skip_end) //если дошел до конца команды 
					{
						buff_command.skip = true;
						break; // и выход
					}
					buff_command.skip_count = string_to_int(tempdir);
				}
				continue;
			}
			//====================================================================================================================================
			//																 ENDNUM
			//====================================================================================================================================
			if (tempdir == command_endnum)
			{
				buff_command.end = true;
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
			//																ORDERS
			//====================================================================================================================================
			if (tempdir == command_custom_order_start)
			{
				while (getline(buff, tempdir))
				{
					tempdir = tempdir.substr(0, tempdir.size() - 1); // убирает последний символ строки
					if (tempdir == command_custom_order_end) //если дошел до конца команды 
					{
						break; // и выход
					}
					buff_command.orders.push_back(tempdir);
				}
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
				search_voice(&voice, "..\\Resources\\voice.txt", tempdir); // получение деррикторий для указанного файла voice

				command_script.push_back(buff_command);
				New_command(&buff_command);// сброс команд

			}
			//====================================================================================================================================
			//																END
			//====================================================================================================================================
		}
	}

	struct sprite_data
	{
		vector<SPRITEBOX> sprite_box;
		vector<bool> simple;
	};

	void Get_Skip()
	{
		if (skip == 0)
			throw string("ERROOR_MISSING_SKIP_NUM");
		num = skip;
		skip = 0;
	}

	void Next_num()
	{
		skip = 0;
		num++;
	}

	sprite_data Get_Sprite(cocos2d::Node *Game_Mode) //ключ simleuse используются в виде исключения ТОЛЬКО в ALLBLACK swichscene, ignorecommand осущевствляет выбор между вызовом спрайта с помощью этой функции или просто записать адреса
	{
		vector<SPRITEBOX> temp_sprite_box;
		vector<bool> simple;
		for (int n = 0; n < 3; n++)
		{
			if (command_script[num].spr[n] == true)
			{
				temp_sprite_box.push_back(sprite[command_script[num].id_spr[n]]); // сохраняем во временный вектор вызова спрайт бокса спрайт
				if (usesprite.use_id[n] == false) // если спрайт под этим id еще не вызван
				{ //  в дальнейшем помогает определить вызывать ли simple(смена только лица) вызов или нет (полная смена спрайта)
					usesprite.use_id[n] = true; // сохраняется значение bool в структуру usesprite что под данным id спрайт вызван 
					usesprite.id[n] = sprite[command_script[num].id_spr[n]]; // сохраняет в структуру сам вызванный спрайт
					if (temp_sprite_box.back().Chek_simplebox() == false) // указывает значение простой ли будет вызов или нет, идет проверка дерективы <SIMPLE>
						simple.push_back(false);
					else
						simple.push_back(true);
				}
				else //если уже вызван
				{
					if (sprite[command_script[num].id_spr[n]] == usesprite.id[n] && sprite[command_script[num].id_spr[n]].Get_hide() == false) //проверка нужен ли сложный вызов или нет
						simple.push_back(true); // если простой вызываем простой
					else
					{
						if (temp_sprite_box.back().Chek_simplebox() == false) // или же сложный, идет проверка дерективы <SIMPLE>
							simple.push_back(false);
						else
							simple.push_back(true);

						if (sprite[command_script[num].id_spr[n]].Get_hide() == true) // идет проверка пропадает ли спрайт
							usesprite.use_id[n] = false; // если пропадает то спрайт под этим id перестает быть активным
						else // и если он не пропадает сохраняем его новое значение в структуру активных спрайтов
							usesprite.id[n] = sprite[command_script[num].id_spr[n]];
					}
				}
			}
		} 
		sprite_data temp;
		temp.sprite_box.assign(temp_sprite_box.begin(), temp_sprite_box.end());
		temp.simple.assign(simple.begin(), simple.end());
		return (temp);
	}

	bool Old_Sprite(int id)
	{
		if (usesprite.use_id[id] == true)
			return true;
		else
			return false;
	}

	void Get_Text(Node *Game_Mode)
	{
		auto *set_text = static_cast<cocos2d::ui::Text*>(Game_Mode->getChildByName("Set_text")); // элемент текста в игровом меню
		auto *set_name = static_cast<cocos2d::ui::Text*>(Game_Mode->getChildByName("Set_name")); // элемент имени в игровом меню
		auto *Button_click = static_cast<cocos2d::ui::Button*>(Game_Mode->getChildByName("Button_click"));
		Button_click->addClickEventListener([=](Ref *)
		{
			Button_click->setVisible(false);
			set_text->setString("");
			set_name->setString("");
			cocos2d::experimental::AudioEngine::stop(Voice_id);
			CONSOLE.Star(Game_Mode, false);
			num++;
			Get_Script(Game_Mode);
		});
		set_text->enableShadow(ccc4(0, 0, 0, 155)); // включает тень
		set_name->enableShadow(ccc4(0, 0, 0, 155)); // включает тень
		if (command_script[num].name == true)
		{
			set_name->setString(string(name[command_script[num].id_name]));
		}
		else
		{
			set_name->setString("");
		}
		set_text->setString(Correct_Text());
		if (command_script[num].cloud == false)
		{
			if (command_script[num].skip == true)
				num = command_script[num].skip_count;
			Button_click->setVisible(true);
		}
		else
			CONSOLE.view(Game_Mode);
	}

	void search_voice(vector<string> *out, const char *filename, string num_voice)
	{
		
		ifstream file;
		string buff = "    ";//буфер байтов файла - нужен для поиска коробки с дирректориями
		string tempdir; // просто временная дерриктория для копирования строк из файла в вектор
		int relese = 0; // считает совпадения байт
		file.open(filename, ios::binary);
		for (int x = 0; x < 4; x++)
			buff[x] = num_voice[x];
		if (buff == "ffff")
		{
			(*(out)).push_back("ffff");
			return;
		}
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
	}
	
	void Get_Script(cocos2d::Node *Game_Mode)
	{
		
		auto *Restart = static_cast<cocos2d::ui::Button*>(Game_Mode->getChildByName("Restart"));

		vector<string> script_commands;



		if (command_script[num].orders.size() == 0)
		{

			if (command_script[num].create_model == true)
			{
				CONSOLE.Set_model_create_data(
					command_model_create[command_script[num].id_create_model].INDEX_MODEL,
					command_model_create[command_script[num].id_create_model].INDEX_TEXTURE,
					command_model_create[command_script[num].id_create_model].x,
					command_model_create[command_script[num].id_create_model].y,
					command_model_create[command_script[num].id_create_model].z);
				script_commands.push_back("create_model");
			}

			if (command_script[num].command_model == true)
			{
				if (command_model_commands[command_script[num].id_command_model].action == true)
				{
					CONSOLE.Set_model_command_data(
						command_model_commands[command_script[num].id_command_model].EXPRESSION_BOX,
						command_model_commands[command_script[num].id_command_model].EXPRESSION_BOX_ACTION,
						command_model_commands[command_script[num].id_command_model].num_idle,
						command_model_commands[command_script[num].id_command_model].num_action);
				}
				else
				{
					CONSOLE.Set_model_command_data(
						command_model_commands[command_script[num].id_command_model].EXPRESSION_BOX,
						command_model_commands[command_script[num].id_command_model].num_idle);
				}
				script_commands.push_back("command_model");
			}

			if (command_script[num].mus == true)
			{
				script_commands.push_back("music");
				CONSOLE.Set_music_data(command_music[command_script[num].id_mus]);
			}

			if (command_script[num].shake == true)
			{
				CONSOLE.Set_shake_data(command_shake[command_script[num].id_shake]);
				script_commands.push_back("shake");
			}

			if (command_script[num].scn == true)
			{
				string dir = command_swich_scene[command_script[num].id_scn];
				string swich = "None";
				if (dir == "S&H")
				{
					dir = command_swich_scene[command_script[num].id_scn + 1];
					swich = "S&H";
				}
				if (dir == "ALLBLACK")
				{
					dir = "None";
					swich = "ALLBLACK";
				}
				if (dir == "SHOWBOX")
				{
					dir = command_swich_scene[command_script[num].id_scn + 1];
					swich = "SHOWBOX";
				}
				if (dir == "HIDEBOX")
				{
					dir = command_swich_scene[command_script[num].id_scn + 1];
					swich = "HIDEBOX";
				}
				CONSOLE.Set_scene_data(dir, swich);
				script_commands.push_back("scene");
			}
			if (command_script[num].spr[0] == true || command_script[num].spr[1] == true || command_script[num].spr[2] == true) //проверка на вызов спрайтов
			{
				auto data = Get_Sprite(Game_Mode);
				if (command_script[num].scn == true)
				{
					int simplebox = 0;
					for (int n = 0; n < data.simple.size(); n++)
					if (data.simple[n] == true)
						simplebox++;
					if (data.simple.size() == simplebox)
					{
						script_commands.push_back("sprite_simple");
					}
					else
					{
						script_commands.push_back("sprite");
					}
				}
				else
				{
					script_commands.push_back("sprite");
				}
				CONSOLE.Set_sprite_data(data.sprite_box, data.simple);
			}

			if (command_script[num].sound == true)
			{
				CONSOLE.Set_sound_data(command_sound[command_script[num].id_sound]);
				script_commands.push_back("sound");
			}

			if (command_script[num].end == true)
				script_commands.push_back("return");
			else
			{
				CONSOLE.Set_voice_data(voice[num]);
				script_commands.push_back("voice");

				//if (command_script[num].voice_model == true)
				//{
				//	CONSOLE.Set_voicebox_model_data(command_voice_model[command_script[num].id_voice_model]);
				//	script_commands.push_back("voice_model");
				//}

				script_commands.push_back("text");
			}

			if (command_script[num].cloud == true)
			{
				CONSOLE.Set_cloud_data(command_cloud[command_script[num].id_cloud].arg, command_cloud[command_script[num].id_cloud].text, command_cloud[command_script[num].id_cloud].duration);
				skip = command_cloud[command_script[num].id_cloud].skip;
				script_commands.push_back("cloud");
			}

		}
		else
		{
			for (int n = 0; command_script[num].orders.size() > n; n++)
			{
				script_commands.push_back(command_script[num].orders[n]); // каждая команда копируется в вектор
				if (command_script[num].orders[n] == "sprite")
				{
					auto data = Get_Sprite(Game_Mode);
					CONSOLE.Set_sprite_data(data.sprite_box, data.simple);
				}

				//if (command_script[num].orders[n] == "model")
				//{
				//	CONSOLE.Set_model(command_model[command_script[num].id_model].current_model, command_model[command_script[num].id_model].motion, command_model[command_script[num].id_model].size_motion);
				//}
				if (command_script[num].orders[n] == "scene")
				{
					string dir = command_swich_scene[command_script[num].id_scn];
					string swich = "None";
					if (dir == "S&H")
					{
						dir = command_swich_scene[command_script[num].id_scn + 1];
						swich = "S&H";
					}
					if (dir == "ALLBLACK")
					{
						dir = "None";
						swich = "ALLBLACK";
					}
					if (dir == "SHOWBOX")
					{
						dir = command_swich_scene[command_script[num].id_scn + 1];
						swich = "SHOWBOX";
					}
					if (dir == "HIDEBOX")
					{
						dir = command_swich_scene[command_script[num].id_scn + 1];
						swich = "HIDEBOX";
					}
					CONSOLE.Set_scene_data(dir, swich);
				}
				if (command_script[num].orders[n] == "sound")
				{
					CONSOLE.Set_sound_data(command_sound[command_script[num].id_sound]);
				}

				if (command_script[num].orders[n] == "shake")
				{
					CONSOLE.Set_shake_data(command_shake[command_script[num].id_shake]);
				}

				if (command_script[num].orders[n] == "music")
				{
					CONSOLE.Set_music_data(command_music[command_script[num].id_mus]);
				}

			}

			CONSOLE.Set_voice_data(voice[num]);
			script_commands.push_back("voice");

			script_commands.push_back("text");

		}
		CONSOLE.Create_commands_script(script_commands);
		CONSOLE.view(Game_Mode);
	}
};


GAMEBOX GAME; // СОЗДАНИЕ ОБЪЕКТА ИГРОВОЙ ЛОГИКИ


class SWICHSCENE
{
private:
	string custom_swich = "None";
	string dir_scene;
public:

	void Set_Data(string scene)
	{
		this->dir_scene = scene;
		this->custom_swich = "None";
	}
	void Set_Data(string scene, string swich)
	{
		this->dir_scene = scene;
		this->custom_swich = swich;
	}
	void Get_scene(Sprite *swich_scene)
	{
		swich_scene->setTexture(dir_scene);
	}

	void Get_scene_complete(Sprite *scene)
	{
		scene->setTexture(dir_scene);
	}

	void swich(Node *Game_Mode, Sprite *scene, Sprite *swich_scene, bool reverse)
	{
		auto endaction = CallFunc::create([=]()
		{
			CONSOLE.Use_command_scene(Game_Mode);
		});




		if (reverse == false)
		{
			if (custom_swich == "None")
			{
				//scene->runAction(FadeOut::create(0.7f));
				swich_scene->runAction(Sequence::create(FadeIn::create(0.7f), DelayTime::create(0.7f), endaction, nullptr));
			}
			else if (custom_swich == "HIDE")
			{
				auto *Text_Box = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Text_Box"));
				Text_Box->runAction(Sequence::create(MoveBy::create(0.5, Vec2(0, -206)), DelayTime::create(0.5f), endaction, nullptr));
			}
			else if (custom_swich == "SHOW")
			{
				auto *Text_Box = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Text_Box"));
				Text_Box->runAction(Sequence::create(MoveBy::create(0.5, Vec2(0, 206)), DelayTime::create(0.5f), endaction, nullptr));
			}
			else if (custom_swich == "ALLBLACK")
			{
				auto *Black_screen = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Black_screen"));
				Black_screen->runAction(Sequence::create(FadeIn::create(0.7f), DelayTime::create(0.7f), endaction, nullptr));
			}
			
		}
		else
		{
			if (custom_swich == "None")
			{
				scene->setOpacity(255);
				swich_scene->setOpacity(0);
				CONSOLE.Use_command_scene(Game_Mode);
			}
			else if (custom_swich == "ALLBLACK")
			{
				auto *Black_screen = static_cast<cocos2d::Sprite*>(Game_Mode->getChildByName("Black_screen"));
				Black_screen->runAction(Sequence::create(FadeOut::create(0.7f), DelayTime::create(0.7f), endaction, nullptr));
			}
		}

	}

	void swich_with_sprite(Node *Game_Mode, Sprite *scene, Sprite *swich_scene, Node* box_sprite, Node* box_unsprite, Node* Box_scene, Node* Box_unscene, bool reverse)
	{
		if (reverse == false)
		{
			auto endaction = CallFunc::create([=]()
			{
				CONSOLE.Use_command_scene(Game_Mode);
			});

			Box_unscene->setOpacity(0);
			box_unsprite->setOpacity(255);
			swich_scene->setOpacity(255);

			Box_scene->runAction(FadeOut::create(0.7f));
			Box_unscene->runAction(Sequence::create(FadeIn::create(0.7f), DelayTime::create(0.7f), endaction, nullptr));
		}
		else
		{
			Box_scene->setOpacity(255);
			Box_unscene->setOpacity(0);
			box_unsprite->setOpacity(0);
			swich_scene->setOpacity(0);
			Box_unscene->setOpacity(255);
			CONSOLE.Use_command_scene(Game_Mode);
		}
	}
};

class SWICHSPRITE
{
private:
	vector<string> samples; // вектор пустышек текстур сэмплев
	Vec2 custom_position[4]; //кастомная позиция для увеличенных спрайтов
	vector<CallFunc*> blink;
public:

	SWICHSPRITE()
	{
		samples.push_back("Sprites\\Samples\\Sample_Sprite.png"); //[0]
		samples.push_back("Sprites\\Samples\\Sample_Blink.png"); // [1]
		samples.push_back("Sprites\\Samples\\Sample_Speak.png"); // [2]
		custom_position[0] = Vec2(NULL, NULL);
		custom_position[1] = Vec2(NULL, NULL);
		custom_position[2] = Vec2(NULL, NULL);
		custom_position[3] = Vec2(NULL, NULL);
		blink.push_back(CallFunc::create([](){}));
		blink.push_back(CallFunc::create([](){}));
		blink.push_back(CallFunc::create([](){}));
	}

	void Set_Custom_Position(Vec2 custom, int id)
	{
		this->custom_position[id] = custom;
	}

	//превызов спрайта на верхний слой
	void Get_Sprite(Node *Sprite_und, Node *Sprite_swich, int id, vector<Vec2> position, vector<string> texture, bool hide)
	{
		auto *Set_Sprite_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Sprite"));
		auto *Set_Blink_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Blink"));
		auto *Set_Speak_Swich = static_cast<cocos2d::Sprite*>(Sprite_swich->getChildByName("Speak"));

		if (hide == true)
		{
			if (samples.size() < 3)
				throw string("ERROR_MISSING_SAMPLES");
			Set_Sprite_Swich->setTexture(samples[0]);
			Set_Blink_Swich->setTexture(samples[1]);
			Set_Speak_Swich->setTexture(samples[2]);
		}
		else
		{
			if (position.size() < 4)
				throw string("ERROR_MISSING_POSITION");
			Set_Sprite_Swich->setPosition(position[0]);
			Set_Blink_Swich->setPosition(position[1]);
			Set_Speak_Swich->setPosition(position[2]);
			if (custom_position[id] != Vec2(NULL, NULL))
				Sprite_swich->setPosition(custom_position[id]);
			else
				Sprite_swich->setPosition(position[3]);

			if (texture.size() < 3)
				throw string("ERROR_MISSING_TEXTURE");
			Set_Sprite_Swich->setTexture(texture[0]);
			Set_Blink_Swich->setTexture(texture[1]);
			Set_Speak_Swich->setTexture(texture[2]);
			
		}
	} 

	//завершающий вызов спрайта на нижний слой
	void Get_sprite_complete(Node *Sprite_und, Node *Sprite_swich, int id, vector<Vec2> position, vector<string> texture, bool hide) //отчиски нет
	{
		auto *Set_Sprite = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Sprite"));
		auto *Set_Blink = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Blink"));
		auto *Set_Speak = static_cast<cocos2d::Sprite*>(Sprite_und->getChildByName("Speak"));
		Set_Blink->stopAllActions();

		if (hide == true)
		{
			if (samples.size() < 3)
				throw string("ERROR_MISSING_SAMPLES");
			Set_Sprite->setTexture(samples[0]);
			Set_Blink->setTexture(samples[1]);
			Set_Speak->setTexture(samples[2]);

		}
		else
		{
			if (position.size() < 4)
				throw string("ERROR_MISSING_POSITION");
			Set_Sprite->setPosition(position[0]);
			Set_Blink->setPosition(position[1]);
			Set_Speak->setPosition(position[2]);
			if (custom_position[id] != Vec2(NULL, NULL))
				Sprite_und->setPosition(custom_position[id]);
			else
				Sprite_und->setPosition(position[3]);


			if (texture.size() < 3)
				throw string("ERROR_MISSING_TEXTURE");
			Set_Sprite->setTexture(texture[0]);
			Set_Blink->setTexture(texture[1]);
			Set_Speak->setTexture(texture[2]);
			cocos2d::Vector<SpriteFrame*> BlinkFrame;
			BlinkFrame.pushBack(SpriteFrame::create(texture[3], Set_Blink->getTextureRect()));
			BlinkFrame.pushBack(SpriteFrame::create(texture[4], Set_Blink->getTextureRect()));
			BlinkFrame.pushBack(SpriteFrame::create(texture[3], Set_Blink->getTextureRect()));
			BlinkFrame.pushBack(SpriteFrame::create(texture[1], Set_Blink->getTextureRect()));

			auto delay ([]()->int{
				std::mt19937 mersenne(static_cast<unsigned int>(time(0)));
				return((mersenne() % 4) + 4);
			});
			
			auto twice([]()->int{
				std::mt19937 mersenne(static_cast<unsigned int>(time(0)));
				int z= ((mersenne() % 4) + 1);
				if (z == 4)
					return 2;
				else 
					return 1;
			});

			blink[id] = CallFunc::create([=]()
			{
				Set_Blink->runAction(Sequence::create(DelayTime::create(delay()), Repeat::create(Animate::create(Animation::createWithSpriteFrames(BlinkFrame, 0.05f)), twice()), blink[id], nullptr));
			});

			Set_Blink->runAction(blink[id]);
		}
	}

	// выполняет только обычный свич - для кастомного написать доп функцию //reverse завершает а тоесть выполняет обратные действия обычного свич
	void swich(Node *Game_Mode, Node *Sprite, Node *Sprite_swich, bool reverse)
	{
		auto endaction = CallFunc::create([=]()
		{
			CONSOLE.Use_command_sprite(Game_Mode);
		});


		if (reverse == false)
		{
			Sprite->runAction(FadeOut::create(0.7f));
			Sprite_swich->runAction(Sequence::create(FadeIn::create(0.7f), DelayTime::create(0.7f), endaction, nullptr));

		}
		else
		{
			Sprite->setOpacity(255);
			Sprite_swich->setOpacity(0);		
			CONSOLE.Use_command_sprite(Game_Mode);
		}


	} 

	void custom_swich(Node *Game_Mode, Node *Sprite, Node *Sprite_swich, string custom, bool hide)
	{

		auto endaction = CallFunc::create([=]()
		{
			CONSOLE.Use_command_sprite(Game_Mode);
		});

		float z = 0;
		int smeh_position = 50;

		if (custom == "LTR")
		{
			if (hide == false) //пропадает ли спарйт иначе - появляется и нужно сместить по координатам
			{
				Sprite_swich->setPosition(Sprite_swich->getPosition() - Vec2(smeh_position, 0));
				Sprite_swich->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(smeh_position, 0)), FadeIn::create(0.7f)), DelayTime::create(0.7f), endaction, nullptr));
				Sprite->runAction(FadeOut::create(0.7f));
			}
			else
			{
				Sprite_swich->runAction(FadeIn::create(0.7f));
				Sprite->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(smeh_position, 0)), FadeOut::create(0.7f)), DelayTime::create(0.7f), endaction, nullptr));
			}

		}
		else if (custom == "RTL")
		{
			if (hide == false)
			{
				Sprite_swich->setPosition(Sprite_swich->getPosition() + Vec2(smeh_position, 0));
				Sprite_swich->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(-smeh_position, 0)), FadeIn::create(0.7f)), DelayTime::create(0.7f), endaction, nullptr));
				Sprite->runAction(FadeOut::create(0.7f));
			}
			else
			{
				Sprite_swich->runAction(FadeIn::create(0.7f));
				Sprite->runAction(Sequence::create(Spawn::createWithTwoActions(MoveBy::create(0.7f, Vec2(smeh_position, 0)), FadeOut::create(0.7f)), DelayTime::create(0.7f), endaction, nullptr));
			}

		}
		else if (custom == "TTT")
		{
			Sprite_swich->runAction(Sequence::create(FadeIn::create(0.7f), DelayTime::create(0.7f), endaction, nullptr));
			Sprite->runAction(FadeOut::create(0.7f));
		}
		else
			throw ("ERROR_UNKNOWN_PREFIX_SWICH");
	}


	void Get_action(Node *Game_Mode, Node *Temp_Sprites, string current_action, vector<Vec2> position, int id, bool inf, bool old_sprite)
	{


		auto endaction = CallFunc::create([=]()
		{
			CONSOLE.Use_command_sprite(Game_Mode);
		});

		if (current_action == "MINIJUMP")
		{
			if (inf == false && old_sprite == false)
				throw string("ERROR_USING_MINIJUMP");
			Temp_Sprites->runAction(Sequence::create(MoveBy::create(0.15f, Vec2(0, 20)), DelayTime::create(0.15f), MoveBy::create(0.15f, Vec2(0, -20)), DelayTime::create(0.15f), endaction, nullptr));
		}
		else if (current_action == "JUMP")
		{
			if (inf == false && old_sprite == false)
				throw string("ERROR_USING_JUMP");
			Temp_Sprites->runAction(Sequence::create(MoveBy::create(0.07, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f), 
									MoveBy::create(0.07f, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f), endaction, nullptr));

		}
		else if (current_action == "DECREASE")
		{


			float time = 0.25;
			if (inf == false && old_sprite == false)
				time = 0;
			Temp_Sprites->setAnchorPoint(Vec2(0.5f, 0.5f));
			Temp_Sprites->setPosition(position[3] + (Vec2(256, 256)*1.7));

			auto preendaction = CallFunc::create([=]()
			{
				auto temppos = (Temp_Sprites->getPosition() - (Vec2(256, 256)*1.7));
				Temp_Sprites->setAnchorPoint(Vec2(0.0f, 0.0f));
				Temp_Sprites->setPosition(temppos);
				//Temp_Swich_Sprites->setScale(Temp_Sprites->getScale());
				custom_position[id] = Vec2(0, 0);
			});

			Temp_Sprites->runAction(Sequence::create(ScaleTo::create(time, 1.7f, 1.7f), DelayTime::create(time), preendaction, endaction, nullptr));

			
		}
		else if (current_action == "INCREASE") //осталась одна проблема получения координат следующими спрайтами (координат ноды) нужно вычисление нужных координат
		{


			float time = 0.25;
			if (inf == false && old_sprite == false)
				time = 0;

			Temp_Sprites->setAnchorPoint(Vec2(0.5f, 0.5f));
			Temp_Sprites->setPosition(position[3] + (Vec2(256, 256)*1.7));


			auto preendaction = CallFunc::create([=]()
			{
				auto temppos = (Temp_Sprites->getPosition() - (Vec2(256, 256)*2.1));
				Temp_Sprites->setAnchorPoint(Vec2(0.0f, 0.0f));
				Temp_Sprites->setPosition(temppos);
				//Temp_Swich_Sprites->setScale(Temp_Sprites->getScale());
				Set_Custom_Position(temppos, id);
				custom_position[id] = temppos;
			});

			Temp_Sprites->runAction(Sequence::create(ScaleTo::create(time, 2.1f, 2.1f), DelayTime::create(time), preendaction, endaction, nullptr));



			// нужно сохранить координаты для последующего использования их спрайтом
			 // и id
		}
		else if (current_action == "MINI_INCREASE") //осталась одна проблема получения координат следующими спрайтами (координат ноды) нужно вычисление нужных координат
		{
			float time = 0.25;
			if (inf == false && old_sprite == false)
				time = 0;

			Temp_Sprites->setAnchorPoint(Vec2(0.5f, 0.5f));
			Temp_Sprites->setPosition(position[3] + (Vec2(256, 256)*1.7));


			auto preendaction = CallFunc::create([=]()
			{
				auto temppos = (Temp_Sprites->getPosition() - (Vec2(256, 256)*1.9f));
				Temp_Sprites->setAnchorPoint(Vec2(0.0f, 0.0f));
				Temp_Sprites->setPosition(temppos);
				//Temp_Swich_Sprites->setScale(Temp_Sprites->getScale());
				Set_Custom_Position(temppos, id);
				custom_position[id] = temppos;
			});

			Temp_Sprites->runAction(Sequence::create(ScaleTo::create(time, 1.9f, 1.9f), DelayTime::create(time), preendaction, endaction, nullptr));


			// нужно сохранить координаты для последующего использования их спрайтом
			 // и id
		}
	}
	void Get_action(Node *Game_Mode, Node *Temp_Sprites, string current_action, int id, bool inf, bool old_sprite)
	{


		auto endaction = CallFunc::create([=]()
		{
			CONSOLE.Use_command_sprite(Game_Mode);
		});

		if (current_action == "MINIJUMP")
		{
			if (inf == false && old_sprite == false)
				throw string("ERROR_USING_MINIJUMP");
			Temp_Sprites->runAction(Sequence::create(MoveBy::create(0.15f, Vec2(0, 20)), DelayTime::create(0.15f), MoveBy::create(0.15f, Vec2(0, -20)), DelayTime::create(0.15f), endaction, nullptr));
		}
		else if (current_action == "JUMP")
		{
			if (inf == false && old_sprite == false)
				throw string("ERROR_USING_JUMP");
			Temp_Sprites->runAction(Sequence::create(MoveBy::create(0.07, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f),
				MoveBy::create(0.07f, Vec2(0, 20)), DelayTime::create(0.07f), MoveBy::create(0.07f, Vec2(0, -20)), DelayTime::create(0.07f), endaction, nullptr));

		}
		else if (current_action == "DECREASE")
		{


			float time = 0.25;
			if (inf == false && old_sprite == false)
				time = 0;
			Temp_Sprites->setAnchorPoint(Vec2(0.5f, 0.5f));
			Temp_Sprites->setPosition(Temp_Sprites->getPosition() + (Vec2(256, 256)*1.7));

			auto preendaction = CallFunc::create([=]()
			{
				auto temppos = (Temp_Sprites->getPosition() - (Vec2(256, 256)*1.7));
				Temp_Sprites->setAnchorPoint(Vec2(0.0f, 0.0f));
				Temp_Sprites->setPosition(temppos);
				//Temp_Swich_Sprites->setScale(Temp_Sprites->getScale());
				custom_position[id] = Vec2(0, 0);
			});

			Temp_Sprites->runAction(Sequence::create(ScaleTo::create(time, 1.7f, 1.7f), DelayTime::create(time), preendaction, endaction, nullptr));


		}
		else if (current_action == "INCREASE") //осталась одна проблема получения координат следующими спрайтами (координат ноды) нужно вычисление нужных координат
		{


			float time = 0.25;
			if (inf == false && old_sprite == false)
				time = 0;

			Temp_Sprites->setAnchorPoint(Vec2(0.5f, 0.5f));
			Temp_Sprites->setPosition(Temp_Sprites->getPosition() + (Vec2(256, 256)*1.7));


			auto preendaction = CallFunc::create([=]()
			{
				auto temppos = (Temp_Sprites->getPosition() - (Vec2(256, 256)*2.1));
				Temp_Sprites->setAnchorPoint(Vec2(0.0f, 0.0f));
				Temp_Sprites->setPosition(temppos);
				//Temp_Swich_Sprites->setScale(Temp_Sprites->getScale());
				Set_Custom_Position(temppos, id);
				custom_position[id] = temppos;
			});

			Temp_Sprites->runAction(Sequence::create(ScaleTo::create(time, 2.1f, 2.1f), DelayTime::create(time), preendaction, endaction, nullptr));



			// нужно сохранить координаты для последующего использования их спрайтом
			// и id
		}
		else if (current_action == "MINI_INCREASE") //осталась одна проблема получения координат следующими спрайтами (координат ноды) нужно вычисление нужных координат
		{
			float time = 0.25;
			if (inf == false && old_sprite == false)
				time = 0;

			Temp_Sprites->setAnchorPoint(Vec2(0.5f, 0.5f));
			Temp_Sprites->setPosition(Temp_Sprites->getPosition() + (Vec2(256, 256)*1.7));


			auto preendaction = CallFunc::create([=]()
			{
				auto temppos = (Temp_Sprites->getPosition() - (Vec2(256, 256)*1.9f));
				Temp_Sprites->setAnchorPoint(Vec2(0.0f, 0.0f));
				Temp_Sprites->setPosition(temppos);
				//Temp_Swich_Sprites->setScale(Temp_Sprites->getScale());
				Set_Custom_Position(temppos, id);
				custom_position[id] = temppos;
			});

			Temp_Sprites->runAction(Sequence::create(ScaleTo::create(time, 1.9f, 1.9f), DelayTime::create(time), preendaction, endaction, nullptr));


			// нужно сохранить координаты для последующего использования их спрайтом
			// и id
		}
	}

};



SWICHSPRITE SWICHSPRITEBOX;
SWICHSCENE SWICHSCENEBOX; 

void VIEWERCONSOLE::Set_cloud_data(int arg, string text, float duration)
{
	this->arg_cloud = arg;
	this->text_cloud = text;
	this->duration_cloud = duration;
}

void VIEWERCONSOLE::Set_sprite_data(vector <SPRITEBOX> temp_sprites, vector <bool> temp_simple_sprite)
{
	this->sprites.clear();
	this->sprites.assign(temp_sprites.begin(), temp_sprites.end());
	simple_sprite.clear();
	simple_sprite.assign(temp_simple_sprite.begin(), temp_simple_sprite.end());
}

void VIEWERCONSOLE::Create_commands_sprite(Node *Game_Mode) // при свиче идет вызов анимаций - менять систему
{
	if (sprites.size() < 1)
		throw string("ERROR_MISSING_SPRITES");
	if (sprites.size() != simple_sprite.size())
		throw string("ERROR_MISSING_SIMPLE_DATA");
	bool custom_swich = false;
	bool ingore_swich = false;
	bool ignore_sprite = false;
	bool action_sprite = false;
	sprite_commands.clear(); // отчищается все что было
	num_sprite_commands = NULL; // номер команды возвращается в ноль



	for (int n = 0; n < sprites.size(); n++) // идет появления спрайта на слое для свича
	{
		if (sprites[n].Get_swich() != "None")//идет проверка на кастомные свичи спрайтов
			custom_swich = true;//если хоть один кастомный
		if (sprites[n].Get_action() != "None") // проверка каждого спрайта на действие, поддерживается всего одно действие
		{
			action_sprite = true;
			sprite_commands.push_back("action_sprite");

			stringstream temp;
			temp << n;
			string s_temp;
			temp >> s_temp;

			sprite_commands.push_back(s_temp);

		}
		if (simple_sprite[n] == true) //проверка на простую смену лица
		{
			ingore_swich = true;
		}
		if (sprites[n].Check_inf() == false && sprites[n].Get_hide() == false)
		{
			ignore_sprite = true;
		}
	}
	if (ingore_swich == false && ignore_sprite == false)
	{
		if (custom_swich == true)// идет проверка кастомный ли свич 
		{//тут каждый спрайт появляется отдельно друг от друга
			for (int n = 0; n < sprites.size(); n++)
			{
				sprite_commands.push_back("custom_swich");

				stringstream temp;
				temp << n;
				string s_temp;
				temp >> s_temp;

				sprite_commands.push_back(s_temp);
				sprite_commands.push_back("custom_complete_sprite");
			}

		}
		else
		{// тут создаются ноды для обычного свича и свичатся спрайты
			sprite_commands.push_back("simple_swich");
			sprite_commands.push_back("complete_sprite");
		}
	}
	else
	{
		if (action_sprite == true)
			sprite_commands.insert(sprite_commands.begin(), "ignore_swich");
		else
			sprite_commands.push_back("ignore_swich");


		if (ignore_sprite == false)
			sprite_commands.push_back("simple_complete_sprite");
	}

	sprite_commands.push_back("end");
}

void VIEWERCONSOLE::Use_command_sprite(Node *Game_Mode)
{
	Node *Box_scene = Game_Mode->getChildByName("Box_scene");
	Node *Box_unscene = Game_Mode->getChildByName("Box_unscene");
	sprite_node = Box_scene->getChildByName("sprite_node");

	auto use_action([=](Node *Sprite, int n)
	{
		bool old_sprite = false;
		if (GAME.Old_Sprite(sprites[n].Get_id() - 1) == true)
			old_sprite = true;
		

		if (sprites[n].Check_inf() == true)
			SWICHSPRITEBOX.Get_action(Game_Mode, Sprite, sprites[n].Get_action(), sprites[n].Get_position(), sprites[n].Get_id(), sprites[n].Check_inf(), old_sprite);
		else
			SWICHSPRITEBOX.Get_action(Game_Mode, Sprite, sprites[n].Get_action(), sprites[n].Get_id(), sprites[n].Check_inf(), old_sprite);
	});

	if (sprite_commands[num_sprite_commands] == "action_sprite")
	{
			stringstream temp;
			temp << sprite_commands[num_sprite_commands + 1];
			int n;
			temp >> n;
			switch (sprites[n].Get_id())
			{
			case 1:
				Sprite_und = sprite_node->getChildByName("Sprite_1");
				break;
			case 2:
				Sprite_und = sprite_node->getChildByName("Sprite_2");
				break;
			case 3:
				Sprite_und = sprite_node->getChildByName("Sprite_3");
				break;
			}
			num_sprite_commands++;
			num_sprite_commands++;
			use_action(Sprite_und, n);
	}
	else if (sprite_commands[num_sprite_commands] == "get_sprite_swich")
	{
		sprite_node = Box_scene->getChildByName("sprite_node");
		sprite_swich_node = Node::create();
		sprite_swich_node->setOpacity(0); //установка свич ноды прозрачность на ноль
		sprite_swich_node->setCascadeOpacityEnabled(true); // надстройка передачи всем дочерним объектам прозрачности
		Box_unscene->addChild(sprite_swich_node); // помещаются ноды как дети в нужные ноды 
		(Box_unscene->getChildByName("sprite_swich_node"))->removeFromParent();
		sprite_swich_node->setName("sprite_swich_node");

		for (int n = 0; n < sprites.size(); n++) // идет создание нод для спайтов которые свичатся
		{
			switch (sprites[n].Get_id())
			{
			case 1:
				Sprite_swich = CSLoader::createNode("All_Scene_cocos\\Game_Scene\\Sprite\\Sprite_1_switch.csb");
				Sprite_und = sprite_node->getChildByName("Sprite_1");
				Sprite_swich->setName("Sprite_1_switch");
				break;
			case 2:
				Sprite_swich = CSLoader::createNode("All_Scene_cocos\\Game_Scene\\Sprite\\Sprite_2_switch.csb");
				Sprite_und = sprite_node->getChildByName("Sprite_2");
				Sprite_swich->setName("Sprite_2_switch");
				break;
			case 3:
				Sprite_swich = CSLoader::createNode("All_Scene_cocos\\Game_Scene\\Sprite\\Sprite_3_switch.csb");
				Sprite_und = sprite_node->getChildByName("Sprite_3");
				Sprite_swich->setName("Sprite_3_switch");
				break;
			}
			Sprite_swich->setScale(Sprite_und->getScale());
			sprite_swich_node->addChild(Sprite_swich);
			SWICHSPRITEBOX.Get_Sprite(Sprite_und, Sprite_swich, sprites[n].Get_id(), sprites[n].Get_position(), sprites[n].Get_texture(), sprites[n].Get_hide()); // работает				
		}
		num_sprite_commands++;
		Use_command_sprite(Game_Mode);
	}
	else if (sprite_commands[num_sprite_commands] == "simple_swich")
	{
		sprite_node = Box_scene->getChildByName("sprite_node");
		sprite_swich_node = Node::create();
		sprite_swich_node->setOpacity(0); //установка свич ноды прозрачность на ноль
		sprite_swich_node->setCascadeOpacityEnabled(true); // надстройка передачи всем дочерним объектам прозрачности
		Box_unscene->addChild(sprite_swich_node); // помещаются ноды как дети в нужные ноды 
		(Box_unscene->getChildByName("sprite_swich_node"))->removeFromParent();
		sprite_swich_node->setName("sprite_swich_node");

		for (int n = 0; n < sprites.size(); n++) // идет создание нод для спайтов которые свичатся
		{
			switch (sprites[n].Get_id())
			{
			case 1:
				Sprite_swich = CSLoader::createNode("All_Scene_cocos\\Game_Scene\\Sprite\\Sprite_1_switch.csb");
				Sprite_und = sprite_node->getChildByName("Sprite_1");
				Sprite_swich->setName("Sprite_1_switch");
				break;
			case 2:
				Sprite_swich = CSLoader::createNode("All_Scene_cocos\\Game_Scene\\Sprite\\Sprite_2_switch.csb");
				Sprite_und = sprite_node->getChildByName("Sprite_2");
				Sprite_swich->setName("Sprite_2_switch");
				break;
			case 3:
				Sprite_swich = CSLoader::createNode("All_Scene_cocos\\Game_Scene\\Sprite\\Sprite_3_switch.csb");
				Sprite_und = sprite_node->getChildByName("Sprite_3");
				Sprite_swich->setName("Sprite_3_switch");
				break;
			}
			Sprite_swich->setScale(Sprite_und->getScale());
			sprite_swich_node->addChild(Sprite_swich);
			SWICHSPRITEBOX.Get_Sprite(Sprite_und, Sprite_swich, sprites[n].Get_id(), sprites[n].Get_position(), sprites[n].Get_texture(), sprites[n].Get_hide()); // работает				
		}
		SWICHSPRITEBOX.swich(Game_Mode, sprite_node, sprite_swich_node, false); // свичет !!! все сразу
		num_sprite_commands++;
	}
	else if (sprite_commands[num_sprite_commands] == "custom_swich")
	{

		num_sprite_commands++; // переход на следующую команду указывает спрайт который выполняет действие
		stringstream temp;
		temp << sprite_commands[num_sprite_commands];
		int n;
		temp >> n;

		sprite_node = Box_scene->getChildByName("sprite_node");
		sprite_swich_node = Node::create();
		sprite_swich_node->setOpacity(255); //установка свич ноды прозрачность на ноль
		sprite_swich_node->setCascadeOpacityEnabled(false); // надстройка передачи всем дочерним объектам прозрачности
		Box_unscene->addChild(sprite_swich_node); // помещаются ноды как дети в нужные ноды 
		(Box_unscene->getChildByName("sprite_swich_node"))->removeFromParent();
		sprite_swich_node->setName("sprite_swich_node");
		switch (sprites[n].Get_id())
		{
		case 1:
			Sprite_swich = CSLoader::createNode("All_Scene_cocos\\Game_Scene\\Sprite\\Sprite_1_switch.csb");
			Sprite_und = sprite_node->getChildByName("Sprite_1");
			Sprite_swich->setName("Sprite_1_switch");
			break;
		case 2:
			Sprite_swich = CSLoader::createNode("All_Scene_cocos\\Game_Scene\\Sprite\\Sprite_2_switch.csb");
			Sprite_und = sprite_node->getChildByName("Sprite_2");
			Sprite_swich->setName("Sprite_2_switch");
			break;
		case 3:
			Sprite_swich = CSLoader::createNode("All_Scene_cocos\\Game_Scene\\Sprite\\Sprite_3_switch.csb");
			Sprite_und = sprite_node->getChildByName("Sprite_3");
			Sprite_swich->setName("Sprite_3_switch");
			break;
		}
		Sprite_swich->setScale(Sprite_und->getScale());
		Sprite_swich->setOpacity(0);
		sprite_swich_node->addChild(Sprite_swich);
		SWICHSPRITEBOX.Get_Sprite(Sprite_und, Sprite_swich, sprites[n].Get_id(), sprites[n].Get_position(), sprites[n].Get_texture(), sprites[n].Get_hide());
		num_sprite_commands++;
		SWICHSPRITEBOX.custom_swich(Game_Mode, Sprite_und, Sprite_swich, sprites[n].Get_swich(), sprites[n].Get_hide()); // свич по очереди

	}
	else if (sprite_commands[num_sprite_commands] == "ignore_swich")
	{
		num_sprite_commands++;
		Use_command_sprite(Game_Mode);
	}
	else if (sprite_commands[num_sprite_commands] == "complete_sprite")
	{

		for (int n = 0; n < sprites.size(); n++)
		{
			switch (sprites[n].Get_id())
			{
			case 1:
				Sprite_und = sprite_node->getChildByName("Sprite_1");
				Sprite_swich = sprite_swich_node->getChildByName("Sprite_1_switch");
				break;
			case 2:
				Sprite_und = sprite_node->getChildByName("Sprite_2");
				Sprite_swich = sprite_swich_node->getChildByName("Sprite_2_switch");
				break;
			case 3:
				Sprite_und = sprite_node->getChildByName("Sprite_3");
				Sprite_swich = sprite_swich_node->getChildByName("Sprite_3_switch");
				break;
			}
			SWICHSPRITEBOX.Get_sprite_complete(Sprite_und, Sprite_swich, sprites[n].Get_id(), sprites[n].Get_position(), sprites[n].Get_texture(), sprites[n].Get_hide()); // идет появления спрайта на основном слое	
		}
		num_sprite_commands++;
		SWICHSPRITEBOX.swich(Game_Mode, sprite_node, sprite_swich_node, true); //возвращает состояние слоев в норму после свича
	}
	else if (sprite_commands[num_sprite_commands] == "custom_complete_sprite")
	{
		stringstream temp;
		temp << sprite_commands[num_sprite_commands - 1];
		int n;
		temp >> n;

		switch (sprites[n].Get_id())
		{
		case 1:
			Sprite_und = sprite_node->getChildByName("Sprite_1");
			Sprite_swich = sprite_swich_node->getChildByName("Sprite_1_switch");
			break;
		case 2:
			Sprite_und = sprite_node->getChildByName("Sprite_2");
			Sprite_swich = sprite_swich_node->getChildByName("Sprite_2_switch");
			break;
		case 3:
			Sprite_und = sprite_node->getChildByName("Sprite_3");
			Sprite_swich = sprite_swich_node->getChildByName("Sprite_3_switch");
			break;
		}
		SWICHSPRITEBOX.Get_sprite_complete(Sprite_und, Sprite_swich, sprites[n].Get_id(), sprites[n].Get_position(), sprites[n].Get_texture(), sprites[n].Get_hide()); // идет появления спрайта на основном слое	
		num_sprite_commands++;
		SWICHSPRITEBOX.swich(Game_Mode, Sprite_und, Sprite_swich, true); //возвращает состояние слоев в норму после свича

	}
	else if (sprite_commands[num_sprite_commands] == "simple_complete_sprite")
	{
		for (int n = 0; n < sprites.size(); n++)
		{
			switch (sprites[n].Get_id())
			{
			case 1:
				Sprite_und = sprite_node->getChildByName("Sprite_1");
				break;
			case 2:
				Sprite_und = sprite_node->getChildByName("Sprite_2");
				break;
			case 3:
				Sprite_und = sprite_node->getChildByName("Sprite_3");
				break;
			}
			SWICHSPRITEBOX.Get_sprite_complete(Sprite_und, Sprite_swich, sprites[n].Get_id(), sprites[n].Get_position(), sprites[n].Get_texture(), sprites[n].Get_hide()); // идет появления спрайта на основном слое	
		}
		num_sprite_commands++;
		Use_command_sprite(Game_Mode);
	}
	else if (sprite_commands[num_sprite_commands] == "return_scene")
	{
		num_sprite_commands++;
		Use_command_scene(Game_Mode);
	}
	else if (sprite_commands[num_sprite_commands] == "end")
	{
		if (return_scene == false)
		{
			view(Game_Mode);
		}
		else
		{
			return_scene = false;
			Use_command_scene(Game_Mode);
		}
	}
	else
	{
		throw string("ERROR_UNKNOWN_SPRITE_COMMAND");
	}
	// // всегда по завершению вызова 
}

void VIEWERCONSOLE::Set_scene_data(string dir, string swich)
{
	this->dir_scene = dir;
	this->custom_swich_scene = swich;
}

void VIEWERCONSOLE::Get_cloud(Node* Game_Mode)
{
	auto *set_text = static_cast<cocos2d::ui::Text*>(Game_Mode->getChildByName("Set_text")); // элемент текста в игровом меню
	auto *set_name = static_cast<cocos2d::ui::Text*>(Game_Mode->getChildByName("Set_name")); // элемент имени в игровом меню
	auto *Button_click = static_cast<cocos2d::ui::Button*>(Game_Mode->getChildByName("Button_click"));

	auto Cloud_Node = Game_Mode->getChildByName("Cloud_Node");
	auto No_arg_cloud = static_cast<Sprite*>(Cloud_Node->getChildByName("No_arg"));
	auto Arg_cloud = static_cast<Sprite*>(Cloud_Node->getChildByName("Agr"));
	auto Text_cloud = static_cast<ui::Text*> (Cloud_Node->getChildByName("Text"));
	auto Box_scene = Game_Mode->getChildByName("Box_scene");

	auto decrease = ([=]()
	{
		Box_scene->stopAllActions();
		//Box_scene->getChildByName("Set_scene")->runAction(Spawn::create(MoveBy::create(0.3, Vec3(0, 50, -100)), CallFunc::create([=](){current_model->Decrease_Model(); }), nullptr));
	});

	auto Use_cloud = CallFunc::create([=]()
	{	
		Button_click->addClickEventListener([=](Ref *)
		{
			Button_click->setVisible(false);
			Game_Mode->stopAllActions();
			Cloud_Node->stopAllActions();
			//if (current_model != 0)
			//	current_model->Stop_sp_model();
			cocos2d::experimental::AudioEngine::stop(Game_id);
			Game_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[14], false, All_Volume*Voice_Volume); // при скрытых подсказках
			//Game_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[26], false, All_Volume*Voice_Volume);
			decrease();
			Cloud_Node->runAction(Sequence::create(FadeOut::create(0.5), DelayTime::create(0.5), CallFunc::create([=](){
				Cloud_Node->setPosition(Vec2(1850, 35));
				Cloud_Node->setOpacity(255);
				set_text->setString("");
				set_name->setString("");
				CONSOLE.Star(Game_Mode, false);
				GAME.Next_num();
				GAME.Get_Script(Game_Mode); 
			}), nullptr));
		});
	Button_click->setVisible(true);
	});

	auto End_cloud = CallFunc::create([=]()
	{
		Button_click->setVisible(false);
		cocos2d::experimental::AudioEngine::stop(Game_id);
		//if (current_model != 0)
		//	current_model->Stop_sp_model();
		cocos2d::experimental::AudioEngine::stop(Game_id);
		Game_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[13], false, All_Volume*Voice_Volume); // при скрытых подсказках
		decrease();
		Cloud_Node->runAction(Sequence::create(MoveBy::create(0.5, Vec2(-800, 0)), DelayTime::create(0.5), CallFunc::create([=](){
			//Game_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[27], false, All_Volume*Voice_Volume); //при включенных подсказках
			set_text->setString("");
			set_name->setString("");
			CONSOLE.Star(Game_Mode, false);
			GAME.Get_Skip();
			Cloud_Node->setPosition(Vec2(1850, 35));
			Cloud_Node->setOpacity(255);
			GAME.Get_Script(Game_Mode);
		}), nullptr));
	});

	auto Vuuu = CallFunc::create([=]()
	{
		cocos2d::experimental::AudioEngine::stop(Game_id);
		Game_id = cocos2d::experimental::AudioEngine::play2d(setsystemse[12], false, All_Volume*Voice_Volume); // выезжает звук облака
//		Box_scene->getChildByName("Set_scene")->runAction(Spawn::create(MoveBy::create(0.3, Vec3(0, -50, 100)), CallFunc::create([=](){current_model->Increase_Model(); }), nullptr)); // increase scene
		//Game_Mode->getChildByName("Box_scene")->setAnchorPoint(Vec2(0.5f, 0.5f));
		//current_model->runAction(Sequence::create(MoveBy::create(0.5, Vec3(-0, -100, 100)), nullptr));
		//Game_Mode->getChildByName("Box_scene")->setPosition(-Vec2(200, 200));
	});


	if (arg_cloud == 0)
	{
		No_arg_cloud->setVisible(true);
		Arg_cloud->setVisible(false);
	}
	else
	{
		No_arg_cloud->setVisible(false);
		Arg_cloud->setVisible(true);
	}
	Text_cloud->setString(text_cloud);
	


	Cloud_Node->runAction(Sequence::create(	DelayTime::create(duration_cloud / 2), 
											MoveBy::create(0.5, Vec2(-800, 0)), 
											MoveBy::create(duration_cloud / 2, Vec2(-100, 0)), 
											nullptr));

	Game_Mode->runAction(Sequence::create(	DelayTime::create(duration_cloud / 2), 
											Vuuu, 
											DelayTime::create(0.5), 
											Use_cloud, 
											DelayTime::create(duration_cloud / 2), End_cloud, nullptr));
}

void VIEWERCONSOLE::Create_commands_scene(Node *Game_Mode)
{
	scene_commands.clear();
	num_scene_commands = NULL;
	if (custom_swich_scene == "None")
	{
		scene_commands.push_back("Set_data");
		scene_commands.push_back("Get_scene");
		if (script_commands[num_script_commands] == "sprite_simple")
		{
			Create_commands_sprite(Game_Mode);
			for (int n = 0; n < sprite_commands.size(); n++)
			{
				if (sprite_commands[n] == "ignore_swich")
				{
					scene_commands.push_back("Get_sprite");
					sprite_commands[n] = "get_sprite_swich";
					sprite_commands.insert(sprite_commands.begin() + n + 1, "return_scene");
					break;
				}
			}
			scene_commands.push_back("swich_scene_with_sprite");	
		}
		else
			scene_commands.push_back("Swich_scene");
		scene_commands.push_back("Get_complete_scene");

		if (script_commands[num_script_commands] == "sprite_simple")
		{
			scene_commands.push_back("Get_sprite");
			script_commands.erase(script_commands.begin() + num_script_commands);
			scene_commands.push_back("Reverse_swich_scene_with_sprite");
		}
		else
			scene_commands.push_back("Reverse_swich_scene");
		scene_commands.push_back("end");
	}
	else if (custom_swich_scene == "ALLBLACK")
	{
		scene_commands.push_back("ALLBLACK");
		if (script_commands[num_script_commands] == "sprite_simple")
		{
			Create_commands_sprite(Game_Mode);
			scene_commands.push_back("Get_sprite");
			script_commands.erase(script_commands.begin() + num_script_commands);
		}
		scene_commands.push_back("Reverse_swich_scene");
		if (dir_scene != "None") // если в ALLBLACK сменяется сцена можно будет потом дописать получение данных из блока, и записовать команду смена сцены тут
		{
			scene_commands.push_back("Get_complete_scene");
		}
		scene_commands.push_back("end");
	}
	else if (custom_swich_scene == "S&H") // для спрайтов не работает дописать
	{
		scene_commands.push_back("HIDE_TEXTBOX");
		scene_commands.push_back("Set_data");
		scene_commands.push_back("Get_scene");
		scene_commands.push_back("Swich_scene");
		scene_commands.push_back("SHOW_TEXTBOX");
		scene_commands.push_back("Set_data");
		scene_commands.push_back("Get_complete_scene");
		scene_commands.push_back("Reverse_swich_scene");
		scene_commands.push_back("end");
	}
	else if (custom_swich_scene == "HIDEBOX")
	{
		scene_commands.push_back("HIDE_TEXTBOX");
		scene_commands.push_back("Set_data");
		scene_commands.push_back("Get_scene");
		scene_commands.push_back("Swich_scene");
		scene_commands.push_back("Get_complete_scene");
		scene_commands.push_back("Reverse_swich_scene");
		scene_commands.push_back("end");
	}
	else if (custom_swich_scene == "SHOWBOX")
	{
		scene_commands.push_back("SHOW_TEXTBOX");
		scene_commands.push_back("Set_data");
		scene_commands.push_back("Get_scene");
		scene_commands.push_back("Swich_scene");
		scene_commands.push_back("Get_complete_scene");
		scene_commands.push_back("Reverse_swich_scene");
		scene_commands.push_back("end");
	}
}

void VIEWERCONSOLE::Use_command_scene(Node *Game_Mode)
{
	Node *Box_scene = Game_Mode->getChildByName("Box_scene");
	Node *Box_unscene = Game_Mode->getChildByName("Box_unscene");
	auto Set_scene = static_cast<Sprite*>(Box_scene->getChildByName("Set_scene"));
	auto Set_unscene = static_cast<Sprite*>(Box_unscene->getChildByName("Set_unscene"));
	if (scene_commands[num_scene_commands] == "Set_data")
	{
		num_scene_commands++;
		SWICHSCENEBOX.Set_Data(this->dir_scene);
		Use_command_scene(Game_Mode);
	}
	else if (scene_commands[num_scene_commands] == "Get_scene")
	{
		num_scene_commands++;
		SWICHSCENEBOX.Get_scene(Set_unscene);
		Use_command_scene(Game_Mode);
	}
	else if (scene_commands[num_scene_commands] == "Get_complete_scene")
	{
		num_scene_commands++;
		SWICHSCENEBOX.Get_scene_complete(Set_scene);
		Use_command_scene(Game_Mode);
	}
	else if (scene_commands[num_scene_commands] == "HIDE_TEXTBOX")
	{
		num_scene_commands++;
		SWICHSCENEBOX.Set_Data("None", "HIDE");
		SWICHSCENEBOX.swich(Game_Mode, Set_scene, Set_unscene, false);
	}
	else if (scene_commands[num_scene_commands] == "SHOW_TEXTBOX")
	{
		num_scene_commands++;
		SWICHSCENEBOX.Set_Data("None", "SHOW");
		SWICHSCENEBOX.swich(Game_Mode, Set_scene, Set_unscene, false);
	}
	else if (scene_commands[num_scene_commands] == "ALLBLACK")
	{
		num_scene_commands++;
		SWICHSCENEBOX.Set_Data("None", "ALLBLACK");
		SWICHSCENEBOX.swich(Game_Mode, Set_scene, Set_unscene, false);
	}
	else if (scene_commands[num_scene_commands] == "Swich_scene")
	{
		num_scene_commands++;
		SWICHSCENEBOX.swich(Game_Mode, Set_scene, Set_unscene, false);
		
	}
	else if (scene_commands[num_scene_commands] == "Reverse_swich_scene")
	{
		num_scene_commands++;
		SWICHSCENEBOX.swich(Game_Mode, Set_scene, Set_unscene, true);		
	}
	else if (scene_commands[num_scene_commands] == "Get_sprite")
	{
		num_scene_commands++;
		return_scene = true;
		Use_command_sprite(Game_Mode);
	}
	else if (scene_commands[num_scene_commands] == "swich_scene_with_sprite")
	{
		num_scene_commands++;
		SWICHSCENEBOX.swich_with_sprite(Game_Mode, Set_scene, Set_unscene, sprite_node, sprite_swich_node, Box_scene, Box_unscene, false);
	}
	else if (scene_commands[num_scene_commands] == "Reverse_swich_scene_with_sprite")
	{
		num_scene_commands++;
		SWICHSCENEBOX.swich_with_sprite(Game_Mode, Set_scene, Set_unscene, sprite_node, sprite_swich_node, Box_scene, Box_unscene, true);
	}
	else if (scene_commands[num_scene_commands] == "end")
	{
		view(Game_Mode);
	}
	else
	{
		throw string("ERROR_UNKNOWN_SCENE_COMMAND");
	}

		
}

void VIEWERCONSOLE::Create_commands_script(vector<string> commands) // копирует вектор команд для их последующего вызова
	{
		script_commands.clear();
		num_script_commands = NULL;
		script_commands.assign(commands.begin(), commands.end());
	}

void VIEWERCONSOLE::Set_music_data(string dir)
{
	this->dir_music = dir;
}

void VIEWERCONSOLE::Set_voice_data(string dir)
{
	this->dir_voice = dir;
}

void VIEWERCONSOLE::Set_sound_data(string dir)
{
	this->dir_sound = dir;
}

void VIEWERCONSOLE::Set_shake_data(string effect)
{
	this->shake_effect = effect;
}

void VIEWERCONSOLE::Star(Node *Game_Mode, bool Get_star)
{
	Sprite *Star_sprite = static_cast<Sprite*>(Game_Mode->getChildByName("Star"));
	if (Get_star == true)
	{
		cocostudio::timeline::ActionTimeline *AllTime = CSLoader::createTimeline("All_Scene_cocos\\Game_Scene\\Game_Menu.csb");
		AllTime->setTimeSpeed(1.0f);
		AllTime->gotoFrameAndPlay(0);	
		Star_sprite->runAction(AllTime);
		Star_sprite->setVisible(true);
	}
	else
	{
		Star_sprite->setVisible(false);
		Star_sprite->stopAllActions();
	}
}



void VIEWERCONSOLE::Use_shake(Node *Game_Mode)
{
	float speed = 0.03;
	auto shake_simple([=](Node *scene) // просто трясет то что нужно потрясти
	{
		scene->runAction(Sequence::create(
			MoveBy::create(speed, Vec2(206, 100)), DelayTime::create(speed),
			MoveBy::create(speed, Vec2(-206, -100)), DelayTime::create(speed),
			MoveBy::create(speed, Vec2(-206, -100)), DelayTime::create(speed),
			MoveBy::create(speed, Vec2(206, 100)), DelayTime::create(speed),
			MoveBy::create(speed, Vec2(106, 100)), DelayTime::create(speed),
			MoveBy::create(speed, Vec2(-106, -100)), DelayTime::create(speed),
			 nullptr));
	});

	auto shake_punch([=](Node *scene) // просто трясет то что нужно потрясти
	{
		auto White_screen =Game_Mode->getChildByName("White_screen");
		White_screen->runAction(Sequence::create(FadeIn::create(0.05f), DelayTime::create(0.05f), FadeOut::create(0.05f), nullptr));
		scene->runAction(Sequence::create(
			DelayTime::create(0.2f),
			MoveBy::create(speed, Vec2(0, 150)), DelayTime::create(speed),
			MoveBy::create(speed, Vec2(0, -150)), DelayTime::create(speed),
			MoveBy::create(speed, Vec2(0, 100)), DelayTime::create(speed),
			MoveBy::create(speed, Vec2(0, -100)), DelayTime::create(speed),
			MoveBy::create(speed, Vec2(0, 50)), DelayTime::create(speed),
			MoveBy::create(speed, Vec2(0, -50)), DelayTime::create(speed),
			 nullptr));
	});

	if (shake_effect == "1") // трясется экран во все стороны
	{
		auto scene = Game_Mode->getChildByName("Box_scene");
		scene = scene->getChildByName("Set_scene");
		shake_simple(scene);

	}
	else if (shake_effect == "2") // трясется только текстбокс
	{
		auto textbox = Game_Mode->getChildByName("Text_Box");
		shake_simple(textbox);
	}
	else if (shake_effect == "3") // вверх вниз + белая вспышка
	{
		auto scene = Game_Mode->getChildByName("Box_scene");
		shake_punch(scene);
	}
}


void VIEWERCONSOLE::Set_model_create_data(int index_model, int index_texture, float x, float y, float z)
{
	this->INDEX_MODEL = index_model;
	this->INDEX_TEXTURE = index_texture;
	this->coordinata_model[0] = x;
	this->coordinata_model[1] = y;
	this->coordinata_model[2] = z;
}

void VIEWERCONSOLE::Set_model_command_data(vector<string> expression_command, int temp_num_idle)
{
	EXPRESSION_BOX.clear();
	this->EXPRESSION_BOX.assign(expression_command.begin(), expression_command.end());
	this->num_idle = temp_num_idle;
	this->action_model = false;
}

void VIEWERCONSOLE::Set_model_command_data(vector<string> expression_command, vector<string> expression_action_command, int temp_num_idle, int temp_num_action)
{
	EXPRESSION_BOX.clear();
	EXPRESSION_ACTION_BOX.clear();
	this->EXPRESSION_BOX.assign(expression_command.begin(), expression_command.end());
	this->EXPRESSION_ACTION_BOX.assign(expression_action_command.begin(), expression_action_command.end());
	this->num_idle = temp_num_idle;
	this->num_action = temp_num_action;
	this->action_model = true;
}

void VIEWERCONSOLE::Draw_model(Node* Game_Mode)
{
	setting_model = LAppLive2DManager::getInstance(INDEX_MODEL, INDEX_TEXTURE); // загрузка модели
	setting_model->changeCoordinate(coordinata_model[0], coordinata_model[1], coordinata_model[2]); //смена координат модели
	current_model = LAppView::createDrawNode(setting_model); // создание объекта модели
	Game_Mode->getChildByName("Box_scene")->addChild(current_model); //наложение модели на слой

}

void VIEWERCONSOLE::Command_model()
{
	
	if (action_model == true)
	{
		setting_model->changeExpression(EXPRESSION_ACTION_BOX);
		setting_model->changeAction(num_action, num_idle, EXPRESSION_BOX);
	}
	else
	{
		setting_model->changeExpression(EXPRESSION_BOX);
		setting_model->changeIdle(num_idle);
	}
}

void VIEWERCONSOLE::view(Node *Game_Mode)
{

	if (script_commands[num_script_commands] == "sprite")
	{
		num_script_commands++;
		Create_commands_sprite(Game_Mode);
		Use_command_sprite(Game_Mode);
	}
	else if (script_commands[num_script_commands] == "scene")
	{
		num_script_commands++;
		Create_commands_scene(Game_Mode);
		Use_command_scene(Game_Mode);
	}
	else if (script_commands[num_script_commands] == "music")
	{
		num_script_commands++;
		background_smooth(Game_Mode, 1, dir_music);
		CONSOLE.view(Game_Mode);
	}
	else if (script_commands[num_script_commands] == "voice")
	{
		num_script_commands++;
		cocos2d::experimental::AudioEngine::stop(Voice_id);
		
		if (dir_voice != "ffff")
			Voice_id = cocos2d::experimental::AudioEngine::play2d(dir_voice, false, All_Volume*Voice_Volume);
		CONSOLE.view(Game_Mode);
	}
	//else if (script_commands[num_script_commands] == "voice_model")
	//{
	//	num_script_commands++;
	//	if (current_model != 0)
	//		current_model->Set_sp_model(Game_Mode->getChildByName("Box_scene"), Voice_id, voicebox);
	//	CONSOLE.view(Game_Mode);
	//}
	else if (script_commands[num_script_commands] == "sound")
	{
		num_script_commands++;
		cocos2d::experimental::AudioEngine::stop(Game_id);
		Game_id = cocos2d::experimental::AudioEngine::play2d(dir_sound, false, All_Volume*Voice_Volume);
		CONSOLE.view(Game_Mode);
	}
	else if (script_commands[num_script_commands] == "shake")
	{
		num_script_commands++;
		Use_shake(Game_Mode);
		CONSOLE.view(Game_Mode);
	}
	else if (script_commands[num_script_commands] == "create_model")
	{
		num_script_commands++;
		Draw_model(Game_Mode);
		CONSOLE.view(Game_Mode);
	}
	else if (script_commands[num_script_commands] == "command_model")
	{
		num_script_commands++;
		Command_model();
		CONSOLE.view(Game_Mode);
	}
	else if (script_commands[num_script_commands] == "cloud")
	{
		num_script_commands++;
		CONSOLE.Get_cloud(Game_Mode);
	}
	else if (script_commands[num_script_commands] == "text")
	{
		num_script_commands++;
		GAME.Get_Text(Game_Mode);
		Star(Game_Mode, true);
	}
	else if (script_commands[num_script_commands] == "return")
	{
		GAME.Next_num();
		GAME.Get_Script(Game_Mode);
	}
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

