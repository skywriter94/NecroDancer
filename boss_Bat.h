#pragma once
#include "slave.h"

class boss_Bat : public slave
{

public:
	boss_Bat();
	~boss_Bat();

	HRESULT init();
	void update();

	void move();							// �����̺��� ������ ����

	void boss_Bat_ChangeAnimation();		// �����̺� ������ �ִϸ��̼� ü���� �Լ�
	

};

