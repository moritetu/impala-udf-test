#include "udf-sample.h"
#include <string>
#include <sstream>

//
// UDFs Test
//

//
// Concat
//
// ex)
//   select concat(':', 'a', 'b', 'c') from default.dual; 
//   => a:b:c
//
StringVal Concat(FunctionContext* context, const StringVal& separator,
  const int len, const StringVal* args)
{
  if (separator.is_null || args->is_null) {
    return StringVal::null();
  }
  if (len == 1) return args[0];

  const StringVal *p = args;
  std::string str((const char*)p++->ptr);

  for (int i = 1; i < len; p++, i++) {
    if (p->is_null) return StringVal::null();
    str.append((const char*)separator.ptr);
    str.append((const char*)p->ptr);
  }
  StringVal result(context, str.size());
  memcpy(result.ptr, str.c_str(), str.size());
  return result;
}

static int32_t factorial(int32_t n)
{
  return (n > 1) ? n * factorial(n - 1): 1;
}

//
// Factorial
//
// ex)
//   select factorial(5) from default.dual; 
//   => 120
//
IntVal Factorial(FunctionContext* context, const IntVal& n)
{
  if (n.is_null) {
    return IntVal::null();
  }
  return IntVal(factorial(n.val));
}
