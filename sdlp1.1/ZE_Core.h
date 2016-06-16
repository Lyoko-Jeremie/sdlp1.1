#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <deque>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "ZE_error.h"
#include "ZE_Sprite.h"
#include "ZE_EventManager.h"
#include "ZE_Controller.h"
#include "ZE_Fraps.h"
#include "ZE_Font.h"
#include "ZE_EngineGlobalState.h"

using namespace std;

// ������ǰ
class ZeroEngine;

//[Global]ZE�汾��
extern string ZE_version;
//[Global]����ȫ��״̬����
extern unique_ptr<EngineGlobalState> GlobalState;
//[Global]������ʵ����ָ��
extern unique_ptr<ZeroEngine> g_Engine_ptr;


//��ɫ�ṹ�壬Ҳ��������̨��ɫ��ʱ������
struct Color
{
	int red;
	int green;
	int blue;
};

//��Game�࣬�û�Ӧ�̳д��ಢ��дMainLoop��Close������Ȼ��һ�������ָ�봫�ݸ�start����
class Game
{
public:
	virtual void MainLoop() = 0;
	virtual void Close() = 0;
	virtual ~Game() {}
};

//ͷ�ļ��������࣬cpp�ж����࣬ȫ��һ��
//���ļ���ZE�ĺ����࣬��������������Ķ����ڴ�����
//ʹ��ʱ���̳б��ಢ����Draw()����������ͼ����д��Draw������
class ZeroEngine
{
public:
	ZeroEngine();
	~ZeroEngine();
	ZeroEngine(const ZeroEngine&) = delete;
	ZeroEngine(ZeroEngine&&) = delete;

	//��̨��ɫ��Ĭ��Ϊ��
	Color stageColor = { 0, 0, 0 };
	//��ʼ��������ʹ��ZEǰ������ô˷���
	//�÷��������˱����е����������������ֱ��ʼ�����ⲿ��SDL��SDL_IMAGE
	//�÷����᷵��һ��boolֵ��������ģ���ʼ���ɹ��򷵻�true�����򷵻�false
	//�ⲿ��ı���д�ڶ�Ӧ������
	bool Init(string, int, int, bool, std::string defaultFontFile = "data/ttf/SourceHanSansSC-Normal.otf") const;
	//�÷�����ZE����ѭ��������Ŀǰ�����ð�
	void Start(Game*);
	// �Һ�
	size_t getNewDisplayObjectIndex();

private:
	//�����Ⱦ����̨�ϣ���ʾһЩ���ӱ���
	unique_ptr<Fraps> fraps;
	//SDL�ĳ�ʼ���������÷��������������ֱ��Ǵ��ڱ��⡢���ڿ�ȡ����ڸ߶�
	static bool Init_SDL(string, int, int);
	//��ʼ����SDL_IMAGE��������
	bool Init_SDL_Image(bool) const;
	//��ʼ����SDL_TTF��������
	static bool Init_SDL_ttf();
	static bool Init_SDL_Mixer();
	//����������ȫ�Ĺر�SDL���˳�����
	void Close() const;
	//�û�����Ϸ����
	Game* maingame{ nullptr };
	// ��ʾ����index������
	std::atomic_size_t display_object_index{ 0 };
};