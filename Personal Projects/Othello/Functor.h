#pragma once
// Functor classes "Borrrowed" from www.newty.de/fpt/functor.html
// abstract base class
template <typename T>
class TFunctor
{
public:

  // two possible functions to call member function. virtual cause derived
  // classes will use a pointer to an object and a pointer to a member function
  // to make the function call
  virtual void operator()(T val)=0;  // call using operator
  virtual void Call(T val)=0;        // call using function
};


// derived template class
template <class TClass, class ParamType> class TSpecificFunctor : public TFunctor<ParamType>
{
private:
	void (TClass::*fpt)(ParamType);   // pointer to member function
	TClass* pt2Object;                  // pointer to object

public:

	TSpecificFunctor()
	{ pt2Object = 0; fpt = 0;}

  // constructor - takes pointer to an object and pointer to a member and stores
  // them in two private variables
  TSpecificFunctor(TClass* _pt2Object, void(TClass::*_fpt)(ParamType))
     { pt2Object = _pt2Object;  fpt=_fpt; };

  // override operator "()"
  virtual void operator()(ParamType val)
   { (*pt2Object.*fpt)(val);};              // execute member function

  // override function "Call"
  virtual void Call(ParamType val)
    { (*pt2Object.*fpt)(val);};             // execute member function
};
