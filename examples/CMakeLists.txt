# 查找所有.h,.hpp和.cpp文件
file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")

# 创建可执行文件
add_executable(plotExample ${SOURCES})

# 查找 fmt 和 spdlog
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# 添加库搜索路径
link_directories(${CMAKE_BINARY_DIR}/lib)

# 链接依赖库
target_link_libraries(plotExample PRIVATE ${Cairo_LIBRARIES})
target_link_libraries(plotExample PRIVATE fmt::fmt)  # 确保 fmt 在 spdlog 之前
target_link_libraries(plotExample PRIVATE spdlog::spdlog)
target_link_libraries(plotExample PRIVATE nnPlot_shared)  # 链接动态库