#pragma once
#include "Page.h"


map<Node*, Node*> original_parent;// for returned mixed actions node original parents


class Script
{
private:
	string dir_script;
	vector<shared_ptr<Page>> All_Pages;

public:
	
	Script();//������ ������������ ��� �������� �������

	Script(string); //������ � ��������� ���� �������

	void Add_page(); // ������� �������� � �������

	void Set_page(int); //��������� ������� �� ��������� ��������

	void init();//��������� ��� �������� �� �������

	void draw();// ������� ������� � �������� �� ���� ��������

	


};