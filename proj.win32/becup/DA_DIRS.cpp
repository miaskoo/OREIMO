#include "DA_DIRS.h"


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
