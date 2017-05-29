struct NIL{};

class BaseArgs
{
public:
  virtual ~BaseArgs() {};
};

template <typename T1 = NIL, typename T2 = NIL>
class Args: public BaseArgs
{
public:
  Args() { }
  Args(T1 arg1)
  {
    arg1_ = arg1;
  }
  Args(T1 arg1, T2 arg2)
  {
    arg1_ = arg1;
    arg2_ = arg2;
  }
  T1 arg1_;
  T2 arg2_;
};

//! ===== Containers =====

class BaseContainer
{
public:
  virtual void Call(BaseArgs* args) = 0;
};

template <class DClass, typename DMethod>
class Container: public BaseContainer {};

template <class DClass>
class Container<DClass, void (DClass::*)(void)>: public BaseContainer
{
typedef void (DClass::* DMethod)(void);
public:
  Container(DClass* cls, DMethod method)
  {
    cls_ = cls;
    method_ = method;
  }
  void Call( BaseArgs* args )
  {
    (cls_->*method_)();
  }
private:
  DClass* cls_;
  DMethod method_;
};


template <class DClass, class A1>
class Container<DClass, void (DClass::*)(A1)>: public BaseContainer
{
typedef void (DClass::* DMethod)(A1);
public:
  Container(DClass* cls, DMethod method)
  {
    cls_ = cls;
    method_ = method;
  }
  void Call( BaseArgs* args )
  {
    Arg_* arg = dynamic_cast<Arg_*>(args);
    if (arg)
      (cls_->*method_)(arg->arg1_);
  }
private:
  typedef Args<A1> Arg_;
  DClass* cls_;
  DMethod method_;
};

template <class DClass, class A1, class A2>
class Container<DClass, void (DClass::*)(A1, A2)>: public BaseContainer
{
typedef void (DClass::* DMethod)(A1, A2);
public:
  Container(DClass* cls, DMethod method)
  {
    cls_ = cls;
    method_ = method;
  }
  void Call( BaseArgs* args )
  {
    Arg_* arg = dynamic_cast<Arg_*>(args);
    if (arg)
      (cls_->*method_)(arg->arg1_, arg->arg2_);
  }
private:
  typedef Args<A1,A2> Arg_;
  DClass* cls_;
  DMethod method_;
};
//! ===== Delegate =====

class Delegate
{
public:
  Delegate()
  {
    container_ = nullptr;
  }
  ~Delegate()
  {
    if (container_)
      delete container_;
  }

  void operator()()
  {
    Args<> arg = Args<>();
    container_->Call( &arg );
  }

  template <class T1>
  void operator()(T1 arg1)
  {
    container_->Call( & Args<T1>(arg1) );
  }

  template <class T1, class T2>
  void operator()(T1 arg1, T2 arg2)
  {
    container_->Call( & Args<T1,T2>(arg1, arg2) );
  }

  template <class DClass, typename DMethod>
  void Connect(DClass* cls, DMethod method)
  {
    if (container_)
      delete container_;
    container_ = new Container<DClass, DMethod>(cls, method);
  }

private:
  BaseContainer* container_;
};
