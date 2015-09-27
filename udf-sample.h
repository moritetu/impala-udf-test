#ifndef IMPALA_UDF_SAMPLE_UDF_H
#define IMPALA_UDF_SAMPLE_UDF_H

#include <impala_udf/udf.h>

using namespace impala_udf;

StringVal Concat(FunctionContext* context, const StringVal& separator, int num_of_args, const StringVal* string);
IntVal Factorial(FunctionContext* context, const IntVal& n);

#endif
