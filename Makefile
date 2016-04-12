#programs,flags,etc.
INCLUDE	=	-I include
TARGET	=	bin/server bin/client 

#ALL Phony Targets
.PHONY:	everything	clean	all

#Default starting position
everything:	$(TARGET)
clean:	
	rm -f $(TARGET)
all:	clean everything
install: 
	install bin/* /usr/bin/

bin/server:	src/server/tcp_server.c	\
			src/server/services.c include/services.h	\
			src/server/preservices.c include/preservices.h	\
			src/server/tools.c include/tools.h
	gcc $(INCLUDE) -g -o bin/server src/server/tcp_server.c src/server/services.c src/server/preservices.c src/server/tools.c

bin/client:	src/client/tcp_client.c  \
			src/client/requestservices.c include/requestservices.h 			
	gcc $(INCLUDE) -g -o bin/client src/client/tcp_client.c src/client/requestservices.c