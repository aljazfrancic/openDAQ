opendaq_dependency(
    NAME                native_streaming
    REQUIRED_VERSION    1.0.8
    GIT_REPOSITORY      https://github.com/openDAQ/libNativeStreaming.git
    GIT_REF             v1.0.10
    EXPECT_TARGET       daq::native_streaming
)
