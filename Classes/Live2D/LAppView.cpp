/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "LAppView.h"

//Live2D Application
#include "LAppLive2DManager.h"
#include "LAppDefine.h"


using namespace live2d;
using namespace live2d::framework;

USING_NS_CC;

LAppView::LAppView():DrawNode()
{
	log("hello");
}

void LAppView::onEnter()
{
	DrawNode::onEnter();
	
	
	//// タッチ関係のイベント管理
	//touchMgr=new TouchManager();
	//
	// デバイス座標からスクリーン座標に変換するための
	deviceToScreen=new L2DMatrix44();
	
	// 画面の表示の拡大縮小や移動の変換を行う行列
	viewMatrix=new L2DViewMatrix();

	Size size=Director::getInstance()->getWinSize();
	
	float width=size.width;
	float height=size.height;
	float ratio = (float)height / width;
	float left = VIEW_LOGICAL_LEFT;
	float right = VIEW_LOGICAL_RIGHT;
	float bottom = -ratio;
	float top = ratio;
	
	viewMatrix->setScreenRect(left,right,bottom,top);// デバイスに対応する画面の範囲。 Xの左端, Xの右端, Yの下端, Yの上端

	float screenW=abs(left-right);
	deviceToScreen->multTranslate(-width/2.0f,-height/2.0f );
	deviceToScreen->multScale(screenW / width, -screenW / width );
	
	// 表示範囲の設定
	viewMatrix->setMaxScale( VIEW_MAX_SCALE );// 限界拡大率
	viewMatrix->setMinScale(VIEW_MIN_SCALE);// 限界縮小率
	
	// 表示できる最大範囲
	viewMatrix->setMaxScreenRect(
								 VIEW_LOGICAL_MAX_LEFT,
								 VIEW_LOGICAL_MAX_RIGHT,
								 VIEW_LOGICAL_MAX_BOTTOM,
								 VIEW_LOGICAL_MAX_TOP
								 );
}


void LAppView::onExit()
{
	DrawNode::onExit();

}


void LAppView::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	DrawNode::draw(renderer, transform, flags);
	
	
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(LAppView::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}


void LAppView::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
	kmGLPushMatrix();
    kmGLLoadMatrix(&transform);
	
	//LAppLive2DManager* Live2DMgr = LAppLive2DManager::getInstance(0, 0);
	Live2DMgr->onUpdate();
	
	
	kmGLPopMatrix();
}

LAppView* LAppView::createDrawNode(LAppLive2DManager* temp)
{
	
	LAppView *ret = new (std::nothrow) LAppView();
	
	ret->Live2DMgr = temp;
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;

}