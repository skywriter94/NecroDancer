#pragma once
#include"animation.h"
#include"gameNode.h"
enum class enemyState
{
	STATE_IDLE,STATE_MOVE,STATE_ATTACK,STATE_DIE
};
enum class Direction
{
	LEFT, RIGHT, UP, DOWN
};
struct EnemyInfo
{
	enemyState state;					//enemy�� ���¸� ������ enum��
	Direction direction;				//enemy�� ������ ������ enum��
	Direction parentDirection;
	Direction AttackDirection;			//
	animation* Animation;	
	image* Image;
	animation* attackAnimation;
	image* attackImage;
	int previousIdx, previousIdy;
	int idx, idy;
	float x, y;	
	float routeX,routeY;
	float angle;
	float worldTimeCount;
	float MoveSpeed;
	RECT rc;
	RECT discoveryRc;					//�÷��̾ �߰��� �ν� ����
	int beatCount;						//
	float HP;
	float damage;
	bool Light;							//�þ� �ȿ� �ִ��� ���θ� �Ǵ��ϱ� ���� bool��
	bool parentLight;			
	bool aniChange;						//�ִϸ��̼��� �ٲ���� �Ǵ��ϱ� ���� bool��
	bool Beat;
	bool Attack;
	bool Move;
	bool left;
	bool right;
	bool up;
	bool down;
	bool object;
	bool correction;
	bool attackEffect;
};
struct playerInfo
{
	float x, y;
	int idx, idy;
};
class Enemy:public gameNode
{
protected:
	EnemyInfo* _enemyInfo;				//���ʹ� ����(����ü)
	playerInfo* _playerInfo;			//���޹޾ƿ� �÷��̾� ����(����ü) (��ǥ���� �޾ƿ�)


	float _time = 0.25;

public:
	Enemy() {};
	~Enemy() {};

	virtual HRESULT init();
	//virtual HRESULT init(int idx, int idy, string enemyName);
	virtual void relase();
	virtual void update();
	virtual void render();

	void AniStart();					//_enemyInfo�� anichange���� true�� �Ǹ� animation�� start()�Լ��� ����
	//�������� ������,��������,�ð��� ��
	virtual float LinearInterpolation(float value1, float value2, float amount);
	virtual void Beat();				//
	virtual void Action();				//enemy�� ���¸� �ٲ��ֱ� ���� �Լ�
	virtual void Idle();
	virtual void Move();				//enemy�� ������ "����"�� ������ �Լ�
	virtual void moveAction();			//�������� enemy�� �������� ������ �Լ�
	virtual void enemyAngle();		
	virtual void HalfMove();			//enemy�� ���� �ε����ų� �÷��̾�� �ε����� ���ݸ� �����̰� ���ڸ��� ���ƿ��� �������� ������ �Լ�
	virtual void AniChange();			//enemy�� �ִϸ��̼��� �ٲ��ֱ� ���� �Լ�(���� update�� �־����� Move�Լ����� direction�� �ٲ� ������ ����)
	virtual void Attack();				//enemy�� ������ ������ �Լ�
	virtual void Die();

	//Enemy���� �Լ�
	virtual void EnemyCreate(float x, float y, float HP,float damage);
	virtual void EnemyCreate(float x, float y, float HP, float damage,Direction direction);
	virtual void EnemyCreate(float x, float y, float HP, float damage, const char* enemyName, const char* enemyAnimation);
	virtual void EnemyCreate(float x, float y, float HP, float damage, const char* enemyName, const char* enemyAnimation,Direction direction);

	virtual void Hit(float damage) { _enemyInfo->HP -= damage; }

	//virtual void wallCheck()

	//Enemy���� ������
	virtual EnemyInfo* getEnemyInfo() { return _enemyInfo; }
	virtual void setPlayerInfo(float x, float y, float idx, float idy) { _playerInfo->idx = idx; _playerInfo->idy = idy; _playerInfo->x = x;_playerInfo->y = y; }

	//enemy move

	


};

