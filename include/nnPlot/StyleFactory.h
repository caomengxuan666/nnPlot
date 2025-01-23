/**
 * @FilePath     : /nnPlot/include/nnPlot/StyleFactory.h
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-23 21:15:30
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#ifndef STYLEFACTORY_H
#define STYLEFACTORY_H

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <functional>
#include<nnPlot/Style.h>

namespace nnPlot::LayerStyle {
// 工厂类
class StyleFactory {
public:
    static std::unique_ptr<Style> createStyle(const std::string& type);
    static void collectStyles(const std::string& type, std::function<std::unique_ptr<Style>()> creator);

private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Style>()>>& getStyles();
};

} // namespace nnPlot::LayerStyle
#endif