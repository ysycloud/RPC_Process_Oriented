#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "netdb.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "preservices.h"
#include "services.h"
#include "tools.h"
#include <rpc/rpc.h>
#include <rpc/types.h>

#define PORT 5678

const int SERVICES_MAX = 500;

void initServices(struct func *funcs);
void registerServices(struct func *funcs, char name[] , char* (*f)(char *));
void StartService(struct func *funcs);


void main()
{
	
	struct func funcs[SERVICES_MAX];
	initServices(funcs);
	
	//注册服务
	registerServices(funcs,"sayHello",pre_sayHello);
	registerServices(funcs,"sum",pre_sum);
	registerServices(funcs,"sayGoodbye",pre_sayGoodbye);
	
	//启动服务
	StartService(funcs);  
	
}

void initServices(struct func *funcs)
{
	int i;
	for(i=0;i<SERVICES_MAX;i++)
		funcs[i].flag = 0;
}

void registerServices(struct func *funcs, char name[] , char* (*f)(char *))
{
	int pos = findEmptyPos(funcs,name,SERVICES_MAX);
	if(pos==-1)
	{
		printf("no empty postion,can not register\n");
		return;
	}

	funcs[pos].f = f;
	strcpy(funcs[pos].name,name);
	funcs[pos].flag = 1;
}

void StartService(struct func *funcs)
{
	//print TCP packets from a remote client
	struct sockaddr_in sock;
	pid_t pid;
	int len = sizeof(sock);
	struct hostent *hp;
	int port = PORT;
	int acc,soc,tmp;
	
	//create server socket to accept a connection
	if((acc = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("Server:SOCKET()");
		exit(-1);
	}
	memset((char*)&sock,0,sizeof(sock));
	sock.sin_addr.s_addr = htonl(INADDR_ANY); //绑定自己的IP
	sock.sin_family = AF_INET;
	sock.sin_port = htons(port);
	
	if(bind(acc,(struct sockaddr*)&sock,len)<0)
	{
		perror("server:bind()");
		close(acc);
		exit(-1);
	}
	
	//await connection
	if(listen(acc,5)<0)
	{
		perror("Server: listen()");
		close(acc);
		exit(-1);
	}
	
	while(1)
	{
	//	printf("waiting for accept....!\n");
		if((soc = accept(acc,(struct sockaddr*)&sock,&len))<0)
		{
			perror("server: accept()");
			close(acc);
			exit(-1);
		}
	
		if((pid=fork())==0)
		{
			//子进程处理客户端请求
			char buffer[SEND_MAX];
	//		printf("soc:%d\n",soc);
			//echo message receive from client back to user
			if(recv(soc,buffer,sizeof(buffer),0)<0)
			{
				perror("Child: rev()");
				close(soc);
				exit(-1);
			}			
			
			//解码服务名		
			XDR xdrs;
			char funcName[FUNC_MAX];
			char *pfn = funcName;
			xdrmem_create(&xdrs,buffer,SEND_MAX,XDR_DECODE);
			xdr_string(&xdrs,&pfn,FUNC_MAX);	
					
			//查找并调用服务
			char result[RETURN_MAX];
			int pos = findFunction(funcs,funcName,SERVICES_MAX);
			if(pos!=-1)
			{
				printf("have service!\n");
				stpcpy(result,funcs[pos].f(buffer));
			}
			else
			{
				printf("No service!\n");
				stpcpy(result,"NO this Service!\0");
			}
			printf("function result is: %s\n",result);
			
			//对返回结果进行编码
			char *p = result;
			XDR xdrs1;
			char buf[RETURN_MAX];
			xdrmem_create(&xdrs1, buf, RETURN_MAX, XDR_ENCODE);
			xdr_string(&xdrs1,&p,RETURN_MAX);
			
			//返回结果
			if(send(soc,buf,RETURN_MAX,0) < 0)
			{
				perror("client: send()");
				close(soc);
				exit(-1);
			}
			close(soc);
		}
		else
			close(soc);
		
	}	
	close(acc);
}