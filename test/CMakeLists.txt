include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(TestUtils
	TestIterator.cpp
	TestAlgorithm.cpp
	TestUtility.cpp
	TestTypeTraits.cpp
)
target_link_libraries(TestUtils gtest_main)
add_test(NAME TestUtils COMMAND TestUtils)

add_executable(TestVector TestVector.cpp)
target_link_libraries(TestVector gtest_main)
add_test(NAME TestVector COMMAND TestVector)
