#include "preservices.h"
#include "services.h"
#include "tools.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char* pre_sayHello(char *str)
{
	//解码
	char funcName[FUNC_MAX],ParaList[SEND_MAX-FUNC_MAX];
	decodeFunc(str,funcName,ParaList);
	
	printf("request: %s( %s )\n",funcName,ParaList);
	
	char myName[20];
	int myAge;
	
	//解析拆分参数列表字符串
	char params[PARAM_MAX][PARAM_LEN];
	int num; //参数个数
	spiltStr( ParaList, params , &num);
	
	//参数格式判断
	if(num!=2)
		return "the number of parameters is wrong!";	
	if(isInt(params[1])==0)
		return "the arg1 is wrong!"; 
	
	strcpy(myName,params[0]);
	myAge = atoi(params[1]);
		
	return sayHello(myName,myAge);
}


char* pre_sum(char *str)
{
	//解码
	char funcName[FUNC_MAX],ParaList[SEND_MAX-FUNC_MAX];
	decodeFunc(str,funcName,ParaList);
	
	printf("request: %s( %s )\n",funcName,ParaList);
	
	int item1,item2;
	
	//解析拆分参数列表字符串
	char params[PARAM_MAX][PARAM_LEN];
	int num; //参数个数
	spiltStr( ParaList, params , &num);
	
	//参数格式判断
	if(num!=2)
		return "the number of parameters is wrong!";	
	if(isInt(params[0])==0)
		return "the arg0 is wrong!";
	if(isInt(params[1])==0)
		return "the arg1 is wrong!";	
	
	item1 = atoi(params[0]);
	item2 = atoi(params[1]);
	char *sumstr = (char *)malloc(sizeof(char)*10);
	sprintf(sumstr,"%d",sum(item1,item2));
	return sumstr;
}

char* pre_sayGoodbye(char *str)
{
	//解码
	char funcName[FUNC_MAX],ParaList[SEND_MAX-FUNC_MAX];
	decodeFunc(str,funcName,ParaList);
	
	printf("request: %s( %s )\n",funcName,ParaList);
	
	//解析拆分参数列表字符串
	char params[PARAM_MAX][PARAM_LEN];
	int num; //参数个数
	spiltStr( ParaList, params , &num);
	
	char myName[20];
	//参数格式判断
	if(num!=1)
		return "the number of parameters is wrong!";	
	
	strcpy(myName,params[0]);
	
	return sayGoodbye(myName);
}