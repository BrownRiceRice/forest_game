
set(TEST_SOURCES
    tests.cpp
    test_base.cpp
)

add_executable(UnitTests catch.hpp ${TEST_SOURCES})
target_compile_features(UnitTests PRIVATE cxx_nonstatic_member_init)
target_link_libraries(UnitTests Forest_Lib)
add_test(NAME MyUnitTests COMMAND UnitTests)
