#pragma once
#include "gameNode.h"
#include "slaveLibrary.h"

class slave : public gameNode
{
protected:
	SLAVE_INFO		_slave;
	slaveLibrary	_library;

public:
	slave();
	~slave();

	virtual HRESULT init(SLAVE_TYPE type, int idx, int idy);
	virtual void release();
	virtual void update();
	virtual void render();

	// �����̺�, �÷��̾�, UI
	virtual void move();				// �����̺��� ������ ����

	SLAVE_INFO* get_Slave() { return &_slave; }					// �����̺��� ���� �ּҸ� �޾ƿ´�.
	void slave_Pos_Setting();									// �����̺� ��ǥ ���� ����

	void slave_Hit(int damage) { _slave.status.hp -= damage; if (_slave.status.hp < 0) _slave.status.hp = 0; }
};

// �����̺� �⺻ Ŭ���� 