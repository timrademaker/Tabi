#include "Resources/Model.h"
#include <Logging.h>

#include <ModelLoaderUtils.h>

#include <tinygltf/tiny_gltf.h>

using namespace tabi;


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
    tabi::shared_ptr<Model> loadedModel = tabi::make_shared<Model>();


    loadedModel->m_Cameras = gltf::GetCameras(a_GLTFModel, &loadedModel->m_MainCamera);
    loadedModel->m_Lights = gltf::GetLights(a_GLTFModel);
    loadedModel->m_Meshes = gltf::GetMeshes(a_GLTFModel);

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
