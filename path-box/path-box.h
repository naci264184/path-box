#pragma once


int sl = 0;							//当前的工具数量
int gjsx = 21;						//工具数量的上限（修改工具上限时，需要修改两个地方，另一个是数组的元素个数）（工具集的最大上限为21个）
string sjbc_lj = "temp/data/paths.txt";		//数据保存_路径
string lssj_lj = "temp/logs/temp.txt";		//临时数据_路径
namespace fs = std::filesystem;			//将fs设置为命名空间filesystem
string lssj_ml = "temp/data";			//临时数据目录
string lssj_ml2 = "temp/logs";			//临时数据目录2

class gjl								//工具类
{
public:
	char gjm[255];						//工具名
	char lj[255];						//路径（需要用双引号括起来）
};

gjl gj[21];								//修改工具上限时，还需要修改这里的数组元素数量

int gjcsh(gjl* gj)						//工具集的初始化
{
	int i = 0;
	ifstream ifs;										//打开存储数据的文件
	ifs.open(sjbc_lj, ios::in | ios::app);
	if (!ifs.is_open())									//如果打开失败
	{
		ifs.close();									//关闭文件，并记录数量为0
		return 0;
	}

	while (ifs.getline(gj[i].lj, 255))					//如果打开成功，将里面的路径，逐一赋值给工具的路径
	{
		if ((gj[i].lj)[0] != '\"')						//如果路径的第一个字符不是双引号："
		{
			string temp = gj[i].lj;						//可能是因为路径是手动输入的
			temp.insert(0, "\"");						//给该工具的路径加上双引号
			temp += "\"";
			strzch(temp, gj[i].lj);
		}

		hqmc(gj[i].lj, gj[i].gjm);						//获取名称
		i++;
	}
	return i;
}

void jm()
{
	cout << "欢迎使用工具集" << endl;
	cout << endl;
	cout << "0.退出" << endl;
	cout << "00.进入功能界面" << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl;
	system("pause");
	system("cls");
}

void strzch(string& str, char* ch)				//string类型的值，赋值给char[]类型
{
	ofstream ofs;
	ofs.open(lssj_lj, ios::out);
	ofs << str << endl;
	ofs.close();

	ifstream ifs;
	ifs.open(lssj_lj, ios::in);
	if (!ifs.is_open())
	{
		ifs.close();
		return;
	}
	ifs.getline(ch, 255);
	ifs.close();
}
void chzstr(char* ch, string& str)				//char[]类型的值，赋值给string类型
{
	ofstream ofs;
	ofs.open(lssj_lj, ios::out);
	ofs << ch << endl;
	ofs.close();

	ifstream ifs;
	ifs.open(lssj_lj, ios::in);
	if (!ifs.is_open())
	{
		ifs.close();
		return;
	}
	getline(ifs, str);

	ifs.close();
}

void hqmc(char* lj, char* wjm)				//截取路径中的文件名（查找函数需要用到string类型，需要先将char*类型的路径转成string类型）
{
	//变量的定义
	string str;
	string temp;
	int wz = 0;
	int wz2 = 0;

	chzstr(lj, str);						//将路径赋值给string类型临时变量

	//开始查找
	wz = str.rfind("\\");					//记录路径中最后一个斜杆的位置
	wz2 = str.rfind(".");					//记录路径中最后一个.的位置

	temp = str.substr(wz + 1, wz2 - wz - 1);	//将斜杆到点之间的字符（文件名）传给临时变量2

	strzch(temp, wjm);							//将获取到的文件名，赋值给文件名
}

void scwj(char* lj)								//传入一个路径
{
	string temp;								//记录路径的string类型
	string temp2 = "\"del ";					//删除指令
	char ch[255];								//记录完整的删除命令（删除指令+文件路径）

	chzstr(lj, temp);							//将路径转成string类型
	temp.erase(0, 1);							//去掉前面的双引号"

	temp2 += lj;								//在删除指令的后面加上路径
	strzch(temp2, ch);							//转成char*类型

	system(ch);									//将该char*类型变量传入system函数，删除路径
}

bool pdlj(string lj)							//判断文件（路径）是否可以打开
{
	ifstream ifs;
	ifs.open(lj, ios::in || ios::binary);
	if (ifs.is_open())							//如果打开成功
	{
		ifs.close();
		return true;							//返回true
	}
	else										//否则（打开失败）
	{
		ifs.close();
		return false;							//返回false
	}
}

bool pdzflx(string& str, int len)					//判断是否为工具集的编号，的数字
{
	int ws = gjsx / 10;								//获取工具上限的数，中的十位数

	//单位数
	if (str[0] > 48 && str[0] <= 57 && len == 1)	//如果字符串只有一个字符，且该字符为1~9
	{
		return true;								//返回真
	}

	//双位数
	int sw;						//十位
	int gw;						//个位
	int gs;						//十位数的最大数时，个位数的范围

	if (len != 2)				//如果这时字符串的字符个数不为两个，则为假
	{
		return false;
	}

	for (int cs = 0;cs < ws;cs++)			//进入循环，循环次数为十位的数字，第一次，十位数为1，第二次，十位数为2...一直到循环次数不小于十位的数字
	{
		sw = 49 + cs;						//十位从1开始

		if (sw == ws)								//如果当前数字为十位的最大数
		{
			gs = gjsx - (sw * 10);					//则它的个位数的范围为：工具数量上限 - 该十位数字*10
			gw = 48;
			for (int cs2 = 0;cs2 < gs;cs2++)
			{
				if (str[0] == sw && str[1] == gw)		//如果第一个字符为当前位数，且第二个字符为个数
				{
					return true;						//返回真
				}
				gw++;
			}
		}
															//如果当前数字不为十位的最大数，
		if (str[0] == sw && str[1] >= 48 && str[1] <= 57)	//但是第一个字符为当前位数，且第二个字符为0~9的数字
		{
			return true;									//返回真
		}

		sw++;									//检测完一次十位，就将十位数字加1，进入下次检测
	}


	return false;									//如果都不是，返回假
}

double zfzsz(string* str, int len)
{
	bool fs;							//记录是否为负数
	int zfqd = 0;						//字符起点
	double num;							//数
	double sz[10] = { 0.0, };			//单个数字，当前最大为10个
	int gs;								//单个数字的个数，数字的位数

	if ((*str)[0] == '-')				//如果第一个字符等于负号
	{
		fs = true;						//则这个数为负数
		zfqd = 1;						//数字从第二个字符开始
	}
	else								//否则（第一个字符不是负号）
	{
		fs = false;						//这个数为正数
	}
	gs = len - zfqd;					//单个数字的个数为：字符的个数 - 数字的起点位置


	for (int i = 0;i < gs;i++)			//根据ASCII码，将字符串的一个一个数字字符，转换为0~9的数字，装入数组中
	{
		sz[i] = (double)(*str)[zfqd] - 48;
		zfqd++;
	}

	num = sz[0];
	for (int i = 1;i < gs;i++)			//将一个一个单个数字，拼接成一个数
	{
		num *= 10;
		num += sz[i];
	}

	if (fs)								//如果为负数
	{
		num *= -1;						//将这个数乘以-1
	}

	return num;
}

void csh()							//初始化
{
	string temp;					//创建第一个工具
	while (1)
	{
		cout << "工具集初始化" << endl << endl;
		cout << "初始化完毕后就可以开始使用，退出键为0，进入功能界面为00" << endl;
		cout << "请输入一个路径" << endl;
		cin >> temp;				//输入一个路径
		if (pdlj(temp))				//判断路径是否可以打开
		{
			break;
		}

		cout << "没有该路径" << endl;
		system("pause");
		system("cls");
	}
	string Temp;
	Temp = "\"";					//添加路径
	Temp += temp;
	Temp += "\"";

	strzch(Temp, gj[0].lj);			//将string类型路径，转成char类型后，赋值给第一个工具的路径

	hqmc(gj[0].lj, gj[0].gjm);		//添加名称

	sl++;							//记录工具数量+1
	bc();

	cout << "添加成功" << endl;
	system("pause");
	system("cls");
}

void zsgj()													//展示所有工具
{
	string jc_zfcd;					//检测字符长度
	int zfcd = 0;					//字符长度
	int zbf_gs = 0;					//水平制表符_个数

	cout << "工具集" << endl;
	cout << "\t\t\t文件名\t\t\t文件路径" << endl;

	for (int i = 0;i < sl;i++)								//打印所有工具
	{
		cout << i + 1 << "：\t\t\t" << gj[i].gjm;

		//根据工具名长度，自动判定制表符输出个数
		jc_zfcd = gj[i].gjm;
		zfcd = jc_zfcd.size();

		//cout << "字符长度：" << zfcd << endl;
		//system("pause");

		if (zfcd < 8)
		{
			zbf_gs = 3;
		}
		else if (zfcd < 16 && zfcd >= 8)
		{
			zbf_gs = 2;
		}
		else if (zfcd < 24 && zfcd >= 16)
		{
			zbf_gs = 1;
		}
		else
		{
			zbf_gs = 0;
		}

		for (int i = 0;i < zbf_gs;i++)
		{
			cout << "\t";
		}

		cout << gj[i].lj << endl;
	}
	cout << endl;
}

void gn()
{
	string xz;

A:

	system("cls");
	cout << "功能" << endl;
	cout << endl;
	cout << "1.添加文件\t\t\t\t\t2.工具排序" << endl;;
	cout << "3.删除工具\t\t\t\t\t4.清空工具" << endl;
	cout << "0.退出" << endl;
	cout << endl;
	cout << "请选择要进行的操作" << endl;

	cin >> xz;

	if (xz == "1")
	{
		system("cls");
		tj();
	}
	else if (xz == "2")
	{
		system("cls");
		px();
	}
	else if (xz == "3")
	{
		system("cls");
		sc();
	}
	else if (xz == "4")
	{
		string temp;
		cout << "是否确认清空";
		Sleep(2000);
		cout << "\t\t\t\t\t（输入1清空）" << endl;
		cin >> temp;
		if (temp == "是" || temp == "1")
		{
			ofstream ofs;
			ofs.open(sjbc_lj, ios::out);
			sl = 0;		
			cout << "清空完毕" << endl;
			system("pause");
		}
		
	}
	else if (xz == "0")
	{
		return;
	}
	else
	{
		cout << "没有该选项" << endl;
		system("pause");
		goto A;
	}

}

void tj()
{
	zsgj();
	if (sl == gjsx)									//如果刚进来数量就是满的
	{
		cout << "数量已达到上限" << endl;			//输出一句话提示，并暂停系统，按任意键后退出
		Sleep(2000);
		system("pause");
		return;
	}

	string temp;
	string scnr = "单个添加\n请输入添加的文件的路径\t\t\t\t\t（输入00切换添加模式）\n";
	bool xh = false;								//判断后面是否进入循环
	int cs = 1;

	do												//如果刚进来时，数量并不是满的
	{
		system("cls");
		zsgj();

		if (sl == gjsx)								//但是在中途添加到上限了，就不提示，也不暂停系统，直接退出
		{
			return;
		}
		else
		{
			while (1)								//添加工具
			{
				system("cls");
				zsgj();

				cout << scnr;
				cin >> temp;						//输入工具的路径
				if (temp == "0")					//如果输入内容为0
				{
					return;							//则退出
				}
				else if (temp == "00")
				{
					if (cs == 1)
					{
						xh = true;
						scnr = "批量添加\n请输入添加的文件的路径\t\t\t\t\t（输入00切换添加模式）\n";
						cs = 2;
					}
					else if (cs == 2)
					{
						xh = false;
						scnr = "单个添加\n请输入添加的文件的路径\t\t\t\t\t（输入00切换添加模式）\n";
						cs = 1;
					}
					continue;
				}
				if (pdlj(temp))						//判断是否可以打开
				{
					break;							//可以打开就退出循环
				}

				cout << "没有该路径" << endl;		//否则，提示一下，然后进入循环重新输入
				Sleep(2000);
				system("pause");
			}

			string Temp;
			Temp = "\"";						//添加路径
			Temp += temp;
			Temp += "\"";

			strzch(Temp, gj[sl].lj);			//将string类型路径，转成char类型后，赋给对应工具的路径
			hqmc(gj[sl].lj, gj[sl].gjm);		//添加名称

			sl++;								//记录工具数量+1
			bc();								//保存

			cout << "添加成功" << endl;
			//Sleep(2000);
			system("pause");
			system("cls");
		}
	} while (xh);

}

int xzgj(string& ts, int& sr, int ms = 1, int sr2 = 0);	//输出一个提示，然后输入一个工具编号，判断是否为当前拥有的工具，的编号，
														//不是则进入循环重新输入，直到输入正确的、或者输入退出键0，才能退出函数，
														//参数：(提示内容,输入内容,模式（默认为1，模式2会在提示语句后面一行输出第4个参数）,输出内容2)

void px()
{
	int xz1 = 0, xz2 = 0;
	char tlj[255];
	char tgjm[255];

	string temp = "单次操作\n请输入两个工具的编号：\t\t\t\t\t（输入00切换操作模式）\n";
	int pd = 0;
	bool xh = false;						//判断后面是否进入循环
	int cs = 1;

	do
	{
		while (1)
		{
			system("cls");
			pd = xzgj(temp, xz1);			//输入数字，然后判断工具是否为当前拥有的工具，的编号

			if (pd == 0)					//输入内容为0，退出排序
			{
				return;
			}
			else if (pd == 3)
			{
				if (cs == 1)
				{
					xh = true;
					temp = "批量操作\n请输入两个工具的编号：\t\t\t\t\t（输入00切换操作模式）\n";
					cs = 2;
				}
				else if (cs == 2)
				{
					xh = false;
					temp = "单次操作\n请输入两个工具的编号：\t\t\t\t\t（输入00切换操作模式）\n";
					cs = 1;
				}
				continue;
			}
			else if (pd == 1)				//输入内容为当前拥有的工具，的编号，退出循环
			{
				system("cls");
				break;
			}
			scnr();							//否则，跳过后面的内容，进入下次循环重新输入
		}

		while (1)
		{
			system("cls");						//清屏
			pd = xzgj(temp, xz2, 2, xz1);		//输入数字，判断工具是否为当前拥有的工具，的编号

			if (pd == 0)						//输入内容为0，退出排序
			{
				return;
			}
			else if (pd == 1)					//输入内容为当前拥有的工具，的编号，退出循环
			{
				break;
			}
			else if (pd == 3)
			{
				if (cs == 1)
				{
					xh = true;
					temp = "批量操作\n请输入两个工具的编号：\t\t\t\t\t（输入00切换操作模式）\n";
					cs = 2;
				}
				else if (cs == 2)
				{
					xh = false;
					temp = "单次操作\n请输入两个工具的编号：\t\t\t\t\t（输入00切换操作模式）\n";
					cs = 1;
				}
				continue;
			}
			else if (pd == 2)					//输入内容，和上面一个输入相同（自己和自己换位置），跳过后面内容，进入下次循环
			{
				break;
			}
			scnr();								//如果都不是，跳过后面所有内容，进入下次循环重新输入
		}

		if (pd == 2)
		{
			continue;
		}

		xz1--;									//选择工具时，是从1开始选的，但是工具在数组中，是从0开始的，这里要将下标数字减一
		xz2--;

		strcpy_s(tgjm, gj[xz1].gjm);					//将工具1的工具名、路径，复制给临时变量
		strcpy_s(tlj, gj[xz1].lj);

		strcpy_s(gj[xz1].gjm, gj[xz2].gjm);				//将工具2的工具名、路径，复制给工具1
		strcpy_s(gj[xz1].lj, gj[xz2].lj);

		strcpy_s(gj[xz2].gjm, tgjm);					//将临时变量（工具1）的工具名、路径，复制给工具2
		strcpy_s(gj[xz2].lj, tlj);

		bc();											//保存

		cout << "替换成功" << endl;						//提示替换成功，然后进入循环进行下次排序
		//Sleep(2000);
		system("pause");
	} while (xh);
}

void sc()
{	
	bool pd;
	int xz = 0;

	string temp = "单个删除\n请输入需要删除的工具的编号\t\t\t\t\t（输入00切换模式）\n";
	int pd2 = 0;
	bool xh = false;					//判断后面是否进入循环
	int cs = 1;

	do
	{
		while (1)
		{
			system("cls");
			pd2 = xzgj(temp, xz);		//输入数字，判断工具是否为当前拥有的工具，的编号

			if (pd2 == 0)				//退出
			{
				return;
			}
			else if (pd2 == 3)
			{
				if (cs == 1)
				{
					xh = true;
					temp = "批量删除\n请输入需要删除的工具的编号\t\t\t\t\t（输入00切换模式）\n";
					cs = 2;
				}
				else if (cs == 2)
				{
					xh = false;
					temp = "单个删除\n请输入需要删除的工具的编号\t\t\t\t\t（输入00切换模式）\n";
					cs = 1;
				}
				continue;
			}
			if (pd2 == 1)				//是
			{				
				break;
			}
			scnr();						//否则，提示一下，然后进入下次循环
		}

		for (int i = xz - 1;i < sl - 1;i++)		//删除指定编号工具，从该编号工具开始，赋值为后面一位编号的工具，的值，一直到将后面所有都赋值完
		{
			gj[i] = gj[i + 1];
		}
		sl--;									//记录的工具数量减一
		bc();									//保存

		cout << "删除成功" << endl;
		//Sleep(2000);
		system("pause");
	} while (xh);
}

void bc()												//保存（将所有工具的路径，写入文件中）
{
	ofstream ofs;
	ofs.open(sjbc_lj, ios::out);
	for (int i = 0;i < sl;i++)							//写入文件前，先将文件内所有内容清除
	{
		ofs << gj[i].lj << endl;
	}
	ofs.close();
}

int xzgj(string& ts, int& sr, int ms, int sr2)			//选择工具（返回值：0（退出函数）、1（退出循环）、2（跳过后面内容，进入下次循环））
{
	string Sr;
	zsgj();												//展示所有工具
	cout << ts;
	if (ms == 2)
	{
		cout << sr2 << endl;
	}

	cin >> Sr;									//输入第一个工具的路径
	if (Sr == "0")								//如果输入内容为0，则退出排序
	{
		return 0;
	}
	else if (Sr == "00")						//如果输入内容为00，则切换删除模式
	{
		return 3;
	}
	bool pd = pdzflx(Sr, Sr.size());			//判断输入内容是否为数字
	if (pd)										//如果为数字
	{
		sr = zfzsz(&Sr, Sr.size());				//将该字符串，转为数字类型
		if (ms == 2 && sr == sr2)				//如果为第二模式，并且第二个输入内容和第一个输入内容相同
		{
			cout << "无效操作" << endl;			//相当自己和自己互相换位置，无效操作，跳过后面所有内容，进入下次循环
			Sleep(2000);
			system("pause");					//则为跳过后面内容，进入下次循环
			return 2;
		}
		if (sr >= 1 && sr <= sl)				//如果该数字，为目前拥有的工具，的编号
		{
			return 1;							//则为退出循环
		}
	}
}

void scnr()										//输出内容（减少代码长度用的，输出一些内容）
{
	cout << "没有该工具" << endl;
	Sleep(2000);
	system("pause");
	system("cls");
}