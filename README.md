# ParaGSEA
A common Implementation of process-oriented RPC mechanism

## Tools

this software is implemented by C, using socket to finish the network programming, and XDR to complete the extern encode.


### C Tools: c/

#### Requirements:
gcc compiler 

#### using by command line:
First you should enter the project directory , and then execute the "make all" to generate the executable file in /bin directory.
Then execute the "bin/server" to start up the server, and execute the "bin/client ip" any times to request the services in a parallel way. More details can be seen in related documents.