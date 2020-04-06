#pragma once
#include "gameNode.h"
#include "slave.h"
#include "bossKinds.h"
#include "slaveManager_Library.h"

class slaveManager : public gameNode
{
private:
	vector<slave*>					_vSlaveList;		// �����̺긦 ��� ����
	vector<slave*>::iterator		_viSlaveList;		// �����̺� ���Ϳ�����

	slaveManager_Library*			_library;			// �����̺� �Ŵ��� �Լ�

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// ����
	vector<slave*> get_SlaveList() { return _vSlaveList; }			// �����̺� ����
	slaveManager_Library* get_SlaveLibrary() { return _library; }	// �����̺� �Լ�

	// �����̺� ��ȯ 
	// ������������������������������������������������������������������������������������������
	// SLAVE_BAT,				 ����				// SLAVE_GHOST,				 ��Ʈ
	// SLAVE_SKELETON,			 ���̷���			// SLAVE_SKELETON_YELLOW,	 ���ο� ���̷���
	// SLAVE_NONE				 ����
	void create_Slave(SLAVE_TYPE type, int idx, int idy);
	//void create_Slave(SLAVE_TYPE type, int idx, int idy) { _library->create_Slave(&_vSlaveList, type, idx, idy); }

	void delete_Slave();								// �����̺� ����
};

