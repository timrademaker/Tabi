#pragma once

#include <TabiTypes.h>

#include <cassert>

namespace tinygltf
{
    class Model;
}

namespace tabi
{
    class Camera;
    class Light;
    class Mesh;

    namespace gltf
    {
        tinygltf::Model LoadGLTFModelFromPath(const char* a_Path);
        tinygltf::Model LoadGLBModelFromPath(const char* a_Path);

        tabi::vector<char> LoadGLTFFileContentFromPath(const char* a_Path, bool a_IsBinary = false);

        tabi::vector<tabi::shared_ptr<Camera>> GetCameras(const tinygltf::Model& a_Model, tabi::shared_ptr<Camera>* a_MainCamera = nullptr);
        tabi::vector<tabi::shared_ptr<Light>> GetLights(const tinygltf::Model& a_Model);
        tabi::vector<tabi::shared_ptr<Mesh>> GetMeshes(const tinygltf::Model& a_Model);

        template<typename T>
        inline static const T* GetElementFromBuffer(const unsigned char* a_Data, const std::size_t a_Offset, const std::size_t a_Index)
        {
            assert(a_Data != nullptr);

            return reinterpret_cast<const T*>(reinterpret_cast<std::size_t>(a_Data) + a_Offset + (a_Index * sizeof(T)));
        }

    }
}