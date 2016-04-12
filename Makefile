#programs,flags,etc.
TARGET	=	server client 

#ALL Phony Targets
.PHONY:	everything	clean	all

#Default starting position
everything:	$(TARGET)
clean:	
	rm -f $(TARGET)
all:	clean everything

server:	src/tcp_server.c 
	gcc $(INCLUDE) -g -o server src/tcp_server.c 

client:	src/tcp_client.c  		
	gcc $(INCLUDE) -g -o client src/tcp_client.c