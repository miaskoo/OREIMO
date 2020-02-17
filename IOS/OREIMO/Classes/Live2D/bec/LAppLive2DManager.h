/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once
#include <vector>
#include "LAppDefine.h"
#include "L2DTargetPoint.h"
#include "L2DMatrix44.h"
#include "cocos2d.h"

class LAppModel;

class LAppLive2DManager{
private :
	std::vector<LAppModel*> models;
	//L2DTargetPoint* dragMgr;
	int Index_model;
	int Index_texture;
	float Coordinate_model_x;
	float Coordinate_model_y;
	float Coordinate_model_z;




	//MyLive2DAllocator	myAllocator ;
	live2d::framework::L2DMatrix44* viewMatrix;
	//SimplePlayer* voice;
public:
	static LAppLive2DManager* getInstance(int model, int texture);
    static void releaseInstance();

#ifdef L2D_TARGET_ANDROID_ES2
	void reinit();
#endif
	void onDrag(float x,float y);
	//void onTap(float x,float y);
	void onUpdate();
	
//	void playVoice(int index);
	
	void setViewMatrix(live2d::framework::L2DMatrix44* m){viewMatrix=m;}
	void releaseModel();
    LAppModel* getModel(int no){ return models[no]; }
    size_t getModelNum(){return models.size();}
	
	//Live2D Model
	void changeModel();
	void changeCoordinate(float x, float y, float z);
	void changeExpression(std::vector<std::string> expression);
	void changeIdle(int num_idle);
	void changeAction(int num_action, int num_idle, std::vector<std::string> idle_expression);
private:
    LAppLive2DManager(int model, int texture) ;
    virtual ~LAppLive2DManager() ;
};
 