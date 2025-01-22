/**
 * @FilePath     : /nnPlot/include/nnPlot/Renderer.h
 * @Description  : 渲染模块
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-22 20:10:14
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#ifndef RENDERER_H
#define RENDERER_H

#include "nnPlot/Layer.h"
#include "nnPlot/Property.h"
#include <cairo/cairo.h>
#include <functional>
#include <nnPlot/Model.h>
#include <string>

namespace nnPlot {

class Renderer {

public:
    using DrawCallback = std::function<void(Renderer&)>; // 定义回调函数类型
    Renderer(cairo_surface_t* surface);
    ~Renderer();

    void drawLayer(const Layer& layer, double x, double y, double width, double height);
    void drawConnection(const Layer& from, const Layer& to, const Model& model);

    // 设置背景颜色（使用元组形式）
    void setBackgroundColor(const Property::Color& color);

    // 设置节点颜色（使用元组形式）
    void setNodeColor(const Property::Color& color);

    // 设置连接线颜色（使用元组形式）
    void setConnectionColor(const Property::Color& color);

    // 绘制文本（使用元组形式）
    void drawText(double x, double y, const std::string& text, int fontSize, const Property::Color& color);

    // 执行绘制回调函数
    void render(const std::vector<DrawCallback>& callbacks);

private:
    cairo_t* cr; // Cairo 上下文
    Property::Color nodeColor; // 节点颜色
    Property::Color connectionColor; // 连接线颜色

    void drawArrow(double x1, double y1, double x2, double y2); // 绘制带箭头的连接线

    // 辅助函数：从元组中提取 r, g, b 值
    void applyColor(const Property::Color& color);
};

} // namespace nnPlot

#endif // RENDERER_H