#pragma once
#include "Page.h"


map<Node*, Node*> original_parent;// for returned mixed actions node original parents


class Script
{
private:
	string dir_script;
	vector<shared_ptr<Page>> All_Pages;

public:
	
	Script();//пустой иницилизатор для создания скрипта

	Script(string); //запись и прогрузка всех страниц

	void Add_page(); // добавит страницу к скрипту

	void Set_page(int); //установит счетчик на указанную страницу

	void init();//проинитит все страницы из скрипта

	void draw();// обновит счетчик и перескок на след страницу

	


};