#include "ISink.h"

#include "gmock/gmock.h"

class MockSink : public tabi::logger::ISink
{
public:
    MOCK_METHOD(void, SinkMessage, (const SinkMsg_t& a_Message), (override));
    MOCK_METHOD(void, Flush, (), (override));
};
