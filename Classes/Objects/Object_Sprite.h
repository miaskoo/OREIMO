#pragma once
#include "Object_Scene.h"



extern const int cout_anim; //���������� ������� ������ - ����� - ���
extern const int cout_sprite; // ������������ ���������� ������������ ��������

extern std::array <Node**, 6> index_sprite;//������ ��� ��������
extern map< Node**, any_enum::state_node> check_sprite_for_state; // �������� �� ������
extern map<any_enum::name_sprite, Node**> name_for_node; //��� ������������ �� ����� �������
extern string dir_home_sprite; // ������������ ����
void relese_old_state(Node *);
void clear_mapani(Sprite*);
std::string Get_name_from_enum(any_enum::name_sprite my_name);//�������� ��� � string �� enum
std::array<positions, 3> search_pos(std::string name, std::string pos);//���� � ������� ��� ������ ������� ������� ��������� ��� ������� ���������� 

class Object_Sprite : public Object_Scene
{
protected:
	any_enum::name_sprite my_name; // ��� ���

	string face_dir; //����������� ����


	std::array<positions,3> pos; //���������� ��  ��������� ������� - ���� - ��� �� ������� � ����� ����

	any_enum::posicion_sprite my_pos = any_enum::centr; // ������� ������������� �� ����������

	bool hide = false;
public:

	Object_Sprite(any_enum::name_sprite, string, int, int);// ��������� ������ ������� � ��� ����������

	Object_Sprite(any_enum::name_sprite); // ��� ��������(�������) ������� �� �����

	bool Get_hide() { return this->hide; } // ������� ����� ��

	any_enum::name_sprite Get_name(){ return this->my_name; }

	void Set_pos(any_enum::posicion_sprite cur_pos) { my_pos = cur_pos; }

	virtual swich_node draw() override;// ������������������ ����� �� ������� ������ � ������������������ ������ �� ����� ������ Sprite

	//~Object_Sprite(); 

};

std::array<positions, 3> search_pos(std::string name, std::string pos);
extern map<any_enum::posicion_sprite, positions> POS_HEAD;