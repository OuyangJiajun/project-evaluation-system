#include "speechManager.h"

SpeechManager::SpeechManager()
{
	initSpeech();
	createSpeaker();
	loadRecord();
}

SpeechManager::~SpeechManager()
{
	
}

void SpeechManager::showMenu()
{
	cout << "*************************************" << endl;
	cout << "**********欢迎参加演讲比赛****** ****" << endl;
	cout << "***********1.开始演讲比赛******* ****" << endl;
	cout << "***********2.查看往届记录************" << endl;
	cout << "***********3.清空比赛记录************" << endl;
	cout << "***********0.退出比赛程序************" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	v1.clear();
	v2.clear();
	vVictory.clear();
	m_Speaker.clear();
	m_Index = 1;
	m_Record.clear();
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		//姓名
		string name = "选手";
		name += nameSeed[i];

		//speaker初始化姓名与分数
		Speaker sp;
		sp.m_Name = name;
		sp.m_Score[0] = 0;
		sp.m_Score[1] = 0;

		//初始化vector和map
		v1.push_back(i + 10001);
		m_Speaker.insert(pair<int, Speaker>(i + 10001,sp));
	}
}

void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1.抽签
	speechDraw();
	
	//2.比赛
	speechContest();

	//3.显示晋级结果
	showResult();

	//第二轮比赛
	//1.抽签
	speechDraw();

	//2.比赛
	speechContest();

	//3.显示最终结果
	showResult();

	//4.保存分数
	saveRecord();

	//重新初始化
	initSpeech();
	createSpeaker();
	loadRecord();
}

void SpeechManager::speechDraw()
{
	cout << "第" << m_Index << "轮选手正在抽签" << endl;
	if (m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	system("pause");
}

void SpeechManager::speechContest()
{
	srand((unsigned int)time(NULL));
	cout << "第" << m_Index << "轮比赛正式开始" << endl;

	vector<int> v_Src; //优化：新建了一个v_Src，第一轮 = v1，第二轮 = v2。其余的打分晋级代码通用
	if (m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//六进三时用
	//优化：%6的循环写法，实现一二轮通用的六进三
	int count = 0;//记录当前录入的人数
	//修正错误：改用multimap防止同分数时后面的插入失败
	//优化：添加greater<double>()使得从大到小排
	multimap<double, int, greater<double>> groupScore;//记录分数和编号

	//给所有比赛选手打分，分数放入维护的m_Speaker
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		deque<double> d;//优化：改成了deque容器，然后用sort算法，可以更方便的去除做高分最低分
		for (int i = 0; i < 10; i++)
		{
			d.push_back((rand() % 401 + 600) / 10.f);//优化：从整数评分改成小数评分不容易重复   （rand()%401+600）/10.f    即600~1000除10，由此带上了小数
		}
		//去掉最低分和最高分
		sort(d.begin(), d.end());
		d.pop_back();
		d.pop_front();
		//平均分即该选手得分
		double sum = accumulate(d.begin(),d.end(),0.0f);//优化：改用了STL的accumulate算法
		double avg= sum / d.size();
		m_Speaker[*it].m_Score[m_Index-1] = avg;//优化：取消通过m_Index-1判断轮数，直接用m_Index-1赋值
		groupScore.insert(pair<double, int>(avg, *it));
		count++;//人数+1

		if (count % 6 == 0)//满六个
		{
			//输出分数排名
			cout << "第" << count / 6 << "组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it= groupScore.begin();it!=groupScore.end();it++)
			{
				cout << "选手编号：" << (*it).second << "\t姓名：" << m_Speaker[(*it).second].m_Name << "\t分数：" << m_Speaker[(*it).second].m_Score[m_Index-1] << endl;
			}
			//实现晋级
			int num = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && num < 3; it++, num++)
			{
				if (m_Index == 1)
				{
					v2.push_back(it->second);
				}
				else
				{
					vVictory.push_back(it->second);
				}
			}
			//清空map
			groupScore.clear();
		}
	}
}

void SpeechManager::showResult()
{
	cout << "第" << m_Index << "轮晋级选手" << endl;
	if (m_Index == 1)//显示第一轮晋级结果
	{
		int i = 0;
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++, i++)
		{
			if (i < 3)
			{
				if(i==0)cout << "第一组晋级选手：" << endl;
				cout << "选手编号：" << *it << "\t选手姓名：" << (m_Speaker.find(*it))->second.m_Name << "\t选手得分：" << (m_Speaker.find(*it))->second.m_Score[0] << endl;
			}
			else
			{
				if(i==3)cout << "第二组晋级选手：" << endl;
				cout << "选手编号：" << *it << "\t选手姓名：" << (m_Speaker.find(*it))->second.m_Name << "\t选手得分：" << (m_Speaker.find(*it))->second.m_Score[0] << endl;
			}
		}
		m_Index = 2;
	}
	else//显示第二轮最终结果
	{
		for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
		{
			cout << "选手编号：" << *it << "\t选手姓名：" << (m_Speaker.find(*it))->second.m_Name << "\t选手得分：" << (m_Speaker.find(*it))->second.m_Score[1] << endl;
		}
	}
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv",ios::out|ios::app);//csv以逗号分隔
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "文件记录已保存" << endl;
	system("pause");
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
	//文件不存在的情况
	if (!ifs.is_open())
	{
		fileIsEmpty = true;
		ifs.close();
		return;
	}

	//空文件情况
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	fileIsEmpty = false;
	ifs.putback(ch);//放回上面读取的字符

	
	int index=1;//代表届数
	string data;//读取完整的字符串
	while (ifs >> data)
	{
		string str;//，分隔的子串
		vector<string> v;//放子串的vector
		v.clear();
		int start = 0;//开始查找的下标。初始从0开始查
		int pos = -1;//返回的，的下标。初始为找不到的-1
		while (true)
		{
			pos = data.find(',', start);
			if (pos == -1) 
				break;
			str = data.substr(start, pos - start);
			v.push_back(str);
			start = pos + 1;
		}
		m_Record[index] = v;
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord()
{
	if (fileIsEmpty)
	{
		cout << "文件打开失败或文件为空" << endl;
	}
	else
	{ 
		for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
		{
			cout << "第" << it->first << "届" << endl;
			cout << "第一名编号：" << it->second[0] << "\t分数：" << it->second[1] << endl;
			cout << "第二名编号：" << it->second[2] << "\t分数：" << it->second[3] << endl;
			cout << "第三名编号：" << it->second[4] << "\t分数：" << it->second[5] << endl;
		}
	}
	system("pause");
}

void SpeechManager::clearRecord()
{
	cout << "是否确认清空" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs;
		ofs.open("speech.csv", ios::trunc);
		ofs.close();
		initSpeech();
		createSpeaker();
		loadRecord();
		cout << "清空成功" << endl;
		system("pause");
	}
}