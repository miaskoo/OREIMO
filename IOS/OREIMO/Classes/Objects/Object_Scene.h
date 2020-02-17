#pragma once
#include <vector>
#include <string>
#include <array>
#include "cocos2d.h"
#include "Classes\Dirs\Resourse.h"
using namespace std;
using namespace cocos2d;

namespace any_enum
{
	const int size_ore = 64;
	const int size_chapter = 11;
	const int size_agr_model = 36;//���������� �������� � ���������� ��������
	enum scale_sprite{ little, standart, big };
	enum open_resurce{ lock, unlock, old };
	enum use_ore{ ORER, OREL, nonuse };
	enum state_node { FREE, BUSY };
	enum posicion_sprite{ left, left_centr, centr, right_centr, right, custom };
	enum name_sprite { KI, AY, DA, AK, KA, KU, MA, RO, SA, SE, YO, NONE };
	enum global_filtr { sepia, night, evening, morning};
}

struct swich_node
{
	Node* old_ptr;
	Node* new_ptr;
};

struct positions
{
	int x;
	int y;
};


extern Node *Scene1;
extern Node *Scene2;
extern Node *Sprite1;
extern Node *Sprite2;
extern Node *Sprite3;
extern Node *Sprite4;
extern Node *Sprite5;
extern Node *Sprite6;

extern map< Node**, any_enum::state_node> check_scene_for_state;
extern map< Node**, bool> unlock_parent;
extern  array<Node**, 8> all_nodes;

GLProgramState *GetShader(any_enum::global_filtr state);//��������� �������� ������ �� ����� �� ����

class Object_Scene
{
protected:
	Node *my_node = nullptr;//����������� ������������ ����
	const std::string BAD = "empty";
	string dir_obj = BAD; // ����������� ������� ������
	any_enum::global_filtr state = any_enum::morning;
public:
	Object_Scene(){}; // �� ���������
	Object_Scene(string, int, any_enum::global_filtr = any_enum::morning);// ������� ���������� ��� ������ ����
	bool wait = false;
	virtual swich_node draw();
	Node *Get_Node(){ return this->my_node; }
	void Set_wait(bool x){ this->wait = std::move(x); }
	bool Get_wait(){ return this->wait; };

};

