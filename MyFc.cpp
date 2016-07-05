// 中文分词

#include "stdafx.h"


#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stack>

#include "MyFc.h"

using namespace std;




 Dictiory D; //加载词典

void Dictiory::init(string dictiory_filename)
{
	int i,j;
	for(i = 0; i < e1 - s1;i++)
		for(j = 0; j < e2 - s2;j++)
			hash[i][j] = -1;
	H.resize(6768);

	fin.open(dictiory_filename.c_str());
		
	LoadDic();
}


void Dictiory::LoadDic()
{
	char cstr[maxwordlen];
	string str;
	int i,j,k = 0,wordnumber;




    while(fin.getline(cstr,maxwordlen))
    {
		i = (unsigned char)cstr[0] - s1;
		j = (unsigned char)cstr[1] - s2;
		hash[i][j] = k;		
		H[k].key = cstr;				
		wordnumber = GetNum();				
		for(i = 0; i < wordnumber;i++)
		{
             fin.getline(cstr,maxwordlen);             
			 str = cstr;
			 str = str.substr(2,str.length() - 2);			 
	    	 AddWord(str,k);
		}
		k++;
	}
}



int Dictiory::BinarySearch(string str,int k)
{
	unsigned int len = str.length();
	int L = 0,R = H[k].W.size() - 1,M;
	while(L <= R)
	{
		M = (L + R)/2;
		if(H[k].W[M]->key.size() == len)
			return M;
		else if(H[k].W[M]->key.size() < len)
			L = M + 1;
		else R = M - 1;
	}	
	return -1;
}

void Dictiory::AddWord(string str,int k)
{	


	if((int)str.length() > H[k].size)
	{
		H[k].size = str.length();
		Second *t = new Second(str);
		H[k].W.push_back(t);
	}
	else
		InsertWord(str,k);	
}

void Dictiory::InsertWord(string str, int k)
{

	int in = BinarySearch(str,k);	
	if(in == -1)
	{
	   unsigned int L = 0,R = H[k].W.size() - 1;
	   unsigned int len = str.length();
	   while(L <= R&&len > H[k].W[L]->key.size())
		L++;
	   H[k].W.resize(H[k].W.size() + 1);		
	   for(unsigned int i = R + 1;i > L;i--)
		  H[k].W[i] = H[k].W[i - 1];
	   Second *t = new Second(str);
	   H[k].W[L] = t;
	}
	else
	{
		Second *pre,*t = H[k].W[in];
		while(t)
		{
		  pre = t;
		  t = t->next;
		}
		pre->next = new Second(str);
	}
}

int Dictiory::GetNum()
{
	char cstr[maxwordlen];
	fin.getline(cstr,maxwordlen);
	int n = 0;
	unsigned int  i;

	for(i = 0; i < strlen(cstr);i++)
		n = n * 10 + cstr[i] - '0';
	return n;
}



bool Dictiory::IsC(char c)
{
	unsigned value =  unsigned((unsigned char)c);
	return value >= s1&&value < e1;
}

bool Dictiory::IsEc(char c)
{
	unsigned value =  unsigned((unsigned char)c);
	return value <= 0X7F;
}

bool Dictiory::IsWord(string str,int k,int t)
{	
	Second *temp = H[k].W[t];
	while(temp)
	{
		if(temp->key == str)
			return true;
		temp = temp->next;
	}
	return false;
}

void Dictiory::SkipNotChinese(string &str,stack<string> &stk)
{	
	unsigned L = 0,R = str.length();
	while(L < R&&!IsC(str[L]))
	{		
		if(!IsEc(str[L]))
			L++;		
		L++;
	}
	if(L > 0)
	{
	    stk.push(str.substr(0,L));	
	    str = str.substr(L,R - L);
	}
}




bool Dictiory::FC_char_read(string s,char *c,unsigned int *i,unsigned int maxl) //读取字符串中的字符，并记数
{



 if(*i==maxl+1) return 0;


 *c=s[*i];



 *i=*i+1;

 return 1;

}





string Dictiory::SegmentWord(string s) //对字符串进行中文分词
{
	stack<string> stk;
	

	string str,sstr;	
	int i,j,startpos,endpos;
	char c;

  string my_text;

    int bb;

	   unsigned int zz=0;

 unsigned int s_l=s.length();


 c=s[zz];

 FC_char_read(s,&c, &zz,s_l);


	while(1)
	{

 

		if(!IsC(c))
		{		
			if(!str.empty())
			{
				//cout << str << " " << str.length() << endl;
		        startpos = 0,endpos = str.length();
		        while(startpos < endpos)
		        {				
			       if(str.length() <= 2)
			       {				
				       stk.push(str);
				       if(!sstr.empty())
				       {
					       str = sstr;
					       //sstr.clear();
						   sstr="";
				        }
				        startpos += 2;
			        }
			       else
			       {			
				       i = (unsigned char)str[0] - s1,j = (unsigned char)str[1] - s2;				
				       if(hash[i][j] >= 0)
				       {
					        string word = str.substr(2,str.length() - 2);
					        int in = BinarySearch(word,hash[i][j]);
					        if((in != -1)&&IsWord(word,hash[i][j],in))
					        {
						        stk.push(H[hash[i][j]].key + word);
						        startpos += str.length();
						        str = sstr;
					            //sstr.clear();
						        sstr="";						
					         }
					         else
					         {
						         sstr = sstr + str.substr(0,2);
						         str = str.substr(2,str.length() - 2);
					         }
				         }
				         else
				         {						
					          sstr = sstr + str.substr(0,2);
					          str = str.substr(2,str.length() - 2);
				          }
			         }
		         }
		         while(!stk.empty())
 	             {



                   my_text += stk.top(); //中文
                   my_text += " ";

		            stk.pop();
	              }
			}							
			//str.clear();
								     
			str="";
			str += c;




        while(FC_char_read(s,&c, &zz,s_l) )
 
			{





			 if(IsC(c)) break;

			 str += c;

             bb=(int)c;
	
			// if(bb>0) my_text += "e";

			// else my_text += "z";

			}






			my_text += str;   //英文
            my_text += " ";


			 //cout << str << " " << str.length() <<  endl;
			 //str.clear();
             str="";
			 str += c;
			 FC_char_read(s,&c, &zz,s_l);
			 str += c;
		}	
		else
		{
			 str += c;
			 FC_char_read(s,&c, &zz,s_l);


			 str += c;
		}

       if(FC_char_read(s,&c, &zz,s_l)==0) break;

	}



 return my_text;


}




string Dictiory::int2str(int num) 
{ 
if(num == 0) 
return "0"; 

string str = ""; 

while(num) 
{ 
str = (char)(num % 10 + 48) + str; 
num /= 10; 
} 

return str; 
} 



