#include "Object_Noise.h"
#include "AudioEngine.h"


extern Node* Game_Mode;


Object_Noise::Object_Noise(string dir, type_noise cur_type) : Object_Scene()
{
	this->my_type = cur_type;
	switch (this->my_type)
	{
	case music:
	{
				  this->dir_obj = MUSIC_DIR[dir];
	}
	case sound:
	{
				  this->dir_obj = GAMESE_DIR[dir];
	}
	}
}

swich_node Object_Noise::draw()
{
	//if (this->my_type == music)
	//{
	//	Game_Mode->stopAllActions();
	//	if (cocos2d::experimental::AudioEngine::getVolume(Background_id) - 0.1f < 0)
	//	{
	//		cocos2d::experimental::AudioEngine::stop(Background_id);
	//		Background_id = cocos2d::experimental::AudioEngine::play2d(this->dir_obj, true, All_Volume*Background_Volume);
	//	}
	//	else
	//	{
	//		Game_Mode->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([=](){
	//			this->draw(); }), nullptr));
	//	}
	//}
	//else
	//{
	//	Game_id = cocos2d::experimental::AudioEngine::play2d(this->dir_obj, true, All_Volume*Game_Volume);
	//}
	return swich_node{NULL,NULL};
}
