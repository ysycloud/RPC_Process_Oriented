#include "tools.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "services.h"
#include <rpc/rpc.h>
#include <rpc/types.h>

int HashString(char *str ,int numBins)
{
	short cntr = 0;
	long sum = 0;

	while(str[cntr]!='\0')
		sum = (31 * sum) + str[cntr++];

	return (int) (sum % numBins);
}

int findEmptyPos(struct func *funcs,char *name, int numBins)
{
	int initpos = HashString(name,numBins);
	int count = 0;
	while(funcs[initpos].flag == 1)
	{
		initpos = (initpos + 1)%numBins;
		count++;
		if(count==numBins)
			return -1;    //hash表已经全满  
	}		
	return initpos;
}


int findFunction(struct func *funcs,char *name,int numBins)
{
	int initpos = HashString(name,numBins);
	int count = 0;
	while(strcmp(funcs[initpos].name,name)!=0)
	{
		initpos = (initpos + 1)%numBins;
		count++;
		if(count==numBins)
			return -1;    //hash表没有该记录  
	}		
	return initpos;
}

void decodeFunc(char *str,char *funcName,char *paraList)
{
	XDR xdrs;
			
	xdrmem_create(&xdrs,str,SEND_MAX,XDR_DECODE);
	xdr_string(&xdrs,&funcName,FUNC_MAX);
	xdr_string(&xdrs,&paraList,SEND_MAX-FUNC_MAX-1);
}

void spiltStr(char *str, char params[PARAM_MAX][PARAM_LEN] , int *num)
{
	*num = 0;
	int count;
	while((*str)!='\0')
	{
		count = 0;
		for(;((*str)!=',')&&((*str)!='\0');str++)
			params[*num][count++] = (*str);
		params[(*num)++][count] = '\0';
		
		if((*str)=='\0')
			break;
		else
			str++;					
	}
}

int isInt(char *str)
{
	while((*str)!='\0')
	{
		if((*str)<'0'||(*str)>'9')
		{
			return 0;
		}
		str++;
	}
	return 1;
}

int isFloat(char *str)
{
	int count=0;
	while((*str)!='\0')
	{
		if(((*str)<'0'||(*str)>'9')&&(*str)!='.')
		{
			return 0;
		}
		if((*str)=='.')
		{
			count++;
			if(count>1)  //多余一个点号也不是浮点数
				return 0;
		}
		str++;
	}
	return 1;
}