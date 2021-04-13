#include "IResource.h"

class TestResource : public tabi::IResource
{
public:
    TestResource(const tabi::string& a_ResourcePath) { (a_ResourcePath); }
};
