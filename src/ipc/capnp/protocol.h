// Copyright (c) 2021 The future Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef future_IPC_CAPNP_PROTOCOL_H
#define future_IPC_CAPNP_PROTOCOL_H

#include <memory>

namespace ipc {
class Protocol;
namespace capnp {
std::unique_ptr<Protocol> MakeCapnpProtocol();
} // namespace capnp
} // namespace ipc

#endif // future_IPC_CAPNP_PROTOCOL_H
