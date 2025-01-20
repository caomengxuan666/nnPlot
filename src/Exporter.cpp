#include <nnPlot/Exporter.h>
#include <nnPlot/utils.hpp> // 包含工具函数
#include <cairo/cairo-pdf.h>      // 用于 PDF 导出
#include <cairo/cairo-svg.h>      // 用于 SVG 导出

using namespace nnPlot;

void Exporter::exportToPNG(cairo_surface_t* surface, const std::string& filename, const std::string& path) {
    // 使用工具函数保存为 PNG
    if (!Utils::File::save_cairo_surface(surface, filename, path)) {
        spdlog::error("Failed to export to PNG: {}", filename);
    }
}

void Exporter::exportToPDF(cairo_surface_t* surface, const std::string& filename, double width, double height, const std::string& path) {
    // 获取输出路径
    std::filesystem::path output_path = Utils::File::get_output_path(filename, path);

    // 创建 PDF 表面
    cairo_surface_t* pdf_surface = cairo_pdf_surface_create(output_path.string().c_str(), width, height);
    if (cairo_surface_status(pdf_surface) != CAIRO_STATUS_SUCCESS) {
        spdlog::error("Failed to create PDF surface: {}", cairo_status_to_string(cairo_surface_status(pdf_surface)));
        return;
    }

    // 将原始表面内容绘制到 PDF 表面
    cairo_t* cr = cairo_create(pdf_surface);
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    // 清理资源
    cairo_destroy(cr);
    cairo_surface_flush(pdf_surface);
    cairo_surface_destroy(pdf_surface);

    spdlog::info("PDF exported successfully: {}", output_path.string());
}

void Exporter::exportToSVG(cairo_surface_t* surface, const std::string& filename, double width, double height, const std::string& path) {
    // 获取输出路径
    std::filesystem::path output_path = Utils::File::get_output_path(filename, path);

    // 创建 SVG 表面
    cairo_surface_t* svg_surface = cairo_svg_surface_create(output_path.string().c_str(), width, height);
    if (cairo_surface_status(svg_surface) != CAIRO_STATUS_SUCCESS) {
        spdlog::error("Failed to create SVG surface: {}", cairo_status_to_string(cairo_surface_status(svg_surface)));
        return;
    }

    // 将原始表面内容绘制到 SVG 表面
    cairo_t* cr = cairo_create(svg_surface);
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    // 清理资源
    cairo_destroy(cr);
    cairo_surface_flush(svg_surface);
    cairo_surface_destroy(svg_surface);

    spdlog::info("SVG exported successfully: {}", output_path.string());
}