#pragma once
#include "gameNode.h"


class video:public gameNode
{
private:
	VideoCapture cap;		// opencv ���� ���� ����ü 
	const char* _aviName;
	bool _play;				// BOOL ��(�ʿ����� ������ �Ǵ��� ����)
public:

	video();
	~video();

	HRESULT init(const char* videoName,bool ending = FALSE);
	void release();
	void update();
	void render();

	void videoRecord();		// �����ϴ� �ڵ� ���� �������� ����(�Ǵܿ���)

	// Ȥ�� ���� ����� ���� (���� ����)
	void setPlay();
	void setStop();
};

