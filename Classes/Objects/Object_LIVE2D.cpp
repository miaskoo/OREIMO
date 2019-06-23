#include "Object_LIVE2D.h"

#include "Live2D/LAppView.h"
#include "Live2D/LAppLive2DManager.h"
#include "Live2D/LAppDefine.h"
#include "Live2DFramework.h"
#include "Classes\Live2D\LAppModel.h"

extern Node *LIVE2D_NODE_CREATE;//созданная нода в LIVE2d объекте
//extern Node *LIVE2D_NODE_COCOS;//созданная нода в кокос сцене




namespace LIVE2D_CREATE
{
	LAppModel *LIVE2D_model = nullptr;//адрес созданной модельки
	int model_num = -1;//текущее имя модельки
	int model_tex = -1;

	void relese_model()
	{
		if (LIVE2D_model != nullptr)
		{
			LAppLive2DManager* Live2DMgr = LAppLive2DManager::getInstance(); // получаем объект управления
			Live2DMgr->releaseModel();//отчищаем модели
			LIVE2D_model = nullptr;//обнуляем указатель на модел
		}
	}

	void scep_live2d(Node* parent)
	{
		if (parent != nullptr && LIVE2D_NODE_CREATE != nullptr)
		{
			relese_model();
			model_num = -1; //сбрасываем ей имя
			model_tex = -1;// и текстурку
			LIVE2D_NODE_CREATE->removeFromParent();//открепляемя от своего прошлого отца
			LIVE2D_NODE_CREATE = LAppView::createDrawNode();//чистим и создаем новую
			parent->addChild(LIVE2D_NODE_CREATE);
		}
		else
		{
			MessageBoxA(nullptr, "Ошибка перепривязки модели", "Ошибка", MB_OK | MB_ICONERROR);
		}
	}
	bool check_model_settings(int model, int tex)
	{
		if (model == model_num && tex == model_tex)
			return false;
		return true;
	}

	bool check_live_model()
	{
		if (LIVE2D_model != nullptr)
			return true;
		return false;
	}

	void init_model(int model, int tex)
	{
		LAppLive2DManager* Live2DMgr = LAppLive2DManager::getInstance();
		LIVE2D_CREATE::LIVE2D_model = Live2DMgr->changeScene(model, tex);
	
		model_num = model;
		model_tex = tex;
	}

	void init_expression(vector<string> expressions)
	{
		if (LIVE2D_model != nullptr)
		{
			LIVE2D_model->setExpression(expressions);
		}
	}
}

void Get_model_from_name(any_enum::name_sprite my_name, int &index_model, int &index_tex)
{

	switch (my_name)
	{
	case any_enum::AY:
	{
		index_model = INDEX_MODEL_AYASE;
		if (index_tex >= INDEX_MODEL_AYASE_MAX)
			index_tex = INDEX_MODEL_AYASE_MAX - 1;
		break;
	}
	case any_enum::KA:
	{
		index_model = INDEX_MODEL_KANAKO;
		if (index_tex >= INDEX_MODEL_KANAKO_MAX)
			index_tex = INDEX_MODEL_KANAKO_MAX - 1;
		break;
	}
	case any_enum::KI:
	{
		index_model = INDEX_MODEL_KIRINO;
		if (index_tex >= INDEX_MODEL_KIRINO_MAX)
			index_tex = INDEX_MODEL_KIRINO_MAX - 1;
		break;
	}
	case any_enum::KU:
	{
		index_model = INDEX_MODEL_KURONEKO;
		if (index_tex >= INDEX_MODEL_KURONEKO_MAX)
			index_tex = INDEX_MODEL_KURONEKO_MAX - 1;
		break;
	}
	case any_enum::MA:
	{
		index_model = INDEX_MODEL_MANAMI;
		if (index_tex >= INDEX_MODEL_MANAMI_MAX)
			index_tex = INDEX_MODEL_MANAMI_MAX - 1;
		break;
	}
	case any_enum::SA:
	{
		index_model = INDEX_MODEL_SAORI;
		if (index_tex >= INDEX_MODEL_SAORI_MAX)
			index_tex = INDEX_MODEL_SAORI_MAX - 1;
		break;
	}
	default:
		break;
	}


}


vector<string> Get_ex_vector_from_string(std::string _expressions)
{
	vector<string> expression_main;
	std::string expressions = _expressions;
	auto search_ex([&expression_main, expressions](std::string buff) {
		if (expressions.find(buff) != std::string::npos)
		{
			int index = expressions.find(buff);
			if (expressions.substr(index + 4, 2) != "99")
				expression_main.push_back(expressions.substr(index, 6));
		}
	});
	search_ex("brow");
	search_ex("body");
	search_ex("head");
	search_ex("face");
	search_ex("hand");
	return expression_main;

}


Object_LIVE2D::Object_LIVE2D(any_enum::name_sprite _name, int _tex, std::string _args)
{
	this->name = _name;
	this->tex = _tex;
	this->args = _args;
	this->hide = false;
}

Object_LIVE2D::Object_LIVE2D(any_enum::name_sprite _name)
{
	this->name = _name;
	this->hide = true;
}

Object_LIVE2D::Object_LIVE2D(any_enum::name_sprite _name, std::string motion_name)
{
	this->name = _name;
	this->args = motion_name;
}

swich_node Object_LIVE2D::draw()//управление через ножу (перемешение или опасити - не работают с моделькой
// над писать ручной обрабочкик анимки для можельки)
{
	if (this->hide == false)
	{
		if (this->anim == false)
		{
			if (LIVE2D_CREATE::check_live_model() == false)
			{
				//LIVE2D_NODE_CREATE->setOpacity(0);
				Get_model_from_name(this->name, this->model, this->tex);//выхываю не в конструкторе - а зачем, если всеравно номер модельки нужен только при создании модели
				LIVE2D_CREATE::init_model(this->model, this->tex);
				//LIVE2D_NODE_CREATE->setPosition(-400, 0);
			}

			auto arg_vec = Get_ex_vector_from_string(this->args);
			if (arg_vec.size() > 0)
				LIVE2D_CREATE::init_expression(arg_vec);

		}
		
	}
	else
	{
		LIVE2D_CREATE::relese_model();
	}
	

	return { nullptr, LIVE2D_NODE_CREATE };
}