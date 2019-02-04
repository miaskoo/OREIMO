#pragma once
#include "Object_Scene.h"

enum posicion_sprite{ left, left_centr, centr, right_centr , right };
enum name_sprite { KI, AY, DA };

struct positions
{
	int x;
	int y;
};



extern const int cout_anim; //���������� ������� ������ - ����� - ���
extern const int cout_sprite; // ������������ ���������� ������������ ��������

extern map <int, Node** > index_sprite;
extern map< Node**, state_node> check_sprite_for_state; // �������� �� ������
extern map<name_sprite, Node**> name_for_node; //��� ������������ �� ����� �������

extern map<string, std::array<positions, 3>> POS_KI;
extern map<string, std::array<positions, 3>> POS_AY;
extern map<string, std::array<positions, 3>> POS_DA;

class Object_Sprtite : public Object_Scene
{
private:
	name_sprite my_name; // ��� ���

	string face_dir; //����������� ����
	
	std::array<positions,3> pos; //���������� ��  ��������� ������� - ���� - ��� �� ������� � ����� ����

	posicion_sprite my_pos = centr; // ������� ������������� �� ����������

public:

	Object_Sprtite(name_sprite, string, int, int);// ��������� ������ ������� � ��� ����������

	void Set_pos(posicion_sprite cur_pos) { my_pos = cur_pos; }

	virtual swich_node draw() override;// ������������������ ����� �� ������� ������ � ������������������ ������ �� ����� ������ Sprite

	~Object_Sprtite();
};

