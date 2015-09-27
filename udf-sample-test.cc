#include <iostream>
#include <vector>

#include <impala_udf/udf-test-harness.h>
#include "udf-sample.h"

using namespace impala;
using namespace impala_udf;
using namespace std;

struct Test {
  int success;
  int failure;

  Test() : success(0), failure(0) {}
  int total() { return success + failure; }
  void report(int passed, const string& message) {
    if (passed) {
      cout << "[SUCCESS]";
      success++;
    } else {
      cout << "[FAIL]";
      failure++;
    }
    cout << " " << message;
    cout << endl;
  }
};
  
int main(int argc, char** argv) {
  Test test;
    
  //
  // Factorial
  //
  // <ARG1, RET>(function, ARG1, RET)
  test.report(UdfTestHarness::ValidateUdf<IntVal, IntVal>(
		Factorial, IntVal(5), IntVal(120)), "Factorial(5)");

  test.report(UdfTestHarness::ValidateUdf<IntVal, IntVal>(
		Factorial, IntVal(1), IntVal(1)), "Factorial(1)");

  //
  // Concat
  //
  // <RET, SEPARATOR, ARGS>(function, SEPARATOR, args, RET)
  //
  vector<StringVal> vargs1{ StringVal(" "), StringVal::null(), StringVal("a") };
  test.report(UdfTestHarness::ValidateUdf<StringVal, StringVal, StringVal>(
		Concat, StringVal(" "), vargs1, StringVal::null()), "Concat(' ', null, 'a')");

  vector<StringVal> vargs2{ StringVal::null(), StringVal("a") };
  test.report(UdfTestHarness::ValidateUdf<StringVal, StringVal, StringVal>(
		Concat, StringVal::null(), vargs2, StringVal::null()), "Concat(null, 'a')");

  vector<StringVal> vargs3{ StringVal("a"), StringVal::null() };
  test.report(UdfTestHarness::ValidateUdf<StringVal, StringVal, StringVal>(
		Concat, StringVal::null(), vargs3, StringVal::null()), "Concat(null, 'a', null)");

  vector<StringVal> vargs4{ StringVal("I"), StringVal("like"), StringVal("dogs") };
  test.report(UdfTestHarness::ValidateUdf<StringVal, StringVal, StringVal>(
		Concat, StringVal(" "), vargs4, StringVal("I like dogs")), "Concat(' ', 'I', 'like', 'dogs')");

  bool passed = UdfTestHarness::ValidateUdf<StringVal, StringVal, StringVal>(
	  Concat, StringVal(" "), vargs4, StringVal("I like dogs"));

  cout << endl
       << "total " << test.total() << ", ";
  cout << "success " << test.success << ", ";
  cout << "fail " << test.failure << endl;

  return test.failure > 0 ? 1: 0;
}
