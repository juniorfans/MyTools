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

//���ֽ�תΪ���ֽ�. char -> Unicode
wchar_t* multCharSetToWide(const char * buf,size_t bufLen,size_t *realNumLen)
{
	/*
	setlocale(LC_ALL,"chs");

	FileEncoding fed;	//CP_UTF8
	size_t testLen = bufLen < 4096 ? bufLen : 4096;
	int CP_PAGE = fed.getCharSetPageCode(buf,testLen);
	//TODO ���ﻹ�� BUG����ʱ��һ�ε��� MultiByteToWideChar ���� 0 �ֽ�
	int theUTF8 = CP_UTF8;
	//���ֽ��ַ���ת��Ϊ���ַ�������һ��������ʾԴ�ַ����Ĵ���ҳ
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