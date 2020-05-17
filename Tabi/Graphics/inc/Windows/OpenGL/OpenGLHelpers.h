#pragma once


namespace tabi
{
    namespace graphics
    {
        namespace helpers
        {
            // Check if loading a mesh resulted in an error
            bool CheckMeshLoadError(unsigned int a_Buffer);

            // Check if shader compilation resulted in an error
            bool CheckShaderLoadError(unsigned int a_Shader);

            // Check if shader program compilation resulted in an error
            bool CheckShaderProgramError(unsigned int a_Program);
        }
    }
}