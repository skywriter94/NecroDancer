#pragma once
#include "slave.h"

class boss_Skeleton_Yellow : public slave
{
protected:

public:
	boss_Skeleton_Yellow();
	~boss_Skeleton_Yellow();

	HRESULT init();
	void update();

	void move();										// �����̺��� ������ ����

	void boss_Skeleton_Yellow_ChangeAnimation();		// �����̺� ������ �ִϸ��̼� ü���� �Լ�


};

