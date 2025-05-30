set(BASE_NAME native_streaming_protocol)
set(LIB_NAME ${SDK_TARGET_NAME}_${BASE_NAME})

set(SRC_Cpp native_streaming_client_handler.cpp
            native_streaming_server_handler.cpp
            native_streaming_protocol_types.cpp
            server_session_handler.cpp
            client_session_handler.cpp
            base_session_handler.cpp
            streaming_manager.cpp
)

set(SRC_PublicHeaders native_streaming_protocol.h
                      native_streaming_client_handler.h
                      native_streaming_server_handler.h
                      native_streaming_protocol_types.h
                      server_session_handler.h
                      client_session_handler.h
                      base_session_handler.h
                      streaming_manager.h
)

set(INCLUDE_DIR ../include/native_streaming_protocol)
prepend_include(${INCLUDE_DIR} SRC_PublicHeaders)


set(SRC_PrivateHeaders )


add_library(${LIB_NAME} STATIC ${SRC_Cpp}
                               ${SRC_PublicHeaders}
                               ${SRC_PrivateHeaders}
)

add_library(${SDK_TARGET_NAMESPACE}::${BASE_NAME} ALIAS ${LIB_NAME})

if(BUILD_64Bit OR BUILD_ARM)
    set_target_properties(${LIB_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
else()
    set_target_properties(${LIB_NAME} PROPERTIES POSITION_INDEPENDENT_CODE OFF)
endif()

target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
                                              $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../include>

                                              $<INSTALL_INTERFACE:include>
)

target_link_libraries(${LIB_NAME} PUBLIC daq::opendaq
                                         daq::packet_streaming
                                         daq::native_streaming
                                  PRIVATE daq::config_protocol
                                          daq::opendaq_dev
)

if (WIN32)
    target_link_libraries(${LIB_NAME} PUBLIC
            ws2_32
            wsock32
    )
endif()

set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "${SRC_PublicHeaders}")

opendaq_set_output_lib_name(${LIB_NAME} ${PROJECT_VERSION_MAJOR})
