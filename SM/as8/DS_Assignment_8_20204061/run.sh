#!/bin/bash
BASEDIR=`dirname $0`
 
if [ "$#" -lt 1 ]
then
	echo "Usage $0 [server|interactive-client|client]"
	echo "Example: bash $0 server"
	echo
	echo "server: start Java server"
	echo "interactive-client: start Java interactive-client"
	echo "client: start C++ client"
	exit 1
fi

case "$1" in
"server")
	cd java
	java server.QuizServer -ORBInitRef NameService=corbaloc::localhost:4333/NameService
	;;
"interactive-client")
	cd java
	java client.QuizClientInteractive -ORBInitRef NameService=corbaloc::localhost:4333/NameService
	;;
"client")
	cd cpp
	./client -ORBInitRef NameService=corbaloc::localhost:4333/NameService
esac
