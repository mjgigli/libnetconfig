add_executable(test-ipv4address test_ipv4address.cpp)
target_link_libraries(test-ipv4address ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(test-ipv4address netconfig)
add_test(test-ipv4address test-ipv4address)

add_executable(test-prefix test_prefix.cpp)
target_link_libraries(test-prefix ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(test-prefix netconfig)
add_test(test-prefix test-prefix)
