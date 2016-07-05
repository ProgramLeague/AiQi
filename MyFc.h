// 中文分词
#ifndef MY_ZWFC 
#define MY_ZWFC

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stack>

using namespace std;

const int s1 = 0XB0,s2 = 0XA1,e1 = 0XF8,e2 = 0XFF;
const int maxwordlen = 50;






struct Second
{
	string key;
	Second *next;
	Second(string k = "",Second *n = 0):key(k),next(n){}
};

struct Head
{
	int size;
	string key;
	vector<Second*> W;
	Head(string k = "",int s = 0):key(k),size(s){}
};

class Dictiory
{
	vector<Head> H; //创建空容器，其对象结构类型为Head
	ifstream fin; //词典文件


	int hash[e1 - s1][e2 - s2];	//哈希表  (散列表)，是根据关键码值(Key value)而直接进行访问的数据结构。若关键字为k，则其值存放在f(k)的存储位置上。
	int BinarySearch(string str,int k);
	int GetNum();	
	void LoadDic();

	void AddWord(string str,int k);
	void InsertWord(string str, int k);	
	bool IsWord(string str,int k,int t);	
	void SkipNotChinese(string &str,stack<string> &stk);

	bool FC_char_read(string s,char *c,unsigned int *i,unsigned int maxl);//读取字符串中的字符，并记数

public:

	bool IsC(char c);
	bool IsEc(char c);


    void init(string dictiory_filename);



	string SegmentWord(string s); //分词


string int2str(int num) ;
};

extern Dictiory D; //加载词典

#endif