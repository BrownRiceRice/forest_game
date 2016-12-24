
add_executable(UnitTests catch.hpp tests.cpp)
target_link_libraries(UnitTests Forest_Lib)
add_test(NAME MyUnitTests COMMAND UnitTests)
