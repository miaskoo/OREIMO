/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#ifndef __sampleCocos2dx__SampleLive2DSprite__
#define __sampleCocos2dx__SampleLive2DSprite__

#include "cocos2d.h"
#include "2d/CCSprite.h"
#include <vector>
#include "Live2DModelOpenGL.h"
#include "motion/MotionQueueManager.h"
#include "motion/Live2DMotion.h"
#include <vector>
#include <string>



class SampleLive2DSprite :public cocos2d::DrawNode {
	
	live2d::Live2DModelOpenGL* model;
	//live2d::Live2DModelOpenGL* simple_model;
	std::vector<cocos2d::Texture2D*> textures ;
	live2d::MotionQueueManager* motionMgr = NULL;
	live2d::Live2DMotion* motion = NULL;
	live2d::MotionQueueManager* actionMgr = NULL;
	live2d::Live2DMotion* action = NULL;
private:
	std::string premodel; //модель
	std::vector<std::string> pretexturs; // текстуры
	unsigned char *complete_motion; //готовый эффект
	int complete_motion_size;
	float x_y[2]; //матрица положения
	unsigned char *complete_action; //готовый эффект
	int complete_action_size;
	float current_matrix[16];
	int timing_num = 0;
	int Voice_id;
	Node* Voice = NULL;
public:
	SampleLive2DSprite();
	virtual ~SampleLive2DSprite();

	virtual bool init();
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
	static SampleLive2DSprite* createDrawNode(std::string temp_model, std::vector<std::string> temp_texturs, float x, float y, float z);
	void set_data_idle(unsigned char* motion, int size_motion)
	{
		this->complete_motion = motion;
		this->complete_motion_size = size_motion;
	}
	void set_data_action(unsigned char* action, int size_action)
	{
		this->complete_action = action;
		this->complete_action_size = size_action;
	}
	void Set_sp_model(Node* tempnode, int voice_id, std::vector<bool> timing);
	void Get_sp_model(std::vector<bool> timing);
	void Stop_sp_model();
	void Increase_Model();
	void Decrease_Model();
	void get_idle();
	void get_action();

protected:
	cocos2d::CustomCommand _customCommand;
};

#endif /* defined(__sampleCocos2dx__SampleLive2DSprite__) */
