/**
 * @FilePath     : /nnPlot/include/nnPlot/LayoutEngine.h
 * @Description  :  LayOutEngine
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-25 20:23:45
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
// nnPlot/LayoutEngine.h
#ifndef LAYOUT_ENGINE_H
#define LAYOUT_ENGINE_H

#include <memory>
#include <nnPlot/Model.h>
#include <nnPlot/concrete_layout.hpp>
namespace nnPlot {

template <class LayoutMode = nnPlot::Layout::VerticalLayout>
class LayoutEngine {
public:
    LayoutEngine()
        : mode(std::make_unique<LayoutMode>())
    {
    }
    void applyLayout(Model& model); // 将计算出来的位置应用到模型中,调用具体模式的layout方法。
    std::unique_ptr<LayoutMode> mode;
};
}

#endif // LAYOUT_ENGINE_H