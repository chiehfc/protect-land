#include <stdio.h>
#include <string.h>
#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "cocos2d.h"
using namespace std;

CFileManager* CFileManager::s_Instance = NULL;
CFileManager::CFileManager()
{
}

CFileManager::~CFileManager()
{
}

char* CFileManager::GetFileContent(const char* path)
{
	FILE * pFile;
	long lSize;
	char* buffer = NULL;
	size_t result;

	pFile = fopen (path, "rb" );
	if (pFile==NULL) 
	{
		printf("Cannot open file %s\n", path);
		return NULL;
	}

	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	buffer = new char[sizeof(char)*lSize + 1];
	memset(buffer, 0, sizeof(char)*lSize + 1);

	if (buffer == NULL) 
	{
		printf ("Do not memory to allocate\n");
		return NULL;
	}

	result = fread (buffer,1,lSize,pFile);
	buffer[sizeof(char)*lSize] = '\0';
	
	fclose (pFile);
	return buffer;
}

CFileManager* CFileManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new CFileManager();
	return s_Instance;
}

void CFileManager::DestroyInstance()
{
	CC_SAFE_DELETE(s_Instance);
}

char*  CFileManager::getStringFile(const char* path)
{
	int iSize = getSizeFile(path);
	char* cData = new char[iSize];

	
	ifstream ifs(path);
	if(ifs.is_open())
	{
		ifs.read(cData, iSize);
	}

	ifs.close();

	return cData;
}

int CFileManager::getSizeFile(const char* path)
{
	ifstream myfile (path);
	int begin = myfile.tellg();
	myfile.seekg (0, ios::end);
	int end = myfile.tellg();
	myfile.close();
	return end - begin;
}

vector<string> CFileManager::getListLine(const char* path)
{
	vector<string> vtLines;
	ifstream ifs(path);
	if(ifs.is_open())
	{
		string sLine;
		while(!ifs.eof())
		{
			getline(ifs, sLine);
			vtLines.push_back(sLine);
		}
	}


	return vtLines;
	
}