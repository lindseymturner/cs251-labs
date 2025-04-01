//
// Created by davew on 9/29/22.
//

#include <logic.h>    // HaverfordCS preconditions, etc.
#include "SafeInt.h"


#include <doctest.h>
// #include <climits>  // for, e.g., INT_MAX, which might be wanted in testing


// The boring, repetitive part of setting up _member_ and _friend_ functions was done by
//   right-clicking in this file in C-Lion, and choosing "Generate -> Generate Definitions"
//   and then choosing either the class name (for members) or "top-level functions" (for friends, etc.)
//   and then selecting all the ones we want

SafeInt::SafeInt(int i) {
    if (i > SafeInt::MAX or i < SafeInt::MIN) {
        throw std::domain_error("Illegal Safe Int value during initialization");
    }
    this->theValue = i;    // We _strongly_ recommend you put "this->" for all initializations in constructor
    // same as   (*this).theValue = i;
    // but _not_  *this .theValue = i;
    // and _not_   this .theValue = i;
    // ToDo: Understand why the above two are wrong

    postcondition(this->repInv());
}

/*
  * We could choose to provide automatic initialization to 0, with the following

SafeInt::SafeInt()
{

 this->theValue = 0;
 postcondition(this->repInv());
}

  * but we are leaving them potentially un-initialized, as with C/C++ "int" variables,
  * with "=default" in the class.
  */

// A method to type-cast a SafeInt into type "int" ...
//  since we can't create a constructor for class int, we create an "operator int" for class SafeInt
SafeInt::operator int() const {
    // could throw bad_cast exception, except that can't happen since SafeInt must be in bounds :-)
    return this->theValue;
}

TEST_CASE("SafeInt initializing constructor and casting-back operator int")
{
    CHECK(int(SafeInt(0))  == 0);
    CHECK(int(SafeInt(42)) == 42);
    CHECK_THROWS(SafeInt(SafeInt::MAX + 5)); // OK as long as SafeInt::MAX isn't too close to max. int
}


bool SafeInt::repInv() const {
    return this->theValue <= SafeInt::MAX and this->theValue >= SafeInt::MIN;
}


// This isn't a method, so no "this" pointer is available.
// But, it is listed in the class (as "friend", so it does have access to private fields)
// Defining non-mutating operators as friends allows implicit type-casting of both operands
SafeInt operator+(const SafeInt &lhs, const SafeInt &rhs) {
    // ToDo: figure out how to check for overflow better than this,
    //       if we want to use MAXINT as SafeInt::MAX
    //       (at the moment, lhs+rhs can "wrap around" and appear not to be > MAX, even when it is)
    if (lhs.theValue+rhs.theValue > SafeInt::MAX or lhs.theValue + rhs.theValue < SafeInt::MIN) {
        throw std::domain_error("Value out of range in SafeInt addition");
    }
    return SafeInt(lhs.theValue + rhs.theValue);
}
TEST_CASE("SafeInt addition")
{
    CHECK(int(SafeInt(0)  + SafeInt(0))  == 0);
    CHECK(int(SafeInt(42) + SafeInt(0))  == 42);
    CHECK(int(SafeInt(25) + SafeInt(17)) == 42);
    SafeInt i = 25, j = 17;
    CHECK(int(i + j)  == 42);
    CHECK(int(i)  == 25);  // i + j must _not_ change i
    CHECK(int(j)  == 17);  // i + j must _not_ change j

    CHECK_THROWS(SafeInt(SafeInt::MAX-1) + SafeInt(5));
}

// Operator+= is in the class without "friend", so it's a method
// It gets access and has a "this" object (the left-hand side, in a += b)
// Defining mutator operators as methods prevents implicit type-casting of the left-hand side
// Note that, in C and C++, assignment operations are "right-associative" and produce a reference to their lhs, so
//      a = b = c = d+e;
//   is the same as
//      a = (b = (c = d+e));
//   is the same as
//      c = d+e;
//      b = c;
//      a = b;
SafeInt &SafeInt::operator+=(const SafeInt &rhs) {
    // The not-too-weird-looking version of the quick-and-easy way to do +=
    SafeInt sum= (*this) + rhs;  // use operator + above
    (*this) = sum;
    postcondition(this->repInv());
    return *this;
    // The concise-and-clever version for confident C/C++ programmers
    // return (*this) = (*this) + rhs);  // use the "assignment produces a reference to lhs" property
}
TEST_CASE("SafeInt add-assign")
{
    SafeInt i = 0;
    CHECK(int(i)  == 0);
    i += 25;
    CHECK(int(i)  == 25);
    SafeInt j = 17;
    CHECK(int(i += j) == 42);  // i += j is the sum, like i+j ...
    CHECK(int(i)  == 42);      //        ... but also changes i
    CHECK(int(j)  == 17);      // i += j must _not_ change j

    CHECK_THROWS(i+=SafeInt(SafeInt::MAX - 42 + 1));
}



// The subtraction operators are pretty much like the additions, but say "-"...
SafeInt operator-(const SafeInt &lhs, const SafeInt &rhs) {
    // ToDo: figure out how to check for overflow better than this,
    //       if we want to use MAXINT as SafeInt::MAX
    //       (at the moment, lhs+rhs can "wrap around" and appear not to be > MAX, even when it is)
    if (lhs.theValue-rhs.theValue > SafeInt::MAX or lhs.theValue - rhs.theValue < SafeInt::MIN) {
        throw std::domain_error("Value out of range in SafeInt addition");
    }
    return SafeInt(lhs.theValue - rhs.theValue);
}
SafeInt &SafeInt::operator-=(const SafeInt &rhs) {
    // The not-too-weird-looking version of the quick-and-easy way to do +=
    SafeInt sum= (*this) - rhs;  // use operator - above
    (*this) = sum;
    postcondition(this->repInv());
    return *this;
}
TEST_CASE("SafeInt subtraction and subtract-assign")
{
    SafeInt i = 13, j = 37;
    CHECK(int(i - SafeInt(0))  == 13);
    CHECK(int(i - SafeInt(1))  == 12);
    CHECK(int(j-i) == 37-13);
    CHECK(int(i)  == 13);  // j-i must _not_ change i
    CHECK(int(j)  == 37);  // j-i must _not_ change j
    CHECK(int(j -= 0) == 37);
    CHECK(int(j)      == 37);
    CHECK(int(j -= i) == 37-13);
    CHECK(int(j)      == 37-13);
    CHECK(int(i)      == 13);

    CHECK_THROWS(j-(37-13+1));
}



// Since this is supposed to work like a /= operation, we'll make it a method, like +=
SafeInt &SafeInt::divSet(const SafeInt &rhs) {
    (*this) = (div(*this, rhs));
    postcondition(this->repInv());
    return *this;
}
SafeInt div(const SafeInt &lhs, const SafeInt &rhs) {
    hccs_assert(SafeInt::MIN >= 0);  // @ToDo: need to fix the following if these can be < 0, due to C's "/" definition
    int quotient = lhs.theValue / rhs.theValue;
    return SafeInt(quotient);
    // or, just the one-line version below
    // return SafeInt( lhs.theValue / rhs.theValue );
}
SafeInt mod(const SafeInt &lhs, const SafeInt &rhs) {
    hccs_assert(SafeInt::MIN >= 0);  // @ToDo: need to fix the following if these can be < 0, due to C's "%" definition
    int remainder = lhs.theValue % rhs.theValue;
    return SafeInt(remainder);
}
double operator/(const SafeInt &lhs, const SafeInt &rhs) {
    return double(lhs.theValue)/double(rhs.theValue);
}

TEST_CASE("SafeInt integer and real-number division")
{
    SafeInt cookies = 19, kids = 4;
    CHECK(int(div(cookies, kids))  == 4);
    CHECK(int(mod(cookies, kids))  == 3);  // uh-oh, this can't work well, somebody gets left out.
    CHECK(cookies/ kids  == 4.75);                 // maybe each kid can have 4 + 3/4 cookies.

    CHECK(int(cookies)  == 19);
    CHECK(int(kids)     == 4);

    CHECK(int(cookies.divSet(kids)) == 4);
    CHECK(int(cookies)  == 4);
    CHECK(int(kids)     == 4);
    // perhaps it would be cool to have a function divAndSetToMod(x, y) that returns x/y and sets x to x%y


    // ToDo: Should have several exception-throwing tests here, for divide by zero, and maybe others
}


bool operator==(const SafeInt &lhs, const SafeInt &rhs) {
    return lhs.theValue == rhs.theValue;
}
bool operator!=(const SafeInt &lhs, const SafeInt &rhs) {
    return lhs.theValue != rhs.theValue;
}
TEST_CASE("SafeInt comparisons")
{
    SafeInt i = 7, j = 3;
    CHECK((i == i)  == true);
    CHECK((i == j)  == false);
    CHECK((j == i)  == false);
    CHECK((i == 7)  == true);  // just checking implicit casting, but, why not...
    CHECK((i != i)  == false);
    CHECK((i != j)  == true);
    CHECK((j != i)  == true);
    CHECK((i != 7)  == false);  // just checking implicit casting, but, why not...

    CHECK(int(i)  == 7);
    CHECK(int(j)  == 3);
}


// Streams return a reference to the stream they used, but are left-associative, so
//      cout << x << y << endl;
//   is the same thing as
//      ((cout << x) << y) << endl;
//   is the same thing as
//      (cout << x);
//      (cout << y);
//      cout << endl;
std::ostream &operator<<(std::ostream &any_ostream, const SafeInt &printMe)             // output operation
{
    return any_ostream << int(printMe);  // ToDo: Think: Why is "cout" wrong here?  Why is "endl" inappropriate?
}
std::istream &operator>>(std::istream &any_istream, SafeInt &inputMe)             // input operation ... _changes_ the SafeInt object
{
    int readAnInt;  // we could also read characters and convert them...
    any_istream >> readAnInt;
    if (any_istream) { // only process input if we actually _got_ something
        if (readAnInt > SafeInt::MAX || readAnInt < SafeInt::MIN) {
            any_istream.setstate(std::ios::failbit);  // indicate failure
            hccs_assert(!any_istream); // setting failbit should make the stream count as false, e.g., for the stuff below
        } else {
            inputMe = SafeInt(readAnInt);
        }
    }
    return any_istream;
}

using std::cin, std::cout, std::endl, std::cerr;
#include <sstream>


TEST_CASE("SafeInt << and >> operations")
{
    std::istringstream read_this_42_and_17(std::string("42 17"));
    SafeInt fortyTwo, seventeen;  // possibly poor style not to initialize these, but we're about to read them...
    read_this_42_and_17 >> fortyTwo >> seventeen;

    CHECK(read_this_42_and_17);  // stream should still be valid, haven't read past end yet...
    CHECK(fortyTwo  == 42);  // uses SafeInt ==, but we did test that above
    CHECK(seventeen == 17);  // uses SafeInt ==, but we did test that above

    std::ostringstream save_numbers_here;
    save_numbers_here << "Here's 42: " << fortyTwo << " and here's 17: " << seventeen;
    CHECK(save_numbers_here.str() == "Here's 42: 42 and here's 17: 17");
    CHECK(fortyTwo  == 42);  // operator << shouldn't change fortyTwo
    CHECK(seventeen == 17);

    CHECK(!(read_this_42_and_17 >> fortyTwo)); // can't read any more from that empty stream
    CHECK(!read_this_42_and_17);  // stream should no longer be valid, after read-past-end
}



void SafeInt_Demo()
{
    cout << "Enter an integer, and I'll triple it until it makes me sad to do so." << endl;
    cout << "   (entering 0 stops the loop)" << endl;
    SafeInt n=0;
    while (cin >> n and n != 0) {  // Stops when cin fails, due to end-of-input or non-integer entered, or when n==0
        cout << "I read in the value " << n << ", time to start tripling!!!" << endl;
        try {
            while (true) { // run until error
                int one = 1;  // a regular int, to demonstrate casting below
                n = n+n+n;
                n = n + one;   // 1 gets implicitly cast to SafeInt to provide a const SafeInt& parameter to operator+
                n = one + n;   // works for left or right-hand side ... we could use 1 rather than one, throughout
                n += one;      // works for right-hand side of operator+=
            //  one += n;      // does not work for left-hand side of operator+=, because that's a non-const member
                n -= 3;       // go back down so we're just tripling, i.e., take of the " + one", etc., above
                cout << "Managed to triple it and get " << n << endl;
            }
        } catch (std::domain_error &e) {
            cout << "Aha! I thought so ... eventually we got domain_error" << endl;
        } catch (const char *complaint) {
            cout << "Current version should throw proper exceptions like domain_error, not C-style strings like" << complaint << endl;
        } catch (const std::string &complaint) {
            cout << "Current version should throw proper exceptions like domain_error, not std::strings like" << complaint << endl;
        } catch (...) {
            cerr << "Wait, what?  Got some exception other than domain_error, when trying to triple " << n << endl;
        }
    }
}

