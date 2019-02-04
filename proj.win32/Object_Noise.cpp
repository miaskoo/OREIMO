#include "Object_Noise.h"
#include "AudioEngine.h"


extern Node* AUDIONODE;
extern void music_play(Node *cur_node, string dir);
extern void sound_play(string dir);

Object_Noise::Object_Noise(type_noise cur_type, string dir) : Object_Scene()
{
	this->my_type = cur_type;
	switch (this->my_type)
	{
	case music:
	{
				  this->dir_obj = MUSIC_DIR[dir];
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
