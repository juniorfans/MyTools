#ifndef TEST_PROCESS_THREAD
#define TEST_PROCESS_THREAD
#include <windows.h>


//��õ�ǰϵͳ�ڴ�ռ��
SIZE_T getCurrentMemoryUse(SIZE_T *peakMemory);

//���Ե�һ�����г���. ��֮ǰû�������������ҷ��� 0. ��������,����1
int tryFirstRunModule();

//���ݽ��� id kill ����. ���� TRUE ��ʾ kill �ɹ�����ʧ��
BOOL KillProcess(DWORD dwPid, DWORD waitKillMs)  ;

//�������̽���, ���� TRUE �ɹ�����ʧ��
BOOL EnableDebugPrevilige(BOOL   fEnable) ;


/************************************************************************/
/*  
���ݽ����� kill ����.
���� 2 ��ʾû�ҵ�����
���� 1 ��ʾ�رս���ʧ��
���� 0 ��ʾ�رճɹ�
/************************************************************************/
int KillProcessByName(const TCHAR *lpszProcessName) ;

//�������ֲ��ҽ���
BOOL findProcess(const TCHAR *lpszProcessName) ;

#endif