#pragma once
#include "stdafx.h"

#define SCREENMOVESPEED 10

// ���� �ȷ�Ʈ 
struct MovePalette
{
	RECT terrainTile;
	RECT wallTile;
	RECT trapTile;
	RECT armorTile;
	RECT weaponTile;
	RECT stuffTile;
	RECT characterTile;
	POINT pos_Start;	// ���콺�� Ŭ���� ���� ��ǥ�� ��Ƶд�.
	POINT pos_End;		// ���콺�� ���� ��ġ ��ǥ�� ��Ƶд�.
	bool isClick;		// ���콺�� �������� �� ��������
	bool choice;		// �׸��� ���ϴ� �̹����� Ŭ�� �ߴ�.
};


struct mousePointRect
{
	RECT mouseRect;		// ���콺 �����Ͱ� ����Ű�� �ִ� Ÿ�� ��Ʈ ������ ��´�.
	int frameX, frameY;	// �̹��� ������ x, y
};


//���� ��Ʈ�� ���缭 Ÿ���� �ٲ�°�
//ü�� ���� ������ �α�
//�̹��� ������ ������ �ϱ�
//