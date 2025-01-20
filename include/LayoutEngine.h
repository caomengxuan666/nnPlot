/**
 * @FilePath     : /nnPlot/include/LayoutEngine.h
 * @Description  :  
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 18:36:10
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
#ifndef LAYOUT_ENGINE_H
#define LAYOUT_ENGINE_H

#include <Model.h>
#include <vector>

namespace nnPlot {

class LayoutEngine {
public:
    // 自动布局
    void layout(Model& model);

private:
    // 层次化布局
    void hierarchicalLayout(Model& model);
};

} // namespace nnPlot

#endif // LAYOUT_ENGINE_H