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

//项目评优管理类
class ProjectManager
{
public:

	//构造
	ProjectManager();

	//析构
	~ProjectManager();

	//展示菜单
	void showMenu();

	//退出系统
	void exitSystem();

	//初始化函数
	void initEvaluation();

	//创建项目
	void createProject();

	//开始评优——全流程
	void startEvaluation();

	//抽签
	void evaluationDraw();

	//评分并完成晋级
	void evaluationContest();

	//显示晋级结果并改为第二轮
	void showResult();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届得分
	void showRecord();

	//清空记录
	void clearRecord();

	//第一轮项目容器 12
	vector<int> v1;

	//第二轮项目容器 6
	vector<int> v2;

	//获胜项目容器 3
	vector<int> vVictory;

	//存放编号与对应的项目
	map<int, Project> m_Project;

	//记录评优轮数
	int m_Index;

	//判断文件是否为空的标志
	bool fileIsEmpty;

	//存放往届记录的容器
	map<int, vector<string>> m_Record;
};