// Copyright (c) 2016-2021 The future Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef future_WALLET_RPC_WALLET_H
#define future_WALLET_RPC_WALLET_H

#include <span.h>

class CRPCCommand;

namespace wallet {
Span<const CRPCCommand> GetWalletRPCCommands();
} // namespace wallet

#endif // future_WALLET_RPC_WALLET_H
