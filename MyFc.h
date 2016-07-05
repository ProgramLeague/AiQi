// ���ķִ�
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
	vector<Head> H; //�����������������ṹ����ΪHead
	ifstream fin; //�ʵ��ļ�


	int hash[e1 - s1][e2 - s2];	//��ϣ��  (ɢ�б�)���Ǹ��ݹؼ���ֵ(Key value)��ֱ�ӽ��з��ʵ����ݽṹ�����ؼ���Ϊk������ֵ�����f(k)�Ĵ洢λ���ϡ�
	int BinarySearch(string str,int k);
	int GetNum();	
	void LoadDic();

	void AddWord(string str,int k);
	void InsertWord(string str, int k);	
	bool IsWord(string str,int k,int t);	
	void SkipNotChinese(string &str,stack<string> &stk);

	bool FC_char_read(string s,char *c,unsigned int *i,unsigned int maxl);//��ȡ�ַ����е��ַ���������

public:

	bool IsC(char c);
	bool IsEc(char c);


    void init(string dictiory_filename);



	string SegmentWord(string s); //�ִ�


string int2str(int num) ;
};

extern Dictiory D; //���شʵ�

#endif