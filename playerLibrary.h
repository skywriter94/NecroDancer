#pragma once

class EnemyManager;
class Enemy;
class deathMetal;
class slave;

enum NOWSTAGE // ���������� ��Ÿ�� 
{
	NOWSTAGE_STAGE,
	NOWSTAGE_BOSS
};

enum PLAYERDIRECTION			// �÷��̾��� ����
{
	PLAYERDIRECTION_RIGHT,
	PLAYERDIRECTION_DOWN,
	PLAYERDIRECTION_LEFT,
	PLAYERDIRECTION_UP,		
};

enum PLAYERWAEPON				// �÷��̾��� ����
{
	PLAYERWAEPON_NONE,			// �������
	PLAYERWAEPON_DAGGER,		// �ܰ�
	PLAYERWAEPON_SPEAR,			// �ս��Ǿ�
	PLAYERWAEPON_RAPIER,		// �����Ǿ�
	PLAYERWAEPON_LONGSWORD,		// �ռҵ�
	PLAYERWAEPON_BROADSWORD,	// ��ε�ҵ�
};

struct tagPlayer				//�÷��̾��� ����
{
	PLAYERDIRECTION direction;	// ����   
	PLAYERWAEPON weapon;		// ���� 
	animation* headAni;			// �Ӹ� �ִϸ��̼�
	animation* bodyAni;			// ��   �ִϸ��̼� 
	image* headImage;			//	    �̹��� 
	image* bodyImage;			//      �̹��� 
	RECT rc;					// RECT
	float x, y;					// ��ǥ ��(X,Y)  
	float maxHp;				// �ִ� HP
	float hp;					// hp
	float guard;				// ���
	int idx, idy;				// �ε��� (idx,idy)
	int sight;					// �þ߰�
	int damage;					// ���ݷ� 
	int score;					// ����
	int coin;					// ��
	int diamond;				// ���̾� 
	bool isWeapon;				// �������� ��� �ִ� Bool ��  
	bool isArmor;				// ��
	bool potion;				// ����
	bool torch;					// Ƚ�� 
};

struct tagItem			// ������
{
	TYPE type;			// Ÿ�� 
	WEAPON weapon;		// ���� Ÿ��
	ARMOR armor;		// �� Ÿ��
	STUFF stuff;		// �Ҹ�ǰ Ÿ��
	int frameX;			//������ ��ȣ
	int frameY;			//������ ��ȣ
	int sight;			// �þ߰�
	int damege;			// ���ݷ�
	float guard;		// ���� 
	float hp;			// ü�� 
};