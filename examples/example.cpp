/**
 * @FilePath     : /nnPlot/examples/example.cpp
 * @Description  : Example program to draw a simple neural network model using Cairo.
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 15:29:54
 * @Copyright    : PERSONAL DEVELOPER CMX., Copyright (c) 2025.
 **/

#include <cairo/cairo.h>
#include <iostream>
#include <math.h>
#include "utils.hpp" // Include the utils header

int main() {
    // 创建一个 PNG 图像表面
    const int width = 800;
    const int height = 600;
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t* cr = cairo_create(surface);

    // 设置背景颜色
    cairo_set_source_rgb(cr, 1, 1, 1); // 白色背景
    cairo_paint(cr);

    // 定义模型结构
    const int layerCount = 3; // 输入层、隐藏层、输出层
    const char* layerNames[] = { "Input", "Hidden", "Output" };
    const int layerSizes[] = { 4, 6, 2 }; // 每层的节点数
    const double layerX[] = { 100, 400, 700 }; // 每层的 X 坐标
    const double layerY[] = { 300, 300, 300 }; // 每层的 Y 坐标

    // 绘制节点
    cairo_set_source_rgb(cr, 0, 0, 0); // 黑色
    cairo_set_line_width(cr, 2.0);

    for (int i = 0; i < layerCount; i++) {
        double x = layerX[i];
        double y = layerY[i] - (layerSizes[i] - 1) * 30; // 垂直居中

        for (int j = 0; j < layerSizes[i]; j++) {
            // 绘制节点（圆形）
            cairo_arc(cr, x, y + j * 60, 20, 0, 2 * M_PI);
            cairo_stroke(cr);

            // 绘制节点名称
            cairo_move_to(cr, x - 15, y + j * 60 + 5);
            cairo_show_text(cr, layerNames[i]);
        }
    }

    // 绘制连接线
    for (int i = 0; i < layerCount - 1; i++) {
        double x1 = layerX[i] + 20;
        double x2 = layerX[i + 1] - 20;

        for (int j = 0; j < layerSizes[i]; j++) {
            double y1 = layerY[i] - (layerSizes[i] - 1) * 30 + j * 60;

            for (int k = 0; k < layerSizes[i + 1]; k++) {
                double y2 = layerY[i + 1] - (layerSizes[i + 1] - 1) * 30 + k * 60;

                // 绘制连接线
                cairo_move_to(cr, x1, y1);
                cairo_line_to(cr, x2, y2);
                cairo_stroke(cr);
            }
        }
    }

    // 保存为 PNG 文件
    if (!Utils::File::save_cairo_surface(surface, "model_structure.png")) {
        std::cerr << "Failed to save the model structure." << std::endl;
    }

    // 清理资源
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return 0;
}