#pragma once
#include "gameNode.h"
#include "bossLibrary.h"
#include "bossMove.h"

class boss : gameNode
{
protected:
	// ���� �������ͽ�
	BOSSTYPE			type;					// ���� Ÿ��
	BOSS_PHASESTATE		phase;					// ���� ������ ����
	BOSS_DIRECTION		direction;				// ���� ����
	int					hp;						// HP ����Ʈ
	int					shield;					// �ǵ� ����Ʈ
	float				attack;					// ������ ���ݷ�
	float				magicAttack;			// ������ �������ݷ�

	// ���� ��ǥ
	RECT		rc;								// ������ ��Ʈ		  (Ÿ���� left, bottom �������� ����ؼ� �����)
	POINTFLOAT	center;							// ������ �߽� ��ǥ	  (Ÿ���� �߽�)
	POINT		index;							// ������ �迭 �ε���	  (��� Ÿ�Ͽ� �ִ��� �ε���)

	// ���� �̹���
	animation*  attack_Ani;						// ���� ���� ����Ʈ �ִϸ��̼� ����
	image*		att_Image;						// ���� ���� �̹����� ��´�.
	POINTFLOAT	ani_Center;						// ����Ʈ �ִϸ��̼��� �Ѹ� ��ǥ�� �����Ѵ�.

	animation*  ani;							// ������ ���ϸ��̼� ����
	image*		_image;							// ������ �̹����� ��´�.

	// ���� �����ϴ� �� �����ϴ� ����
	int			_tileSize_X, _tileSize_Y;		// Ÿ���� ����� ��Ƶд�.
	int			skill_Casting_Cnt;				// ��ų ĳ���� �ð�
	bool		isMove;							// ������ ���������� ����
	bool		isJump;							// ������ �̵��� �Ҷ� ���� ����
	bool		isChangeAni;					// ������ �������ٸ� �ִϸ��̼��� �ٲ�����Ѵ�.
	bool		isCasting;						// ��ų ���� ������ ����
	bool		isClosePlayer;					// �÷��̾ ��ó�� �ִ��� ����
	bool		isThrowShield;					// �ǵ带 �������� ����
	bool		isShield_Hit;					// �ǵ尡 �ǰ� ���ߴٸ� true

	float		angle;							// ������ �̵��Ҷ� ���ϰ���
	float       time;							// ������ ���� Ÿ�ϱ��� �̵��Ҷ� �ɸ��� �ð�
	float		speed;							// ������ ���� Ÿ�ϱ��� �̵��ϴ� �ӵ�
	float		distance;						// Ÿ�� ������
	float       worldTime;						// ���� Ÿ�� 
	bossMove	move;							// ���� �̵��� �ʿ��� ���� �Լ�
	tagBossJump jump;							// ���� ������ �ʿ��� ���� �Լ�
	int			move_Count;						// ������ �̵� ������ ���ڸ� �����Ѵ�.

	BOSS_BOOL	boss_Bool;						// ������ ����ϴ� bool�� ��Ƶξ���.
	BOSS_SUMMONS_SKILL	slave_Summon;			// �����̺� ��ȯ ��ų
	BOSS_Magic_SKILL	boss_FireBall;			// ���� ���̾ ��ų

	BOSS_DIRECTION save_Direction;				// ������ ������ �����صд�.
	bool		   change_Ani;					// �ִϸ��̼� ü������ �������� ����
	bool		   save_ClosePlayer;		    // �÷��̾ ��ó�� �ִ��� ���� ���̺�

	int			   save_HP;						// ������ ���� HP�� �����صд�.
	int			   max_HP;						// ������ �ִ� HP

public:
	boss();
	~boss();

	virtual HRESULT init(string bossName, int _idx, int _idy, int _tileSizeX, int _tileSizeY);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(ThrowShield info);

	void findBossType(string bossname);																				// ���� Ÿ���� ã���ش�.
	void findBossImage();																							// Ÿ�� ������ ���� �̹����� ã�� �ִ´�.
	void settingBossPos(int idx, int idy, int tileSizeX, int tileSizeY);											// ������ ���� ��ǥ ���� �ʱ�ȭ
	void settingBossMoveVariable(int tileSizeX, int tileSizeY);														// ������ �̵� ���� �ʱ�ȭ
	void settingBossVariable();																						// �������� ����� ���� �ʱ�ȭ
	void showBossHP();																								// ������ ü�� �̹��� ǥ��
	void setBoss_isShield_Hit(bool shield_Hit) { isShield_Hit = shield_Hit; }										// �ǵ� ������ �����Ѵ�.

	// ���� ���� ���� �Լ�
	int getBoss_HP() { return hp; }																					// ������ HP�� �޾ƿ´�.
	int getBoss_Shield() { return shield; }																			// ������ �ǵ带 �޾ƿ´�.
	float getBoss_Atk() { return attack; }																			// ������ ���ݷ��� �޾ƿ´�.
	float getBoss_MegicAtk() { return magicAttack; }
	BOSS_DIRECTION getBoss_Direction() { return direction; }														// ������ �ٶ󺸴� ������ �޾ƿ´�.

	RECT getBoss_Rect() { return rc; }																				// ������ ��Ʈ�� �޾ƿ´�.
	POINTFLOAT getBoss_Center() { return center; }																	// ������ ������ �޾ƿ´�.
	POINT getBoss_Index() { return index; }																			// ������ �迭 �ε����� �޾ƿ´�.

	int getBoss_Move_Count_Value() { return move.get_BossMoveCount(); }
	int getBoss_Move_Count() { return move_Count; }

	bool getBoss_Beat() { return boss_Bool.get_Beat; }																// ������ ��Ʈ�� �޾Ҵ��� ����
	POINTFLOAT getBoss_BaseAttack_Pos() { return ani_Center; }														// ����Ʈ �ִϸ��̼��� �Ѹ� ��ǥ
	image* getBoss_AttImage() { return att_Image; }
	BOSS_PHASESTATE getBoss_Phase() { return phase;	}																// ���� ������ �޾ƿ���.
	bool getBoss_isShield_Hit() { return isShield_Hit; }															// �ǵ� �ǰ� ���� �޾ƿ���.

	bool getBoss_Dead() { return boss_Bool.boss_Die; }																// ���� �׾����� ����
	bool getBoss_ClosePlayer() { return isClosePlayer; }
	BOSS_SUMMONS_SKILL getBoss_SummonSkill() { return slave_Summon; }												// �����̺� ��ȯ�� �ʿ��� ������ ����
	BOSS_SUMMONS_SKILL* boss_SummonSkill() { return &slave_Summon; }
	BOSS_Magic_SKILL* boss_FireBallSkill() { return &boss_FireBall; }
	BOSS_BOOL* getBoss_Bool() { return &boss_Bool; }


	// ���� ���� ���� �Լ�
	void setBoss_HP(int _hp) { hp = _hp; if (hp > 9) hp = 9; if (hp < 0) hp = 0; }									// ������ HP�� �����Ѵ�. (hp�� �ִ�ġ �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_HP_Hit() { hp--; if (hp < 0) hp = 0; }																// ������ ü���� 1 �����Ѵ�. (hp�� �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_HP_Hit(int damage) { hp -= damage; if (hp < 0) hp = 0; }	 										// �޾� �� ��ġ��ŭ ������ ü���� �����Ѵ�. (hp�� �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)

	void setBoss_HP_Heal() { hp++; if (hp > 9) hp = 9; }															// ������ ü���� 1 �����Ѵ�. (hp�� �ִ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_HP_Heal(int heal) { hp += heal; if (hp > 9) hp = 9; }												// �޾� �� ��ġ��ŭ ������ ü���� �����Ѵ�. (hp�� �ִ�ġ�� �Ѿ�� �ʰ� ����ó��) 

	void setBoss_Shield(int _shield) { shield = _shield; if (shield > 2) shield = 2; if (shield < 0) shield = 0; }	// �ǵ��� ���� �����Ѵ�. (�ǵ尡 �ִ�ġ �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_Shield_Hit() { shield--; if (shield < 0) shield = 0; }												// �ǵ带 1 �����Ѵ�. (�ǵ尡 �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_Shield_Hit(int damage) { shield -= damage; if (shield < 0) shield = 0; }							// 1 �̻��� �������� ���� ��ŭ �ǵ带 �����Ѵ�. (�ǵ尡 �ּ�ġ�� �Ѿ�� �ʰ� ����ó��)

	void setBoss_Shield_Heal() { shield++; if (shield > 2) shield = 2; }											// �ǵ带 1 �����Ѵ�. (�ǵ尡 �ִ�ġ�� �Ѿ�� �ʰ� ����ó��)
	void setBoss_Shield_Heal(int heal) { shield += heal; if (shield > 2) shield = 2; }								// �޾� �� ��ġ��ŭ �ǵ带 ������Ų��. (�ǵ尡 �ִ�ġ�� �Ѿ�� �ʰ� ����ó��)

	void setBoss_Attack(float _atk) { attack = _atk; if (attack < 0) attack = 0; }									// ������ ���ݷ��� �����Ѵ�. (���ݷ��� 0 ���Ϸ� �������� �ʰ� ����ó��)
	void setBoss_Attack_Plus() { attack++; }																		// ������ ���ݷ��� 1 ������Ų��.
	void setBoss_Attack_Plus(float buff) { attack += buff; }														// ������ ���ݷ��� �ش� ��ġ��ŭ ������Ų��.

	void setBoss_MagicAttack(float _matk) { magicAttack = _matk; if (magicAttack < 0) magicAttack = 0; }			// ������ �������ݷ��� �����Ѵ�. (�������ݷ���0 ���Ϸ� �Ѿ�� �ʰ� ����ó��)
	void setBoss_MagicAttack_Plus() { magicAttack++; }																// ������ �������ݷ��� 1 ������Ų��.
	void setBoss_MagicAttack_Plus(float buff) { magicAttack += buff; }												// ������ �������ݷ��� �ش� ��ġ��ŭ ������Ų��.

	void setBoss_Rect(RECT _rc, int _RECT_SIZEX, int _RECT_SIZEY)													//���� �̹����� ����� ��Ʈ ��ġ�� ���Ѵ�. 
	{
		// ������ �̹����� Ŭ ��츦 ����ؼ� ������ �������� �̹��� ũ�⸸ŭ ���� Top�� ���ߴ�.
		rc = RectMake(_rc.left, (_rc.top + _RECT_SIZEY) - _image->getFrameWidth(), _image->getFrameWidth(), _image->getFrameHeight());
	}

	void setBoss_center(RECT _rc) { center.x = (_rc.left + _rc.right) / 2; center.y = (_rc.top + _rc.bottom) / 2; }	// Ÿ���� ��Ʈ�� �޾ƿ� ������ ���Ѵ�.

	void setBoss_Index(int idx, int idy) { index.x = idx; index.y = idy; }											// Ÿ���� �ε����� �޾ƿ� �����Ѵ�.

	void setBoss_Image(string bossName) { _image = IMAGEMANAGER->findImage(bossName); }								// ������ �̹����� �����Ѵ�.

	void setBoss_Animation(string bossAni) { ani = KEYANIMANAGER->findAnimation(bossAni); }							// ������ �ִϸ��̼��� �ٲ��ش�.

	void setBoss_ClosePlayer(bool close) { isClosePlayer = close; }													// ���� ��ó�� �÷��̾ �ִ��� ������

	void ChangeAni() { isChangeAni = true; }

	void setBoss_Move_Count() { move_Count--; }																		// ������ ���� ī��Ʈ�� ���� ��Ų��.
	void setBoss_Move_Count(int num) { move_Count = num; }

	void setBoss_Direction(BOSS_DIRECTION dir) { direction = dir; }													// ������ ������ �����Ѵ�.

	void setBoss_WorldTime(float wTime) { worldTime = wTime; }														// ���� Ÿ���� �����Ѵ�.

	void setBoss_Move_BoolValue_Ture() { 
		/*isMove = isJump = isChangeAni = true;*/ isMove = isJump = isChangeAni = true;	}									// ���꿡 �ʿ��� bool���� �ѹ��� �����Ѵ�.

	void setBoss_Beat(bool value) { boss_Bool.get_Beat = value; }													// ��Ʈ�� �޾Ҵ��� ������ �����Ѵ�. (������ �ߺ� �޴°��� ���ϱ� ����)

	void setBoss_BaseSkill(string skillName) { attack_Ani = KEYANIMANAGER->findAnimation(skillName); }				// �ش� �ִϸ��̼��� ã�Ƽ� �־��ش�.

	void setBoss_BaseSkill_Image(string skillName) { att_Image = IMAGEMANAGER->findImage(skillName); }

	void setBoss_BaseAttack_Pos(float x, float y) { ani_Center.x = x; ani_Center.y = y; }							// ����Ʈ �ִϸ��̼��� �Ѹ� ��ǥ�� �����Ѵ�.

	void setBoss_Shield_Hit_True() { isShield_Hit = true; }																// �ǵ尡 �ǰ� ���ϸ� true

	void setBoss_Angle(float ang) { angle = ang; }

	void setBoss_SummonSkill(int num) { slave_Summon.rnd = num; }													// �������� �����Ѵ�.

	void setBoss_isCasting(bool value) { isCasting = value; }														// ĳ���� ���� ����

	void setBoss_HP_1() { hp = 1; }

	// ������Ʈ �Լ�
	void Info_Update();																								// ���� ���� �Լ�
	void boss_Move();																								// ���� �̵� ���� �Լ�
	void start_AttackAni() { attack_Ani->start(); }																	// ����Ʈ �ִϸ��̼��� �����Ѵ�.

};

// �������� (inear intetpolation)
// lerp() ���� �Լ�
// lerp(min, max, ����)�� ���ָ� min ~ max ���̿� ���ϴ� ������ ���� ã�� �� �ִ� �Լ�
// ���۰� ���� ���� �˰� ������ �� ������ � ���� ���������� ã�� �� ����
// ���� : (max - min) * ���� + min
// 
// ���� ���� : ���ϰ��� �ϴ� ���� - 1�� �и�� �ΰ� ���ڿ� 1�� �θ� ������ ã�� �� �ִ�.
// 