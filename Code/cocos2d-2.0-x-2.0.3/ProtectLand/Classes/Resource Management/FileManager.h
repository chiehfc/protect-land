#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__


#include <fstream>
#include <vector>

using namespace std;

class CFileManager
{
protected:
	static CFileManager* s_Instance;

	CFileManager();
	CFileManager(const CFileManager&){}
	CFileManager& operator=(const CFileManager&){}
	virtual ~CFileManager();

public:
	// Methods
	char* GetFileContent(const char* path);
	static CFileManager* GetInstance();
	static void DestroyInstance();

public:
	static char*  getStringFile(const char* path);
	static int getSizeFile(const char* path);
	static vector<string>  getListLine(const char* path);
};
#endif