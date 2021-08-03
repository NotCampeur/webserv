# webserv
A 42 project about HTTP  

> :warning: **Warning**: It is educational project.  

> :warning: **Warning**: You can take inspiration from it but don't copy / paste what you don't understand.  

## Install  
You only need to run **make**.  
All libraries will be build and the binary will be ready to launch  

## Content
* A simple HTTP server.  
 
## Resources  
* https://www.ibm.com/docs/en/i/7.2?topic=designs-using-poll-instead-select     <-Different API explanation  
* https://www.restapitutorial.com/httpstatuscodes.html  <-HTTP Return status  
* https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa      <-HTTP Server tuto  
 
 CGI:
* http://speed.eik.bme.hu/help/html/Special_Edition-Using_CGI/ch1.htm <- Introduction to CGI
* http://www.whizkidtech.redprince.net/cgi-bin/tutorial  <- CGI basics
* https://jkorpela.fi/forms/cgic.html  <- CGI programming tutorial
* https://www.garshol.priv.no/download/text/http-tut.html <- HTTP and CGI explained
 
 Reactor pattern:
* http://www.dre.vanderbilt.edu/~schmidt/PDF/reactor-siemens.pdf  
 
## [The Norm](.readme/norm.md)  

### :zzz: TODO :zzz:
*  Parsing of Hexadecimal values in URL -> in validator class
*  Comment each methods  
*  Need to manage the route in the config

### :boom: Known bugs.. I mean features :boom:  
* Getting "Relais brisé (pipe)" error sometimes when trying to read clients' requests.
* Valrgind throwing errors following SIGINT: seems to come from poll, as poll gets interupted by SIGINT (signal handler seems to be reset during poll call)
* When you try to get a file inside a file you get a 500 error. -> "[Tue Aug  3 20:03:05 2021] {ERROR} Error on stat call: Not a directory : 192.168.0.139"
## :writing_hand: Change log :writing_hand:  
* The headers' protection have been standardize.  
* Sources directories restructuring.  
* Fixed a SystemException bug, the class was not a correct derived class of std::exception.