/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "LAppLive2DManager.h"


//Live2D Application
#include "LAppModel.h"
#include "PlatformManager.h"

#include "L2DStandardID.h"
#include "Live2DFramework.h"

#include "graphics/DrawProfileCocos2D.h"

#ifdef L2D_TARGET_ANDROID_ES2
	//android向けのシェーダ設定のために読み込み
	#include "graphics/DrawParam_OpenGLES2.h"
#endif

USING_NS_CC;

using namespace live2d;
using namespace live2d::framework;

static LAppLive2DManager* instance=NULL;



LAppLive2DManager* LAppLive2DManager::getInstance(int model, int texture)
{


	if (instance==NULL)
	{
		instance=new LAppLive2DManager(model, texture);
	}
	else
	{
		delete instance;
		instance = new LAppLive2DManager(model, texture);
	}
	
	return instance;
}


void LAppLive2DManager::releaseInstance()
{
	if (instance)
	{
		delete instance;
		auto framework=live2d::framework::Live2DFramework::getPlatformManager();
		delete framework;
	}

	instance=NULL;
}


LAppLive2DManager::LAppLive2DManager(int model, int texture)
{
	Index_model = model;
	Index_texture = texture;

	if (LAppDefine::DEBUG_LOG) {
		log( "==============================================" ) ;
		log( "   Live2D SDK Sample App1") ;
		log( "==============================================" ) ;
	}
	
	// 以下の命令でメモリリークの検査を実施（_DEBUGモードのみ）
	// Live2D::dispose()時に、Live2Dの管理するメモリでリークが発生していた場合にダンプする
	// リークしている場合は、MEMORY_DEBUG_MEMORY_INFO_ALLでより詳細な情報をダンプします
	// 検査用のデータはglobal new演算子を使います
	//UtDebug::addMemoryDebugFlags( live2d::UtDebug::MEMORY_DEBUG_MEMORY_INFO_COUNT ) ;
	
	// Initialize Live2D
	//Live2D::init( &myAllocator );
	Live2D::init();

	#ifdef L2D_TARGET_ANDROID_ES2
	    char *exts = (char*)glGetString(GL_EXTENSIONS);
	    if(strstr(exts, "GL_NV_shader_framebuffer_fetch ")){
	        live2d::DrawParam_OpenGLES2::setExtShaderMode( true , true );
	    }
	#endif

	Live2DFramework::setPlatformManager(new PlatformManager());

//	dragMgr=new L2DTargetPoint();
	changeModel();
	
	//voice=new SimplePlayer();
	//voice->OnInitialize();
	viewMatrix=NULL;
}


LAppLive2DManager::~LAppLive2DManager()
{
	releaseModel();
	Live2D::dispose();
	
}


void LAppLive2DManager::releaseModel()
{
	for (int i=0; i<models.size(); i++)
	{
		delete models[i];
	}
    models.clear();
}

#ifdef L2D_TARGET_ANDROID_ES2
void LAppLive2DManager::reinit()
{
	live2d::DrawParam_OpenGLES2::reloadShader();
	changeScene(sceneIndex);
}
#endif

void LAppLive2DManager::onDrag(float x, float y)
{
	for (int i=0; i<models.size(); i++)
	{
		LAppModel* model = getModel(i);
		
		model->setDrag(x,y);
		
	}
}

void LAppLive2DManager::onUpdate()
{
	// Live2Dの描画前と描画後に以下の関数を呼んでください
	//live2d::DrawProfileCocos2D::preDraw() ;
	//live2d::DrawProfileCocos2D::postDraw() ;
	// これはOpenGLの状態をもとに戻すための処理です。
	// これを行わない場合、Cocos2DかLive2Dどちらかで状態の不整合が起こります。
	live2d::DrawProfileCocos2D::preDraw();

	L2DMatrix44 projection;
	Director* director=Director::getInstance();
	Size window=director->getWinSize();
	projection.scale(1, window.width/window.height);
	
	if (viewMatrix!=NULL) {
		projection.append(viewMatrix);
	}
	

	for (int i=0; i<models.size(); i++)
	{
		LAppModel* model = getModel(i);
		
		
		model->update();
		model->draw(projection, Coordinate_model_x, Coordinate_model_y, Coordinate_model_z);
	}
	
	live2d::DrawProfileCocos2D::postDraw() ;
}


void LAppLive2DManager::changeModel()
{
	//sceneIndex=index;
	if (LAppDefine::DEBUG_LOG)log("model index : %d", Index_model, Index_texture);
	//Index_model = 2; // установка номера мождели вручную
	//Index_texture = 2; //установка номера текстуры вручную
	switch (Index_model)
	{
	case INDEX_MODEL_AYASE:
		releaseModel();
		models.push_back(new LAppModel());
		switch (Index_texture)
		{
		case 0:
			models[0]->load(MODEL_AYASE_DIR, MODEL_AYASE_A);
			break;
		case 1:
			models[0]->load(MODEL_AYASE_DIR, MODEL_AYASE_B);
			break;
		default:
			break;
		}
		Coordinate_model_x = AYASE_MATRIX_X;
		Coordinate_model_y = AYASE_MATRIX_Y;
		Coordinate_model_z = AYASE_MATRIX_Z;
		break;
	case INDEX_MODEL_KANAKO:
			releaseModel();
			models.push_back(new LAppModel());
			switch (Index_texture)
			{
			case 0:
				models[0]->load(MODEL_KANAKO_DIR, MODEL_KANAKO_A);
				break;
			case 1:
				models[0]->load(MODEL_KANAKO_DIR, MODEL_KANAKO_B);
				break;
			case 2:
				models[0]->load(MODEL_KANAKO_DIR, MODEL_KANAKO_C);
				break;
			default:
				break;
			}
			Coordinate_model_x = KANAKO_MATRIX_X;
			Coordinate_model_y = KANAKO_MATRIX_Y;
			Coordinate_model_z = KANAKO_MATRIX_Z;
			break;
		case INDEX_MODEL_KIRINO:
			releaseModel();
			models.push_back(new LAppModel());
			switch (Index_texture)
			{
			case 0:
				models[0]->load(MODEL_KIRINO_DIR, MODEL_KIRINO_A);
				break;
			case 1:
				models[0]->load(MODEL_KIRINO_DIR, MODEL_KIRINO_B);
				break;
			case 2:
				models[0]->load(MODEL_KIRINO_DIR, MODEL_KIRINO_C);
				break;
			default:
				break;
			}
			Coordinate_model_x = KIRINO_MATRIX_X;
			Coordinate_model_y = KIRINO_MATRIX_Y;
			Coordinate_model_z = KIRINO_MATRIX_Z;
			break;
		case INDEX_MODEL_KURONEKO:
			releaseModel();
			models.push_back(new LAppModel());
			switch (Index_texture)
			{
			case 0:
				models[0]->load(MODEL_KURONEKO_DIR, MODEL_KURONEKO_A);
				break;
			case 1:
				models[0]->load(MODEL_KURONEKO_DIR, MODEL_KURONEKO_B);
				break;
			default:
				break;
			}
			Coordinate_model_x = KURONEKO_MATRIX_X;
			Coordinate_model_y = KURONEKO_MATRIX_Y;
			Coordinate_model_z = KURONEKO_MATRIX_Z;
			break;
		case INDEX_MODEL_MANAMI:
			models.push_back(new LAppModel());
			switch (Index_texture)
			{
			case 0:
				models[0]->load(MODEL_MANAMI_DIR, MODEL_MANAMI_A);
				break;
			case 1:
				models[0]->load(MODEL_MANAMI_DIR, MODEL_MANAMI_B);
				break;
			default:
				break;
			}
			Coordinate_model_x = MANAMI_MATRIX_X;
			Coordinate_model_y = MANAMI_MATRIX_Y;
			Coordinate_model_z = MANAMI_MATRIX_Z;
			break;
		case INDEX_MODEL_SAORI:
			releaseModel();
			models.push_back(new LAppModel());
			switch (Index_texture)
			{
			case 0:
				models[0]->load(MODEL_SAORI_DIR, MODEL_SAORI_A);
				break;
			case 1:
				models[0]->load(MODEL_SAORI_DIR, MODEL_SAORI_B);
				break;
			default:
				break;
			}
			Coordinate_model_x = SAORI_MATRIX_X;
			Coordinate_model_y = SAORI_MATRIX_Y;
			Coordinate_model_z = SAORI_MATRIX_Z;
			break;
		default:
			break;
	}
	
}
using namespace std;

void LAppLive2DManager::changeCoordinate(float x, float y, float z)
{
	this->Coordinate_model_x = x;
	this->Coordinate_model_y = y;
	this->Coordinate_model_z = z;
}

void LAppLive2DManager::changeExpression(vector<string> expression)
{
	models[0]->setExpression(expression[0].c_str());

	//switch (expression.size())
	//{
	//case 1:
	//	models[0]->setExpression(expression[0].c_str());
	//	break;
	//case 2:
	//	models[0]->setExpression(expression[0].c_str(), expression[1].c_str());
	//	break;
	//case 3:
	//	models[0]->setExpression(expression[0].c_str(), expression[1].c_str(), expression[2].c_str());
	//	break;
	//case 4:
	//	models[0]->setExpression(expression[0].c_str(), expression[1].c_str(), expression[2].c_str(), expression[3].c_str());
	//	break;
	//case 5:
	//	models[0]->setExpression(expression[0].c_str(), expression[1].c_str(), expression[2].c_str(), expression[3].c_str(), expression[4].c_str());
	//	break;
	//default:
	//	break;
	//}
	
}

void LAppLive2DManager::changeIdle(int num_idle)
{
	models[0]->setIdle(num_idle);
}

void LAppLive2DManager::changeAction(int num_action, int num_idle, vector<string> idle_expression)
{
	models[0]->setAction(num_action);
	models[0]->setdeferredIdle(num_idle, idle_expression);
}