// nnPlot/include/nnPlot/surface.h
/**
 * @FilePath     : /nnPlot/include/nnPlot/surface.h
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 20:51:28
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#include <cairo/cairo.h>
#include <spdlog/spdlog.h>
namespace nnPlot {
    class surface {
public:
    // 默认构造函数
    surface(unsigned int width = 1200, unsigned int height = 800, cairo_format_t format = CAIRO_FORMAT_ARGB32)
        : width(width), height(height), cairo_format(format) {
        _surface = cairo_image_surface_create(format, width, height);
        if (cairo_surface_status(_surface) != CAIRO_STATUS_SUCCESS) {
            spdlog::error("Failed to create Cairo surface: {}", cairo_status_to_string(cairo_surface_status(_surface)));
        }
    }

    // 析构函数
    ~surface() {
        if (_surface) {
            cairo_surface_destroy(_surface);
        }
    }

    // 获取 Cairo 表面
    cairo_surface_t* getSurface() const {
        return _surface;
    }

private:
    cairo_surface_t* _surface;
    unsigned int width;
    unsigned int height;
    cairo_format_t cairo_format;
};
};
