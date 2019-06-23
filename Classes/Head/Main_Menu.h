/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#pragma once
#include "cocos2d.h"
#include <ui/CocosGUI.h> // Использует label string
#include "Live2D/LAppLive2DManager.h"

namespace profile_player
{
	static bool Skip_All = false, ORE_old = false, Com_twoshot = false, Tips_twoshot = false, Text_old = false, Autosave1 = false, Autosave2 = false, Musalb = false; // Все настройки типа bool

	static float All_Volume = NULL, Background_Volume = NULL, System_Volume = NULL, Game_Volume = NULL, Voice_Volume = NULL; // Вся громкость

	static int Speed_Skip_Text = NULL, Speed_Text = NULL, Speed_Auto_Text = NULL; // Скорость режима пропуска текста, текста, и режима авто чтения

	static int Background_id = NULL, System_id = NULL, Game_id = NULL, Voice_id = NULL; // id потоков аудио будет здесь
}




class MAINBOX : public cocos2d::Layer
{
private:
	bool task = false;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void mainset();

	void gameset();

	void creatorset();

	void loadsetmain();

	void loadsetgame(int current_script);

	void loadsetcreator();


    // implement the "static create()" method manually
	CREATE_FUNC(MAINBOX);

};

#endif