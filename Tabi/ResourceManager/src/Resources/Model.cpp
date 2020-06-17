#include "Resources/Model.h"
#include <Logging.h>

#include <ModelLoaderUtils.h>

#include <tinygltf/tiny_gltf.h>

using namespace tabi;

tabi::Model::Model(const char* a_Path)
{
    auto path = tabi::string(a_Path);
    auto dotInd = path.find_last_of(".");
    tabi::string fileExt = path.substr(dotInd + 1);

    tinygltf::Model model;

    if (fileExt == "glb")
    {
        model = tabi::gltf::LoadGLBModelFromPath(a_Path);
    }
    else if (fileExt == "gltf")
    {
        model = tabi::gltf::LoadGLTFModelFromPath(a_Path);
    }

    *this = LoadModelRaw(model);
}

tabi::shared_ptr<Model> tabi::Model::LoadModelFromPath(const char* a_Path)
{
    auto gltfModel = gltf::LoadGLTFModelFromPath(a_Path);

    return LoadModel(gltfModel);
}

tabi::shared_ptr<Model> tabi::Model::LoadBinaryModelFromPath(const char * a_Path)
{
    auto glbModel = gltf::LoadGLBModelFromPath(a_Path);

    return LoadModel(glbModel);
}

tabi::shared_ptr<Model> tabi::Model::LoadModel(tinygltf::Model & a_GLTFModel)
{
    auto model = LoadModelRaw(a_GLTFModel);

    tabi::shared_ptr<Model> loadedModel = tabi::shared_ptr<Model>(&model);

    return loadedModel;
}

Model tabi::Model::LoadModelRaw(const tinygltf::Model& a_Model)
{
    Model loadedModel;

    loadedModel.m_Cameras = gltf::GetCameras(a_Model, &loadedModel.m_MainCamera);
    loadedModel.m_Lights = gltf::GetLights(a_Model);
    loadedModel.m_Meshes = gltf::GetMeshes(a_Model);

    //loadedModel->m_BaseNodes = levelloader::GetBaseNodes(a_GLTFModel, &(loadedModel->m_Nodes));

    //// Set meshes for all nodes that should have one
    //for (auto& node : loadedModel->m_Nodes)
    //{
    //    if (node->m_MeshIndex >= 0)
    //    {
    //        node->m_Mesh = loadedModel->m_Meshes.at(node->m_MeshIndex);
    //    }
    //}

    return loadedModel;
}
