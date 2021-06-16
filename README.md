# webserv
A 42 project about HTTP  

> :warning: **Warning**: It is educational project.  

> :warning: **Warning**: You can take inspiration from it but don't copy / paste what you don't understand.  

## Install  
You only need to run **make**.  
All libraries will be build and the binary will be ready to launch  

## Content
* A simple HTTP server.  
 
## Ressources  
* https://www.ibm.com/docs/en/i/7.2?topic=designs-using-poll-instead-select     <-Different API explanation  
* https://www.restapitutorial.com/httpstatuscodes.html  <-HTTP Return status  
* https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa      <-HTTP Server tuto  
 
 CGI:
* http://www.whizkidtech.redprince.net/cgi-bin/tutorial  <- CGI basics
* https://jkorpela.fi/forms/cgic.html  <- CGI programming tutorial
* https://www.garshol.priv.no/download/text/http-tut.html <- HTTP and CGI explained
 
 Reactor pattern:
* http://www.dre.vanderbilt.edu/~schmidt/PDF/reactor-siemens.pdf  
 
## [The Norm](.readme/norm.md)  

### :zzz: TODO :zzz:  
*  Comment each methods  
*  Standardize the headers' protection.  
*  Update setsockopt to be able to reuse sockets after program quits  
### :boom: Known bugs.. I mean features :boom:  
* Getting "Relais brisé (pipe)" error sometimes when trying to read clients' requests.
* Valrgind throwing errors following SIGINT: seems to come from poll, as poll gets interupted by SIGINT (signal handler seems to be reset during poll call)
* Server crash if restarted before socket becomes available again

## :writing_hand: Change log :writing_hand:  
* Logger class improved and commented.  

### Git status return :

        modified:   .gitignore
        modified:   srcs/classes/client_request/ClientRequest.cpp
        modified:   srcs/classes/logger/Logger.cpp
        modified:   srcs/classes/logger/Logger.hpp
        modified:   srcs/classes/reactor/ClientHandler.cpp
        modified:   srcs/classes/reactor/Demultiplexer.cpp
        modified:   srcs/classes/reactor/HandlerTable.cpp
        modified:   srcs/classes/reactor/InitiationDispatcher.cpp
        modified:   srcs/classes/reactor/ServerHandler.cpp
        modified:   srcs/classes/server/Server.cpp
        modified:   srcs/classes/server/Server.hpp
        modified:   srcs/main.cpp
