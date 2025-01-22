add_executable(ExporterTest ExporterTest.cpp)

link_directories(${CMAKE_BINARY_DIR}/lib)

target_link_libraries(ExporterTest PRIVATE GTest::GTest GTest::Main)

target_link_libraries(ExporterTest PRIVATE ${Cairo_LIBRARIES})
target_link_libraries(ExporterTest PRIVATE nnPlot_shared)  # 链接动态库
add_test(NAME ExporterTest COMMAND ExporterTest)