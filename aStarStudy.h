#pragma once
#include "gameNode.h"
#include <vector>
#define MAX_X 500
#define MAX_Y 500
enum class NODESTATE
{
	NODE_START,
	NODE_END,
	NODE_EMPTY
};
class node
{
	//���̽�Ÿ���� ����ؾ� �� 2����
	//1. ���(F, G, H)
	//2. �θ��� ������(��������� ������)
public:
	RECT rc;				//��Ʈ
	int idx, idy;			//�ε��� x, y
	int F, G, H;			//F = G + H //G = ���� to ���� //H = ���� to ����
	node* parentNode;		//�θ� ����ų ���(�������)
	NODESTATE nodeState;	//����� ����(����, ����, ��, ����)
	//��� ������
	node() {}
	//������ �����ε��� ���� �ʱ�ȭ
	node(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		F = G = H = 0;
		nodeState = NODESTATE::NODE_EMPTY;
		parentNode = NULL;
	}
};
class aStarStudy:public gameNode
{
private:
	node* _totalNode[MAX_X][MAX_Y];
	node* _startNode;
	node* _endNode;
	node* _curNode;

	vector<node*> _openList;
	vector<node*> _closeList;
	vector<node*> _finalList;

	int _count;
	bool _isFind;

public:
	HRESULT init();
	void release();
	void update();

	void setStart(int idx, int idy);
	void setEnd(int idx, int idy);

	/*�߿��Լ�*/
	//��ã�� �Լ�
	void pathFinding();
	//���¸���Ʈ�� �߰� �Լ�
	void addOpenList(int idx, int idy);
	//���¸���Ʈ ����
	void delOpenList(int index);

	vector<node*> getFinalList() { return _finalList; }

	aStarStudy() : _startNode(NULL), _endNode(NULL) {}
	~aStarStudy() {}
};

