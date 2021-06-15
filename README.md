# webserv
A 42 project about HTTP  

> :warning: **Warning**: It is educational project.  

> :warning: **Warning**: You can take inspiration from it but don't copy / paste what you don't understand.  

## Install  
You only need to run **make**.  
All libraries will be build and the binary will be ready to launch  

## Content
* A simple read/write communication HTTP server.  
 
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
*  Improve Logger (add a template or use ostringstream | Add a level of importance)
### :boom: Known bugs.. I mean features :boom:  
* Getting "Relais brisé (pipe)" error sometimes when trying to read clients' requests.
* Valrgind throwing errors following SIGINT: seems to come from poll, as poll gets interupted by SIGINT (signal handler seems to be reset during poll call)
* Server crash if restarted before socket becomes available again

## :writing_hand: Change log :writing_hand:  
* Logger class added.  
* Main tests improved.    

### Git status return :

        modifié :         Makefile
        modifié :         includes/webserv.hpp
        modifié :         includes/webserv_param.hpp
        supprimé :        srcs/classes/Reactor/ClientHandler.cpp
        supprimé :        srcs/classes/Reactor/ClientHandler.hpp
        supprimé :        srcs/classes/Reactor/HandlerTable.hpp
        supprimé :        srcs/classes/Reactor/IEventHandler.hpp
        modifié :         srcs/classes/client_request/ClientRequest.cpp
        nouveau fichier : srcs/classes/logger/Logger.cpp
        nouveau fichier : srcs/classes/logger/Logger.hpp
        modifié :         srcs/classes/reactor/ClientHandler.cpp
        modifié :         srcs/classes/reactor/ClientHandler.hpp
        renommé :         srcs/classes/Reactor/Demultiplexer.cpp -> srcs/classes/reactor/Demultiplexer.cpp
        renommé :         srcs/classes/Reactor/Demultiplexer.hpp -> srcs/classes/reactor/Demultiplexer.hpp
        renommé :         srcs/classes/Reactor/HandlerTable.cpp -> srcs/classes/reactor/HandlerTable.cpp
        modifié :         srcs/classes/reactor/HandlerTable.hpp
        modifié :         srcs/classes/reactor/IEventHandler.hpp
        renommé :         srcs/classes/Reactor/InitiationDispatcher.cpp -> srcs/classes/reactor/InitiationDispatcher.cpp
        renommé :         srcs/classes/Reactor/InitiationDispatcher.hpp -> srcs/classes/reactor/InitiationDispatcher.hpp
        renommé :         srcs/classes/Reactor/ServerHandler.cpp -> srcs/classes/reactor/ServerHandler.cpp
        renommé :         srcs/classes/Reactor/ServerHandler.hpp -> srcs/classes/reactor/ServerHandler.hpp
        supprimé :        srcs/classes/reactor/handlerTable.cpp
        modifié :         srcs/classes/server/Server.cpp
        modifié :         srcs/main.cpp
        modifié :         srcs/signals/sigint_handler.cpp
