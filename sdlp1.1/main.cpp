////////////////////////////////////////////////////////////
//���е������ʾ��������ע�Ͷ�д����/����/������������һ��//
//˵���׳���֮��Ҳ��һ�������������������...             //
////////////////////////////////////////////////////////////

#include "ZE_Core.h"

#ifdef _DEBUG
#include <vld.h>
#endif // _DEBUG

#include "mygame.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[])
{
	g_Engine_ptr.reset(new ZeroEngine);
	g_Engine_ptr->Init(u8"��TM������һ��SDL���ڻ���һ��TM��Ӣ��ȫ��ǻ�ϱ���Ĵ����Բۣ�!��", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	{
		mygame game;

		//����������̨Ĭ����ɫ��Ҳûʲô����
		g_Engine_ptr->stageColor = { 0, 0, 0 };

		game.Init();

		g_Engine_ptr->Start(&game);
	}
	cout << "mygame end" << endl;

	return 0;
}