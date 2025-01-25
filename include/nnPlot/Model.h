/**
 * @FilePath     : /nnPlot/include/nnPlot/Model.h
 * @Description  :  Model
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-25 19:58:37
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
// nnPlot/Model.h
#ifndef NNPLOT_MODEL_H
#define NNPLOT_MODEL_H

#include <nnPlot/Layer.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace nnPlot {

class Model {
public:
    void addLayer(const Layer& layer);
    void connectLayers(const std::string& fromLayerName, const std::string& toLayerName);
    Layer& getLayer(const std::string& name);
    const Layer& getLayer(const std::string& name) const;
    std::vector<Layer>& getLayers();
    const std::vector<Layer>& getLayers() const;
    std::vector<std::string> getLayerNames() const;

    // 新增接口：设置层和节点位置
    void setLayerPosition(const std::string& layerName, int x, int y);
    void setNodePosition(const std::string& layerName, int nodeIndex, int y);

private:
    std::vector<Layer> layers;
    std::unordered_map<std::string, int> layerIndexMap;
};

} // namespace nnPlot

#endif // NNPLOT_MODEL_H