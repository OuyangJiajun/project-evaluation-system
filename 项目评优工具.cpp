#include <iostream>
#include "projectManager.h"
#include <map>
using namespace std;


int main()
{
	//�������������
	ProjectManager pm;
	
	/*���Դ�����Ŀ
	for (map<int, Project>::iterator it = pm.m_Project.begin(); it != pm.m_Project.end(); it++)
	{
		cout << "��Ŀ��ţ�" << it->first << "\t��Ŀ���ƣ�" << it->second.m_Name << "\t��Ŀ������" << "��һ��" << it->second.m_Score[0] << " �ڶ���" << it->second.m_Score[1] << endl;;
	}
	*/

	int choice = 0;//�洢�û���ѡ��

	while (true)
	{
		pm.showMenu();

		cout << "����������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1://��ʼ����
			pm.startEvaluation();
			break;
		case 2://�鿴��¼
			pm.showRecord();
			break;
		case 3://��ռ�¼
			pm.clearRecord();
			break;
		case 0://�˳�ϵͳ
			pm.exitSystem();
			break;
		default:
			system("cls");//����
			break;
		}

		system("cls");
	}

	return 0;
}