package Example;

/**
* Example/HelloWorldHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from example.idl
* Monday, 20 November, 2023 9:06:27 PM IST
*/

public final class HelloWorldHolder implements org.omg.CORBA.portable.Streamable
{
  public Example.HelloWorld value = null;

  public HelloWorldHolder ()
  {
  }

  public HelloWorldHolder (Example.HelloWorld initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = Example.HelloWorldHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    Example.HelloWorldHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return Example.HelloWorldHelper.type ();
  }

}
