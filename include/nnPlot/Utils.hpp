/**
 * @FilePath     : /nnPlot/include/nnPlot/Utils.hpp
 * @Description  : Some utility functions for file operations.
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-30 23:04:56
 * @Copyright    : PERSONAL DEVELOPER CMX., Copyright (c) 2025.
 **/

#ifndef UTILS_HPP
#define UTILS_HPP
#include <cairo/cairo.h>
#include <filesystem>
#include <nnPlot/Concrete_style.h>
#include <spdlog/spdlog.h>
#include <string>

namespace Utils::File {

/**
 * @author       : cmx
 * @brief        : Save a Cairo surface to a file at the specified path.
 *                 If no path is provided, the file is saved in the project root's example_output directory.
 * @param surface : The Cairo surface to save.
 * @param filename : The name of the file to save (e.g., "model.png").
 * @param path     : The directory path where the file should be saved (optional).
 * @return        : True if the file was saved successfully, false otherwise.
 **/
inline bool save_cairo_surface(cairo_surface_t* surface, const std::string& filename, const std::string& path = "")
{
    // 获取项目根目录（项目根目录是包含 CMakeLists.txt 的目录）
    std::filesystem::path project_root = std::filesystem::current_path();
    while (project_root.has_parent_path() && !std::filesystem::exists(project_root / "CMakeLists.txt")) {
        project_root = project_root.parent_path();
    }

    // 如果找不到 CMakeLists.txt，则使用当前目录
    if (!std::filesystem::exists(project_root / "CMakeLists.txt")) {
        project_root = std::filesystem::current_path();
        spdlog::warn("Could not find project root (CMakeLists.txt). Using current directory: {}", project_root.string());
    }

    // Default output directory (project root / example_output)
    std::filesystem::path output_dir = path.empty() ? project_root / "example_output" : std::filesystem::path(path);

    // 如果输出路径包含 'build'，则重定向到项目根目录下的 example_output
    if (output_dir.string().find("build") != std::string::npos) {
        output_dir = project_root / "example_output";
        spdlog::warn("Output directory contained 'build'. Redirecting to: {}", output_dir.string());
    }

    // Create the output directory if it doesn't exist
    if (!std::filesystem::exists(output_dir)) {
        if (!std::filesystem::create_directories(output_dir)) {
            spdlog::error("Failed to create output directory: {}", output_dir.string());
            return false;
        }
    }

    // Construct the full file path
    std::filesystem::path file_path = output_dir / filename;

    // Save the Cairo surface to the file
    cairo_status_t status = cairo_surface_write_to_png(surface, file_path.string().c_str());
    if (status != CAIRO_STATUS_SUCCESS) {
        spdlog::error("Failed to save file: {} (Cairo error: {})", file_path.string(), cairo_status_to_string(status));
        return false;
    }

    spdlog::info("File saved successfully: {}", file_path.string());
    return true;
}

} // namespace File::Out

namespace Utils::File {

/**
 * @brief Get the output path for a file.
 * @param filename The name of the file.
 * @param path The directory path (optional).
 * @return The full output path.
 **/
inline std::filesystem::path get_output_path(const std::string& filename, const std::string& path = "")
{
    // 获取项目根目录
    std::filesystem::path project_root = std::filesystem::current_path();
    while (project_root.has_parent_path() && !std::filesystem::exists(project_root / "CMakeLists.txt")) {
        project_root = project_root.parent_path();
    }

    // 如果找不到 CMakeLists.txt，则使用当前目录
    if (!std::filesystem::exists(project_root / "CMakeLists.txt")) {
        project_root = std::filesystem::current_path();
        spdlog::warn("Could not find project root (CMakeLists.txt). Using current directory: {}", project_root.string());
    }

    // 默认输出目录（项目根目录 / example_output）
    std::filesystem::path output_dir = path.empty() ? project_root / "example_output" : std::filesystem::path(path);

    // 如果输出路径包含 'build'，则重定向到项目根目录下的 example_output
    if (output_dir.string().find("build") != std::string::npos) {
        output_dir = project_root / "example_output";
        spdlog::warn("Output directory contained 'build'. Redirecting to: {}", output_dir.string());
    }

    // 创建输出目录（如果不存在）
    if (!std::filesystem::exists(output_dir)) {
        if (!std::filesystem::create_directories(output_dir)) {
            spdlog::error("Failed to create output directory: {}", output_dir.string());
            return "";
        }
    }

    // 返回完整文件路径
    return output_dir / filename;
}

} // namespace Utils::File

namespace Utils::Time {
/**
 * @author       : cmx
 * @brief        : generate a time stamp
 * @return        {*}
 **/

inline const std::string getTimeStamp()
{
    // get current time stamp with chrono
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    // 格式化成yy mm dd hh mm ss
    std::tm* now_tm = std::localtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(now_tm, "%Y-%m-%d-%H-%M-%S");

    return ss.str();
}

}

#endif // UTILS_HPP