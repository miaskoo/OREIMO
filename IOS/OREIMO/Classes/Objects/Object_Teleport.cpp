#include "Object_Teleport.h"
extern bool load_script_exept(std::string dir = "");

Object_Teleport::Object_Teleport(function<void()> _update_load, std::string _buffer)
{
	this->update_load = _update_load;
	this->buffer = _buffer;
	this->load_script = true;
}

Object_Teleport::Object_Teleport(function<void(std::string)> _smeh_page, std::string _buffer, bool z)
{
	this->smeh_page = _smeh_page;
	this->buffer = _buffer;
	this->load_script = false;
}

swich_node Object_Teleport::draw()
{
	if (this->load_script == true)
	{
		if (load_script_exept(this->buffer) == true)//������ ������
		{
			this->update_load();//��������� ���������� �����
		}
	}
	else
	{
		this->smeh_page(this->buffer);//��������� �� ���������
	}
	return { nullptr, nullptr };
}