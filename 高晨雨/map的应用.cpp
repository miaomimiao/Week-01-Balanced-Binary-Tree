#include <iostream>
#include<stdio.h>
#include<algorithm>
#include<map>
#include<cstring>
//poj2503调用stl实现map的字典功能
#include<string>
#include<string.h>
using namespace std;

map<string,string>words;

int main()
{
	char str1[12],str2[12],str[30];
	int id=0;
	while(gets(str))
       {
           if(strlen(str)==0)
           break;
           sscanf(str,"%s %s",str1,str2);
           words[str2]=str1;
       }
	string str3;
	char ch,buf[12];
	while(scanf("%c",&ch))
	{
		if(isalpha(ch)) buf[id++]=ch;
		else{
			buf[id]='\0';
			id=0;
			if(words.find(buf)!=words.end()) cout<<words[buf]<<endl;
			else printf("eh\n");
			//putchar(ch);
		}
	}
	return 0;
}