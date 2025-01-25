// nnPlot/Layer.cpp
#include <nnPlot/Layer.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h> // 引入日志文件保存

namespace nnPlot {

// 创建日志文件
static std::shared_ptr<spdlog::logger> logger = spdlog::basic_logger_mt("layer_logger", "layer_log.txt");

Layer::Layer(const std::string& name, const std::string& label, int nodeCount)
    : name(name), label(label), nodeCount(nodeCount), x(0), y(0) {
    // 初始化 nodeYPositions 的大小为 nodeCount
    nodeYPositions.resize(nodeCount);
}

const std::string& Layer::getName() const {
    return name;
}

const std::string& Layer::getLabel() const {
    return label;
}

int Layer::getNodeCount() const {
    return nodeCount;
}

void Layer::setNodeCount(int nodeCount) {
    this->nodeCount = nodeCount;
    // 当 nodeCount 改变时，重新调整 nodeYPositions 的大小
    nodeYPositions.resize(nodeCount);
}

double Layer::getX() const {
    return x;
}

double Layer::getY() const {
    return y;
}

void Layer::setX(double x) {
    logger->info("Setting X for Layer {}: {}", name, x); // 保存到日志文件
    this->x = x;
}

void Layer::setY(double y) {
    logger->info("Setting Y for Layer {}: {}", name, y); // 保存到日志文件
    this->y = y;
}

void Layer::setNodeY(double y, int index) {
    if (index >= 0 && index < nodeCount) {
        logger->info("Setting NodeY for Layer {} Node {}: {}", name, index, y); // 保存到日志文件
        nodeYPositions[index] = y;
    }
}

double Layer::getNodeY(int index) const {
    if (index >= 0 && index < nodeCount) {
        return nodeYPositions[index];
    }
    return 0.0;
}

const std::vector<std::string>& Layer::getInputs() const {
    return inputs;
}

const std::vector<std::string>& Layer::getOutputs() const {
    return outputs;
}

void Layer::addInput(const std::string& input) {
    inputs.push_back(input);
}

void Layer::addOutput(const std::string& output) {
    outputs.push_back(output);
}

} // namespace nnPlot
