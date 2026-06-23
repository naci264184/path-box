#include<iostream>
using namespace std;
#include<fstream>
#include<string>
#include<Windows.h>

class gjl;										//工具类
int gjcsh(gjl* gj);								//工具集的初始化
void strzch(string& str, char* ch);				//string类型的值，赋值给char[]类型
void chzstr(char* ch, string& str);				//char[]类型的值，赋值给string类型
void hqmc(char* lj, char* wjm);					//截取路径中的文件名（查找函数需要用到string类型，需要先将char*类型的路径转成string类型）
void scwj(char* lj);							//删除文件（传入一个路径）
bool pdlj(string lj);							//判断文件（路径）是否可以打开
bool pdzflx(string& str, int len);				//判断是否为该工具集的，工具编号（1~10）的数字（判断该工具编号是否存在的部分，在排序、删除、选择内部）
double zfzsz(string* str, int len);
void csh();										//初始化
void zsgj();									//展示所有工具
void gn();										//功能
void tj();										//添加
void px();										//排序
void sc();										//删除
void bc();
int xzgj(string& ts, int& sr, int ms, int sr2);		//选择工具
void scnr();										//输出内容（减少代码长度用的，输出一些内容）
#include"path-box.h"


//用cin输入时，如果内容中有空格，会将这段内容分为多次输入，如："C:\Program Files\Genshin Impact\Genshin Impact Game\YuanShen.exe"
//这里有4处空格，相当于将内容分成了5段，每一次输入只会输入最左边那一段，当进入下一次输入时，会自动将上一次没有完成赋值的输入，赋值给这次输入
//所以，当输入带有空格的内容时，不能正常输入，当输入带有空格的路径时，无法正常将它装入工具集中，并且会出现跳过多次输入的情况
//解决方法：将路径从文件中传进去，输入遇到空格会停止，但是文件传入不会，文件传入中整行读取的，遇到换行符才会停止输入



int main()
{
	string temp;
	bool pd = false;
	int xz = 0;

	ofstream tofs;						//防止没有文件导致程序出错，先创建出对应存储数据的文件
	tofs.open(sjbc_lj, ios::out | ios::app);
	tofs.close();						//这里之前出现过缓存未加载，这里错误的把后面的ostream同名但局部对象，跟这个变量同地址了，
										//导致后面的文件流对象全是追加方式写出
	sl = gjcsh(gj);
	
	//jm();

	while (1)
	{
		system("cls");

		if (sl == 0)					//如果工具集中一个工具也没有
		{
			csh();						//初始化工具集，添加第一个工具
			continue;					//初始化完后，跳过后面内容，进入下一次循环
		}
		else
		{
			zsgj();								//展示所有工具

			cout << "选择中" << endl;
			cin >> temp;						//输入选择

			if (temp == "0")					//如果输入内容为0，则退出程序
			{
				cout << "欢迎下次使用" << endl;
				system("pause");
				return 0;
			}
			else if (temp == "00")				//如果输入内容为00，则进入功能界面
			{
				gn();
				continue;						//并在退出功能界面时，跳过后面未执行的，进入下次循环
			}

			pd = pdzflx(temp, temp.size());		//如果输入内容不为0和00，则判断一下输入内容是否为1~9的数字
			if (pd == true)						//如果是
			{
				xz = zfzsz(&temp, temp.size());	//则将数字字符串转为数字类型
				if (xz >= 1 && xz <= sl)		//如果该数字，为目前拥有的工具，的编号
				{
					system("cls");				//清屏

					//MessageBoxW(NULL, L"请在2秒内切换到目标应用程序（如记事本）", L"提示", MB_OK);			//创建一个提示窗口（用于音乐）
					system(gj[xz - 1].lj);		//则打开对应工具

					//system("pause");
					continue;
				}
			}
			cout << "没有该工具" << endl;		//否则，就是输入内容不对，或没有数字对应的工具（如：工具集中只有1、2，而这里输入了3号工具）
			system("pause");
		}
	}




	system("pause");
	return 0;
}