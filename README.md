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

### :boom: Known bugs.. I mean features :boom:  
* If the root in the config file is given without ending '/' the server will loop redirections of type 301.
* Possibly lost on config errors.  
* When there is a request on / there is a huge loop on demultiplexer folowed by "{ERROR} CGI error - exit status:1".
* Config can have multiple location referring same path.
* Segfault when using curl -d -v "param1=value1&param2=value2" -X POST http://10.11.12.9:8080/ 
* Segfault when using nc to send requests. exemple :
* " nc 10.11.12.9 8080











YOLO


"
* When you full reload a big file, the server crash without any errors
## :writing_hand: Change log :writing_hand:  
* JsonParser branch has been merged.
