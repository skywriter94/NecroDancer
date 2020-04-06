#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
{
}


soundManager::~soundManager()
{

}

HRESULT soundManager::init()
{
	//FMOD ���忣�� ����Ϸ��� �ʱ�ȭ
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound * [TOTALSOUNDBUFFER];
	_channel = new Channel * [TOTALSOUNDBUFFER];

	ZeroMemory(_sound, sizeof(_sound));
	ZeroMemory(_channel, sizeof(_channel));



	//�����ͱ׷� �߰��� ��� ������ ��������
	_system->getMasterChannelGroup(&_masterGroup);

	//�����ͻ���׷� �߰�
	_system->getMasterSoundGroup(&_masterSound);

	//����Ʈ ���� �׷�
	_system->createChannelGroup("channelEffect", &_effectGroup);

	//BGM �뷡 �׷�
	_system->createChannelGroup("channelMusic", &_musicGroup);
	_system->createSoundGroup("soundMusic", &_musicSound);




	return S_OK;

}

void soundManager::release()
{
	if (*_channel != NULL || *_sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; ++i)
		{
			if (_channel != NULL)
			{
				if (_channel[i])_channel[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound[i] != NULL) _sound[i]->release();
			}
		}
	}

	//�޸� �����ش�
	//�迭�̹Ƿ�
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//���������� FMOD ���� �ý��� �ݾ���
	if (_system != NULL)
	{
		_system->release();
		_system->close();		//�˴� �����ϴ�
	}
}

void soundManager::update()
{
	_system->update();
}



//���� �߰� �Լ�
void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}

	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}

	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));

}




//						Ű��,			����			  BGM = ture,  Effect = false
void soundManager::play(string keyName, float volume, bool isMusic)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	//�迭 �� ���°���� ���˸������� ī��Ʈ ����
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(*iter->second, 0, false, &_channel[count]);
			_channel[count]->setLoopPoints(0, FMOD_TIMEUNIT_MS, 0, FMOD_TIMEUNIT_MS);

			_channel[count]->setVolume(volume);

			if (isMusic)
			{
				_channel[count]->setChannelGroup(_musicGroup);
			}
			else if (!isMusic)
			{
				_channel[count]->setChannelGroup(_effectGroup);
			}

			break;
		}
	}
}


void soundManager::stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();
	//�迭 �� ���°���� ���˸������� ī��Ʈ ����
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}




void soundManager::pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

unsigned int soundManager::getSongPosition(string keyName, unsigned int& pos)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&pos, FMOD_TIMEUNIT_MS);
			break;
		}
	}
	return pos;
}

float soundManager::getPitch(string keyName, float& pitch)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPitch(&pitch);
			break;
		}
	}
	return pitch;
}

void soundManager::setVolume(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::setPitch(string keyName, float pitch)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPitch(pitch);
			break;
		}
	}
}


bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;

	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;

	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}