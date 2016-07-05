#ifndef MYZIBIANMA
#define MYZIBIANMA

#include <string>
using namespace std;

///////////////////////////////////////////////////////////////////////

void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // ��UTF-8ת����Unicode
void UnicodeToUTF_8(char* pOut,wchar_t* pText);  //Unicode ת����UTF-8
void UnicodeToGB2312(char* pOut,wchar_t uData);  // ��Unicode ת���� GB2312
void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 ת���ɡ�Unicode
void GB2312ToUTF_8(string& pOut,char *pText, int pLen);//GB2312 תΪ UTF-8
void UTF_8ToGB2312(string &pOut, char *pText, int pLen);//UTF-8 תΪ GB2312

///////////////////////////////////////////////////////////////////////


CString URLEncode(CString sIn);

inline BYTE toHex(const BYTE &x);

#endif