#ifdef _WIN32
#	include <Windows.h>
#elif defined(ANDROID) || defined(__ANDROID__)
#	include <android/log.h>
#	define TAG "sdlp"
#	define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG ,__VA_ARGS__)
#	define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG ,__VA_ARGS__)
#	define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG ,__VA_ARGS__)
#	define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG ,__VA_ARGS__)
#	define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG ,__VA_ARGS__)
#	define LOGF(...) __android_log_print(ANDROID_LOG_FATAL, TAG ,__VA_ARGS__)
#	define OutputDebugStringA(msg) LOGD("%s", msg)
#else
// TODO Add output for linux and other platforms
#	define OutputDebugStringA
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "ZE_error.h"

using namespace std;

void Error::PopToDebugConsole(string msg, bool mainConsole)
{
	OutputDebugStringA(msg.c_str());
	if (mainConsole)
		cout << msg << endl;
}

void Error::PopDebugConsole_Warning(string msg)
{
	OutputDebugStringA(("Warning: " + msg + "\n").c_str());
}

void Error::PopDebugConsole_Error(string msg, bool quit)
{
	OutputDebugStringA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	OutputDebugStringA((msg + "\n").c_str());
	OutputDebugStringA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	if (quit)
	{
		exit(1);
	}
}

void Error::PopDebugConsole_SDLError(string msg, bool quit)
{
	//��SDL����ʱ��������ʱʹ��SDL_GetError()������ô�����Ϣ
	OutputDebugStringA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	OutputDebugStringA((msg + "[SDL Error: " + SDL_GetError() + "]\n").c_str());
	OutputDebugStringA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	if (quit)
	{
		exit(1);
	}
}

void Error::PopDebugConsole_SDL_ImageError(string msg, bool quit)
{
	//��SDL_Image����ʱ��������ʱʹ��IMG_GetError()������ô�����Ϣ
	OutputDebugStringA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	OutputDebugStringA((msg + "[SDL_Image Error: " + IMG_GetError() + "]\n").c_str());
	OutputDebugStringA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	if (quit)
	{
		exit(1);
	}
}

void Error::PopDebugConsole_SDL_ttfError(string msg, bool quit)
{
	//��SDL_ttf����ʱ��������ʱʹ��TTF_GetError()������ô�����Ϣ
	OutputDebugStringA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	OutputDebugStringA((msg + "[SDL_ttf Error: " + TTF_GetError() + "]\n").c_str());
	OutputDebugStringA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	if (quit)
	{
		exit(1);
	}
}

void Error::PopDebugConsole_SDL_MixerError(string msg, bool quit)
{
	//��SDL_Mixer����ʱ��������ʱʹ��Mix_GetError()������ô�����Ϣ
	OutputDebugStringA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	OutputDebugStringA((msg + "[SDL_Mixer Error: " + Mix_GetError() + "]\n").c_str());
	OutputDebugStringA("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	if (quit)
	{
		exit(1);
	}
}