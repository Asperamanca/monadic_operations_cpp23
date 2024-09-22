#include <functional>
#include "../common/printutils.h"

// Shows the purpose of std::forward
// When we write wrappers around functions, we need to pass their arguments perfectly
//  Otherwise, we get cases where calling the function with the wrapper behaves differently
//  than just calling the function directly.
//  Behaves differently can mean:
//  - Code that should compile no longer compiles
//  - We can call functions through the wrapper that we couldn't call directly (masking mistakes)
//  - We call the wrong overload of a function when passing through the wrapper

// First, we create a list of test subject functions
// We'll test calling those without wrapper first, then with different wrappers

// Accept a value, makes a copy
void fooValue(int value)
{
    // printlnWrapper("fooValue called");
}

// Accepts a const reference
void fooConstRef(const int& value)
{
    // printlnWrapper("fooConstRef called");
}

// Accepts an lvalue (=writable) reference
void fooLValue(int& value)
{
    // printlnWrapper("fooLValue called");
    value+=1;
}

// Accepts an rvalue reference (such as e.g. a literal number)
void fooRValue(int&& value)
{
    // printlnWrapper("fooRValue called");
}


// Level 1: We call the function directly, without any wrapper
void testCallDirectly()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    printlnWrapper("testCallDirectly2");

    // fooValue
    {
        printlnWrapper("call fooValue");
        fooValue(value);
        fooValue(valueConstRef);
        fooValue(valueLValue);
        fooValue(42);
        // Accepts all versions, makes a copy
    }

    // fooConstRef
    {
        printlnWrapper("call fooConstRef");
        fooConstRef(value);
        fooConstRef(valueConstRef);
        fooConstRef(valueLValue);
        fooConstRef(42);
        // Accepts all versions, holds a const&
    }

    // fooLValue
    {
        printlnWrapper("call fooLValue");
        fooLValue(value);
        // fooLValue(valueConstRef);    // Doesn't compile
        fooLValue(valueLValue);
        // fooLValue(42);               // Doesn't compile
        // Only version which receive an LValue reference are accepted
    }

    // fooRValue
    {
        printlnWrapper("call fooRValue");
        // fooRValue(value);            // Doesn't compile
        // fooRValue(valueConstRef);    // Doesn't compile
        // fooRValue(valueLValue);      // Doesn't compile
        fooRValue(42);
        // Only version with RValue (e.g. literal number) is accepted
    }
}

// Level 2: Use a wrapper which accepts the parameter by value and passes it by value
//  This will always make a copy and pass that
// (Don't be confused by the std::forward<TCall> - that's just for the function itself
//  and this is the same for all wrappers)
// ISSUES:
//  - Changes to writable references are only applied to a copy
//  - Unnecessary copies in many cases
//  - Cannot handle functions that only accept rvalue references (int&&)

template<class TCall>
void wrapperByValue(TCall&& fCall, auto param)
{
    printlnWrapper("wrapperByValue param type: {:}",formatTypeInfo<decltype(param)>());
    std::invoke(std::forward<TCall>(fCall), param);
}

void testWrapperByValue()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    printlnWrapper("testWrapperByValue");

    // fooValue
    {
        printlnWrapper("pass fooValue");
        wrapperByValue(fooValue,value);
        wrapperByValue(fooValue,valueConstRef);
        wrapperByValue(fooValue,valueLValue);
        wrapperByValue(fooValue,42);
        // Still works - copies are created
    }

    // fooConstRef
    {
        printlnWrapper("pass fooConstRef");
        wrapperByValue(fooConstRef,value);
        wrapperByValue(fooConstRef,valueConstRef);
        wrapperByValue(fooConstRef,valueLValue);
        wrapperByValue(fooConstRef,42);
        // The wrapper makes a copy first, which is then accepted by all versions of foo
    }

    // fooLValue
    {
        printlnWrapper("pass fooLValue");
        wrapperByValue(fooLValue,value);
        wrapperByValue(fooLValue,valueConstRef);    // Shouldn't compile, but does; creates a copy
        wrapperByValue(fooLValue,valueLValue);
        wrapperByValue(fooLValue,42);               // Shouldn't compile, but does; 42 is converted to value
        // The wrapper makes a copy first, which is then accepted by all versions of foo
        // However, changes to the reference made in fooLValue would be lost!
    }

    // fooRValue
    {
        printlnWrapper("pass fooRValue");
        // wrapperByValue(fooRValue,value);            // Doesn't compile
        // wrapperByValue(fooRValue,valueConstRef);    // Doesn't compile
        // wrapperByValue(fooRValue,valueLValue);      // Doesn't compile
        // wrapperByValue(fooRValue,42);               // Doesn't compile (but should)
        // Not even fooRValue compiles now!
    }
    // --> Error-prone: Copies suggest that LValue references work
    //  Also, fooRValue no longer works with RValues
    //  and unnecessary copies are made in multiple places
}


// Level 3: Take parameter by const reference and pass it
// This will avoid extra copies
// ISSUES:
//  - Cannot handle functions that only accept lvalue references (int&)
//  - Cannot handle functions that only accept rvalue references (int&&)

template<class TCall>
void wrapperByConstRef(TCall&& fCall, const auto& param)
{
    printlnWrapper("wrapperByConstRef param type: {:}",formatTypeInfo<decltype(param)>());
    std::invoke(std::forward<TCall>(fCall), param);
}

void testWrapperByConstRef()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    printlnWrapper("testWrapperByConstRef");

    // fooValue
    {
        printlnWrapper("pass fooValue");
        wrapperByConstRef(fooValue,value);
        wrapperByConstRef(fooValue,valueConstRef);
        wrapperByConstRef(fooValue,valueLValue);
        wrapperByConstRef(fooValue,42);
        // Accepts all versions, passes const& first, then makes a copy on calling fooValue
    }

    // fooConstRef
    {
        printlnWrapper("pass fooConstRef");
        wrapperByConstRef(fooConstRef,value);
        wrapperByConstRef(fooConstRef,valueConstRef);
        wrapperByConstRef(fooConstRef,valueLValue);
        wrapperByConstRef(fooConstRef,42);
        // Accepts all versions, passes through a const&
    }

    // fooLValue
    {
        printlnWrapper("pass fooLValue");
        // wrapperByConstRef(fooLValue,value);            // Doesn't compile (but should)
        // wrapperByConstRef(fooLValue,valueConstRef);    // Doesn't compile
        // wrapperByConstRef(fooLValue,valueLValue);      // Doesn't compile (but should)
        // wrapperByConstRef(fooLValue,42);               // Doesn't compile
        // None of these can handle the const& provided by the wrapper
    }

    // fooRValue
    {
        printlnWrapper("pass fooRValue");
        // wrapperByConstRef(fooRValue,value);            // Doesn't compile
        // wrapperByConstRef(fooRValue,valueConstRef);    // Doesn't compile
        // wrapperByConstRef(fooRValue,valueLValue);      // Doesn't compile
        // wrapperByConstRef(fooRValue,42);               // Doesn't compile (but should)
        // None of these can handle the const& provided by the wrapper
    }

    // --> Accepts neither LValue nor RValue references, even cases that make sense
}

// Level 4: Take the parameter as a reference, then pass it
// Due to 'auto', the reference can be either a writable reference (int&),
//  or a const reference (const int&)
// This will avoid extra copies, but requires that the wrapper can modify the content of the reference
// ISSUES:
//  - Cannot handle functions that only accept rvalue references (int&&)

template<class TCall>
void wrapperByLValue(TCall&& fCall, auto& param)
{
    printlnWrapper("wrapperByLValue param type: {:}",formatTypeInfo<decltype(param)>());
    std::invoke(std::forward<TCall>(fCall), param);
}

void testWrapperByLValue()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    printlnWrapper("testWrapperByLValue");

    // fooValue
    {
        printlnWrapper("pass fooValue");
        wrapperByLValue(fooValue,value);
        wrapperByLValue(fooValue,valueConstRef);
        wrapperByLValue(fooValue,valueLValue);
        // wrapperByLValue(fooValue,42);                  // Doesn't compile (but should)
        // No longer accepts literal RValue
    }

    // fooConstRef
    {
        printlnWrapper("pass fooConstRef");
        wrapperByLValue(fooConstRef,value);
        wrapperByLValue(fooConstRef,valueConstRef);
        wrapperByLValue(fooConstRef,valueLValue);
        // wrapperByLValue(fooConstRef,42);                // Doesn't compile (but should)
        // No longer accepts literal RValue
    }

    // fooLValue
    {
        printlnWrapper("pass fooLValue");
        wrapperByLValue(fooLValue,value);
        // wrapperByLValue(fooLValue,valueConstRef);    // Doesn't compile
        wrapperByLValue(fooLValue,valueLValue);
        // wrapperByLValue(fooLValue,42);               // Doesn't compile
        // Works the same as direct calls
    }

    // fooRValue
    {
        printlnWrapper("pass fooRValue");
        // wrapperByLValue(fooRValue,value);            // Doesn't compile
        // wrapperByLValue(fooRValue,valueConstRef);    // Doesn't compile
        // wrapperByLValue(fooRValue,valueLValue);      // Doesn't compile
        // wrapperByLValue(fooRValue,42);               // Doesn't compile (but should)
        // None of these can handle the LValue provided by the wrapper
    }

    // --> Doesn't accept RValue references in any case, even those that make sense
}

// Level 5: Take the parameter as auto&& (=forwarding reference), then pass it as it is
// ISSUES:
//  - Inside the wrapper, 'param'  becomes an lvalue (since it has a name), therefore...
//  - Cannot handle functions that only accept rvalue references (int&&)
//  - Can call a function that only accepts lvalues when called with an rvalue

template<class TCall>
void wrapperForwardingRefNoForward(TCall&& fCall, auto&& param)
{
    printlnWrapper("wrapperForwardingRefNoForward param type: {:}",formatTypeInfo<decltype(param)>());
    std::invoke(std::forward<TCall>(fCall), param);
}


void testWrapperForwardingRefNoForward()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    printlnWrapper("testWrapperForwardingRefNoForward");

    // fooValue
    {
        printlnWrapper("pass fooValue");
        wrapperForwardingRefNoForward(fooValue,value);
        wrapperForwardingRefNoForward(fooValue,valueConstRef);
        wrapperForwardingRefNoForward(fooValue,valueLValue);
        wrapperForwardingRefNoForward(fooValue,42);
        //
    }

    // fooConstRef
    {
        printlnWrapper("pass fooConstRef");
        wrapperForwardingRefNoForward(fooConstRef,value);
        wrapperForwardingRefNoForward(fooConstRef,valueConstRef);
        wrapperForwardingRefNoForward(fooConstRef,valueLValue);
        wrapperForwardingRefNoForward(fooConstRef,42);
        //
    }

    // fooLValue
    {
        printlnWrapper("pass fooLValue");
        wrapperForwardingRefNoForward(fooLValue,value);
        // wrapperForwardingRefNoForward(fooLValue,valueConstRef);    // Doesn't compile
        wrapperForwardingRefNoForward(fooLValue,valueLValue);
        wrapperForwardingRefNoForward(fooLValue,42);    // This should not compile, but it does
        // Last one works because the int&& is turned into int& inside the wrapper
        //  (it has a name, 'param', inside the wrapper, so it is treated as an lvalue reference)
    }

    // fooRValue
    {
        printlnWrapper("pass fooRValue");
        // wrapperForwardingRefNoForward(fooRValue,value);            // Doesn't compile
        // wrapperForwardingRefNoForward(fooRValue,valueConstRef);    // Doesn't compile
        // wrapperForwardingRefNoForward(fooRValue,valueLValue);      // Doesn't compile
        // wrapperForwardingRefNoForward(fooRValue,42);               // Doesn't compile (but should)
        // Last one loses RValue characteristic due to lack of proper forwarding
    }

    // --> May incorrectly call functions that accept an lvalue when called with an rvalue
    //  Cannot handle rvalue functions correctly
}

// Level 6: Perfect forwarding
// We take a forwarding reference, and then esure it is passed on with unchanged characteristics
// ISSUES:
//  - None

template<class TCall>
void wrapperForwardingRefAndForward(TCall&& fCall, auto&& param)
{
    printlnWrapper("wrapperForwardingRefAndForward param type: {:}",formatTypeInfo<decltype(param)>());
    std::invoke(std::forward<TCall>(fCall), std::forward<decltype(param)>(param));
}

void testWrapperForwardingRefAndForward()
{
    int value{};
    const int& valueConstRef = value;
    int& valueLValue = value;

    printlnWrapper("testWrapperForwardingRefAndForward");

    // fooValue
    {
        printlnWrapper("pass fooValue");
        wrapperForwardingRefAndForward(fooValue,value);
        wrapperForwardingRefAndForward(fooValue,valueConstRef);
        wrapperForwardingRefAndForward(fooValue,valueLValue);
        wrapperForwardingRefAndForward(fooValue,42);
        // Accepts all versions, passes parameter unchanged, then makes a copy on calling fooValue
        // Same behavior as in a direct call to the functions
    }

    // fooConstRef
    {
        printlnWrapper("pass fooConstRef");
        wrapperForwardingRefAndForward(fooConstRef,value);
        wrapperForwardingRefAndForward(fooConstRef,valueConstRef);
        wrapperForwardingRefAndForward(fooConstRef,valueLValue);
        wrapperForwardingRefAndForward(fooConstRef,42);
        // Accepts all versions, passes parameter unchanged, then takes a const&
        // Same behavior as in a direct call to the functions
    }

    // fooLValue
    {
        printlnWrapper("pass fooLValue");
        wrapperForwardingRefAndForward(fooLValue,value);
        // wrapperForwardingRefAndForward(fooLValue,valueConstRef);    // Doesn't compile
        wrapperForwardingRefAndForward(fooLValue,valueLValue);
        // wrapperForwardingRefAndForward(fooLValue,42);               // Doesn't compile
        // Same behavior as in a direct call to the functions
    }

    // fooRValue
    {
        printlnWrapper("pass fooRValue");
        // wrapperForwardingRefAndForward(fooRValue,value);            // Doesn't compile
        // wrapperForwardingRefAndForward(fooRValue,valueConstRef);    // Doesn't compile
        // wrapperForwardingRefAndForward(fooRValue,valueLValue);      // Doesn't compile
        wrapperForwardingRefAndForward(fooRValue,42);
        // Same behavior as in a direct call to the functions
    }

    // --> Behaves exactly like direct calls to the functions
}

int main(int argc, char* argv[])
{
    testCallDirectly();                            // <== Shows expected behavior

    testWrapperByValue();
    testWrapperByConstRef();
    testWrapperByLValue();
    testWrapperForwardingRefNoForward();
    testWrapperForwardingRefAndForward(); // <== Only way to get identical behavior to testFoo!

    return 0;
}


