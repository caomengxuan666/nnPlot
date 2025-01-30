# 查找所有.cpp文件
file(GLOB_RECURSE CPP_FILES "*.cpp")

# 查找 fmt 和 spdlog
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# 添加库搜索路径
link_directories(${CMAKE_BINARY_DIR}/lib)

# 遍历每个.cpp文件并创建独立的目标可执行文件
foreach(CPP_FILE ${CPP_FILES})
    get_filename_component(TARGET_NAME ${CPP_FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${CPP_FILE})
    target_link_libraries(${TARGET_NAME} PRIVATE ${Cairo_LIBRARIES})
    target_link_libraries(${TARGET_NAME} PRIVATE fmt::fmt)  # 确保 fmt 在 spdlog 之前
    target_link_libraries(${TARGET_NAME} PRIVATE spdlog::spdlog)
    target_link_libraries(${TARGET_NAME} PRIVATE nnPlot_shared)  # 链接动态库
    target_link_libraries(${TARGET_NAME} PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)
endforeach()