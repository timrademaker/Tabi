#include "TestResource.h"

#include "ResourceManager.h"

#include "gtest/gtest.h"

TEST(ResourceManagerTests, LoadSameResourceTwice)
{
    tabi::ResourceManager& rm = tabi::ResourceManager::GetInstance();
    const auto expectedResource = rm.LoadResource<TestResource>("TestPath");
    const auto foundResource = rm.LoadResource<TestResource>("TestPath");

    EXPECT_EQ(foundResource, expectedResource);

    const auto otherResource = rm.LoadResource<TestResource>("OtherPath");
    EXPECT_NE(otherResource, expectedResource);
}

TEST(ResourceManagerTests, WildcardReplacement)
{
    const tabi::string assetDirectory = "AssetPath";
    const tabi::string assetDirectoryWildcard = "[Assets]";
    const tabi::string assetName = "TestAsset.obj";

    const tabi::string platformName = "Win64";
    const tabi::string platformNameWildcard = "[Platform]";

    tabi::ResourceManager& rm = tabi::ResourceManager::GetInstance();

    rm.AddWildcard(assetDirectoryWildcard, assetDirectory);
    rm.AddWildcard(platformNameWildcard, platformName);

    // Single wildcard
    {
        const tabi::string inAssetPath = assetDirectoryWildcard + "/" + assetName;
        const tabi::string expectedPath = assetDirectory + "/" + assetName;

        EXPECT_STREQ(rm.GetPath(inAssetPath).c_str(), expectedPath.c_str());
    }

    // Two wildcards
    {
        const tabi::string inAssetPath = assetDirectoryWildcard + "/" + platformNameWildcard + "/" + assetName;
        const tabi::string expectedPath = assetDirectory + "/" + platformName + "/" + assetName;

        EXPECT_STREQ(rm.GetPath(inAssetPath).c_str(), expectedPath.c_str());
    }

    // Same wildcard twice
    {
        const tabi::string inAssetPath = platformNameWildcard + "/" + assetDirectoryWildcard + "/" + platformNameWildcard + "/" + assetName;
        const tabi::string expectedPath = platformName + "/" + assetDirectory + "/" + platformName + "/" + assetName;

        EXPECT_STREQ(rm.GetPath(inAssetPath).c_str(), expectedPath.c_str());
    }

    // Invalid wildcard
    {
        const tabi::string assetPath = "[Test]/abc.obj";
        EXPECT_STREQ(rm.GetPath(assetPath).c_str(), assetPath.c_str());
    }
}
