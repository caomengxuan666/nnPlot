/**
 * @FilePath     : /nnPlot/include/nnPlot/concrete_layout.hpp
 * @Description  :  具体的layout的类
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-25 20:30:56
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/

#ifndef CONCRETE_LAYOUT_HPP
#define CONCRETE_LAYOUT_HPP

#include <nnPlot/Model.h>

namespace nnPlot::Layout {
template <class LayoutModel>
class AbstractLayout {
public:
    virtual void layout(LayoutModel& layoutModel) = 0;
};

// 垂直布局类
class VerticalLayout : public AbstractLayout<Model> {
public:
    void layout(Model& layoutModel) override
    {
        const int layerSpacing = 200; // 层间距
        const int nodeSpacing = 50; // 节点间距

        int x = 50; // 初始 x 坐标
        for (const auto& layerName : layoutModel.getLayerNames()) {
            const Layer& layer = layoutModel.getLayer(layerName);
            int y = 50; // 初始 y 坐标
            layoutModel.setLayerPosition(layerName, x, y);

            for (int i = 0; i < layer.getNodeCount(); ++i) {
                layoutModel.setNodePosition(layerName, i, y);
                y += nodeSpacing;
            }
            x += layerSpacing;
        }
    }
};

class HorizontalLayout : public AbstractLayout<Model> {
public:
    void layout(Model& layoutModel) override
    {
        // todo
    }
};

class GridLayout : public AbstractLayout<Model> {
public:
    void layout(Model& layoutModel) override
    {
        // todo
    }
};
}

#endif // !CONCRETE_LAYOUT_HPP
