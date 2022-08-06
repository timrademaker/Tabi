#include "Helpers/RendererLogger.h"

#include <ConsoleSink.h>

namespace tabi
{
    namespace renderer
    {
        tabi::logger::LoggerPtr s_GraphicsLogger = tabi::logger::CreateTabiLogger<tabi::logger::ConsoleSink>("Renderer");
    }
}
