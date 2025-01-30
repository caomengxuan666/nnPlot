/**
 * @FilePath     : /nnPlot/include/nnPlot/Style.h
 * @Description  : 声明具体模块的样式，Style是所有具体模块的样式父类
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-30 23:13:35
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#ifndef STYLE_H
#define STYLE_H

#include "Property.h"
#include <memory>
#include<functional>

namespace nnPlot {

/**
 * @author       : cmx
 * @brief        : Style类，决定了当前层和下一个连接的样式。
 * @note         : 这里虽然只有一个apply接口，但是建议在子类实现中分别设置当前层与下一连接的。
                   当前层和下一个连接的Style
 * @return        {*}
**/
class Style {
public:
    virtual ~Style() = default;
    virtual void apply()const  = 0;
 // 静态方法，用于注册样式
    static void registerSelf(const std::string& type, std::function<std::unique_ptr<Style>()> creator);
    //todo
    Property::LayerStyle layerStyle;
    Property::ConnectionStyle* nextConnectionStyle;
};

/*
具体样式子类，你可以在其他文件里面实现它。
namespace nnPlot ::LayerStyle {

class ConvStyle : public Style {
public:
    void applyStyle() const override;
    static const std::string& getType()
    {
        static const std::string type = "Conv";
        return type;
    }
    // 使用模板方法进行注册
    static void registerStyle()
    {
        Style::registerStyle<ConvStyle>();
    }
};

class PoolingStyle : public Style {
public:
    void applyStyle() const override;
    // 提供一个静态方法返回类型的字符串标识
    static const std::string& getType()
    {
        static const std::string type = "Pooling";
        return type;
    }

    // 使用模板方法进行注册
    static void registerStyle()
    {
        Style::registerStyle<PoolingStyle>();
    }
};
}

*/

// 上下文类
class StyleContext {
public:
    StyleContext(std::unique_ptr<Style> strategy)
        : strategy_(std::move(strategy))
    {
    }

    void setStrategy(std::unique_ptr<Style> strategy)
    {
        strategy_ = std::move(strategy);
    }

    void applyStyle() const
    {
        strategy_->apply();
    }

private:
    std::unique_ptr<Style> strategy_;
};

} // namespace nnPlot
#endif // !STYLE_H