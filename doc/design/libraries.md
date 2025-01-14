# Libraries

| Name                     | Description |
|--------------------------|-------------|
| *libfuture_cli*         | RPC client functionality used by *future-cli* executable |
| *libfuture_common*      | Home for common functionality shared by different executables and libraries. Similar to *libfuture_util*, but higher-level (see [Dependencies](#dependencies)). |
| *libfuture_consensus*   | Consensus functionality used by *libfuture_node* and *libfuture_wallet*. |
| *libfuture_crypto*      | Hardware-optimized functions for data encryption, hashing, message authentication, and key derivation. |
| *libfuture_kernel*      | Consensus engine and support library used for validation by *libfuture_node*. |
| *libfutureqt*           | GUI functionality used by *future-qt* and *future-gui* executables. |
| *libfuture_ipc*         | IPC functionality used by *future-node*, *future-wallet*, *future-gui* executables to communicate when [`-DWITH_MULTIPROCESS=ON`](multiprocess.md) is used. |
| *libfuture_node*        | P2P and RPC server functionality used by *futured* and *future-qt* executables. |
| *libfuture_util*        | Home for common functionality shared by different executables and libraries. Similar to *libfuture_common*, but lower-level (see [Dependencies](#dependencies)). |
| *libfuture_wallet*      | Wallet functionality used by *futured* and *future-wallet* executables. |
| *libfuture_wallet_tool* | Lower-level wallet functionality used by *future-wallet* executable. |
| *libfuture_zmq*         | [ZeroMQ](../zmq.md) functionality used by *futured* and *future-qt* executables. |

## Conventions

- Most libraries are internal libraries and have APIs which are completely unstable! There are few or no restrictions on backwards compatibility or rules about external dependencies. An exception is *libfuture_kernel*, which, at some future point, will have a documented external interface.

- Generally each library should have a corresponding source directory and namespace. Source code organization is a work in progress, so it is true that some namespaces are applied inconsistently, and if you look at [`add_library(future_* ...)`](../../src/CMakeLists.txt) lists you can see that many libraries pull in files from outside their source directory. But when working with libraries, it is good to follow a consistent pattern like:

  - *libfuture_node* code lives in `src/node/` in the `node::` namespace
  - *libfuture_wallet* code lives in `src/wallet/` in the `wallet::` namespace
  - *libfuture_ipc* code lives in `src/ipc/` in the `ipc::` namespace
  - *libfuture_util* code lives in `src/util/` in the `util::` namespace
  - *libfuture_consensus* code lives in `src/consensus/` in the `Consensus::` namespace

## Dependencies

- Libraries should minimize what other libraries they depend on, and only reference symbols following the arrows shown in the dependency graph below:

<table><tr><td>

```mermaid

%%{ init : { "flowchart" : { "curve" : "basis" }}}%%

graph TD;

future-cli[future-cli]-->libfuture_cli;

futured[futured]-->libfuture_node;
futured[futured]-->libfuture_wallet;

future-qt[future-qt]-->libfuture_node;
future-qt[future-qt]-->libfutureqt;
future-qt[future-qt]-->libfuture_wallet;

future-wallet[future-wallet]-->libfuture_wallet;
future-wallet[future-wallet]-->libfuture_wallet_tool;

libfuture_cli-->libfuture_util;
libfuture_cli-->libfuture_common;

libfuture_consensus-->libfuture_crypto;

libfuture_common-->libfuture_consensus;
libfuture_common-->libfuture_crypto;
libfuture_common-->libfuture_util;

libfuture_kernel-->libfuture_consensus;
libfuture_kernel-->libfuture_crypto;
libfuture_kernel-->libfuture_util;

libfuture_node-->libfuture_consensus;
libfuture_node-->libfuture_crypto;
libfuture_node-->libfuture_kernel;
libfuture_node-->libfuture_common;
libfuture_node-->libfuture_util;

libfutureqt-->libfuture_common;
libfutureqt-->libfuture_util;

libfuture_util-->libfuture_crypto;

libfuture_wallet-->libfuture_common;
libfuture_wallet-->libfuture_crypto;
libfuture_wallet-->libfuture_util;

libfuture_wallet_tool-->libfuture_wallet;
libfuture_wallet_tool-->libfuture_util;

classDef bold stroke-width:2px, font-weight:bold, font-size: smaller;
class future-qt,futured,future-cli,future-wallet bold
```
</td></tr><tr><td>

**Dependency graph**. Arrows show linker symbol dependencies. *Crypto* lib depends on nothing. *Util* lib is depended on by everything. *Kernel* lib depends only on consensus, crypto, and util.

</td></tr></table>

- The graph shows what _linker symbols_ (functions and variables) from each library other libraries can call and reference directly, but it is not a call graph. For example, there is no arrow connecting *libfuture_wallet* and *libfuture_node* libraries, because these libraries are intended to be modular and not depend on each other's internal implementation details. But wallet code is still able to call node code indirectly through the `interfaces::Chain` abstract class in [`interfaces/chain.h`](../../src/interfaces/chain.h) and node code calls wallet code through the `interfaces::ChainClient` and `interfaces::Chain::Notifications` abstract classes in the same file. In general, defining abstract classes in [`src/interfaces/`](../../src/interfaces/) can be a convenient way of avoiding unwanted direct dependencies or circular dependencies between libraries.

- *libfuture_crypto* should be a standalone dependency that any library can depend on, and it should not depend on any other libraries itself.

- *libfuture_consensus* should only depend on *libfuture_crypto*, and all other libraries besides *libfuture_crypto* should be allowed to depend on it.

- *libfuture_util* should be a standalone dependency that any library can depend on, and it should not depend on other libraries except *libfuture_crypto*. It provides basic utilities that fill in gaps in the C++ standard library and provide lightweight abstractions over platform-specific features. Since the util library is distributed with the kernel and is usable by kernel applications, it shouldn't contain functions that external code shouldn't call, like higher level code targeted at the node or wallet. (*libfuture_common* is a better place for higher level code, or code that is meant to be used by internal applications only.)

- *libfuture_common* is a home for miscellaneous shared code used by different future Core applications. It should not depend on anything other than *libfuture_util*, *libfuture_consensus*, and *libfuture_crypto*.

- *libfuture_kernel* should only depend on *libfuture_util*, *libfuture_consensus*, and *libfuture_crypto*.

- The only thing that should depend on *libfuture_kernel* internally should be *libfuture_node*. GUI and wallet libraries *libfutureqt* and *libfuture_wallet* in particular should not depend on *libfuture_kernel* and the unneeded functionality it would pull in, like block validation. To the extent that GUI and wallet code need scripting and signing functionality, they should be get able it from *libfuture_consensus*, *libfuture_common*, *libfuture_crypto*, and *libfuture_util*, instead of *libfuture_kernel*.

- GUI, node, and wallet code internal implementations should all be independent of each other, and the *libfutureqt*, *libfuture_node*, *libfuture_wallet* libraries should never reference each other's symbols. They should only call each other through [`src/interfaces/`](../../src/interfaces/) abstract interfaces.

## Work in progress

- Validation code is moving from *libfuture_node* to *libfuture_kernel* as part of [The libfuturekernel Project #27587](https://github.com/future/future/issues/27587)
