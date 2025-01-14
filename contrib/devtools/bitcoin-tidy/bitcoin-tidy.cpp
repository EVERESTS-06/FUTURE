// Copyright (c) 2023 future Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "nontrivial-threadlocal.h"

#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

class futureModule final : public clang::tidy::ClangTidyModule
{
public:
    void addCheckFactories(clang::tidy::ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<future::NonTrivialThreadLocal>("future-nontrivial-threadlocal");
    }
};

static clang::tidy::ClangTidyModuleRegistry::Add<futureModule>
    X("future-module", "Adds future checks.");

volatile int futureModuleAnchorSource = 0;
