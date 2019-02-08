#include "Object_Noise.h"
#include "AudioEngine.h"


extern Node* AUDIONODE;
extern void music_play(Node *cur_node, string dir);
extern void sound_play(string dir);
extern int string_to_int(string);
//
//
//map<string, string> MUSIC_DIR
//{
//	{ "oRE No IMoUTo", ".\\Resources\\Music\\00000000.mp3" },
//	{ "GOOD MORNiNG", ".\\Resources\\Music\\00000001.mp3" },
//	{ "Immediate Approach", ".\\Resources\\Music\\00000002.mp3" },
//	{ "SOFT BREEZEEEEE", ".\\Resources\\Music\\00000003.mp3" },
//	{ "Merry Go Round", ".\\Resources\\Music\\00000004.mp3" },
//	{ "Roller Coaster", ".\\Resources\\Music\\00000005.mp3" },
//	{ "downpour", ".\\Resources\\Music\\00000006.mp3" },
//	{ "Ferris wheel", ".\\Resources\\Music\\00000007.mp3" },
//	{ "STONiSHMENT HOUSE", ".\\Resources\\Music\\00000008.mp3" },
//	{ "After a storm comes a calm", ".\\Resources\\Music\\00000009.mp3" },
//	{ "street performer", ".\\Resources\\Music\\0000000a.mp3" },
//	{ "Real Substantiality", ".\\Resources\\Music\\0000000b.mp3" },
//	{ "rendezvous", ".\\Resources\\Music\\0000000c.mp3" },
//	{ "AKiHABARA,CHiYODA-KU", ".\\Resources\\Music\\0000000d.mp3" },
//	{ "Super Approach!!", ".\\Resources\\Music\\0000000e.mp3" },
//	{ "DESTROY GAME STORY", ".\\Resources\\Music\\0000000f.mp3" },
//	{ "SECRET x 2", ".\\Resources\\Music\\00000010.mp3" }
//};

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
					  dir_nick = "SOFT BREEZEEEEE";
					  break;					  
				  case 4:
					  dir_nick = "Immediate Approach";
					  break;
				  case 5:
					  dir_nick = "Merry Go Round";
					  break;
				  case 6:
					  dir_nick = "Roller Coaster";
					  break;
				  case 7:
					  dir_nick = "Ferris wheel";
					  break;
				  case 8:
					  dir_nick = "STONiSHMENT HOUSE";
					  break;
				  case 9:
					  dir_nick = "After a storm comes a calm";
					  break;
				  case 10:
					  dir_nick = "street performer";
					  break;
				  case 11:
					  dir_nick = "Real Substantiality";
					  break;
				  case 12:
					  dir_nick = "rendezvous";
					  break;
				  case 13:
					  dir_nick = "AKiHABARA,CHiYODA-KU";
					  break;
				  case 14:
					  dir_nick = "Super Approach!!";
					  break;
				  case 15:
					  dir_nick = "DESTROY GAME STORY";
					  break;
				  case 16:
					  dir_nick = "After a storm comes a calm";
					  break;
				  case 17:
					  dir_nick = "SECRET x 2";
					  break;
				  default:
					  this->dir_obj = "";
					  return;
				  }

				  this->dir_obj = MUSIC_DIR[dir_nick];
				  break;
	}
	case sound:
	{
				  this->dir_obj = GAMESE_DIR[dir];
				  break;
	}
	default:
		break;
	}
}

swich_node Object_Noise::draw()
{
	if (this->my_type == music)
	{
		music_play(AUDIONODE, this->dir_obj);
		/*AUDIONODE->stopAllActions();
		if (cocos2d::experimental::AudioEngine::getVolume(profile_player::Background_id) - 0.1f < 0)
		{
			cocos2d::experimental::AudioEngine::stop(profile_player::Background_id);
			profile_player::Background_id = cocos2d::experimental::AudioEngine::play2d(this->dir_obj, true, profile_player::All_Volume*profile_player::Background_Volume);
		}
		else
		{
			AUDIONODE->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([=](){
				this->draw(); }), nullptr));
		}*/
	}
	else
	{
		sound_play(this->dir_obj);
		//profile_player::Game_id = cocos2d::experimental::AudioEngine::play2d(this->dir_obj, true, profile_player::All_Volume*profile_player::Game_Volume);
	}
	return swich_node{NULL,NULL};
}
