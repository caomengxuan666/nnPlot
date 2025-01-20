#include <cairo/cairo.h>
#include <spdlog/spdlog.h>
#include "nnPlot/Model.h"
#include "nnPlot/Renderer.h"
#include "nnPlot/Exporter.h"
#include "nnPlot/surface.h"

int main() {
    // 初始化 spdlog（设置日志级别为 info）
    spdlog::set_level(spdlog::level::info);

    // 创建一个 surface 对象，指定宽度和高度
    nnPlot::surface surface(1200, 800);

    // 获取 Cairo 表面
    cairo_surface_t* cairoSurface = surface.getSurface();
    if (!cairoSurface) {
        spdlog::error("Failed to get Cairo surface");
        return 1;
    }

    // 定义模型结构
    nnPlot::Model model;

    // 添加更多层
    model.addLayer(nnPlot::Layer("input", "Input", 1));
    model.addLayer(nnPlot::Layer("fc1", "Dense (128)", 128));
    model.addLayer(nnPlot::Layer("fc2", "Dense (64)", 64));
    model.addLayer(nnPlot::Layer("fc3", "Dense (32)", 32));
    model.addLayer(nnPlot::Layer("output", "Output (10)", 10));

    // 添加更多连接
    model.connectLayers("input", "fc1");
    model.connectLayers("fc1", "fc2");
    model.connectLayers("fc2", "fc3");
    model.connectLayers("fc3", "output");

    // 手动设置每一层的 x 和 y 坐标
    const int layerSpacing = 200; // 每层之间的水平间距
    const int nodeSpacing = 50;   // 每个节点之间的垂直间距

    int x = 50; // 初始 x 坐标
    for (const auto& layerName : model.getLayerNames()) {
        nnPlot::Layer& layer = model.getLayer(layerName);
        int y = 50; // 初始 y 坐标
        layer.setX(x);
        for (int i = 0; i < layer.getNodeCount(); ++i) {
            layer.setNodeY(y, i);
            y += nodeSpacing;
        }
        x += layerSpacing;
    }

    // 渲染
    nnPlot::Renderer renderer(cairoSurface);

    // 设置背景颜色
    renderer.setBackgroundColor(0.95, 0.95, 0.95);  // 浅灰色背景

    // 绘制层
    for (const auto& layerName : model.getLayerNames()) {
        const nnPlot::Layer& layer = model.getLayer(layerName);
        // 设置不同层的颜色
        if (layer.getName() == "input") {
            renderer.setNodeColor(0.2, 0.6, 0.8);  // 输入层颜色
        } else if (layer.getName() == "output") {
            renderer.setNodeColor(0.8, 0.4, 0.2);  // 输出层颜色
        } else {
            renderer.setNodeColor(0.4, 0.7, 0.4);  // 隐藏层颜色
        }
        renderer.drawLayer(layer, layer.getX(), layer.getY(), 40, 40);  // 使用 getX() 和 getY()
    }

    // 绘制连接
    renderer.setConnectionColor(0.3, 0.3, 0.3);  // 连接线颜色
    for (const auto& layerName : model.getLayerNames()) {
        const nnPlot::Layer& layer = model.getLayer(layerName);
        for (const auto& input : layer.getInputs()) {
            renderer.drawConnection(model.getLayer(input), layer, model); // 传递 model 参数
        }
    }

    // 添加标题
    renderer.drawText(1200 / 2, 50, "Neural Network Structure", 24, 0.1, 0.1, 0.1);  // 标题

    // 保存为 PNG 文件
    nnPlot::Exporter::exportToPNG(cairoSurface, "model_structure.png");

    // 保存为 PDF 文件
    nnPlot::Exporter::exportToPDF(cairoSurface, "model_structure.pdf", 1200, 800);

    return 0;
}