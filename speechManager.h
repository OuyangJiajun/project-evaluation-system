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

//演讲比赛管理类
class SpeechManager
{
public:

	//构造
	SpeechManager();

	//析构
	~SpeechManager();

	//展示菜单
	void showMenu();

	//退出系统
	void exitSystem();

	//初始化函数
	void initSpeech();

	//创建选手
	void createSpeaker();

	//开始比赛——全流程
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛评分并完成晋级
	void speechContest();

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

	//第一轮选手容器 12人
	vector<int> v1;

	//第二轮选手容器 6人
	vector<int> v2;

	//胜利选手容器 3人
	vector<int> vVictory;

	//存放编号与对应的选手
	map<int, Speaker> m_Speaker;

	//记录比赛轮数
	int m_Index;

	//判断文件是否为空的标志
	bool fileIsEmpty;

	//存放往届记录的容器
	map<int, vector<string>> m_Record;
};