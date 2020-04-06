#pragma once
#include "singletonBase.h" // Scene���� ���������� ����ؾߵǴϱ� ���ֹ����ʰ� �� �� �ֵ��� �̱����� �����
#include <iostream> // ���� ���� �� �ҷ����⸦ ���� ������ �����
#include <fstream> // ���� ���� �� �ҷ����⸦ ���� ������ �����
#include <string> // ���� ���� �� �ҷ����⸦ ���� ������ �����
#include <vector>
using namespace std;

class gameNode; // ���� ���� ���� ����
class player;
class alphaEffect;

#define WINSIZEX_HALF WINSIZEX / 2	// ������ ���� ������ ����
#define NOTE_INTERVAL WINSIZEX_HALF / 3 // ��Ʈ ���� ����
#define NOTE_RADIUS_X 6 // ��Ʈ �ϳ��� ���� ������ ����
#define HEARTFRAME_RATE 3 // ���� �ڵ� ������ ���� �ð�


enum tagStage // �׽�Ʈ������ ������ Scene����
{
	STAGE_TITILE,
	STAGE_LOBBY,
	STAGE_1_1,
	STAGE_1_2,
	STAGE_1_3,
	BOSS
};

struct tagPlayOnceSound // �ݺ� ����Ǵ� �� �ȿ� �ִ� ��쿡 ���
{
	string soundKeyName;
	float volume;
	bool isPlayAgain;
};

struct tagNote // ��Ʈ ����ü
{
	RECT rc;
	POINTFLOAT pos;
	float speed;
	image* img;
	bool isCol; // ���� �ڵ� �ִϸ��̼� �ߺ� ������ ���� bool
	bool isRender;
	bool colision;// ���� �߰� 
	int alpha;
};



class Beat : public singletonBase<Beat> // �̱��� ��ӹޱ�
{
private:
	tagStage _currentStage; // ���� ��������
	string _oldSongName, _oldShopKeeper, _currentSongName, _currentShopkeeper; // ���� �� Ű���� �������� Ű �� & ���� �� Ű���� �������� Ű ��
	string _noteFileName; // ��Ʈ ���� ����(ms)�� �ҷ����� ���� ��θ�
	bool _loopSong; // �ݺ������� �ƴ��� �Ǻ��ϴ� bool

	vector<int> _vMsTimeInfo; // ��Ʈ ������ ���� ���Ͽ��� �и������� ������ ���� ����
	vector<tagNote> _vNoteLeft; // ���ʿ��� ������ ��Ʈ
	vector<tagNote> _vNoteRight; // �����ʿ��� ������ ��Ʈ
	int _countNote; // ������� ��Ʈ�� � ������ ���� ���� ����

	int _oldStageID, _currentStageID; // ���� ���������� ���� �������� ��
	unsigned int _songPos; // ���� ���� ����ð�(ms) 
	unsigned int _songLength;  // FMOD::SOUND�� getLength()�Լ��� �������� ������� �Ф�... getLength() �Լ��� ����Ͽ� ���� ���̸� ���� �� �ְ� ���� ����

	float _deltaTime;	// TIMEMANAGER���� getElapsedTime()�� �Ź� ���� �ٲ�� ���� ȣ���ϱ� ����� ������ ���� ���۵Ǳ� ��, �� ���� getElapsedTime()ȣ���ϰ� �� ���� �����ϴ� �뵵�� ����
	float _songLeftTime; // ���� ���� ���� �ð�
	float _pitch; // ���� ���� pitch�� (1�� �⺻ ��, 1�̸� �� ���� ������, 1�̻� �� ������)
	float _pitchTemp;

	RECT heartRC, heartSmallRC, shopKeeperRC, test_Player, test_slowPlatform, test_fastPlatform; // RECT��(����, ���� ����� ���� ���� ��Ʈ(������ ������), �÷��̾�, �������� ����, �������� ����)
	POINTFLOAT playerPos, test_SlowPlatformPos, test_FastPlatformPos; // X,Y��ǥ��(���� ����, �÷��̾�, �������� ����, �������� ����)
	POINT shopKeeperPos, shopKeeperID;
	bool isFindPlayerPos;
	bool isFindShopkeeperPos;

	image* heartImg; // ���� �̹���
	int heartFrameCount; // ���� ���� ������
	bool _isBeating; // ���� �ڵ��� �־��� �ð� ���ݸ��� �ѹ� ���� �αٰŸ��� ���� bool

	float noteTimeInterval;
	float noteTimeIntervalCount;
	float inputIntervalCount;
	bool Interval;
	player* _player;
	bool _effect;

	int musicID; // ������ �ε����� �����ִ� ����
	int musicID_Temp;
	bool _tileOnOff; // Ÿ���� 

private:
	void init_AddSoundAndImg(); // ���� & �̹��� �߰�
	void init_SetObjs(); // Beat Ŭ������ �ִ� ���� ������Ʈ ������ �ʱ�ȭ

	void update_SetSceneMusic(); // Scene������ �޾ƿ� �Լ�
	void update_PlayerMoveTest(); // �׽�Ʈ�� �÷��̾�
	void update_SongAndNoteControl(); // ��� ��Ʈ�� �����ϴ� �Լ�
	void update_BeatEffect(); // ���� �ڵ� �� �ٲ��� �̹����� ȿ����
	void update_SoundDistanceControl(); // ���� �����̳� ���� ��� �Ÿ��� ���� �Ҹ��� ũ�⸦ �������ִ� �Լ�
	void update_PitchControl(); // ���� �ӵ��� �����ϴ� �Լ�

	void render_DebugLog(HDC getMemDC); // ����� ���� �Լ�


private:
	void Load(); // ��Ʈ ���� �ε� �Լ�
	void CreateNewNote(bool dirRight); // �� ���� ������ ��Ʈ�� ��ġ�ϴ� �Լ�. bool�� ���������� ������ ������ �ƴ��� �Ǻ�.
	void CreateNewNoteWhilePlay(bool dirRight); // �� �����ϰ� �÷��� �߿� ��Ʈ�� ��ġ�ϴ� �Լ�. bool�� ���������� ������ ������ �ƴ��� �Ǻ�.
	float GetSongVariousTime(unsigned int playTime, unsigned int songLength); // �� ��� ��Ʈ ��� ���� Ư�� ����(Ư�� �ð�)�� �̾ƿ��� ���� ���� �Լ�
	void Move();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool getBeating() { return _isBeating; }
	void setPlayerAddressLink(player* player) { _player = player; }

	void HitNoteEffect(float x, float y);
	bool getInterval() { return  Interval; }
	float getHeartMiddle() { return (heartRC.left + heartRC.right) / 2; }
	//float lerp(float start, float end, float timeAmount) { return float(start + ((float)(end - start) * timeAmount)); }
	float lerp(float start, float end, float timeAmount) { return (float)((end - start) * timeAmount); }

	void SetMusicID(int _musicID) { musicID = _musicID; } // ���� �ε����� ���� �������ִ� setter! (id --> <1 = �κ�>,  <2 = �������� 1_1>,  <3 = �������� 1_2>, <4 = �������� 1_3>, <5 = ����>) 
	int GetMusicID() { return musicID; } // ���� �ε����� �������� getter

	bool getTurnOnOff() { return _tileOnOff; }
	void AllStopMusic();

	void Set_PlayerPos(POINTFLOAT _playerPos) { playerPos = _playerPos; }
	void Set_ShopkeeperPos(POINT _shopkeeperPos) { shopKeeperPos = _shopkeeperPos; }
	POINT Get_ShopkeeperPos() { return shopKeeperPos; }

	void Set_ShopkeeperID(POINT _shopKeeperID) { shopKeeperID = _shopKeeperID; }
	POINT Get_ShopkeeperID() { return shopKeeperID; }

	void Set_FindShopkeeperPos(bool isFind) { isFindShopkeeperPos = isFind; }
	bool Get_FindShopkeeperPos() { return isFindShopkeeperPos; }
};