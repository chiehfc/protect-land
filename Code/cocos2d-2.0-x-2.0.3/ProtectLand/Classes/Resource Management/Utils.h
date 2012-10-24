#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<string> SplitStringWithWhiteSpace(string sInput);
unsigned int HexStringToInt(char* str);
int ReadLine(char* pSrc, char* pDest, int offset);
float RandomFloat(float min, float max);
int static ConvertStringToInt(string sInput);
void static StringToLowerCase(char* & str);

#endif