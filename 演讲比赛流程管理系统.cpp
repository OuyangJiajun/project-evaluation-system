#include <iostream>
#include "speechManager.h"
#include <map>
using namespace std;


int main()
{
	//�������������
	SpeechManager sm;
	
	/*���Դ���ѡ��
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << it->first << "\tѡ��������" << it->second.m_Name << "\tѡ�ַ�����" << "��һ��" << it->second.m_Score[0] << " �ڶ���" << it->second.m_Score[1] << endl;;
	}
	*/

	int choice = 0;//�洢�û���ѡ��

	while (true)
	{
		sm.showMenu();

		cout << "����������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴��¼
			sm.showRecord();
			break;
		case 3://��ռ�¼
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls");//����
			break;
		}

		system("cls");
	}

	return 0;
}