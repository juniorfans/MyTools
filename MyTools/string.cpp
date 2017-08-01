#include "string.h"




void upToLowCase(char *buf,size_t bufLen)
{
	char ch;
	const int diff = 'a' - 'A';
	for (size_t i = 0;i < bufLen;++ i)
	{
		ch = *(buf + i);
		if(ch >= 'A' && ch <= 'Z')
		{
			*(buf + i) = ch + diff;
		}
	}
}

//多字节转为宽字节. char -> Unicode
wchar_t* multCharSetToWide(const char * buf,size_t bufLen,size_t *realNumLen)
{
	/*
	setlocale(LC_ALL,"chs");

	FileEncoding fed;	//CP_UTF8
	size_t testLen = bufLen < 4096 ? bufLen : 4096;
	int CP_PAGE = fed.getCharSetPageCode(buf,testLen);
	//TODO 这里还有 BUG，有时第一次调用 MultiByteToWideChar 返回 0 字节
	int theUTF8 = CP_UTF8;
	//多字节字符串转化为宽字符串，第一个参数表示源字符串的代码页
	size_t nMBLen = MultiByteToWideChar(CP_PAGE,0,buf,bufLen,NULL,NULL);
	if(0 == nMBLen)
	{
	int ne = GetLastError();
	printf("MultiByteToWideChar failed. source file page code is : %d\r\n",CP_PAGE);
	}
	wchar_t* szWcsBuffer = (wchar_t*)malloc(sizeof(wchar_t) * (nMBLen + 1));

	ZeroMemory(szWcsBuffer, sizeof(wchar_t)*(1+nMBLen));
	MultiByteToWideChar(CP_PAGE,0,buf,bufLen, szWcsBuffer, nMBLen);
	*realNumLen = nMBLen;
	return szWcsBuffer;
	*/
	return NULL;
}