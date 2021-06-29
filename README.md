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
*  Config file options and parsing
*  Requests handling
*  Timeout checks
### :boom: Known bugs.. I mean features :boom:  
* Getting "Relais brisé (pipe)" error sometimes when trying to read clients' requests.
* Valrgind throwing errors following SIGINT: seems to come from poll, as poll gets interupted by SIGINT (signal handler seems to be reset during poll call)

## :writing_hand: Change log :writing_hand:  
* The headers' protection have been standardize.  
* Sources directories restructuring.  

### Git status return :

        modified:   includes/webserv.hpp
        new file:   includes/webserv_sig_handler.hpp
        renamed:    srcs/classes/client/Client.cpp -> srcs/http/client_related/client/Client.cpp
        renamed:    srcs/classes/client/Client.hpp -> srcs/http/client_related/client/Client.hpp
        renamed:    srcs/classes/client_request/ClientRequest.cpp -> srcs/http/client_related/client_request/ClientRequest.cpp
        renamed:    includes/classes/ClientRequest.hpp -> srcs/http/client_related/client_request/ClientRequest.hpp
        renamed:    srcs/classes/reactor/ClientHandler.cpp -> srcs/http/handler/client_handler/ClientHandler.cpp
        renamed:    srcs/classes/reactor/ClientHandler.hpp -> srcs/http/handler/client_handler/ClientHandler.hpp
        renamed:    srcs/classes/reactor/HandlerTable.cpp -> srcs/http/handler/handler_table/HandlerTable.cpp
        renamed:    srcs/classes/reactor/HandlerTable.hpp -> srcs/http/handler/handler_table/HandlerTable.hpp
        renamed:    srcs/classes/reactor/IEventHandler.hpp -> srcs/http/handler/interface/IEventHandler.hpp
        renamed:    srcs/classes/reactor/ServerHandler.cpp -> srcs/http/handler/server_handler/ServerHandler.cpp
        renamed:    srcs/classes/reactor/ServerHandler.hpp -> srcs/http/handler/server_handler/ServerHandler.hpp
        renamed:    srcs/classes/reactor/Demultiplexer.cpp -> srcs/http/server_related/demultiplexer/Demultiplexer.cpp
        renamed:    srcs/classes/reactor/Demultiplexer.hpp -> srcs/http/server_related/demultiplexer/Demultiplexer.hpp
        renamed:    srcs/classes/reactor/InitiationDispatcher.cpp -> srcs/http/server_related/initiation_dispatcher/InitiationDispatcher.cpp
        renamed:    srcs/classes/reactor/InitiationDispatcher.hpp -> srcs/http/server_related/initiation_dispatcher/InitiationDispatcher.hpp
        renamed:    srcs/classes/server/Server.cpp -> srcs/http/server_related/server/Server.cpp
        renamed:    srcs/classes/server/Server.hpp -> srcs/http/server_related/server/Server.hpp
        renamed:    srcs/classes/logger/Logger.cpp -> srcs/logger/Logger.cpp
        renamed:    srcs/classes/logger/Logger.hpp -> srcs/logger/Logger.hpp
        modified:   srcs/main.cpp
