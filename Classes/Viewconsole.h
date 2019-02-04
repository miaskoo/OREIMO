
#include <memory> // для использования smart_pointer
#include <vector>
#include <string>

using namespace std;
using namespace cocos2d;

class LAppView;
class LAppLive2DManager;

class VIEWERCONSOLE
{
private:
	Node *sprite_node; // спрайтовая нода скрипта
	Node *sprite_swich_node; //создаваемая каждый свич нода спрайтов свич


	vector <SPRITEBOX> sprites; // хранит спрайты используемые на странице
	vector <bool> simple_sprite; // хранит значения сложный переход спрайта или простой

	string dir_scene = "None";
	string custom_swich_scene = "None";
	bool return_scene = false;

	string dir_music;
	string dir_voice;
	string dir_sound;
	string shake_effect;
	vector <string> script_commands; //упорядоченные команды скрипта
	int num_script_commands; //текущий номер команды

	vector <string> sprite_commands; // упорядоченные команды для вызова спрайтов
	int num_sprite_commands; //текущий номер команды

	vector <string> scene_commands;// упорядоченные команды для вызова сцены
	int num_scene_commands; // текущий номер команды

	LAppLive2DManager *setting_model = NULL; // настройки модели
	LAppView *current_model = NULL; // объект модели 
	vector<bool> voicebox; //данные для рта модели(при озвучке)
	int INDEX_MODEL;
	int INDEX_TEXTURE;
	float coordinata_model[3];
	int num_idle = NULL;
	bool action_model = false;
	int num_action = NULL;
	vector<string> EXPRESSION_BOX;
	vector<string> EXPRESSION_ACTION_BOX;


	int arg_cloud; //аргумент облака 0 - не злое 1 - злое
	string text_cloud; //текст вызванного облака
	float duration_cloud;

	Node *Sprite_und; //хранит ноду спрайтов
	Node *Sprite_swich; //хранит ноду свичащихся спрайтов
public:

	void Create_commands_sprite(Node *Game_Mode); // при свиче идет вызов анимаций - менять систему

	void Create_commands_scene(Node *Game_Mode);

	void Create_commands_script(vector<string> commands);

	void Use_command_sprite(Node *Game_Mode);

	void Use_command_scene(Node *Game_Mode);

	void view(Node *Game_Mode);

	void Set_model_create_data(int index_model, int index_texture, float x, float y, float z);

	void Set_model_command_data(vector<string> expression_command, int num_idle);

	void Set_model_command_data(vector<string> expression_command, vector<string> expression_action_command, int temp_num_idle, int temp_num_action);

	void Get_cloud(Node* Game_Mode);

	void Draw_model(Node* Game_Mode);

	void Command_model();

	void Create_custom_idle();

	void Create_simple_idle();

	void Set_sprite_data(vector <SPRITEBOX> temp_sprites, vector <bool> temp_simple_sprite);

	void Set_scene_data(string dir, string swich);

	void Set_music_data(string dir);

	void Set_voice_data(string dir);

	void Set_voicebox_model_data(vector<bool> temp_voicebox)
	{
		this->voicebox.assign(temp_voicebox.begin(), temp_voicebox.end());
	}

	void Set_sound_data(string dir);

	void Set_shake_data(string effect);

	void Set_cloud_data(int arg, string text, float duration);

	void Use_shake(Node *Game_Mode);

	void Star(Node *Game_Mode, bool Get_star);
};

VIEWERCONSOLE CONSOLE;