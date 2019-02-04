#include "Page.h"

Node *Game_Mode = NULL;
Node *Text_Box = NULL;

Page::Page(vector<Object_Scene*> cur_obj_ptr, vector<type_object> cur_type, vector <type_interactions> cur_intr, vector <type_swich> сur_swich, vector<type_action> cur_act, text_box* cur_text)
{
	page_text = cur_text;
	for (int n = 0; n < int(cur_obj_ptr.size()); n++)
	{
		this->objects.push_back(shared_ptr<Object_Scene>(cur_obj_ptr[n]));// объектики
		objects_type[&objects.back()] = cur_type[n]; //типы к объектикам
		if (cur_type[n] == sprite || cur_type[n] == scene || cur_type[n] == mixed || cur_type[n] == texbox)
		{
			objects_intreractions[&objects.back()] = cur_intr[n]; // привязка типа взаимодействия к объектам

			if (cur_intr[n] == swich)
			{
				objects_swich[&objects.back()] = сur_swich[n]; // привязка к swich мапе по типа взаимодействия swich
			}
			else if (cur_intr[n] == action)
			{
				objects_action[&objects.back()] = cur_act[n]; // привязка действия action по типу взаимодействия action
			}
		}
	}
}

bool Page::update()
{
	for (int n = 0; n < int(all_nodes.size()); n++)
	{
		if (unlock_parent[all_nodes[n]] == true)
		{
			(*all_nodes[n])->removeFromParent();
			Game_Mode->addChild(*all_nodes[n]);
		}
	}
	return true;
}



bool Page::draw()
{
	update();
	if (int(objects.size()) - 1 < cur_obj)
		return false;
	//bool(*fuct_ptr)(auto);
	//fuct_ptr = this->draw ;
	auto fuct = [=]() { this->draw(); };
	auto fuct_ptr = &fuct;
	switch (objects_type[&objects[cur_obj]])
	{
	case mixed:
	{
				  if (objects_action[&objects[cur_obj]] == swich)
				  {
					  auto data = objects[cur_obj]->draw();
					  
					  Action_mixed::swish(fuct_ptr, data.old_ptr, data.new_ptr);
				  }
	}
	case sprite:
	{
				   if (objects_action[&objects[cur_obj]] == action)
				   {
					   Action_sprite::action(fuct_ptr, objects[cur_obj]->Get_Node(), objects_action[&objects[cur_obj]], false);
				   }
				   else if (objects_action[&objects[cur_obj]] == swich)
				   {
					   auto data = objects[cur_obj]->draw();
					   Action_sprite::swich(fuct_ptr, data.old_ptr, data.new_ptr, objects_swich[&objects[cur_obj]], false);
				   }
	}
	case scene:
	{
				  if (objects_action[&objects[cur_obj]] == action)
				  {

				  }
				  else if (objects_action[&objects[cur_obj]] == swich)
				  {
					  auto data = objects[cur_obj]->draw();
					  Action_scene::swich(fuct_ptr, data.old_ptr, data.new_ptr);
				  }
	}
	default:
		return true;
	}
	cur_obj++;
	return true;
}

