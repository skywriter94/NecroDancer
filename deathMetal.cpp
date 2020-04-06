#include "stdafx.h"
#include "deathMetal.h"

HRESULT deathMetal::init(string bossName, int idx, int idy, int TILE_SIZEX, int TILE_SIZEY)
{
	boss::hp = 9;														 // ������Ż�� �⺻ ü�� �ʱ�ȭ
	boss::save_HP = 9;													 // ������Ż�� ���̺� ü��
	boss::max_HP = 9;													 // ������Ż�� �ƽ� ü��
	boss::shield = 2;													 // ������Ż�� �⺻ �ǵ� �ʱ�ȭ
	boss::attack = 1.5;													 // ������Ż�� �⺻ ���ݷ� �ʱ�ȭ
	boss::magicAttack = 2;												 // ������Ż�� �⺻ �������ݷ� �ʱ�ȭ
	boss::init(bossName, idx, idy, TILE_SIZEX, TILE_SIZEY);				 // ������Ż�� ��ǥ ���� �ʱ�ȭ

	boss::direction = BD_DOWN;											 // ������Ż�� ó���� �Ʒ��� �ٶ󺸰� �ִ�.
	boss::save_Direction = boss::direction;								 // ������Ż�� ������ ������ �д�. (���� ������ �ٲ� ��쿡 �ִϸ��̼��� �ٲܶ� ���)
	boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SDown");		 // ������Ż�� ���� �ִϸ��̼��� ������ٿ�
	boss::ani->start();													 // �ִϸ��̼��� �����Ѵ�.
	boss::isMove = false;												 // ������Ż�� �����̸� �� ���� true�� �ٲ��.
	boss::isJump = false;												 // ������Ż�� �����̸� �� ���� true�� �ٲ��. (��¦ ���� �ϴ� ȿ��)
	boss::isChangeAni = false;											 // ������Ż�� �����̸� �� ���� true�� �ٲ��.
	boss::isCasting = false;											 // ������Ż�� ������ ĳ���� ���̶�� �� ���� true�� �ٲ��.
	boss::isClosePlayer = false;										 // ������Ż�� �÷��̾� ��ó�� �ִٸ� �� ���� true�� �ٲ��.
	boss::save_ClosePlayer = boss::isClosePlayer;						 // ��ó�� �÷��̾ �ִ��� ���θ� �����صд�. 
	boss::isShield_Hit = false;

	clearThrowShield();													 // ������Ż�� �ǵ� ������ �ʱ�ȭ ���ش�.

	return S_OK;
}

void deathMetal::release()
{
}

void deathMetal::update()
{
	Info_Update();												 // ������Ż�� �ε��� ������ �ٲ�� �ڵ����� ����, ��Ʈ�� �������ش�.
	//deathMetal_Animation_Test();								 // ������Ż�� �ִϸ��̼� �׽�Ʈ �Լ�
	deathMetal_ChangePhase();									 // ������Ż�� ������ ü���� �Լ�									
	deathMetal_ChangeAnimation();								 // ������Ż�� �ִϸ��̼� ü���� �Լ�
	boss_Move();												 // ������Ż�� �̵� ���� �Լ�
}

void deathMetal::render()
{
	boss::render();
	if(_throwShield.isOut) boss::render(_throwShield);	 // ������ 1�� ������ �ǵ��� ������ ���ŵǰ�, �׶����� ���̱� �����Ѵ�.
}

void deathMetal::clearThrowShield()
{
	// �ǵ� �̹����� �ִ´�.
	_throwShield.image = IMAGEMANAGER->findImage("deathMetal_Shield");
	_throwShield.center.x = 0;
	_throwShield.center.y = 0;
	_throwShield.angle = 0;
	_throwShield.speed = 0;
	_throwShield.isShieldUpdate = false;
	_throwShield.isOut = false;
	boss::isThrowShield = false;
}

void deathMetal::deathMetal_Animation_Test()
{
	// �ִϸ��̼� �׽�Ʈ �Լ�

	// ������Ż�� �̵��� ������ �������� Ű �Է��� ���´�.
	if (!boss::isMove)
	{

		// ������Ż�� ������ �ٲٰ�, �ִϸ��̼��� �ٲٱ� ���� true������ ����
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
		{
			boss::direction = BD_LEFT;
			worldTime = TIMEMANAGER->getWorldTime();	// ���� Ÿ���� �����Ѵ�.
														// ���� �Լ� ��������

			boss::isChangeAni = true;	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
			boss::isMove = true;		// ������ �������ٸ� Move�� true��
			boss::isJump = true;		// ������ �����϶� ��¦ �����Ѵ�. ���� true��
		}

		// ������Ż�� ������ �ٲٰ�, �ִϸ��̼��� �ٲٱ� ���� true������ ����
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
		{
			boss::direction = BD_UP;
			worldTime = TIMEMANAGER->getWorldTime();	// ���� Ÿ���� �����Ѵ�.
														// ���� �Լ� ��������

			//boss::index.y--;
			boss::isChangeAni = true;	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
			boss::isMove = true;		// ������ �������ٸ� Move�� true��
			boss::isJump = true;		// ������ �����϶� ��¦ �����Ѵ�. ���� true��
		}

		// ������Ż�� ������ �ٲٰ�, �ִϸ��̼��� �ٲٱ� ���� true������ ����
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
		{
			boss::direction = BD_RIGHT;
			worldTime = TIMEMANAGER->getWorldTime();	// ���� Ÿ���� �����Ѵ�.
														// ���� �Լ� ��������

			//boss::index.x++;
			boss::isChangeAni = true;	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
			boss::isMove = true;		// ������ �������ٸ� Move�� true��
			boss::isJump = true;		// ������ �����϶� ��¦ �����Ѵ�. ���� true��
		}

		// ������Ż�� ������ �ٲٰ�, �ִϸ��̼��� �ٲٱ� ���� true������ ����
		if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
		{
			boss::direction = BD_DOWN;
			worldTime = TIMEMANAGER->getWorldTime();	// ���� Ÿ���� �����Ѵ�.
														// ���� �Լ� ��������

			//boss::index.y++;
			boss::isChangeAni = true;	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
			boss::isMove = true;		// ������ �������ٸ� Move�� true��
			boss::isJump = true;		// ������ �����϶� ��¦ �����Ѵ�. ���� true��
		}
	}

	// ������Ż�� �ִϸ��̼��� ���� ������� �ٲٰ� ����
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Attack");
		boss::ani->start();
	}

	// ������Ż�� �ִϸ��̼��� ��� ������� �ٲٰ� ����
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Idle");
		boss::ani->start();
	}

	// ������Ż�� ü���� ���ҽ�Ų��.
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
	{
		boss::setBoss_HP_Hit();	// ������ ü���� 1 ���� ��Ų��.
		boss::isChangeAni = true;
	}

	// �÷��̾ ��ó�� ������ true ������ false (�׽�Ʈ��)
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
	{
		boss::isClosePlayer = !boss::isClosePlayer;	// �÷��̾ ������ �ִٸ� true
		boss::isChangeAni = true;
	}

	// ������Ż �ǵ� �׽�Ʈ��
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
	{
		boss::hp = 8;
		deathMetal_ShieldPosUpdate();
		boss::isThrowShield = false;
		_throwShield.isShieldUpdate = false;
		_throwShield.isOut = false;
		boss::isChangeAni = true;
	}
}

void deathMetal::deathMetal_ChangeAnimation()
{
	// ���⿡ ��ȭ�� ������ true�� ���� �־��ش�.
	if (boss::direction != boss::save_Direction)
	{
		// ���� ������ ��ȭ �Ҷ����� �̰��� ������ �ʴ´�.
		boss::save_Direction = boss::direction;
		boss::isChangeAni = true;
		boss::change_Ani = true;
	}

	// �÷��̾ ��ó�� �ְų� �ָ� ���ų� ���� ���� �Ǿ����� ���´�.
	if (boss::isClosePlayer != boss::save_ClosePlayer)
	{
		// ���� ��ȭ�� ���������� ������ �ʴ´�.
		boss::save_ClosePlayer = boss::isClosePlayer;
		boss::isChangeAni = true;
		boss::change_Ani = true;
	}
	
	// ������Ż�� ü�¿� ��ȭ�� �ִٸ� �ִϸ��̼��� �ٲ��ش�.
	if (boss::save_HP != boss::hp)
	{
		SOUNDMANAGER->play("deathmetal_hit", 1.5f);
		// ���� 1����� �ƴ϶�� �����̵��� �����Ѵ�.
		if (boss::phase != BP_PHASE_1)
		{
			// ������ ��ġ�� 10�� ���ٸ�
			if (boss::index.x >= 8 && boss::index.x <= 13 &&
				boss::index.y >= 10 && boss::index.y <= 14)
			{
				boss::index.x = 17;
				boss::index.y = 17;
				boss::direction = BD_LEFT;
			}
	
			// ������ ��ġ�� 2�� ���ٸ�
			else if (boss::index.x >= 13 && boss::index.x <= 18 &&
				boss::index.y >= 10 && boss::index.y <= 14)
			{
				boss::index.x = 9;
				boss::index.y = 17;
				boss::direction = BD_RIGHT;
			}
	
			// ������ ��ġ�� 7�� ���ٸ�
			else if (boss::index.x >= 8 && boss::index.x <= 13 &&
				boss::index.y >= 14 && boss::index.y <= 18)
			{
				boss::index.x = 17;
				boss::index.y = 11;
				boss::direction = BD_LEFT;
			}
	
			// ������ ��ġ�� 5�� ���ٸ�
			else if (boss::index.x >= 13 && boss::index.x <= 18 &&
				boss::index.y >= 14 && boss::index.y <= 18)
			{
				boss::index.x = 9;
				boss::index.y = 11;
				boss::direction = BD_RIGHT;
			}
	
		}
	
		// ���� �Ǵ� �����̺� ��ȯ ĳ���� ���߿� ������ ����
		boss::slave_Summon.cTime = boss::slave_Summon.cTime_M;
		boss::slave_Summon.isCasting = false;
	
		boss::save_HP = boss::hp;
		boss::isChangeAni = true;
		boss::change_Ani = true;
	}

	// ������Ż�� �ٶ󺸴� ���⿡ ���� �ִϸ��̼��� �ٲ��ش�.
	if (boss::isChangeAni)	// ������ �������ٸ� �ִϸ��̼��� �ٲ��־���Ѵ�.
	{
		switch (boss::direction)
		{
		case BD_LEFT:
			// ������Ż�� 1������� ���и� ��� �ִ� �ִϸ��̼��̴�.
			if (boss::phase == BP_PHASE_1)
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Left");
					//boss::ani->start();
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SLeft");
					//boss::ani->start();
				}
			}

			// ������Ż�� 2��������ʹ� ���ݸ��, ����� 2���θ� �����δ�.
			else
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Idle");
						//boss::ani->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						//boss::ani->start();
					}
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
						//boss::ani->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						//boss::ani->start();
					}
				}
			}

			// ������Ż�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
			boss::angle = PI;
			break;

		case BD_UP:
			// ������Ż�� 1������� ���и� ��� �ִ� �ִϸ��̼��̴�.
			if (boss::phase == BP_PHASE_1)
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Up");
					//boss::ani->start();
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SUp");
					//boss::ani->start();
				}
			}

			// ������Ż�� 2��������ʹ� ���ݸ��, ����� 2���θ� �����δ�.
			else
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Idle");
						//boss::ani->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						//boss::ani->start();
					}
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
						//boss::ani->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						//boss::ani->start();
					}
				}
			}

			// ������Ż�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
			boss::angle = PI / 180 * 90;

			break;

		case BD_RIGHT:
			// ������Ż�� 1������� ���и� ��� �ִ� �ִϸ��̼��̴�.
			if (boss::phase == BP_PHASE_1)
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Right");
					//boss::ani->start();
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SRight");
					//boss::ani->start();
				}
			}

			// ������Ż�� 2��������ʹ� ���ݸ��, ����� 2���θ� �����δ�.
			else
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Idle");
						//boss::ani->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						//boss::ani->start();
					}
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
						//boss::ani->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						//boss::ani->start();

					}
				}

				// ������Ż�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
				boss::angle = PI*2;

				break;

		case BD_DOWN:
			// ������Ż�� 1������� ���и� ��� �ִ� �ִϸ��̼��̴�.
			if (boss::phase == BP_PHASE_1)
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Down");
					//boss::ani->start();
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SDown");
					//boss::ani->start();
				}
			}

			// ������Ż�� 2��������ʹ� ���ݸ��, ����� 2���θ� �����δ�.
			else
			{
				// �÷��̾���� �Ÿ��� ����� ��� ������Ż�� ���δ�.
				if (boss::isClosePlayer)
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Idle");
						//boss::ani->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_Attack");
						//boss::ani->start();
					}
				}

				// �÷��̾���� �Ÿ��� �� ��� ������Ż�� ������ ���� �̹����̴�.
				else
				{
					// ���� ĳ���� ���� �ƴҶ��� �����
					if (!boss::isCasting)
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SIdle");
						//boss::ani->start();
					}

					// ���� ĳ���� ���϶��� ���� ���
					else
					{
						boss::ani = KEYANIMANAGER->findAnimation("deathMetal_SAttack");
						//boss::ani->start();
					}
				}
			}

			// ������Ż�� �ش� ������ ���� ������ ������ �ʱ�ȭ���ش�.
			boss::angle = PI / 180 * 270;

			break;
			}
			boss::isChangeAni = false;		// ������ �����ӿ� ���� �ִϸ��̼��� �ٲ��־��ٸ�, ���� �����ӱ��� false�� �־ �ٽ� �ٲ��� �ʰ� �Ѵ�.
		}
	}

	// ture�� ���϶� �ѹ��� ��ŸƮ ���ְ� �ٽ� false��
	if (boss::change_Ani)
	{
		boss::change_Ani = false;
		boss::ani->start();
	}
}

void deathMetal::deathMetal_ChangePhase()
{
	if (boss::hp >= 7)		boss::phase = BP_PHASE_1;
	else if (boss::hp >= 5)	boss::phase = BP_PHASE_2;
	else if (boss::hp >= 3)	boss::phase = BP_PHASE_3;
	else if (boss::hp > 0)	boss::phase = BP_PHASE_4; 

	// ������Ż ������
	// HP 9 ~ 7 : ���и� ��� �� ���ڸ��� �̵��ϸ鼭 �÷��̾�� �ٰ�����.
	//            �Ϲ� ����� ���и� �� ������ ���� ��Ż�� ���鿡�� �����ϸ� �ڷ� ƨ��Ը� �� ���̸�, ���ÿ� ���㰡 ��ȯ�ȴ�.
	//            �ݵ�� ���̳� �ڸ� �����ؾ� �Ѵ�. �ٸ� ���� ȿ���� �ִ� ���⸦ ����ϸ� ���鿡���� ������ �� �ִ�.
	// HP 6 ~ 5 : ���и� ���� ������ �� ���ڸ��� �����̸鼭 �÷��̾�� �Ÿ��� �д�. �̵��� "Come to me!"��� ��ġ�� ���� ���ø��µ�,
	//            ���� �� ���� ���� ���ݹ��� ������ 1~3 ������ �ذ��� ��ȯ�Ѵ�. �̶����ʹ� ���ݹ����� �ݴ������� ���� �̵��Ѵ�.
	// HP 4 ~ 3 : "End of the line!"�� ��ġ�� ��� �ذ��� ��ȯ�Ѵ�.
	// HP 2 ~ 1 : �� ���ڸ��� �̵��ϱ� �����ϸ鼭 �����̳� ������ ���� �ٴ´�. �� �� ���������� �÷��̾ ���󰡸鼭 �� ���ڸ���
	//            "Bathe in fire!"�� ��ġ�� ���������� ���̾�� �߻��Ѵ�.

	// ���� ����� 1�̰�, ���� ������ ������ ���� �ʾҴٸ� �̰����� ����.
	if (boss::phase == BP_PHASE_1 && !boss::boss_Bool.PHASE_BOOL.PHASE_1_Set)
	{
		boss::move.set_BossMoveCount(3);	// 1��������� 3���� ���� �̵��� �Ѵ�.
		boss::move_Count = boss::move.get_BossMoveCount();	// �̵��� �ʿ��� ���ڸ� �����Ѵ�.
		boss::boss_Bool.PHASE_BOOL.PHASE_1_Set = true;	// ������ �������� ture�� ���� �ְ� �ٽ� �̰��� ������ �ʵ��� �Ѵ�.
	}

	// ���� ����� 2�̰�, ���� ������ ������ ���� �ʾҴٸ� �̰����� ����.
	if (boss::phase == BP_PHASE_2 && !boss::boss_Bool.PHASE_BOOL.PHASE_2_Set)
	{
		boss::move.set_BossMoveCount(2);					// 2��������� 2���� ���� �̵��� �Ѵ�.
		boss::move_Count = boss::move.get_BossMoveCount();	// �̵��� �ʿ��� ���ڸ� �����Ѵ�.
		boss::boss_Bool.PHASE_BOOL.PHASE_2_Set = true;		// ������ �������� ture�� ���� �ְ� �ٽ� �̰��� ������ �ʵ��� �Ѵ�.

		boss::slave_Summon.cTime = 4;						// ��ų ��Ÿ��
		boss::slave_Summon.cTime_M = 4;						// �ܽ�Ʈ ��ų ��Ÿ��
		SOUNDMANAGER->play("deathmetal_skels");
	}

	// ���� ����� 3�̰�, ���� ������ ������ ���� �ʾҴٸ� �̰����� ����.
	if (boss::phase == BP_PHASE_3 && !boss::boss_Bool.PHASE_BOOL.PHASE_3_Set)
	{
		boss::move_Count = boss::move.get_BossMoveCount();	// �̵��� �ʿ��� ���ڸ� �����Ѵ�.
		boss::boss_Bool.PHASE_BOOL.PHASE_3_Set = true;	// ������ �������� ture�� ���� �ְ� �ٽ� �̰��� ������ �ʵ��� �Ѵ�.

		boss::isCasting = false;
	}

	// ���� ����� 4�̰�, ���� ������ ������ ���� �ʾҴٸ� �̰����� ����.
	if (boss::phase == BP_PHASE_4 && !boss::boss_Bool.PHASE_BOOL.PHASE_4_Set)
	{
		boss::move.set_BossMoveCount(2);	// 4��������� 1���� ���� �̵��� �Ѵ�.
		boss::move_Count = boss::move.get_BossMoveCount();	// �̵��� �ʿ��� ���ڸ� �����Ѵ�.
		boss::boss_Bool.PHASE_BOOL.PHASE_4_Set = true;	// ������ �������� ture�� ���� �ְ� �ٽ� �̰��� ������ �ʵ��� �Ѵ�.
		SOUNDMANAGER->play("deathmetal_skels2");
			
		// ���̾ ��Ÿ��
		boss::boss_FireBall.cTime = 4;						// ��ų ��Ÿ��
		boss::boss_FireBall.cTime_M = 4;					// �ܽ�Ʈ ��ų ��Ÿ��
		boss::boss_FireBall.isCasting = false;				// ��ų ����� �Ҷ� true
	}

	// ���� ���� ����� 2�� �ٲ����, �ǵ带 ���� ������ �ʾҴٸ� �����Ѵ�. (�ǵ� ������ �ִϸ��̼� �Լ�)
	if (boss::phase != BP_PHASE_1 && !boss::isThrowShield)	deathMetal_ThrowShield();

	// ������ �׾���. �����̸� �ȵ� ������ �׾��ٸ� �Ⱥ��̰� �����.
	if (boss::hp <= 0)	boss::boss_Bool.boss_Die = true;

	if (boss::boss_Bool.boss_Die)
	{
		// ���� �̰� �� ����?
	}
}

void deathMetal::deathMetal_ShieldPosUpdate()
{
	// ��Ʈ�� ���Ѵ�. (����x - �ǵ��̹��� ���� / 2, ����y - �����̹��� ���� / 2, �ǵ��̹��� ����, �ǵ��̹��� ����)
	_throwShield.rc = RectMake(boss::center.x - _throwShield.image->getWidth() / 2, 
		boss::center.y - boss::_image->getFrameHeight() / 2, _throwShield.image->getWidth(), _throwShield.image->getHeight());

	// ��Ʈ�� �̿��Ͽ� ������ ���Ѵ�.
	_throwShield.center.x = (_throwShield.rc.left + _throwShield.rc.right) / 2;
	_throwShield.center.y = (_throwShield.rc.top + _throwShield.rc.bottom) / 2;

	// �ǵ尡 ó�� ���ư� ���� (������ �ٶ󺸴� ���⿡ ���� ���а� ���ư��� ������ �ٸ���.)
	switch (boss::direction)
	{
	case BD_LEFT:
			_throwShield.angle = PI / 180 * 190;
		break;

	case BD_UP:
			_throwShield.angle = PI / 180 * 100;
		break;

	case BD_RIGHT:
			_throwShield.angle = PI / 180 * 40;
		break;

	case BD_DOWN:
			_throwShield.angle = PI / 180 * 330;
		break;
	}
	
	// ������ �ٶ󺸴� ������ �����صд�. (���Ŀ� ������ �̵��� �� �� �ֱ� ������)
	_throwShield.direction = boss::direction;

	// �ǵ尡 ���ư��� �ӵ�
	_throwShield.speed = 3.0f;

	// ������ �ѹ��� �Ѵ�.
	_throwShield.isShieldUpdate = true;		// ��� ��ǥ ������ �����ٸ� true�� ������ ����
	_throwShield.isOut = true;				// ������ �����ٸ� ���и� ������ش�.
}

void deathMetal::deathMetal_ThrowShield()
{
	if(!_throwShield.isShieldUpdate) deathMetal_ShieldPosUpdate();		// ������Ż�� ��ǥ�� �̿��Ͽ� �ǵ��� ��ġ�� �������ش�. (���� �� ture�� ������ ���� �Ѵ�.)

	// �ǵ�� ������ �ӵ���ŭ ���� �� ������ ���ư���.
	_throwShield.center.x += cosf(_throwShield.angle) * _throwShield.speed;
	_throwShield.center.y += -sinf(_throwShield.angle) * _throwShield.speed;

	// �ǵ��� ������ �̼��ϰ� �ٲ��ش�. (������ �ϵ��� ����� ����)
	_throwShield.angle += 0.07f;

	// �ǵ��� ��Ʈ ��ġ�� �������ش�.
	_throwShield.rc = RectMake(_throwShield.center.x - _throwShield.image->getWidth() / 2,
		_throwShield.center.y - _throwShield.image->getHeight() / 2, _throwShield.image->getWidth(), _throwShield.image->getHeight());

	// �ǵ� �������� ��� ������ isThrowShield�� ���� true�� �ǰ� ��°� ������ ��� �����Ѵ�.
	// ������ ���⿡ ���� �ǵ尡 ������� ������ �ٸ��� ������ �ٽ� �ѹ� ����ġ���� �����ش�.
	switch (_throwShield.direction)
	{
	case BD_LEFT:
		if (_throwShield.angle >= PI / 180 * 360)
		{
			boss::isThrowShield = true;					// �ǵ� ������ �����ٸ� true
			_throwShield.isOut = false;					// �ǵ� �̹����� �� �̻� �׸��� �ʵ��� false
		}
		break;

	case BD_UP:
		if (_throwShield.angle >= PI / 180 * 270)
		{
			boss::isThrowShield = true;					// �ǵ� ������ �����ٸ� true
			_throwShield.isOut = false;					// �ǵ� �̹����� �� �̻� �׸��� �ʵ��� false
		}
		break;

	case BD_RIGHT:
		if (_throwShield.angle >= PI / 180 * 210)
		{
			boss::isThrowShield = true;					// �ǵ� ������ �����ٸ� true
			_throwShield.isOut = false;					// �ǵ� �̹����� �� �̻� �׸��� �ʵ��� false
		}
		break;

	case BD_DOWN:
		if (_throwShield.angle >= PI / 180 * 500)
		{
			boss::isThrowShield = true;					// �ǵ� ������ �����ٸ� true
			_throwShield.isOut = false;					// �ǵ� �̹����� �� �̻� �׸��� �ʵ��� false
		}
		break;
	}
}
