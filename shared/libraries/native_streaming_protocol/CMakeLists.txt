cmake_minimum_required(VERSION 3.10)
set_cmake_folder_context(TARGET_FOLDER_NAME ${SDK_TARGET_NAMESPACE}_native_streaming_protocol)
project(OpenDaqNativeStreamingProtocol
    VERSION 1.0.0
    LANGUAGES CXX
)

add_subdirectory(src)

if (OPENDAQ_ENABLE_TESTS)
    add_subdirectory(tests)
endif()
