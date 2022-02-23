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
	cout << "**********��ӭ�μ��ݽ�����****** ****" << endl;
	cout << "***********1.��ʼ�ݽ�����******* ****" << endl;
	cout << "***********2.�鿴�����¼************" << endl;
	cout << "***********3.��ձ�����¼************" << endl;
	cout << "***********0.�˳���������************" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
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
		//����
		string name = "ѡ��";
		name += nameSeed[i];

		//speaker��ʼ�����������
		Speaker sp;
		sp.m_Name = name;
		sp.m_Score[0] = 0;
		sp.m_Score[1] = 0;

		//��ʼ��vector��map
		v1.push_back(i + 10001);
		m_Speaker.insert(pair<int, Speaker>(i + 10001,sp));
	}
}

void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1.��ǩ
	speechDraw();
	
	//2.����
	speechContest();

	//3.��ʾ�������
	showResult();

	//�ڶ��ֱ���
	//1.��ǩ
	speechDraw();

	//2.����
	speechContest();

	//3.��ʾ���ս��
	showResult();

	//4.�������
	saveRecord();

	//���³�ʼ��
	initSpeech();
	createSpeaker();
	loadRecord();
}

void SpeechManager::speechDraw()
{
	cout << "��" << m_Index << "��ѡ�����ڳ�ǩ" << endl;
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
	cout << "��" << m_Index << "�ֱ�����ʽ��ʼ" << endl;

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

	//�����б���ѡ�ִ�֣���������ά����m_Speaker
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
		//ƽ���ּ���ѡ�ֵ÷�
		double sum = accumulate(d.begin(),d.end(),0.0f);//�Ż���������STL��accumulate�㷨
		double avg= sum / d.size();
		m_Speaker[*it].m_Score[m_Index-1] = avg;//�Ż���ȡ��ͨ��m_Index-1�ж�������ֱ����m_Index-1��ֵ
		groupScore.insert(pair<double, int>(avg, *it));
		count++;//����+1

		if (count % 6 == 0)//������
		{
			//�����������
			cout << "��" << count / 6 << "���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it= groupScore.begin();it!=groupScore.end();it++)
			{
				cout << "ѡ�ֱ�ţ�" << (*it).second << "\t������" << m_Speaker[(*it).second].m_Name << "\t������" << m_Speaker[(*it).second].m_Score[m_Index-1] << endl;
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

void SpeechManager::showResult()
{
	cout << "��" << m_Index << "�ֽ���ѡ��" << endl;
	if (m_Index == 1)//��ʾ��һ�ֽ������
	{
		int i = 0;
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++, i++)
		{
			if (i < 3)
			{
				if(i==0)cout << "��һ�����ѡ�֣�" << endl;
				cout << "ѡ�ֱ�ţ�" << *it << "\tѡ��������" << (m_Speaker.find(*it))->second.m_Name << "\tѡ�ֵ÷֣�" << (m_Speaker.find(*it))->second.m_Score[0] << endl;
			}
			else
			{
				if(i==3)cout << "�ڶ������ѡ�֣�" << endl;
				cout << "ѡ�ֱ�ţ�" << *it << "\tѡ��������" << (m_Speaker.find(*it))->second.m_Name << "\tѡ�ֵ÷֣�" << (m_Speaker.find(*it))->second.m_Score[0] << endl;
			}
		}
		m_Index = 2;
	}
	else//��ʾ�ڶ������ս��
	{
		for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
		{
			cout << "ѡ�ֱ�ţ�" << *it << "\tѡ��������" << (m_Speaker.find(*it))->second.m_Name << "\tѡ�ֵ÷֣�" << (m_Speaker.find(*it))->second.m_Score[1] << endl;
		}
	}
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv",ios::out|ios::app);//csv�Զ��ŷָ�
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�ļ���¼�ѱ���" << endl;
	system("pause");
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);
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

void SpeechManager::showRecord()
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

void SpeechManager::clearRecord()
{
	cout << "�Ƿ�ȷ�����" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;

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
		cout << "��ճɹ�" << endl;
		system("pause");
	}
}