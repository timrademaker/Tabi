#pragma once

#include "gmock/gmock.h"

MATCHER_P(OverlapInfoMatcher, a_OverlapEvent, "")
{
    (result_listener);
    return (arg.m_OtherEntity == a_OverlapEvent.m_OtherEntity && arg.m_OverlappedCollider == a_OverlapEvent.m_OverlappedCollider);
}
