set(BASE_NAME coreobjects)
set(LIB_NAME ${SDK_TARGET_NAMESPACE}${BASE_NAME})


set(SDK_HEADERS_DIR ../include/${BASE_NAME})
set(GENERATED_HEADERS_DIR ${CMAKE_CURRENT_BINARY_DIR}/${SDK_HEADERS_DIR})

set(ConfigHeaderSource ${SDK_HEADERS_DIR}/coreobjects_config.h.in)
set(ConfigHeader ${GENERATED_HEADERS_DIR}/coreobjects_config.h)

configure_file(${ConfigHeaderSource} ${ConfigHeader})

set_source_files_properties(${ConfigHeader} PROPERTIES GENERATED TRUE)
source_group("Generated\\Header Files" FILES ${ConfigHeader})

set(RTGEN_HEADERS_DIR ${SDK_HEADERS_DIR})
set(RTGEN_OUTPUT_DIR ${GENERATED_HEADERS_DIR})
set(RTGEN_RELATIVE_PARENT_DIR core/${BASE_NAME})
#set(RTGEN_VERBOSE TRUE)

rtgen(SRC_EvalValue eval_value.h)
rtgen(SRC_Ownable ownable.h)
rtgen(SRC_Property property.h)
rtgen(SRC_PropertyInternal property_internal.h INTERNAL)
rtgen(SRC_PropertyBuilder property_builder.h)
rtgen(SRC_PropertyValueEventArgs property_value_event_args.h)
rtgen(SRC_EndUpdateEventArgs end_update_event_args.h)
rtgen(SRC_PropertyObject property_object.h)
rtgen(SRC_PropertyObjectInternal property_object_internal.h)
rtgen(SRC_PropertyObjectClass property_object_class.h)
rtgen(SRC_PropertyObjectClassBuilder property_object_class_builder.h)
rtgen(SRC_PropertyObjectClassInternal property_object_class_internal.h INTERNAL)
rtgen(SRC_PropertyObjectProtected property_object_protected.h)
rtgen(SRC_CallableInfo callable_info.h)
rtgen(SRC_ArgumentInfo argument_info.h)
rtgen(SRC_Coercer coercer.h)
rtgen(SRC_Validator validator.h)
rtgen(SRC_Unit unit.h)
rtgen(SRC_UnitBuilder unit_builder.h)
rtgen(SRC_CoreEventArgs core_event_args.h)
rtgen(SRC_User user.h)
rtgen(SRC_UserInternal user_internal.h)
rtgen(SRC_AuthenticationProvider authentication_provider.h)
rtgen(SRC_PermissionManager permission_manager.h)
rtgen(SRC_PermissionManagerInternal permission_manager_internal.h)
rtgen(SRC_PermisisonsBuilder permissions_builder.h)
rtgen(SRC_PermisisonMaskBuilder permission_mask_builder.h)
rtgen(SRC_Permisisons permissions.h)
rtgen(SRC_PermisisonsInternal permissions_internal.h)
rtgen(SRC_ObjectLockGuard object_lock_guard.h)

get_target_property(CORE_CONTAINERS_SRCS core_containers INTERFACE_SOURCES)

source_group("core_containers" FILES ${CORE_CONTAINERS_SRCS})

source_group("eval_value" FILES ${SDK_HEADERS_DIR}/eval_nodes.h
                                ${SDK_HEADERS_DIR}/eval_value.h
                                ${SDK_HEADERS_DIR}/eval_value_factory.h
                                ${SDK_HEADERS_DIR}/eval_value_helpers.h
                                ${SDK_HEADERS_DIR}/eval_value_impl.h
                                ${SDK_HEADERS_DIR}/eval_value_parser.h
                                ${SDK_HEADERS_DIR}/eval_value_lexer.h
                                eval_value_impl.cpp
                                eval_value_lexer.cpp
                                eval_value_parser.cpp
                                eval_nodes.cpp
)

source_group("validation" FILES ${SDK_HEADERS_DIR}/validator.h
                                ${SDK_HEADERS_DIR}/validator_factory.h
                                ${SDK_HEADERS_DIR}/validator_impl.h
                                ${SDK_HEADERS_DIR}/coercer.h
                                ${SDK_HEADERS_DIR}/coercer_factory.h
                                ${SDK_HEADERS_DIR}/coercer_impl.h
                                validator_impl.cpp
                                coercer_impl.cpp
)

source_group("property" FILES ${SDK_HEADERS_DIR}/property.h
                              ${SDK_HEADERS_DIR}/property_internal.h
                              ${SDK_HEADERS_DIR}/property_builder.h
                              ${SDK_HEADERS_DIR}/property_ptr.fwd_declare.h
                              ${SDK_HEADERS_DIR}/property_factory.h
                              ${SDK_HEADERS_DIR}/property_impl.h
                              ${SDK_HEADERS_DIR}/property_builder_impl.h
                              ${SDK_HEADERS_DIR}/argument_info.h
                              ${SDK_HEADERS_DIR}/argument_info_factory.h
                              ${SDK_HEADERS_DIR}/argument_info_impl.h
                              ${SDK_HEADERS_DIR}/callable_info_factory.h
                              ${SDK_HEADERS_DIR}/callable_info_impl.h
                              ${SDK_HEADERS_DIR}/callable_info.h
                              ${SDK_HEADERS_DIR}/search_filter.h
                              ${SDK_HEADERS_DIR}/search_filter_impl.h
                              ${SDK_HEADERS_DIR}/search_filter_factory.h
                              property_impl.cpp
                              property_builder_impl.cpp
                              argument_info_impl.cpp
                              callable_info_impl.cpp
                              search_filter_impl.cpp
)

source_group("property_object" FILES ${SDK_HEADERS_DIR}/property_object.h
                                     ${SDK_HEADERS_DIR}/property_object_factory.h
                                     ${SDK_HEADERS_DIR}/property_object_impl.h
                                     ${SDK_HEADERS_DIR}/object_keys.h
                                     ${SDK_HEADERS_DIR}/property_object_ptr.custom.h
                                     ${SDK_HEADERS_DIR}/property_object_protected.h
                                     ${SDK_HEADERS_DIR}/property_object_internal.h
                                     ${SDK_HEADERS_DIR}/object_lock_guard.h
                                     property_object_impl.cpp
)

source_group("property_object_class" FILES ${SDK_HEADERS_DIR}/property_object_class.h
                                           ${SDK_HEADERS_DIR}/property_object_class_builder.h
                                           ${SDK_HEADERS_DIR}/property_object_class_factory.h
                                           ${SDK_HEADERS_DIR}/property_object_class_impl.h
                                           ${SDK_HEADERS_DIR}/property_object_class_builder_impl.h
                                           ${SDK_HEADERS_DIR}/property_object_class_internal.h
                                           property_object_class_impl.cpp
                                           property_object_class_builder_impl.cpp
)

source_group("property_value" FILES ${SDK_HEADERS_DIR}/property_value.h
                                    ${SDK_HEADERS_DIR}/property_value_event_args.h
                                    ${SDK_HEADERS_DIR}/property_value_event_args_factory.h
                                    ${SDK_HEADERS_DIR}/property_value_event_args_impl.h
                                    property_value_event_args_impl.cpp
)

source_group("end_update_event_args" FILES ${SDK_HEADERS_DIR}/end_update_event_args.h
                                           ${SDK_HEADERS_DIR}/end_update_event_args_factory.h
                                           ${SDK_HEADERS_DIR}/end_update_event_args_impl.h
                                           end_update_event_args_impl.cpp
)

source_group("owning_containers" FILES ${SDK_HEADERS_DIR}/owning_dict_factory.h
                                       ${SDK_HEADERS_DIR}/owning_dict_impl.h
                                       ${SDK_HEADERS_DIR}/owning_list_factory.h
                                       ${SDK_HEADERS_DIR}/owning_list_impl.h
                                       owning_dict_impl.cpp
                                       owning_list_impl.cpp
)

source_group("unit" FILES ${SDK_HEADERS_DIR}/unit.h
                          ${SDK_HEADERS_DIR}/unit_impl.h
                          ${SDK_HEADERS_DIR}/unit_factory.h
                          ${SDK_HEADERS_DIR}/unit_builder.h
                          ${SDK_HEADERS_DIR}/unit_builder_impl.h
                          unit_impl.cpp
                          unit_builder_impl.cpp
)

source_group("core_event_args" FILES ${SDK_HEADERS_DIR}/core_event_args.h
                                     ${SDK_HEADERS_DIR}/core_event_args_factory.h
                                     ${SDK_HEADERS_DIR}/core_event_args_impl.h
                                     ${SDK_HEADERS_DIR}/core_event_args_ids.h
                                     core_event_args_impl.cpp
)

source_group("user" FILES ${SDK_HEADERS_DIR}/user.h
                          ${SDK_HEADERS_DIR}/user_internal.h
                          ${SDK_HEADERS_DIR}/user_factory.h
                          ${SDK_HEADERS_DIR}/user_impl.h
                          user_impl.cpp
)

source_group("authentication_provider" FILES ${SDK_HEADERS_DIR}/authentication_provider.h
                                             ${SDK_HEADERS_DIR}/authentication_provider_factory.h
                                             ${SDK_HEADERS_DIR}/authentication_provider_impl.h
                                             authentication_provider_impl.cpp
)

source_group("permission_manager" FILES ${SDK_HEADERS_DIR}/permission_manager.h
                                        ${SDK_HEADERS_DIR}/permission_manager_factory.h
                                        ${SDK_HEADERS_DIR}/permission_manager_internal.h
                                        ${SDK_HEADERS_DIR}/permission_manager_impl.h
                                        permission_manager_impl.cpp
)

source_group("permission_builder" FILES ${SDK_HEADERS_DIR}/permissions_builder.h
                                        ${SDK_HEADERS_DIR}/permissions_builder_factory.h
                                        ${SDK_HEADERS_DIR}/permissions_builder_impl.h
                                        permissions_builder_impl.cpp
                                        ${SDK_HEADERS_DIR}/permission_mask_builder.h
                                        ${SDK_HEADERS_DIR}/permission_mask_builder_factory.h
                                        ${SDK_HEADERS_DIR}/permission_mask_builder_impl.h
                                        permission_mask_builder_impl.cpp
                                        ${SDK_HEADERS_DIR}/permissions.h
                                        ${SDK_HEADERS_DIR}/permissions_internal.h
                                        ${SDK_HEADERS_DIR}/permissions_impl.h
                                        permissions_impl.cpp
)

set(SRC_Cpp version.cpp
            eval_value_impl.cpp
            eval_value_lexer.cpp
            eval_value_parser.cpp
            eval_nodes.cpp
            property_builder_impl.cpp
            property_impl.cpp
            property_object_impl.cpp
            property_object_class_impl.cpp
            property_object_class_builder_impl.cpp
            property_value_event_args_impl.cpp
            end_update_event_args_impl.cpp
            owning_list_impl.cpp
            owning_dict_impl.cpp
            callable_info_impl.cpp
            argument_info_impl.cpp
            validator_impl.cpp
            coercer_impl.cpp
            util.cpp
            unit_impl.cpp
            unit_builder_impl.cpp
            core_event_args_impl.cpp
            user_impl.cpp
            authentication_provider_impl.cpp
            permission_manager_impl.cpp
            permissions_impl.cpp
            permissions_builder_impl.cpp
            permission_mask_builder_impl.cpp
            search_filter_impl.cpp
)

set(SRC_PublicHeaders coreobjects.h
                      object_keys.h
                      version.h
                      serialization_utils.h
                      eval_value_factory.h
                      property_value.h
                      property_factory.h
                      property_ptr.fwd_declare.h
                      property_impl.h
                      property_value_event_args_factory.h
                      end_update_event_args_factory.h
                      property_object_impl.h
                      property_object_factory.h
                      property_object_class_factory.h
                      property_object_class_impl.h
                      property_object_ptr.custom.h
                      owning_list_factory.h
                      owning_dict_factory.h
                      callable_info_factory.h
                      argument_info_factory.h
                      validator.h
                      validator_factory.h
                      coercer.h
                      coercer_factory.h
                      util.h
                      exceptions.h
                      errors.h
                      unit_factory.h
                      core_event_args_factory.h 
                      core_event_args_ids.h 
                      core_event_args_impl.h
                      user.h
                      user_internal.h
                      user_factory.h
                      authentication_provider.h
                      authentication_provider_factory.h
                      permission_manager.h
                      permission_manager_internal.h
                      permission_manager_factory.h
                      permissions.h
                      permissions_builder.h
                      permissions_builder_factory.h
                      permission_mask_builder.h
                      permission_mask_builder_factory.h
                      object_lock_guard.h
                      search_filter.h
                      search_filter_factory.h
)

set(SRC_PrivateHeaders eval_value_impl.h
                       eval_nodes.h
                       eval_value_lexer.h
                       eval_value_parser.h
                       eval_value_helpers.h
                       owning_list_impl.h
                       owning_dict_impl.h
                       callable_info_impl.h
                       argument_info_impl.h
                       property_value_event_args_impl.h
                       end_update_event_args_impl.h
                       validator_impl.h
                       coercer_impl.h
                       unit_impl.h
                       unit_builder_impl.h
                       property_builder_impl.h
                       property_object_class_builder_impl.h
                       property_object_internal.h
                       user_impl.h
                       authentication_provider_impl.h
                       permission_manager_impl.h
                       permissions_internal.h
                       permissions_impl.h
                       permissions_builder_impl.h
                       permission_mask_builder_impl.h
                       search_filter_impl.h
)

prepend_include(${TARGET_FOLDER_NAME} SRC_PrivateHeaders)
prepend_include(${TARGET_FOLDER_NAME} SRC_PublicHeaders)

list(APPEND SRC_PublicHeaders  ${ConfigHeader}
                               ${SRC_Property}
                               ${SRC_PropertyInternal}
                               ${SRC_PropertyBuilder}
                               ${SRC_PropertyObjectProtected}
                               ${SRC_PropertyObjectClass}
                               ${SRC_PropertyObjectClassBuilder}
                               ${SRC_PropertyObjectClassInternal}
                               ${SRC_PropertyObjectInternal}
                               ${SRC_PropertyObject_PublicHeaders}
                               ${SRC_Ownable}
                               ${SRC_EvalValue}
                               ${SRC_DelphiBindings}
                               ${SRC_PropertyValueEventArgs}
                               ${SRC_EndUpdateEventArgs}
                               ${SRC_CallableInfo}
                               ${SRC_ArgumentInfo}
                               ${SRC_Validator}
                               ${SRC_Coercer}
                               ${SRC_Unit}
                               ${SRC_UnitBuilder}
                               ${SRC_CoreEventArgs}
                               ${SRC_User}
                               ${SRC_UserInternal}
                               ${SRC_AuthenticationProvider}
                               ${SRC_PermissionManager}
                               ${SRC_PermissionManagerInternal}
                               ${SRC_PermisisonsBuilder}
                               ${SRC_PermisisonMaskBuilder}
                               ${SRC_Permisisons}
                               ${SRC_ObjectLockGuard}
                               coreobjects.natvis
)

add_library(${LIB_NAME} SHARED ${SRC_Cpp}
                               ${SRC_PrivateHeaders}
                               ${SRC_PublicHeaders}
                               ${ConfigHeaderSource}
)

add_library(${SDK_TARGET_NAMESPACE}::${BASE_NAME} ALIAS ${LIB_NAME})

rtgen_config(${PROJECT_NAME}
             ${LIB_NAME}
             ${PROJECT_VERSION_MAJOR}
             ${PROJECT_VERSION_MINOR}
             ${PROJECT_VERSION_PATCH}
)

target_link_libraries(${LIB_NAME}
    PUBLIC
        daq::coretypes
        tsl::ordered_map
    PRIVATE
        daq::core_containers
        rapidjson
        bcrypt::bcrypt
        $<BUILD_INTERFACE:Boost::algorithm>
        $<BUILD_INTERFACE:std::filesystem>
)

target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
                                              $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../include>
                                              $<BUILD_INTERFACE:${GENERATED_HEADERS_DIR}>

                                              $<INSTALL_INTERFACE:include>
)

if (OPENDAQ_ENABLE_ACCESS_CONTROL)
    message(STATUS "Access control enabled")
    target_compile_definitions(${LIB_NAME} PUBLIC OPENDAQ_ENABLE_ACCESS_CONTROL)
else()
    message(STATUS "Access control disabled")
endif()

target_compile_definitions(${LIB_NAME} PRIVATE BUILDING_SHARED_LIBRARY
                                       INTERFACE OPENDAQ_LINKS_CORE_OBJECTS
)
set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "${SRC_PublicHeaders}")

opendaq_set_output_lib_name(${LIB_NAME} ${PROJECT_VERSION_MAJOR})
create_version_header(${LIB_NAME} ONLY_RC)

install(TARGETS ${LIB_NAME}
        EXPORT ${SDK_NAME}
        RUNTIME
            DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT ${SDK_NAME}_${BASE_NAME}_Runtime
        LIBRARY
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT          ${SDK_NAME}_${BASE_NAME}_Runtime
            NAMELINK_COMPONENT ${SDK_NAME}_${BASE_NAME}_Development
        ARCHIVE
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT ${SDK_NAME}_${BASE_NAME}_Development
        PUBLIC_HEADER
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BASE_NAME}
            COMPONENT ${SDK_NAME}_${BASE_NAME}_Development
)
