add_executable(ExporterTest ExporterTest.cpp)


target_link_libraries(ExporterTest PRIVATE GTest::GTest GTest::Main)

add_test(NAME ExporterTest COMMAND ExporterTest)