#pragma once
#include "Object_Scene.h"



extern const int cout_anim; //���������� ������� ������ - ����� - ���
extern const int cout_sprite; // ������������ ���������� ������������ ��������

extern map <int, Node** > index_sprite;
extern map< Node**, any_enum::state_node> check_sprite_for_state; // �������� �� ������
extern map<any_enum::name_sprite, Node**> name_for_node; //��� ������������ �� ����� �������

extern map<string, std::array<positions, 3>> POS_KI;
extern map<string, std::array<positions, 3>> POS_AY;
extern map<string, std::array<positions, 3>> POS_DA;

class Object_Sprtite : public Object_Scene
{
private:
	any_enum::name_sprite my_name; // ��� ���
	
	string face_dir; //����������� ����
	string home_dir = ".\\Resources\\Sprites";
	std::array<positions,3> pos; //���������� ��  ��������� ������� - ���� - ��� �� ������� � ����� ����

	any_enum::posicion_sprite my_pos = any_enum::centr; // ������� ������������� �� ����������
	bool hide = false;
public:

	Object_Sprtite(any_enum::name_sprite, string, int, int);// ��������� ������ ������� � ��� ����������

	Object_Sprtite(any_enum::name_sprite); // ��� �������� ������� �� �����

	bool Get_hide() { return this->hide; }

	any_enum::name_sprite Get_name(){ return this->my_name; }

	void Set_pos(any_enum::posicion_sprite cur_pos) { my_pos = cur_pos; }

	virtual swich_node draw() override;// ������������������ ����� �� ������� ������ � ������������������ ������ �� ����� ������ Sprite

	~Object_Sprtite();
};



extern map<string, std::array<positions, 3>> POS_AY;
extern map<string, std::array<positions, 3>> POS_DA;
extern map<string, std::array<positions, 3>> POS_KI;
extern map<string, std::array<positions, 3>> POS_AK;
extern map<string, std::array<positions, 3>> POS_KA;
extern map<string, std::array<positions, 3>> POS_KU;
extern map<string, std::array<positions, 3>> POS_MA;
extern map<string, std::array<positions, 3>> POS_RO;
extern map<string, std::array<positions, 3>> POS_SA;
extern map<string, std::array<positions, 3>> POS_SE;
extern map<string, std::array<positions, 3>> POS_YO;

