#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "netdb.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <rpc/rpc.h>
#include <rpc/types.h>
#include <requestservices.h>

void startRequest(char* funcName, char* paraList, char *ip, char *result)
{	
	
	XDR xdrs;
	char buf[SEND_MAX];
	xdrmem_create(&xdrs, buf, SEND_MAX, XDR_ENCODE);
	xdr_string(&xdrs,&funcName,FUNC_MAX);
	xdr_string(&xdrs,&paraList,SEND_MAX-FUNC_MAX-1);
		
	requestService( buf , ip, result);
}

void requestService(char* buf ,char *ip, char* result)
{
	//send TCP packets to a remote server
	struct sockaddr_in sock;
	struct hostent *hp;
	int port = PORT;
	int fd;
	
	//get vitals regarding remote server
	if((hp = gethostbyname(ip))==NULL)
	{
		perror("Client:gethostbyname()");
		exit(-1);
	}

	//establish and initialize TCP stream socket structure
	if((fd = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("Client:SOCKET()");
		exit(-1);
	}
	memset((char*)&sock,0,sizeof(sock));
	memcpy(&sock.sin_addr,hp->h_addr,hp->h_length);
	sock.sin_family = hp->h_addrtype;
	sock.sin_port = htons(port);
	
	//connect to the remote server
	if(connect(fd,(struct sockaddr*)&sock,sizeof(sock))<0)
	{
		perror("client: connect()");
		return;
	}

	//send a message typed from interactive user to remote server
	fflush(stdout);	
	if(send(fd,buf,SEND_MAX,0) < 0)
	{
		perror("client: send()");
		return;
	}
		
	if(recv(fd,result,RETURN_MAX,0)<0)
	{
		perror("Child: rev()");
		close(fd);
		return;
	}
	close(fd);
}