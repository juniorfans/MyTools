#include "pthread.h"
#include "string.h"

#include <Psapi.h>
#pragma comment(lib,"Psapi.lib")
#include <process.h>
#include <tlhelp32.h>

//��õ�ǰϵͳ�ڴ�ռ��
SIZE_T getCurrentMemoryUse(SIZE_T *peakMemory)
{
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	if(NULL != peakMemory)
		*peakMemory = pmc.PeakWorkingSetSize;
	return pmc.WorkingSetSize;
}


#pragma data_seg("Shared") 
int volatile g_lAppInstance = 0; 
#pragma data_seg() 
#pragma comment(linker,"/section:Shared,RWS")
//���Ե�һ�����г���. ��֮ǰû�������������ҷ��� 0. ��������,����1
int tryFirstRunModule()
{
	if (0 == g_lAppInstance)
	{
		g_lAppInstance = 1;
		return 0; //��ǰû�����й�
	}
	else 
	{
		return 1;
	}
}

//���ݽ��� id kill ����. ���� TRUE ��ʾ kill �ɹ�����ʧ��
BOOL KillProcess(DWORD dwPid, DWORD waitKillMs)  
{  
	HANDLE hPrc;  

	if( 0 == dwPid) return FALSE;  

	hPrc = OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwPid);  // Opens handle to the process.  

	if( !TerminateProcess(hPrc,0) ) // Terminates a process.  
	{  
		CloseHandle( hPrc );  
		return FALSE;  
	}  
	else  
		WaitForSingleObject(hPrc, waitKillMs); // At most ,waite 2000  millisecond.  

	CloseHandle(hPrc);  
	return TRUE;  
}  

//�������̽���, ���� TRUE �ɹ�����ʧ��
BOOL EnableDebugPrevilige(BOOL   fEnable) 
{ 
	BOOL   fOk   =   FALSE;         //   Assume   function   fails 
	HANDLE   hToken;
	if   (OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,   
		&hToken))
	{
		TOKEN_PRIVILEGES   tp; 
		tp.PrivilegeCount   =   1; 
		LookupPrivilegeValue(NULL,   SE_DEBUG_NAME,   &tp.Privileges[0].Luid); 
		tp.Privileges[0].Attributes   =   fEnable   ?   SE_PRIVILEGE_ENABLED   :   0; 
		AdjustTokenPrivileges(hToken,   FALSE,   &tp,   sizeof(tp),   NULL,   NULL); 
		fOk   =   (GetLastError()   ==   ERROR_SUCCESS); 
		CloseHandle(hToken); 
	} 
	return(fOk);
}

/************************************************************************/
/*  
���ݽ����� kill ����.
���� 2 ��ʾû�ҵ�����
���� 1 ��ʾ�رս���ʧ��
���� 0 ��ʾ�رճɹ�
/************************************************************************/
int KillProcessByName(const TCHAR *lpszProcessName) 
{  
	EnableDebugPrevilige(TRUE);
	unsigned int   pid = -1;  
	int    retval = 2;  

	if (lpszProcessName == NULL)  
		return -1;

	DWORD dwRet = 0;  
	HANDLE hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS,0 );  
	PROCESSENTRY32 processInfo;  
	processInfo.dwSize = sizeof( PROCESSENTRY32 );  
	int flag = Process32First( hSnapshot, &processInfo );  

	// Find the process with name as same as lpszProcessName  
	while (flag != 0)  
	{  
		if (strEqual(processInfo.szExeFile, lpszProcessName)) {  
			retval = 1;
			// Terminate the process.  
			pid = processInfo.th32ProcessID;  
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);  

			if (TerminateProcess(hProcess, 0) != TRUE) { // Failed to terminate it.  
				break;  
			}
			else
			{
				retval = 0;	//�رճɹ�
			}
		}  

		flag = Process32Next(hSnapshot, &processInfo);   
	} // while (flag != 0)  

	CloseHandle(hSnapshot);  
	EnableDebugPrevilige(FALSE);

	return retval;  
}

//�������ֲ��ҽ���
BOOL findProcess(const TCHAR *lpszProcessName) 
{  
	EnableDebugPrevilige(TRUE);
	unsigned int   pid = -1;  
	int    retval = 2;  

	if (lpszProcessName == NULL)  
		return -1;

	DWORD dwRet = 0;  
	HANDLE hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS,0 );  
	PROCESSENTRY32 processInfo;  
	processInfo.dwSize = sizeof( PROCESSENTRY32 );  
	int flag = Process32First( hSnapshot, &processInfo );  

	// Find the process with name as same as lpszProcessName  
	while (flag != 0)  
	{  
		if (strEqual(processInfo.szExeFile, lpszProcessName) ) {  
			return TRUE;
		}  

		flag = Process32Next(hSnapshot, &processInfo);   
	} // while (flag != 0)  

	CloseHandle(hSnapshot);  
	EnableDebugPrevilige(FALSE);

	return FALSE;  
}