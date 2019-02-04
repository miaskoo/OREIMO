/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once

#include "cocos2d.h"


//Live2D Framework
#include "L2DBaseModel.h"
#include "L2DTargetPoint.h"
#include "L2DStandardID.h"
#include <map>
#include <memory>
#include <vector>
//Live2D Lib
#include "Live2DModelOpenGL.h"

//utils
#include "ModelSetting.h"


class LAppModel : public live2d::framework::L2DBaseModel
{
private:
    ModelSetting* modelSetting;

	const char* modelHomeDir;
	std::vector<std::string> idle_expression;
	int num_idle = 0;
	int num_action = 0;
public:
    LAppModel();
    virtual ~LAppModel(void);
	//Initialize
	void init(ModelSetting* setting);
	
	//Load
    void load(const char dir[],const char path[]);
	void preloadMotionGroup(const char name[]);
	void releaseMotionGroup(const char name[]);
	
	//Update
    void update();
    void draw();
	void draw(live2d::framework::L2DMatrix44& matrix, float x, float y, float z);
	void setViewMatrix(float matrix[16]);
	
	

	//Animation
    int startMotion(const char group[],int no,int priority);
	//int startRandomMotion(const char name[],int priority);
	void setIdle(int no);
	void setdeferredIdle(int no, std::vector<std::string> temp_idle_expression);
	void setAction(int no);
	void set_CustomAction();
	void setExpression(const char name[]);
	void setExpression(const char name1[], const char name2[]);
	void setExpression(const char name1[], const char name2[], const char name3[]);
	void setExpression(const char name1[], const char name2[], const char name3[], const char name4[]);
	void setExpression(const char name1[], const char name2[], const char name3[], const char name4[], const char name5[]);
	ModelSetting* GetSetting()
	{
		return modelSetting;
	}
	//void setRandomExpression();
    
	//Other
	std::map< std::string, std::shared_ptr<std::string>> dir_expression;// дирректория пресетов
};



