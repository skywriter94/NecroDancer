#include "stdafx.h"
#include "video.h"

video::video()
{
}

video::~video()
{
}

HRESULT video::init(const char* videoName, bool ending)
{
	if (ending)
	{
		cv::namedWindow(WINNAME);
		HWND cvWnd = (HWND)cvGetWindowHandle(WINNAME);
		if (!cvWnd) return false;
		HWND oldParent = ::GetParent(cvWnd);
		::SetParent(cvWnd, oldParent);
		//::ShowWindow(oldParent, SW_HIDE);
		// resizeWindow(WINNAME, WINSIZEX + 100, WINSIZEY+ 50); //������ ũ��� �ȉ� 
		moveWindow(WINNAME, -74, -120);		// �̵���Ű�� 
		::SetParent(oldParent, _hWnd);
	}
	//ShowWindow(_hWnd, NULL);

	SCENEMANAGER->setVideoPlay(true); // ������ �÷��� �ϴϱ� �÷��� true�� 
	_aviName = videoName;
	cap.open(videoName);		// ���� Name�� ��� 

	if (!cap.isOpened())	// ���� ������ �ƴϸ� ���� �޽����� ��� 
	{
		MessageBox(NULL, "�������� ���� �����ϴ�.", "���� �޽���", MB_OK);		// �޽��� ��� 
		SCENEMANAGER->setVideoPlay(false);
		SCENEMANAGER->changeScene("Stage");									// Ȥ�� �𸣴� ���������� 
	}
	_play = true;	// BOOL �� ����
	return S_OK;
}

void video::release()
{
}

void video::update()
{
}

void video::render()
{
	// �ʱⰪ�� ���� 
	if (_play)
	{
		//
		if (cap.isOpened())
		{
			Mat frame;			     // opencv���� ����ϴ� ����ü  
			frame.setTo(Scalar(0));	 // �ʱⰪ �ʱ�ȭ 
			cap >> frame;			 // cap(����������) -> frame�̶�� ����ü�� �ִ´�.		
			double fps = cap.get(CAP_PROP_FPS);
			int delay = cvRound(1000 / fps);
			//if (cap.get(CAP_PROP_POS_FRAMES) == cap.get(CAP_PROP_FRAME_COUNT)) ( ���� ������ == �ִ� ������ )  // ���߿� ������ ������ �ּ�ó�� 
			// ���� �������� ��������� 
			if (frame.empty())
			{
				_play = false;
				SCENEMANAGER->setVideoPlay(false);  // �� �Ŵ����� ���� ���� �������� 
				cap.release();
				frame.release();
				destroyAllWindows();	// opencv â���� 
				// ��Ʈ�� �̸� 
				if (_aviName == "intro.avi")
				{
					// �ε������� ����
					//BEATMANAGER->AllStopMusic();
					//SOUNDMANAGER->play("Intro");
					SCENEMANAGER->changeScene("Loading");
				}
				else // endScene�̸� ����������  
				{
					SCENEMANAGER->changeScene("Stage");
				}
				return;
			}
			Mat edges;
			// ���������� �ε������� 
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_play = false;
				SCENEMANAGER->setVideoPlay(false); // �� �Ŵ����� ���� ���� �������� 
				cap.release();
				frame.release();
				destroyAllWindows();			// opencv â���� 
				if (_aviName == "intro.avi")
				{
					//�ε�������
					//BEATMANAGER->AllStopMusic();
					//SOUNDMANAGER->play("Intro");
					SCENEMANAGER->changeScene("Loading");
				}
				else // endScene�̸� ����������  
				{
					SCENEMANAGER->changeScene("Stage");
				}
				return;
			}
			imshow(WINNAME, frame);  // ������â�� �������� ���� -> ������ �������� ���� �ڵ� 
			waitKey(delay);
		}
	}

}

// ���߿� Ȥ�ó� ���ϼ� ������ �����ص� 
void video::videoRecord()
{
	//	double fps = 15;
	//
	//	int fourcc = CV_FOURCC('X', 'V', 'I', 'D'); // codec
	//
	//	bool isColor = true;
	//
	//
	//
	//	VideoWriter* video = new VideoWriter;
	//
	//	if (!video->open("result.avi", fourcc, fps, Size(img_w, img_h), isColor)) {
	//
	//		delete video;
	//
	//		return;
	//
	//	}
	//
	//
	//
	//	Mat img;
	//
	//	while (1) {
	//
	//		// ...
	//
	//		*video << img;
	//
	//		// ...
	//
	//	}
	//
	//	delete video;
	//
	//
	//
	//��ó: https://jangjy.tistory.com/21 [��ٺ���..]
}

void video::setPlay()
{
	_play = true;
}

void video::setStop()
{
	_play = false;
}

