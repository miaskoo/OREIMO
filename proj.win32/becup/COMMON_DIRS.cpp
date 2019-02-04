#include "COMMON_DIRS.h"
#include <map>
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
