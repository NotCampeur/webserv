# webserv
A 42 project about HTTP  

> :warning: **Warning**: It is educational project.  

> :warning: **Warning**: You can take inspiration from it but don't copy / paste what you don't understand.  

## Install  
You only need to run **make**.  
All libraries will be build and the binary will be ready to launch  

## Content
* A simple read/write communication HTTP server.  

## The Norm
<img align="center" src="Norm.png" alt="Screenshot of the project norm" />

### :zzz: TODO :zzz:  
*  End the work and merge to main  

### :boom: Known bugs.. I mean features :boom:  
* Getting "Relais brisé (pipe)" error sometimes when trying to read clients' requests.  

## :writing_hand: Change log :writing_hand:  
* Renaming request to client_request.  
* Adding multiple verbose rules to makefile to output debug.  
	Therefore I removed the verbose mode in server class.  
### Git status return :

        renommé :         Includes/Classes/request.hpp -> Includes/Classes/client_request.hpp
        modifié :         Includes/Classes/server.hpp
        modifié :         Makefile
        modifié :         README.md
        nouveau fichier : Srcs/Classes/ClientRequest/client_request.cpp
        supprimé :        Srcs/Classes/Request/request.cpp
        modifié :         Srcs/Classes/Server/server.cpp
        modifié :         Srcs/main.cpp
