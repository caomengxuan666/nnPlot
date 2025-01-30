#include <cairo/cairo.h>
#include <cmath>
#include <nnPlot/Exporter.h>
#include <nnPlot/ThreeD_shape.hpp>

using namespace nnPlot::shape::Rectangle_3D;

int main()
{
    // 自定义形状的参数
    double x = 100.0, /* 起始位置 */
        y = 100.0,
           width = 204.8, /* 宽度 */
        height = 204.8, /* 高度 */
        depth = 10.0; /* 深度，非常薄 */

    constexpr double degrees = M_PI / 180.0;

    // 设置更明显的侧面视角的偏移量
    double offset_x = width * 0.5; // 深度引起的水平偏移（更大，表现为更明显的侧面）
    double offset_y = height * 0.25; // 深度引起的垂直偏移（更大，表现为更明显的侧面）

    // 创建绘图表面
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width + 2 * x + offset_x, height + 2 * y + offset_y);
    cairo_t* cr = cairo_create(surface);

    // 创建背景（可选）
    cairo_set_source_rgb(cr, 0.95, 0.95, 0.95); // 浅灰色背景
    cairo_paint(cr);

    // 绘制背面矩形
    draw_rectangle(cr, x + offset_x, y - offset_y, width, height);

    // 创建背面矩形的线性渐变模式
    cairo_pattern_t* back_gradient = nnPlot::shape::Rectangle_3D::create_gradient(x + offset_x, 
                                                                                 y - offset_y, 
                                                                                 width, 
                                                                                 height, 
                                                                                 true);

    // 设置矩形的填充色为渐变模式
    cairo_set_source(cr, back_gradient);
    cairo_fill_preserve(cr);

    // 设置边框颜色
    cairo_set_source_rgba(cr, 0.5, 0, 0, 0.7); // 边框颜色
    cairo_set_line_width(cr, 5.0);
    cairo_stroke(cr);

    // 绘制正面矩形
    draw_rectangle(cr, x, y, width, height);

    // 创建正面矩形的线性渐变模式
    cairo_pattern_t* front_gradient = create_gradient(x, y, width, height, false);

    // 设置矩形的填充色为渐变模式
    cairo_set_source(cr, front_gradient);
    cairo_fill_preserve(cr);

    // 设置边框颜色
    cairo_set_source_rgba(cr, 0.5, 0, 0, 0.7); // 边框颜色
    cairo_stroke(cr);

    // 绘制连接正面和背面的边
    draw_edges(cr, x, y, width, height, offset_x, offset_y);

    // 导出图像
    nnPlot::Exporter::exportToPNG(surface, "pooling_layer_example.png");

    // 释放资源
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    // 释放渐变模式资源
    cairo_pattern_destroy(front_gradient);
    cairo_pattern_destroy(back_gradient);

    return 0;
}