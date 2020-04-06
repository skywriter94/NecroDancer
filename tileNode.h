#pragma once

#define TESTTILEX 30
#define TESTTILEY 30
//=========================================
//�� Ÿ���� ������� 32�� �Ѵ�. 32 X 32
#define TILESIZE 52

//Ÿ�ϼ� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
#define SAMPLETILEX 20
#define SAMPLETILEY 9

//��� �� ���ϴ°͵����ε�, �ݸ����� �� ��Ʃ����� ���ٰ� ī����
//������ �޸� �뷮�� ������ �޸� �Ƴ��ٱ� ���� ����� ��Ʈ�ʵ�

#define ATTR_UNMOVE 0x00000001
#define ATTR_SWAMP  0x00000002
#define ATTR_POISON 0x00000004
#define ATTR_FROZEN 0x00000008

//��������Ʈ�Ҷ� �� �̳����� �Ӽ�ó���ص� �����ҵ�


//���� MAPTOOL

#define TESTTILESIZE 52

//Ÿ�� ������ ���� 100 / ���� 100
#define TILEX 40
#define TILEY 40

//Ÿ�� �� ������� 2080 X 2080
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//���� Ÿ�� �� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
#define TERRAINTILEX 6
#define TERRAINTILEY 6

//�� Ÿ�� �� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
#define WALLTILEX 16
#define WALLTILEY 4

//���� Ÿ�� �� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
#define TRAPTILEX 6
#define TRAPTILEY 7

//������ Ÿ�� �� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
#define ITEMTILEX 4
#define ITEMTILEY 5

//������ Ÿ�� �� ����(Ÿ���� ���� �ȷ�Ʈ ���� ����)
#define CHARACTERTILEX 4
#define CHARACTERTILEY 4

#define ROBYSIZE 40 * 40
#define STAGESIZE 100 * 100
#define BOSSSTAGESIZE 40 * 80

//�̴ϸ� Ÿ�� ������
#define MINTILESIZE 15

enum STAGE
{
	LOBY_STAGE,
	BASIC_STAGE,
	BOSSS_STAGE
};
//����
enum TERRAIN
{
	TR_BASIC_STAGE_TILE, TR_BASIC_COMBO_TILE,
	TR_BOSS_STAGE_TILE, TR_BOSS_COMBO_TILE,
	TR_STAIR, TR_BOSS_STAIR, TR_SHOP,
	TR_NONE,
	TR_END,
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER
};

//�� 
enum WALL
{
	W_WALL, W_ITEM_WALL, W_WALL2, W_SHOP_WALL,		//�⺻ ��, �������� ����ִ� ��, 
	W_END_WALL, W_BOSS_WALL,						//�μ����� �ʴ� ��
	W_DOOR,											//��. ��ġ, �� ���
	W_NONE											//���߿� ����뵵
};

enum TRAP
{
	TRAP_FAST_BEAT, TRAP_SLOW_BEAT, TRAP_MUTE,		//���� ���� ���� �� ���Ұ� ����
	TRAP_LT_JUMP, TRAP_T_JUMP, TRAP_RT_JUMP,		// �밢�� ���� �����¿� ���� ����
	TRAP_L_JUMP, TRAP_R_JUMP,
	TRAP_LB_JUMP, TRAP_B_JUMP, TRAP_RB_JUMP,
	TRAP_CONFUSE,									//ȥ�� ����
	TRAP_BOMB,										//��ź ����
	TRAP_NIDDLE,									//���� ����
	TRAP_SHADOW, TRAP_NIDDLE_SHADOW,				//���� �׸���
	TRAP_NONE
};

//������
enum ARMOR
{
	//��
	A_HELMET, A_SHOVEL,
	A_ARMOR_1, A_ARMOR_2, A_ARMOR_3, A_ARMOR_4,
	A_BOOTS,
	A_RING,
	A_TORCH_1, A_TORCH_2, A_TORCH_3, 
	A_NONE
};
enum WEAPON
{
	//����
	WP_DAGGER_1, WP_DAGGER_2, WP_RAPIER, WP_BROAD_SWORD,
	WP_BOMB, WP_RIFLE, WP_SHOTGUN,
	WP_SPEAR, WP_MACE,WP_LONG_SWORD,
	WP_WHIP, WP_NINETAILS_WHIP,
	WP_BOW, WP_CROSS_BOW,
	WP_NONE
};

enum STUFF
{
	ST_DIAMOND,
	ST_ONE_COIN, ST_ONE_HALF_COIN,
	ST_COINS, ST_MORE_COINS,
	ST_APPLE, ST_CHEESE, ST_MEAT,
	ST_NONE,
};

enum OBJECT
{
	OBJ_WATER,										//�ٴۿ� �ѷ����� ������Ʈ
	OBJ_FALLING_DOOR,								//�������� �ٴ�
};

enum CHARACTER
{
	CHAR_PLAYER, CHAR_SHOPKEEPER,						
	CHAR_BAT, 
	CHAR_SLIME_BLUE, CHAR_SLIME_ORANGE, 
	CHAR_GHOST, CHAR_WRAITH,
	CHAR_SKELETON, CHAR_SKELETON_YELLOW, CHAR_ZOMBIE,
	CHAR_MINO, CHAR_DRAGON, CHAR_BOSS,
	CHAR_NONE,
};

//position
enum POS
{
	POS_PLAYER
};

enum TYPE
{
	TYPE_TERRAIN,
	TYPE_WALL,
	TYPE_TRAP,
	TYPE_ITEM_ARMOR, TYPE_ITEM_WEAPON, TYPE_ITEM_STUFF,
	TYPE_OBJECT,
	TYPE_CHARACTER,
	TYPE_NONE
};

struct tagTile
{
	TYPE type;				//����
	TERRAIN terrain;		//����
	WALL wall;				//��
	TRAP trap;				//����
	ARMOR armor;				//��
	WEAPON weapon;			//����
	OBJECT obj;				//������Ʈ
	CHARACTER character;	//ĳ����
	STUFF stuff;			//����ǰ
	RECT rc;				//��Ʈ
	int terrainFrameX, terrainFrameY;		//�ͷ��� ��ȣ
	int wallFrameX, wallFrameY;				//�� ��ȣ
	int charFrameX, charFrameY;				//ĳ���� ��ȣ
	int	floorObjFrameX, floorObjFrameY;		//�ٴ� ������Ʈ ��ȣ
	int armorFrameX, armorFrameY;			//������(��) ��ȣ
	int weaponFrameX, weaponFrameY;			//������(����) ��ȣ
	int stuffFrameX, stuffFrameY;			//������(����ǰ) ��ȣ
	int characterFrameX, characterFrameY;	//ĳ���� ��ȣ
	int trapFrameX, trapFrameY;				//���� ��ȣ
	
	int alphaValue;			//�þ� �� ���ϱ� ���� ���� ���� ����
	bool alphaEyesight;		//�÷��̾� �þ�
	
	bool isRender;

	int idX;
	int idY;
	POINT XY;
};

//Ÿ�ϼ� 
struct tagSetTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//���� Ÿ�� == ���� Ŭ���� ����Ÿ�� ������ ������ ����ü
struct tagCurrentTile
{
	int x;
	int y;
};

struct tagButton
{
	RECT rc;
	POINT XY;
	bool isClick;
};

struct tagMouse
{
	RECT rc;
	POINT XY;
};

// ���� �߰�
enum EFFECTTYPE
{
	TIMESLOW,// �ð��� ������ �����				// ��    
	SLOW,	 // ������ ���� �ö󰡸鼭 �����		// ������
	STOP,	 // ������ �ڸ����� �����			// ��Ʈ
	FRAMEIMAGE,
};

