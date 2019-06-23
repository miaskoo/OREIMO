#pragma once
#include "Object_Scene.h"

class Object_Teleport : public Object_Scene
{
private:
	std::string buffer;
	function<void()> update_load;
	function<void(std::string)> smeh_page;
	bool load_script = false;
public:
	Object_Teleport(function<void()>, std::string);
	Object_Teleport(function<void(std::string)>, std::string, bool z);

	virtual swich_node draw() override;// проиницилизировать ноду с объектами с одновременным выводом 
};