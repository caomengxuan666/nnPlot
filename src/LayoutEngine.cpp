// nnPlot/LayoutEngine.cpp
#include "nnPlot/LayoutEngine.h"
#include "nnPlot/Model.h"
#include "nnPlot/Layer.h"

namespace nnPlot {

void LayoutEngine::layout(Model& model) {
    const double layerSpacing = 200.0; // 层之间的水平间距
    const double nodeSpacing = 60.0; // 节点之间的垂直间距
    const double startX = 100.0; // 起始 X 坐标
    const double startY = 100.0; // 起始 Y 坐标

    // 获取所有层
    auto layers = model.getLayers();

    // 设置每层的坐标
    double x = startX;
    for (auto& layer : layers) {
        // 计算层的 Y 坐标
        double layerHeight = layer.getNodeCount() * nodeSpacing;
        double y = startY + (800 - layerHeight) / 2; // 中心对齐

        // 设置层的坐标
        layer.setX(x);
        layer.setY(y);

        // 计算每个节点的具体位置
        double nodeY = y;
        for (int i = 0; i < layer.getNodeCount(); ++i) {
            layer.setNodeY(nodeY, i); // 使用 setNodeY 方法设置节点的 Y 坐标
            nodeY += nodeSpacing;
        }

        // 更新 X 坐标
        x += layerSpacing;
    }
}

} // namespace nnPlot