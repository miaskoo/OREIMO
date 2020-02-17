#include "Object_Scene.h"

extern Node *Game_mode;
extern Node *Scene1;
extern Node *Scene2;
extern Node *Sprite1;
extern Node *Sprite2;
extern Node *Sprite3;
extern Node *Sprite4;
extern Node *Sprite5;
extern Node *Sprite6;

map< Node**, any_enum::state_node> check_scene_for_state{ { &Scene1, any_enum::FREE }, { &Scene2, any_enum::FREE } };

array<Node**, 8> all_nodes = { &Scene1, &Scene2, &Sprite1, &Sprite2, &Sprite3, &Sprite4, &Sprite5, &Sprite6 };


GLProgramState *GetShader(any_enum::global_filtr state)
{
	switch (state)
	{
	case any_enum::sepia:
	{
		std::string shaderName = ".\\Resources\\Shaders\\sepia";
		auto glCache = GLProgramCache::getInstance();
		GLProgram* prog = glCache->getGLProgram(shaderName);
		GLProgramState* state = nullptr;
		auto fs = FileUtils::getInstance();
		auto fragPath = fs->fullPathForFilename(shaderName + ".frag");
		auto vertPath = fs->fullPathForFilename(shaderName + ".vert");
		std::string fragmentSource = fs->getStringFromFile(fragPath);
		std::string vertexSource = fs->getStringFromFile(vertPath);
		auto fragB = fragmentSource.c_str();
		auto vertB = vertexSource.c_str();
		prog = GLProgram::createWithByteArrays(vertB, fragB);
		if (prog != nullptr)
		{
			glCache->addGLProgram(prog, shaderName);
			auto for_ret = GLProgramState::getOrCreateWithGLProgram(prog);
			return for_ret;
		}
		break;
	}
	case any_enum::evening:
	{
		std::string shaderName = ".\\Resources\\Shaders\\evening";
		auto glCache = GLProgramCache::getInstance();
		GLProgram* prog = glCache->getGLProgram(shaderName);
		GLProgramState* state = nullptr;
		auto fs = FileUtils::getInstance();
		auto fragPath = fs->fullPathForFilename(shaderName + ".frag");
		auto vertPath = fs->fullPathForFilename(shaderName + ".vert");
		std::string fragmentSource = fs->getStringFromFile(fragPath);
		std::string vertexSource = fs->getStringFromFile(vertPath);
		auto fragB = fragmentSource.c_str();
		auto vertB = vertexSource.c_str();
		prog = GLProgram::createWithByteArrays(vertB, fragB);
		if (prog != nullptr)
		{
			glCache->addGLProgram(prog, shaderName);
			auto for_ret = GLProgramState::getOrCreateWithGLProgram(prog);
			return for_ret;
		}
		break;
	}
	case any_enum::night:
	{
		std::string shaderName = ".\\Resources\\Shaders\\night";
		auto glCache = GLProgramCache::getInstance();
		GLProgram* prog = glCache->getGLProgram(shaderName);
		GLProgramState* state = nullptr;
		auto fs = FileUtils::getInstance();
		auto fragPath = fs->fullPathForFilename(shaderName + ".frag");
		auto vertPath = fs->fullPathForFilename(shaderName + ".vert");
		std::string fragmentSource = fs->getStringFromFile(fragPath);
		std::string vertexSource = fs->getStringFromFile(vertPath);
		auto fragB = fragmentSource.c_str();
		auto vertB = vertexSource.c_str();
		prog = GLProgram::createWithByteArrays(vertB, fragB);
		if (prog != nullptr)
		{
			glCache->addGLProgram(prog, shaderName);
			auto for_ret = GLProgramState::getOrCreateWithGLProgram(prog);
			return for_ret;
		}
		break;
	}
	case any_enum::morning:
	{
		return GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP);
		break;
	}
	}
	return nullptr;
}

Object_Scene::Object_Scene(string type, int num, any_enum::global_filtr render_type)
{ 
	if (type == "CG")
	{
		if (num >= -1 && num < 168)
		{
			dir_obj = CG_DIR[num];
		}
	}
	else if (type == "BG")
	{
		if (num >= -1 && num < 83)
		{
			dir_obj = BG_DIR[num];
		}
	}
	this->state = render_type;
	
}

swich_node Object_Scene::draw()
{
	swich_node for_return{ nullptr, nullptr };
	Sprite *cur_sp = nullptr;
	if (dir_obj != "empty")
	{

		if (check_scene_for_state[&Scene1] == any_enum::FREE)
		{
			this->my_node = Scene1;
			for_return = { Scene2, Scene1 };
			check_scene_for_state[&Scene1] = any_enum::BUSY;
			check_scene_for_state[&Scene2] = any_enum::FREE;
		}
		else if (check_scene_for_state[&Scene2] == any_enum::FREE)
		{
			this->my_node = Scene2;
			for_return = { Scene1, Scene2 };
			check_scene_for_state[&Scene1] = any_enum::FREE;
			check_scene_for_state[&Scene2] = any_enum::BUSY;
		}


		cur_sp = static_cast<Sprite*>(this->my_node->getChildByName("Sprite"));
		cur_sp->setTexture(dir_obj);

		//смена рендера прорисовки ипользуется только в SWITCH !!!
		any_enum::global_filtr state_c = any_enum::morning;
		if (this->state == any_enum::sepia)
			state_c = any_enum::sepia;

		GLProgramState* state = GetShader(state_c);

		if (state != nullptr && cur_sp != nullptr)
		{
			cur_sp->setGLProgramState(state);
		}
		else
		{
			MessageBox("Ошибка создания шейдера!", "Ошибка!");
			std::terminate();
		}
	}
	else
	{
		this->my_node = check_scene_for_state[&Scene1] == any_enum::FREE ? Scene2 : Scene1;
		return for_return;
	}



	return for_return;
}