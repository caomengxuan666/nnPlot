// nnPlot/LayoutEngine.h
#ifndef LAYOUT_ENGINE_H
#define LAYOUT_ENGINE_H

namespace nnPlot {

class Model;
class LayoutEngine {
public:
    // 自动布局
    void layout(Model& model);

private:
    // 层次化布局
    void hierarchicalLayout(Model& model);
};

} // namespace nnPlot

#endif // LAYOUT_ENGINE_H