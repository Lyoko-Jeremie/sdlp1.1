#include "ZE_EngineGlobalState.h"
#include <assert.h>

#include <iostream>

std::atomic_bool EngineGlobalState_Singleton{ false };

EngineGlobalState::EngineGlobalState()
{
	if (EngineGlobalState_Singleton.exchange(true))
	{
		throw std::runtime_error("EngineGlobalState Re Ctor");
	}
	std::cout << "EngineGlobalState::EngineGlobalState()" << std::endl;
}


EngineGlobalState::~EngineGlobalState()
{
	// �������ն��� �˶�����DEBUGģʽ�¼����������Ƿ�Ϊ��
	// ������������µ�ָ���Ƿ���ȷ�ÿ�
	assert(nullptr == g_ZE_Window);
	assert(nullptr == g_ZE_MainSurface);
	assert(nullptr == g_ZE_MainRenderer);
	std::cout << "EngineGlobalState::~EngineGlobalState()" << std::endl;
}
