// nnPlot/LayoutEngine.cpp
#include "spdlog/sinks/basic_file_sink.h"
#include <nnPlot/Layer.h>
#include <nnPlot/LayoutEngine.h>
#include <nnPlot/Model.h>
#include <spdlog/spdlog.h>

static spdlog::logger logger("logger", std::make_shared<spdlog::sinks::basic_file_sink_mt>("LayOutEngineLog.txt"));

namespace nnPlot {

template<> void LayoutEngine<>::applyLayout(Model& model)
{
    
    mode->layout(model);
}

} // namespace nnPlot