#pragma once
#include "Common/Resources.h"

#include <fmt/format.h>

namespace CT_COMMON_NAMESPACE
{
#ifndef CT_EXCEPTION_MESSAGE
    #ifdef CT_DEBUG
        #define CT_EXCEPTION_MESSAGE(message) fmt::format("{}\nFile: {}\nLine: {}", message, __FILE__, __LINE__)
    #else
        #define CT_EXCEPTION_MESSAGE(message) message
    #endif
#endif

#ifndef CT_THROW
    #define CT_THROW(message)        throw std::runtime_error(CT_EXCEPTION_MESSAGE(message))
    #define CT_THROW_FROM(exception) throw std::runtime_error(CT_EXCEPTION_MESSAGE(exception.what()));
#endif
} // namespace CT_COMMON_NAMESPACE
