#pragma once
#include "gameNode.h"


#define LOADINGMAX 100									//�ε� ī��Ʈ �ƽ�ġ

class loadingScene : public gameNode
{
private:
	image* _background;										//�̹��� ����� ���� ������ְ�

public:
	loadingScene();
	~loadingScene();

	int _currentCount;										//�ε� ī��Ʈ �����ġ

	HRESULT init();
	void release();
	void update();
	void render();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);	//��𿡼��� �� �� �ְ� static �������
															//�ҷ������� CALLBACK�Լ�
															//�Ķ���Ͱ��� � �ڷ����� ���� �����ϰ� LPVOID
