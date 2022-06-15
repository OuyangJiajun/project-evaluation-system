#include "projectManager.h"

ProjectManager::ProjectManager()
{
	initEvaluation();
	createProject();
	loadRecord();
}

ProjectManager::~ProjectManager()
{
	
}

void ProjectManager::showMenu()
{
	cout << "*************************************" << endl;
	cout << "**********��ӭ�μ���Ŀ����****** ****" << endl;
	cout << "***********1.��ʼ��Ŀ����******* ****" << endl;
	cout << "***********2.�鿴�����¼************" << endl;
	cout << "***********3.������ż�¼************" << endl;
	cout << "***********0.�˳����ų���************" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}

void ProjectManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void ProjectManager::initEvaluation()
{
	v1.clear();
	v2.clear();
	vVictory.clear();
	m_Project.clear();
	m_Index = 1;
	m_Record.clear();
}

void ProjectManager::createProject()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		//����
		string name = "��Ŀ";
		name += nameSeed[i];

		//speaker��ʼ�����������
		Project sp;
		sp.m_Name = name;
		sp.m_Score[0] = 0;
		sp.m_Score[1] = 0;

		//��ʼ��vector��map
		v1.push_back(i + 10001);
		m_Project.insert(pair<int, Project>(i + 10001,sp));
	}
}

void ProjectManager::startEvaluation()
{
	//��һ������
	//1.��ǩ
	evaluationDraw();
	
	//2.����
	evaluationContest();

	//3.��ʾ�������
	showResult();

	//�ڶ�������
	//1.��ǩ
	evaluationDraw();

	//2.����
	evaluationContest();

	//3.��ʾ���ս��
	showResult();

	//4.�������
	saveRecord();

	//���³�ʼ��
	initEvaluation();
	createProject();
	loadRecord();
}

void ProjectManager::evaluationDraw()
{
	cout << "��" << m_Index << "����Ŀ���ڳ�ǩ" << endl;
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

void ProjectManager::evaluationContest()
{
	srand((unsigned int)time(NULL));
	cout << "��" << m_Index << "��������ʽ��ʼ" << endl;

	vector<int> v_Src; //�Ż����½���һ��v_Src����һ�� = v1���ڶ��� = v2������Ĵ�ֽ�������ͨ��
	if (m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//������ʱ��
	//�Ż���%6��ѭ��д����ʵ��һ����ͨ�õ�������
	int count = 0;//��¼��ǰ¼�������
	//�������󣺸���multimap��ֹͬ����ʱ����Ĳ���ʧ��
	//�Ż������greater<double>()ʹ�ôӴ�С��
	multimap<double, int, greater<double>> groupScore;//��¼�����ͱ��

	//������������Ŀ��֣���������ά����m_Project
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		deque<double> d;//�Ż����ĳ���deque������Ȼ����sort�㷨�����Ը������ȥ�����߷���ͷ�
		for (int i = 0; i < 10; i++)
		{
			d.push_back((rand() % 401 + 600) / 10.f);//�Ż������������ָĳ�С�����ֲ������ظ�   ��rand()%401+600��/10.f    ��600~1000��10���ɴ˴�����С��
		}
		//ȥ����ͷֺ���߷�
		sort(d.begin(), d.end());
		d.pop_back();
		d.pop_front();
		//ƽ���ּ�����Ŀ�÷�
		double sum = accumulate(d.begin(),d.end(),0.0f);//�Ż���������STL��accumulate�㷨
		double avg= sum / d.size();
		m_Project[*it].m_Score[m_Index-1] = avg;//�Ż���ȡ��ͨ��m_Index-1�ж�������ֱ����m_Index-1��ֵ
		groupScore.insert(pair<double, int>(avg, *it));
		count++;//����+1

		if (count % 6 == 0)//������
		{
			//�����������
			cout << "��" << count / 6 << "����������" << endl;
			for (multimap<double, int, greater<double>>::iterator it= groupScore.begin();it!=groupScore.end();it++)
			{
				cout << "��Ŀ��ţ�" << (*it).second << "\t���ƣ�" << m_Project[(*it).second].m_Name << "\t������" << m_Project[(*it).second].m_Score[m_Index-1] << endl;
			}
			//ʵ�ֽ���
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
			//���map
			groupScore.clear();
		}
	}
}

void ProjectManager::showResult()
{
	cout << "��" << m_Index << "�ֽ�����Ŀ" << endl;
	if (m_Index == 1)//��ʾ��һ�ֽ������
	{
		int i = 0;
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++, i++)
		{
			if (i < 3)
			{
				if(i==0)cout << "��һ�������Ŀ��" << endl;
				cout << "��Ŀ��ţ�" << *it << "\t��Ŀ���ƣ�" << (m_Project.find(*it))->second.m_Name << "\t��Ŀ�÷֣�" << (m_Project.find(*it))->second.m_Score[0] << endl;
			}
			else
			{
				if(i==3)cout << "�ڶ��������Ŀ��" << endl;
				cout << "��Ŀ��ţ�" << *it << "\t��Ŀ���ƣ�" << (m_Project.find(*it))->second.m_Name << "\t��Ŀ�÷֣�" << (m_Project.find(*it))->second.m_Score[0] << endl;
			}
		}
		m_Index = 2;
	}
	else//��ʾ�ڶ������ս��
	{
		for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
		{
			cout << "��Ŀ��ţ�" << *it << "\t��Ŀ���ƣ�" << (m_Project.find(*it))->second.m_Name << "\t��Ŀ�÷֣�" << (m_Project.find(*it))->second.m_Score[1] << endl;
		}
	}
}

void ProjectManager::saveRecord()
{
	ofstream ofs;
	ofs.open("evaluation.csv",ios::out|ios::app);//csv�Զ��ŷָ�
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << m_Project[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�ļ���¼�ѱ���" << endl;
	system("pause");
}

void ProjectManager::loadRecord()
{
	ifstream ifs("evaluation.csv", ios::in);
	//�ļ������ڵ����
	if (!ifs.is_open())
	{
		fileIsEmpty = true;
		ifs.close();
		return;
	}

	//���ļ����
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	fileIsEmpty = false;
	ifs.putback(ch);//�Ż������ȡ���ַ�

	
	int index=1;//�������
	string data;//��ȡ�������ַ���
	while (ifs >> data)
	{
		string str;//���ָ����Ӵ�
		vector<string> v;//���Ӵ���vector
		v.clear();
		int start = 0;//��ʼ���ҵ��±ꡣ��ʼ��0��ʼ��
		int pos = -1;//���صģ����±ꡣ��ʼΪ�Ҳ�����-1
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

void ProjectManager::showRecord()
{
	if (fileIsEmpty)
	{
		cout << "�ļ���ʧ�ܻ��ļ�Ϊ��" << endl;
	}
	else
	{ 
		for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
		{
			cout << "��" << it->first << "��" << endl;
			cout << "��һ����ţ�" << it->second[0] << "\t������" << it->second[1] << endl;
			cout << "�ڶ�����ţ�" << it->second[2] << "\t������" << it->second[3] << endl;
			cout << "��������ţ�" << it->second[4] << "\t������" << it->second[5] << endl;
		}
	}
	system("pause");
}

void ProjectManager::clearRecord()
{
	cout << "�Ƿ�ȷ�����" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs;
		ofs.open("evaluation.csv", ios::trunc);
		ofs.close();
		initEvaluation();
		createProject();
		loadRecord();
		cout << "��ճɹ�" << endl;
		system("pause");
	}
}