#ifndef UNITTEST_H
#define UNITTEST_H

#include <iostream>
#include <string>

/*
 *  This class helps support self-checking unit tests.
 *  
 *  A small collection of test assertions (inspired by the JUNIT
 *  package for Java is supported). The number of successes and failures
 *  of these assertions are tallied and can be accessed at any time (typically
 *  at the end of the test suite).
 *
 *  In addition, detailed error messages are printed for the first
 *  DETAIL_LIMIT failures. (After that additional failures are tallied
 *  but not printed.)
 *
 */

class UnitTest {
private:
  static long numSuccesses;
  static long numFailures;
  static long DETAIL_LIMIT;
  static long NOTICE_INTERVAL;

public:
  // The main test function - normally called via one of the macros
  // declared following this class.
  static void checkTest (bool condition, const char* conditionStr,
			 const char* fileName, int lineNumber);
  static void checkTest (bool condition, const std::string& conditionStr,
			 const char* fileName, int lineNumber);

  static void checkEqualityTest (const char* x, const std::string& y,
			 const char* fileName, int lineNumber)
  {
    checkEqualityTest (std::string(x), y, fileName, lineNumber);
  }


  template <typename T>
  static void checkEqualityTest (const T& x, const T& y,
			 const char* fileName, int lineNumber)
  {
    using namespace std;

    if (x == y)
      {
	++numSuccesses;
      }
    else
      {
	++numFailures;
	if (numFailures < DETAIL_LIMIT)
	  {
	    cerr << "UnitTest: " << "Failed test #" 
		 << numFailures + numSuccesses << ": ";
	    cerr << "'";
	    cerr << x;
	    cerr << "' != '";
	    cerr << y;
	    cerr << "'" << ", in line " << lineNumber << " of " << fileName << endl;
	  }
      }
    long total = numFailures + numSuccesses;
    if (total % NOTICE_INTERVAL == 0)
      cerr << "UnitTest: completed " << total << " tests so far" << endl;
    if (total == NOTICE_INTERVAL * 10L)
      NOTICE_INTERVAL = 10L * NOTICE_INTERVAL;
  }



  // Summary info about tests conducted so far
  static long getNumTests()     {return numSuccesses + numFailures;} 
  static long getNumFailures()  {return numFailures;} 
  static long getNumSuccesses() {return numSuccesses;} 
  
  // Change the number of detailed messages to be printed.
  static void setDetailLimit (long limit) {DETAIL_LIMIT = limit;}

  // Start a fresh tally.
  static void reset() {numSuccesses = numFailures = 0L; NOTICE_INTERVAL = 10L;}

  // Print a simple summary report
  static void report (std::ostream& out);
};


/**
 *   Macros - actual tests will invoke one of these
 */

#define assertTrue(cond) UnitTest::checkTest (cond, #cond, __FILE__, __LINE__)
#define assertFalse(cond) UnitTest::checkTest (!(cond), "!( ## cond ## )", __FILE__, __LINE__)

#define assertEqual( x, y ) UnitTest::checkEqualityTest (x, y, \
                            __FILE__, __LINE__)

#define assertNotEqual( x , y ) assertFalse ((x)==(y))

#define assertNull(x) checkTest ((x)==0)

#define assertNotNull(x) checkTest ((x)!=0)

#define succeed UnitTest::checkTest (true, "succeed", __FILE__, __LINE__)

#define fail UnitTest::checkTest (false, "fail", __FILE__, __LINE__)




#endif
