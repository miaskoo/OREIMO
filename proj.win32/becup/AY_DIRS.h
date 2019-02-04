#pragma once
#include <map>
#include <vector>
#include <string>
#include <COMMON_DIRS.h>

using namespace std;
extern const string AY_C_DIR;
extern const string AY_C_YAN_DIR;
extern const string AY_L_DIR;
extern const string AY_L_YAN_DIR;
extern const string AY_L_OLD_DIR;
extern const string AY_R_DIR;
extern const string AY_R_YAN_DIR;
extern const string AY_R_OLD_DIR;

extern map<string, string> SPRITE_AY_INDEX_SPRITE_C_DIR;
extern map<string, string> SPRITE_AY_INDEX_FACE_C_DIR;
extern map<string, map<string, string>> SPRITE_AY_INDEX_C;
extern map<string, string> SPRITE_AY_INDEX_SPRITE_C_YAN_DIR;
extern map<string, string> SPRITE_AY_INDEX_FACE_C_YAN_DIR;
extern map<string, map<string, string>> SPRITE_AY_INDEX_C_YAN;
extern map<string, string> SPRITE_AY_INDEX_SPRITE_L_DIR;
extern map<string, string> SPRITE_AY_INDEX_FACE_L_DIR;
extern map<string, map<string, string>> SPRITE_AY_INDEX_L;
extern map<string, string> SPRITE_AY_INDEX_SPRITE_L_YAN_DIR;
extern map<string, string> SPRITE_AY_INDEX_FACE_L_YAN_DIR;
extern map<string, map<string, string>> SPRITE_AY_INDEX_L_YAN;
extern map<string, string> SPRITE_AY_INDEX_SPRITE_L_OLD_DIR;
extern map<string, string> SPRITE_AY_INDEX_FACE_L_OLD_DIR;
extern map<string, map<string, string>> SPRITE_AY_INDEX_L_OLD;
extern map<string, string> SPRITE_AY_INDEX_SPRITE_R_DIR;
extern map<string, string> SPRITE_AY_INDEX_FACE_R_DIR;
extern map<string, map<string, string>> SPRITE_AY_INDEX_R;
extern map<string, string> SPRITE_AY_INDEX_SPRITE_R_YAN_DIR;
extern map<string, string> SPRITE_AY_INDEX_FACE_R_YAN_DIR;
extern map<string, map<string, string>> SPRITE_AY_INDEX_R_YAN;
extern map<string, string> SPRITE_AY_INDEX_SPRITE_R_OLD_DIR;
extern map<string, string> SPRITE_AY_INDEX_FACE_R_OLD_DIR;
extern map<string, map<string, string>> SPRITE_AY_INDEX_R_OLD;
extern map<string, map<string, map<string, string>>> SPRITE_AY_DIR;