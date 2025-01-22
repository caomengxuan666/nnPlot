/**
 * @FilePath     : /nnPlot/include/nnPlot/Property.h
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-22 19:52:22
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#ifndef PLOTPROPERTY_H
#define PLOTPROPERTY_H

#include <string>
#include <tuple>

namespace nnPlot::Property {

// Color 结构体
struct Color {
    std::tuple<float, float, float> color;

    // 默认构造函数
    Color()
        : color { 0.0f, 0.0f, 0.0f }
    {
    }

    // 构造函数，支持 (r, g, b) 初始化
    Color(float r, float g, float b)
        : color { r, g, b }
    {
    }

    // 获取 r, g, b 的值
    float r() const { return std::get<0>(color); }
    float g() const { return std::get<1>(color); }
    float b() const { return std::get<2>(color); }
};

// 特化 std::tuple_size 和 std::tuple_element 以支持结构化绑定
// 实现 get<N> 以支持结构化绑定
template <std::size_t N>
inline constexpr float get(const Color& color)
{
    if constexpr (N == 0)
        return color.r();
    else if constexpr (N == 1)
        return color.g();
    else if constexpr (N == 2)
        return color.b();
}

struct LineWidth {
    float width;
};

struct Opacity {
    float value; // from 0.0-1.0f
};

struct Font {
    std::string family; // 字体族，例如 "Sans", "Serif"
    float size; // 字体大小
    bool bold; // 是否加粗
    bool italic; // 是否斜体
};

struct LayerStyle {
    Color fillColor; // 填充颜色
    Color borderColor; // 边框颜色
    LineWidth borderWidth; // 边框宽度
    float borderRadius; // 边框圆角半径
    bool shadowEnabled; // 是否启用阴影
    Color shadowColor; // 阴影颜色
    float shadowOffsetX; // 阴影 X 偏移
    float shadowOffsetY; // 阴影 Y 偏移
    float shadowBlur; // 阴影模糊半径
};

struct ConnectionStyle {
    Color color; // 连接线颜色
    LineWidth width; // 连接线宽度
    bool arrowEnabled; // 是否启用箭头
    float arrowSize; // 箭头大小
};

struct TextStyle {
    Color color; // 文本颜色
    Font font; // 字体
    std::string alignment; // 对齐方式，例如 "left", "center", "right"
};

struct Shadow {
    Color color; // 阴影颜色
    float offsetX; // 阴影 X 偏移
    float offsetY; // 阴影 Y 偏移
    float blur; // 阴影模糊半径
};

struct Padding {
    float top;
    float right;
    float bottom;
    float left;
};

struct Gradient {
    Color startColor; // 渐变起始颜色
    Color endColor; // 渐变结束颜色
    float angle; // 渐变角度
};

struct PlotProperty {
    LayerStyle layerStyle; // 图层样式
    ConnectionStyle connectionStyle; // 连接线样式
    TextStyle textStyle; // 文本样式
    Shadow shadow; // 阴影
    Padding padding; // 内边距
    Gradient gradient; // 渐变
};

} // namespace nnPlot::Property

namespace std {
template <>
struct tuple_size<nnPlot::Property::Color> : integral_constant<size_t, 3> { };

template <size_t N>
struct tuple_element<N, nnPlot::Property::Color> {
    using type = float;
};
} // namespace std

#endif // PLOTPROPERTY_H
