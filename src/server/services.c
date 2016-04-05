#include "services.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char* sayHello(char myName[], int myAge)
{
	char *str = (char *)malloc(sizeof(char)*RETURN_MAX);
	sprintf(str,"Hello, %d years old %s \n\0",myAge,myName);
	return str;
}

int sum( int item1, int item2)
{
	return (item1+item2);
}

char* sayGoodbye(char myName[])
{
	char *str = (char *)malloc(sizeof(char)*RETURN_MAX);
	sprintf(str,"Goodbye %s, have a nice day! \n\0",myName);
	return str;
}