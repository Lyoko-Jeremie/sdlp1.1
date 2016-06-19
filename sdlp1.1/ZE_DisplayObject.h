#pragma once
#include <string>
#include <unordered_map>
#include "ZE_EventDispatcher.h"

using namespace std;

//���м̳��Ա�����඼Ӧ��дRender����
//����sprite�е�render����ѭ�����������е�Ԫ�ز�����render����
//image��render������Ⱦ�Լ���texture
//ԭ����TM���Ǹ����ڵ��Ҳ���ʶ��
class DisplayObject
	: public EventDispatcher,
	public std::enable_shared_from_this<DisplayObject>
{
public:
	DisplayObject();
	DisplayObject(size_t index);


	//�����û��ı�������ȫû����
	string name;
	int x = 0;
	int y = 0;
	//������ű�����Ĭ��Ϊ1
	double scaleX = 1;
	//�߶����ű�����Ĭ��Ϊ1
	double scaleY = 1;
	//͸����
	double alpah = 1;
	//��ת�㣬�õ�ָʾ����ͼ���Լ�������Ϊԭ���һ�����꣬������̨����
	SDL_Point rotationPoint = { 0, 0 };
	//��ת�Ƕȣ�����0-360�ĽǶȱ���
	double rotationAngle = 0;
	//��תģʽ
	//�޷�ת:SDL_FLIP_NONE
	//���ҷ�ת:SDL_FLIP_HORIZONTAL
	//���·�ת:SDL_FLIP_VERTICAL
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	//��Ⱦģʽ
	SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;

	// ������
	const size_t index;

	//����һ��DO������
	void addChild(shared_ptr<DisplayObject>);
	//�����Ұְ�
	void setParent(shared_ptr<DisplayObject> parent);
	//�����ҵ���ʵ��Ⱦ����
	SDL_Rect setRenderRect(int, int);
	//ɾ��һ���ӽڵ�������е��ӽڵ�
	void removeChild(shared_ptr<DisplayObject>, bool disposeIt = true);
	//���ҴӸ��ڵ���ɾ��
	void removeFromParent(bool disposeMe = false);
	//������ӽڵ�������Դ
	virtual ~DisplayObject();

	// ��Ⱦ��������д
	// ���麯��
	virtual void Render() = 0;
	virtual void dispose();
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;

protected:
	//��������ʹ��add���������DO����
	unordered_map<size_t, shared_ptr<DisplayObject>> addedObjects;
	//�ְ�ָ��  Ϊ����ѭ�����ã�ʹ����ָ��
	weak_ptr<DisplayObject> parent;
};