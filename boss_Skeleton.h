#pragma once
#include "slave.h"

class boss_Skeleton : public slave
{
protected:

public:
	boss_Skeleton();
	~boss_Skeleton();

	HRESULT init();
	void update();

	void move();								// �����̺��� ������ ����

	void boss_Skeleton_ChangeAnimation();		// �����̺� ������ �ִϸ��̼� ü���� �Լ�


};

