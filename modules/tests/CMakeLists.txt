if (DAQMODULES_REF_FB_MODULE AND DAQMODULES_REF_DEVICE_MODULE)
    message(STATUS "Reference device & function block module test app")
    add_subdirectory(test_ref_modules)
endif()

if (DAQMODULES_OPENDAQ_CLIENT_MODULE AND
        DAQMODULES_OPENDAQ_SERVER_MODULE AND
        OPENDAQ_ENABLE_WEBSOCKET_STREAMING AND
        OPENDAQ_ENABLE_NATIVE_STREAMING AND
        OPENDAQ_ENABLE_OPCUA AND
        DAQMODULES_REF_FB_MODULE AND
        DAQMODULES_REF_DEVICE_MODULE)
    message(STATUS "${SDK_NAME} device and server module test app")
    add_subdirectory(test_opendaq_device_modules)
endif()

if (DAQMODULES_OPENDAQ_CLIENT_MODULE AND
        OPENDAQ_ENABLE_WS_SIGGEN_INTEGRATION_TESTS)
    message(STATUS "Websocket streaming signal generator tool integration test app")
    add_subdirectory(test_ws_siggen_integration)
endif()
