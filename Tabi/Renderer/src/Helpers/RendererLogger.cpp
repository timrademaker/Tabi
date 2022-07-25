#include "Helpers/RendererLogger.h"

#include <ConsoleSink.h>

tabi::logger::LoggerPtr s_GraphicsLogger = tabi::logger::CreateTabiLogger<tabi::logger::ConsoleSink>("Renderer");
