#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);
	//���� �ȷ�Ʈ Ʋ
	IMAGEMANAGER->addImage("terrainPalette", "./image/mapTool/icon/toolbar.bmp", 360, 360, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wallPalette", "./image/mapTool/icon/walltoolbar.bmp", 884, 468, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("trapPalette", "./image/mapTool/icon/traptoolbar.bmp", 364, 416, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("itemPalette", "./image/mapTool/icon/itemtoolbar.bmp", 260, 312, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("left", "./image/mapTool/icon/left.bmp", 25, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("right", "./image/mapTool/icon/right.bmp", 25, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("top", "./image/mapTool/icon/top.bmp", 1800, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bottom", "./image/mapTool/icon/bottom.bmp", 1800, 25, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("save", "./image/mapTool/icon/i_save.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("load", "./image/mapTool/icon/i_load.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item", "./image/mapTool/icon/i_item.bmp", 72, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("armor", "./image/mapTool/icon/i_armor.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("weapon", "./image/mapTool/icon/i_weapon.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("terrain", "./image/mapTool/icon/i_terrain.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("trap", "./image/mapTool/icon/i_trap.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wall", "./image/mapTool/icon/i_wall.bmp", 52, 52, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("eraser", "./image/mapTool/icon/i_eraser.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tr_eraser", "./image/mapTool/icon/i_terrain_E.bmp", 38, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("trap_eraser", "./image/mapTool/icon/i_trap_E.bmp", 38, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("w_eraser", "./image/mapTool/icon/i_wall_E.bmp", 38, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("s_eraser", "./image/mapTool/icon/i_stuff_E.bmp", 38, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("a_eraser", "./image/mapTool/icon/i_armor_E.bmp", 38, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wp_eraser", "./image/mapTool/icon/i_weapon_E.bmp", 38, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("char_eraser", "./image/mapTool/icon/i_char_E.bmp", 38, 43, true, RGB(255, 0, 255));
	

	IMAGEMANAGER->addImage("exit", "./image/mapTool/icon/i_exit.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stuff", "./image/mapTool/icon/i_stuff.bmp", 52, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("map", "./image/mapTool/icon/i_map.bmp", 72, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("character", "./image/mapTool/icon/i_char.bmp", 72, 72, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("loby", "./image/mapTool/icon/loby.bmp", 100, 27, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("stage", "./image/mapTool/icon/stage.bmp", 100, 27, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("boss", "./image/mapTool/icon/boss.bmp", 100, 27, true, RGB(255, 0, 255), true);


	//�ȷ�Ʈ�� ���� �̹�����
	IMAGEMANAGER->addFrameImage("terrainTiles", "./image/mapTool/terrain/tile.bmp", 312, 312, TERRAINTILEX, TERRAINTILEY, true, RGB(255, 0, 255),true);
	IMAGEMANAGER->addFrameImage("wallTiles", "./image/mapTool/wall/wall.bmp", 832, 416, WALLTILEX, WALLTILEY, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("trapTiles", "./image/mapTool/trap/trap.bmp", 312, 364, TRAPTILEX, TRAPTILEY, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("armorTiles", "./image/mapTool/item/passive.bmp", 208, 260, ITEMTILEX, ITEMTILEY, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("weaponTiles", "./image/mapTool/item/weapon.bmp", 208, 260, ITEMTILEX, ITEMTILEY, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("stuffTiles", "./image/mapTool/item/stuff.bmp", 208, 260, ITEMTILEX, ITEMTILEY, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("characterTiles", "./image/mapTool/char/character.bmp", 208, 260, ITEMTILEX, ITEMTILEY, true, RGB(255, 0, 255));

	_sm = new scene_Manager;
	_sm->init();

	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();
	_sm->release();
}


void playGround::update()
{
	gameNode::update();
	_sm->update();
}



void playGround::render()
{
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY, BLACKNESS);
	//PatBlt(CAMERAMANAGER->getmapToolDC(), CAMERAMANAGER->get_CameraMapSize_X(), CAMERAMANAGER->get_CameraMapSize_Y(), WINSIZEX, WINSIZEY, BLACKNESS);

	//===========================================================
	
	_sm->render();

	//TIMEMANAGER->render(getMemDC());

	//===========================================================
	if (!SCENEMANAGER->getVideoPlay()) _backBuffer->render(getHDC(), 0, 0);

}
