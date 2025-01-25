// nnPlot/Model.cpp
#include<nnPlot/Model.h>
#include <stdexcept>

namespace nnPlot {

// 添加层
void Model::addLayer(const Layer& layer) {
    layers.push_back(layer);
    layerIndexMap[layer.getName()] = layers.size() - 1;
}

// 连接层
void Model::connectLayers(const std::string& fromLayerName, const std::string& toLayerName) {
    if (layerIndexMap.find(fromLayerName) == layerIndexMap.end() || layerIndexMap.find(toLayerName) == layerIndexMap.end()) {
        throw std::runtime_error("Layer not found");
    }
    layers[layerIndexMap.at(toLayerName)].addInput(fromLayerName);
    layers[layerIndexMap.at(fromLayerName)].addOutput(toLayerName);
}

// 获取层（非const版本）
Layer& Model::getLayer(const std::string& name) {
    if (layerIndexMap.find(name) == layerIndexMap.end()) {
        throw std::runtime_error("Layer not found");
    }
    return layers[layerIndexMap.at(name)];
}

// 获取层（const版本）
const Layer& Model::getLayer(const std::string& name) const {
    if (layerIndexMap.find(name) == layerIndexMap.end()) {
        throw std::runtime_error("Layer not found");
    }
    return layers[layerIndexMap.at(name)];
}

// 获取所有层
std::vector<Layer>& Model::getLayers() {
    return layers;
}

// 获取所有层（const版本）
const std::vector<Layer>& Model::getLayers() const {
    return layers;
}

// 获取所有层名
std::vector<std::string> Model::getLayerNames() const {
    std::vector<std::string> names;
    for (const auto& layer : layers) {
        names.emplace_back(layer.getName());
    }
    return names;
}

// 设置层的位置
void Model::setLayerPosition(const std::string& layerName, int x, int y) {
    Layer& layer = getLayer(layerName);
    layer.setX(x);
    // 如果你有更多位置相关的属性，可以在这里设置，未来这两个函数我会将其拿出进行解耦合。
}

// 设置节点的位置
void Model::setNodePosition(const std::string& layerName, int nodeIndex, int y) {
    Layer& layer = getLayer(layerName);
    layer.setNodeY(y, nodeIndex);
}



} // namespace nnPlot