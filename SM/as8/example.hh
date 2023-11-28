// This file is generated by omniidl (C++ backend)- omniORB_4_3. Do not edit.
#ifndef __example_hh__
#define __example_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_example
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_example
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_example
#endif






#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif



_CORBA_MODULE Example

_CORBA_MODULE_BEG

#ifndef __Example_mHelloWorld__
#define __Example_mHelloWorld__
  class HelloWorld;
  class _objref_HelloWorld;
  class _impl_HelloWorld;
  
  typedef _objref_HelloWorld* HelloWorld_ptr;
  typedef HelloWorld_ptr HelloWorldRef;

  class HelloWorld_Helper {
  public:
    typedef HelloWorld_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_HelloWorld, HelloWorld_Helper> HelloWorld_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_HelloWorld,HelloWorld_Helper > HelloWorld_out;

#endif

  // interface HelloWorld
  class HelloWorld {
  public:
    // Declarations for this interface type.
    typedef HelloWorld_ptr _ptr_type;
    typedef HelloWorld_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(::CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
    
    static _ptr_type _nil();

    static inline void _marshalObjRef(_ptr_type, cdrStream&);

    static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static inline _ptr_type _fromObjRef(omniObjRef* o) {
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static _core_attr const char* _PD_repoId;

    // Other IDL defined within this scope.
    
  };

  class _objref_HelloWorld :
    public virtual ::CORBA::Object,
    public virtual omniObjRef
  {
  public:
    // IDL operations
    char* sayHello();

    // Constructors
    inline _objref_HelloWorld()  { _PR_setobj(0); }  // nil
    _objref_HelloWorld(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_HelloWorld();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_HelloWorld(const _objref_HelloWorld&);
    _objref_HelloWorld& operator = (const _objref_HelloWorld&);
    // not implemented

    friend class HelloWorld;
  };

  class _pof_HelloWorld : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_HelloWorld() : _OMNI_NS(proxyObjectFactory)(HelloWorld::_PD_repoId) {}
    virtual ~_pof_HelloWorld();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_HelloWorld :
    public virtual omniServant
  {
  public:
    virtual ~_impl_HelloWorld();

    virtual char* sayHello() = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


_CORBA_MODULE_END



_CORBA_MODULE POA_Example
_CORBA_MODULE_BEG

  class HelloWorld :
    public virtual Example::_impl_HelloWorld,
    public virtual ::PortableServer::ServantBase
  {
  public:
    virtual ~HelloWorld();

    inline ::Example::HelloWorld_ptr _this() {
      return (::Example::HelloWorld_ptr) _do_this(::Example::HelloWorld::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_Example
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr



inline void
Example::HelloWorld::_marshalObjRef(::Example::HelloWorld_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}



#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_example
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_example
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_example
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_example
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_example
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_example
#endif

#endif  // __example_hh__
