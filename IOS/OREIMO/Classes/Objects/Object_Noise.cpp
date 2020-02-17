#include "Object_Noise.h"
#include "AudioEngine.h"


extern Node* AUDIONODE;
extern void music_play(Node *cur_node, string dir);
extern void sound_play(string dir);
extern int string_to_int(string);


Object_Noise::Object_Noise(type_noise cur_type, string dir) : Object_Scene()
{
	this->my_type = cur_type;
	switch (this->my_type)
	{
	case music:
	{
		int dir_bite = string_to_int(dir);
		string dir_nick = "";
		switch (dir_bite)
		{
		case 1:
			dir_nick = "oRE No IMoUTo";
			break;
		case 2:
			dir_nick = "GOOD MORNiNG";
			break;
		case 3:
			dir_nick = "Immediate Approach";
			break;
		case 4:
			dir_nick = "SOFT BREEZEEEEE";
			break;
		case 5:
			dir_nick = "Merry Go Round";
			break;
		case 6:
			dir_nick = "Roller Coaster";
			break;
		case 7:
			dir_nick = "downpour";
			break;
		case 8:
			dir_nick = "Ferris wheel";
			break;
		case 9:
			dir_nick = "STONiSHMENT HOUSE";
			break;
		case 10:
			dir_nick = "After a storm comes a calm";
			break;
		case 11:
			dir_nick = "street performer";
			break;
		case 12:
			dir_nick = "Real Substantiality";
			break;
		case 13:
			dir_nick = "rendezvous";
			break;
		case 14:
			dir_nick = "AKiHABARA,CHiYODA-KU";
			break;
		case 15:
			dir_nick = "Super Approach!!";
			break;
		case 16:
			dir_nick = "DESTROY GAME STORY";
			break;
		case 17:
			dir_nick = "SECRET x 2";
			break;
		default:
			dir_nick = "";
			this->dir_obj = "";
			return;
		}

		if (MUSIC_DIR.find(dir_nick) == MUSIC_DIR.cend())
		{
			this->dir_obj = this->BAD;
			MessageBox("Ошибка иницилизации музыки", "Ошибка");
			return;
		}
		this->dir_obj = MUSIC_DIR[dir_nick];
		break;
	}
	case sound:
	{

		if (GAMESE_DIR.find(dir) == GAMESE_DIR.cend())
		{
			this->dir_obj = this->BAD;
			MessageBox("Ошибка иницилизации звука", "Ошибка");
			return;
		}
		this->dir_obj = GAMESE_DIR[dir];
		break;
	}
	default:
		break;
	}
}

swich_node Object_Noise::draw()
{
	if (this->dir_obj != this->BAD)
	{
		if (this->my_type == music)
		{
			music_play(AUDIONODE, this->dir_obj);
		}
		else
		{
			sound_play(this->dir_obj);
		}
	}
	else
	{
		MessageBox("Ошибка проигрыша музики, dir_obj == BAD", "Ошибка");
	}

	return swich_node{NULL,NULL};
}
