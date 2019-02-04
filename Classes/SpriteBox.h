
#include <memory> // для использования smart_pointer
#include <vector>
#include <string>

using namespace std;
using namespace cocos2d;

struct chek_id
{
	string id1 = "empty";
	string id2 = "empty";
	string id3 = "empty";
};

chek_id active_sprite;


class SPRITEBOX
{
private:

	int id;
	int name;
	vector<string> blink; // глаза

	vector<string> speak; // рот

	//SPRITE
	string sprite = "None";
	//SPRITE

	//SAMPLE
	string sprite_sample = "Sprites\\Samples\\Sample_Sprite.png";
	string blink_samle = "Sprites\\Samples\\Sample_Blink.png";
	string speak_sample = "Sprites\\Samples\\Sample_Speak.png";
	//SAMPLE

	string action = "None";
	bool hide = false; //отвечает за скрытие спрайта
	bool inf = false;
	bool simplebox = false;
	vector<int> pos_x; //координаты по x
	vector<int> pos_y; //координаты по y
	char LCR = 'C'; //координаты по основному x по умолчанию центр  D - между левым и средним P - между правым и средним


	string custom_swich = "None"; // Переменная отвечающая за управление эффектом появления спрайта - если по умолчанию должна быть равна нулю есть два состаяния - движение слева на право - LTR и справа налево - RTL


public:

	int Set_id(string chapter, bool hide)
	{
		if (chapter == active_sprite.id1)
		{
			if (hide == false)
				active_sprite.id1 = chapter;
			else
				active_sprite.id1 = "empty";

			return 1;
		}
		else if (chapter == active_sprite.id2)
		{
			if (hide == false)
				active_sprite.id2 = chapter;
			else
				active_sprite.id2 = "empty";

			return 2;
		}
		else if (chapter == active_sprite.id3)
		{
			if (hide == false)
				active_sprite.id3 = chapter;
			else
				active_sprite.id3 = "empty";

			return 3;
		}
		else if (active_sprite.id1 == "empty")
		{
			active_sprite.id1 = chapter;
			return 1;
		}
		else if (active_sprite.id2 == "empty")
		{
			active_sprite.id2 = chapter;
			return 2;
		}
		else if (active_sprite.id3 == "empty")
		{
			active_sprite.id3 = chapter;
			return 3;
		}
	}

	int Set_Sprite(vector<string> dir, vector<string> command) //Получает вектор дирректорий всех спрайтов и команды определяющие спрайт а также id
	{
		if (command[0] == "<SIMPLE>")
		{
			command.erase(command.begin());
			simplebox = true;
		}
		if (command[0] == "HIDE")
		{
			this->id = Set_id(command[1], true);// ----------------------------------------------Сделать выход из спрайта по имени------------------------------------------ 
			this->hide = true;
			if (command.size() > 2)
			{
				if (command[2] == "<actionsprite>")
				{
					command.erase(command.begin() + 2);
					action = command[2];
					command.erase(command.begin() + 2);
				}
				if (command.size() > 2)
				{
					custom_swich = string(command[2]);
				}
			}
			//this->inf = true;
			return this->id;
		}

		this->id = Set_id(command[0], false); // определение id спрайта

		if (command[1] == "<actionsprite>")
		{
			command.erase(command.begin() + 1);
			action = command[1];
			command.erase(command.begin() + 1);
			if (command.size() < 2)
				return this->id;
		}


		for (int i = 0; i < dir.size(); i++)
		{
			if (string(dir[i]) == string("{" + command[0] + "}"))
			{
				while (string(dir[i]) != string("{/" + command[0] + "}"))
				{
					i++;
					if (string(dir[i]) == string("|" + command[1] + "|"))
					{
						i++;
						sprite = dir[i];
						while (string(dir[i]) != string("|/" + command[1] + "|"))
						{
							i++;
							if (string(dir[i]) == string(command[2]))
							{
								while (string(dir[i + 4]) != string("/" + command[2]))
								{
									i++;
									blink.push_back(dir[i]);
									speak.push_back(dir[i + 3]);
								}

							}
						}
					}
				}
			}
		}
		this->inf = true;
		if (command.size() > 3) // если есть - определить положение
		{
			LCR = string(command[3])[0];
			if (command.size() > 4)
			{
				custom_swich = string(command[4]);
			}
		}
		/*
		const char AY[] = { 'A', 'Y' };
		const char KY[] = { 'K', 'Y' };
		const char KU[] = { 'K', 'U' };
		const char MA[] = { 'M', 'A' };
		const char KI[] = { 'K', 'I' };
		const char DA[] = { 'D', 'A' };
		const char SA[] = { 'S', 'A' };
		const char SI[] = { 'S', 'I' };*/

		if (command[0] == "AY")
			name = 0;
		if (command[0] == "KY")
			name = 1;
		if (command[0] == "KU")
			name = 2;
		if (command[0] == "MA")
			name = 3;
		if (command[0] == "KI")
			name = 4;
		if (command[0] == "DA")
			name = 5;
		if (command[0] == "SA")
			name = 6;
		if (command[0] == "SI")
			name = 7;

		if (command[0] == "KI") //-------------------------------KIRINO-------------------------------//
		{
			if (command[1] == "1C" || command[1] == "2C" || command[1] == "3C" || command[1] == "1C_OLD" || command[1] == "3C_OLD")
			{
				//SPRITE//
				pos_x.push_back(0);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(204);
				pos_y.push_back(373);
				//BLINK//

				//SPEAK//
				pos_x.push_back(235);
				pos_y.push_back(358);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(115 - (pos_x[0] * 1.77));
					pos_y.push_back(-288);
					break;
				case 'L':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 285);
					pos_y.push_back(-288);
					break;
				case 'R':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 285);
					pos_y.push_back(-288);
					break;
				case 'D':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 140);
					pos_y.push_back(-288);
					break;
				case 'P':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 140);
					pos_y.push_back(-288);
					break;
				}
				//POSITION

			}
			if (command[1] == "1L" || command[1] == "2L" || command[1] == "3L" || command[1] == "1L_OLD")
			{
				//SPRITE//
				pos_x.push_back(0);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(214);
				pos_y.push_back(367);
				//BLINK//

				//SPEAK//
				pos_x.push_back(247);
				pos_y.push_back(358);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(115 - (pos_x[0] * 1.77));
					pos_y.push_back(-288);
					break;
				case 'L':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 285);
					pos_y.push_back(-288);
					break;
				case 'R':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 285);
					pos_y.push_back(-288);
					break;
				case 'D':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 140);
					pos_y.push_back(-288);
					break;
				case 'P':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 140);
					pos_y.push_back(-288);
					break;
				}
				//POSITION

			}
			if (command[1] == "1R" || command[1] == "2R" || command[1] == "3R" || command[1] == "2R_OLD" || command[1] == "3R_OLD")
			{
				//SPRITE//
				pos_x.push_back(0);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(213);
				pos_y.push_back(359);
				//BLINK//

				//SPEAK//
				pos_x.push_back(237);
				pos_y.push_back(356);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(115 - (pos_x[0] * 1.77));
					pos_y.push_back(-288);
					break;
				case 'L':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 285);
					pos_y.push_back(-288);
					break;
				case 'R':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 285);
					pos_y.push_back(-288);
					break;
				case 'D':
					pos_x.push_back(115 - (pos_x[0] * 1.77) - 140);
					pos_y.push_back(-288);
					break;
				case 'P':
					pos_x.push_back(115 - (pos_x[0] * 1.77) + 140);
					pos_y.push_back(-288);
					break;
				}
				//POSITION
			}

		}
		//if (chapter == "SA") //-------------------------------SAORI-------------------------------//
		//{
		//	switch (LCR)
		//	{
		//	case 'L':
		//		pos_x.push_back(-230);
		//		pos_y.push_back(-220);
		//		break;
		//	case 'C':
		//		pos_x.push_back(120);// не проверено
		//		pos_y.push_back(-220);
		//		break;
		//	case 'R':
		//		pos_x.push_back(720);// не проверено
		//		pos_y.push_back(-220);
		//		break;
		//	}
		//}
		//if (chapter == "KU") //-------------------------------KURONEKO-------------------------------//
		//{
		//	switch (LCR)
		//	{
		//	case 'L':
		//		pos_x.push_back(-230);// не проверено
		//		pos_y.push_back(-360);
		//		break;
		//	case 'C':
		//		pos_x.push_back(120);// не проверено
		//		pos_y.push_back(-360);
		//		break;
		//	case 'R':
		//		pos_x.push_back(720);
		//		pos_y.push_back(-360);
		//		break;
		//	}
		//}
		if (command[0] == "AY") //-------------------------------AYASE-------------------------------//
		{
			if (command[1] == "1C" || command[1] == "2C" || command[1] == "1C_YAN" || command[1] == "2C_YAN")
			{
				//SPRITE//
				pos_x.push_back(252);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(69 + pos_x[0]);
				pos_y.push_back(378);
				//BLINK//

				//SPEAK//
				pos_x.push_back(107 + pos_x[0]);
				pos_y.push_back(361);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(345 - (pos_x[0] * 1.77));
					pos_y.push_back(-288);
					break;
				case 'L':
					pos_x.push_back(345 - (pos_x[0] * 1.77) - 285);
					pos_y.push_back(-288);
					break;
				case 'R':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 285);
					pos_y.push_back(-288);
					break;
				case 'D':
					pos_x.push_back(345 - (pos_x[0] * 1.77) - 140);
					pos_y.push_back(-288);
					break;
				case 'P':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 140);
					pos_y.push_back(-288);
					break;
				}
				//POSITION
			}
			if (command[1] == "1L" || command[1] == "2L" || command[1] == "1L_YAN" || command[1] == "2L_YAN" || command[1] == "2L_OLD")
			{
				//SPRITE//
				pos_x.push_back(212);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(44 + pos_x[0]);
				pos_y.push_back(374);
				//BLINK//

				//SPEAK//
				pos_x.push_back(87 + pos_x[0]);
				pos_y.push_back(363);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 36);
					pos_y.push_back(-290);
					break;
				case 'L':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 36 - 285);
					pos_y.push_back(-290);
					break;
				case 'R':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 36 + 285);
					pos_y.push_back(-290);
					break;
				case 'D':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 36 - 140);
					pos_y.push_back(-290);
					break;
				case 'P':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 36 + 140);
					pos_y.push_back(-290);
					break;
				}
				//POSITION

			}
			if (command[1] == "1R" || command[1] == "2R" || command[1] == "1R_YAN" || command[1] == "2R_YAN" || command[1] == "1R_OLD")
			{
				//SPRITE//
				pos_x.push_back(252);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(73 + pos_x[0]);
				pos_y.push_back(372);
				//BLINK//

				//SPEAK//
				pos_x.push_back(108 + pos_x[0]);
				pos_y.push_back(366);
				//SPEAK//

				//POSITION
				switch (LCR)
				{
				case 'C':
					pos_x.push_back(345 - (pos_x[0] * 1.77));
					pos_y.push_back(-288);
					break;
				case 'L':
					pos_x.push_back(345 - (pos_x[0] * 1.77) - 285);
					pos_y.push_back(-288);
					break;
				case 'R':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 285);
					pos_y.push_back(-288);
					break;
				case 'D':
					pos_x.push_back(345 - (pos_x[0] * 1.77) - 140);
					pos_y.push_back(-288);
					break;
				case 'P':
					pos_x.push_back(345 - (pos_x[0] * 1.77) + 140);
					pos_y.push_back(-288);
					break;
				}
				//POSITION
			}

		}
		if (command[0] == "DA") //-------------------------------DAISUKE-------------------------------//
		{
			if (command[1] == "1C" || command[1] == "1C_OLD")
			{
				//SPRITE//
				pos_x.push_back(0);
				pos_y.push_back(0);
				//SPRITE//

				//BLINK//
				pos_x.push_back(108);
				pos_y.push_back(406);
				//BLINK//

				//SPEAK//
				pos_x.push_back(129);
				pos_y.push_back(348);
				//SPEAK//
			}
			switch (LCR)
			{
			case 'L':
				pos_x.push_back(-230);
				pos_y.push_back(-360); // не проверено
				break;
			case 'C':
				pos_x.push_back(280);
				pos_y.push_back(-200);
				break;
			case 'R':
				pos_x.push_back(720); // не проверено
				pos_y.push_back(-360);
				break;
			}
		}
		return this->id;
	}

	void operator=(const SPRITEBOX& x)
	{
		sprite = x.sprite;
		blink.assign(x.blink.begin(), x.blink.end());
		speak.assign(x.speak.begin(), x.speak.end());
		pos_x.assign(x.pos_x.begin(), x.pos_x.end());
		pos_y.assign(x.pos_y.begin(), x.pos_y.end());
		LCR = x.LCR;
	}

	bool operator==(const SPRITEBOX& x)
	{
		if (sprite == x.sprite)
			return(true);
		else
			return(false);
	}

	int Get_id()
	{
		return this->id;
	}

	vector<Vec2> Get_position()
	{
		if ((pos_x.size() < 4 || pos_y.size() < 4) && inf == true && hide == false)
			throw string("ERROR_MISSING_POSITION");
		vector<Vec2> temp;
		if (hide == false)
		{
			temp.push_back(Vec2(pos_x[0], pos_y[0]));
			temp.push_back(Vec2(pos_x[1], pos_y[1]));
			temp.push_back(Vec2(pos_x[2], pos_y[2]));
			temp.push_back(Vec2(pos_x[3], pos_y[3]));
		}
		return temp;
	}

	vector<string> Get_texture()
	{
		vector<string> temp;
		if ((sprite == "None" || blink.size() < 3 || speak.size() < 3) && inf == true && hide == false)
			throw string("ERROR_MISSING_TEXTURE");
		if (hide == false)
		{
			temp.push_back(sprite);
			temp.push_back(blink[0]);
			temp.push_back(speak[0]);
			temp.push_back(blink[1]);
			temp.push_back(blink[2]);
		}
		return temp;
	}

	bool Get_hide()
	{
		return hide;
	}

	string Get_swich()
	{
		return custom_swich;
	}

	string Get_action()
	{
		return action;
	}

	bool Check_inf()
	{
		return this->inf;
	}

	bool Chek_simplebox()
	{
		return this->simplebox;
	}
};

