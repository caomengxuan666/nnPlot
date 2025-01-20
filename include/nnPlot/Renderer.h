/**
 * @FilePath     : /nnPlot/include/nnPlot/Renderer.h
 * @Description  :  Renderer.h
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 20:35:09
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
// nnPlot/Renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#include "nnPlot/Layer.h"
#include <cairo/cairo.h>
#include <nnPlot/Model.h>
#include <string>

namespace nnPlot {

class Renderer {
public:
    Renderer(cairo_surface_t* surface);
    ~Renderer();

    void drawLayer(const Layer& layer, double x, double y, double width, double height);
    void drawConnection(const Layer& from, const Layer& to, const Model& model);

    void setBackgroundColor(double r, double g, double b);
    void setNodeColor(double r, double g, double b);
    void setConnectionColor(double r, double g, double b);
    void drawText(double x, double y, const std::string& text, int fontSize, double r, double g, double b);

private:
    cairo_t* cr; // Cairo 上下文
    double nodeColor[3]; // 节点颜色
    double connectionColor[3]; // 连接线颜色

    void drawArrow(double x1, double y1, double x2, double y2); // 绘制带箭头的连接线
};

} // namespace nnPlot

#endif // RENDERER_H