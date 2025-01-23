/**
 * @FilePath     : /nnPlot/src/Concrete_style.cpp
 * @Description  :  具体的类的实现，这里实现一些比较经典的样式
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-23 21:40:41
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#include <nnPlot/Concrete_style.h>


namespace nnPlot::LayerStyle {

void ConvStyle::apply() const
{
    // todo  实现卷积层的绘图样式
}

void PoolingStyle::apply() const
{
    // todo  实现池化层的绘图样式
}

// 初始化静态实例
ConvStyle::Register ConvStyle::registerInstance;
PoolingStyle::Register PoolingStyle::registerInstance;
}
