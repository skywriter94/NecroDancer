#pragma once
#include "stdafx.h"

class slaveManager_Library
{


public:

	
	void create_Slave(vector<slave*>* vSlaveList, SLAVE_TYPE type, int idx, int idy)	// �����̺긦 �����. �ش� �̸��� ���� �����̺긦 �ε��� x, y ��ġ�� �����.
	{
		slave* new_Slave;
		new_Slave = new slave;								// ���� �Ҵ��� �޴´�.
		new_Slave->init(type, idx, idy);					// �ش� �����̺긦 �����.

		vSlaveList->push_back(new_Slave);					// ���� ������� �����̺긦 �����Ѵ�.
	}

};
