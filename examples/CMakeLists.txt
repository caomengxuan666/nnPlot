# 查找所有.h,.hpp和.cpp文件
file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")

add_executable(plotExample ${SOURCES})

target_link_libraries(plotExample PRIVATE ${Cairo_LIBRARIES})

target_link_libraries(plotExample PRIVATE spdlog::spdlog)