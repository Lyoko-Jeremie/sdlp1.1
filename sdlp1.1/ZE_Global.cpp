#include "ZE_Global.h"

#include "ZE_EngineGlobalState.h"


//[Global]ZE�汾��
std::string ZE_version = "1.0.0";

//[Global]����ȫ��״̬����
std::unique_ptr<EngineGlobalState> GlobalState{ new EngineGlobalState() };

