#pragma once
#include "gameNode.h"

class tile : public gameNode
{
private:
	image* _image;		 // �÷��̾� �׽�Ʈ 

	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	//F = G + H
	float _totalCost;		//�� ���
	float _costFromStart;	//������ġ�κ��� ���� ���
	float _costToGoal;		//���� ���κ��� ���������� ��κ��

	bool _isOpen;

	tile* _parentNode;		//���� Ÿ��(�������� ���ǰ��ִ�)

	COLORREF _color;
	HBRUSH _brush;
	HPEN _pen;

	const char* _attribute;	//Ÿ�ϼӼ�

	int _alphaValue;		// ���ĺ��� �� 

public:
	tile();
	~tile();

	HRESULT init(int idX, int idY);
	HRESULT init(const char* imageName, int idX, int idY, int tileWidth, int tileHeight);  // �÷��̾� �׽�Ʈ 
	void release();
	void update();
	void render();
	void render(HDC hdc);  // �÷��̾� �׽�Ʈ ����

	int getIdX() { return _idX; }
	int getIdY() { return _idY; }

	int getAlphaValue() { return _alphaValue; }
	void setAlphaValue(int value) { _alphaValue = value; }

	void setColor(COLORREF color)
	{
		DeleteObject(_brush);
		_color = color;
		_brush = CreateSolidBrush(_color);
	}

	RECT getRect() { return _rc; }

	//================= ������ & ������ ==================

	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	void setAttribute(const char* str) { _attribute = str; }
	const char* getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }




};

