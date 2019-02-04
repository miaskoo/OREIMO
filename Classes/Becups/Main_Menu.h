/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
//#ifndef __HELLOWORLD_SCENE_H__
//#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <ui/CocosGUI.h> // Использует label string


class Game : public cocos2d::Layer
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

	void loadsetmain();

	void loadsetgame(int current_script);


    // implement the "static create()" method manually
	CREATE_FUNC(Game);

};

//#endif // __HELLOWORLD_SCENE_H__
