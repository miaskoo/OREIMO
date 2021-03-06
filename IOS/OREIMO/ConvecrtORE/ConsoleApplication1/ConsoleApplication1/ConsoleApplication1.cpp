
#include "stdafx.h"
#include <string> 
#include <locale> 
#include <codecvt> 

using namespace std;


struct data_obj
{
	int my_type = 2;//текст
	int my_inter = 0;
	int my_swich = 0;
	int my_action = 0;
	int my_name = 0;
	int my_position = 0;
	std::string data1 = "";
	std::string data2 = "";
	std::string data3 = "";
	bool hide = false;

};

data_obj text_pres{ 2,0,0,0,0,0,"","","",false };
data_obj sound_pres{ 5,1,0,0,0,0, "1", "", "", false };

struct page_obj
{
	int cur_box_count = NULL;// количество боксов
	map<int, int> cur_row_count; //количество дейсвий по номеру бокса

	int cur_box_smeh = NULL; //смещает данные бокса по их количеству сейчас все настроено на смещение влево на один при добовлении более 3 коробок передвижение по ним нет
	map<int, int> cur_row_smeh; //относительно текущего бокса говорит какое сейчас будет смещение в рядах

	array<bool, 3> visable_id_box = { { false, false, false } };// Видимость боксов 

																///////////BOX//////ROW////VISIBLE/////
	map <int, map<int, bool>> visable_id_button; //получение по номеру бокса и номеру ряда информацию о видимости кнопок в полях

												 ///////////BOX//////ROW////DATA/////
	map<int, map<int, data_obj>> intedex_data; //получение по номеру бокса и номеру ряда информацию текущей ячейки
};

TCHAR main_dir[MAX_PATH];

vector<page_obj*> cur_page_data;  // хранит разобранную инфу страниц


int save_script(std::wstring dir);

struct CHAPTER_BOX
{
	int page;
	int type;//0 - text, 1 - sound
	std::string name;
	std::string text;
	std::string sound;
};



char buff[1024];
static void cp1251_to_utf8(char *out, const char *in) {
	static const int table[128] = {
		0x82D0,0x83D0,0x9A80E2,0x93D1,0x9E80E2,0xA680E2,0xA080E2,0xA180E2,
		0xAC82E2,0xB080E2,0x89D0,0xB980E2,0x8AD0,0x8CD0,0x8BD0,0x8FD0,
		0x92D1,0x9880E2,0x9980E2,0x9C80E2,0x9D80E2,0xA280E2,0x9380E2,0x9480E2,
		0,0xA284E2,0x99D1,0xBA80E2,0x9AD1,0x9CD1,0x9BD1,0x9FD1,
		0xA0C2,0x8ED0,0x9ED1,0x88D0,0xA4C2,0x90D2,0xA6C2,0xA7C2,
		0x81D0,0xA9C2,0x84D0,0xABC2,0xACC2,0xADC2,0xAEC2,0x87D0,
		0xB0C2,0xB1C2,0x86D0,0x96D1,0x91D2,0xB5C2,0xB6C2,0xB7C2,
		0x91D1,0x9684E2,0x94D1,0xBBC2,0x98D1,0x85D0,0x95D1,0x97D1,
		0x90D0,0x91D0,0x92D0,0x93D0,0x94D0,0x95D0,0x96D0,0x97D0,
		0x98D0,0x99D0,0x9AD0,0x9BD0,0x9CD0,0x9DD0,0x9ED0,0x9FD0,
		0xA0D0,0xA1D0,0xA2D0,0xA3D0,0xA4D0,0xA5D0,0xA6D0,0xA7D0,
		0xA8D0,0xA9D0,0xAAD0,0xABD0,0xACD0,0xADD0,0xAED0,0xAFD0,
		0xB0D0,0xB1D0,0xB2D0,0xB3D0,0xB4D0,0xB5D0,0xB6D0,0xB7D0,
		0xB8D0,0xB9D0,0xBAD0,0xBBD0,0xBCD0,0xBDD0,0xBED0,0xBFD0,
		0x80D1,0x81D1,0x82D1,0x83D1,0x84D1,0x85D1,0x86D1,0x87D1,
		0x88D1,0x89D1,0x8AD1,0x8BD1,0x8CD1,0x8DD1,0x8ED1,0x8FD1
	};
	while (*in)
		if (*in & 0x80) {
			int v = table[(int)(0x7f & *in++)];
			if (!v)
				continue;
			*out++ = (char)v;
			*out++ = (char)(v >> 8);
			if (v >>= 16)
				*out++ = (char)v;
		}
		else
			*out++ = *in++;
	*out = 0;
}

std::string string_to_hex(const std::string& input)
{
	static const char* const lut = "0123456789abcdef";
	size_t len = input.length();

	std::string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}
	return output;
}


int main()
{
	GetCurrentDirectory(MAX_PATH, main_dir);
	std::wstring main_dir_str = L"";
	std::wstring name_file = L"";
	for (int n = 0; n < wstring(main_dir).length(); n++)
	{
		main_dir_str += main_dir[n];
	}
	
	std::wstring obj_dir1 = main_dir_str + L"\\Obj\\*.obj";
	WIN32_FIND_DATA  search_object;
	HANDLE result_search = FindFirstFile((LPWSTR)obj_dir1.c_str(), &search_object);
	std::wstring cur_name = search_object.cFileName;
	cur_name = cur_name.substr(0, cur_name.length() - 4);
	if (cur_name.length() < 5)
		return 0;
	while (name_file != cur_name)
	{
		
		name_file = cur_name;

		std::wstring in_dir1 = main_dir_str + L"\\Obj\\" + name_file + L".obj";
		std::wstring in_dir2 = main_dir_str + L"\\txt_utf8\\" + name_file + L".extracted.txt";
		std::wstring out_dir = main_dir_str + L"\\dat\\" + name_file + L".dat";

		ifstream InFile1(in_dir1, ios::in | ios::binary);



		if (!InFile1)
		{
			cout << "Unable to open input file in_dir1" <<  endl;
			return -1;
		}

		//Skip header
		char Header[0x30];
		InFile1.read(Header, 0x30);

		int TotalLines = 0;
		std::vector<CHAPTER_BOX> pages;
		int cur_page = 0;
		while (InFile1)
		{
			CHAPTER_BOX temp_obj;
			temp_obj = CHAPTER_BOX{};
			unsigned _int32 Size = 0;

			InFile1.read((char*)&Size, 4);
			//Cheating end condition here
			if (Size == 0)
				break;

			TotalLines++;

			int Lines = Size / 0xF;

			//OutFile << "Entry 0x" << hex << TotalLines << " 0x" << Size << " bytes\t";

			char *Buffer = new char[Size];

			InFile1.seekg(-4, ios_base::cur);
			InFile1.read(Buffer, Size);

			//Let's figure out what this line is
			unsigned char Type = Buffer[4];

			switch (Type)
			{
			case 0x5C://звуки
			{
				temp_obj.type = 1;
				temp_obj.page = cur_page;

				temp_obj.sound += (int)Buffer[5] - 0x01;//пришлось удалять на один ибо иначе странные смешения
														//а может тут и вовсе неверно получаем цифру

				temp_obj.sound = string_to_hex(temp_obj.sound);

				pages.push_back(temp_obj);
				break;
			}
			case 0x64:
			{
				//OutFile << "64 - dialogue\t";
				//OutFile.write(Buffer, Size);
				temp_obj.type = 0;
				temp_obj.page = cur_page;

				temp_obj.sound += (int)Buffer[7];
				temp_obj.sound += (int)Buffer[8];
				temp_obj.sound += (int)Buffer[9];
				temp_obj.sound += (int)Buffer[10];


				temp_obj.sound = temp_obj.sound.substr(0, 2);
				std::reverse(temp_obj.sound.begin(), temp_obj.sound.end());
				temp_obj.sound = string_to_hex(temp_obj.sound);

				cur_page++;
				pages.push_back(temp_obj);
				break;
			}
			}

			//OutFile << endl << endl;

			delete[] Buffer;

		}
		InFile1.close();



		ifstream InFile2(in_dir2, ios::in | ios::binary);



		if (!InFile2)
		{
			cout << "Unable to open input file in_dir2" << endl;
			return -1;
		}

		const size_t size_b = 2;
		auto read = ([=, &InFile2]()
		{
			char bite;
			InFile2.read(&bite, 1);

			if (InFile2.eof() == true)
			{
				InFile2.close();
			}
			return bite;
		});

		auto check([=, &InFile2]()
		{
			char bite[2];
			InFile2.read(bite, 2);
			if (InFile2.eof() == true)
			{
				InFile2.close();
			}
			if (bite[0] == (char)0x80 && bite[1] == (char)0x8C)
				return true;

			InFile2.seekg(InFile2.cur - 2);
			return false;
		});

		auto check2([=, &InFile2]()
		{
			char bite[2];
			InFile2.read(bite, 2);
			if (InFile2.eof() == true)
			{
				InFile2.close();
			}
			if (bite[0] == (char)0x80 && bite[1] == (char)0x8d)
				return true;

			InFile2.seekg(InFile2.cur - 2);
			return false;
		});

		for (int n = 0; n<pages.size(); n++)
		{
			if (pages[n].type != 0)
				continue;
			char bite;
			memset(&bite, NULL, 1);
			bite = read();
			while (bite != (char)0x3e)//знак >
			{
				bite = read();
			}
			bite = read();

			std::string buff = "";
			std::string buff2 = "";
			while (true)
			{
				bite = read();
				if (bite == (char)0x0d)//переносы строки
				{
					continue;
				}
				if (bite == (char)0x0a)//переносы строки
				{
					continue;
				}
				if (bite == (char)0x5b)//проверка на открывающую скобку
				{
					buff2 += bite;
					while (!InFile2.eof())
					{
						bite = read();
						if (bite == (char)0x0d)//переносы строки
						{
							continue;
						}
						if (bite == (char)0x0a)//переносы строки
						{
							continue;
						}
						if (bite == (char)0x5b)//а тут на закрывающую
						{
							continue;
						}
						if (bite == (char)0x3c || InFile2.eof())//штука  <
						{
							pages[n].name = buff;
							pages[n].text = buff2;
							break;
						}
						buff2 += bite;
					}
					break;
				}
				if (bite == (char)0x3c || InFile2.eof())//штука  <
				{
					pages[n].name = "None";
					pages[n].text = buff;
					break;
				}
				buff += bite;
			}


		}

		InFile2.close();
		//cur_page_data.resize(pages.size());

		for (int n = 0; n < pages.size(); n++)
		{

			data_obj temp_obj;

			if (pages[n].type == 0)
			{
				temp_obj = text_pres;
				temp_obj.data1 = pages[n].name;
				temp_obj.data2 = pages[n].text;

				temp_obj.data3 = pages[n].sound;
			}
			else
			{
				temp_obj = sound_pres;
				temp_obj.data1 = "1";
				temp_obj.data2 = pages[n].sound;
			}




			page_obj temp;

			if (cur_page_data.size() > pages[n].page)
			{
				temp = *cur_page_data[pages[n].page];
			}

			temp.cur_box_count++;
			temp.cur_row_count[temp.intedex_data.size()] = 1;
			temp.intedex_data[temp.intedex_data.size()][0] = temp_obj;

			if (cur_page_data.size() > pages[n].page)
			{
				*cur_page_data[pages[n].page] = temp;
			}
			else
			{
				cur_page_data.push_back(new page_obj(temp));
			}

		}
		save_script(out_dir);
		pages.clear();
		cur_page_data.clear();
		FindNextFile(result_search, &search_object);
		cur_name = search_object.cFileName;
		cur_name = cur_name.substr(0, cur_name.length() - 4);
	}



	


	//ofstream OutFile(out_dir, ios::out | ios::trunc);
	//if (!OutFile)
	//{
	//	cout << "Unable to write log file " << out_dir << endl;
	//	return -1;
	//}

	//OutFile.close();
	return 0;
}

bool file_winapi(wchar_t *file_dir, size_t size, bool load = false)
{
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = L"OREIMO Files (*.dat)\0*.dat\0All Files (*.*)\0*.*\0";
	ofn.lpstrDefExt = (LPCWSTR)L"dat";
	ofn.lpstrFile = file_dir;
	ofn.nMaxFile = size;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;

	if (load == true)
	{
		if (GetOpenFileName(&ofn) == TRUE)
			return true;
		else
			return false;
	}
	else
	{
		if (GetSaveFileName(&ofn) == TRUE)
			return true;
		else
			return false;
	}
}


int save_script(std::wstring dir)
{
	const size_t size_dir = 260;
	//wchar_t file_dir[size_dir];

	//memset(file_dir, NULL, sizeof(file_dir));
	//if (file_winapi(file_dir, size_dir) == false)
	//{
	//	SetCurrentDirectory(main_dir);
	//	return 3;
	//}
	//else
	//{
	//	SetCurrentDirectory(main_dir);
	//}

	wstring cur_name_script = dir;//dir_save_script + "cus_script " + to_string(time(0));


	//for (int n = 0; n < sizeof(file_dir); n++)
	//{
	//	if (file_dir[n] == '\0')
	//		break;
	//	cur_name_script += file_dir[n];
	//}
	if (cur_name_script.length() == 0)
		return 3;

	vector<unsigned char>buff;

	int n = 0;
	int i = 0;
	int p = 0;

	buff.push_back((unsigned char)cur_page_data.size());//записали количество страничек скрипта
	for (p = 0; p < cur_page_data.size(); p++)
	{
		auto gpi([=]()
		{
			return cur_page_data[p];
		});
		auto sign = ([=](int &x, int &y) {
			return &gpi()->intedex_data[x][y];
		});

		buff.push_back((unsigned char)gpi()->cur_box_count);//создаем байт размерности страницы
															//int bite_page = buff.size() - 1;
		for (n = 0; n < gpi()->cur_box_count; n++)
		{
			buff.push_back((unsigned char)gpi()->cur_row_count[n]);//создаем байт размерности бокса
																   //int bite_box = buff.size() - 1;
			for (i = 0; i < gpi()->cur_row_count[n]; i++)
			{
				buff.push_back(0x00);//создаем байт размерности объекта бокса
				int bite_obj = buff.size() - 1;//номер байта в котором хранится информация о размере объекта
				buff.push_back(0x00);//создаем второй байт размерности объекта бокса

				auto obj = sign(n, i);//объект который записываем
				int size_obj = 0;
				buff.push_back((unsigned char)(obj->data1.length()/255));
				buff.push_back((unsigned char)(obj->data1.length()%255));
				if (obj->data1.length() > 10000 || obj->data2.length() > 10000)
					MessageBox(nullptr, L"Ошикба переполн", L"Ошибка", MB_OK);
				buff.push_back((unsigned char)(obj->data2.length()/255));
				buff.push_back((unsigned char)(obj->data2.length()%255));
				buff.push_back((unsigned char)(obj->data3.length()/255));
				buff.push_back((unsigned char)(obj->data3.length()%255));
				buff.push_back((unsigned char)obj->my_type);
				buff.push_back((unsigned char)obj->my_inter);
				buff.push_back((unsigned char)obj->my_swich);
				buff.push_back((unsigned char)obj->my_action);
				buff.push_back((unsigned char)obj->my_name);
				buff.push_back((unsigned char)obj->my_position);
				buff.push_back((unsigned char)obj->hide);
				for (int z = 0; z < obj->data1.length(); z++)
				{
					buff.push_back(obj->data1[z]);
				}

				for (int z = 0; z < obj->data2.length(); z++)
				{
					buff.push_back(obj->data2[z]);
				}

				for (int z = 0; z < obj->data3.length(); z++)
				{
					buff.push_back(obj->data3[z]);
				}


				size_obj += 15 + obj->data1.length() + obj->data2.length() + obj->data3.length();


				buff[bite_obj] = (unsigned char)(size_obj/255);
				buff[bite_obj+1] = (unsigned char)(size_obj%255);
			}
		}
	}

	ofstream file(cur_name_script, ios::binary);

	if (!file)
		return 2;

	if (buff.size() == 0)
		return 1;

	for (int _n = 0; _n < buff.size(); _n++)
	{
		file << buff[_n];
	}

	file.close();
	return 0;
}
