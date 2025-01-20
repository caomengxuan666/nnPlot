/**
 * @FilePath     : /nnPlot/include/nnPlot/Layer.h
 * @Description  :  Layers
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 20:35:35
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
// nnPlot/Layer.h
#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <vector>

namespace nnPlot {

class Layer {
public:
    // 构造函数，支持名称、标签和节点数量
    Layer(const std::string& name, const std::string& label, int nodeCount = 1);

    // 获取层名称
    const std::string& getName() const;

    // 获取层标签
    const std::string& getLabel() const;

    // 获取节点数量
    int getNodeCount() const;

    // 设置节点数量
    void setNodeCount(int nodeCount);

    // 获取层的 X 坐标
    double getX() const;

    // 获取层的 Y 坐标
    double getY() const;

    // 设置层的 X 坐标
    void setX(double x);

    // 设置层的 Y 坐标
    void setY(double y);

    // 获取输入连接
    const std::vector<std::string>& getInputs() const;

    // 获取输出连接
    const std::vector<std::string>& getOutputs() const;

    // 添加输入连接
    void addInput(const std::string& input);

    // 添加输出连接
    void addOutput(const std::string& output);

    void setNodeY(double y, int index);

    double getNodeY(int index) const;

private:
    std::string name; // 层名称
    std::string label; // 层标签
    int nodeCount; // 节点数量
    double x, y; // 层的坐标
    std::vector<std::string> inputs; // 输入连接
    std::vector<std::string> outputs; // 输出连接
    std::vector<double> nodeYPositions;
};

} // namespace nnPlot

#endif // LAYER_H