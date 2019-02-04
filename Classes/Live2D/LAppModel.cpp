/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "LAppModel.h"

#include <memory>
#include <fstream>
//Live2D Application
#include "LAppDefine.h"

//utils
#include "ModelSettingJson.h"

#include "SimpleAudioEngine.h"
#include "platform/CCImage.h"

using namespace CocosDenshion;

using namespace std;
using namespace live2d;
using namespace live2d::framework;
USING_NS_CC;


LAppModel::LAppModel()
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
		const char* group=modelSetting->getMotionGroupName(i);
		releaseMotionGroup(group);
	}
	expressions.clear();
	delete modelSetting;
}


void LAppModel::load(const char dir[],const char fileName[])
{
	modelHomeDir = dir;
    
    if(LAppDefine::DEBUG_LOG)log( "create model : %s",fileName);
    
    
	ssize_t size;
	string path=fileName;
	path=dir+path;
    unsigned char* data=CCFileUtils::getInstance()->getFileData(path.c_str(),"rb", &size);
    
    ModelSetting* setting=new ModelSettingJson((const char*)data,size);
	free(data);
	init(setting);
}

void LAppModel::init(ModelSetting* setting)
{
	updating=true;
    initialized=false;
	
	modelSetting=setting;
	
	//Live2D Model
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
	
    //Expression
	if (modelSetting->getExpressionNum() > 0)
	{
		int len=modelSetting->getExpressionNum();
		for (int i=0; i<len; i++)
		{
			string name=modelSetting->getExpressionName(i);
			string file=modelSetting->getExpressionFile(i);
			file=modelHomeDir+file;
			if (dir_expression[name] != NULL)
			{
				delete expressions[name];
				expressions[name] = NULL;
			}
			shared_ptr<string> temp_dir_expression(new string(file));
			dir_expression[name.c_str()] = temp_dir_expression;
			//loadExpression(name.c_str(), file.c_str());
		}
	}
	
	//Physics
	if( strcmp( modelSetting->getPhysicsFile(), "" ) != 0 )
    {
		string path=modelSetting->getPhysicsFile();
		path=modelHomeDir+path;
        loadPhysics(path.c_str());
    }
	
	//Pose
	if( strcmp( modelSetting->getPoseFile() , "" ) != 0 )
    {
		string path=modelSetting->getPoseFile();
		path=modelHomeDir+path;
        loadPose(path.c_str());
    }
	
	//Layout
	map<string, float> layout;
	modelSetting->getLayout(layout);
	modelMatrix->setupLayout(layout);
	
	
	for ( int i = 0; i < modelSetting->getInitParamNum(); i++)
	{
		live2DModel->setParamFloat(modelSetting->getInitParamID(i), modelSetting->getInitParamValue(i));
	}
	
	for ( int i = 0; i < modelSetting->getInitPartsVisibleNum(); i++)
	{
		live2DModel->setPartsOpacity(modelSetting->getInitPartsVisibleID(i), modelSetting->getInitPartsVisibleValue(i));
	}
	
	live2DModel->saveParam();
	live2DModel->setPremultipliedAlpha(true);
	
	for (int i = 0; i < modelSetting->getMotionGroupNum(); i++)
	{
		const char* group=modelSetting->getMotionGroupName(i);
		preloadMotionGroup(group);
	}
	
	mainMotionMgr->stopAllMotions();
	
	
	
    updating=false;
    initialized=true;
}


void LAppModel::preloadMotionGroup(const char group[])
{
    int len = modelSetting->getMotionNum( group );
    for (int i = 0; i < len; i++)
	{
		std::stringstream ss;
		
		//ex) idle_0
		ss << group << "_" <<  i;
		
		string name=ss.str();
		string path=modelSetting->getMotionFile(group,i);
		path=modelHomeDir+path;

        if(LAppDefine::DEBUG_LOG)log("load motion name:%s ",name.c_str());
        
		loadMotion(name.c_str(),path.c_str());

		const char* voice=modelSetting->getMotionSound(group,i);
		if (strcmp( voice , "" ) != 0 )
		{
			string path=voice;
			path=modelHomeDir+ path;
			
	
			SimpleAudioEngine::getInstance()->preloadEffect(path.c_str());
		}
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


void LAppModel::set_CustomAction()// расписанные движения туда сюда для глаз или пальцев
{
	// 5 - глаза по y

	live2DModel->setParamFloat(5, 0.02);

	live2DModel->setParamFloat(5, 0.04);

	live2DModel->setParamFloat(5, 0.06);

	live2DModel->setParamFloat(5, 0.08);

	live2DModel->setParamFloat(5, 0.1);
	live2DModel->setParamFloat(5, 0.1);
	live2DModel->setParamFloat(5, 0.1);

	live2DModel->setParamFloat(5, 0.08);

	live2DModel->setParamFloat(5, 0.06);

	live2DModel->setParamFloat(5, 0.04);

	live2DModel->setParamFloat(5, 0.02);

	live2DModel->setParamFloat(5, 0.f);

	live2DModel->setParamFloat(5, -0.02);

	live2DModel->setParamFloat(5, -0.04);

	live2DModel->setParamFloat(5, -0.06);

	live2DModel->setParamFloat(5, -0.08);

	live2DModel->setParamFloat(5, -0.1);
	live2DModel->setParamFloat(5, -0.1);
	live2DModel->setParamFloat(5, -0.1);

	live2DModel->setParamFloat(5, -0.08);

	live2DModel->setParamFloat(5, -0.06);

	live2DModel->setParamFloat(5, -0.04);

	live2DModel->setParamFloat(5, -0.02);

	live2DModel->setParamFloat(5, 0.f);



}

void LAppModel::update()
{
	dragMgr->update();
	dragX=dragMgr->getX();
	dragY=dragMgr->getY();
	
	//-----------------------------------------------------------------
	live2DModel->loadParam();// 前回セーブされた状態をロード
	if(mainMotionMgr->isFinished())
	{
		// モーションの再生がない場合、待機モーションの中からランダムで再生する
		//startRandomMotion(MOTION_GROUP_IDLE, PRIORITY_IDLE);
		switch(idle_expression.size())
		{
		case 1:
			setExpression(idle_expression[0].c_str());
			idle_expression.clear();
			break;	
		case 2:
			setExpression(idle_expression[0].c_str(), idle_expression[1].c_str());
			idle_expression.clear();
			break;
		case 3:
			setExpression(idle_expression[0].c_str(), idle_expression[1].c_str(), idle_expression[2].c_str());
			idle_expression.clear();
			break;
		case 4:
			setExpression(idle_expression[0].c_str(), idle_expression[1].c_str(), idle_expression[2].c_str(), idle_expression[3].c_str());
			idle_expression.clear();
			break;
		case 5:
			setExpression(idle_expression[0].c_str(), idle_expression[1].c_str(), idle_expression[2].c_str(), idle_expression[3].c_str(), idle_expression[4].c_str());
			idle_expression.clear();
			break;
		default:
			break;
		}
		startMotion(MOTION_GROUP_IDLE, num_idle, PRIORITY_IDLE);
	}
	else
	{
		mainMotionMgr->updateParam(live2DModel);	
	//	live2DModel->setParamFloat(); // ТУТ НУЖНО БУДЕТ НАСТРАИВАТЬ ПОБОЧНЫЕ ДЕЙСТВИЯ (движения глаз движение пальца)
	}
	live2DModel->saveParam();// 状態を保存
	//-----------------------------------------------------------------


	if(expressionMgr!=NULL)expressionMgr->updateParam(live2DModel);// 表情でパラメータ更新（相対変化）

	if(physics!=NULL)physics->updateParam(live2DModel);// 物理演算でパラメータ更新
	
	// リップシンクの設定
	if(lipSync)
	{
		float value = 0;// リアルタイムでリップシンクを行う場合、システムから音量を取得して0～1の範囲で入力してください。
		live2DModel->setParamFloat(PARAM_MOUTH_OPEN_Y, value, 0.8f);
	}
	
	// ポーズの設定
	if(pose!=NULL)pose->updateParam(live2DModel);
	
	live2DModel->update();
	
}

void LAppModel::setIdle(int no)
{
	num_idle = no;
	startMotion(MOTION_GROUP_IDLE, num_idle, PRIORITY_IDLE);
}

void LAppModel::setdeferredIdle(int no, vector<string> temp_idle_expression)
{
	num_idle = no;
	idle_expression.clear();
	idle_expression.assign(temp_idle_expression.begin(), temp_idle_expression.end());
}

void LAppModel::setAction(int no)
{
	num_action = no;
	startMotion(MOTION_GROUP_ACTION, num_action, PRIORITY_NORMAL);
}

int LAppModel::startMotion(const char group[],int no,int priority)
{
	if (priority==PRIORITY_FORCE)
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
	AMotion* motion = motions[name.c_str()];
	bool autoDelete = false;
	if ( motion == NULL )
	{
		string path=fileName;
		path=modelHomeDir+path;
		motion = loadMotion(NULL,path.c_str());
		
		autoDelete = true;// 終了時にメモリから削除
	}
	
	motion->setFadeIn(  modelSetting->getMotionFadeIn(group,no)  );
	motion->setFadeOut( modelSetting->getMotionFadeOut(group,no) );
	
    if(LAppDefine::DEBUG_LOG)log("start motion ( %s : %d )",group,no);
	
	////voice
	//const char* voice=modelSetting->getMotionSound(group,no);
	//if (voice!=NULL && strcmp( voice , "" ) != 0)
	//{
	//	string path=voice;
	//
	//	path=modelHomeDir+ path;
	//
	//	SimpleAudioEngine::getInstance()->playEffect(path.c_str());
	//}
	
	
	return mainMotionMgr->startMotionPrio(motion,autoDelete,priority);
}


void LAppModel::draw()
{
    if (live2DModel == NULL)return;
	
	live2DModel->draw();
}


void LAppModel::draw(live2d::framework::L2DMatrix44& matrix, float x, float y, float z)
{
	if (live2DModel == NULL)return;
		
	float mvp[16];
	L2DMatrix44::mul(  matrix.getArray(),modelMatrix->getArray(),mvp);

	mvp[12] = x;
	mvp[13] = y;
    mvp[0] = mvp[0] / (z*1.2);
	mvp[5] = mvp[5] / (z*1.2);
	((Live2DModelOpenGL*)live2DModel)->setMatrix(mvp) ;
	draw();
}


string int_to_string(int x)
{
	std::stringstream buff;
	buff << x;
	string complete;
	buff >> complete;
	return complete;
}

void LAppModel::setExpression(const char expressionID[])
{
	loadExpression("comlete_expression", (*dir_expression[expressionID]).c_str());
	AMotion* motion = expressions["comlete_expression"];
	
	if(LAppDefine::DEBUG_LOG)log( "expression[%s]" , expressionID ) ;
	if( motion != NULL )
	{
		expressionMgr->startMotion(motion, false) ;
	}
	else
	{
		if(LAppDefine::DEBUG_LOG)log( "expression[%s] is null " , expressionID ) ;
	}
}


void LAppModel::setExpression(const char expressionID1[], const char expressionID2[])
{


	auto filedata([=](string dir1, string dir2)
	{
		ssize_t size1;
		ssize_t size2;
		unsigned char* data1 = CCFileUtils::getInstance()->getFileData(dir1.c_str(), "rb", &size1);
		unsigned char* data2 = CCFileUtils::getInstance()->getFileData(dir2.c_str(), "rb", &size2);
		string complete = string(reinterpret_cast<char const*>(data1), size1 - 7);
		complete = complete + ',';
		for (int n = 0; n < size2; n++)
		{
			if (data2[n] == 0x5b)
			{
				n++;
				for (; n < size2; n++)
				{
					complete = complete + static_cast<char>(data2[n]);
				}
			}
		}
		delete[] data1;
		delete[] data2;
		return complete;
	});
	string expression = filedata(*dir_expression[expressionID1], *dir_expression[expressionID2]);
	ofstream temp("Debug.win32\\temp.json", ios::binary);
	temp.write(expression.c_str(), expression.length());
	temp.close();
	string name_expression = int_to_string(rand()); // каждый раз необходимо создавать уникальное имя
	loadExpression(name_expression.c_str(), "temp.json");
	std::remove("Debug.win32\\temp.json");
	AMotion* motion = expressions[name_expression.c_str()];

	if (LAppDefine::DEBUG_LOG)log("expression[%s]", expressionID1, expressionID2);
	if (motion != NULL)
	{
		expressionMgr->startMotion(motion, false);
	}
	else
	{
		if (LAppDefine::DEBUG_LOG)log("expression[%s] is null ", expressionID1, expressionID2);
	}
}



void LAppModel::setExpression(const char expressionID1[], const char expressionID2[], const char expressionID3[])
{


	auto filedata([=](string dir1, string dir2, string dir3)
	{
		ssize_t size1;
		ssize_t size2;
		ssize_t size3;
		unsigned char* data1 = CCFileUtils::getInstance()->getFileData(dir1.c_str(), "rb", &size1);
		unsigned char* data2 = CCFileUtils::getInstance()->getFileData(dir2.c_str(), "rb", &size2);
		unsigned char* data3 = CCFileUtils::getInstance()->getFileData(dir3.c_str(), "rb", &size3);
		string complete = string(reinterpret_cast<char const*>(data1), size1 - 7);
		complete = complete + ',';
		for (int n = 0; n < size2; n++)
		{
			if (data2[n] == 0x5b)
			{
				n++;
				for (; n < size2-7; n++)
				{
					complete = complete + static_cast<char>(data2[n]);
				}
			}
		}
		complete = complete + ',';
		for (int n = 0; n < size3; n++)
		{
			if (data3[n] == 0x5b)
			{
				n++;
				for (; n < size3; n++)
				{
					complete = complete + static_cast<char>(data3[n]);
				}
			}
		}
		delete[] data1;
		delete[] data2;
		delete[] data3;
		return(complete);
	});

	string expression = filedata(*dir_expression[expressionID1], *dir_expression[expressionID2], *dir_expression[expressionID3]);
	ofstream temp("Debug.win32\\temp.json", ios::binary);
	temp.write(expression.c_str(), expression.length());
	temp.close();
	string name_expression = int_to_string(rand()); // каждый раз необходимо создавать уникальное имя
	loadExpression(name_expression.c_str(), "temp.json");
	std::remove("Debug.win32\\temp.json");
	AMotion* motion = expressions[name_expression.c_str()];


	if (LAppDefine::DEBUG_LOG)log("expression[%s]", expressionID1, expressionID2, expressionID3);
	if (motion != NULL)
	{
		expressionMgr->startMotion(motion, false);
	}
	else
	{
		if (LAppDefine::DEBUG_LOG)log("expression[%s] is null ", expressionID1, expressionID2, expressionID3);
	}
}

void LAppModel::setExpression(const char expressionID1[], const char expressionID2[], const char expressionID3[], const char expressionID4[])
{


	auto filedata([=](string dir1, string dir2, string dir3, string dir4)
	{
		ssize_t size1;
		ssize_t size2;
		ssize_t size3;
		ssize_t size4;
		unsigned char* data1 = CCFileUtils::getInstance()->getFileData(dir1.c_str(), "rb", &size1);
		unsigned char* data2 = CCFileUtils::getInstance()->getFileData(dir2.c_str(), "rb", &size2);
		unsigned char* data3 = CCFileUtils::getInstance()->getFileData(dir3.c_str(), "rb", &size3);
		unsigned char* data4 = CCFileUtils::getInstance()->getFileData(dir4.c_str(), "rb", &size4);
		string complete = string(reinterpret_cast<char const*>(data1), size1 - 7);
		complete = complete + ',';
		for (int n = 0; n < size2; n++)
		{
			if (data2[n] == 0x5b)
			{
				n++;
				for (; n < size2 - 7; n++)
				{
					complete = complete + static_cast<char>(data2[n]);
				}
			}
		}
		complete = complete + ',';
		for (int n = 0; n < size3 - 7; n++)
		{
			if (data3[n] == 0x5b)
			{
				n++;
				for (; n < size3 - 7; n++)
				{
					complete = complete + static_cast<char>(data3[n]);
				}
			}
		}
		complete = complete + ',';
		for (int n = 0; n < size4; n++)
		{
			if (data4[n] == 0x5b)
			{
				n++;
				for (; n < size4; n++)
				{
					complete = complete + static_cast<char>(data4[n]);
				}
			}
		}
		delete[] data1;
		delete[] data2;
		delete[] data3;
		delete[] data4;
		return(complete);
	});

	string expression = filedata(*dir_expression[expressionID1], *dir_expression[expressionID2], *dir_expression[expressionID3], *dir_expression[expressionID4]);
	ofstream temp("Debug.win32\\temp.json", ios::binary);
	temp.write(expression.c_str(), expression.length());
	temp.close();
	string name_expression = int_to_string(rand()); // каждый раз необходимо создавать уникальное имя
	loadExpression(name_expression.c_str(), "temp.json");
	std::remove("Debug.win32\\temp.json");
	AMotion* motion = expressions[name_expression.c_str()];


	if (LAppDefine::DEBUG_LOG)log("expression[%s]", expressionID1, expressionID2, expressionID3, expressionID4);
	if (motion != NULL)
	{
		expressionMgr->startMotion(motion, false);
	}
	else
	{
		if (LAppDefine::DEBUG_LOG)log("expression[%s] is null ", expressionID1, expressionID2, expressionID3, expressionID4);
	}
}

void LAppModel::setExpression(const char expressionID1[], const char expressionID2[], const char expressionID3[], const char expressionID4[], const char expressionID5[])
{


	auto filedata([=](string dir1, string dir2, string dir3, string dir4, string dir5)
	{
		ssize_t size1;
		ssize_t size2;
		ssize_t size3;
		ssize_t size4;
		ssize_t size5;
		unsigned char* data1 = CCFileUtils::getInstance()->getFileData(dir1.c_str(), "rb", &size1);
		unsigned char* data2 = CCFileUtils::getInstance()->getFileData(dir2.c_str(), "rb", &size2);
		unsigned char* data3 = CCFileUtils::getInstance()->getFileData(dir3.c_str(), "rb", &size3);
		unsigned char* data4 = CCFileUtils::getInstance()->getFileData(dir4.c_str(), "rb", &size4);
		unsigned char* data5 = CCFileUtils::getInstance()->getFileData(dir5.c_str(), "rb", &size5);
		string complete = string(reinterpret_cast<char const*>(data1), size1 - 7);
		complete = complete + ',';
		for (int n = 0; n < size2; n++)
		{
			if (data2[n] == 0x5b)
			{
				n++;
				for (; n < size2 - 7; n++)
				{
					complete = complete + static_cast<char>(data2[n]);
				}
			}
		}
		complete = complete + ',';
		for (int n = 0; n < size3 - 7; n++)
		{
			if (data3[n] == 0x5b)
			{
				n++;
				for (; n < size3 - 7; n++)
				{
					complete = complete + static_cast<char>(data3[n]);
				}
			}
		}
		complete = complete + ',';
		for (int n = 0; n < size4 - 7; n++)
		{
			if (data3[n] == 0x5b)
			{
				n++;
				for (; n < size4 - 7; n++)
				{
					complete = complete + static_cast<char>(data4[n]);
				}
			}
		}
		complete = complete + ',';
		for (int n = 0; n < size5; n++)
		{
			if (data5[n] == 0x5b)
			{
				n++;
				for (; n < size5; n++)
				{
					complete = complete + static_cast<char>(data5[n]);
				}
			}
		}
		delete[] data1;
		delete[] data2;
		delete[] data3;
		delete[] data4;
		delete[] data5;
		return(complete);
	});

	string expression = filedata(*dir_expression[expressionID1], *dir_expression[expressionID2], *dir_expression[expressionID3], *dir_expression[expressionID4], *dir_expression[expressionID5]);
	ofstream temp("Debug.win32\\temp.json", ios::binary);
	temp.write(expression.c_str(), expression.length());
	temp.close();
	string name_expression = int_to_string(rand()); // каждый раз необходимо создавать уникальное имя
	loadExpression(name_expression.c_str(), "temp.json");
	std::remove("Debug.win32\\temp.json");
	AMotion* motion = expressions[name_expression.c_str()];

	motion->setFadeIn(1000);
	motion->setFadeOut(1000);
	if (LAppDefine::DEBUG_LOG)log("expression[%s]", expressionID1, expressionID2, expressionID3, expressionID4, expressionID5);
	if (motion != NULL)
	{
		expressionMgr->startMotion(motion, false);
	}
	else
	{
		if (LAppDefine::DEBUG_LOG)log("expression[%s] is null ", expressionID1, expressionID2, expressionID3, expressionID4, expressionID5);
	}
}
