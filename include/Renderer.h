/**
 * @FilePath     : /nnPlot/include/Renderer.h
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 18:43:04
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#ifndef RENDERER_H
#define RENDERER_H

#include <cairo/cairo.h>
#include<Layer.h>

namespace nnPlot {

class Renderer {
public:
    Renderer(cairo_surface_t* surface);
    void drawLayer(const Layer& layer, double x, double y);
    void drawConnection(const Layer& from, const Layer& to);

private:
    cairo_t* cr; // Cairo 上下文
};

} // namespace nnPlot

#endif // RENDERER_H