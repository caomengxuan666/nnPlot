// nnPlot/Renderer.cpp
#include "nnPlot/Layer.h"
#include <cairo/cairo.h>
#include <cmath>
#include <nnPlot/Renderer.h>
#include <spdlog/spdlog.h>
#include <string>
#include <nnPlot/Model.h>

namespace nnPlot {

Renderer::Renderer(cairo_surface_t* surface)
{
    cr = cairo_create(surface);
    if (!cr) {
        spdlog::error("Failed to create Cairo context");
    }
}

Renderer::~Renderer()
{
    if (cr) {
        cairo_destroy(cr);
    }
}

void Renderer::setBackgroundColor(double r, double g, double b)
{
    if (cr) {
        cairo_set_source_rgb(cr, r, g, b);
        cairo_paint(cr); // 填充整个表面
    }
}

void Renderer::setNodeColor(double r, double g, double b)
{
    nodeColor[0] = r;
    nodeColor[1] = g;
    nodeColor[2] = b;
}

void Renderer::setConnectionColor(double r, double g, double b)
{
    connectionColor[0] = r;
    connectionColor[1] = g;
    connectionColor[2] = b;
}

void Renderer::drawText(double x, double y, const std::string& text, int fontSize, double r, double g, double b)
{
    if (cr) {
        cairo_set_source_rgb(cr, r, g, b);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, fontSize);

        // 计算文本宽度以居中
        cairo_text_extents_t extents;
        cairo_text_extents(cr, text.c_str(), &extents);
        cairo_move_to(cr, x - extents.width / 2, y);
        cairo_show_text(cr, text.c_str());
    }
}

void Renderer::drawLayer(const Layer& layer, double x, double y, double width, double height) {
    if (cr) {
        // 设置节点颜色
        cairo_set_source_rgb(cr, nodeColor[0], nodeColor[1], nodeColor[2]);

        // 绘制矩形节点
        for (int i = 0; i < layer.getNodeCount(); ++i) {
            double nodeY = layer.getNodeY(i);
            cairo_rectangle(cr, x - width / 2, nodeY - height / 2, width, height);
            cairo_fill(cr);

            // 绘制节点标签
            drawText(x, nodeY + height / 2 + 10, layer.getLabel(), 12, 0.0, 0.0, 0.0);
        }
    }
}

void Renderer::drawConnection(const Layer& from, const Layer& to, const Model& model)
{
    if (cr) {
        // 设置连接线颜色
        cairo_set_source_rgb(cr, connectionColor[0], connectionColor[1], connectionColor[2]);

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

} // namespace nnPlot