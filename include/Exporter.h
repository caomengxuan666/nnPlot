/**
 * @FilePath     : /nnPlot/include/Exporter.h
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 15:27:36
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#ifndef EXPORTER_H
#define EXPORTER_H
struct cairo_surface_t;
#include <string>

class Exporter {
public:
    static void exportToPNG(cairo_surface_t* surface, const std::string& filename);
    static void exportToPDF(cairo_surface_t* surface, const std::string& filename);
    static void exportToSVG(cairo_surface_t* surface, const std::string& filename);
};
#endif