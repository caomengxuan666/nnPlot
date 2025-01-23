/**
 * @FilePath     : /nnPlot/include/nnPlot/Property.h
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-23 19:32:47
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/
#ifndef PLOTPROPERTY_H
#define PLOTPROPERTY_H

#include <sstream>
#include <string>
#include <tuple>

namespace nnPlot::Property {

// Color 结构体
struct Color {
    std::tuple<float, float, float> color;
    float alpha; // 透明度

    // 默认构造函数
    Color()
        : color { 0.0f, 0.0f, 0.0f }
        , alpha { 1.0f }
    {
    }

    // 支持从255 进制的RGB值初始化
    Color(std::tuple<int, int, int> rgb)
    {
        color = { std::get<0>(rgb) / 255.0f, std::get<1>(rgb) / 255.0f, std::get<2>(rgb) / 255.0f };
        alpha = 1.0f;
    }

    // 支持从255 进制的RGBA值初始化
    Color(std::tuple<int, int, int, int> rgba)
    {
        color = { std::get<0>(rgba) / 255.0f, std::get<1>(rgba) / 255.0f, std::get<2>(rgba) / 255.0f };
        alpha = std::get<3>(rgba) / 255.0f;
    }

    // 构造函数，支持 (r, g, b) 初始化,从0.0-1.0映射0-255
    Color(float r, float g, float b)
        : color { r, g, b }
        , alpha { 1.0f }
    {
    }

    // 构造函数，支持 (r, g, b, a) 初始化,从0.0-1.0映射0-255
    Color(float r, float g, float b, float a)
        : color { r, g, b }
        , alpha { a }
    {
    }

    // 支持从十六进制字符串初始化
    Color(const std::string& hex)
    {
        if (hex.size() == 7 && hex[0] == '#') {
            std::stringstream ss;
            ss << std::hex << hex.substr(1, 2);
            int r;
            ss >> r;
            ss.clear();
            ss << std::hex << hex.substr(3, 2);
            int g;
            ss >> g;
            ss.clear();
            ss << std::hex << hex.substr(5, 2);
            int b;
            ss >> b;
            color = { r / 255.0f, g / 255.0f, b / 255.0f };
            alpha = 1.0f;
        } else if (hex.size() == 9 && hex[0] == '#') {
            std::stringstream ss;
            ss << std::hex << hex.substr(1, 2);
            int r;
            ss >> r;
            ss.clear();
            ss << std::hex << hex.substr(3, 2);
            int g;
            ss >> g;
            ss.clear();
            ss << std::hex << hex.substr(5, 2);
            int b;
            ss >> b;
            ss.clear();
            ss << std::hex << hex.substr(7, 2);
            int a;
            ss >> a;
            color = { r / 255.0f, g / 255.0f, b / 255.0f };
            alpha = a / 255.0f;
        } else {
            throw std::invalid_argument("Invalid hex color string");
        }
    }

    Color& operator=(const Color& other)
    {
        color = other.color;
        alpha = other.alpha;
        return *this;
    }

    Color& operator=(const std::tuple<float, float, float>& other)
    {
        color = other;
        alpha = 1.0f;
        return *this;
    }

    Color(const Color& other)
        : color { other.color }
        , alpha { other.alpha }
    {
    }

    // 获取 r, g, b 的值
    float r() const { return std::get<0>(color); }
    float g() const { return std::get<1>(color); }
    float b() const { return std::get<2>(color); }
    float a() const { return alpha; }

    // 颜色混合
    Color mix(const Color& other, float ratio) const
    {
        float r = this->r() * (1 - ratio) + other.r() * ratio;
        float g = this->g() * (1 - ratio) + other.g() * ratio;
        float b = this->b() * (1 - ratio) + other.b() * ratio;
        float a = this->a() * (1 - ratio) + other.a() * ratio;
        return Color(r, g, b, a);
    }
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
    else if constexpr (N == 3)
        return color.a();
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

struct PlainText {
    std::string text;
    TextStyle textStyle;
    Opacity opacity;
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
    bool gradientEnabled; // 是否启用渐变
    Gradient gradient; // 渐变
    PlainText plainText; // 该层显示的文本内容
    Padding padding;
};

struct ConnectionStyle {
    Color color; // 连接线颜色
    LineWidth width; // 连接线宽度
    bool arrowEnabled; // 是否启用箭头
    float arrowSize; // 箭头大小
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
