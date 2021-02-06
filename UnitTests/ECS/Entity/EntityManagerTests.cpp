#include "EntityManager.h"

#include "gtest/gtest.h"

TEST(EntityTests, EntitySignature)
{
    tabi::EntityManager em;
    tabi::Entity ent = em.CreateEntity();
    const tabi::EntitySignature firstExpectedSignature{ 0b101 };
    em.SetSignature(ent, firstExpectedSignature);

    EXPECT_EQ(em.GetSignature(ent), firstExpectedSignature);

    const tabi::Entity ent2 = em.CreateEntity();
    const tabi::EntitySignature secondExpectedSignature{ 0b1010 };
    em.SetSignature(ent2, secondExpectedSignature);

    EXPECT_EQ(em.GetSignature(ent), firstExpectedSignature);
    EXPECT_EQ(em.GetSignature(ent2), secondExpectedSignature);

    em.DestroyEntity(ent);
    
    // Check if destroying one entity affects another
    EXPECT_EQ(em.GetSignature(ent2), secondExpectedSignature);
}

TEST(EntityTests, DestroyingInvalidatesEntity)
{
    tabi::EntityManager em;
    tabi::Entity ent = em.CreateEntity();
    em.DestroyEntity(ent);

    EXPECT_EQ(ent, tabi::INVALID_ENTITY_ID);
}

TEST(EntityTests, InvalidEntityInteraction)
{
    tabi::EntityManager em;

    EXPECT_DEBUG_DEATH(em.GetSignature(tabi::INVALID_ENTITY_ID), "");
}

TEST(EntityTests, MaxEntitiesReached)
{
    tabi::EntityManager em;
    for (size_t i = 0; i < tabi::MAX_ENTITIES; ++i)
    {
        em.CreateEntity();
    }

    EXPECT_DEBUG_DEATH(em.CreateEntity() , "");
}
