/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "AppDelegate.h"
#include "Main_Menu.h"
#include "Live2D.h"

#ifdef L2D_TARGET_ANDROID_ES2
    //android向けのシェーダ設定のために読み込み
    #include "graphics/DrawParam_OpenGLES2.h"
    #include "base/CCEventListenerCustom.h"
#endif

using namespace live2d;
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
#ifdef L2D_TARGET_ANDROID_ES2
    Director::getInstance()->getEventDispatcher()->removeEventListener(_recreatedEventlistener);
#endif
	LAppLive2DManager* Live2DMgr = LAppLive2DManager::getInstance();
	Live2DMgr->releaseInstance();
	//Live2D::dispose();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("ORE NO IMOUTO");
        director->setOpenGLView(glview);
    }
	//director->getOpenGLView()->setDesignResolutionSize(1136, 640, ResolutionPolicy::SHOW_ALL);
	director->getOpenGLView()->setDesignResolutionSize(1136, 640, ResolutionPolicy::SHOW_ALL);

	//Live2D
	LAppLive2DManager* Live2DMgr = LAppLive2DManager::getInstance();
	//Live2D::init();

#ifdef L2D_TARGET_ANDROID_ES2
	_recreatedEventlistener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, 
		[this](EventCustom*) 
	{
		LAppLive2DManager::getInstance()->reinit();
	});
	director->getEventDispatcher()->addEventListenerWithFixedPriority(_recreatedEventlistener, -1);
#endif

    // create a scene. it's an autorelease object
    auto scene = MAINBOX::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
