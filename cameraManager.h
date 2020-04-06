#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	RECT  _cameraRect;							// ������ RECT   
	float _cameraWorldSizeX, _cameraWorldSizeY; // ī�޶� ����� 
	float _cameraSizeX, _cameraSizeY;			// ī�޶� ũ�� 
	float _cameraX, _cameraY;					// ī�޶� ��ǥ 

	float _cameraMapFullTileSizeX, _cameraMapFullTileSizeY; //���� �ִ� ������
	float _cameraMapTileSizeX, _cameraMapTileSizeY;			//���� ũ��
	float _cameraMapSizeX, _cameraMapSizeY;					//���� ��ǥ			

	HDC _worldDC;
	image* _worldImage;

	//HDC _mapToolDC;
	//image* _mapToolImage;

	bool _isCameraMoveX;
	bool _isCameraMoveY;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// ī�޶� ������ 
	void set_CameraSize(float x, float y);
	float get_CameraSize_X() { return _cameraSizeX; }
	float get_CameraSize_Y() { return _cameraSizeY; }

	// ī�޶��� ��ǥ 
	void set_CameraXY(int x, int y);
	void set_CameraXY(float x, float y, bool fast = FALSE);
	void set_CameraXY(POINT xy);
	void set_CameraXY(RECT rc);

	float get_CameraX() { return _cameraX; }
	float get_CameraY() { return _cameraY; }

	//ī�޶� �� ������ ������ ���ϰ� 
	void Camera_Correction();
	void Camera_Move();
	// ���� DC
	HDC getWorldDC() { return _worldDC; }
	image* getWorldImage() { return _worldImage; }
	// ���� DC
	/*HDC getmapToolDC() { return _mapToolDC; }
	image* getmapToolImage() { return _mapToolImage; }*/
	
	// ���� ������
	void set_CameraMapTielSize(float x, float y);
	float get_CameraMapTileSize_X() { return _cameraMapTileSizeX; }
	float get_CameraMapTileSize_Y() { return _cameraMapTileSizeY; }

	// ���� ��ǥ
	void set_CameraMapTool_XY(int x, int y);
	void set_CameraMapTool_XY(float x, float y);
	void set_CameraMapTool_XY(POINT xy);
	void set_CameraMapTool_XY(RECT rc);

	float get_CameraMapSize_X() { return _cameraMapSizeX; }
	float get_CameraMapSize_Y() { return _cameraMapSizeY; }

	void CameraMapTool_Correction();
	void CameraMapTool_Move();

	//ī�޶� ��鸮�º��� 
	void Camera_WorldDC_Shake();
	RECT getCamera_Rect() { return _cameraRect; }
	void set_CameraPos_Update(float x, float y);

};

