#include <my_module/my_module_impl.h>
#include <my_module/version.h>

#include <coretypes/version_info_factory.h>

#include <utility>

BEGIN_NAMESPACE_MY_MODULE

MyModule::MyModule(ContextPtr context)
    : Module("My module",
            daq::VersionInfo(MY_MODULE_MAJOR_VERSION, MY_MODULE_MINOR_VERSION, MY_MODULE_PATCH_VERSION),
            std::move(context)
    )
{
}

END_NAMESPACE_MY_MODULE
