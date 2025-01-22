#include <nnPlot/Exporter.h>
#include <nnPlot/Model.h>
#include <nnPlot/Renderer.h>
#include <nnPlot/surface.h>
#include <spdlog/spdlog.h>
#include <unordered_map>

int main()
{
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
    const int nodeSpacing = 50; // 每个节点之间的垂直间距

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

    // 定义图层颜色映射
    std::unordered_map<std::string, nnPlot::Property::Color> layerColors = {
        { "input", { 0.2f, 0.6f, 0.8f } }, // 输入层颜色
        { "output", { 0.8f, 0.4f, 0.2f } }, // 输出层颜色
        { "fc1", { 0.4f, 0.7f, 0.4f } }, // 隐藏层颜色
        { "fc2", { 0.4f, 0.7f, 0.4f } }, // 隐藏层颜色
        { "fc3", { 0.4f, 0.7f, 0.4f } } // 隐藏层颜色
    };

    // 定义绘制回调函数，注意，要先绘制连接线才能绘制图层，否则图层会被连接线遮挡，
    // 即使定义了透明度也会影响美观程度
    std::vector<nnPlot::Renderer::DrawCallback> callbacks = {
        // 1. 设置背景颜色
        [](nnPlot::Renderer& renderer) {
            renderer.setBackgroundColor({ 0.95f, 0.95f, 0.95f });
        },

        // 2. 绘制连接线
        [&model](nnPlot::Renderer& renderer) {
            renderer.setConnectionColor({ 0.8f, 0.7f, 0.7f });
            for (const auto& layerName : model.getLayerNames()) {
                const nnPlot::Layer& layer = model.getLayer(layerName);
                for (const auto& input : layer.getInputs()) {
                    renderer.drawConnection(model.getLayer(input), layer, model);
                }
            }
        },

        // 3. 绘制图层
        [&model, &layerColors](nnPlot::Renderer& renderer) {
            for (const auto& layerName : model.getLayerNames()) {
                const nnPlot::Layer& layer = model.getLayer(layerName);
                renderer.setNodeColor(layerColors[layer.getName()]);
                renderer.drawLayer(layer, layer.getX(), layer.getY(), 40, 40);
            }
        },

        // 4. 添加标题
        [](nnPlot::Renderer& renderer) {
            renderer.drawText(1200 / 2.0, 50, "Neural Network Structure", 24, { 0.1f, 0.1f, 0.1f });
        }
    };

    // 执行绘制回调函数
    renderer.render(callbacks);

    // 保存为 PNG 文件
    nnPlot::Exporter::exportToPNG(cairoSurface, "model_structure.png");

    // 保存为 PDF 文件
    nnPlot::Exporter::exportToPDF(cairoSurface, "model_structure.pdf", 1200, 800);

    return 0;
}