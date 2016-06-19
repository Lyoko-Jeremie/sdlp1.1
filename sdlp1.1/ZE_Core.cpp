
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "ZE_Core.h"
#include "ZE_Global.h"
#include "ZE_EventManager.h"
#include "ZE_Error.h"
#include "ZE_Fraps.h"
#include "ZE_Controller.h"
#include "ZE_EngineGlobalState.h"

using namespace std;

std::atomic_bool ZeroEngineSingleton{ false };

ZeroEngine::ZeroEngine()
{
	if (ZeroEngineSingleton.exchange(true))
	{
		throw std::runtime_error("ZeroEngine must be singleton.");
	}

	GlobalState->ZE_eventHandler.reset(new EventManager);
	GlobalState->ZE_error.reset(new Error);
	fraps = make_unique<Fraps>(this->getNewDisplayObjectIndex());
	GlobalState->ZE_stage.reset(new Sprite);
}

ZeroEngine::~ZeroEngine()
{
	Close();
	GlobalState->ZE_stage.reset();
	fraps.reset();
	GlobalState->ZE_error.reset();
	GlobalState->ZE_eventHandler.reset();
	GlobalState.reset();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	//�˳�
	cout << "ZeroEngine::~ZeroEngine()" << endl;
}

bool ZeroEngine::Init(string Title, int windowWidth, int windowHeight, bool useVSync, std::string defaultFontFile) const
{
	bool success = true;
	if (!Init_SDL(Title, windowWidth, windowHeight))
	{
		success = false;
	}
	else if (!Init_SDL_Image(useVSync))
	{
		success = false;
	}
	else if (!Init_SDL_ttf())
	{
		success = false;
	}
	else if (!Init_SDL_Mixer())
	{
		success = false;
	}


	// ��������
	GlobalState->defaultFont = make_shared<Font>("default", defaultFontFile);


	function<void(SDL_Event)> addJoyStick = [](SDL_Event evt)->void
	{
		GlobalState->ZE_Controllers.emplace_back(new Controller(SDL_NumJoysticks() - 1));
	};

	function<void(SDL_Event)> removeJoyStick = [](SDL_Event evt)->void
	{
		//delete(ZE_Controllers[evt.jdevice.which]);
		//ZE_Controllers[evt.jdevice.which].reset();
		// FIXME ����ʹ���±���з��ʲ�����ĳ�������ըô
		GlobalState->ZE_Controllers.erase(GlobalState->ZE_Controllers.begin() + evt.jdevice.which);
	};
	GlobalState->ZE_stage->addEventListener(EventMode::RawEventMode, SDL_JOYDEVICEADDED, addJoyStick);
	GlobalState->ZE_stage->addEventListener(EventMode::RawEventMode, SDL_JOYDEVICEREMOVED, removeJoyStick);

	return success;
}

bool ZeroEngine::Init_SDL(string Title, int windowWidth, int windowHeight)
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_AUDIO) < 0)
	{
		//Ŀǰ������VIDEO flag����ֻ��ʼ��SDL����Ƶģ��
		GlobalState->ZE_error->PopDebugConsole_SDLError("SDL could not initialize!");
		//����ʼ��ʧ�������error�൯�������Ժ�һ��
		success = false;
	}
	else
	{
		const char* tit = Title.c_str();
		//��ΪSDL�Ǵ�C����������Ҫ��stringת��ΪC��char�����㲻���ô�C���������������ֻ���ܴ�C
		GlobalState->g_ZE_Window.reset(SDL_CreateWindow(tit, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN));
		//�������壺���ڱ��⣬���ڳ���λ�õ�X����(�ñ������岻��)�����ڳ���λ�õ�Y����(�ñ������岻��)�����ڿ�ȣ�
		//���ڸ߶ȣ���������(���������ʾ�����򿪴��ڣ����Ǿ���������ʲô�������滻��ʲô���滻����ʲô���ö���֪��)
		if (GlobalState->g_ZE_Window == nullptr)
		{
			GlobalState->ZE_error->PopDebugConsole_SDLError("Window could not be created!");
			success = false;
		}
		else
		{
			GlobalState->g_ZE_MainSurface.reset(SDL_GetWindowSurface(GlobalState->g_ZE_Window.get()));
			//ץȡ���ڵ���Surface�����еĻ��ƶ����������surface��
		}
	}

	return success;
}

bool ZeroEngine::Init_SDL_Image(bool useVSync) const
{
	bool success = true;

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) == imgFlags))
	{
		//����ֻ��ʼ����PNG��IMG�ĳ�ʼ���������᷵�ض�Ӧ��FLAG����ʾ�ɹ�
		//�в�֪������������������������ã���������ô��������������ʲô
		//����һ��SDL_IMAGE֧�ֶ��ָ�ʽ�治�Ǹǵģ����˳���JPG PNG֮���Ȼ��֧��GIF������ټ�������һЩ�����еĸ�ʽ
		//BTW��IMG_INIT_PNG == 2
		GlobalState->ZE_error->PopDebugConsole_SDL_ImageError("SDL_image could not initialize!");
		success = false;
	}

	int renderFlag;
	if (useVSync)
		renderFlag = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	else
		renderFlag = SDL_RENDERER_ACCELERATED;
	GlobalState->g_ZE_MainRenderer.reset(SDL_CreateRenderer(GlobalState->g_ZE_Window.get(), -1, renderFlag));
	//��ʼ��������Ⱦ��
	if (GlobalState->g_ZE_MainRenderer == nullptr)
	{
		GlobalState->ZE_error->PopDebugConsole_SDLError("Renderer could not be created!");
		success = false;
	}
	else
	{
		SDL_SetRenderDrawColor(GlobalState->g_ZE_MainRenderer.get(), stageColor.red, stageColor.green, stageColor.blue, 1);
		//������Ⱦ���Ļ�����ɫ
		//Ҫ����Ⱦ����Ĭ��ͼ�εĻ�����SDL_RENDERDRAWRECT�����Ҫ���ϵ��л�������ɫ��
		//����Ҫ��̨�ǰ�ɫ�ģ������Ǻ�ɫ�ģ���Ҫ�Ȼ�����̨���ٻ��췽�飬��һ��ѭ�����л��ذ�ɫ
	}

	return success;
}

bool ZeroEngine::Init_SDL_ttf()
{
	bool success = true;
	if (TTF_Init() == -1)
	{
		GlobalState->ZE_error->PopDebugConsole_SDL_ttfError("SDL_ttf could not initialize!");
		success = false;
	}
	return success;
}

bool ZeroEngine::Init_SDL_Mixer()
{
	bool success = true;
	if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) < 0)
	{
		success = false;
		GlobalState->ZE_error->PopDebugConsole_SDL_MixerError("SDL_mixer could not initialize!");
	}
	else
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			success = false;
			GlobalState->ZE_error->PopDebugConsole_SDL_MixerError("cuold not open audio on SDL_mixer!");
		}
	}

	return success;
}

void ZeroEngine::Start(Game* userGame)
{
	maingame = userGame;
	fraps->setUp();
	while (!GlobalState->ZE_QUIT_MAIN_LOOP)
	{

		//�����¼�
		GlobalState->ZE_eventHandler->handleEvent();
		//���
		SDL_RenderClear(GlobalState->g_ZE_MainRenderer.get());
		//���߼�
		maingame->MainLoop();
		//�ػ�
		GlobalState->ZE_stage->Render();
		//��frapsִ���߼�
		fraps->setText();
		fraps->Render();
		//�ı��Ĭ����ɫ
		SDL_SetRenderDrawColor(GlobalState->g_ZE_MainRenderer.get(), stageColor.red, stageColor.green, stageColor.blue, 1);
		//��ˢ��
		SDL_RenderPresent(GlobalState->g_ZE_MainRenderer.get());
	}
	Close();
}

size_t ZeroEngine::getNewDisplayObjectIndex()
{
	return ++display_object_index;
}

void ZeroEngine::Close() const
{
	//for (auto& con : ZE_Controllers)
	//{
	//	//delete(con);
	//	//con = NULL;
	//	con.reset();
	//}
	GlobalState->ZE_Controllers.clear();

	//������̨
	GlobalState->ZE_stage->dispose();
	//�����û��Ĺرշ���
	maingame->Close();

	// ���������ѭ��Ӧ�����ʼ��˳���෴
	// �ͷű���ָ��
	//SDL_FreeSurface(GlobalState->g_ZE_MainSurface);
	//GlobalState->g_ZE_MainSurface = NULL;
	GlobalState->g_ZE_MainSurface.reset();
	////ɾ����Ⱦ��
	//SDL_DestroyRenderer(GlobalState->g_ZE_MainRenderer);
	//GlobalState->g_ZE_MainRenderer = NULL;
	GlobalState->g_ZE_MainRenderer.reset();
	//ɾ��SDL����
	//SDL_DestroyWindow(GlobalState->g_ZE_Window);
	//GlobalState->g_ZE_Window = NULL;
	GlobalState->g_ZE_Window.reset();
	//���뽫ָ����շ����Ұָ��
	Mix_CloseAudio();
	while (Mix_Init(0))
	{
		Mix_Quit();
	}
	//���Ĭ������  
	//��Ϊ�����ʹ����SDL�ռ䣬Ȼ��������ȫ�ֱ����������ڱ����泤��������Ҫ��SDL�ر�ǰ�ֶ��ͷ�
	//�����Զ��ͷŻᷢ����SDL�رպ�exe����ǰ
	GlobalState->defaultFont.reset();


}
