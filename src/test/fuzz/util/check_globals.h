// Copyright (c) 2024-present The future Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef future_TEST_FUZZ_UTIL_CHECK_GLOBALS_H
#define future_TEST_FUZZ_UTIL_CHECK_GLOBALS_H

#include <atomic>
#include <memory>
#include <optional>
#include <string>

extern std::atomic<bool> g_used_system_time;

struct CheckGlobalsImpl;
struct CheckGlobals {
    CheckGlobals();
    ~CheckGlobals();
    std::unique_ptr<CheckGlobalsImpl> m_impl;
};

#endif // future_TEST_FUZZ_UTIL_CHECK_GLOBALS_H