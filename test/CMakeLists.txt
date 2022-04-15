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

add_executable(TestTree TestTree.cpp)
target_link_libraries(TestTree gtest_main)
add_test(NAME TestTree COMMAND TestTree)

add_executable(TestVector TestVector.cpp)
target_link_libraries(TestVector gtest_main)
add_test(NAME TestVector COMMAND TestVector)

add_executable(TestMap TestMap.cpp)
target_link_libraries(TestMap gtest_main)
add_test(NAME TestMap COMMAND TestMap)

add_executable(TestStack TestStack.cpp)
target_link_libraries(TestStack gtest_main)
add_test(NAME TestStack COMMAND TestStack)

add_executable(TestSet TestSet.cpp)
target_link_libraries(TestSet gtest_main)
add_test(NAME TestSet COMMAND TestSet)

add_executable(TestPerformance TestPerformance.cpp)
target_link_libraries(TestPerformance gtest_main)
add_test(NAME TestPerformance COMMAND TestPerformance)

