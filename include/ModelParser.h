/**
 * @FilePath     : /nnPlot/include/ModelParser.h
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 15:20:28
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/

#ifndef MODELPARSER_H
#define MODELPARSER_H

#include <string>
#include <vector>

struct Layer {
    std::string name;
    std::string type; // 如 "Conv", "Pool", "FC"
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
};

class Model {
public:
    void addLayer(const Layer& layer);
    const std::vector<Layer>& getLayers() const;

private:
    std::vector<Layer> layers;
};

#endif //MODELPARSER_H