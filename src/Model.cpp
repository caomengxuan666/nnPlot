// nnPlot/Model.cpp
#include "nnPlot/Model.h"
#include <stdexcept>

namespace nnPlot {

void Model::addLayer(const Layer& layer) {
    layers.push_back(layer);
    layerIndexMap[layer.getName()] = layers.size() - 1;
}

void Model::connectLayers(const std::string& fromLayerName, const std::string& toLayerName) {
    if (layerIndexMap.find(fromLayerName) == layerIndexMap.end() || layerIndexMap.find(toLayerName) == layerIndexMap.end()) {
        throw std::runtime_error("Layer not found");
    }
    layers[layerIndexMap.at(toLayerName)].addInput(fromLayerName);
    layers[layerIndexMap.at(fromLayerName)].addOutput(toLayerName);
}

Layer& Model::getLayer(const std::string& name) {
    if (layerIndexMap.find(name) == layerIndexMap.end()) {
        throw std::runtime_error("Layer not found");
    }
    return layers[layerIndexMap.at(name)];
}

const Layer& Model::getLayer(const std::string& name) const {
    if (layerIndexMap.find(name) == layerIndexMap.end()) {
        throw std::runtime_error("Layer not found");
    }
    return layers[layerIndexMap.at(name)];
}

std::vector<Layer>& Model::getLayers() {
    return layers;
}

const std::vector<Layer>& Model::getLayers() const {
    return layers;
}

std::vector<std::string> Model::getLayerNames() const {
    std::vector<std::string> names;
    for (const auto& layer : layers) {
        names.push_back(layer.getName());
    }
    return names;
}

} // namespace nnPlot