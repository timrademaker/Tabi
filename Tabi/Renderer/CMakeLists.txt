# CMakeList.txt : CMake project for Renderer
cmake_minimum_required (VERSION 3.8)

# Set headers for Renderer
set(HEADERS
    inc/IBuffer.h
    inc/ICommandList.h
    inc/IComputePipeline.h
    inc/IDevice.h
    inc/IFence.h
    inc/IGraphicsPipeline.h
    inc/IRenderTarget.h
    inc/ISampler.h
    inc/IShader.h
    inc/ITexture.h

    inc/TextureUpdateDescription.h

    inc/Enums/Format.h
    inc/Enums/ComparisonFunction.h
)

# Set sources for Renderer
set(SOURCES
    src/IDevice.cpp
)

if(WINDOWS)
    list(APPEND HEADERS 
        
    )
    
    list(APPEND SOURCES
        
    )
endif()

if(USE_OPENGL)
    list(APPEND HEADERS 
        
    )
    
    list(APPEND SOURCES
        
    )
endif()

# Add source to this project's executable.
add_library(Renderer EXCLUDE_FROM_ALL ${SOURCES} ${HEADERS})

target_include_directories(Renderer PUBLIC ${CMAKE_CURRENT_LIST_DIR}/inc)

# Add libraries
target_link_libraries(Renderer PUBLIC TabiCommon Logger Core)
