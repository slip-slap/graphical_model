find_package(GTest REQUIRED)
find_package(Boost 1.76.0 COMPONENTS ALL)


include_directories(TheTest ${Boost_INCLUDE_DIR})


message("${Boost_FOUND}")
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")
message("${CMAKE_INSTALL_PREFIX}")

add_executable(TheTest test_gmnode.cpp)
target_link_libraries(TheTest ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(TheTest ${Boost_LIBRARIES})
#target_link_libraries(TheTest GTest::gmock GTest::gmock_main)

#target_link_libraries(TheTest /usr/local/Cellar/googletest/1.11.0/lib/libgmock.a)
#target_link_libraries(TheTest /usr/local/Cellar/googletest/1.11.0/lib/libgmock_main.a)



