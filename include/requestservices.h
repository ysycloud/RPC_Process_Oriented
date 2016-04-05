#ifndef _MY_REQUESTSERVICES_H_
#define _MY_REQUESTSERVICES_H_

#define PORT 5678
#define FUNC_MAX 50
#define SEND_MAX 500
#define RETURN_MAX 500

void startRequest(char* funcName, char* paraList, char *ip, char *result);
void requestService(char* buf ,char *ip, char* result);

#endif
