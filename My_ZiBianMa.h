#ifndef MYZIBIANMA
#define MYZIBIANMA

#include <string>
using namespace std;

///////////////////////////////////////////////////////////////////////

void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // 把UTF-8转换成Unicode
void UnicodeToUTF_8(char* pOut,wchar_t* pText);  //Unicode 转换成UTF-8
void UnicodeToGB2312(char* pOut,wchar_t uData);  // 把Unicode 转换成 GB2312
void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 转换成　Unicode
void GB2312ToUTF_8(string& pOut,char *pText, int pLen);//GB2312 转为 UTF-8
void UTF_8ToGB2312(string &pOut, char *pText, int pLen);//UTF-8 转为 GB2312

///////////////////////////////////////////////////////////////////////


CString URLEncode(CString sIn);

inline BYTE toHex(const BYTE &x);

#endif