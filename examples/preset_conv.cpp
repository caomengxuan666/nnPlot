/**
 * @FilePath     : /nnPlot/examples/preset_conv.cpp
 * @Description  :  预设的conv的值，后续开放接口更改style
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-30 22:55:11
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/

#include <nnPlot/Concrete_style.h>
#include <iostream>

int main() {
    // 获取ConvStyle实例
    auto convStyle = nnPlot::LayerStyle::StyleFactory::createStyle("Conv");

    if (convStyle) {
        std::cout << "Applying ConvStyle..." << std::endl;
        convStyle->apply();
    } else {
        std::cerr << "Failed to get ConvStyle instance." << std::endl;
    }

    return 0;
}