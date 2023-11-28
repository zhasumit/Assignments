import Example.*;

public class Client {
    public static void main(String[] args) {
        try {
            org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init(args, null);
            org.omg.CORBA.Object obj = orb.string_to_object("corbaname::localhost:1050#HelloWorld");
            HelloWorld helloWorld = HelloWorldHelper.narrow(obj);
            String result = helloWorld.sayHello();
            System.out.println("Message from server: " + result);
        } catch (Exception e) {
            System.err.println("Exception: " + e);
            e.printStackTrace(System.out);
        }
    }
}
