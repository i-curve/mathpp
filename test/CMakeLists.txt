add_executable(mathpp_test mathpp_test.cpp)
target_link_libraries(mathpp_test PRIVATE mathpp::mathpp)
target_include_directories(mathpp_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_test(NAME mathpp_test_example COMMAND mathpp_test)
