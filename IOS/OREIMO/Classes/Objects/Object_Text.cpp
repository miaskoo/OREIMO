#include "Object_Text.h"
#include "ui\UIText.h"
extern ui::Text *Label_text;
extern ui::Text *Label_name;
extern Node* Text_Box;
extern void voice_play(string dir);



Object_Text::Object_Text(string cur_name, string cur_text, string cur_voice)
{
	my_name = cur_name;
	my_text = cur_text;
	my_voice = cur_voice;
	if (my_name == "None")
		my_name = "";
}



swich_node Object_Text::draw()
{
	if (my_text == "")
	{
		this->my_node = Text_Box;
	}
	else
	{
		Label_name->setString(my_name);
		Label_text->setString(my_text);
		voice_play(my_voice);
		this->my_node = Label_text;
	}
	return swich_node{ this->my_node, nullptr };
}