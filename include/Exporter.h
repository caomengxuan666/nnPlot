/**
 * @FilePath     : /nnPlot/include/Exporter.h
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 18:36:39
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#ifndef EXPORTER_H
#define EXPORTER_H

#include <cairo/cairo.h>
#include <string>

namespace nnPlot {

class Exporter {
public:
    static void exportToPNG(cairo_surface_t* surface, const std::string& filename);
    static void exportToPDF(cairo_surface_t* surface, const std::string& filename, double width, double height);
    static void exportToSVG(cairo_surface_t* surface, const std::string& filename, double width, double height);
};

} // namespace nnPlot

#endif // EXPORTER_H