#pragma once

#include "Entity.h"
#include "ISystem.h"

#include <TabiContainers.h>
#include <TabiPointers.h>
#include <TabiMacros.h>

namespace tabi
{
    // The signature of a system. Represents the components required for this system
    using SystemSignature = bitset<MAX_COMPONENTS>;

    class SystemManager
    {
        using SystemTypeHash = const char*;

    public:
        /**
         * @brief Register a new system
         * @params a_ComponentManager The ComponentManager this system is used on
         * @returns The created system
         */
        template<typename SystemType>
        tabi::shared_ptr<SystemType> RegisterSystem(ComponentManager* a_ComponentManager);

        /**
         * @brief Gets a registered system
         * @returns The requested system
         */
        template<typename SystemType>
        tabi::shared_ptr<SystemType> GetSystem();

        /**
         * @brief Should be called when an entity is destroyed
         * @params a_Entity The entity that was destroyed
         */
        void OnEntityDestroyed(const Entity a_Entity);
        /**
         * @brief Should be called when an entity's signature changes
         * @params a_Entity The entity of which the signature changed
         * @params a_Signature The entity's signature
         */
        void OnEntitySignatureChanged(const Entity a_Entity, EntitySignature a_Signature);

        /**
         * @brief Updates all registered systems
         * @params a_DeltaTime The time between the previous update and this update
         */
        void Update(float a_DeltaTime) const;
        /**
         * @brief Calls OnRender() on all registered systems
         */
        void Render() const;

    private:
        /**
         * @brief Hashes a system type. The hash can be used as a key in a map
         * @returns A hash of the system type
         */
        template<typename SystemType>
        static SystemTypeHash CreateHash();

    private:
        /** A map containing registered systems */
        tabi::map<SystemTypeHash, tabi::shared_ptr<ISystem>> m_Systems;
    };

    template <typename SystemType>
    tabi::shared_ptr<SystemType> SystemManager::RegisterSystem(ComponentManager* a_ComponentManager)
    {
        const SystemTypeHash hash = CreateHash<SystemType>();

        // Check if the system has already been registered
        TABI_ASSERT(m_Systems.find(hash) == m_Systems.end());

        auto system = tabi::make_shared<SystemType>(a_ComponentManager);
        m_Systems.insert(tabi::make_pair(hash, system));

        return system;
    }

    template<typename SystemType>
    inline tabi::shared_ptr<SystemType> SystemManager::GetSystem()
    {
        const SystemTypeHash hash = CreateHash<SystemType>();
        // Check if the system has already been registered
        TABI_ASSERT(m_Systems.find(hash) != m_Systems.end());
        return std::static_pointer_cast<SystemType>(m_Systems[hash]);
    }

    template <typename SystemType>
    inline SystemManager::SystemTypeHash SystemManager::CreateHash()
    {
        return typeid(SystemType).name();
    }
}
