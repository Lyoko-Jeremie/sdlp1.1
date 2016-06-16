#pragma once

#include <memory>
#include <atomic>
#include <SDL.h>
#include "ZE_Sprite.h"
#include "ZE_error.h"
#include "ZE_EventManager.h"
#include "ZE_Controller.h"
#include "ZE_Font.h"
#include "ZE_Core.h"


// ������
// ��װSDLָ�뵽����ָ��

template<typename PtrType, typename DestoryType>
auto make_sdl_unique_ptr(PtrType* ptr, DestoryType destory_func)
{
	return std::move(unique_ptr<PtrType, DestoryType>(ptr, destory_func));
}





// �����ȫ��״̬������
// ��������ȫ�ֱ����Խ�����������鹹˳������
class EngineGlobalState
{
public:
	// ��ֹ�ظ�����
	EngineGlobalState();
	~EngineGlobalState();
	// ��ֹ�ƶ������뿽������
	EngineGlobalState(const EngineGlobalState&) = delete;
	EngineGlobalState(EngineGlobalState&&) = delete;
	EngineGlobalState& operator=(const EngineGlobalState&) = delete;
	EngineGlobalState& operator=(EngineGlobalState&&) = delete;

	//[Global]����SDL�����ָ��
	unique_ptr<SDL_Window, decltype(SDL_DestroyWindow)*> g_ZE_Window{ nullptr,SDL_DestroyWindow };
	//[Global]����SDL��Surface��ָ��
	unique_ptr<SDL_Surface, decltype(SDL_FreeSurface)*> g_ZE_MainSurface{ nullptr,SDL_FreeSurface };
	//[Global]����Ⱦ�����󶨵���window
	unique_ptr<SDL_Renderer, decltype(SDL_DestroyRenderer)*> g_ZE_MainRenderer{ nullptr,SDL_DestroyRenderer };
	//[Global]stage����Ψһ
	unique_ptr<Sprite> ZE_stage;
	//[Global]error����(Ӧ����Ψһ�������������Ҳ��private)
	unique_ptr<Error> ZE_error;
	//[Global]�¼�����������Ψһ
	unique_ptr<EventManager> ZE_eventHandler;
	//[Global]�˳���ѭ�����ж�����
	atomic_bool ZE_QUIT_MAIN_LOOP{ false };
	//[Global]�������е��ֱ�ָ��
	deque<unique_ptr<Controller>> ZE_Controllers;
	//[Global]ϵͳĬ������
	shared_ptr<Font> defaultFont;
};







