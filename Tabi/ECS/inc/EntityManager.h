#pragma once

#include "Entity.h"
#include "ECS_Constants.h"

#include <TabiContainers.h>

namespace tabi
{
    class EntityManager
    {
    public:
        // Fill the available ID list
        EntityManager();
        ~EntityManager();

        /**
         * @brief Create an entity
         * @returns The created entity
         */
        Entity CreateEntity();
        /**
         * @brief Destroy an entity
         * @params a_Entity The entity to destroy
         */
        void DestroyEntity(Entity& a_Entity);
        /**
         * @brief Get the signature of an entity (containing information about the components it has)
         * @params a_Entity The entity for which to retrieve the signature
         * @returns The signature of the given entity
         */
        EntitySignature GetSignature(const Entity& a_Entity);
        /**
         * @brief Sets the signature of an entity
         * @params a_Entity The entity of which the signature should be modified
         * @params a_Signature The signature to apply to the entity
         */
        void SetSignature(const Entity& a_Entity, const EntitySignature& a_Signature);

    public:
        tabi::array<EntitySignature, MAX_ENTITIES> m_Entities;
        tabi::queue<Entity::ID_t> m_AvailableIDs;
        size_t m_LivingEntityCount;
    };
}