# 查找所有.h, .hpp 和 .cpp 文件
file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")

# 查找 fmt 和 spdlog
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# 生成静态库
add_library(nnPlot_static STATIC ${SOURCES})
target_link_libraries(nnPlot_static PUBLIC ${Cairo_LIBRARIES})
target_link_libraries(nnPlot_static PUBLIC fmt::fmt)  # 链接 fmt
target_link_libraries(nnPlot_static PUBLIC spdlog::spdlog)  # 链接 spdlog

# 生成动态库
add_library(nnPlot_shared SHARED ${SOURCES})
target_link_libraries(nnPlot_shared PUBLIC ${Cairo_LIBRARIES})
target_link_libraries(nnPlot_shared PUBLIC fmt::fmt)  # 链接 fmt
target_link_libraries(nnPlot_shared PUBLIC spdlog::spdlog)  # 链接 spdlog
target_link_libraries(nnPlot_shared PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)
# 设置动态库的符号可见性，避免spdlog和fmt符号冲突
set_target_properties(nnPlot_shared PROPERTIES
    CXX_VISIBILITY_PRESET hidden  # 默认隐藏符号
    VISIBILITY_INLINES_HIDDEN ON  # 隐藏内联函数的符号
)

# 定义 NNPLOT_EXPORTS 宏（仅对动态库生效）
target_compile_definitions(nnPlot_shared PRIVATE NNPLOT_EXPORTS)

# 显式导出符号（仅对动态库生效）
set_target_properties(nnPlot_shared PROPERTIES
    CXX_VISIBILITY_PRESET default  # 导出符号
    VISIBILITY_INLINES_HIDDEN OFF  # 不隐藏内联函数的符号
)