#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <fstream>
#include "project.h"
using namespace std;

//��Ŀ���Ź�����
class ProjectManager
{
public:

	//����
	ProjectManager();

	//����
	~ProjectManager();

	//չʾ�˵�
	void showMenu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ������
	void initEvaluation();

	//������Ŀ
	void createProject();

	//��ʼ���š���ȫ����
	void startEvaluation();

	//��ǩ
	void evaluationDraw();

	//���ֲ���ɽ���
	void evaluationContest();

	//��ʾ�����������Ϊ�ڶ���
	void showResult();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ����÷�
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//��һ����Ŀ���� 12
	vector<int> v1;

	//�ڶ�����Ŀ���� 6
	vector<int> v2;

	//��ʤ��Ŀ���� 3
	vector<int> vVictory;

	//��ű�����Ӧ����Ŀ
	map<int, Project> m_Project;

	//��¼��������
	int m_Index;

	//�ж��ļ��Ƿ�Ϊ�յı�־
	bool fileIsEmpty;

	//��������¼������
	map<int, vector<string>> m_Record;
};