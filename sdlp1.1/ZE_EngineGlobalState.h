#pragma once

#include <memory>
#include <atomic>
#include <deque>
#include <SDL.h>


class Sprite;
class Error;
class EventManager;
class Controller;
class Font;
class ZeroEngine;



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
	std::unique_ptr<SDL_Window, decltype(SDL_DestroyWindow)*> g_ZE_Window{ nullptr,SDL_DestroyWindow };
	//[Global]����SDL��Surface��ָ��
	std::unique_ptr<SDL_Surface, decltype(SDL_FreeSurface)*> g_ZE_MainSurface{ nullptr,SDL_FreeSurface };
	//[Global]����Ⱦ�����󶨵���window
	std::unique_ptr<SDL_Renderer, decltype(SDL_DestroyRenderer)*> g_ZE_MainRenderer{ nullptr,SDL_DestroyRenderer };
	//[Global]stage����Ψһ
	std::unique_ptr<Sprite> ZE_stage;
	//[Global]error����(Ӧ����Ψһ�������������Ҳ��private)
	std::unique_ptr<Error> ZE_error;
	//[Global]�¼�����������Ψһ
	std::unique_ptr<EventManager> ZE_eventHandler;
	//[Global]�˳���ѭ�����ж�����
	std::atomic_bool ZE_QUIT_MAIN_LOOP{ false };
	//[Global]�������е��ֱ�ָ��
	std::deque<std::unique_ptr<Controller>> ZE_Controllers;
	//[Global]ϵͳĬ������
	std::shared_ptr<Font> defaultFont;
	//[Global]������ʵ����ָ��
	std::unique_ptr<ZeroEngine> g_Engine_ptr;
};







