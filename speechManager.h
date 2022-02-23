#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <fstream>
#include "speaker.h"
using namespace std;

//�ݽ�����������
class SpeechManager
{
public:

	//����
	SpeechManager();

	//����
	~SpeechManager();

	//չʾ�˵�
	void showMenu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ������
	void initSpeech();

	//����ѡ��
	void createSpeaker();

	//��ʼ��������ȫ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//�������ֲ���ɽ���
	void speechContest();

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

	//��һ��ѡ������ 12��
	vector<int> v1;

	//�ڶ���ѡ������ 6��
	vector<int> v2;

	//ʤ��ѡ������ 3��
	vector<int> vVictory;

	//��ű�����Ӧ��ѡ��
	map<int, Speaker> m_Speaker;

	//��¼��������
	int m_Index;

	//�ж��ļ��Ƿ�Ϊ�յı�־
	bool fileIsEmpty;

	//��������¼������
	map<int, vector<string>> m_Record;
};