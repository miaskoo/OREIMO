#include "COMMON_DIRS.h"
const string SPRITE_BLINK_DIR = "\\Blink";
const string SPRITE_SPEAK_DIR = "\\Speak";
const string NUMSPRITE_ONE_DIR = "\\Sprite1.png";
const string NUMSPRITE_TWO_DIR = "\\Sprite2.png";
const string NUMSPRITE_THREE_DIR = "\\Sprite3.png";
const string NUMFACE_FOUR_DIR = "\\0004";
const string NUMFACE_FIVE_DIR = "\\0005";
const string NUMFACE_SIX_DIR = "\\0006";
const string NUMFACE_SEVEN_DIR = "\\0007";
const string NUMFACE_EIGHT_DIR = "\\0008";
const string NUMFACE_NINE_DIR = "\\0009";
const string NUMFACE_TEN_DIR = "\\0010";
const string NUMFACE_ELEVEN_DIR = "\\0011";
const string NUMFACE_TWELWE_DIR = "\\0012";
const string NUMFACE_THIRTEEN_DIR = "\\0013";
const string NUMFACE_FOURTEEN_DIR = "\\0014";
const string NUMFACE_FIVETEEN_DIR = "\\0015";
const string NUMFACE_SIXTEEN_DIR = "\\0016";
const string NUMFACE_SEVENTEEN_DIR = "\\0017";
const string NUMFACE_EIGHTTEEN_DIR = "\\0018";
const string NUMFACE_NINETEEN_DIR = "\\0019";
const string NAME_MAP_SPRITE = "SPRITE";
const string NAME_MAP_FACE = "FACE";
const string SPRITE_BLINK_ANIM_DIR[3] {{ "\\Blink1.png" }, { "\\Blink2.png" }, { "\\Blink3.png" }};//имена для картинок анимации моргания везде одни
const string SPRITE_SPEAK_ANIM_DIR[3] {{ "\\Speak1.png" }, { "\\Speak2.png" }, { "\\Speak3.png" }};//имена для картинок анимации говорения везде одни


map <int, string> ALL_FACE_INDEX
{
	{ 4, NUMFACE_FOUR_DIR },
	{ 5, NUMFACE_FIVE_DIR },
	{ 6, NUMFACE_SIX_DIR },
	{ 7, NUMFACE_SEVEN_DIR },
	{ 8, NUMFACE_EIGHT_DIR },
	{ 9, NUMFACE_NINE_DIR },
	{ 10, NUMFACE_TEN_DIR },
	{ 11, NUMFACE_ELEVEN_DIR },
	{ 12, NUMFACE_TWELWE_DIR },
	{ 13, NUMFACE_THIRTEEN_DIR },
	{ 14, NUMFACE_FOURTEEN_DIR },
	{ 15, NUMFACE_FIVETEEN_DIR },
	{ 16, NUMFACE_SIXTEEN_DIR },
	{ 17, NUMFACE_SEVENTEEN_DIR },
	{ 18, NUMFACE_EIGHTTEEN_DIR },
	{ 19, NUMFACE_NINETEEN_DIR },
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const string AY_C_DIR = "\\AY_C";
const string AY_C_YAN_DIR = "\\AY_C_COSP";
const string AY_L_DIR = "\\AY_L";
const string AY_L_YAN_DIR = "\\AY_L_COSP";
const string AY_L_OLD_DIR = "\\AY_L_OLD";
const string AY_R_DIR = "\\AY_R";
const string AY_R_YAN_DIR = "\\AY_R_COSP";
const string AY_R_OLD_DIR = "\\AY_R_OLD";



//AY
//C
// sp 1 2
map<string, string> SPRITE_AY_INDEX_SPRITE_C_DIR{ { "1", AY_C_DIR + NUMSPRITE_ONE_DIR }, { "2", AY_C_DIR + NUMSPRITE_TWO_DIR } };

//4 5 6 7 8 9 10 11 14 15 16 18 19
map<string, string> SPRITE_AY_INDEX_FACE_C_DIR{
	{ "4", AY_C_DIR + ALL_FACE_INDEX[4] },
	{ "5", AY_C_DIR + ALL_FACE_INDEX[5] },
	{ "6", AY_C_DIR + ALL_FACE_INDEX[6] },
	{ "7", AY_C_DIR + ALL_FACE_INDEX[7] },
	{ "8", AY_C_DIR + ALL_FACE_INDEX[8] },
	{ "9", AY_C_DIR + ALL_FACE_INDEX[9] },
	{ "10", AY_C_DIR + ALL_FACE_INDEX[10] },
	{ "11", AY_C_DIR + ALL_FACE_INDEX[11] },
	{ "14", AY_C_DIR + ALL_FACE_INDEX[14] },
	{ "15", AY_C_DIR + ALL_FACE_INDEX[15] },
	{ "16", AY_C_DIR + ALL_FACE_INDEX[16] },
	{ "18", AY_C_DIR + ALL_FACE_INDEX[18] },
	{ "19", AY_C_DIR + ALL_FACE_INDEX[19] }
};
map<string, map<string, string>> SPRITE_AY_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_AY_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_AY_INDEX_FACE_C_DIR }
};
//C_YAN 
// sp 1 2
map<string, string> SPRITE_AY_INDEX_SPRITE_C_YAN_DIR{ { "1", AY_C_YAN_DIR + NUMSPRITE_ONE_DIR }, { "2", AY_C_YAN_DIR + NUMSPRITE_TWO_DIR } };

//4 5 6 7 8 9 10 11 14 15 16 18 19
map<string, string> SPRITE_AY_INDEX_FACE_C_YAN_DIR{
	{ "4", AY_C_YAN_DIR + ALL_FACE_INDEX[4] },
	{ "5", AY_C_YAN_DIR + ALL_FACE_INDEX[5] },
	{ "6", AY_C_YAN_DIR + ALL_FACE_INDEX[6] },
	{ "7", AY_C_YAN_DIR + ALL_FACE_INDEX[7] },
	{ "8", AY_C_YAN_DIR + ALL_FACE_INDEX[8] },
	{ "9", AY_C_YAN_DIR + ALL_FACE_INDEX[9] },
	{ "10", AY_C_YAN_DIR + ALL_FACE_INDEX[10] },
	{ "11", AY_C_YAN_DIR + ALL_FACE_INDEX[11] },
	{ "14", AY_C_YAN_DIR + ALL_FACE_INDEX[14] },
	{ "15", AY_C_YAN_DIR + ALL_FACE_INDEX[15] },
	{ "16", AY_C_YAN_DIR + ALL_FACE_INDEX[16] },
	{ "18", AY_C_YAN_DIR + ALL_FACE_INDEX[18] },
	{ "19", AY_C_YAN_DIR + ALL_FACE_INDEX[19] }
};
map<string, map<string, string>> SPRITE_AY_INDEX_C_YAN
{
	{ NAME_MAP_SPRITE, SPRITE_AY_INDEX_SPRITE_C_YAN_DIR },
	{ NAME_MAP_FACE, SPRITE_AY_INDEX_FACE_C_YAN_DIR }
};
//L 
// sp 1 2  
map<string, string> SPRITE_AY_INDEX_SPRITE_L_DIR{ { "1", AY_L_DIR + NUMSPRITE_ONE_DIR }, { "2", AY_L_DIR + NUMSPRITE_TWO_DIR } };
// 4 5 6 7 8 10 11 14 15 16	18 19 
map<string, string> SPRITE_AY_INDEX_FACE_L_DIR{
	{ "4", AY_L_DIR + ALL_FACE_INDEX[4] },
	{ "5", AY_L_DIR + ALL_FACE_INDEX[5] },
	{ "7", AY_L_DIR + ALL_FACE_INDEX[7] },
	{ "8", AY_L_DIR + ALL_FACE_INDEX[8] },
	{ "10", AY_L_DIR + ALL_FACE_INDEX[10] },
	{ "11", AY_L_DIR + ALL_FACE_INDEX[11] },
	{ "14", AY_L_DIR + ALL_FACE_INDEX[14] },
	{ "15", AY_L_DIR + ALL_FACE_INDEX[15] },
	{ "16", AY_L_DIR + ALL_FACE_INDEX[16] },
	{ "18", AY_L_DIR + ALL_FACE_INDEX[18] },
	{ "19", AY_L_DIR + ALL_FACE_INDEX[19] }
};
map<string, map<string, string>> SPRITE_AY_INDEX_L
{
	{ NAME_MAP_SPRITE, SPRITE_AY_INDEX_SPRITE_L_DIR },
	{ NAME_MAP_FACE, SPRITE_AY_INDEX_FACE_L_DIR }
};
//L_YAN  
// sp 1 2  
map<string, string> SPRITE_AY_INDEX_SPRITE_L_YAN_DIR{ { "1", AY_L_YAN_DIR + NUMSPRITE_ONE_DIR }, { "2", AY_L_YAN_DIR + NUMSPRITE_TWO_DIR } };
// 4 5 6 7 8 10 11 14 15 16 18 19 
map<string, string> SPRITE_AY_INDEX_FACE_L_YAN_DIR{
	{ "4", AY_L_YAN_DIR + ALL_FACE_INDEX[4] },
	{ "5", AY_L_YAN_DIR + ALL_FACE_INDEX[5] },
	{ "7", AY_L_YAN_DIR + ALL_FACE_INDEX[7] },
	{ "8", AY_L_YAN_DIR + ALL_FACE_INDEX[8] },
	{ "10", AY_L_YAN_DIR + ALL_FACE_INDEX[10] },
	{ "11", AY_L_YAN_DIR + ALL_FACE_INDEX[11] },
	{ "14", AY_L_YAN_DIR + ALL_FACE_INDEX[14] },
	{ "15", AY_L_YAN_DIR + ALL_FACE_INDEX[15] },
	{ "16", AY_L_YAN_DIR + ALL_FACE_INDEX[16] },
	{ "18", AY_L_YAN_DIR + ALL_FACE_INDEX[18] },
	{ "19", AY_L_YAN_DIR + ALL_FACE_INDEX[19] }
};
map<string, map<string, string>> SPRITE_AY_INDEX_L_YAN
{
	{ NAME_MAP_SPRITE, SPRITE_AY_INDEX_SPRITE_L_YAN_DIR },
	{ NAME_MAP_FACE, SPRITE_AY_INDEX_FACE_L_YAN_DIR }
};
//L_OLD
// sp 2
map<string, string> SPRITE_AY_INDEX_SPRITE_L_OLD_DIR{ { "1", AY_L_OLD_DIR + NUMSPRITE_TWO_DIR } };

// 8 
map<string, string> SPRITE_AY_INDEX_FACE_L_OLD_DIR{
	{ "8", AY_L_OLD_DIR + ALL_FACE_INDEX[8] }
};
map<string, map<string, string>> SPRITE_AY_INDEX_L_OLD
{
	{ NAME_MAP_SPRITE, SPRITE_AY_INDEX_SPRITE_L_OLD_DIR },
	{ NAME_MAP_FACE, SPRITE_AY_INDEX_FACE_L_OLD_DIR }
};
//R 
// sp 1 2 
map<string, string> SPRITE_AY_INDEX_SPRITE_R_DIR{ { "1", AY_R_DIR + NUMSPRITE_ONE_DIR }, { "2", AY_R_DIR + NUMSPRITE_TWO_DIR } };
// 4 5 6 7 8 9 10 14 15 16 18 19
map<string, string> SPRITE_AY_INDEX_FACE_R_DIR{
	{ "4", AY_R_DIR + ALL_FACE_INDEX[4] },
	{ "5", AY_R_DIR + ALL_FACE_INDEX[5] },
	{ "6", AY_R_DIR + ALL_FACE_INDEX[6] },
	{ "7", AY_R_DIR + ALL_FACE_INDEX[7] },
	{ "8", AY_R_DIR + ALL_FACE_INDEX[8] },
	{ "9", AY_R_DIR + ALL_FACE_INDEX[9] },
	{ "10", AY_R_DIR + ALL_FACE_INDEX[10] },
	{ "14", AY_R_DIR + ALL_FACE_INDEX[14] },
	{ "15", AY_R_DIR + ALL_FACE_INDEX[15] },
	{ "16", AY_R_DIR + ALL_FACE_INDEX[16] },
	{ "18", AY_R_DIR + ALL_FACE_INDEX[18] },
	{ "19", AY_R_DIR + ALL_FACE_INDEX[19] }
};
map<string, map<string, string>> SPRITE_AY_INDEX_R
{
	{ NAME_MAP_SPRITE, SPRITE_AY_INDEX_SPRITE_R_DIR },
	{ NAME_MAP_FACE, SPRITE_AY_INDEX_FACE_R_DIR }
};
//R_YAN 
// sp 1 2 
map<string, string> SPRITE_AY_INDEX_SPRITE_R_YAN_DIR{ { "1", AY_R_YAN_DIR + NUMSPRITE_ONE_DIR }, { "2", AY_R_YAN_DIR + NUMSPRITE_TWO_DIR } };
// 4 5 6 7 8 9 10 14 15 16 18 19 
map<string, string> SPRITE_AY_INDEX_FACE_R_YAN_DIR{
	{ "4", AY_R_YAN_DIR + ALL_FACE_INDEX[4] },
	{ "5", AY_R_YAN_DIR + ALL_FACE_INDEX[5] },
	{ "6", AY_R_YAN_DIR + ALL_FACE_INDEX[6] },
	{ "7", AY_R_YAN_DIR + ALL_FACE_INDEX[7] },
	{ "8", AY_R_YAN_DIR + ALL_FACE_INDEX[8] },
	{ "9", AY_R_YAN_DIR + ALL_FACE_INDEX[9] },
	{ "10", AY_R_YAN_DIR + ALL_FACE_INDEX[10] },
	{ "14", AY_R_YAN_DIR + ALL_FACE_INDEX[14] },
	{ "15", AY_R_YAN_DIR + ALL_FACE_INDEX[15] },
	{ "16", AY_R_YAN_DIR + ALL_FACE_INDEX[16] },
	{ "18", AY_R_YAN_DIR + ALL_FACE_INDEX[18] },
	{ "19", AY_R_YAN_DIR + ALL_FACE_INDEX[19] }
};
map<string, map<string, string>> SPRITE_AY_INDEX_R_YAN
{
	{ NAME_MAP_SPRITE, SPRITE_AY_INDEX_SPRITE_R_YAN_DIR },
	{ NAME_MAP_FACE, SPRITE_AY_INDEX_FACE_R_YAN_DIR }
};
//R_OLD 
// sp 2
map<string, string> SPRITE_AY_INDEX_SPRITE_R_OLD_DIR{ { "2", AY_R_OLD_DIR + NUMSPRITE_TWO_DIR } };
// 7 
map<string, string> SPRITE_AY_INDEX_FACE_R_OLD_DIR{
	{ "7", AY_R_OLD_DIR + ALL_FACE_INDEX[7] }
};
map<string, map<string, string>> SPRITE_AY_INDEX_R_OLD
{
	{ NAME_MAP_SPRITE, SPRITE_AY_INDEX_SPRITE_R_OLD_DIR },
	{ NAME_MAP_FACE, SPRITE_AY_INDEX_FACE_R_OLD_DIR }
};
map<string, map<string, map<string, string>>> SPRITE_AY_DIR
{
	{ "C", SPRITE_AY_INDEX_C },
	{ "C_COSP", SPRITE_AY_INDEX_C_YAN },
	{ "L", SPRITE_AY_INDEX_L },
	{ "L_OLD", SPRITE_AY_INDEX_L_OLD },
	{ "L_COSP", SPRITE_AY_INDEX_L_YAN },
	{ "R", SPRITE_AY_INDEX_R },
	{ "R_OLD", SPRITE_AY_INDEX_R_OLD },
	{ "R_COSP", SPRITE_AY_INDEX_R_YAN }

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const string DA_C_DIR = "\\DA_C";
const string DA_C_OLD_DIR = "\\DA_C_OLD";

//DA
//C
map<string, string> SPRITE_DA_INDEX_SPRITE_C_DIR{ { "1", DA_C_DIR + NUMSPRITE_ONE_DIR } };

map<string, string> SPRITE_DA_INDEX_FACE_C_DIR{
	{ "6", DA_C_DIR + ALL_FACE_INDEX[6] },
	{ "7", DA_C_DIR + ALL_FACE_INDEX[7] },
	{ "8", DA_C_DIR + ALL_FACE_INDEX[8] },
	{ "15", DA_C_DIR + ALL_FACE_INDEX[15] },
	{ "16", DA_C_DIR + ALL_FACE_INDEX[16] }
};
map<string, map<string, string>> SPRITE_DA_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_DA_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_DA_INDEX_FACE_C_DIR }
};

//C_OLD
map<string, string> SPRITE_DA_INDEX_SPRITE_C_OLD_DIR{ { "1", DA_C_OLD_DIR + NUMSPRITE_ONE_DIR } };

map<string, string> SPRITE_DA_INDEX_FACE_C_OLD_DIR{
	{ "7", DA_C_OLD_DIR + ALL_FACE_INDEX[7] },
	{ "8", DA_C_OLD_DIR + ALL_FACE_INDEX[8] }
};

map<string, map<string, string>> SPRITE_DA_INDEX_C_OLD
{
	{ NAME_MAP_SPRITE, SPRITE_DA_INDEX_SPRITE_C_OLD_DIR },
	{ NAME_MAP_FACE, SPRITE_DA_INDEX_FACE_C_OLD_DIR }
};

map<string, map<string, map<string, string>>> SPRITE_DA_DIR{
	{ "C", SPRITE_DA_INDEX_C },
	{ "C_OLD", SPRITE_DA_INDEX_C_OLD },
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const string KI_C_DIR = "\\KI_C";
const string KI_C_OLD_DIR = "\\KI_C_OLD";
const string KI_L_DIR = "\\KI_L";
const string KI_L_OLD_DIR = "\\KI_L_OLD";
const string KI_R_DIR = "\\KI_R";
const string KI_R_OLD_DIR = "\\KI_R_OLD";

//KI
//C
map<string, string> SPRITE_KI_INDEX_SPRITE_C_DIR{ { "1", KI_C_DIR + NUMSPRITE_ONE_DIR }, { "2", KI_C_DIR + NUMSPRITE_TWO_DIR }, { "3", KI_C_DIR + NUMSPRITE_THREE_DIR } };

//c 4 5 6 7 8 9 10 12 13 14 15 16 18 19
map<string, string> SPRITE_KI_INDEX_FACE_C_DIR{
	{ "4", KI_C_DIR + ALL_FACE_INDEX[4] },
	{ "5", KI_C_DIR + ALL_FACE_INDEX[5] },
	{ "6", KI_C_DIR + ALL_FACE_INDEX[6] },
	{ "7", KI_C_DIR + ALL_FACE_INDEX[7] },
	{ "8", KI_C_DIR + ALL_FACE_INDEX[8] },
	{ "9", KI_C_DIR + ALL_FACE_INDEX[9] },
	{ "10", KI_C_DIR + ALL_FACE_INDEX[10] },
	{ "12", KI_C_DIR + ALL_FACE_INDEX[12] },
	{ "13", KI_C_DIR + ALL_FACE_INDEX[13] },
	{ "14", KI_C_DIR + ALL_FACE_INDEX[14] },
	{ "15", KI_C_DIR + ALL_FACE_INDEX[15] },
	{ "16", KI_C_DIR + ALL_FACE_INDEX[16] },
	{ "18", KI_C_DIR + ALL_FACE_INDEX[18] },
	{ "19", KI_C_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KI_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_KI_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_KI_INDEX_FACE_C_DIR }

};
//C_OLD
//sp 1 3
map<string, string> SPRITE_KI_INDEX_SPRITE_C_OLD_DIR{ { "1", KI_C_OLD_DIR + NUMSPRITE_ONE_DIR }, { "3", KI_C_OLD_DIR + NUMSPRITE_THREE_DIR } };
//c old 6 7 9 13 
map<string, string> SPRITE_KI_INDEX_FACE_C_OLD_DIR{
	{ "6", KI_C_OLD_DIR + ALL_FACE_INDEX[6] },
	{ "7", KI_C_OLD_DIR + ALL_FACE_INDEX[7] },
	{ "9", KI_C_OLD_DIR + ALL_FACE_INDEX[9] },
	{ "13", KI_C_OLD_DIR + ALL_FACE_INDEX[13] }
};
map<string, map<string, string>> SPRITE_KI_INDEX_C_OLD
{
	{ NAME_MAP_SPRITE, SPRITE_KI_INDEX_SPRITE_C_OLD_DIR },
	{ NAME_MAP_FACE, SPRITE_KI_INDEX_FACE_C_OLD_DIR }

};
//L
// sp 1 2 3
map<string, string> SPRITE_KI_INDEX_SPRITE_L_DIR{ { "1", KI_L_DIR + NUMSPRITE_ONE_DIR }, { "2", KI_L_DIR + NUMSPRITE_TWO_DIR }, { "3", KI_L_DIR + NUMSPRITE_THREE_DIR } };
//l 4 5 6 7 8 9 13 14 15 18 19
map<string, string> SPRITE_KI_INDEX_FACE_L_DIR{
	{ "4", KI_L_DIR + ALL_FACE_INDEX[4] },
	{ "5", KI_L_DIR + ALL_FACE_INDEX[5] },
	{ "6", KI_L_DIR + ALL_FACE_INDEX[6] },
	{ "7", KI_L_DIR + ALL_FACE_INDEX[7] },
	{ "8", KI_L_DIR + ALL_FACE_INDEX[8] },
	{ "9", KI_L_DIR + ALL_FACE_INDEX[9] },
	{ "13", KI_L_DIR + ALL_FACE_INDEX[13] },
	{ "14", KI_L_DIR + ALL_FACE_INDEX[14] },
	{ "15", KI_L_DIR + ALL_FACE_INDEX[15] },
	{ "18", KI_L_DIR + ALL_FACE_INDEX[18] },
	{ "19", KI_L_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KI_INDEX_L
{
	{ NAME_MAP_SPRITE, SPRITE_KI_INDEX_SPRITE_L_DIR },
	{ NAME_MAP_FACE, SPRITE_KI_INDEX_FACE_L_DIR }

};
//L_OLD
// sp 1
map<string, string> SPRITE_KI_INDEX_SPRITE_L_OLD_DIR{ { "1", KI_L_OLD_DIR + NUMSPRITE_ONE_DIR } };
// l old 13 
map<string, string>	SPRITE_KI_INDEX_FACE_L_OLD_DIR{
	{ "13", KI_L_OLD_DIR + NUMFACE_THIRTEEN_DIR }
};

map<string, map<string, string>> SPRITE_KI_INDEX_L_OLD
{
	{ NAME_MAP_SPRITE, SPRITE_KI_INDEX_SPRITE_L_OLD_DIR },
	{ NAME_MAP_FACE, SPRITE_KI_INDEX_FACE_L_OLD_DIR }

};
//R
//sp 1 2 3
map<string, string> SPRITE_KI_INDEX_SPRITE_R_DIR{ { "1", KI_R_DIR + NUMSPRITE_ONE_DIR }, { "2", KI_R_DIR + NUMSPRITE_TWO_DIR }, { "3", KI_R_DIR + NUMSPRITE_THREE_DIR } };
//r 4 5 6 7 8 9 10 11 15 16 18 19 
map<string, string> SPRITE_KI_INDEX_FACE_R_DIR{
	{ "4", KI_R_DIR + ALL_FACE_INDEX[4] },
	{ "5", KI_R_DIR + ALL_FACE_INDEX[5] },
	{ "6", KI_R_DIR + ALL_FACE_INDEX[6] },
	{ "7", KI_R_DIR + ALL_FACE_INDEX[7] },
	{ "8", KI_R_DIR + ALL_FACE_INDEX[8] },
	{ "9", KI_R_DIR + ALL_FACE_INDEX[9] },
	{ "10", KI_R_DIR + ALL_FACE_INDEX[10] },
	{ "11", KI_R_DIR + ALL_FACE_INDEX[11] },
	{ "15", KI_R_DIR + ALL_FACE_INDEX[15] },
	{ "16", KI_R_DIR + ALL_FACE_INDEX[16] },
	{ "18", KI_R_DIR + ALL_FACE_INDEX[18] },
	{ "19", KI_R_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KI_INDEX_R
{
	{ NAME_MAP_SPRITE, SPRITE_KI_INDEX_SPRITE_R_DIR },
	{ NAME_MAP_FACE, SPRITE_KI_INDEX_FACE_R_DIR }
};

//R_OLD
// sp 2 3 
map<string, string> SPRITE_KI_INDEX_SPRITE_R_OLD_DIR{ { "2", KI_R_OLD_DIR + NUMSPRITE_TWO_DIR }, { "3", KI_R_OLD_DIR + NUMSPRITE_THREE_DIR } };

//r old 4 5 6 9 10 
map<string, string> SPRITE_KI_INDEX_FACE_R_OLD_DIR{
	{ "4", KI_R_OLD_DIR + ALL_FACE_INDEX[4] },
	{ "5", KI_R_OLD_DIR + ALL_FACE_INDEX[5] },
	{ "6", KI_R_OLD_DIR + ALL_FACE_INDEX[6] },
	{ "9", KI_R_OLD_DIR + ALL_FACE_INDEX[9] },
	{ "10", KI_R_OLD_DIR + ALL_FACE_INDEX[10] }
};

map<string, map<string, string>> SPRITE_KI_INDEX_R_OLD
{
	{ NAME_MAP_SPRITE, SPRITE_KI_INDEX_SPRITE_R_OLD_DIR },
	{ NAME_MAP_FACE, SPRITE_KI_INDEX_FACE_R_OLD_DIR }
};

map<string, map<string, map<string, string>>> SPRITE_KI_DIR
{
	{ "C", SPRITE_KI_INDEX_C },
	{ "C_OLD", SPRITE_KI_INDEX_C_OLD },
	{ "L", SPRITE_KI_INDEX_L },
	{ "L_OLD", SPRITE_KI_INDEX_L_OLD },
	{ "R", SPRITE_KI_INDEX_R },
	{ "R_OLD", SPRITE_KI_INDEX_R_OLD }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string AK_C_DIR = "\\AK_C";
const string AK_L_DIR = "\\AK_L";

//AK
//C
map<string, string> SPRITE_AK_INDEX_SPRITE_C_DIR{ { "1", AK_C_DIR + NUMSPRITE_ONE_DIR }, { "2", AK_C_DIR + NUMSPRITE_TWO_DIR }};

//C 4 6 7 10 12 13 14 15 16
map<string, string> SPRITE_AK_INDEX_FACE_C_DIR{
	{ "4", AK_C_DIR + ALL_FACE_INDEX[4] },
	{ "6", AK_C_DIR + ALL_FACE_INDEX[6] },
	{ "7", AK_C_DIR + ALL_FACE_INDEX[7] },
	{ "10", AK_C_DIR + ALL_FACE_INDEX[10] },
	{ "12", AK_C_DIR + ALL_FACE_INDEX[12] },
	{ "13", AK_C_DIR + ALL_FACE_INDEX[13] },
	{ "14", AK_C_DIR + ALL_FACE_INDEX[14] },
	{ "15", AK_C_DIR + ALL_FACE_INDEX[15] },
	{ "16", AK_C_DIR + ALL_FACE_INDEX[16] }
};

map<string, map<string, string>> SPRITE_AK_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_AK_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_AK_INDEX_FACE_C_DIR }
};

//L
map<string, string> SPRITE_AK_INDEX_SPRITE_L_DIR{ { "1", AK_L_DIR + NUMSPRITE_ONE_DIR }, { "2", AK_L_DIR + NUMSPRITE_TWO_DIR } };

//l 4 6 7 10 12 13 14 15 16
map<string, string> SPRITE_AK_INDEX_FACE_L_DIR{
	{ "4", AK_L_DIR + ALL_FACE_INDEX[4] },
	{ "6", AK_L_DIR + ALL_FACE_INDEX[6] },
	{ "7", AK_L_DIR + ALL_FACE_INDEX[7] },
	{ "10", AK_L_DIR + ALL_FACE_INDEX[10] },
	{ "12", AK_L_DIR + ALL_FACE_INDEX[12] },
	{ "13", AK_L_DIR + ALL_FACE_INDEX[13] },
	{ "14", AK_L_DIR + ALL_FACE_INDEX[14] },
	{ "15", AK_L_DIR + ALL_FACE_INDEX[15] },
	{ "16", AK_L_DIR + ALL_FACE_INDEX[16] }
};

map<string, map<string, string>> SPRITE_AK_INDEX_L
{
	{ NAME_MAP_SPRITE, SPRITE_AK_INDEX_SPRITE_L_DIR },
	{ NAME_MAP_FACE, SPRITE_AK_INDEX_FACE_L_DIR }
};

map<string, map<string, map<string, string>>> SPRITE_AK_DIR
{
	{ "C", SPRITE_AK_INDEX_C },
	{ "L", SPRITE_AK_INDEX_L },
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const string KA_C_DIR = "\\KA_C";
const string KA_C_COSP_DIR = "\\KA_C_COSP";
const string KA_R_DIR = "\\KA_R";
const string KA_R_COSP_DIR = "\\KA_R_COSP";


//AK
//C
map<string, string> SPRITE_KA_INDEX_SPRITE_C_DIR{ { "1", KA_C_DIR + NUMSPRITE_ONE_DIR }, { "2", KA_C_DIR + NUMSPRITE_TWO_DIR } };

//C 4 5 6 7 8 10 14 15 16 18 19
map<string, string> SPRITE_KA_INDEX_FACE_C_DIR{
	{ "4", KA_C_DIR + ALL_FACE_INDEX[4] },
	{ "5", KA_C_DIR + ALL_FACE_INDEX[5] },
	{ "6", KA_C_DIR + ALL_FACE_INDEX[6] },
	{ "7", KA_C_DIR + ALL_FACE_INDEX[7] },
	{ "8", KA_C_DIR + ALL_FACE_INDEX[8] },
	{ "10", KA_C_DIR + ALL_FACE_INDEX[10] },
	{ "14", KA_C_DIR + ALL_FACE_INDEX[14] },
	{ "15", KA_C_DIR + ALL_FACE_INDEX[15] },
	{ "16", KA_C_DIR + ALL_FACE_INDEX[16] },
	{ "18", KA_C_DIR + ALL_FACE_INDEX[18] },
	{ "19", KA_C_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KA_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_KA_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_KA_INDEX_FACE_C_DIR }
};



//C_COSP
map<string, string> SPRITE_KA_INDEX_SPRITE_C_COSP_DIR{ { "1", KA_C_COSP_DIR + NUMSPRITE_ONE_DIR } };

//C_COSP 4 5 6 7 8 10 14 15 16 18 19
map<string, string> SPRITE_KA_INDEX_FACE_C_COSP_DIR{
	{ "4", KA_C_COSP_DIR + ALL_FACE_INDEX[4] },
	{ "5", KA_C_COSP_DIR + ALL_FACE_INDEX[5] },
	{ "6", KA_C_COSP_DIR + ALL_FACE_INDEX[6] },
	{ "7", KA_C_COSP_DIR + ALL_FACE_INDEX[7] },
	{ "8", KA_C_COSP_DIR + ALL_FACE_INDEX[8] },
	{ "10", KA_C_COSP_DIR + ALL_FACE_INDEX[10] },
	{ "14", KA_C_COSP_DIR + ALL_FACE_INDEX[14] },
	{ "15", KA_C_COSP_DIR + ALL_FACE_INDEX[15] },
	{ "16", KA_C_COSP_DIR + ALL_FACE_INDEX[16] },
	{ "18", KA_C_COSP_DIR + ALL_FACE_INDEX[18] },
	{ "19", KA_C_COSP_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KA_INDEX_C_COSP
{
	{ NAME_MAP_SPRITE, SPRITE_KA_INDEX_SPRITE_C_COSP_DIR },
	{ NAME_MAP_FACE, SPRITE_KA_INDEX_FACE_C_COSP_DIR }
};



//R
map<string, string> SPRITE_KA_INDEX_SPRITE_R_DIR{ { "1", KA_R_DIR + NUMSPRITE_ONE_DIR } };

//R 4 5 6 7 8 10 14 15 16 18 19
map<string, string> SPRITE_KA_INDEX_FACE_R_DIR{
	{ "4", KA_R_DIR + ALL_FACE_INDEX[4] },
	{ "5", KA_R_DIR + ALL_FACE_INDEX[5] },
	{ "6", KA_R_DIR + ALL_FACE_INDEX[6] },
	{ "7", KA_R_DIR + ALL_FACE_INDEX[7] },
	{ "8", KA_R_DIR + ALL_FACE_INDEX[8] },
	{ "10", KA_R_DIR + ALL_FACE_INDEX[10] },
	{ "14", KA_R_DIR + ALL_FACE_INDEX[14] },
	{ "15", KA_R_DIR + ALL_FACE_INDEX[15] },
	{ "16", KA_R_DIR + ALL_FACE_INDEX[16] },
	{ "18", KA_R_DIR + ALL_FACE_INDEX[18] },
	{ "19", KA_R_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KA_INDEX_R
{
	{ NAME_MAP_SPRITE, SPRITE_KA_INDEX_SPRITE_R_DIR },
	{ NAME_MAP_FACE, SPRITE_KA_INDEX_FACE_R_DIR }
};



//R_COSP
map<string, string> SPRITE_KA_INDEX_SPRITE_R_COSP_DIR{ { "1", KA_R_COSP_DIR + NUMSPRITE_ONE_DIR } };

//R_COSP 4 5 6 7 8 10 14 15 16 18 19
map<string, string> SPRITE_KA_INDEX_FACE_R_COSP_DIR{
	{ "4", KA_R_COSP_DIR + ALL_FACE_INDEX[4] },
	{ "5", KA_R_COSP_DIR + ALL_FACE_INDEX[5] },
	{ "6", KA_R_COSP_DIR + ALL_FACE_INDEX[6] },
	{ "7", KA_R_COSP_DIR + ALL_FACE_INDEX[7] },
	{ "8", KA_R_COSP_DIR + ALL_FACE_INDEX[8] },
	{ "10", KA_R_COSP_DIR + ALL_FACE_INDEX[10] },
	{ "14", KA_R_COSP_DIR + ALL_FACE_INDEX[14] },
	{ "15", KA_R_COSP_DIR + ALL_FACE_INDEX[15] },
	{ "16", KA_R_COSP_DIR + ALL_FACE_INDEX[16] },
	{ "18", KA_R_COSP_DIR + ALL_FACE_INDEX[18] },
	{ "19", KA_R_COSP_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KA_INDEX_R_COSP
{
	{ NAME_MAP_SPRITE, SPRITE_KA_INDEX_SPRITE_R_COSP_DIR },
	{ NAME_MAP_FACE, SPRITE_KA_INDEX_FACE_R_COSP_DIR }
};


map<string, map<string, map<string, string>>> SPRITE_KA_DIR
{
	{ "C", SPRITE_KA_INDEX_C },
	{ "C_COSP", SPRITE_KA_INDEX_C_COSP },
	{ "R", SPRITE_KA_INDEX_R },
	{ "R_COSP", SPRITE_KA_INDEX_R_COSP },
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const string KU_C_DIR = "\\KU_C";
const string KU_C_COSP_DIR = "\\KU_C_COSP";
const string KU_L_DIR = "\\KU_L";
const string KU_L_COSP_DIR = "\\KU_L_COSP";
const string KU_R_DIR = "\\KU_R";
const string KU_R_COSP_DIR = "\\KU_R_COSP";

//KU
//C
map<string, string> SPRITE_KU_INDEX_SPRITE_C_DIR{ { "1", KU_C_DIR + NUMSPRITE_ONE_DIR }};

//C 4 5 6 7 8 9 10 11 14 15 16 17 18 19
map<string, string> SPRITE_KU_INDEX_FACE_C_DIR{
	{ "4", KU_C_DIR + ALL_FACE_INDEX[4] },
	{ "5", KU_C_DIR + ALL_FACE_INDEX[5] },
	{ "6", KU_C_DIR + ALL_FACE_INDEX[6] },
	{ "7", KU_C_DIR + ALL_FACE_INDEX[7] },
	{ "8", KU_C_DIR + ALL_FACE_INDEX[8] },
	{ "9", KU_C_DIR + ALL_FACE_INDEX[9] },
	{ "10", KU_C_DIR + ALL_FACE_INDEX[10] },
	{ "11", KU_C_DIR + ALL_FACE_INDEX[11] },
	{ "14", KU_C_DIR + ALL_FACE_INDEX[14] },
	{ "15", KU_C_DIR + ALL_FACE_INDEX[15] },
	{ "16", KU_C_DIR + ALL_FACE_INDEX[16] },
	{ "17", KU_C_DIR + ALL_FACE_INDEX[17] },
	{ "18", KU_C_DIR + ALL_FACE_INDEX[18] },
	{ "19", KU_C_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KU_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_KU_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_KU_INDEX_FACE_C_DIR }
};


//C_COSP
map<string, string> SPRITE_KU_INDEX_SPRITE_C_COSP_DIR{ { "1", KU_C_COSP_DIR + NUMSPRITE_ONE_DIR } };

//C 4 5 6 7 8 9 10 11 14 15 16 17 18 19
map<string, string> SPRITE_KU_INDEX_FACE_C_COSP_DIR{
	{ "4", KU_C_COSP_DIR + ALL_FACE_INDEX[4] },
	{ "5", KU_C_COSP_DIR + ALL_FACE_INDEX[5] },
	{ "6", KU_C_COSP_DIR + ALL_FACE_INDEX[6] },
	{ "7", KU_C_COSP_DIR + ALL_FACE_INDEX[7] },
	{ "8", KU_C_COSP_DIR + ALL_FACE_INDEX[8] },
	{ "9", KU_C_COSP_DIR + ALL_FACE_INDEX[9] },
	{ "10", KU_C_COSP_DIR + ALL_FACE_INDEX[10] },
	{ "11", KU_C_COSP_DIR + ALL_FACE_INDEX[11] },
	{ "14", KU_C_COSP_DIR + ALL_FACE_INDEX[14] },
	{ "15", KU_C_COSP_DIR + ALL_FACE_INDEX[15] },
	{ "16", KU_C_COSP_DIR + ALL_FACE_INDEX[16] },
	{ "17", KU_C_COSP_DIR + ALL_FACE_INDEX[17] },
	{ "18", KU_C_COSP_DIR + ALL_FACE_INDEX[18] },
	{ "19", KU_C_COSP_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KU_INDEX_C_COSP
{
	{ NAME_MAP_SPRITE, SPRITE_KU_INDEX_SPRITE_C_COSP_DIR },
	{ NAME_MAP_FACE, SPRITE_KU_INDEX_FACE_C_COSP_DIR }
};


//L
map<string, string> SPRITE_KU_INDEX_SPRITE_L_DIR{ { "1", KU_L_DIR + NUMSPRITE_ONE_DIR } };

//L 4 5 6 7 8 9 10 11 12 15 16 17 18 19
map<string, string> SPRITE_KU_INDEX_FACE_L_DIR{
	{ "4", KU_L_DIR + ALL_FACE_INDEX[4] },
	{ "5", KU_L_DIR + ALL_FACE_INDEX[5] },
	{ "6", KU_L_DIR + ALL_FACE_INDEX[6] },
	{ "7", KU_L_DIR + ALL_FACE_INDEX[7] },
	{ "8", KU_L_DIR + ALL_FACE_INDEX[8] },
	{ "9", KU_L_DIR + ALL_FACE_INDEX[9] },
	{ "10", KU_L_DIR + ALL_FACE_INDEX[10] },
	{ "11", KU_L_DIR + ALL_FACE_INDEX[11] },
	{ "12", KU_L_DIR + ALL_FACE_INDEX[12] },
	{ "15", KU_L_DIR + ALL_FACE_INDEX[15] },
	{ "16", KU_L_DIR + ALL_FACE_INDEX[16] },
	{ "17", KU_L_DIR + ALL_FACE_INDEX[17] },
	{ "18", KU_L_DIR + ALL_FACE_INDEX[18] },
	{ "19", KU_L_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KU_INDEX_L
{
	{ NAME_MAP_SPRITE, SPRITE_KU_INDEX_SPRITE_L_DIR },
	{ NAME_MAP_FACE, SPRITE_KU_INDEX_FACE_L_DIR }
};



//L_COSP
map<string, string> SPRITE_KU_INDEX_SPRITE_L_COSP_DIR{ { "1", KU_L_COSP_DIR + NUMSPRITE_ONE_DIR } };

//L 4 5 6 7 8 9 10 11 12 15 16 17 18 19
map<string, string> SPRITE_KU_INDEX_FACE_L_COSP_DIR{
	{ "4", KU_L_COSP_DIR + ALL_FACE_INDEX[4] },
	{ "5", KU_L_COSP_DIR + ALL_FACE_INDEX[5] },
	{ "6", KU_L_COSP_DIR + ALL_FACE_INDEX[6] },
	{ "7", KU_L_COSP_DIR + ALL_FACE_INDEX[7] },
	{ "8", KU_L_COSP_DIR + ALL_FACE_INDEX[8] },
	{ "9", KU_L_COSP_DIR + ALL_FACE_INDEX[9] },
	{ "10", KU_L_COSP_DIR + ALL_FACE_INDEX[10] },
	{ "11", KU_L_COSP_DIR + ALL_FACE_INDEX[11] },
	{ "12", KU_L_COSP_DIR + ALL_FACE_INDEX[12] },
	{ "15", KU_L_COSP_DIR + ALL_FACE_INDEX[15] },
	{ "16", KU_L_COSP_DIR + ALL_FACE_INDEX[16] },
	{ "17", KU_L_COSP_DIR + ALL_FACE_INDEX[17] },
	{ "18", KU_L_COSP_DIR + ALL_FACE_INDEX[18] },
	{ "19", KU_L_COSP_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KU_INDEX_L_COSP
{
	{ NAME_MAP_SPRITE, SPRITE_KU_INDEX_SPRITE_L_COSP_DIR },
	{ NAME_MAP_FACE, SPRITE_KU_INDEX_FACE_L_COSP_DIR }
};

//R
map<string, string> SPRITE_KU_INDEX_SPRITE_R_DIR{ { "1", KU_R_DIR + NUMSPRITE_ONE_DIR } };

//R 4 5 6 7 8 14 15 16 18 19
map<string, string> SPRITE_KU_INDEX_FACE_R_DIR{
	{ "4", KU_R_DIR + ALL_FACE_INDEX[4] },
	{ "5", KU_R_DIR + ALL_FACE_INDEX[5] },
	{ "6", KU_R_DIR + ALL_FACE_INDEX[6] },
	{ "7", KU_R_DIR + ALL_FACE_INDEX[7] },
	{ "8", KU_R_DIR + ALL_FACE_INDEX[8] },
	{ "14", KU_R_DIR + ALL_FACE_INDEX[14] },
	{ "15", KU_R_DIR + ALL_FACE_INDEX[15] },
	{ "16", KU_R_DIR + ALL_FACE_INDEX[16] },
	{ "18", KU_R_DIR + ALL_FACE_INDEX[18] },
	{ "19", KU_R_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KU_INDEX_R
{
	{ NAME_MAP_SPRITE, SPRITE_KU_INDEX_SPRITE_R_DIR },
	{ NAME_MAP_FACE, SPRITE_KU_INDEX_FACE_R_DIR }
};


//R_COSP
map<string, string> SPRITE_KU_INDEX_SPRITE_R_COSP_DIR{ { "1", KU_R_COSP_DIR + NUMSPRITE_ONE_DIR } };

//R_COSP 4 5 6 7 8 14 15 16 18 19
map<string, string> SPRITE_KU_INDEX_FACE_R_COSP_DIR{
	{ "4", KU_R_COSP_DIR + ALL_FACE_INDEX[4] },
	{ "5", KU_R_COSP_DIR + ALL_FACE_INDEX[5] },
	{ "6", KU_R_COSP_DIR + ALL_FACE_INDEX[6] },
	{ "7", KU_R_COSP_DIR + ALL_FACE_INDEX[7] },
	{ "8", KU_R_COSP_DIR + ALL_FACE_INDEX[8] },
	{ "14", KU_R_COSP_DIR + ALL_FACE_INDEX[14] },
	{ "15", KU_R_COSP_DIR + ALL_FACE_INDEX[15] },
	{ "16", KU_R_COSP_DIR + ALL_FACE_INDEX[16] },
	{ "18", KU_R_COSP_DIR + ALL_FACE_INDEX[18] },
	{ "19", KU_R_COSP_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_KU_INDEX_R_COSP
{
	{ NAME_MAP_SPRITE, SPRITE_KU_INDEX_SPRITE_R_COSP_DIR },
	{ NAME_MAP_FACE, SPRITE_KU_INDEX_FACE_R_COSP_DIR }
};

map<string, map<string, map<string, string>>> SPRITE_KU_DIR
{
	{ "C", SPRITE_KU_INDEX_C },
	{ "C_COSP", SPRITE_KU_INDEX_C_COSP },
	{ "L", SPRITE_KU_INDEX_L },
	{ "L_COSP", SPRITE_KU_INDEX_L_COSP },
	{ "R", SPRITE_KU_INDEX_R },
	{ "R_COSP", SPRITE_KU_INDEX_R_COSP },
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const string MA_C_DIR = "\\MA_C";
const string MA_L_DIR = "\\MA_L";
const string MA_R_DIR = "\\MA_R";

//MA
//C
map<string, string> SPRITE_MA_INDEX_SPRITE_C_DIR{ { "1", MA_C_DIR + NUMSPRITE_ONE_DIR }, { "2", MA_C_DIR + NUMSPRITE_TWO_DIR } };

//C 4 6 7 9 10 11 14 15 16 17 18 19
map<string, string> SPRITE_MA_INDEX_FACE_C_DIR{
	{ "4", MA_C_DIR + ALL_FACE_INDEX[4] },
	{ "6", MA_C_DIR + ALL_FACE_INDEX[6] },
	{ "7", MA_C_DIR + ALL_FACE_INDEX[7] },
	{ "9", MA_C_DIR + ALL_FACE_INDEX[9] },
	{ "10", MA_C_DIR + ALL_FACE_INDEX[10] },
	{ "11", MA_C_DIR + ALL_FACE_INDEX[11] },
	{ "14", MA_C_DIR + ALL_FACE_INDEX[14] },
	{ "15", MA_C_DIR + ALL_FACE_INDEX[15] },
	{ "16", MA_C_DIR + ALL_FACE_INDEX[16] },
	{ "17", MA_C_DIR + ALL_FACE_INDEX[17] },
	{ "18", MA_C_DIR + ALL_FACE_INDEX[18] },
	{ "19", MA_C_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_MA_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_MA_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_MA_INDEX_FACE_C_DIR }
};

//L
map<string, string> SPRITE_MA_INDEX_SPRITE_L_DIR{ { "1", MA_L_DIR + NUMSPRITE_ONE_DIR }, { "2", MA_L_DIR + NUMSPRITE_TWO_DIR } };

//L 4 6 7 9 10 11 14 15 16 17 18 19
map<string, string> SPRITE_MA_INDEX_FACE_L_DIR{
	{ "4", MA_L_DIR + ALL_FACE_INDEX[4] },
	{ "6", MA_L_DIR + ALL_FACE_INDEX[6] },
	{ "7", MA_L_DIR + ALL_FACE_INDEX[7] },
	{ "9", MA_L_DIR + ALL_FACE_INDEX[9] },
	{ "10", MA_L_DIR + ALL_FACE_INDEX[10] },
	{ "11", MA_L_DIR + ALL_FACE_INDEX[11] },
	{ "14", MA_L_DIR + ALL_FACE_INDEX[14] },
	{ "15", MA_L_DIR + ALL_FACE_INDEX[15] },
	{ "16", MA_L_DIR + ALL_FACE_INDEX[16] },
	{ "17", MA_L_DIR + ALL_FACE_INDEX[17] },
	{ "18", MA_L_DIR + ALL_FACE_INDEX[18] },
	{ "19", MA_L_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_MA_INDEX_L
{
	{ NAME_MAP_SPRITE, SPRITE_MA_INDEX_SPRITE_L_DIR },
	{ NAME_MAP_FACE, SPRITE_MA_INDEX_FACE_L_DIR }
};

//R
map<string, string> SPRITE_MA_INDEX_SPRITE_R_DIR{ { "1", MA_R_DIR + NUMSPRITE_ONE_DIR }, { "2", MA_R_DIR + NUMSPRITE_TWO_DIR } };

//R 4 6 7 9 11 14 15 16 18 19
map<string, string> SPRITE_MA_INDEX_FACE_R_DIR{
	{ "4", MA_R_DIR + ALL_FACE_INDEX[4] },
	{ "6", MA_R_DIR + ALL_FACE_INDEX[6] },
	{ "7", MA_R_DIR + ALL_FACE_INDEX[7] },
	{ "9", MA_R_DIR + ALL_FACE_INDEX[9] },
	{ "11", MA_R_DIR + ALL_FACE_INDEX[11] },
	{ "14", MA_R_DIR + ALL_FACE_INDEX[14] },
	{ "15", MA_R_DIR + ALL_FACE_INDEX[15] },
	{ "16", MA_R_DIR + ALL_FACE_INDEX[16] },
	{ "18", MA_R_DIR + ALL_FACE_INDEX[18] },
	{ "19", MA_R_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_MA_INDEX_R
{
	{ NAME_MAP_SPRITE, SPRITE_MA_INDEX_SPRITE_R_DIR },
	{ NAME_MAP_FACE, SPRITE_MA_INDEX_FACE_R_DIR }
};

map<string, map<string, map<string, string>>> SPRITE_MA_DIR
{
	{ "C", SPRITE_MA_INDEX_C },
	{ "L", SPRITE_MA_INDEX_L },
	{ "R", SPRITE_MA_INDEX_R },
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const string RO_C_DIR = "\\RO_C";
const string RO_R_DIR = "\\RO_R";



//RO
//C
map<string, string> SPRITE_RO_INDEX_SPRITE_C_DIR{ { "1", RO_C_DIR + NUMSPRITE_ONE_DIR }};

//C 4 6 9 10 11 14 16 18
map<string, string> SPRITE_RO_INDEX_FACE_C_DIR{
	{ "4", RO_C_DIR + ALL_FACE_INDEX[4] },
	{ "6", RO_C_DIR + ALL_FACE_INDEX[6] },
	{ "9", RO_C_DIR + ALL_FACE_INDEX[9] },
	{ "10", RO_C_DIR + ALL_FACE_INDEX[10] },
	{ "11", RO_C_DIR + ALL_FACE_INDEX[11] },
	{ "14", RO_C_DIR + ALL_FACE_INDEX[14] },
	{ "16", RO_C_DIR + ALL_FACE_INDEX[16] }
};

map<string, map<string, string>> SPRITE_RO_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_RO_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_RO_INDEX_FACE_C_DIR }
};


//R
map<string, string> SPRITE_RO_INDEX_SPRITE_R_DIR{ { "1", RO_R_DIR + NUMSPRITE_ONE_DIR }};

//R 4 6 9 10 11 14 16 18
map<string, string> SPRITE_RO_INDEX_FACE_R_DIR{
	{ "4", RO_R_DIR + ALL_FACE_INDEX[4] },
	{ "6", RO_R_DIR + ALL_FACE_INDEX[6] },
	{ "9", RO_R_DIR + ALL_FACE_INDEX[9] },
	{ "10", RO_R_DIR + ALL_FACE_INDEX[10] },
	{ "11", RO_R_DIR + ALL_FACE_INDEX[11] },
	{ "14", RO_R_DIR + ALL_FACE_INDEX[14] },
	{ "16", RO_R_DIR + ALL_FACE_INDEX[16] }
};

map<string, map<string, string>> SPRITE_RO_INDEX_R
{
	{ NAME_MAP_SPRITE, SPRITE_RO_INDEX_SPRITE_R_DIR },
	{ NAME_MAP_FACE, SPRITE_RO_INDEX_FACE_R_DIR }
};

map<string, map<string, map<string, string>>> SPRITE_RO_DIR
{
	{ "C", SPRITE_RO_INDEX_C },
	{ "R", SPRITE_RO_INDEX_R },
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const string SA_C_DIR = "\\SA_C";
const string SA_L_DIR = "\\SA_L";
const string SA_L_COSP_DIR = "\\SA_L_COSP";
const string SA_R_DIR = "\\SA_R";


//SA
//C
map<string, string> SPRITE_SA_INDEX_SPRITE_C_DIR{ { "1", SA_C_DIR + NUMSPRITE_ONE_DIR } };

//C 4 5 6 7 9 10 11 13 14 16 17 18
map<string, string> SPRITE_SA_INDEX_FACE_C_DIR{
	{ "4", SA_C_DIR + ALL_FACE_INDEX[4] },
	{ "5", SA_C_DIR + ALL_FACE_INDEX[5] },
	{ "6", SA_C_DIR + ALL_FACE_INDEX[6] },
	{ "7", SA_C_DIR + ALL_FACE_INDEX[7] },
	{ "9", SA_C_DIR + ALL_FACE_INDEX[9] },
	{ "10", SA_C_DIR + ALL_FACE_INDEX[10] },
	{ "11", SA_C_DIR + ALL_FACE_INDEX[11] },
	{ "13", SA_C_DIR + ALL_FACE_INDEX[13] },
	{ "14", SA_C_DIR + ALL_FACE_INDEX[14] },
	{ "16", SA_C_DIR + ALL_FACE_INDEX[16] },
	{ "17", SA_C_DIR + ALL_FACE_INDEX[17] },
	{ "18", SA_C_DIR + ALL_FACE_INDEX[18] }
};

map<string, map<string, string>> SPRITE_SA_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_SA_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_SA_INDEX_FACE_C_DIR }
};


//L
map<string, string> SPRITE_SA_INDEX_SPRITE_L_DIR{ { "1", SA_L_DIR + NUMSPRITE_ONE_DIR } };

//L 4 5 6 7 9 10 11 13 14 16
map<string, string> SPRITE_SA_INDEX_FACE_L_DIR{
	{ "4", SA_L_DIR + ALL_FACE_INDEX[4] },
	{ "5", SA_L_DIR + ALL_FACE_INDEX[5] },
	{ "6", SA_L_DIR + ALL_FACE_INDEX[6] },
	{ "7", SA_L_DIR + ALL_FACE_INDEX[7] },
	{ "9", SA_L_DIR + ALL_FACE_INDEX[9] },
	{ "10", SA_L_DIR + ALL_FACE_INDEX[10] },
	{ "11", SA_L_DIR + ALL_FACE_INDEX[11] },
	{ "13", SA_L_DIR + ALL_FACE_INDEX[13] },
	{ "14", SA_L_DIR + ALL_FACE_INDEX[14] },
	{ "16", SA_L_DIR + ALL_FACE_INDEX[16] }
};

map<string, map<string, string>> SPRITE_SA_INDEX_L
{
	{ NAME_MAP_SPRITE, SPRITE_SA_INDEX_SPRITE_L_DIR },
	{ NAME_MAP_FACE, SPRITE_SA_INDEX_FACE_L_DIR }
};

//L_COSP
map<string, string> SPRITE_SA_INDEX_SPRITE_L_COSP_DIR{ { "1", SA_L_COSP_DIR + NUMSPRITE_ONE_DIR } };

//L_COSP 4 5 6 16
map<string, string> SPRITE_SA_INDEX_FACE_L_COSP_DIR{
	{ "4", SA_L_COSP_DIR + ALL_FACE_INDEX[4] },
	{ "5", SA_L_COSP_DIR + ALL_FACE_INDEX[5] },
	{ "6", SA_L_COSP_DIR + ALL_FACE_INDEX[6] },
	{ "16", SA_L_COSP_DIR + ALL_FACE_INDEX[16] }
};

map<string, map<string, string>> SPRITE_SA_INDEX_L_COSP
{
	{ NAME_MAP_SPRITE, SPRITE_SA_INDEX_SPRITE_L_COSP_DIR },
	{ NAME_MAP_FACE, SPRITE_SA_INDEX_FACE_L_COSP_DIR }
};

//R
map<string, string> SPRITE_SA_INDEX_SPRITE_R_DIR{ { "1", SA_R_DIR + NUMSPRITE_ONE_DIR } };


//R 4 5 6 13 14 16 17 18
map<string, string> SPRITE_SA_INDEX_FACE_R_DIR{
	{ "4", SA_R_DIR + ALL_FACE_INDEX[4] },
	{ "5", SA_R_DIR + ALL_FACE_INDEX[5] },
	{ "6", SA_R_DIR + ALL_FACE_INDEX[6] },
	{ "13", SA_R_DIR + ALL_FACE_INDEX[13] },
	{ "14", SA_R_DIR + ALL_FACE_INDEX[14] },
	{ "16", SA_R_DIR + ALL_FACE_INDEX[16] },
	{ "17", SA_R_DIR + ALL_FACE_INDEX[17] },
	{ "18", SA_R_DIR + ALL_FACE_INDEX[18] }
};

map<string, map<string, string>> SPRITE_SA_INDEX_R
{
	{ NAME_MAP_SPRITE, SPRITE_SA_INDEX_SPRITE_R_DIR },
	{ NAME_MAP_FACE, SPRITE_SA_INDEX_FACE_R_DIR }
};

map<string, map<string, map<string, string>>> SPRITE_SA_DIR
{
	{ "C", SPRITE_SA_INDEX_C },
	{ "L", SPRITE_SA_INDEX_L },
	{ "L_COSP", SPRITE_SA_INDEX_L_COSP },
	{ "R", SPRITE_SA_INDEX_R }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const string SE_C_DIR = "\\SE_C";
const string SE_L_DIR = "\\SE_L";
const string SE_R_DIR = "\\SE_R";


//SE
//C
map<string, string> SPRITE_SE_INDEX_SPRITE_C_DIR{ { "1", SE_C_DIR + NUMSPRITE_ONE_DIR }, { "2", SE_C_DIR + NUMSPRITE_TWO_DIR } };

//C 4 5 6 7 8 9 10 11 13 14 15 16 18 19
map<string, string> SPRITE_SE_INDEX_FACE_C_DIR{
	{ "4", SE_C_DIR + ALL_FACE_INDEX[4] },
	{ "5", SE_C_DIR + ALL_FACE_INDEX[5] },
	{ "6", SE_C_DIR + ALL_FACE_INDEX[6] },
	{ "7", SE_C_DIR + ALL_FACE_INDEX[7] },
	{ "8", SE_C_DIR + ALL_FACE_INDEX[8] },
	{ "9", SE_C_DIR + ALL_FACE_INDEX[9] },
	{ "10", SE_C_DIR + ALL_FACE_INDEX[10] },
	{ "11", SE_C_DIR + ALL_FACE_INDEX[11] },
	{ "13", SE_C_DIR + ALL_FACE_INDEX[13] },
	{ "14", SE_C_DIR + ALL_FACE_INDEX[14] },
	{ "15", SE_C_DIR + ALL_FACE_INDEX[15] },
	{ "16", SE_C_DIR + ALL_FACE_INDEX[16] },
	{ "18", SE_C_DIR + ALL_FACE_INDEX[18] },
	{ "19", SE_C_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_SE_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_SE_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_SE_INDEX_FACE_C_DIR }
};

//L
map<string, string> SPRITE_SE_INDEX_SPRITE_L_DIR{ { "1", SE_L_DIR + NUMSPRITE_ONE_DIR }, { "2", SE_L_DIR + NUMSPRITE_TWO_DIR } };

//L 4 5 6 7 10 11 13 14 15 16 18 19
map<string, string> SPRITE_SE_INDEX_FACE_L_DIR{
	{ "4", SE_L_DIR + ALL_FACE_INDEX[4] },
	{ "5", SE_L_DIR + ALL_FACE_INDEX[5] },
	{ "6", SE_L_DIR + ALL_FACE_INDEX[6] },
	{ "7", SE_L_DIR + ALL_FACE_INDEX[7] },
	{ "10", SE_L_DIR + ALL_FACE_INDEX[10] },
	{ "11", SE_L_DIR + ALL_FACE_INDEX[11] },
	{ "13", SE_C_DIR + ALL_FACE_INDEX[13] },
	{ "14", SE_L_DIR + ALL_FACE_INDEX[14] },
	{ "15", SE_L_DIR + ALL_FACE_INDEX[15] },
	{ "16", SE_L_DIR + ALL_FACE_INDEX[16] },
	{ "18", SE_L_DIR + ALL_FACE_INDEX[18] },
	{ "19", SE_L_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_SE_INDEX_L
{
	{ NAME_MAP_SPRITE, SPRITE_SE_INDEX_SPRITE_L_DIR },
	{ NAME_MAP_FACE, SPRITE_SE_INDEX_FACE_L_DIR }
};


//R
map<string, string> SPRITE_SE_INDEX_SPRITE_R_DIR{ { "1", SE_R_DIR + NUMSPRITE_ONE_DIR }, { "2", SE_R_DIR + NUMSPRITE_TWO_DIR } };

//R 4 5 6 7 9 10 13 14 15 16 18 19
map<string, string> SPRITE_SE_INDEX_FACE_R_DIR{
	{ "4", SE_R_DIR + ALL_FACE_INDEX[4] },
	{ "5", SE_R_DIR + ALL_FACE_INDEX[5] },
	{ "6", SE_R_DIR + ALL_FACE_INDEX[6] },
	{ "7", SE_R_DIR + ALL_FACE_INDEX[7] },
	{ "9", SE_R_DIR + ALL_FACE_INDEX[9] },
	{ "10", SE_R_DIR + ALL_FACE_INDEX[10] },
	{ "13", SE_R_DIR + ALL_FACE_INDEX[13] },
	{ "14", SE_R_DIR + ALL_FACE_INDEX[14] },
	{ "15", SE_R_DIR + ALL_FACE_INDEX[15] },
	{ "16", SE_R_DIR + ALL_FACE_INDEX[16] },
	{ "18", SE_R_DIR + ALL_FACE_INDEX[18] },
	{ "19", SE_R_DIR + ALL_FACE_INDEX[19] }
};

map<string, map<string, string>> SPRITE_SE_INDEX_R
{
	{ NAME_MAP_SPRITE, SPRITE_SE_INDEX_SPRITE_R_DIR },
	{ NAME_MAP_FACE, SPRITE_SE_INDEX_FACE_R_DIR }
};

map<string, map<string, map<string, string>>> SPRITE_SE_DIR
{
	{ "C", SPRITE_SE_INDEX_C },
	{ "L", SPRITE_SE_INDEX_L },
	{ "R", SPRITE_SE_INDEX_R }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const string YO_C_DIR = "\\YO_C";

//YO
//C
map<string, string> SPRITE_YO_INDEX_SPRITE_C_DIR{ { "1", YO_C_DIR + NUMSPRITE_ONE_DIR } };

//C 4 5 6 7 14 15 16
map<string, string> SPRITE_YO_INDEX_FACE_C_DIR{
	{ "4", YO_C_DIR + ALL_FACE_INDEX[4] },
	{ "5", YO_C_DIR + ALL_FACE_INDEX[5] },
	{ "6", YO_C_DIR + ALL_FACE_INDEX[6] },
	{ "7", YO_C_DIR + ALL_FACE_INDEX[7] },
	{ "14", YO_C_DIR + ALL_FACE_INDEX[14] },
	{ "15", YO_C_DIR + ALL_FACE_INDEX[15] },
	{ "16", YO_C_DIR + ALL_FACE_INDEX[16] }
};

map<string, map<string, string>> SPRITE_YO_INDEX_C
{
	{ NAME_MAP_SPRITE, SPRITE_YO_INDEX_SPRITE_C_DIR },
	{ NAME_MAP_FACE, SPRITE_YO_INDEX_FACE_C_DIR }
};


map<string, map<string, map<string, string>>> SPRITE_YO_DIR
{
	{ "C", SPRITE_YO_INDEX_C },
};