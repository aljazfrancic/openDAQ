set(LIB_NAME my_module)
set(MODULE_HEADERS_DIR ../include/${TARGET_FOLDER_NAME})

set(SRC_Include common.h
                module_dll.h
                my_module_impl.h
                my_filter_impl.h
                dispatch.h
				butterworth.h
)

set(SRC_Srcs module_dll.cpp
             my_module_impl.cpp
             my_filter_impl.cpp
			 butterworth.cpp
)

prepend_include(${TARGET_FOLDER_NAME} SRC_Include)

source_group("module" FILES ${MODULE_HEADERS_DIR}/my_module_common.h
                            ${MODULE_HEADERS_DIR}/my_module_impl.h
                            ${MODULE_HEADERS_DIR}/my_filter_impl.h
                            ${MODULE_HEADERS_DIR}/module_dll.h
							${MODULE_HEADERS_DIR}/butterworth.h
                            module_dll.cpp
                            my_module_impl.cpp
                            my_filter_impl.cpp
							butterworth.cpp
)


add_library(${LIB_NAME} SHARED ${SRC_Include}
                               ${SRC_Srcs}
)

add_library(${SDK_TARGET_NAMESPACE}::${LIB_NAME} ALIAS ${LIB_NAME})

target_link_libraries(${LIB_NAME} PUBLIC daq::opendaq
)

target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
                                              $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../include>
                                              $<INSTALL_INTERFACE:include>
)

opendaq_set_module_properties(${LIB_NAME} ${PROJECT_VERSION_MAJOR})
create_version_header(${LIB_NAME})
