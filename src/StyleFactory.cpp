/**
 * @FilePath     : /nnPlot/src/StyleFactory.cpp
 * @Description  :  
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-30 23:49:16
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
#include <nnPlot/StyleFactory.h>
#include <stdexcept>
namespace nnPlot::LayerStyle {

std::unordered_map<std::string, std::function<std::unique_ptr<Style>()>>& StyleFactory::getStyles() {
    static std::unordered_map<std::string, std::function<std::unique_ptr<Style>()>> styles;
    return styles;
}

std::unique_ptr<Style> StyleFactory::createStyle(const std::string& type) {
    auto it = getStyles().find(type);
    if (it != getStyles().end()) {
        return it->second();
    } else {
        throw std::invalid_argument("Unknown style type");
    }
}

void StyleFactory::collectStyles(const std::string& type, std::function<std::unique_ptr<Style>()> creator) {
    getStyles()[type] = creator;
}

} // namespace nnPlot::LayerStyle