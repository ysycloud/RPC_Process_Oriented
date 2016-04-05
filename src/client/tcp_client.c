#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <rpc/rpc.h>
#include <rpc/types.h>
#include "requestservices.h"

void main(int argc ,char *argv[])
{
	
	if(argc<2)
	{
		printf("\n\tUsage:%s <IP_Addr>\n\n",argv[0]);
		exit(-1);
	}
	char ip[50],result[RETURN_MAX];
	//get vitals regarding remote server
	strncpy(ip,argv[1],sizeof(ip));
	
	char funcName[FUNC_MAX],paraList[SEND_MAX-FUNC_MAX];
	printf("input Service name(stop by enter exit):");
	scanf("%s",funcName);
		
	while(strcmp(funcName,"exit")!=0)
	{
		printf("input the paraList(split by ','):\n");
		scanf("%s",paraList);
		
		//请求方法并获得返回结果
		startRequest( funcName, paraList, ip, result);
	
		//对返回结果进行解码
		XDR xdrs;
		char buf[RETURN_MAX];
		char *p = buf;
		xdrmem_create(&xdrs,result,RETURN_MAX,XDR_DECODE);
		xdr_string(&xdrs,&p,RETURN_MAX);

		printf("result is :%s\n",buf);
		
		printf("input Service name:");
		scanf("%s",funcName);	
	}
	
}

