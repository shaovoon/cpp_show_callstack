// The MIT License (MIT)
// C++23 Exception Class With Callstack 1.0
// Copyright (C) 2023 by Wong Shao Voon (shaovoon@yahoo.com)
//
// http://opensource.org/licenses/MIT
//
// version 1.0   : First release


#pragma once
#include <stacktrace>
#include <stdexcept>
#include <string>
#include <string_view>

struct Cpp23ExceptionWithCallstack : std::runtime_error {
    Cpp23ExceptionWithCallstack(const char* msg) :
        runtime_error{ msg },
        m_stacktrace{ std::stacktrace::current(1 /*skipped frames*/) } {}
    std::stacktrace m_stacktrace;

    std::string GetCallstack() const
    {
        using namespace std; // without using std ns, the sv literal fails to compile. Strange.
        std::string result;
        for (const std::stacktrace_entry& entry : m_stacktrace) {
            const std::string file = entry.source_file();
            const std::string_view sview = file.empty() ? "unknown"sv : file;
            result += entry.description();
            result += ", ";
            result += sview;
            result += "(";
            result += std::to_string(entry.source_line());
            result += ")\n";
        }
        return result;
    }
};
