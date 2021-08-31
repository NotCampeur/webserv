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
*  Need to implement the locations on the request manager.  
*  You can configurate multiple configuration for the same server but the first one will always be apply for the moment. Need to modify the request class.  
* Renaming "host" into "ip" in the config to be less distrubing.  

### :boom: Known bugs.. I mean features :boom:  
* If the root in the config file is given without ending '/' the server will loop redirections of type 301.
## :writing_hand: Change log :writing_hand:  
* JsonParser branch has been merged.
