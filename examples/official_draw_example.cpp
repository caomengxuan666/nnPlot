#include <cairo/cairo.h>
#include <cmath>
#include <nnPlot/Exporter.h>

int main()
{
    // 定义球体的参数
    double center_x = 250.0; // 球体中心 x 坐标
    double center_y = 250.0; // 球体中心 y 坐标
    double radius = 200.0;   // 球体半径

    // 创建绘图表面
    int surface_width = 500;
    int surface_height = 500;
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, surface_width, surface_height);
    cairo_t* cr = cairo_create(surface);

    // 创建背景（可选）
    cairo_set_source_rgb(cr, 0.95, 0.95, 0.95); // 浅灰色背景
    cairo_paint(cr);

    // 创建球体的径向渐变
    cairo_pattern_t* radial_pattern = cairo_pattern_create_radial(
        center_x - radius * 0.3, center_y - radius * 0.3, radius * 0.1, // 渐变起点
        center_x, center_y, radius                                      // 渐变终点
    );

    // 添加颜色停止点，实现分层效果
    cairo_pattern_add_color_stop_rgba(radial_pattern, 0.0, 0.1, 0.1, 0.8, 1.0); // 中心深蓝色
    cairo_pattern_add_color_stop_rgba(radial_pattern, 0.2, 0.1, 0.1, 0.8, 1.0); // 保持中心颜色
    cairo_pattern_add_color_stop_rgba(radial_pattern, 0.2, 0.2, 0.5, 0.9, 1.0); // 中间蓝绿色
    cairo_pattern_add_color_stop_rgba(radial_pattern, 0.4, 0.2, 0.5, 0.9, 1.0); // 保持中间颜色
    cairo_pattern_add_color_stop_rgba(radial_pattern, 0.4, 0.8, 0.8, 0.9, 1.0); // 边缘浅灰色
    cairo_pattern_add_color_stop_rgba(radial_pattern, 1.0, 0.8, 0.8, 0.9, 1.0); // 保持边缘颜色

    // 设置渐变并绘制球体
    cairo_set_source(cr, radial_pattern);
    cairo_arc(cr, center_x, center_y, radius, 0, 2 * M_PI);
    cairo_fill(cr);

    // 释放渐变对象
    cairo_pattern_destroy(radial_pattern);

    // 导出图像
    nnPlot::Exporter::exportToPNG(surface, "3d_sphere_example.png");

    // 清理资源
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return 0;
}