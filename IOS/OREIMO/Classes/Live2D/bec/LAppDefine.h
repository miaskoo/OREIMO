/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once


// 画面
static const float VIEW_MAX_SCALE = 2.0f;
static const float VIEW_MIN_SCALE = 0.8f;

static const float VIEW_LOGICAL_LEFT = -1;
static const float VIEW_LOGICAL_RIGHT = 1;

static const float VIEW_LOGICAL_MAX_LEFT = -2;
static const float VIEW_LOGICAL_MAX_RIGHT = 2;
static const float VIEW_LOGICAL_MAX_BOTTOM = -2;
static const float VIEW_LOGICAL_MAX_TOP = 2;


// モデル定義------------------------------------------------------------------------
// モデルの後ろにある背景の画像ファイル // Фон за моделью
//static const char BACK_IMAGE_NAME[] = "back_class_normal.png" ;


// モデル定義-----------------------------------------------------------------------
static const int INDEX_MODEL_AYASE = 0;
static const int INDEX_MODEL_KANAKO = 1;
static const int INDEX_MODEL_KIRINO = 2;
static const int INDEX_MODEL_KURONEKO = 3;
static const int INDEX_MODEL_MANAMI = 4;
static const int INDEX_MODEL_SAORI = 5;

static const int INDEX_MODEL_AYASE_MAX = 2;
static const int INDEX_MODEL_KANAKO_MAX = 3;
static const int INDEX_MODEL_KIRINO_MAX = 3;
static const int INDEX_MODEL_KURONEKO_MAX = 2;
static const int INDEX_MODEL_MANAMI_MAX = 2;
static const int INDEX_MODEL_SAORI_MAX = 1;

static const char MODEL_AYASE_DIR[]			= "Resources/Live2D/ayase/";
static const char MODEL_KANAKO_DIR[]		= "Resources/Live2D/kanako/";
static const char MODEL_KIRINO_DIR[]		= "Resources/Live2D/kirino/";
static const char MODEL_KURONEKO_DIR[]		= "Resources/Live2D/kuroneko/";
static const char MODEL_MANAMI_DIR[]		= "Resources/Live2D/manami/";
static const char MODEL_SAORI_DIR[]			= "Resources/Live2D/saori/";


static const char MODEL_AYASE_A[] = "ayase_seifuku.model.json";
static const char MODEL_AYASE_B[] = "ayase_shifuku.model.json";
static const char MODEL_KANAKO_A[] = "kanako_meruru.model.json";
static const char MODEL_KANAKO_B[] = "kanako_shifuku.model.json";
static const char MODEL_KANAKO_C[] = "kanako_shifuku_B.model.json";
static const char MODEL_KIRINO_A[] = "kirino_heyagi.model.json";
static const char MODEL_KIRINO_B[] = "kirino_seifuku.model.json";
static const char MODEL_KIRINO_C[] = "kirino_shifuku.model.json";
static const char MODEL_KURONEKO_A[] = "kuroneko_seifuku.model.json";
static const char MODEL_KURONEKO_B[] = "kuroneko_shifuku.model.json";
static const char MODEL_MANAMI_A[] = "manami_seifuku.model.json";
static const char MODEL_MANAMI_B[] = "manami_shifuku.model.json";
static const char MODEL_SAORI_A[] = "saori_shifuku.model.json";
static const char MODEL_SAORI_B[] = "saori_ojousama.model.json";



// 外部定義ファイル(json)と合わせる
static const char MOTION_GROUP_IDLE[]			="idle";// idle
static const char MOTION_GROUP_ACTION[]			="action";// action

// 外部定義ファイル(json)と合わせる
static const char HIT_AREA_NAME_HEAD[]		="head";
static const char HIT_AREA_NAME_BODY[]		="body";

// モーションの優先度定数 // приоритеты?
static const int PRIORITY_NONE  = 0;
static const int PRIORITY_IDLE = 1;
static const int PRIORITY_NORMAL= 2;
static const int PRIORITY_EXPRESSION = 3;
static const int PRIORITY_FORCE = 4;
// данные матрицы размеров
static const float AYASE_MATRIX_X = -1.4;
static const float AYASE_MATRIX_Y = 1.3;
static const float AYASE_MATRIX_Z = 1;

static const float KANAKO_MATRIX_X = -1.45;
static const float KANAKO_MATRIX_Y = 1.15;
static const float KANAKO_MATRIX_Z = 1;

static const float KIRINO_MATRIX_X = -1.45;
static const float KIRINO_MATRIX_Y = 1.35;
static const float KIRINO_MATRIX_Z = 1;

static const float KURONEKO_MATRIX_X = -1.3;
static const float KURONEKO_MATRIX_Y = 1.15;
static const float KURONEKO_MATRIX_Z = 1.3;

static const float MANAMI_MATRIX_X = -1.4;
static const float MANAMI_MATRIX_Y = 1.3;
static const float MANAMI_MATRIX_Z = 1;

static const float SAORI_MATRIX_X = -1.4;
static const float SAORI_MATRIX_Y = 2.1;
static const float SAORI_MATRIX_Z = 1;

class LAppDefine {
public:
    static const bool DEBUG_LOG=false;// デバッグ用ログの表示
	static const bool DEBUG_TOUCH_LOG=false;
};
