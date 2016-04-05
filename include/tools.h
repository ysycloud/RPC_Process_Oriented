#ifndef _MY_TOOLS_H_
#define _MY_TOOLS_H_

struct func
{
    char name[50];  //函数名
    char* (*f)(char *args);  //服务的入口地址
	int flag;  //该服务是否已经注册存在
};

int HashString(char *str ,int numBins);
int findEmptyPos(struct func *funcs,char *name, int numBins);
int findFunction(struct func *funcs,char *name, int numBins);
void decodeFunc(char *str,char *funcName,char *paraList);
void spiltStr(char *str, char params[20][50] , int *num);
int isInt(char *str);
int isFloat(char *str);

#endif
