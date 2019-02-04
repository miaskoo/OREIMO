#pragma once
#include <vector>
#include <string>
#include <array>
#include "cocos2d.h"
#include "Resourse.h"
using namespace std;
using namespace cocos2d;


enum state_node { FREE, BUSY };

struct swich_node
{
	Node* old_ptr;
	Node* new_ptr;
};


extern Node *Scene1;
extern Node *Scene2;
extern Node *Sprite1;
extern Node *Sprite2;
extern Node *Sprite3;
extern Node *Sprite4;
extern Node *Sprite5;
extern Node *Sprite6;

extern map< Node**, state_node> check_scene_for_state;
extern map< Node**, bool> unlock_parent;
extern  array<Node**, 8> all_nodes;


extern Node *Custom_Node;
extern Node *Custom_Node_old;
extern const int Custom_Tag;
extern const int Custom_Tag_old;

class Object_Scene
{
protected:
	Node *my_node = NULL;//����������� ������������ ����
	string dir_obj = ""; // ����������� ������� ������
public:
	Object_Scene(){}; // �� ���������
	Object_Scene(string);// ������� ���������� ��� BG
	Object_Scene(int);// ������� ���������� ��� CG
	virtual swich_node draw();
	Node *Get_Node(){ return this->my_node; }
};