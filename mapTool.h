#pragma once
#include "gameNode.h"
#include <string>
#include "mapTool_Library.h"
class mapTool: public gameNode
{

private:
	
	tagCurrentTile  _currentTile;
	tagSetTile		_terrainTile[TERRAINTILEX * TERRAINTILEY];
	tagSetTile		_wallTile[WALLTILEX * WALLTILEY];
	tagSetTile		_trapTile[TRAPTILEX * TRAPTILEY];
	tagSetTile		_armorTile[ITEMTILEX * ITEMTILEY];
	tagSetTile		_weaponTile[ITEMTILEX * ITEMTILEY];
	tagSetTile		_stuffTile[ITEMTILEX * ITEMTILEY];
	tagSetTile		_characterTile[CHARACTERTILEX * CHARACTERTILEY];
	tagTile			_tiles[TILEX * TILEY];

	float _WINSIZEX, _WINSIZEY;
	int _pos[2];

	tagButton _map[9];
	int _mapDirection;
	mousePointRect _mouseEffect;
private:
	tagButton _saveButton;				//����
	tagButton _loadButton;				//�ε�
	tagButton _mapButton;				//��ü �� ����
	tagButton _mapEraseButton;			//��ü �� ���찳
	tagButton _terrainButton;			//����
	tagButton _wallButton;				//��
	tagButton _wallEraseButton;			//�� ���찳
	tagButton _trapButton;				//����
	tagButton _trapEraseButton;			//���� ���찳
	tagButton _itemButton;				//������
	tagButton _itemEraseButton;			//������ ���찳
	tagButton _armorButton;				//��
	tagButton _armorEraseButton;		//�� ���찳
	tagButton _weaponButton;			//����
	tagButton _weaponEraseButton;		//���� ���찳
	tagButton _stuffButton;				//����ǰ
	tagButton _characterButton;			//ĳ����
	tagButton _characterEraseButton;	//ĳ���� ���찳
	tagButton _eraseButton;				//���찳
	tagButton _lobyButton;				//�κ�
	tagButton _stageButton;				//��������
	tagButton _bossButton;				//����

	tagButton _exitButton;				//������
private:
	tagMouse _RectCreate;
	bool _isClick, _isItemButtonClick, _isMapButtonClick;
	bool _isLobyButtonClick, _isStageButtonClick, _isBossButtonClick;
	int _startL, _startT, _endR, _endB;
	RECT _left, _top, _right, _bottom;
	MovePalette _palette;	// â �̵����� ����� ��Ʈ
	tagMouse _mousePoint;
	int alpha;
public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void save();
	virtual void load();
	virtual void clickButton();
	virtual void render();

	void setup();

	virtual void setMap();

	//virtual void clickLeft();

	//� ������ �����ߴ°�?
	TERRAIN terrainSelect(int frameX, int frameY);
	//� ���� �����ߴ°�?
	WALL wallSelect(int frameX, int frameY);
	//� ������ �����ߴ°�?
	TRAP trapSelect(int frameX, int frameY);
	//� �������� �����ߴ°�?
	STUFF stuffSelect(int frameX, int frameY);
	ARMOR armorSelect(int frameX, int frameY);
	WEAPON weaponSelect(int frameX, int frameY);
	//� ĳ������ �����ߴ°�?
	CHARACTER characterSelect(int frameX, int frameY);

	void setS(int num) { _crtSelect = num; }
	void tile_Click();

	void palette_Click();				// ��� �ȷ�Ʈ�� Ŭ���ߴ��� ã���ִ� �Լ�.
	void palette_Click(bool start);		// �ȷ�Ʈ Ŭ�� �� ����� ���� �غ� �Լ�.
	void palette_Rect_Update();			// �ȷ�Ʈ�� ��Ʈ�� �������ִ� �Լ�.
	void palette_Move();				// �ȷ�Ʈ�� �̵� ������ ���ִ� �Լ�.
	void menu_Choice();					// �޴� ���� �Լ�.
	void rectCreate_Update();			// ��Ʈũ������Ʈ ����
	bool using_Palette();				// �ȷ�Ʈ ��� �߿� Ÿ���� ������ �ʰ� �ϴ� �Լ�.
	void mouseRectUpdate();				// ���콺 ��Ʈ ������Ʈ �Լ�.
};

