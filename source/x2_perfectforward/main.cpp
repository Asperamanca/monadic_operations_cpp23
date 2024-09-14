#include <functional>

void fooValue(int value)
{
}

void fooConstRef(const int& value)
{
}

void fooLValue(int& value)
{
    value+=1;
}

void fooRValue(int&& value)
{
}


void testFoo()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    // fooValue
    {
        fooValue(value);
        fooValue(valueConstRef);
        fooValue(valueLValue);
        fooValue(42);
        // Accepts all versions, makes a copy
    }

    // fooConstRef
    {
        fooConstRef(value);
        fooConstRef(valueConstRef);
        fooConstRef(valueLValue);
        fooConstRef(42);
        // Accepts all versions, holds a const&
    }

    // fooLValue
    {
        fooLValue(value);
        // fooLValue(valueConstRef);    // Doesn't compile
        fooLValue(valueLValue);
        // fooLValue(42);               // Doesn't compile
        // Only version which receive and LValue are accepted
    }

    // fooRValue
    {
        // fooRValue(value);            // Doesn't compile
        // fooRValue(valueConstRef);    // Doesn't compile
        // fooRValue(valueLValue);      // Doesn't compile
        fooRValue(42);
        // Only version with literal RValue is accepted
    }
}

template<class TCall>
void wrapperByValue(TCall&& fCall, auto param)
{
    std::invoke(std::forward<TCall>(fCall), param);
}

template<class TCall>
void wrapperByConstRef(TCall&& fCall, const auto& param)
{
    std::invoke(std::forward<TCall>(fCall), param);
}

template<class TCall>
void wrapperByLValue(TCall&& fCall, auto& param)
{
    std::invoke(std::forward<TCall>(fCall), param);
}

template<class TCall>
void wrapperForwardingRefNoForward(TCall&& fCall, auto&& param)
{
    std::invoke(std::forward<TCall>(fCall), param);
}

template<class TCall>
void wrapperForwardingRefAndForward(TCall&& fCall, auto&& param)
{
    std::invoke(std::forward<TCall>(fCall), std::forward<decltype(param)>(param));
}

void testWrapperByValue()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    // fooValue
    {
        wrapperByValue(fooValue,value);
        wrapperByValue(fooValue,valueConstRef);
        wrapperByValue(fooValue,valueLValue);
        wrapperByValue(fooValue,42);
        // No Change
    }

    // fooConstRef
    {
        wrapperByValue(fooConstRef,value);
        wrapperByValue(fooConstRef,valueConstRef);
        wrapperByValue(fooConstRef,valueLValue);
        wrapperByValue(fooConstRef,42);
        // The wrapper makes a copy first, which is then accepted by all versions of foo
    }

    // fooLValue
    {
        wrapperByValue(fooLValue,value);
        wrapperByValue(fooLValue,valueConstRef);    // Works now, but creates a copy
        wrapperByValue(fooLValue,valueLValue);
        wrapperByValue(fooLValue,42);               // Works now, 42 is converted to value
        // The wrapper makes a copy first, which is then accepted by all versions of foo
        // However, changes to the reference made in fooLValue would be lost
    }

    // fooRValue
    {
        // wrapperByValue(fooRValue,value);            // Doesn't compile
        // wrapperByValue(fooRValue,valueConstRef);    // Doesn't compile
        // wrapperByValue(fooRValue,valueLValue);      // Doesn't compile
        // wrapperByValue(fooRValue,42);               // Doesn't compile
        // Not even fooRValue compiles now!
    }
    // --> Error-prone: Copies suggest that LValue references work
    //  Also, fooRValue no longer works with RValues
}

void testWrapperByConstRef()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    // fooValue
    {
        wrapperByConstRef(fooValue,value);
        wrapperByConstRef(fooValue,valueConstRef);
        wrapperByConstRef(fooValue,valueLValue);
        wrapperByConstRef(fooValue,42);
        // Accepts all versions, passes const& first, then makes a copy on calling fooValue
    }

    // fooConstRef
    {
        wrapperByConstRef(fooConstRef,value);
        wrapperByConstRef(fooConstRef,valueConstRef);
        wrapperByConstRef(fooConstRef,valueLValue);
        wrapperByConstRef(fooConstRef,42);
        // Accepts all versions, passes through a const&
    }

    // fooLValue
    {
        // wrapperByConstRef(fooLValue,value);            // Doesn't compile
        // wrapperByConstRef(fooLValue,valueConstRef);    // Doesn't compile
        // wrapperByConstRef(fooLValue,valueLValue);      // Doesn't compile
        // wrapperByConstRef(fooLValue,42);               // Doesn't compile
        // None of these can handle the const& provided by the wrapper
    }

    // fooRValue
    {
        // wrapperByConstRef(fooRValue,value);            // Doesn't compile
        // wrapperByConstRef(fooRValue,valueConstRef);    // Doesn't compile
        // wrapperByConstRef(fooRValue,valueLValue);      // Doesn't compile
        // wrapperByConstRef(fooRValue,42);               // Doesn't compile
        // None of these can handle the const& provided by the wrapper
    }

    // --> Accepts neither LValue nor RValue references, even cases that make sense
}

void testWrapperByLValue()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    // fooValue
    {
        wrapperByLValue(fooValue,value);
        wrapperByLValue(fooValue,valueConstRef);
        wrapperByLValue(fooValue,valueLValue);
        // wrapperByLValue(fooValue,42);                  // Doesn't compile
        // No longer accepts literal RValue
    }

    // fooConstRef
    {
        wrapperByLValue(fooConstRef,value);
        wrapperByLValue(fooConstRef,valueConstRef);
        wrapperByLValue(fooConstRef,valueLValue);
        // wrapperByLValue(fooConstRef,42);                // Doesn't compile
        // No longer accepts literal RValue
    }

    // fooLValue
    {
        wrapperByLValue(fooLValue,value);
        // wrapperByLValue(fooLValue,valueConstRef);    // Doesn't compile
        wrapperByLValue(fooLValue,valueLValue);
        // wrapperByLValue(fooLValue,42);               // Doesn't compile
        // Works the same as direct calls
    }

    // fooRValue
    {
        // wrapperByLValue(fooRValue,value);            // Doesn't compile
        // wrapperByLValue(fooRValue,valueConstRef);    // Doesn't compile
        // wrapperByLValue(fooRValue,valueLValue);      // Doesn't compile
        // wrapperByLValue(fooRValue,42);               // Doesn't compile
        // None of these can handle the LValue provided by the wrapper
    }

    // --> Doesn't accept RValue references in any case, even those that make sense
}

void testWrapperForwardingRefNoForward()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    // fooValue
    {
        wrapperForwardingRefNoForward(fooValue,value);
        wrapperForwardingRefNoForward(fooValue,valueConstRef);
        wrapperForwardingRefNoForward(fooValue,valueLValue);
        wrapperForwardingRefNoForward(fooValue,42);
        // Accepts all versions, passes const& first, then makes a copy on calling fooValue
    }

    // fooConstRef
    {
        wrapperForwardingRefNoForward(fooConstRef,value);
        wrapperForwardingRefNoForward(fooConstRef,valueConstRef);
        wrapperForwardingRefNoForward(fooConstRef,valueLValue);
        wrapperForwardingRefNoForward(fooConstRef,42);
        // Accepts all versions, passes through a const&
    }

    // fooLValue
    {
        wrapperForwardingRefNoForward(fooLValue,value);
        // wrapperForwardingRefNoForward(fooLValue,valueConstRef);    // Doesn't compile
        wrapperForwardingRefNoForward(fooLValue,valueLValue);
        wrapperForwardingRefNoForward(fooLValue,42);
        // ???
    }

    // fooRValue
    {
        // wrapperForwardingRefNoForward(fooRValue,value);            // Doesn't compile
        // wrapperForwardingRefNoForward(fooRValue,valueConstRef);    // Doesn't compile
        // wrapperForwardingRefNoForward(fooRValue,valueLValue);      // Doesn't compile
        // wrapperForwardingRefNoForward(fooRValue,42);               // Doesn't compile
        // First three wouldn't compile anyway
        // Last one loses RValue characteristic due to lack of proper forwarding
    }

    // --> ???
}

void testWrapperForwardingRefAndForward()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    // fooValue
    {
        wrapperForwardingRefAndForward(fooValue,value);
        wrapperForwardingRefAndForward(fooValue,valueConstRef);
        wrapperForwardingRefAndForward(fooValue,valueLValue);
        wrapperForwardingRefAndForward(fooValue,42);
        // Accepts all versions, passes parameter unchanged, then makes a copy on calling fooValue
        // Same behavior as in a direct call to the functions
    }

    // fooConstRef
    {
        wrapperForwardingRefAndForward(fooConstRef,value);
        wrapperForwardingRefAndForward(fooConstRef,valueConstRef);
        wrapperForwardingRefAndForward(fooConstRef,valueLValue);
        wrapperForwardingRefAndForward(fooConstRef,42);
        // Accepts all versions, passes parameter unchanged, then takes a const&
        // Same behavior as in a direct call to the functions
    }

    // fooLValue
    {
        wrapperForwardingRefAndForward(fooLValue,value);            // Doesn't compile
        // wrapperForwardingRefAndForward(fooLValue,valueConstRef);    // Doesn't compile
        wrapperForwardingRefAndForward(fooLValue,valueLValue);      // Doesn't compile
        // wrapperForwardingRefAndForward(fooLValue,42);               // Doesn't compile
        // Same behavior as in a direct call to the functions
    }

    // fooRValue
    {
        // wrapperForwardingRefAndForward(fooRValue,value);            // Doesn't compile
        // wrapperForwardingRefAndForward(fooRValue,valueConstRef);    // Doesn't compile
        // wrapperForwardingRefAndForward(fooRValue,valueLValue);      // Doesn't compile
        wrapperForwardingRefAndForward(fooRValue,42);               // Doesn't compile
        // Same behavior as in a direct call to the functions
    }

    // --> Behaves exactly like direct calls to the functions
}

int main(int argc, char* argv[])
{
    testFoo();                            // <== Shows expected behavior

    testWrapperByValue();
    testWrapperByConstRef();
    testWrapperByLValue();
    testWrapperForwardingRefNoForward();
    testWrapperForwardingRefAndForward(); // <== Only way to get identical behavior to testFoo!


    return 0;
}


