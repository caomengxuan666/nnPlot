/**
 * @FilePath     : /nnPlot/include/Renderer.h
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 15:26:56
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#ifndef RENDERER_H
#define RENDERER_H

#include "ModelParser.h"
struct cairo_surface_t;
struct cairo_t;
class Layer;

class Renderer {
public:
    Renderer(cairo_surface_t* surface);
    void drawLayer(const Layer& layer, double x, double y);
    void drawConnection(const Layer& from, const Layer& to);

private:
    cairo_t* cr;
};

#endif // RENDERER_H