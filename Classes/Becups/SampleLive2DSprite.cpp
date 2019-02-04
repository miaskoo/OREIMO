/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "SampleLive2DSprite.h"
#include "base/CCDirector.h"
#include "util/UtSystem.h"

#include "graphics/DrawProfileCocos2D.h"
#include "platform/CCFileUtils.h"
#include "vector"
#include "AudioEngine.h"

using namespace live2d;
USING_NS_CC;


SampleLive2DSprite::SampleLive2DSprite()
{
	/*std::mt19937 mersenne(static_cast<unsigned int>(time(0)));
	curent = mersenne() % 6;*/
}
SampleLive2DSprite::~SampleLive2DSprite()
{
	// テクスチャを解放
	Director::getInstance()->getTextureCache()->removeTextureForKey(pretexturs[0]);
	
	delete motionMgr;
	delete motion;
}

bool SampleLive2DSprite::init()
{
	if (DrawNode::init())
	{
		if (model != nullptr)
		{
			model = nullptr;
		}
		
		for (int i = 0; pretexturs.size()>i; i++)
		{
			auto texture = Director::getInstance()->getTextureCache()->addImage(std::string(pretexturs[i]));			
			int glTexNo = texture->getName() ;
			textures.push_back( texture ) ;
		}


			unsigned char* buf;
			ssize_t bufSize;
			buf = FileUtils::getInstance()->getFileData(premodel, "rb", &bufSize);
		
			auto live2DModel = Live2DModelOpenGL::loadModel( buf,bufSize ) ;
			delete[] buf;
		
			model=live2DModel;
			//simple_model = live2DModel2;
			for (int i = 0; pretexturs.size()>i; i++){
				live2DModel->setTexture( i , textures[i]->getName() ) ;// テクスチャとモデルを結びつける
			}

			// Live2Dモデルはローカル座標で左上を原点にして(CanvasWidth、CanvasWidth)
			// のサイズになるため、以下のようにして調整してください。
			float w = Director::getInstance()->getWinSize().width;
			float h = Director::getInstance()->getWinSize().height;
			float scx = 1.7 / live2DModel->getCanvasWidth() / x_y[2];
			float scy = -1.7 / live2DModel->getCanvasWidth() * (w / h) / x_y[2];
			float x = x_y[0];
			float y = x_y[1];
			float matrix[] = {
				scx, 0, 0, 0,
				0, scy, 0, 0,
				0, 0, 1, 0,
				x, y, 0, 1
			};
			for (int n = 0; n < 16; n++)
				current_matrix[n] = matrix[n];

			live2DModel->setMatrix(matrix) ;// 位置を設定
		
			live2DModel->setPremultipliedAlpha( true );
		
	}
	return true;
}

void SampleLive2DSprite::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	DrawNode::draw(renderer, transform, flags);

	
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(SampleLive2DSprite::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void SampleLive2DSprite::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
	kmGLPushMatrix();
    kmGLLoadMatrix(&transform);
 
	if (actionMgr != NULL)
	{
		if (actionMgr->isFinished())
		{
				delete actionMgr;
				delete action;
				actionMgr = NULL;
				action = NULL;
		}
	}
	else if (motionMgr->isFinished())
	{
		motionMgr->startMotion(motion,false);
	} 


	// Live2Dの描画前と描画後に以下の関数を呼んでください
	// live2d::DrawProfileCocos2D::preDraw() ;
	// live2d::DrawProfileCocos2D::postDraw() ;
	// これはOpenGLの状態をもとに戻すための処理です。
	// これを行わない場合、Cocos2DかLive2Dどちらかで状態の不整合が起こります。
	live2d::DrawProfileCocos2D::preDraw();


		auto live2DModel=model;
		if (actionMgr != NULL)
			actionMgr->updateParam(live2DModel);
		else
			motionMgr->updateParam(live2DModel);
		
		model->update();
		model->draw() ;
	
	
	
	live2d::DrawProfileCocos2D::postDraw() ;


	kmGLPopMatrix();
}
SampleLive2DSprite* SampleLive2DSprite::createDrawNode(std::string temp_model, std::vector<std::string> temp_texturs, float x, float y, float z)
{
	SampleLive2DSprite *ret = new SampleLive2DSprite();
	ret->premodel = temp_model;
	ret->pretexturs.assign(temp_texturs.begin(), temp_texturs.end());

	ret->x_y[0] = x;
	ret->x_y[1] = y;
	ret->x_y[2] = z;

	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}


}

void SampleLive2DSprite::Increase_Model()
{
	auto live2DModel = model;
	// Live2Dモデルはローカル座標で左上を原点にして(CanvasWidth、CanvasWidth)
	// のサイズになるため、以下のようにして調整してください。
	float min = 0.995;
	auto increase = CallFunc::create([=](){
		current_matrix[0] = current_matrix[0] / min;
		current_matrix[5] = current_matrix[5] / min;
		current_matrix[12] = current_matrix[12] / min;
		current_matrix[13] = current_matrix[13] / 0.9985;
		live2DModel->setMatrix(current_matrix);// 位置を設定
	});
	
	auto delay = DelayTime::create(0.0125);
	runAction(Sequence::create(increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, nullptr));
	
}


void SampleLive2DSprite::Decrease_Model()
{
	auto live2DModel = model;
	// Live2Dモデルはローカル座標で左上を原点にして(CanvasWidth、CanvasWidth)
	// のサイズになるため、以下のようにして調整してください。
	float min = 0.995;
	auto increase = CallFunc::create([=](){
		current_matrix[0] = current_matrix[0] * min;
		current_matrix[5] = current_matrix[5] * min;
		current_matrix[12] = current_matrix[12] * min;
		current_matrix[13] = current_matrix[13] * 0.9985;
		live2DModel->setMatrix(current_matrix);// 位置を設定
	});

	auto delay = DelayTime::create(0.0125);
	runAction(Sequence::create(increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, increase, delay, nullptr));

}

void SampleLive2DSprite::Set_sp_model(Node* tempnode, int voice_id, std::vector<bool> timing)
{
	this->Voice = tempnode;
	this->Voice_id = voice_id;
	Get_sp_model(timing);
}

void SampleLive2DSprite::Get_sp_model(std::vector<bool> timing)
{
	timing_num = 0;
	auto delay = DelayTime::create(0.05);
	static Action *id;
	static auto p_id = &id;
	auto speak = CallFunc::create([=]()
	{
		if (timing_num >= timing.size())
			return;

		if (timing[timing_num] == true)
		{
			if (id == NULL)
			{
				*p_id = Voice->runAction(RepeatForever::create(Sequence::create(
					CallFunc::create([=]()
				{
					model->setParamFloat("PARAM_MOUTH_OPEN_Y", 0.3);
				}), DelayTime::create(0.045), CallFunc::create([=]()
				{
					model->setParamFloat("PARAM_MOUTH_OPEN_Y", 0.6);
				}), DelayTime::create(0.045), CallFunc::create([=]()
				{
					model->setParamFloat("PARAM_MOUTH_OPEN_Y", 0.9);
				}), DelayTime::create(0.045), CallFunc::create([=]()
				{
					model->setParamFloat("PARAM_MOUTH_OPEN_Y", 0.6);
				}), DelayTime::create(0.045), CallFunc::create([=]()
				{
					model->setParamFloat("PARAM_MOUTH_OPEN_Y", 0.3);
				}), DelayTime::create(0.045), CallFunc::create([=]()
				{
					model->setParamFloat("PARAM_MOUTH_OPEN_Y", 0.0);
				}), nullptr)));
			}
		}
		else
		{
			if (timing[timing_num] == false)
			{
				Voice->stopAllActions();
				model->setParamFloat("PARAM_MOUTH_OPEN_Y", 0.0);
				*p_id = NULL;
			}
		}
		timing_num++;


	});
	runAction(Repeat::create(Sequence::create(speak, DelayTime::create(0.09), nullptr), timing.size()-1));
	auto setup([=](int s, std::string sws)
	{
		Voice->stopAllActions();
		model->setParamFloat("PARAM_MOUTH_OPEN_Y", 0.0);
	});
	cocos2d::experimental::AudioEngine::setFinishCallback(Voice_id, setup);

}

void SampleLive2DSprite::Stop_sp_model()
{
	if (Voice != NULL)
	{
		Voice->stopAllActions();
		model->setParamFloat("PARAM_MOUTH_OPEN_Y", 0.0);
	}
}

void SampleLive2DSprite::get_idle()
{
	if (motionMgr != NULL)
		delete motionMgr;
	if (motion != NULL)
		delete motion;

	motionMgr = new MotionQueueManager();
	motion = Live2DMotion::loadMotion(complete_motion, complete_motion_size);
	motion->setFadeIn(3000);
	motion->setFadeOut(0);
	delete[] complete_motion;

}
void SampleLive2DSprite::get_action()
{
	if (actionMgr != NULL)
		delete motionMgr;
	if (action != NULL)
		delete motion;

	actionMgr = new MotionQueueManager();
	action = Live2DMotion::loadMotion(complete_action, complete_action_size);
	action->setFadeIn(3000);
	action->setFadeOut(0);
	actionMgr->startMotion(action, false);
	delete[] complete_action;
	get_idle();
	
}

