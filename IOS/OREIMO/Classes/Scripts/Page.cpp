#include "Page.h"

extern Node *OREU;
extern Node *OREL;
extern Node *ORER;

extern void chek_ore_lock(int);
extern void action_ore(any_enum::posicion_sprite, type_action);
extern bool All_fast;

map<any_enum::name_sprite, any_enum::scale_sprite> name_for_scale{
	{ any_enum::AY, any_enum::little }, { any_enum::DA, any_enum::little }, { any_enum::KI, any_enum::little },
	{ any_enum::AK, any_enum::little }, { any_enum::KA, any_enum::little }, { any_enum::KU, any_enum::little },
	{ any_enum::MA, any_enum::little }, { any_enum::RO, any_enum::little }, { any_enum::SA, any_enum::little },
	{ any_enum::SE, any_enum::little }, { any_enum::YO, any_enum::little }
};

map<Node**, any_enum::scale_sprite> sprite_for_scale
{ 
	{ index_sprite[0], any_enum::little }, { index_sprite[1], any_enum::little },
	{ index_sprite[2], any_enum::little }, { index_sprite[3], any_enum::little },
	{ index_sprite[4], any_enum::little }, { index_sprite[5], any_enum::little } 
};




Page::Page(vector<Object_Scene*> cur_obj_ptr, vector<type_struct::type_object> cur_type, vector <type_interactions> cur_intr, vector <type_swich> сur_swich, vector<type_action> cur_act)
{
	for (int n = 0, act = 0, sw = 0; n < int(cur_obj_ptr.size()); n++)
	{
		this->objects.push_back(cur_obj_ptr[n]);// объектики
		objects_type[objects.back()] = cur_type[n]; //типы к объектикам
		if (cur_type[n] != type_struct::none)
		{
			objects_intreractions[objects.back()] = cur_intr[n]; // привязка типа взаимодействия к объектам

			if (cur_intr[n] == swich)
			{
				objects_swich[objects.back()] = сur_swich[sw]; // привязка к swich мапе по типа взаимодействия swich
				sw++;
			}
			else if (cur_intr[n] == action)
			{
				objects_action[objects.back()] = cur_act[act]; // привязка действия action по типу взаимодействия action
				act++;
			}
		}
	}
	All_fast = false;
}

bool Page::isFinish()
{
	if (int(objects.size()) == cur_obj)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Page::draw()
{
	if (int(objects.size()) < cur_obj)
	{
		return false;
	}
	if (isFinish() == true)
		return true;

	switch (objects_type[objects[cur_obj]])
	{
	case type_struct::sprite:
	{
				   if (objects_intreractions[objects[cur_obj]] == action)
				   {
					   auto data = objects[cur_obj]->draw();
					   auto cur_action_sprite = &objects_action[objects[cur_obj]];

					   if (*cur_action_sprite == scale_lit || *cur_action_sprite == scale_mid || *cur_action_sprite == scale_big)
					   {
						   auto cur_scale_chapter = &name_for_scale[static_cast<Object_Sprite*>(objects[cur_obj])->Get_name()];

						   switch (*cur_action_sprite)
						   {
						   case scale_lit:
							   *cur_scale_chapter = any_enum::little;
							   break;
						   case scale_mid:
							   *cur_scale_chapter = any_enum::standart;
							   break;
						   case scale_big:
							   *cur_scale_chapter = any_enum::big;
							   break;
						   default:
							   break;
						   }

						   if (data.old_ptr != nullptr)
						   {
							   auto cur_scale_sprite = &sprite_for_scale[name_for_node[static_cast<Object_Sprite*>(objects[cur_obj])->Get_name()]];

							   switch (*cur_action_sprite)
							   {
							   case scale_lit:
								   *cur_scale_sprite = any_enum::little;
								   break;
							   case scale_mid:
								   *cur_scale_sprite = any_enum::standart;
								   break;
							   case scale_big:
								   *cur_scale_sprite = any_enum::big;
								   break;
							   default:
								   break;
							   }
							   cur_obj++;									
							   Action_sprite::action(data.old_ptr, objects_action[objects[cur_obj - 1]], static_cast<Object_Sprite*>(objects[cur_obj - 1])->Get_hide(), objects[cur_obj - 1]->Get_wait(), this);  
						   }
						   else
						   {
							   cur_obj++;
							   this->draw();
						   }
							   
					   }
					   else
					   {
						   cur_obj++;
						   if (data.old_ptr != nullptr)
							 Action_sprite::action(data.old_ptr, objects_action[objects[cur_obj - 1]], static_cast<Object_Sprite*>(objects[cur_obj - 1])->Get_hide(), objects[cur_obj - 1]->Get_wait(), this);
					   }

				   }
				   else if (objects_intreractions[objects[cur_obj]] == swich)
				   {
					   auto data = objects[cur_obj]->draw();
					   auto cur_scale_chapter = name_for_scale[static_cast<Object_Sprite*>(objects[cur_obj])->Get_name()];
					   auto cur_scale_sprite = &sprite_for_scale[name_for_node[static_cast<Object_Sprite*>(objects[cur_obj])->Get_name()]];

					   auto sp_scale([=](Node *search)
					   {
						   for (int n = 0; n < 6; n++)
						   {
							   if (*index_sprite[n] == search)
							   {
								   return index_sprite[n];
							   }
						   }
						   return static_cast<Node**>(nullptr);
					   });

					   auto new_scale_node = sp_scale(data.new_ptr);

					   if (new_scale_node != nullptr)
					   {
						   if (sprite_for_scale[new_scale_node] != cur_scale_chapter && static_cast<Object_Sprite*>(objects[cur_obj])->Get_hide() != true)
						   {
							   switch (cur_scale_chapter)
							   {
							   case any_enum::little:
							   {
								   float cur_scale = 1.0f;
								   auto sprite = static_cast<Sprite*>(data.new_ptr->getChildByName("Sprite"));
								   sprite->setScale(cur_scale);
								   *cur_scale_sprite = any_enum::little;
								   break;
							   }

							   case any_enum::standart:
							   {
								   float cur_scale = 1.5f;
								   auto sprite = static_cast<Sprite*>(data.new_ptr->getChildByName("Sprite"));
								   sprite->setScale(cur_scale);
								   *cur_scale_sprite = any_enum::standart;
								   break;
							   }
							   case any_enum::big:
							   {
								   float cur_scale = 2.0f;
								   auto sprite = static_cast<Sprite*>(data.new_ptr->getChildByName("Sprite"));
								   sprite->setScale(cur_scale);
								   *cur_scale_sprite = any_enum::big;

								   break;
							   }

							   default:
								   break;
							   }
						   }					  
					   }
					   cur_obj++;//полагаю проверку сюда на то что есть ли новая нода если они одинаковы - не вызывать(подумать с вейтами)
					   Action_sprite::swich(data.old_ptr, data.new_ptr, objects_swich[objects[cur_obj - 1]], static_cast<Object_Sprite*>(objects[cur_obj - 1])->Get_hide(), objects[cur_obj - 1]->Get_wait(), this);
					   
				   }
				   break;
	}
	case type_struct::scene:
	{
				  if (objects_intreractions[objects[cur_obj]] == action)
				  {
					  objects[cur_obj]->draw();
					  cur_obj++;
					  Action_scene::action(objects[cur_obj-1]->Get_Node(), objects_action[objects[cur_obj-1]], objects[cur_obj-1]->Get_wait(), this);
				  }
				  else if (objects_intreractions[objects[cur_obj]] == swich)
				  {
					  auto data = objects[cur_obj]->draw();
					  cur_obj++;
					  Action_scene::swich(data.old_ptr, data.new_ptr, objects_swich[objects[cur_obj - 1]], objects[cur_obj - 1]->Get_wait(), this);


				  }
				  break;
	}
	case type_struct::ore:
	{
							 if (objects_intreractions[objects[cur_obj]] == action)
							 {
								 auto data = objects[cur_obj]->draw();
								 cur_obj++;
								 if (objects_action[objects[cur_obj - 1]] == UNLOCK_ORE)//логику для разблокировки оре пихнул сюда куда в другое место - не предумал
								 {
									 int cur_ore = static_cast<Object_ORE*>(objects[cur_obj - 1])->Get_Ore_num();
									 if (cur_ore <64 && cur_ore> -1)
										 chek_ore_lock(cur_ore);
								 }
								 else
								 {
									 if (data.old_ptr == OREL)
									 {
										 action_ore(any_enum::left, objects_action[objects[cur_obj - 1]]);
									 }
									 if (data.old_ptr == ORER)
									 {
										 action_ore(any_enum::right, objects_action[objects[cur_obj - 1]]);
									 }
								 }
								 Action_ore::action(data.old_ptr, objects_action[objects[cur_obj - 1]], objects[cur_obj - 1]->Get_wait(), this); 
							 }
							 break;
	}
	case type_struct::condition:
	{
								   if (objects_intreractions[objects[cur_obj]] == action)
								   {
									   auto data = objects[cur_obj]->draw();
									   if (data.old_ptr == nullptr)
									   {
										   while (objects[cur_obj]->Get_wait() != true)//скипает объекьы до слежуещего бокса(если условие не прошло)
											   cur_obj++;
										   cur_obj++;
									   }
									   else 
										   cur_obj++;
									   this->draw(); 
								   }	
								   break;
	}
	case type_struct::audio:
	{
							   if (objects_intreractions[objects[cur_obj]] == action)
							   {
								   auto data = objects[cur_obj]->draw();
								   cur_obj++;
								   this->draw();
							   }
							   break;
	}
	case type_struct::text:
	{
				 if (objects_intreractions[objects[cur_obj]] == action)
				 {
					 auto data = objects[cur_obj]->draw();
					 cur_obj++;
					 Action_textbox::action(data.old_ptr, objects_action[objects[cur_obj - 1]], objects[cur_obj - 1]->Get_wait(), this);
				 }
				 else if (objects_intreractions[objects[cur_obj]] == swich)
				 {
					 auto data = objects[cur_obj]->draw();
					 cur_obj++;
				 }
				   break;
	}
	case type_struct::teleport://поскольку это загрузка скрипта там идет полная отчистка всего - дальнейший проигрыш объектов бесмыслен
	{
		if (objects_intreractions[objects[cur_obj]] != unknown)
		{
			auto data = objects[cur_obj]->draw();
			cur_obj++;
		}
		break;
	}
	case type_struct::live2d://поскольку это загрузка скрипта там идет полная отчистка всего - дальнейший проигрыш объектов бесмыслен
	{
		if (objects_intreractions[objects[cur_obj]] == swich)
		{
			auto data = objects[cur_obj]->draw();
			cur_obj++;
			Action_scene::swich(data.old_ptr, data.new_ptr, NULL_TIME, objects[cur_obj - 1]->Get_wait(), this);
		}
		else
		{
			auto data = objects[cur_obj]->draw();
			cur_obj++;
			Action_model::action(data.new_ptr, objects_action[objects[cur_obj - 1]], objects[cur_obj - 1]->Get_wait(), this);
		}
		break;
	}
	default:
	{
			   return true;
			   break;
	}
	}
	return true;
}

void Page::FastFinish()
{
	cur_obj = 0;
	All_fast = true;
	this->draw();
}

Page::~Page()
{
	for (int n = 0; n < objects.size(); n++)
	{
		delete objects[n];
	}
	objects.clear();

}