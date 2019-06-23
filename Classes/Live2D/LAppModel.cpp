/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "LAppModel.h"


//Live2D Application
#include "LAppDefine.h"

//utils
#include "ModelSettingJson.h"

#include "SimpleAudioEngine.h"
#include "platform/CCImage.h"

#include <PlatformManager.h>
#include <Live2DFramework.h>
#include <fstream>
using namespace CocosDenshion;

using namespace std;
using namespace live2d;
using namespace live2d::framework;
USING_NS_CC;
extern Node *LIVE2D_NODE_CREATE;

LAppModel::LAppModel()//конструктор - обнуляет настройки моделей
	:L2DBaseModel(),modelSetting(NULL)
{
	// モーションの開始時と終了時のログを出すことができます
	//mainMotionMgr->setMotionDebugMode(true);

	if (LAppDefine::DEBUG_LOG)
	{
		debugMode=true;
	}
}


LAppModel::~LAppModel(void)
{
	if(LAppDefine::DEBUG_LOG)log("delete model");

	for (int i = 0; i < modelSetting->getMotionGroupNum(); i++)
	{
		const char* group=modelSetting->getMotionGroupName(i);//получаем название группы motion
		releaseMotionGroup(group);//отчищаем motion
	}
	delete modelSetting; //удаляем информацию настроек модели
}


void LAppModel::load(const char dir[],const char fileName[])
{
	modelHomeDir = dir;//получаем дирректорию файла настроек модельки
    
    if(LAppDefine::DEBUG_LOG)log( "create model : %s",fileName);
    
    
	ssize_t size;
	string path=fileName;
	path=dir+path;
    unsigned char* data=CCFileUtils::getInstance()->getFileData(path.c_str(),"rb", &size); //грузим данные из файла
    
    ModelSetting* setting=new ModelSettingJson((const char*)data,size);//загружаем файл настроек модели
	free(data);//освобождаем указатель 
	init(setting);//иницилизируем модель
}


void LAppModel::init(ModelSetting* setting)
{
	updating=true;//завершил апдейт?
    initialized=false;//иницилизация?
	
	modelSetting=setting; //ставим инфу о модели из json
	
	//Live2D Model - грузим модельку, текстурки
	if( strcmp( modelSetting->getModelFile() , "" ) != 0 )
    {
		string path=modelSetting->getModelFile();
		path=modelHomeDir+ path;
        loadModelData(path.c_str());
		
		int len=modelSetting->getTextureNum();
	
		
		for (int i=0; i<len; i++)
		{
			string texturePath=modelSetting->getTextureFile(i);
			texturePath=modelHomeDir+texturePath;
			loadTexture(i,texturePath.c_str());
		}
    }
	
    //Expression - пресеты лица
	if (modelSetting->getExpressionNum() > 0)
	{
		int len = modelSetting->getExpressionNum();
		for (int i = 0; i < len; i++)
		{
			string name = modelSetting->getExpressionName(i);
			string file = modelSetting->getExpressionFile(i);
			file = modelHomeDir + file;
			loadExpression(name.c_str(), file.c_str());


		}
	}
	
	//Physics - физику(волос например)
	if( strcmp( modelSetting->getPhysicsFile(), "" ) != 0 )
    {
		string path=modelSetting->getPhysicsFile();
		path=modelHomeDir+path;
        loadPhysics(path.c_str());
    }
	
	//Pose - поза(можно изменять видимость различных групп элементов, для создания различных поз)
	if( strcmp( modelSetting->getPoseFile() , "" ) != 0 )
    {
		string path=modelSetting->getPoseFile();
		path=modelHomeDir+path;
        loadPose(path.c_str());
    }
	
	//Layout - устанавливаем размеры, позиции
	map<string, float> layout;
	modelSetting->getLayout(layout);//???
	modelMatrix->setupLayout(layout);//устанавливаем положения
	
	
	for ( int i = 0; i < modelSetting->getInitParamNum(); i++)//???
	{
		live2DModel->setParamFloat(modelSetting->getInitParamID(i), modelSetting->getInitParamValue(i));
	}
	
	for ( int i = 0; i < modelSetting->getInitPartsVisibleNum(); i++)//настройка прозрачностей из настроек модельки
	{
		live2DModel->setPartsOpacity(modelSetting->getInitPartsVisibleID(i), modelSetting->getInitPartsVisibleValue(i));
	}
	
	live2DModel->saveParam();//сохраняем
	live2DModel->setPremultipliedAlpha(true);//включает мультиплексинг альфа каналов?
	
	for (int i = 0; i < modelSetting->getMotionGroupNum(); i++)//загружает все motion из настроек модельки
	{
		const char* group=modelSetting->getMotionGroupName(i);//получает название группы motion которое грузим
		preloadMotionGroup(group);//грузит все
	}
	
	mainMotionMgr->stopAllMotions();//стопит все анимации
	
	
	
    updating=false;//можно апдейтить?
    initialized=true;//инилизация завершена
}


void LAppModel::preloadMotionGroup(const char group[])
{
    int len = modelSetting->getMotionNum( group );//узнает количество motion в группе
    for (int i = 0; i < len; i++)
	{
		std::stringstream ss;
		
		//ex) idle_0
		ss << group << "_" <<  i;
		
		string name=ss.str();
		string path=modelSetting->getMotionFile(group,i);
		path=modelHomeDir+path;

        if(LAppDefine::DEBUG_LOG)log("load motion name:%s ",name.c_str());
        
		loadMotion(name.c_str(),path.c_str());//функция загрузки motion уже определена

		//const char* voice=modelSetting->getMotionSound(group,i); - чекает есть ли у конкретной motion озвучка, и если есть грузит настройки для нее?
		//if (strcmp( voice , "" ) != 0 )
		//{
		//	string path=voice;
		//	path=modelHomeDir+ path;
		//	
	
		//	SimpleAudioEngine::getInstance()->preloadEffect(path.c_str());
		//}
    }
}


void LAppModel::releaseMotionGroup(const char group[])
{
    int len = modelSetting->getMotionNum( group );
    for (int i = 0; i < len; i++)
	{
		const char* voice=modelSetting->getMotionSound(group,i);
		if (voice!=NULL)
		{
			string path=voice;
			path=modelHomeDir+ path;
	
			SimpleAudioEngine::getInstance()->unloadEffect(path.c_str());
		}
    }
}


void LAppModel::update()
{
	////опять что то с touch
	//dragMgr->update();
	//dragX=dragMgr->getX();
	//dragY=dragMgr->getY();
	//
	//-----------------------------------------------------------------
	live2DModel->loadParam();// 前回セーブされた状態をロード - грузится последнее сохраненное состаяние (местоположение частей модельки)


	if(mainMotionMgr->isFinished())//если завершился motion
	{
		// モーションの再生がない場合、待機モーションの中からランダムで再生する воспроизводить случайную
		startRandomMotion(MOTION_GROUP_IDLE, PRIORITY_IDLE);//ну вообще тут нужно повтарять установленный idle - или выбирать рандомный из группы idle
	}
	else
	{
		mainMotionMgr->updateParam(live2DModel);//обновление 
	}

	live2DModel->saveParam();// 状態を保存 - сохраняет свое состаяние
	//-----------------------------------------------------------------
	//int index_mouse = live2DModel->getPartsDataIndex("PARAM_MOUTH_FORM");
	//live2DModel->setParamFloat("PARAM_MOUTH_FORM", 0);
	
	if (expressionMgr != NULL)
		expressionMgr->updateParam(live2DModel);// 表情でパラメータ更新（相対変化）
																   // Обновление параметра с относительным выражением (относительное изменение)
	////ドラッグによる変化
	////ドラッグによる顔の向きの調整
	//live2DModel->addToParamFloat( PARAM_ANGLE_X, dragX *  30 );// -30から30の値を加える
	//live2DModel->addToParamFloat( PARAM_ANGLE_Y,dragY *  30 );
	//live2DModel->addToParamFloat( PARAM_ANGLE_Z, (dragX * dragY) * -30 );
	//
	////ドラッグによる体の向きの調整
	//live2DModel->addToParamFloat( PARAM_BODY_ANGLE_X    , dragX * 10 );// -10から10の値を加える
	//
	////ドラッグによる目の向きの調整
	//live2DModel->addToParamFloat( PARAM_EYE_BALL_X, dragX  );// -1から1の値を加える
	//live2DModel->addToParamFloat( PARAM_EYE_BALL_Y,dragY  );
	//
	//// 呼吸など
	//long timeMSec = UtSystem::getUserTimeMSec() - startTimeMSec  ;
	//double t = (timeMSec / 1000.0) * 2 * 3.14159  ;//2*Pi*t
	//
	//live2DModel->addToParamFloat( PARAM_ANGLE_X,	(float) (15 * sin( t/ 6.5345 )) , 0.5f);// -15 ~ +15 まで周期的に加算。周期は他とずらす。
	//live2DModel->addToParamFloat( PARAM_ANGLE_Y,	(float) ( 8 * sin( t/ 3.5345 )) , 0.5f);
	//live2DModel->addToParamFloat( PARAM_ANGLE_Z,	(float) (10 * sin( t/ 5.5345 )) , 0.5f);
	//live2DModel->addToParamFloat( PARAM_BODY_ANGLE_X,	(float) ( 4 * sin( t/15.5345 )) , 0.5f);
	//live2DModel->setParamFloat  ( PARAM_BREATH,	(float) (0.5f + 0.5f * sin( t/3.2345 )),1);// 0~1 まで周期的に設定。モーションを上書き。
	
	
	if(physics!=NULL)physics->updateParam(live2DModel);// 物理演算でパラメータ更新 - обновляет физику
	
	// リップシンクの設定 .. Настройка движений губ при озвучке, нужно тестировать...
	//if(lipSync)
	//{
	//	float value = 0;// リアルタイムでリップシンクを行う場合、システムから音量を取得して0～1の範囲で入力してください。
	//	live2DModel->setParamFloat(PARAM_MOUTH_OPEN_Y, value ,0.8f);
	//}
	//
	// ポーズの設定 - изменяет позу
	if(pose!=NULL)pose->updateParam(live2DModel);
	
	live2DModel->update();


	
}


int LAppModel::startMotion(const char group[],int no,int priority)
{
	if (priority==PRIORITY_FORCE)//при запуске motion идет проверка на максималиный приоритет
	{
		mainMotionMgr->setReservePriority(priority);
	}
	else if (! mainMotionMgr->reserveMotion(priority))
	{
		if(LAppDefine::DEBUG_LOG)log("can't start motion.\n");
		return -1;
	}
	
	const char* fileName = modelSetting->getMotionFile(group, no);
	std::stringstream ss;
	
	//ex) idle_0
	ss << group << "_" <<  no;
	
	string name=ss.str();
	AMotion* motion = motions[name.c_str()]; //получаем motion по имени
	bool autoDelete = false;
	if ( motion == NULL )//если такого не существует (грузим не из файла модельки а кастом) 
	{
		string path=fileName;
		path=modelHomeDir+path;
		motion = loadMotion(NULL, path.c_str());//то прогружаем
		
		autoDelete = true;// 終了時にメモリから削除 // и удаляем из памяти при завершении
	}
	
	motion->setFadeIn(  modelSetting->getMotionFadeIn(group,no)  ); //получаем fatein
	motion->setFadeOut( modelSetting->getMotionFadeOut(group,no) );// и fadeout
	
    if(LAppDefine::DEBUG_LOG)log("start motion ( %s : %d )",group,no);
	
	//voice .. Настройка движений губ при озвучке, нужно тестировать...
	//const char* voice=modelSetting->getMotionSound(group,no);
	//if (voice!=NULL && strcmp( voice , "" ) != 0)
	//{
	//	string path=voice;
	//
	//	path=modelHomeDir+ path;
	//
	//	SimpleAudioEngine::getInstance()->playEffect(path.c_str());
	//}
	
	
	return mainMotionMgr->startMotionPrio(motion,autoDelete,priority); //запускаем motion с приоритетом
}


int LAppModel::startRandomMotion(const char name[],int priority)
{
	if(modelSetting->getMotionNum(name)==0)return -1;
    int no = rand() % modelSetting->getMotionNum(name);
    
    return startMotion(name,no,priority);
}


void LAppModel::draw()//отрисовка моделек?
{
    if (live2DModel == NULL)return; //проверяем есть ли вообще объект для отрисовки моделек
	
	live2DModel->draw();
}


void LAppModel::draw(live2d::framework::L2DMatrix44& matrix, float x, float y, float z)
{
	if (live2DModel == NULL)return;
		
	float mvp[16];
	L2DMatrix44::mul(  matrix.getArray(),modelMatrix->getArray(),mvp);
	
	//LIVE2D_NODE_CREATE->getScale()

	mvp[0] = mvp[0] / LIVE2D_NODE_CREATE->getScale();
	mvp[5] = mvp[5] / LIVE2D_NODE_CREATE->getScale();
	mvp[12] = mvp[12] / (LIVE2D_NODE_CREATE->getScale() *1.5) ;
	mvp[13] = y / (LIVE2D_NODE_CREATE->getScale());
	
	((Live2DModelOpenGL*)live2DModel)->setMatrix(mvp) ;
	draw();
}

void LAppModel::setExpression(const char expressionID[])
{
	AMotion* motion = expressions[expressionID];
	if (LAppDefine::DEBUG_LOG)log("expression[%s]", expressionID);
	if (motion != NULL)
	{
		expressionMgr->startMotion(motion, false);
	}
	else
	{
		if (LAppDefine::DEBUG_LOG)log("expression[%s] is null ", expressionID);
	}
}
//
//void LAppModel::setRandomExpression()
//{
//	int no = rand() % expressions.size();
//	map<string, AMotion* >::const_iterator map_ite;
//	int i = 0;
//	for (map_ite = expressions.begin(); map_ite != expressions.end(); map_ite++)
//	{
//		if (i == no)
//		{
//			string name = (*map_ite).first;
//			setExpression(name.c_str());
//			return;
//		}
//		i++;
//	}
//}


void LAppModel::setExpression(std::vector<std::string> presets)
{
	auto _loadExpression([=](const char *name, size_t size, const char* data)
	{
		if (expressions[name] != NULL)
		{
			delete expressions[name];
			expressions[name] = NULL;
		}
		L2DExpressionMotion* motion = L2DExpressionMotion::loadJson(data, (int)size);
		expressions[name] = motion;
	});
	std::string name_level = "";
	std::string complete = "";
	//Expression - пресеты лица 
	if (modelSetting->getExpressionNum() > 0)
	{
		int len = modelSetting->getExpressionNum();
	
	
		for (int n = 0; n < presets.size(); n++)
		{
			for (int i = 0; i < len; i++)
			{
				string name = modelSetting->getExpressionName(i);
				if (name == presets[n])
				{
					name_level += name;
					string file = modelSetting->getExpressionFile(i);
					file = modelHomeDir + file;

					IPlatformManager* pm = Live2DFramework::getPlatformManager();
					size_t size;
					unsigned char* data = pm->loadBytes(file.c_str(), &size);

					if (complete.length() == 0)
					{
						for (int z = 0; z < size; z++)
							complete += data[z];
					}
					else
					{
						complete = complete.substr(0, complete.length() - 7);
						complete += ',';
						bool ready = false;
						for (int z = 0; z < size; z++)
						{
							if (data[z] == 0x5b)
							{
								ready = true;
								z++;
							}
							if (ready == true)
								complete += data[z];
						}
					}
					free(data);
					break;
				}
			}
		}
	}

	_loadExpression(name_level.c_str(), complete.length(), complete.c_str());
	AMotion* motion = expressions[name_level.c_str()];
	
	if (motion != NULL)
	{
		expressionMgr->startMotion(motion, false);
	}
	else
	{
		if (LAppDefine::DEBUG_LOG)log("expression[%s] is null ", name_level);
	}
}


//
///*
// * 当たり判定との簡易テスト。
// * 指定IDの頂点リストからそれらを含む最大の矩形を計算し、点がそこに含まれるか判定
// *
// */ //опять функция для touch
//bool LAppModel::hitTest(const char pid[],float testX,float testY)
//{
//	if(alpha<1)return false;// 透明時は当たり判定なし。
//	int len=modelSetting->getHitAreasNum();
//	for (int i = 0; i < len; i++)
//	{
//		if( strcmp( modelSetting->getHitAreaName(i) ,pid) == 0 )
//		{
//			const char* drawID=modelSetting->getHitAreaID(i);
//			return hitTestSimple(drawID,testX,testY);
//		}
//	}
//	return false;// 存在しない場合はfalse
//}





