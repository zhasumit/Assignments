#include <iostream>
#include "example.hh"

class HelloWorldImpl : public POA_Example::HelloWorld {
public:
    virtual char* sayHello() {
        return CORBA::string_dup("Hello from C++ server!");
    }
};

int main(int argc, char** argv) {
    try {
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
        CORBA::Object_var poaObj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(poaObj);
        PortableServer::POAManager_var poaManager = poa->the_POAManager();
        HelloWorldImpl* helloWorldImpl = new HelloWorldImpl();
        PortableServer::ObjectId_var myObjId = poa->activate_object(helloWorldImpl);
        CORBA::Object_var helloWorldObj = poa->id_to_reference(myObjId);
        Example::HelloWorld_var helloWorld = Example::HelloWorld::_narrow(helloWorldObj);
        poaManager->activate();
        orb->run();
    } catch (CORBA::Exception& e) {
        std::cerr << "Exception: " << e._name() << ": " << e._rep_id() << std::endl;
        return 1;
    }
    return 0;
}
