#ifndef KLOG_H
#define KLOG_H

#define LOG_INFO(str) klog.info(str,__FILE__,__LINE__)
#define LOG_ERROR(str, errorCode) klog.error(str,errorCode,__FILE__,__LINE__)

#include <fstream>
#include <time.h>
using namespace std;

class KLog
{
public :
	KLog(const char* filePath)
		:filePath(filePath)
	{
		curDate[0] = 0;
		dayCutIfNeed();
	}

	void error(const char* str, int errorCode,const char* srcFile, int srcLine)
	{
		dayCutIfNeed();
		char curtime[32];
		formatCurrentTime(curtime);
		ofile << "[ERROR]" << "[" << curtime << "] " << formatFileName(srcFile) << ":" << srcLine <<" "<< str << errorCode << std::endl;
	}

	void info(const char* str, const char* srcFile, int srcLine)
	{
		dayCutIfNeed();
		char curtime[32];
		formatCurrentTime(curtime);
		ofile << "[INFO]" << "[" << curtime << "] " << formatFileName(srcFile) << ":" << srcLine <<" " << str << std::endl;
	}

	~KLog()
	{
		ofile.close();
	}
private:
	void formatCurrentTime(char *curTimeStr)
	{
		time_t time_seconds = time(0);	
		struct tm now_time;	
		localtime_s(&now_time,&time_seconds);

		strftime(curTimeStr, 20, "%Y-%m-%d %H:%M:%S",&now_time);
	}

	const char* formatFileName(const char* fileName)
	{
		return fileName + lastSlashPos(fileName) + 1;
	}

	void getCurDate(char *curDate)
	{
		time_t time_seconds = time(0);
		struct tm now_time;	
		localtime_s(&now_time,&time_seconds);

		//	int dwsize = strftime(curDate, 20, "%Y-%m-%d-%H-%M",&now_time);
		int dwsize = strftime(curDate, 20, "%Y-%m-%d",&now_time);
	}

	void dayCutIfNeed()
	{
		char valatileCurDate [32] = {0};
		getCurDate(valatileCurDate);
		if(0 != strcmp(valatileCurDate,curDate))
		{
			//·¢ÉúÈÕÇÐ			

			if(0 != curDate[0])
			{
				char curtime[32];
				formatCurrentTime(curtime);
				ofile << "[INFO]" << "[" << curtime << "] " << formatFileName(__FILE__) << ":" << __LINE__ <<" " << "___________________day cut__________________" << std::endl;
				ofile.close();
			}

			getCurDate(curDate);

			char realLogFile [256] = {0};
			sprintf_s(realLogFile,255,"%s_%s",filePath,curDate);

			ofile.open(realLogFile, ios::app);
		}
	}
	ofstream ofile;
	char curDate[32];
	const char *filePath;
};

KLog klog("./log.txt");

#endif