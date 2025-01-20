#ifndef MODEL_H
#define MODEL_H

#include "Layer.h"
#include <vector>
#include <unordered_map>

namespace nnPlot {

class Model {
public:
    // 添加层
    void addLayer(const Layer& layer);

    // 连接层
    void connectLayers(const std::string& from, const std::string& to);

    // 获取所有层
    const std::vector<Layer>& getLayers() const;

    // 获取指定层
    const Layer& getLayer(const std::string& name) const;

private:
    std::vector<Layer> layers; // 所有层
    std::unordered_map<std::string, size_t> layerIndex; // 层名称到索引的映射
};

} // namespace nnPlot

#endif // MODEL_H