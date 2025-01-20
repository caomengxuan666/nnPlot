# 查找所有.h, .hpp 和 .cpp 文件
file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")

# 生成静态库
add_library(nnPlot_static STATIC ${SOURCES})
target_link_libraries(nnPlot_static PUBLIC ${Cairo_LIBRARIES})

# 生成动态库
add_library(nnPlot_shared SHARED ${SOURCES})
target_link_libraries(nnPlot_shared PUBLIC ${Cairo_LIBRARIES})

