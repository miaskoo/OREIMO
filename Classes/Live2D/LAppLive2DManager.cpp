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



extern Node *LIVE2D_NODE_CREATE;


LAppLive2DManager* LAppLive2DManager::getInstance()//можно сказать функция пре конструктор, чтобы объект
{													// LAppLive2DManager существовал в коде в единственном экземпляре

	if (instance==NULL)
	{
		instance=new LAppLive2DManager();//создаем объект
	}
	
	return instance;
}



LAppLive2DManager::LAppLive2DManager() // конструктор (по умолчанию будет выбрана сцена под индексом 0)
{
	
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
	Live2D::init(); //входная иницилизация live2D при выходе юзать Live2D::dispose();

	#ifdef L2D_TARGET_ANDROID_ES2
	    char *exts = (char*)glGetString(GL_EXTENSIONS);
	    if(strstr(exts, "GL_NV_shader_framebuffer_fetch ")){
	        live2d::DrawParam_OpenGLES2::setExtShaderMode( true , true );
	    }
	#endif

	Live2DFramework::setPlatformManager(new PlatformManager());//создаем и устанавливает в себя объект ??? не очень понял что делает
	
	//changeScene(SCENE_INDEX_HARU); // устанавливает модельку
	
	viewMatrix=NULL;//??ну если предположить что эта матрица - кастомное 
	//местоположение моделек в облости - то она просто обнулсяется перед новой иницилизацией
}




#ifdef L2D_TARGET_ANDROID_ES2
void LAppLive2DManager::reinit()
{
	live2d::DrawParam_OpenGLES2::reloadShader();
	changeScene(sceneIndex);
}
#endif

void LAppLive2DManager::onUpdate()
{
	// Live2Dの描画前と描画後に以下の関数を呼んでください Вызываем следующие функции до и после рисования Live2D
	//live2d::DrawProfileCocos2D::preDraw() ;
	//live2d::DrawProfileCocos2D::postDraw() ;
	// これはOpenGLの状態をもとに戻すための処理です。 Это процесс восстановления состояния OpenGL.
	// これを行わない場合、Cocos2DかLive2Dどちらかで状態の不整合が起こります。Если вы этого не сделаете, 
																		//то Cocos2D или Live2D вызовут несогласованность состояний.
	
	live2d::DrawProfileCocos2D::preDraw(); //всегда должна вызываться перед собственной отрисовкой

	L2DMatrix44 projection;
	Director* director=Director::getInstance();
	Size window=director->getWinSize();
	projection.scale(1, window.width/window.height);
	
	if (viewMatrix!=NULL) {
		projection.append(viewMatrix);//(что то там преобразует с матрицей)
	}
	
	
	for (int i=0; i<models.size(); i++)//проходимся по всем активным моделькам - обновляем параметры
	{
		LAppModel* model = getModel(i);//получаем модель по индексу (вот что что но я НИ РАЗУ не понял зачем делать обертку доступа к вектору)
		
		
		model->update();//обновляем пораметры
		//model->getLive2DModel()->getDrawParam()->setBaseColor(0.1f, 1, 1, 1);
		//model->getLive2DModel()->getDrawParam()->setBaseColor(float(LIVE2D_NODE_CREATE->getOpacity())/255.f, 1, 1, 1);//подрубает opacity родительской ноды созданной кокоса

		
		model->draw(projection, Coordinate_model_x, Coordinate_model_y, Coordinate_model_z);//отрисовываем по матрице?..
		
	}
	
	live2d::DrawProfileCocos2D::postDraw(); //всегда должна вызываться после завершения отрисовки
}




LAppModel* LAppLive2DManager::changeScene(int Index_model, int Index_texture)//изменяет модельки по индексу
{
//	sceneIndex=index;
	if(LAppDefine::DEBUG_LOG)log("model index : %d", Index_model);
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
		releaseModel();
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

	return models.back();
}






void LAppLive2DManager::releaseModel()//отчищает все модельки и их настройки
{
	for (int i = 0; i<models.size(); i++)
	{
		delete models[i];
	}
	models.clear();
}


void LAppLive2DManager::releaseInstance()//пре деструктор?
{
	if (instance)
	{
		delete instance;
		auto framework = live2d::framework::Live2DFramework::getPlatformManager();
		delete framework;
	}

	instance = NULL;
}

LAppLive2DManager::~LAppLive2DManager()//деструктор
{
	releaseModel();
	Live2D::dispose();//завершение работы с live2d

}


//void LAppLive2DManager::nextScene()//переключает модельки повышая индекс 0_0? можно будет сделать смену модели с отправкой индекса
//{
//	int no = (sceneIndex+1) % SCENE_NUM;
//	changeScene(no);
//}

//
//void LAppLive2DManager::onDrag(float x, float y)//для touch
//{
//	for (int i = 0; i<models.size(); i++)
//	{
//		LAppModel* model = getModel(i);
//
//		model->setDrag(x, y);
//
//	}
//}
//
//
//void LAppLive2DManager::onTap(float x, float y)//для touch
//{
//	if (LAppDefine::DEBUG_LOG)log("tapEvent");
//
//
//	for (int i = 0; i<models.size(); i++)
//	{
//		if (models[i]->hitTest(HIT_AREA_NAME_HEAD, x, y))
//		{
//			if (LAppDefine::DEBUG_LOG)log("face");
//			models[i]->setRandomExpression();
//		}
//		else if (models[i]->hitTest(HIT_AREA_NAME_BODY, x, y))
//		{
//			if (LAppDefine::DEBUG_LOG)log("body");
//			models[i]->startRandomMotion(MOTION_GROUP_TAP_BODY, PRIORITY_NORMAL);
//		}
//	}
//}
