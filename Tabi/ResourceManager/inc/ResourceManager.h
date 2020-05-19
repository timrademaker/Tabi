#pragma once

#include "IResource.h"
#include <TabiTypes.h>

#include <TabiUtilities.h>

namespace tabi
{
    class ResourceManager
    {
        using ResourceMap = tabi::map<resources::ResouceID, tabi::shared_ptr<IResource>>;
        using WildcardVector = tabi::vector<tabi::pair<tabi::string, tabi::string>>;
    public:
        static ResourceManager& GetInstance();
        template<typename T = IResource, typename ... Args>
        tabi::shared_ptr<T> LoadResource(Args... a_Args);

        /**
        * @brief Replace all (valid) wildcards in a path with their actual value
        * @param a_Path The path to the file
        * @returns The file path with (valid) wildcards replaced
        */
        tabi::string GetPath(const tabi::string& a_Path) const;


        /**
        * @brief Adds a wildcard to the resource manager. If the wildcard already exists, it is replaced.
        * @param a_Wildcard The wildcard to add
        * @param a_Value the value this wildcard represents
        */
        void AddWildcard(const tabi::string& a_Wildcard, const tabi::string& a_Value);

    private:
        ResourceManager() = default;
        ~ResourceManager() = default;
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager operator=(const ResourceManager&) = delete;

    private:
        ResourceMap m_LoadedResources;

        WildcardVector m_Wildcards;
    };


    template<typename T, typename ...Args>
    inline tabi::shared_ptr<T> ResourceManager::LoadResource(Args ...a_Args)
    {
        static_assert(std::is_base_of<IResource, T>::value, "You are trying to load a resource type that is not derived from the correct base class!");

        auto id = CalculateResourceID(tabi::forward(a_Args)...);

        // Check if resource is already loaded
        ResourceMap::iterator foundRes = m_LoadedResources.find(id);
        if (foundRes == m_LoadedResources.end())
        {
            // Load resource
            tabi::shared_ptr<T> resource = tabi::make_shared<T>(tabi::forward(a_Args)...);
            
            // Add resource to loaded resources
            m_LoadedResources.insert(tabi::make_pair(id, resource));
            return resource;
        }
        else
        {
            return foundRes->second;
        }
    }
}