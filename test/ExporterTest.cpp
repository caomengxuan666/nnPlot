// nnPlot/tests/ExporterTest.cpp
#include <gtest/gtest.h>
#include <cairo/cairo.h>
#include <filesystem>
#include <nnPlot/Exporter.h>
#include <nnPlot/Utils.hpp>

namespace fs = std::filesystem;

TEST(ExporterTest, ExportToPNG) {
    const int width = 1200;
    const int height = 800;
    const std::string filename = "test_export_to_png.png";

    // 获取正确的输出路径
    std::filesystem::path output_path = Utils::File::get_output_path(filename);

    // 创建一个 Cairo 表面
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    ASSERT_NE(surface, nullptr);

    // 导出到 PNG 文件
    nnPlot::Exporter::exportToPNG(surface, output_path.string());

    // 检查文件是否存在
    EXPECT_TRUE(fs::exists(output_path));

    // 清理资源
    cairo_surface_destroy(surface);

    // 删除测试文件
    fs::remove(output_path);
}

TEST(ExporterTest, ExportToPDF) {
    const int width = 1200;
    const int height = 800;
    const std::string filename = "test_export_to_pdf.pdf";

    // 获取正确的输出路径
    std::filesystem::path output_path = Utils::File::get_output_path(filename);

    // 创建一个 Cairo 表面
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    ASSERT_NE(surface, nullptr);

    // 导出到 PDF 文件
    nnPlot::Exporter::exportToPDF(surface, output_path.string(), width, height);

    // 检查文件是否存在
    EXPECT_TRUE(fs::exists(output_path));

    // 清理资源
    cairo_surface_destroy(surface);

    // 删除测试文件
    fs::remove(output_path);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}