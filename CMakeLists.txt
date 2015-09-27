cmake_minimum_required(VERSION 2.8) 

ADD_DEFINITIONS(
    -std=c++0x
    # Other flags
)
add_library(myudf SHARED  udf-sample.cc)
target_link_libraries(myudf ImpalaUdf)
add_executable(myudf-test udf-sample-test.cc)
target_link_libraries(myudf-test myudf)
