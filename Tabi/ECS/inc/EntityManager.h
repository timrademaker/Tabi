#pragma once

#include "Entity.h"
#include "ECS_Constants.h"

#include <TabiContainers.h>

namespace tabi
{
    class EntityManager
    {
    public:
        EntityManager();
        EntityManager(EntityManager&) = delete;
        EntityManager(const EntityManager&) = delete;
        ~EntityManager() = default;        

        /**
         * @brief Create an entity
         * @returns The created entity
         */
        Entity CreateEntity();

        /**
         * @brief Destroy an entity and invalidates it
         * @params a_Entity The entity to destroy
         */
        void DestroyEntity(Entity& a_Entity);
        
        /**
         * @brief Get the signature of an entity (containing information about the components it has)
         * @params a_Entity The entity for which to retrieve the signature
         * @returns The signature of the entity
         */
        EntitySignature GetSignature(const Entity a_Entity) const;

        /**
         * @brief Sets the signature of an entity
         * @params a_Entity The entity of which the signature should be modified
         * @params a_Signature The signature to apply to the entity
         */
        void SetSignature(const Entity a_Entity, const EntitySignature& a_Signature);

        /**
         * @brief Get all entity signatures
         * @returns An array with all entitiy signatures (including entities that aren't alive)
         */
        const tabi::array<EntitySignature, MAX_ENTITIES>& GetAllSignatures();

    private:
        /// The signatures of all the entities
        tabi::array<EntitySignature, MAX_ENTITIES> m_EntitySignatures;
        /// EntityIDs which are not currently taken
        tabi::queue<Entity> m_AvailableIDs;
    };
}