/**
 * @FilePath     : /nnPlot/include/Layer.h
 * @Description  :  
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 18:40:42
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <vector>

namespace nnPlot {

struct Layer {
    std::string name;                // 层名称
    std::string type;                // 层类型（如 "Input", "Dense", "Conv2D"）
    std::vector<std::string> inputs; // 输入层名称
    std::vector<std::string> outputs; // 输出层名称

    Layer(const std::string& name, const std::string& type);
};

} // namespace nnPlot

#endif // LAYER_H