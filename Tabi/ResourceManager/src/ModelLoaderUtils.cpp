#include "ModelLoaderUtils.h"

#include <Math/vec3.h>

#include <Camera.h>
#include <Light.h>
#include <Resources/Mesh.h>

#include <Logging.h>

#include <IFile.h>


#ifndef TINYGLTF_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#endif

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#include <tinygltf/tiny_gltf.h>


#if defined(DIRECTX)
constexpr bool swapZPositionSign = true;
#else
constexpr bool swapZPositionSign = false;
#endif

tinygltf::Model tabi::gltf::LoadGLTFModelFromPath(const char* a_Path)
{
    auto gltfContent = LoadGLTFFileContentFromPath(a_Path, false);

    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    if (!loader.LoadASCIIFromString(&model, &err, &warn, &gltfContent[0], static_cast<unsigned int>(gltfContent.size()), "Assets"))
    {
        TABI_ERROR("Unable to load gltf model from string. \nError: %s\nWarning:%s\nModel Path: %s", err.c_str(), warn.c_str(), a_Path);
    }

    return model;

}

tinygltf::Model tabi::gltf::LoadGLBModelFromPath(const char* a_Path)
{
    auto gltfContent = LoadGLTFFileContentFromPath(a_Path, true);

    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    {
        if (!loader.LoadBinaryFromMemory(&model, &err, &warn, (unsigned char*)(&gltfContent[0]), static_cast<unsigned int>(gltfContent.size()), "Assets"))
        {
            TABI_ERROR("Unable to load glb model from string. \nError: %s\nWarning:%s\nModel Path: %s", err.c_str(), warn.c_str(), a_Path);
        }
    }

    return model;
}

tabi::vector<char> tabi::gltf::LoadGLTFFileContentFromPath(const char* a_Path, bool a_IsBinary)
{

    EFileOpenFlags flags = EFileOpenFlags::Read;

    if (a_IsBinary)
    {
        flags |= EFileOpenFlags::Binary;
    }

    auto file = IFile::OpenFile(a_Path, flags);
    if (!file)
    {
        TABI_ERROR("Unable to open file for model %s", a_Path);
        assert(false);
        return {};
    }

    FSize fileLength = 0;
    file->GetLength(fileLength);
    tabi::vector<char> gltfContent(fileLength);

    FSize read = 0;
    auto res = file->Read(&gltfContent[0], fileLength, &read);
    if ((res & EFileResult::Ok) != EFileResult::Ok)
    {
        TABI_ERROR("Something went wrong when reading the file for model %s", a_Path);
        assert(false);
        return {};
    }

    if (a_IsBinary)
    {
        assert(fileLength == read);
    }

    return gltfContent;
}

tabi::vector<tabi::shared_ptr<tabi::Camera>> tabi::gltf::GetCameras(const tinygltf::Model& a_Model,
    tabi::shared_ptr<Camera>* a_MainCamera)
{
    tabi::vector<tabi::shared_ptr<Camera>> cameras;
    cameras.reserve(a_Model.cameras.size());
    tabi::vector<int> cameraNodeIndices;
    cameraNodeIndices.reserve(a_Model.cameras.size());

    for (std::size_t i = 0; i < a_Model.nodes.size(); ++i)
    {
        auto& node = a_Model.nodes.at(i);

        if (node.camera != -1)
        {
            auto camera = a_Model.cameras.at(node.camera);

            auto cam = tabi::make_shared<Camera>(camera.perspective.aspectRatio);
            cam->SetNear(static_cast<float>(camera.perspective.znear));
            cam->SetFar(static_cast<float>(camera.perspective.zfar));
            //cam->m_FoV = static_cast<float>(glm::degrees(camera.perspective.yfov));

            cameraNodeIndices.push_back(static_cast<int>(i));

            cameras.push_back(std::move(cam));
        }

        if (!node.children.empty())
        {
            // See if any of the camera indices are in the node's child nodes

            for (std::size_t j = 0; j < cameraNodeIndices.size(); ++j)
            {
                assert(cameras.size() > j);

                auto ind = cameraNodeIndices[j];
                auto nodeChildIter = std::find(node.children.begin(), node.children.end(), ind);

                if (nodeChildIter != node.children.end())
                {
                    auto& cam = cameras.at(j);

                    float zFlip = 1.0f;
                    if (swapZPositionSign)
                    {
                        zFlip = -1.0f;
                    }

                    if (!node.translation.empty())
                    {
                        cam->MoveTo({
                            static_cast<float>(node.translation[0])
                            , static_cast<float>(node.translation[1])
                            , static_cast<float>(node.translation[2]) * zFlip
                        });
                    }

                    if (!node.rotation.empty())
                    {
                        //glm::quat rotation = glm::quat(
                        //    static_cast<float>(node.rotation[3])
                        //    , static_cast<float>(node.rotation[0])
                        //    , static_cast<float>(node.rotation[1])
                        //    , static_cast<float>(node.rotation[2])
                        //);
                        //cam->RotateBy(rotation);
                    }
                }
            }
        }

        if (a_MainCamera)
        {
            if (node.extras.Has("IsMainCamera") && node.extras.Get("IsMainCamera").GetNumberAsInt() == 1)
            {
                *a_MainCamera = cameras.back();
            }
        }
    }

    return cameras;
}

tabi::vector<tabi::shared_ptr<tabi::Light>> tabi::gltf::GetLights(const tinygltf::Model& a_Model)
{
    tabi::vector<tabi::shared_ptr<Light>> lights;
    lights.reserve(a_Model.lights.size());

    tabi::vector<tabi::pair<tabi::string, tabi::shared_ptr<Light>>> incompleteLights;
    incompleteLights.reserve(a_Model.lights.size());

    for (auto& light : a_Model.lights)
    {
        auto l = tabi::make_shared<Light>();

        l->m_Color = tabi::vec3(
            static_cast<float>(light.color[0]),
            static_cast<float>(light.color[1]),
            static_cast<float>(light.color[2])
        );

        l->m_Intensity = static_cast<float>(light.intensity);

        if (light.type == "point")
        {
            l->m_LightType = ELightType::Point;
        }

        incompleteLights.push_back(tabi::pair<tabi::string, tabi::shared_ptr<Light>>(tabi::string(light.name.c_str()), l));
    }

    for (std::size_t i = 0; i < a_Model.nodes.size(); ++i)
    {
        for (auto iter = incompleteLights.begin(); iter != incompleteLights.end(); ++iter)
        {
            if (tabi::string(a_Model.nodes[i].name.c_str()) == iter->first) {
                if (!a_Model.nodes[i].rotation.empty())
                {
                    //iter->second->RotateTo(glm::quat(
                    //    static_cast<float>(a_Model.nodes[i].rotation[3]),
                    //    static_cast<float>(a_Model.nodes[i].rotation[0]),
                    //    static_cast<float>(a_Model.nodes[i].rotation[1]),
                    //    static_cast<float>(a_Model.nodes[i].rotation[2])
                    //));
                }

                if (!a_Model.nodes[i].translation.empty())
                {
                    iter->second->m_Position = tabi::vec3(
                        static_cast<float>(a_Model.nodes[i].translation[0]), 
                        static_cast<float>(a_Model.nodes[i].translation[1]),
                        static_cast<float>(a_Model.nodes[i].translation[2])
                    );

                    if (swapZPositionSign)
                    {
                        iter->second->m_Position.z = -iter->second->m_Position.z;
                    }

                    
                }

                lights.push_back(iter->second);
                incompleteLights.erase(iter);

                break;
            }
        }
    }

    return lights;
}

tabi::vector<tabi::shared_ptr<tabi::Mesh>> tabi::gltf::GetMeshes(const tinygltf::Model& a_Model)
{
    tabi::vector<tabi::shared_ptr<Mesh>> meshes;
    auto& meshArray = a_Model.meshes;
    meshes.reserve(meshArray.size());

    for (std::size_t i = 0; i < meshArray.size(); ++i)
    {
        auto m = tabi::Mesh::LoadMesh(a_Model, i);

        meshes.push_back(m);
    }

    return meshes;
}
