#include "Utils.h"
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <sstream>
#include "Utils.h"
using namespace std;

vector<string> SplitStringWithWhiteSpace(string sInput)
{
	vector<string>	sTokens;
	string buf;
	stringstream ss(sInput);
	while(ss >> buf)
	{
		sTokens.push_back(buf);
		return sTokens;
	}
}

unsigned int HexStringToInt(char* str)
{
	unsigned int result = 0;

	// remove 0x
	str += 2;

	while(*str)
	{
		result = result * 16 + *str - (*str <= '9'?'0':(*str > 'Z')?'a' - 10:'A' - 10);
		++str;
	}

	return result;
}

int ReadLine(char* pSrc, char* pDest, int offset)
{
	int i = 0;
	while(pSrc[offset] != '\n' && pSrc[offset] != '\0')
	{
		pDest[i] = pSrc[offset];
		++offset;
		++i;
	}
	pDest[i] = '\0';
	return offset + 1;
}

float RandomFloat(float min, float max)
{
	float lerp = (rand() % 1001) / 1000.0f ;
	return min * (1.0f - lerp) + max * lerp;
}

int ConvertStringToInt(string sInput)
{
	int value = atoi(sInput.c_str());
	return value;
}

void StringToLowerCase( char* str, char*& dest )
{
	int i=0;
	char c;
	while (str[i])
	{
		c=str[i];
		putchar (tolower(c));
		i++;
	}
}
