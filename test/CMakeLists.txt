include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
	Test
	TestVector.cpp
	TestAlgorithm.cpp
	)
target_link_libraries(Test gtest_main)

include(GoogleTest)
gtest_discover_tests(Test)

