// The MIT License (MIT)
// C++03 Exception Class With Callstack (Windows only) 1.0
// Copyright (C) 2023 by Wong Shao Voon (shaovoon@yahoo.com)
//
// http://opensource.org/licenses/MIT
//
// version 1.0   : First release

#pragma once
#include <stdexcept>
#include <string>
#include "StackWalker.h"

struct CppException : std::runtime_error {
    CppException(const char* msg) :
        runtime_error{ msg },
        sw{} 
    {
        sw.ShowCallstack(); // despite its name, it does not show callstack, it collects them into a string.
    }
    StackWalker sw;

    std::string GetCallstack() const
    {
        return sw.GetCallstack();
    }
};
