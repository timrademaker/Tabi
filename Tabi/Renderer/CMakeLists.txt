# CMakeList.txt : CMake project for Renderer
cmake_minimum_required (VERSION 3.8)

# Set headers for Renderer
set(HEADERS
    inc/Buffer.h
    inc/ComputePipeline.h
    inc/GraphicsPipeline.h
    inc/ICommandList.h
    inc/IDevice.h
    inc/IFence.h
    inc/RenderTarget.h
    inc/Sampler.h
    inc/Shader.h
    inc/Texture.h

    inc/TextureUpdateDescription.h

    inc/Enums/BufferEnums.h
    inc/Enums/ComparisonFunction.h
    inc/Enums/Format.h
    inc/Enums/GraphicsPipelineEnums.h
    inc/Enums/SamplerEnums.h
    inc/Enums/ShaderEnums.h
    inc/Enums/TextureEnums.h

    inc/helpers/RendererLogger.h
    inc/helpers/FormatInfo.h
)

# Set sources for Renderer
set(SOURCES
    src/IDevice.cpp

    src/helpers/RendererLogger.cpp
    src/helpers/FormatInfo.cpp
)

if(DEBUG_GRAPHICS)
    add_compile_definitions(DEBUG_GRAPHICS=1)
endif()

if(WINDOWS)
    list(APPEND HEADERS 
        
    )
    
    list(APPEND SOURCES
        
    )
endif()

if(USE_OPENGL)
    list(APPEND HEADERS 
        inc/OpenGL/OpenGLBuffer.h
        inc/OpenGL/OpenGLCommandList.h
        inc/OpenGL/OpenGLComputePipeline.h
        inc/OpenGL/OpenGLDevice.h
        inc/OpenGL/OpenGLFence.h
        inc/OpenGL/OpenGLGraphicsPipeline.h
        inc/OpenGL/OpenGLRenderTarget.h
        inc/OpenGL/OpenGLSampler.h
        inc/OpenGL/OpenGLShader.h

        inc/OpenGL/GLConverters.h
    )
    
    list(APPEND SOURCES
        src/OpenGL/OpenGLCommandList.cpp
        src/OpenGL/OpenGLDevice.cpp
        src/OpenGL/OpenGLFence.cpp

        src/OpenGL/GLConverters.cpp
    )
endif()


# Add source to this project's executable.
add_library(Renderer EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(Renderer PUBLIC TabiCommon Logger Core)

if(USE_OPENGL)
    target_link_libraries(Renderer PUBLIC GLAD)
endif()
