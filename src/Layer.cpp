// nnPlot/Layer.cpp
#include "nnPlot/Layer.h"

namespace nnPlot {

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
    this->x = x;
}

void Layer::setY(double y) {
    this->y = y;
}

void Layer::setNodeY(double y, int index) {
    if (index >= 0 && index < nodeCount) {
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