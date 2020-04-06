#include "stdafx.h"
#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::collision_Player_Find_Enemy(player* playerInfo, Enemy* enemyInfo)
{
	// �÷��̾��� ��ó�� ���ʹ̰� �ִٸ� true�� ������ �ٲ��,
	bool isAttack = false;

	// �÷��̾��� ���⿡ ���� ������ �Ѵ�. (���� + ��ĭ�� ��밡 �ִ��� ã���ش�. ��밡 �ִٸ� true�� ���� ����)
	switch (playerInfo->getDirection())
	{
	case PLAYERDIRECTION_LEFT:
		// �÷��̾��� �ε���x -1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� ���ʿ� ���ʹ̰� �ִٴ� �� 
		if (playerInfo->getPlayer().idx - 1 == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_UP:
		// �÷��̾��� �ε���y -1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� ���ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy - 1 == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_RIGHT:
		// �÷��̾��� �ε���x +1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� �����ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx + 1 == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_DOWN:
		// �÷��̾��� �ε���y +1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� �Ʒ��ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy + 1 == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;
	}

	// ��ó�� ���ʹ̰� �ִٸ� true, �ƴϸ� false
	return isAttack;

	//// ���ʹ̰� �÷��̾�� �ǰ��� ������ ���
	//if (isAttack)
	//{
	//	(*enemyInfo).getEnemyInfo()->HP--;
	//
	//	// ���� true��� ���ʹ��� ü���� 1 ���� ��Ų��. ü���� 0 ���϶�� HP�� 0���� ���� �����ش�.
	//	if ((*enemyInfo).getEnemyInfo()->HP <= 0)
	//	{
	//		(*enemyInfo).getEnemyInfo()->HP = 0;
	//
	//		// ���Ͱ� ü���� 0�̶�� ���� ���Ͱ� �׾��ٴ� ���̴�. �ش� ��ġ�� �ִ� Ÿ�� �Ӽ��� �⺻ Ÿ�Ϸ� �ٲ��ش�.
	//		(*mapInfo)[(*enemyInfo).getEnemyInfo()->x + (*enemyInfo).getEnemyInfo()->y * tileSize].type = TYPE_NONE;
	//	}
	//}

	// �� �Ŀ� �߰��� �ؾ� �ϴ� ��
	// ���Ϳ� Ÿ�Կ� ���� � ���ʹ� Ư�� ��Ȳ�� ���� �Ұ��� ���Ͱ� ����
	// ������ Ÿ�Ե� ������ �ϴ��� �����ؾ���

}

bool Collision::collision_Player_Find_Enamy(player* playerInfo, deathMetal* bossInfo)
{
	// �÷��̾��� ��ó�� ������Ż�� �ִٸ� true�� ������ �ٲ��,
	bool isAttack = false;

	// �÷��̾��� ���⿡ ���� ������ �Ѵ�. (���� + ��ĭ�� ��밡 �ִ��� ã���ش�. ��밡 �ִٸ� true�� ���� ����)
	switch (playerInfo->getDirection())
	{
	case PLAYERDIRECTION_LEFT:
		// �÷��̾��� �ε���x -1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� ���ʿ� ���ʹ̰� �ִٴ� �� 
		if (playerInfo->getPlayer().idx - 1 == bossInfo->getBoss_Index().x &&
			playerInfo->getPlayer().idy == bossInfo->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_UP:
		// �÷��̾��� �ε���y -1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� ���ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx == bossInfo->getBoss_Index().x &&
			playerInfo->getPlayer().idy - 1 == bossInfo->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_RIGHT:
		// �÷��̾��� �ε���x +1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� �����ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx + 1 == bossInfo->getBoss_Index().x &&
			playerInfo->getPlayer().idy == bossInfo->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_DOWN:
		// �÷��̾��� �ε���y +1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� �Ʒ��ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx == bossInfo->getBoss_Index().x &&
			playerInfo->getPlayer().idy + 1 == bossInfo->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;
	}

	// ��ó�� ������Ż�� �ִٸ� true, �ƴϸ� false
	return isAttack;
}

void Collision::collision_Enemy_Find_Player(player* playerInfo, Enemy* enemyInfo)
{
	// ���ʹ� ���� ������ ����
}

bool Collision::collision_DeathMetal_Find_Player(player* playerInfo, deathMetal* bossInfo)
{
	// ������Ż�� ���� ������ ��ҿ� �÷��̾ �ִٸ� �� ���� true�� �ٲ��.
	bool isAttack = false;

	// ������Ż�� �ٶ󺸴� ���� �ٷ� �տ� �÷��̾ �ִ��� ã���ش�.
	// ã���� �ϴ� �ε����� �÷��̾��� �ε����� ���ٸ� �װ��� �÷��̾ �ִٴ°�
	switch (bossInfo->getBoss_Direction())
	{
	case BD_LEFT:
		if (bossInfo->getBoss_Index().x - 1 == playerInfo->getPlayer().idx &&
			bossInfo->getBoss_Index().y == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case BD_UP:
		if (bossInfo->getBoss_Index().x == playerInfo->getPlayer().idx &&
			bossInfo->getBoss_Index().y - 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case BD_RIGHT:
		if (bossInfo->getBoss_Index().x + 1 == playerInfo->getPlayer().idx &&
			bossInfo->getBoss_Index().y == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case BD_DOWN:
		if (bossInfo->getBoss_Index().x == playerInfo->getPlayer().idx &&
			bossInfo->getBoss_Index().y + 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;
	}

	// ��ó�� ���ʹ̰� �ִٸ� true, �ƴϸ� false
	return isAttack;
}

bool Collision::collision_DeathMetal_Find_Slave(deathMetal* deathMetal, vector<slave*> _vSlaveList)
{
	// ������Ż�� ���� ������ ��ҿ� �����̺� �ִٸ� �� ���� true�� �ٲ��.
	bool isAttack = false;

	// ������Ż�� �ٶ󺸴� ���� �ٷ� �տ� �����̺� �ִ��� ã���ش�.
	// ã���� �ϴ� �ε����� �����̺��� �ε����� ���ٸ� �װ��� �����̺갡 �ִٴ°�
	for (int i = 0; i < _vSlaveList.size(); ++i)
	{
		switch (deathMetal->getBoss_Direction())
		{
		case BD_LEFT:
			if (deathMetal->getBoss_Index().x - 1 == _vSlaveList[i]->get_Slave()->pos.index.x &&
				deathMetal->getBoss_Index().y == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case BD_UP:
			if (deathMetal->getBoss_Index().x == _vSlaveList[i]->get_Slave()->pos.index.x &&
				deathMetal->getBoss_Index().y - 1 == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case BD_RIGHT:
			if (deathMetal->getBoss_Index().x + 1 == _vSlaveList[i]->get_Slave()->pos.index.x &&
				deathMetal->getBoss_Index().y == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case BD_DOWN:
			if (deathMetal->getBoss_Index().x == _vSlaveList[i]->get_Slave()->pos.index.x &&
				deathMetal->getBoss_Index().y + 1 == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;
		}
	}

	// ��ó�� �����̺� �ִٸ� true, �ƴϸ� false
	return isAttack;
}

bool Collision::collision_Slave_Find_Player(player* playerInfo, SLAVE_INFO* slave)
{
	// �����̺갡 ���� ������ ��ҿ� �÷��̾ �ִٸ� �� ���� true�� �ٲ��.
	bool isAttack = false;

	// �����̺갡 �ٶ󺸴� ���� �ٷ� �տ� �÷��̾ �ִ��� ã���ش�.
	// ã���� �ϴ� �ε����� �÷��̾��� �ε����� ���ٸ� �װ��� �÷��̾ �ִٴ°�
	switch (slave->status.direction)
	{
	case SLAVE_DIRECTION::SD_LEFT:
		if (slave->pos.index.x - 1 == playerInfo->getPlayer().idx &&
			slave->pos.index.y == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_UP:
		if (slave->pos.index.x == playerInfo->getPlayer().idx &&
			slave->pos.index.y - 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_RIGHT:
		if (slave->pos.index.x + 1 == playerInfo->getPlayer().idx &&
			slave->pos.index.y == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_DOWN:
		if (slave->pos.index.x == playerInfo->getPlayer().idx &&
			slave->pos.index.y + 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;
	}

	// ��ó�� ���ʹ̰� �ִٸ� true, �ƴϸ� false
	return isAttack;
}

bool Collision::collision_Slave_Find_DeathMetal(deathMetal* deathMetal, SLAVE_INFO* slave)
{
	// ������Ż�� ���� ������ ��ҿ� �÷��̾ �ִٸ� �� ���� true�� �ٲ��.
	bool isAttack = false;

	// ������Ż�� �ٶ󺸴� ���� �ٷ� �տ� �÷��̾ �ִ��� ã���ش�.
	// ã���� �ϴ� �ε����� �÷��̾��� �ε����� ���ٸ� �װ��� �÷��̾ �ִٴ°�
	switch (slave->status.direction)
	{
	case SLAVE_DIRECTION::SD_LEFT:
		if (slave->pos.index.x - 1 == deathMetal->getBoss_Index().x &&
			slave->pos.index.y == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_UP:
		if (slave->pos.index.x == deathMetal->getBoss_Index().x &&
			slave->pos.index.y - 1 == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_RIGHT:
		if (slave->pos.index.x + 1 == deathMetal->getBoss_Index().x &&
			slave->pos.index.y == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_DOWN:
		if (slave->pos.index.x == deathMetal->getBoss_Index().x &&
			slave->pos.index.y + 1 == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;
	}

	// ��ó�� ���ʹ̰� �ִٸ� true, �ƴϸ� false
	return isAttack;
}

bool Collision::collision_Slave_Find_Slave(SLAVE_INFO* _slave, vector<slave*> _vSlaveList)
{
	// �����̺갡 �̵� �ϴ� ��ҿ� �����̺갡 �ִٸ� true�� �ٲ��.
	bool isAttack = false;

	// �����̺갡 �ٶ󺸴� ���� �ٷ� �տ� �����̺갡 �ִ��� ã���ش�.
	// ã���� �ϴ� �ε����� �����̺��� �ε����� ���ٸ� �װ��� �����̺갡 �ִٴ°�
	for (int i = 0; i < _vSlaveList.size(); ++i)
	{
		switch (_slave->status.direction)
		{
		case SLAVE_DIRECTION::SD_LEFT:
			if (_slave->pos.index.x - 1 == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case SLAVE_DIRECTION::SD_UP:
			if (_slave->pos.index.x == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y - 1 == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case SLAVE_DIRECTION::SD_RIGHT:
			if (_slave->pos.index.x + 1 == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case SLAVE_DIRECTION::SD_DOWN:
			if (_slave->pos.index.x == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y + 1 == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;
		}
	}

	// ��ó�� �����̺갡 �ִٸ� true, �ƴϸ� false
	return isAttack;
}

bool Collision::collision_Slave_Find_Player(player* playerInfo, SLAVE_INFO* slave, bool reverse)
{
	// �����̺갡 ���� ������ ��ҿ� �÷��̾ �ִٸ� �� ���� true�� �ٲ��.
	bool isAttack = false;

	// �����̺갡 �ٶ󺸴� ���� �ݴ� ���⿡ �÷��̾ �ִ��� ã���ش�.
	// ã���� �ϴ� �ε����� �÷��̾��� �ε����� ���ٸ� �װ��� �÷��̾ �ִٴ°�
	switch (slave->status.direction)
	{
	case SLAVE_DIRECTION::SD_LEFT:
		if (slave->pos.index.x + 1 == playerInfo->getPlayer().idx &&
			slave->pos.index.y == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_UP:
		if (slave->pos.index.x == playerInfo->getPlayer().idx &&
			slave->pos.index.y + 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_RIGHT:
		if (slave->pos.index.x - 1 == playerInfo->getPlayer().idx &&
			slave->pos.index.y == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_DOWN:
		if (slave->pos.index.x == playerInfo->getPlayer().idx &&
			slave->pos.index.y - 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;
	}

	// ��ó�� ���ʹ̰� �ִٸ� true, �ƴϸ� false
	return isAttack;
}

bool Collision::collision_Slave_Find_DeathMetal(deathMetal* deathMetal, SLAVE_INFO* slave, bool reverse)
{
	// ������Ż�� ���� ������ ��ҿ� �÷��̾ �ִٸ� �� ���� true�� �ٲ��.
	bool isAttack = false;

	// ������Ż�� �ٶ󺸴� ���� �ݴ� ���⿡ �÷��̾ �ִ��� ã���ش�.
	// ã���� �ϴ� �ε����� �÷��̾��� �ε����� ���ٸ� �װ��� �÷��̾ �ִٴ°�
	switch (slave->status.direction)
	{
	case SLAVE_DIRECTION::SD_LEFT:
		if (slave->pos.index.x + 1 == deathMetal->getBoss_Index().x &&
			slave->pos.index.y == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_UP:
		if (slave->pos.index.x == deathMetal->getBoss_Index().x &&
			slave->pos.index.y + 1 == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_RIGHT:
		if (slave->pos.index.x - 1 == deathMetal->getBoss_Index().x &&
			slave->pos.index.y == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_DOWN:
		if (slave->pos.index.x == deathMetal->getBoss_Index().x &&
			slave->pos.index.y - 1 == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;
	}

	// ��ó�� ���ʹ̰� �ִٸ� true, �ƴϸ� false
	return isAttack;
}

bool Collision::collision_Slave_Find_Slave(SLAVE_INFO* _slave, vector<slave*> _vSlaveList, bool reverse)
{
	// �����̺갡 �̵� �ϴ� ��ҿ� �����̺갡 �ִٸ� true�� �ٲ��.
	bool isAttack = false;

	// �����̺갡 �ٶ󺸴� ���� �ٷ� �տ� �����̺갡 �ִ��� ã���ش�.
	// ã���� �ϴ� �ε����� �����̺��� �ε����� ���ٸ� �װ��� �����̺갡 �ִٴ°�
	for (int i = 0; i < _vSlaveList.size(); ++i)
	{
		switch (_slave->status.direction)
		{
		case SLAVE_DIRECTION::SD_LEFT:
			if (_slave->pos.index.x + 1 == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case SLAVE_DIRECTION::SD_UP:
			if (_slave->pos.index.x == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y + 1 == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case SLAVE_DIRECTION::SD_RIGHT:
			if (_slave->pos.index.x - 1 == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case SLAVE_DIRECTION::SD_DOWN:
			if (_slave->pos.index.x == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y - 1 == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;
		}
	}

	// ��ó�� �����̺갡 �ִٸ� true, �ƴϸ� false
	return isAttack;
}

bool Collision::collision_Charactor_Trab(vector<tagTile>* mapInfo, player* playerInfo)
{
	// ������ ã�Ҵٸ� isTrab�� ���� true�� ���Ѵ�.
	bool isTrab = false;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ĳ���Ͱ� ���� Ÿ�Ͽ� ������ �ִٸ� true
		if ((*mapInfo)[i].type == TYPE_TRAP &&
			(*mapInfo)[i].idX == playerInfo->getPlayer().idx &&
			(*mapInfo)[i].idY == playerInfo->getPlayer().idy)
		{
			isTrab = true;
		}

		// Ʈ���� ã�Ҵٸ� for���� ���͵� �ȴ�.
		if (isTrab) break;
	}

	// ������ ã�Ҵٸ� true, �ƴ϶�� false�� ������ �ȴ�.
	return isTrab;

	// ������ ã�� �� �Ŀ� �ؾ� �Ұ�
	// � �������� ã�ƾ� �ϰ�, �� ������ ����� ���� ���Ѿ���
}

bool Collision::collision_Charactor_Trab(vector<tagTile>* mapInfo, Enemy* enemyInfo)
{
	// ������ ã�Ҵٸ� isTrab�� ���� true�� ���Ѵ�.
	bool isTrab = false;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ĳ���Ͱ� ���� Ÿ�Ͽ� ������ �ִٸ� true
		if ((*mapInfo)[i].type == TYPE_TRAP &&
			(*mapInfo)[i].idX == enemyInfo->getEnemyInfo()->x &&
			(*mapInfo)[i].idY == enemyInfo->getEnemyInfo()->y)
		{
			isTrab = true;
		}

		// Ʈ���� ã�Ҵٸ� for���� ���͵� �ȴ�.
		if (isTrab) break;
	}

	// ������ ã�Ҵٸ� true, �ƴ϶�� false�� ������ �ȴ�.
	return isTrab;

	// ������ ã�� �� �Ŀ� �ؾ� �Ұ�
	// � �������� ã�ƾ� �ϰ�, �� ������ ����� ���� ���Ѿ���
}

bool Collision::collision_Charactor_Trab(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo)
{
	// ������ ã�Ҵٸ� isTrab�� ���� true�� ���Ѵ�.
	bool isTrab = false;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ĳ���Ͱ� ���� Ÿ�Ͽ� ������ �ִٸ� true
		if ((*mapInfo)[i].type == TYPE_TRAP &&
			(*mapInfo)[i].idX == deathMetalInfo->getBoss_Index().x &&
			(*mapInfo)[i].idY == deathMetalInfo->getBoss_Index().y)
		{
			isTrab = true;
		}

		// Ʈ���� ã�Ҵٸ� for���� ���͵� �ȴ�.
		if (isTrab) break;
	}

	// ������ ã�Ҵٸ� true, �ƴ϶�� false�� ������ �ȴ�.
	return isTrab;

	// ������ ã�� �� �Ŀ� �ؾ� �Ұ�
	// � �������� ã�ƾ� �ϰ�, �� ������ ����� ���� ���Ѿ���
}


//bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, player* playerInfo)
//{
//	bool isObject = false;
//
//	// Ÿ�Ͽ��� ������Ʈ�� �ִ��� ã���ش�. (��, ���� ���)
//	for (int i = 0; i < mapInfo->size(); ++i)
//	{
//		// �÷��̾ �ٶ󺸴� ���⿡ ������Ʈ�� �ִٸ� true�� ���� �ȴ�.
//		switch (playerInfo->getPlayer().direction)
//		{
//		case PLAYERDIRECTION_LEFT:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				playerInfo->getPlayer().idx - 1 == (*mapInfo)[i].idX &&
//				playerInfo->getPlayer().idy == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//
//		case PLAYERDIRECTION_UP:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				playerInfo->getPlayer().idx == (*mapInfo)[i].idX &&
//				playerInfo->getPlayer().idy - 1 == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//
//		case PLAYERDIRECTION_RIGHT:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				playerInfo->getPlayer().idx + 1 == (*mapInfo)[i].idX &&
//				playerInfo->getPlayer().idy == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//
//		case PLAYERDIRECTION_DOWN:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				playerInfo->getPlayer().idx == (*mapInfo)[i].idX &&
//				playerInfo->getPlayer().idy + 1 == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//		}
//
//		// ������Ʈ�� ã�Ҵٸ� �ݺ����� ������.
//		if (isObject) break;
//	}
//	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
//	return isObject;
//
//	// �߰� �Ϸ���
//	// ������Ʈ��� � ������Ʈ����
//	// ������Ʈ�� ���������� � ȿ���� �ִ��� ó��?
//}
//
//bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo)
//{
//	bool isObject = false;
//
//	// ���ʹ̴� ���� ������ ����
//
//	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
//	return isObject;
//
//	// �߰� �Ϸ���
//	// ������Ʈ��� � ������Ʈ����
//	// ������Ʈ�� ���������� � ȿ���� �ִ��� ó��?
//}
//
//bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo)
//{
//	bool isObject = false;
//
//	// Ÿ�ϸʿ� ������Ʈ�� �ִ��� ã�´�. (��, ���� ���)
//	for (int i = 0; i < mapInfo->size(); ++i)
//	{
//		// ������Ż�� �ٶ󺸴� ���⿡ ������Ʈ�� �ִٸ� true�� ���� �ȴ�.
//		switch (deathMetalInfo->getBoss_Direction())
//		{
//		case BD_LEFT:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				deathMetalInfo->getBoss_Index().x - 1 == (*mapInfo)[i].idX &&
//				deathMetalInfo->getBoss_Index().y == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//
//		case BD_UP:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				deathMetalInfo->getBoss_Index().x == (*mapInfo)[i].idX &&
//				deathMetalInfo->getBoss_Index().y - 1 == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//
//		case BD_RIGHT:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				deathMetalInfo->getBoss_Index().x + 1 == (*mapInfo)[i].idX &&
//				deathMetalInfo->getBoss_Index().y == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//
//		case BD_DOWN:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				deathMetalInfo->getBoss_Index().x == (*mapInfo)[i].idX &&
//				deathMetalInfo->getBoss_Index().y + 1 == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//		}
//
//		// ������Ʈ�� ã������ �ݺ����� ������.
//		if (isObject) break;
//	}
//
//	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
//	return isObject;
//
//	// �߰� �Ϸ���
//	// ������Ʈ��� � ������Ʈ����
//	// ������Ʈ�� ���������� � ȿ���� �ִ��� ó��?
//}
//
//bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, SLAVE_INFO* slave)
//{
//	bool isObject = false;
//
//	// Ÿ�ϸʿ� ������Ʈ�� �ִ��� ã�´�. (��, ���� ���)
//	for (int i = 0; i < mapInfo->size(); ++i)
//	{
//		// ������Ż�� �ٶ󺸴� ���⿡ ������Ʈ�� �ִٸ� true�� ���� �ȴ�.
//		switch (slave->status.direction)
//		{
//		case SLAVE_DIRECTION::SD_LEFT:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				slave->pos.index.x - 1 == (*mapInfo)[i].idX &&
//				slave->pos.index.y == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//
//		case SLAVE_DIRECTION::SD_UP:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				slave->pos.index.x == (*mapInfo)[i].idX &&
//				slave->pos.index.y - 1 == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//
//		case SLAVE_DIRECTION::SD_RIGHT:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				slave->pos.index.x + 1 == (*mapInfo)[i].idX &&
//				slave->pos.index.y == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//
//		case SLAVE_DIRECTION::SD_DOWN:
//			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
//				slave->pos.index.x == (*mapInfo)[i].idX &&
//				slave->pos.index.y + 1 == (*mapInfo)[i].idY)
//			{
//				isObject = true;
//			}
//			break;
//		}
//
//		// ������Ʈ�� ã������ �ݺ����� ������.
//		if (isObject) break;
//	}
//
//	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
//	return isObject;
//}




bool Collision::collision_Charactor_Object(vector<tagTile*>* mapInfo, player* playerInfo)
{
	bool isObject = false;

	// Ÿ�Ͽ��� ������Ʈ�� �ִ��� ã���ش�. (��, ���� ���)
	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// �÷��̾ �ٶ󺸴� ���⿡ ������Ʈ�� �ִٸ� true�� ���� �ȴ�.
		switch (playerInfo->getPlayer().direction)
		{
		case PLAYERDIRECTION_LEFT:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				playerInfo->getPlayer().idx - 1 == (*mapInfo)[i]->idX &&
				playerInfo->getPlayer().idy == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case PLAYERDIRECTION_UP:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				playerInfo->getPlayer().idx == (*mapInfo)[i]->idX &&
				playerInfo->getPlayer().idy - 1 == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case PLAYERDIRECTION_RIGHT:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				playerInfo->getPlayer().idx + 1 == (*mapInfo)[i]->idX &&
				playerInfo->getPlayer().idy == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case PLAYERDIRECTION_DOWN:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				playerInfo->getPlayer().idx == (*mapInfo)[i]->idX &&
				playerInfo->getPlayer().idy + 1 == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;
		}

		// ������Ʈ�� ã�Ҵٸ� �ݺ����� ������.
		if (isObject) break;
	}
	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
	return isObject;

	// �߰� �Ϸ���
	// ������Ʈ��� � ������Ʈ����
	// ������Ʈ�� ���������� � ȿ���� �ִ��� ó��?
}

bool Collision::collision_Charactor_Object(vector<tagTile*>* mapInfo, Enemy* enemyInfo)
{
	bool isObject = false;

	// ���ʹ̴� ���� ������ ����

	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
	return isObject;

	// �߰� �Ϸ���
	// ������Ʈ��� � ������Ʈ����
	// ������Ʈ�� ���������� � ȿ���� �ִ��� ó��?
}

bool Collision::collision_Charactor_Object(vector<tagTile*>* mapInfo, deathMetal* deathMetalInfo)
{
	bool isObject = false;

	// Ÿ�ϸʿ� ������Ʈ�� �ִ��� ã�´�. (��, ���� ���)
	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ������Ż�� �ٶ󺸴� ���⿡ ������Ʈ�� �ִٸ� true�� ���� �ȴ�.
		switch (deathMetalInfo->getBoss_Direction())
		{
		case BD_LEFT:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x - 1 == (*mapInfo)[i]->idX &&
				deathMetalInfo->getBoss_Index().y == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case BD_UP:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x == (*mapInfo)[i]->idX &&
				deathMetalInfo->getBoss_Index().y - 1 == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case BD_RIGHT:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x + 1 == (*mapInfo)[i]->idX &&
				deathMetalInfo->getBoss_Index().y == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case BD_DOWN:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x == (*mapInfo)[i]->idX &&
				deathMetalInfo->getBoss_Index().y + 1 == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;
		}

		// ������Ʈ�� ã������ �ݺ����� ������.
		if (isObject) break;
	}

	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
	return isObject;

	// �߰� �Ϸ���
	// ������Ʈ��� � ������Ʈ����
	// ������Ʈ�� ���������� � ȿ���� �ִ��� ó��?
}

bool Collision::collision_Charactor_Object(vector<tagTile*>* mapInfo, SLAVE_INFO* slave)
{
	bool isObject = false;

	// Ÿ�ϸʿ� ������Ʈ�� �ִ��� ã�´�. (��, ���� ���)
	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ������Ż�� �ٶ󺸴� ���⿡ ������Ʈ�� �ִٸ� true�� ���� �ȴ�.
		switch (slave->status.direction)
		{
		case SLAVE_DIRECTION::SD_LEFT:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				slave->pos.index.x - 1 == (*mapInfo)[i]->idX &&
				slave->pos.index.y == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case SLAVE_DIRECTION::SD_UP:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				slave->pos.index.x == (*mapInfo)[i]->idX &&
				slave->pos.index.y - 1 == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case SLAVE_DIRECTION::SD_RIGHT:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				slave->pos.index.x + 1 == (*mapInfo)[i]->idX &&
				slave->pos.index.y == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case SLAVE_DIRECTION::SD_DOWN:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				slave->pos.index.x == (*mapInfo)[i]->idX &&
				slave->pos.index.y + 1 == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;
		}

		// ������Ʈ�� ã������ �ݺ����� ������.
		if (isObject) break;
	}

	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
	return isObject;
}

bool Collision::collision_Charactor_Object(vector<tagTile*>* mapInfo, SLAVE_INFO* slave, bool reverse)
{
	bool isObject = false;

	// Ÿ�ϸʿ� ������Ʈ�� �ִ��� ã�´�. (��, ���� ���)
	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ������Ż�� �ٶ󺸴� ���⿡ ������Ʈ�� �ִٸ� true�� ���� �ȴ�.
		switch (slave->status.direction)
		{
		case SLAVE_DIRECTION::SD_LEFT:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				slave->pos.index.x + 1 == (*mapInfo)[i]->idX &&
				slave->pos.index.y == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case SLAVE_DIRECTION::SD_UP:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				slave->pos.index.x == (*mapInfo)[i]->idX &&
				slave->pos.index.y + 1 == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case SLAVE_DIRECTION::SD_RIGHT:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				slave->pos.index.x - 1 == (*mapInfo)[i]->idX &&
				slave->pos.index.y == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

		case SLAVE_DIRECTION::SD_DOWN:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				slave->pos.index.x == (*mapInfo)[i]->idX &&
				slave->pos.index.y - 1 == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;
		}

		// ������Ʈ�� ã������ �ݺ����� ������.
		if (isObject) break;
	}

	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
	return isObject;
}

bool Collision::collision_Charactor_Object_Back(vector<tagTile*>* mapInfo, deathMetal* deathMetalInfo)
{
	bool isObject = false;

	// Ÿ�ϸʿ� ������Ʈ�� �ִ��� ã�´�. (��, ���� ���)
	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ������Ż�� �ٶ󺸴� ���⿡ �ݴ��� ������Ʈ�� �ִٸ� true�� ���� �ȴ�.
		switch (deathMetalInfo->getBoss_Direction())
		{
			// ������ �ٶ󺸰� �ִٸ� �������� ã�´�.
		case BD_LEFT:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x + 1 == (*mapInfo)[i]->idX &&
				deathMetalInfo->getBoss_Index().y == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

			// ���� �ٶ󺸰� �ִٸ� �Ʒ��� ã�´�.
		case BD_UP:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x == (*mapInfo)[i]->idX &&
				deathMetalInfo->getBoss_Index().y + 1 == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

			// �������� �ٶ󺸰� �ִٸ� ������ ã�´�.
		case BD_RIGHT:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x - 1 == (*mapInfo)[i]->idX &&
				deathMetalInfo->getBoss_Index().y == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;

			// �Ʒ��� �ٶ󺸰� ������ ���� ã�´�.
		case BD_DOWN:
			if ((*mapInfo)[i]->type == TYPE_OBJECT || (*mapInfo)[i]->type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x == (*mapInfo)[i]->idX &&
				deathMetalInfo->getBoss_Index().y - 1 == (*mapInfo)[i]->idY)
			{
				isObject = true;
			}
			break;
		}

		// ������Ʈ�� ã������ �ݺ����� ������.
		if (isObject) break;
	}

	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
	return isObject;
}

map<PLAYERDIRECTION, tagTile*> Collision::collision_player_tile(vector<tagTile*>* mapInfo, player* playerInfo)
{
	map<PLAYERDIRECTION, tagTile*> _mPlayerTile;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		if (playerInfo->getPlayer().idx == (*mapInfo)[i]->idX &&
			playerInfo->getPlayer().idy - 1 == (*mapInfo)[i]->idY)
		{
			_mPlayerTile.emplace(pair<PLAYERDIRECTION, tagTile*>(PLAYERDIRECTION_UP, (*mapInfo)[i]));
			continue;
		}
		if (playerInfo->getPlayer().idx == (*mapInfo)[i]->idX &&
			playerInfo->getPlayer().idy + 1 == (*mapInfo)[i]->idY)
		{
			_mPlayerTile.emplace(pair<PLAYERDIRECTION, tagTile*>(PLAYERDIRECTION_DOWN, (*mapInfo)[i]));
			continue;
		}
		if (playerInfo->getPlayer().idx - 1 == (*mapInfo)[i]->idX &&
			playerInfo->getPlayer().idy == (*mapInfo)[i]->idY)
		{
			_mPlayerTile.emplace(pair<PLAYERDIRECTION, tagTile*>(PLAYERDIRECTION_LEFT, (*mapInfo)[i]));
			continue;
		}
		if (playerInfo->getPlayer().idx + 1 == (*mapInfo)[i]->idX &&
			playerInfo->getPlayer().idy == (*mapInfo)[i]->idY)
		{
			_mPlayerTile.emplace(pair<PLAYERDIRECTION, tagTile*>(PLAYERDIRECTION_RIGHT, (*mapInfo)[i]));
			continue;
		}
	}

	return _mPlayerTile;
}

map<PLAYERDIRECTION, Enemy*> Collision::collision_player_Enemy_tile(vector<Enemy*>* enemyInfo, player* playerInfo)
{
	map<PLAYERDIRECTION, Enemy*> _mEnemy;

	switch (playerInfo->getPlayer().weapon)
	{
	case PLAYERWAEPON_NONE:
	case PLAYERWAEPON_DAGGER:
		// ���� for���� ������
		for (int i = 0; i < enemyInfo->size(); ++i)
		{
			if (0 > enemyInfo->size()) break; // ���Ͱ� ������ �� 
			//��
			if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_UP, (*enemyInfo)[i]));
			}//��
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_DOWN, (*enemyInfo)[i]));
			}//��
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_LEFT, (*enemyInfo)[i]));
			}//��
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_RIGHT, (*enemyInfo)[i]));
			}
		}// ��
		return _mEnemy;
		break;
	case PLAYERWAEPON_LONGSWORD:
	case PLAYERWAEPON_RAPIER:
	case PLAYERWAEPON_SPEAR:
		// ���� for���� ������
		for (int i = 0; i < enemyInfo->size(); ++i)
		{
			//��
			if (((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 1) ||
				((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
					&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 2))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_UP, (*enemyInfo)[i]));
			}//��
			else if (((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 1) ||
				((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
					&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 2))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_DOWN, (*enemyInfo)[i]));
			}//��
			else if (((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy) ||
				((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 2
					&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_LEFT, (*enemyInfo)[i]));
			}//��
			else if (((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy) ||
				((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 2
					&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_RIGHT, (*enemyInfo)[i]));
			}
		}// ��
		return _mEnemy;
		break;
	case PLAYERWAEPON_BROADSWORD:
		// ���� for���� ������
		for (int i = 0; i < enemyInfo->size(); ++i)
		{
			//��
			if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_UP, (*enemyInfo)[i]));
			}//��
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_DOWN, (*enemyInfo)[i]));
			}//��
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_LEFT, (*enemyInfo)[i]));
			}//��
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_RIGHT, (*enemyInfo)[i]));
			}// �밢 ����
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_UP, (*enemyInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_LEFT, (*enemyInfo)[i]));
			}// �밢 ���
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_UP, (*enemyInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_RIGHT, (*enemyInfo)[i]));
			}// �밢 ����
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_DOWN, (*enemyInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_LEFT, (*enemyInfo)[i]));
			}// �밢 �Ͽ�
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_DOWN, (*enemyInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_RIGHT, (*enemyInfo)[i]));
			}

		}// ��
		return _mEnemy;
		break;
	}
	// ���� �浹 ó�� ���� �����ϱ� 

	return _mEnemy;
}

map<PLAYERDIRECTION, slave*> Collision::collision_player_slave_tile(vector<slave*>* slaveInfo, player* playerInfo)
{
	map<PLAYERDIRECTION, slave*> _mEnemy;
	
	switch (playerInfo->getPlayer().weapon)
	{
	case PLAYERWAEPON_NONE:
	case PLAYERWAEPON_DAGGER:
		// ���� for���� ������
		for (int i = 0; i < slaveInfo->size(); ++i)
		{
			if (0 > slaveInfo->size()) break; // ���Ͱ� ������ �� 
			//��
			if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_UP, (*slaveInfo)[i]));
			}//��
			else if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_DOWN, (*slaveInfo)[i]));
			}//��
			else if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx - 1
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_LEFT, (*slaveInfo)[i]));
			}//��
			else if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx + 1
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_RIGHT, (*slaveInfo)[i]));
			}
		}// ��
		return _mEnemy;
		break;
	case PLAYERWAEPON_LONGSWORD:
	case PLAYERWAEPON_RAPIER:
	case PLAYERWAEPON_SPEAR:
		// ���� for���� ������
		for (int i = 0; i < slaveInfo->size(); ++i)
		{
			//��
			if (((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy - 1) ||
				((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx
					&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy - 2))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_UP, (*slaveInfo)[i]));
			}//��
			else if (((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy + 1) ||
				((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx
					&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy + 2))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_DOWN, (*slaveInfo)[i]));
			}//��
			else if (((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx - 1
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy) ||
				((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx - 2
					&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_LEFT, (*slaveInfo)[i]));
			}//��
			else if (((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx + 1
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy) ||
				((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx + 2
					&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_RIGHT, (*slaveInfo)[i]));
			}
		}// ��
		return _mEnemy;
		break;
	case PLAYERWAEPON_BROADSWORD:
		// ���� for���� ������
		for (int i = 0; i < slaveInfo->size(); ++i)
		{
			//��
			if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_UP, (*slaveInfo)[i]));
			}//��
			else if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_DOWN, (*slaveInfo)[i]));
			}//��
			else if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx - 1
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_LEFT, (*slaveInfo)[i]));
			}//��
			else if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx + 1
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_RIGHT, (*slaveInfo)[i]));
			}// �밢 ����
			else if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx - 1
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_UP, (*slaveInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_LEFT, (*slaveInfo)[i]));
			}// �밢 ���
			else if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx + 1
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_UP, (*slaveInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_RIGHT, (*slaveInfo)[i]));
			}// �밢 ����
			else if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx - 1
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_DOWN, (*slaveInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_LEFT, (*slaveInfo)[i]));
			}// �밢 �Ͽ�
			else if ((*slaveInfo)[i]->get_Slave()->pos.index.x == playerInfo->getPlayer().idx + 1
				&& (*slaveInfo)[i]->get_Slave()->pos.index.y == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_DOWN, (*slaveInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, slave*>(PLAYERDIRECTION_RIGHT, (*slaveInfo)[i]));
			}

		}// ��
		return _mEnemy;
		break;
	}
	// ���� �浹 ó�� ���� �����ϱ� 

	return _mEnemy;
}

map<PLAYERDIRECTION, deathMetal*> Collision::collision_player_Metal_tile(deathMetal* metalInfo, player* playerInfo)
{
	map<PLAYERDIRECTION, deathMetal*> _mDeathMetal;

	switch (playerInfo->getPlayer().weapon)
	{
	case PLAYERWAEPON_NONE:
	case PLAYERWAEPON_DAGGER:
		// ���� for���� ������

		//��
		if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx
			&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy - 1)
		{
			_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_UP, metalInfo));
		}//��
		else if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx
			&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy + 1)
		{
			_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_DOWN, metalInfo));
		}//��
		else if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx - 1
			&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy)
		{
			_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_LEFT, metalInfo));
		}//��
		else if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx + 1
			&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy)
		{
			_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_RIGHT, metalInfo));
		}

		return _mDeathMetal;
	break;
	case PLAYERWAEPON_LONGSWORD:
	case PLAYERWAEPON_RAPIER:
	case PLAYERWAEPON_SPEAR:
		// ���� for���� ������
	
			//��
			if (((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx
				&& (*metalInfo).getBoss_Index().y== playerInfo->getPlayer().idy - 1) ||
				((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx
					&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy - 2))
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_UP, metalInfo));
			}//��
			else if (((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy + 1) ||
				((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx
					&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy + 2))
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_DOWN, metalInfo));
			}//��
			else if (((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx - 1
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy) ||
				((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx - 2
					&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy))
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_LEFT, metalInfo));
			}//��
			else if (((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx + 1
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy) ||
				((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx + 2
					&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy))
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_RIGHT, metalInfo));
			}
	
		return _mDeathMetal;
		break;
	case PLAYERWAEPON_BROADSWORD:
		// ���� for���� ������
	
			//��
			if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy - 1)
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_UP, metalInfo));
			}//��
			else if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy + 1)
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_DOWN, metalInfo));
			}//��
			else if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx - 1
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy)
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_LEFT, metalInfo));
			}//��
			else if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx + 1
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy)
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_RIGHT, metalInfo));
			}// �밢 ����
			else if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx - 1
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy - 1)
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_UP, metalInfo));
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_LEFT, metalInfo));
			}// �밢 ���
			else if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx + 1
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy - 1)
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_UP, metalInfo));
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_RIGHT, metalInfo));
			}// �밢 ����
			else if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx - 1
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy + 1)
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_DOWN, metalInfo));
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_LEFT, metalInfo));
			}// �밢 �Ͽ�
			else if ((*metalInfo).getBoss_Index().x == playerInfo->getPlayer().idx + 1
				&& (*metalInfo).getBoss_Index().y == playerInfo->getPlayer().idy + 1)
			{
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_DOWN, metalInfo));
				_mDeathMetal.insert(pair<PLAYERDIRECTION, deathMetal*>(PLAYERDIRECTION_RIGHT, metalInfo));
			}

		return _mDeathMetal;
		break;
	}


	return _mDeathMetal;
}

