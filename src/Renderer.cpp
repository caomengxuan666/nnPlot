/**
 * @FilePath     : /nnPlot/src/Renderer.cpp
 * @Description  :  渲染实现模块，未来所有内容将根据Property.h进行重构
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-25 19:35:29
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/

#include "nnPlot/Layer.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <cairo/cairo.h>
#include <cmath>
#include <nnPlot/Model.h>
#include <nnPlot/Renderer.h>
#include <spdlog/spdlog.h>
#include <string>

static spdlog::logger logger("logger", std::make_shared<spdlog::sinks::basic_file_sink_mt>("RenderLog.txt"));

namespace nnPlot {


Renderer::Renderer(cairo_surface_t* surface)
{
    cr = cairo_create(surface);
    if (!cr) {
        spdlog::error("Failed to create Cairo context");
        logger.error("Failed to create Cairo context");
    }
}

Renderer::~Renderer()
{
    if (cr) {
        cairo_destroy(cr);
    }
}

// 辅助函数：从元组中提取 r, g, b 值并应用到 Cairo 上下文
void Renderer::applyColor(const Property::Color& color)
{
    auto [r, g, b] = color; // 结构化绑定解包
    cairo_set_source_rgb(cr, r, g, b);
}

/**
 * @author       : 
 * @brief        : 
 * @param         {Color&} color:
 * @return        {*}
**/
void Renderer::setBackgroundColor(const Property::Color& color)
{
    if (cr) {
        applyColor(color);
        cairo_paint(cr); // 填充整个表面
    }
}

void Renderer::setNodeColor(const Property::Color& color)
{
    nodeColor = color;
}

void Renderer::setConnectionColor(const Property::Color& color)
{
    connectionColor = color;
}

/**
 * @author       : cmx
 * @brief        : 文本绘制模块，未来将开放更多属性。
 * @param         {double} x:
 * @param         {double} y:
 * @param         {string&} text:
 * @param         {int} fontSize:
 * @param         {Color&} color:
 * @return        {*}
**/
void Renderer::drawText(double x, double y, const std::string& text, int fontSize, const Property::Color& color)
{
    if (cr) {
        applyColor(color);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, fontSize);

        // 计算文本宽度以居中
        cairo_text_extents_t extents;
        cairo_text_extents(cr, text.c_str(), &extents);
        cairo_move_to(cr, x - extents.width / 2, y);
        cairo_show_text(cr, text.c_str());
    }
}

/**
 * @author       : cmx
 * @brief        : Layer的绘制模块
 * @note         : 特别需要注意，绘制节点是累加
                   因为我们不能确保用户绘制的下一个是否还是同一个,
                   所以每次开始的时候都需要重新设置节点颜色
 * @param         {Layer&} layer:
 * @param         {double} x:
 * @param         {double} y:
 * @param         {double} width:
 * @param         {double} height:
 * @return        {*}
**/
void Renderer::drawLayer(const Layer& layer, double x, double y, double width, double height)
{
    if (cr) {
        logger.info("Drawing Layer: {}, X: {}, Y: {}", layer.getName(), x, y); // 保存到日志文件

        // 绘制矩形节点
        for (int i = 0; i < layer.getNodeCount(); ++i) {
            double nodeY = layer.getNodeY(i);

            logger.info("  Node {} Y: {}", i, nodeY); // 保存到日志文件

            // 重新设置节点颜色
            applyColor(nodeColor);

            cairo_rectangle(cr, x - width / 2, nodeY - height / 2, width, height);
            cairo_fill(cr);

            // 绘制节点标签
            drawText(x, nodeY + height / 2 + 10, layer.getLabel(), 12, { 0.0f, 0.0f, 0.0f });
        }
    }
}

/**
 * @author       : cmx
 * @brief        : Connection的绘制模块，未来将开放更多属性
 * @param         {Layer&} from:
 * @param         {Layer&} to:
 * @param         {Model&} model:
 * @return        {*}
**/
void Renderer::drawConnection(const Layer& from, const Layer& to, const Model& model) {
    if (cr) {
        // 设置连接线颜色和透明度
        auto [r, g, b] = connectionColor; // 获取颜色值
        float alpha = 1.0f; // 设置透明度（0.0f 完全透明，1.0f 完全不透明）
        cairo_set_source_rgba(cr, r, g, b, alpha); // 使用 cairo_set_source_rgba 设置颜色和透明度

        // 设置线宽
        cairo_set_line_width(cr, 1.0); // 设置连接线宽度

        // 绘制带箭头的连接线
        for (int i = 0; i < from.getNodeCount(); ++i) {
            double fromY = from.getNodeY(i);
            for (int j = 0; j < to.getNodeCount(); ++j) {
                double toY = to.getNodeY(j);
                drawArrow(from.getX() + 20, fromY, to.getX() - 20, toY);
            }
        }
    }
}

/**
 * @author       : cmx
 * @brief        : 绘制箭头模块，这里未来会开放箭头的属性模块
 * @param         {double} x1:
 * @param         {double} y1:
 * @param         {double} x2:
 * @param         {double} y2:
 * @return        {*}
**/
void Renderer::drawArrow(double x1, double y1, double x2, double y2)
{
    if (cr) {
        // 绘制连接线
        cairo_move_to(cr, x1, y1);
        cairo_line_to(cr, x2, y2);
        cairo_stroke(cr);

        // 绘制箭头
        double angle = atan2(y2 - y1, x2 - x1);
        double arrowLength = 10.0; // 箭头长度
        cairo_move_to(cr, x2, y2);
        cairo_line_to(cr, x2 - arrowLength * cos(angle - M_PI / 6), y2 - arrowLength * sin(angle - M_PI / 6));
        cairo_line_to(cr, x2 - arrowLength * cos(angle + M_PI / 6), y2 - arrowLength * sin(angle + M_PI / 6));
        cairo_close_path(cr);
        cairo_fill(cr);
    }
}

void Renderer::render(const std::vector<DrawCallback>& callbacks) {
    logger.info("Starting rendering process..."); // 保存到日志文件
    for (const auto& callback : callbacks) {
        callback(*this); // 依次执行回调函数
    }
}


} // namespace nnPlot
