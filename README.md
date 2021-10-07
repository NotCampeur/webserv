# webserv
A 42 project about HTTP  

> :warning: **Warning**: It is educational project.  

> :warning: **Warning**: You can take inspiration from it but don't copy / paste what you don't understand.  

## Install  
### Two way to use it :
* run **make** if you want to launch the server on your computer or if you don't have docker installed.
* From the root of the software, launch **./starters/build_run.sh**. You will then be in a docker container.  
  To launch the server inside the container you can do a classic **make**,  
  or launch **./starters/start_webserv.sh ressources/config/worpress.conf** to run a server where wordpress and mysql is running.

## Content
* A simple HTTP server.  
* There is a '--help' option which will guide you.  
* There is a default configuration file fully commented **ressources/config/webserv.conf**.  
* The accepted methods are GET POST HEAD and DELETE.  
* You will find a Dockerfile and scripts to launch the server inside of a container.  
 
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
* Nothing to be done.
### :boom: Known bugs.. I mean features :boom: 
* No bugs has been reported.
