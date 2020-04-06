#include "stdafx.h"
#include "boss.h"

boss::boss()
	: hp(0), shield(0), attack(0), magicAttack(0), skill_Casting_Cnt(0), angle(0), speed(0), worldTime(0)
	
{
}

boss::~boss()
{
}

HRESULT boss::init(string bossName, int _idx, int _idy, int _tileSizeX, int _tileSizeY)
{
	findBossType(bossName);											// ������ Ÿ���� �����Ѵ�.
	findBossImage();												// ������ Ÿ���� �̿��Ͽ� �̹����� ã�� �ִ´�.
	settingBossPos(_idx, _idy, _tileSizeX, _tileSizeY);				// ������ ��ǥ �������� �ʱ�ȭ �Ѵ�.
	settingBossMoveVariable(_tileSizeX, _tileSizeY);				// ������ �̵��� �ʿ��� ������ �ʱ�ȭ�Ѵ�.
	settingBossVariable();											// �������� ����� ���� �ʱ�ȭ
	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
}

void boss::render()
{
	//PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY, BLACKNESS);
	// aniRender�� ���� �߽����� �׷�����.
	_image->aniRender(CAMERAMANAGER->getWorldDC(), center.x, center.y - (_image->getFrameHeight() / 3), ani);

	// ������ ü�� �������� �Ѵ� �°� ǥ�� �ȴ�.
	// ���� ü�� ������ �°� �����ʿ������� ���ʱ��� �׷��ش�.
	// ���� ü���� ���ʿ��� ���������� �׷��ش�.
	// ���� ü�� ������ �þ�� ���� ü�� ������ �þ
	if(hp < max_HP) showBossHP();

	if (KEYMANAGER->isStayKeyDown('P'))
	{
		// ������ ��ġ�� Ÿ���� ��Ʈ
		Rectangle(CAMERAMANAGER->getWorldDC(), rc);
	}
}

void boss::render(ThrowShield info)
{
	info.image->render(CAMERAMANAGER->getWorldDC(), info.rc.left, info.rc.top);
}

void boss::findBossType(string bossname)
{
	if (bossname == "������Ż" || bossname == "����_��Ż") type = (BOSSTYPE)DEATH_METAL;
	else type = (BOSSTYPE)EMPTY;
}

void boss::findBossImage()
{
	switch (type)
	{
	case DEATH_METAL:
		_image = IMAGEMANAGER->findImage("Death_Metal");
		break;

	case EMPTY:
		_image = IMAGEMANAGER->findImage("Test_Floor");
		break;
	}
}

void boss::settingBossPos(int idx, int idy, int tileSizeX, int tileSizeY)
{
	index.x = idx;
	index.y = idy;

	// ������ �̹��� ũ�Ⱑ Ÿ�Ϻ��� ũ�� ������ ���� - �̹��� �������� ��Ʈ left�� ���ϰ�, ��Ʈ bottom - �̹��� ���̸� �̿��Ͽ� top�� ���Ѵ�.
	rc = RectMake(idx * tileSizeX, idy * tileSizeY, tileSizeX, tileSizeY);

	// ������ �����.
	center.x = (rc.left + rc.right) / 2;
	center.y = (rc.top + rc.bottom) / 2;

	_tileSize_X = tileSizeX;
	_tileSize_Y = tileSizeY;
}

void boss::settingBossMoveVariable(int tileSizeX, int tileSizeY)
{
	angle = 0;										// ������ �̵� �ؾ� �ϴ� ����
	time = 0.2f;									// ���� Ÿ�ϱ��� �̵� �ð�
	distance = tileSizeX;							// ���� Ÿ�ϱ����� �Ÿ�
	speed = move.getMoveSpeed(time, distance);		// ���� Ÿ�ϱ��� �̵� �ӵ�
}

void boss::settingBossVariable()
{
	boss_Bool.PHASE_BOOL.PHASE_1_Set = false;
	boss_Bool.PHASE_BOOL.PHASE_2_Set = false;
	boss_Bool.PHASE_BOOL.PHASE_3_Set = false;
	boss_Bool.PHASE_BOOL.PHASE_4_Set = false;

	boss_Bool.boss_Die = false;
	boss_Bool.phase4_MoveX_Direction = false;
	boss_Bool.phase4_MoveX_End = false;
	boss_Bool.phase4_MoveX_Direction_Find = false;
	boss_Bool.phase4_MagicRangeSave = false;

	move_Count = 0;

	slave_Summon.isCasting = false;
	slave_Summon.cTime = 0;
	slave_Summon.cTime_M = 0;
	slave_Summon.rnd = 0;

	boss_FireBall.isCasting = false;
	boss_FireBall.cTime = 0;
	boss_FireBall.cTime_M = 0;

}

void boss::showBossHP()
{
	float tempHP_SizeX = IMAGEMANAGER->findImage("Boss_Hp_Full")->getWidth();
	float tempHP_SizeY = IMAGEMANAGER->findImage("Boss_Hp_Full")->getHeight();
	float tempBoss_SizeY = IMAGEMANAGER->findImage("Death_Metal")->getFrameHeight();

	// ���� ���� ü�¸�ŭ �̹����� �����ʿ��� �������� �׷��ش�.
	for (int i = 0; i < hp; ++i)
	{
		IMAGEMANAGER->findImage("Boss_Hp_Full")->render(CAMERAMANAGER->getWorldDC(),
			((center.x + tempHP_SizeX * 4) - tempHP_SizeX / 2) - (i * tempHP_SizeX)
				, center.y - tempBoss_SizeY);
	}

	// ���� ü���� �����ʿ��� �������� �׷��ش�.
	for (int i = 0; i < max_HP - hp; ++i)
	{
		IMAGEMANAGER->findImage("Boss_Hp_Null")->render(CAMERAMANAGER->getWorldDC(),
			((center.x - tempHP_SizeX * 4) - tempHP_SizeX / 2) + (i * tempHP_SizeX)
			, center.y - tempBoss_SizeY);
	}


}

void boss::Info_Update()
{
	if (!isMove)
	{
		// ������ �̹��� ũ�Ⱑ Ÿ�Ϻ��� ũ�� ������ ���� - �̹��� �������� ��Ʈ left�� ���ϰ�, ��Ʈ bottom - �̹��� ���̸� �̿��Ͽ� top�� ���Ѵ�.
		rc = RectMake(index.x * _tileSize_X, index.y * _tileSize_Y, _tileSize_X, _tileSize_Y);

		center.x = (rc.left + rc.right) / 2;
		center.y = (rc.top + rc.bottom) / 2;
	}
}

void boss::boss_Move()
{
	// ������ �������ٸ� true
	if (isMove) move.startMove(&time, &distance, &angle, &speed, &worldTime, &center, &index, direction, &isMove);
	// ������ �������ٸ� ���� ���°� true
	// ������ ������ ������ �ʿ��� ����
	// ������ ��ǥ, ���� ���� ���� ������ �ӵ�?, ���⿡ �°� ��ġ�� �ٸ���
	// ���� �ָ� ��� ������ �ؾ��Ѵ�. �ش� bool���� ����������
	if (isJump) move.jumping(&direction, &center, &jump);
}

