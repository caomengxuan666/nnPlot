/**
 * @FilePath     : /nnPlot/include/nnPlot/ThreeD_shape.hpp
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-26 16:07:42
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/

#ifndef THREED_SHAPE_HPP
#define THREED_SHAPE_HPP

namespace nnPlot::shape::Rectangle_3D {
#include <cairo/cairo.h>
cairo_pattern_t* create_gradient(double x, double y, double width, double height, bool is_back)
{
    cairo_pattern_t* gradient;
    if (is_back) {
        gradient = cairo_pattern_create_linear(x, y, x + width, y + height);
        cairo_pattern_add_color_stop_rgba(gradient, 0.0, 0.7, 0.5, 0.3, 0.5); // 起始颜色
        cairo_pattern_add_color_stop_rgba(gradient, 1.0, 0.5, 0.3, 0.1, 0.5); // 结束颜色
    } else {
        gradient = cairo_pattern_create_linear(x, y, x + width, y + height);
        cairo_pattern_add_color_stop_rgb(gradient, 0.0, 0.9, 0.8, 0.5); // 起始颜色
        cairo_pattern_add_color_stop_rgb(gradient, 1.0, 0.7, 0.6, 0.3); // 结束颜色
    }
    return gradient;
}

// 函数：绘制矩形
void draw_rectangle(cairo_t* cr, double x, double y, double width, double height)
{
    cairo_move_to(cr, x, y); // 左上角
    cairo_line_to(cr, x + width, y); // 右上角
    cairo_line_to(cr, x + width, y + height); // 右下角
    cairo_line_to(cr, x, y + height); // 左下角
    cairo_close_path(cr);
}

// 函数：绘制连接正面和背面的边
void draw_edges(cairo_t* cr, double x, double y, double width, double height, double offset_x, double offset_y)
{
    cairo_move_to(cr, x + width, y); // 右上角
    cairo_line_to(cr, x + width + offset_x, y - offset_y); // 背面右上
    cairo_stroke(cr);

    cairo_move_to(cr, x + width, y + height); // 右下角
    cairo_line_to(cr, x + width + offset_x, y + height - offset_y); // 背面右下
    cairo_stroke(cr);

    cairo_move_to(cr, x, y + height); // 左下角
    cairo_line_to(cr, x + offset_x, y + height - offset_y); // 背面左下
    cairo_stroke(cr);

    cairo_move_to(cr, x, y); // 左上角
    cairo_line_to(cr, x + offset_x, y - offset_y); // 背面左上
    cairo_stroke(cr);
}

}

#endif // !THREED_SHAPE_HPP
