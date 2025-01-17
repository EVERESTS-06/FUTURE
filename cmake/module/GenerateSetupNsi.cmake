# Copyright (c) 2023-present The future Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or https://opensource.org/license/mit/.

function(generate_setup_nsi)
  set(abs_top_srcdir ${PROJECT_SOURCE_DIR})
  set(abs_top_builddir ${PROJECT_BINARY_DIR})
  set(CLIENT_URL ${PROJECT_HOMEPAGE_URL})
  set(CLIENT_TARNAME "future")
  set(future_GUI_NAME "future-qt")
  set(future_DAEMON_NAME "futured")
  set(future_CLI_NAME "future-cli")
  set(future_TX_NAME "future-tx")
  set(future_WALLET_TOOL_NAME "future-wallet")
  set(future_TEST_NAME "test_future")
  set(EXEEXT ${CMAKE_EXECUTABLE_SUFFIX})
  configure_file(${PROJECT_SOURCE_DIR}/share/setup.nsi.in ${PROJECT_BINARY_DIR}/future-win64-setup.nsi USE_SOURCE_PERMISSIONS @ONLY)
endfunction()
