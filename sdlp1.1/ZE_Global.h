#pragma once
#include <string>
#include <memory>


// ������ǰ
class ZeroEngine;
class EngineGlobalState;

//[Global]ZE�汾��
extern std::string ZE_version;
//[Global]����ȫ��״̬����
extern std::unique_ptr<EngineGlobalState> GlobalState;

