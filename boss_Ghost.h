#pragma once
#include "slave.h"

class boss_Ghost : public slave
{
protected:

public:
	boss_Ghost();
	~boss_Ghost();

	HRESULT init();
	void update();

	void move();							// �����̺��� ������ ����

	void boss_Ghost_ChangeAnimation();		// �����̺� ��Ʈ�� �ִϸ��̼� ü���� �Լ�


};

