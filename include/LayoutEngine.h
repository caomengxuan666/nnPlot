/**
 * @FilePath     : /nnPlot/include/LayoutEngine.h
 * @Description  :
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-01-20 15:21:56
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
 **/

#ifndef LAYOUTENGINE_H
#define LAYOUTENGINE_H

class Model;

class LayoutEngine {
public:
    void layout(Model& model);

private:
    void hierarchicalLayout(Model& model);
};

#endif // LAYOUTENGINE_H
