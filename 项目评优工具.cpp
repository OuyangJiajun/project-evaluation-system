#include <iostream>
#include "projectManager.h"
#include <map>
using namespace std;


int main()
{
	//创建管理类对象
	ProjectManager pm;
	
	/*测试创建项目
	for (map<int, Project>::iterator it = pm.m_Project.begin(); it != pm.m_Project.end(); it++)
	{
		cout << "项目编号：" << it->first << "\t项目名称：" << it->second.m_Name << "\t项目分数：" << "第一轮" << it->second.m_Score[0] << " 第二轮" << it->second.m_Score[1] << endl;;
	}
	*/

	int choice = 0;//存储用户的选项

	while (true)
	{
		pm.showMenu();

		cout << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1://开始评优
			pm.startEvaluation();
			break;
		case 2://查看记录
			pm.showRecord();
			break;
		case 3://清空记录
			pm.clearRecord();
			break;
		case 0://退出系统
			pm.exitSystem();
			break;
		default:
			system("cls");//清屏
			break;
		}

		system("cls");
	}

	return 0;
}