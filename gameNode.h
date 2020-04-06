#pragma once

#include "image.h"

//����۴� ������ �Ѱ��� ������ �Ǵ� �������� �����ô�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

enum CTRL
{
	CTRL_SAVE,			//���̺� ��ư���� ���� ��
	CTRL_LOAD,			//�ε� ��ư���� ���� ��
	CTRL_ITEM, CTRL_STUFF, CTRL_ARMOR, CTRL_WEAPON,
	CTRL_OBJECT,		//������Ʈ���� �׸������� ��ư
	CTRL_MAP, CTRL_TERRAINDRAW, CTRL_TRAP, CTRL_WALLDRAW,		//���� ,����, �� �׸��� ��ư
	CTRL_FLOOR_OBJ,		//�ٴۿ� �ִ� ������Ʈ
	CTRL_CHARACTER,		//�÷��̾� �׸��� ��ư
	CTRL_ERASER,		//���찳 ��ư (�߸����� ������Ʈ���� ��������)
	CTRL_MAP_ERASER, CTRL_WALL_ERASER, CTRL_TRAP_ERASER,
	CTRL_ITEM_ERASER, CTRL_ARMOR_ERASER, CTRL_WEAPON_ERASER,
	CTRL_CHAR_ERASER,		
	CTRL_LOBY, CTRL_STAGE, CTRL_BOSS_STAGE,
	CTRL_EXIT
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	int _crtSelect;  // ���� ����� �� 

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ���� �Լ�
	virtual void render();			//�׸��� ���� �Լ�

	/*virtual void loadSet(STAGE stage, int num);
	virtual void load(char* str, tagTile* _tile);*/

	//������� DC�޸� ���� ������
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

