CC            = /usr/bin/g++
CPPFLAGS      = -g -c
LDFLAGS       = -g
OMNI_HOME     = /usr
OMNI_INCLUDES = -I$(OMNI_HOME)/include
OMNI_LIB_DIR  = $(OMNI_HOME)/lib
OMNIIDL       = omniidl
INCLUDES      = $(OMNI_INCLUDES)
LIBS          = -lomniORB4 -lomnithread -lomniDynamic4
OBJECTS       = QuizSK.o client.o

client: $(OBJECTS)
	$(CC) $(LDFLAGS) -o client $(OBJECTS) $(LIBS)

client.o: client.cpp
	$(CC) $(CPPFLAGS) client.cpp

QuizSK.o: QuizSK.cc
	$(CC) $(CPPFLAGS) QuizSK.cc

QuizSK.cc: ../Quiz.idl
	$(OMNIIDL) -bcxx ../Quiz.idl

clean:
	rm -rf *.o
	rm -rf *.hh
	rm -rf *SK.cc
	rm -rf client
