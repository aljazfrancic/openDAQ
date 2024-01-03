#include <my_module/my_filter_impl.h>
#include <my_module/my_module_impl.h>
#include <my_module/version.h>

#include <coretypes/version_info_factory.h>

BEGIN_NAMESPACE_MY_MODULE

MyModule::MyModule(ContextPtr context)
    : Module("My module", daq::VersionInfo(MY_MODULE_MAJOR_VERSION, MY_MODULE_MINOR_VERSION, MY_MODULE_PATCH_VERSION), std::move(context))
{
}

DictPtr<IString, IFunctionBlockType> MyModule::onGetAvailableFunctionBlockTypes()
{
    auto types = Dict<IString, IFunctionBlockType>();

    auto typeClassifier = My::MyFilterImpl::CreateType();
    types.set(typeClassifier.getId(), typeClassifier);

    return types;
}

FunctionBlockPtr MyModule::onCreateFunctionBlock(const StringPtr& id,
                                                 const ComponentPtr& parent,
                                                 const StringPtr& localId,
                                                 const PropertyObjectPtr& config)
{
    if (id == My::MyFilterImpl::CreateType().getId())
    {
        FunctionBlockPtr fb = createWithImplementation<IFunctionBlock, My::MyFilterImpl>(context, parent, localId);
        return fb;
    }

    LOG_W("Function block \"{}\" not found", id);
    throw NotFoundException("Function block not found");
}

END_NAMESPACE_MY_MODULE
