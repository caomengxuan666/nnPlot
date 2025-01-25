/**
 * @FilePath     : /nnPlot/include/nnPlot/Concrete_style.h
 * @Description  :  在这里实现具体的层，比方说我们的卷积层，池化层，我们最后希望的是example中，用户可以直接调用封装好的类
                    ,最多最多自定再加几个自定义类就可以完成复杂神经网络的绘制，我们的主要目的是服务于大众，以简单的方式绘制更漂亮的图。
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-23 21:34:00
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#ifndef CONCRETE_STYLE_H
#define CONCRETE_STYLE_H

#include "Style.h"
#include "StyleFactory.h"
#include <memory>

namespace nnPlot::LayerStyle {

class ConvStyle : public Style {
public:
    void apply() const override;
    // 注册器类
    class Register {
    public:
        Register()
        {
            ConvStyle::registerSelf();
        }
    };

private:
    static void registerSelf()
    {
        StyleFactory::collectStyles("Conv", []() { return std::make_unique<ConvStyle>(); });
    }

    // 静态实例，确保在程序启动时自动注册
    static Register registerInstance;
};

class PoolingStyle : public Style {
public:
    void apply() const override;
    // 注册器类
    class Register {
    public:
        Register()
        {
            PoolingStyle::registerSelf();
        }
    };

private:
    static void registerSelf()
    {
        StyleFactory::collectStyles("Pooling", []() { return std::make_unique<PoolingStyle>(); });
    }

    // 静态实例，确保在程序启动时自动注册
    static Register registerInstance;
};

} // namespace nnPlot::LayerStyle
#endif