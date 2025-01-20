/**
 * @FilePath     : /nnPlot/include/nnPlot/Model.h
 * @Description  :  Model
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 20:35:21
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
// nnPlot/Model.h
#ifndef NNPLOT_MODEL_H
#define NNPLOT_MODEL_H

#include <string>
#include <vector>
#include <unordered_map>
#include "nnPlot/Layer.h"

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

private:
    std::vector<Layer> layers;
    std::unordered_map<std::string, int> layerIndexMap;
};

} // namespace nnPlot

#endif // NNPLOT_MODEL_H