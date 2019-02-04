#include "KI_DIRS.h"

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

