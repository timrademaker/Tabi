#pragma once

#include "../IResource.h"
#include <TabiTypes.h>

namespace tinygltf
{
    class Model;
}

namespace tabi
{
    class Camera;
    class Light;
    class Material;
    class Mesh;

    class Model : public IResource
    {
    public:
        Model() = default;
        Model(const char* a_Path);

        static tabi::shared_ptr<Model> LoadModelFromPath(const char* a_Path);
        static tabi::shared_ptr<Model> LoadBinaryModelFromPath(const char* a_Path);

        //void LoadAsLevel(tabi::GameObjectRegistry& a_Registry, bool a_LoadOnlyBaseNodes = true);

        //static void AddGameObjectType(tabi::string a_Name, tabi::unique_ptr<GameObject>(*a_CreationFunction)());

    private:
        //static bool CheckIfNameAlreadyRegistered(tabi::string a_Name);
        //static bool WriteRegisteredTypeNameToFile(tabi::string a_Name);

        static tabi::shared_ptr<Model> LoadModel(tinygltf::Model& a_GLTFModel);

        static void LoadModelRaw(const tinygltf::Model& a_Model, tabi::Model& a_OutModel);

    public:
        //tabi::vector<tabi::shared_ptr<Node>> m_BaseNodes;
        //tabi::vector<tabi::shared_ptr<Node>> m_Nodes;
        tabi::vector<tabi::shared_ptr<Mesh>> m_Meshes;

        tabi::vector<tabi::shared_ptr<Camera>> m_Cameras;
        tabi::vector<tabi::shared_ptr<Light>> m_Lights;

        tabi::shared_ptr<Camera> m_MainCamera;
    };
}