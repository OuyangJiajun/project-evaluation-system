#include <iostream>
#include "speechManager.h"
#include <map>
using namespace std;


int main()
{
	//创建管理类对象
	SpeechManager sm;
	
	/*测试创建选手
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << "选手编号：" << it->first << "\t选手姓名：" << it->second.m_Name << "\t选手分数：" << "第一轮" << it->second.m_Score[0] << " 第二轮" << it->second.m_Score[1] << endl;;
	}
	*/

	int choice = 0;//存储用户的选项

	while (true)
	{
		sm.showMenu();

		cout << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看记录
			sm.showRecord();
			break;
		case 3://清空记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");//清屏
			break;
		}

		system("cls");
	}

	return 0;
}