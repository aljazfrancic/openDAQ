/*
 * Copyright 2022-2025 openDAQ d.o.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <opendaq/folder_config.h>
#include <opendaq/component_ptr.h>
#include <opendaq/component_impl.h>
#include <opendaq/folder_ptr.h>
#include <tsl/ordered_map.h>
#include <opendaq/component_deserialize_context_factory.h>

BEGIN_NAMESPACE_OPENDAQ

template <class Intf = IFolderConfig, class... Intfs>
class FolderImpl : public ComponentImpl<Intf, Intfs...>
{
public:
    using Super = ComponentImpl<Intf, Intfs ...>;

    FolderImpl(const IntfID& itemId,
               const ContextPtr& context,
               const ComponentPtr& parent,
               const StringPtr& localId,
               const StringPtr& className = nullptr);

    FolderImpl(const ContextPtr& context,
               const ComponentPtr& parent,
               const StringPtr& localId,
               const StringPtr& className = nullptr);

    // IComponent
    ErrCode INTERFACE_FUNC setActive(Bool active) override;

    // IComponentPrivate
    ErrCode INTERFACE_FUNC updateOperationMode(OperationModeType modeType) override;

    // IFolder
    ErrCode INTERFACE_FUNC getItems(IList** items, ISearchFilter* searchFilter = nullptr) override;
    ErrCode INTERFACE_FUNC getItem(IString* localId, IComponent** item) override;
    ErrCode INTERFACE_FUNC isEmpty(Bool* empty) override;
    ErrCode INTERFACE_FUNC hasItem(IString* localId, Bool* value) override;

    // IFolderConfig
    ErrCode INTERFACE_FUNC addItem(IComponent* item) override;
    ErrCode INTERFACE_FUNC removeItem(IComponent* item) override;
    ErrCode INTERFACE_FUNC removeItemWithLocalId(IString* localId) override;
    ErrCode INTERFACE_FUNC clear() override;

    // ISerializable
    ErrCode INTERFACE_FUNC getSerializeId(ConstCharPtr* id) const override;

    // IPropertyObjectInternal
    ErrCode INTERFACE_FUNC enableCoreEventTrigger() override;
    ErrCode INTERFACE_FUNC disableCoreEventTrigger() override;

    static ConstCharPtr SerializeId();
    static ErrCode Deserialize(ISerializedObject* serialized, IBaseObject* context, IFunction* factoryCallback, IBaseObject** obj);

protected:
    tsl::ordered_map<std::string, ComponentPtr> items;

    void removed() override;

    virtual bool addItemInternal(const ComponentPtr& component);
    void serializeCustomObjectValues(const SerializerPtr& serializer, bool forUpdate) override;

    void deserializeCustomObjectValues(const SerializedObjectPtr& serializedObject,
                                       const BaseObjectPtr& context,
                                       const FunctionPtr& factoryCallback) override;

    template <class Interface, class Implementation>
    static BaseObjectPtr DeserializeFolder(const SerializedObjectPtr& serialized,
                                           const BaseObjectPtr& context,
                                           const FunctionPtr& factoryCallback);

    void callBeginUpdateOnChildren() override;
    void callEndUpdateOnChildren() override;
    void onUpdatableUpdateEnd(const BaseObjectPtr& context) override;

    virtual void syncComponentOperationMode(const ComponentPtr& component);

private:
    bool removeItemWithLocalIdInternal(const std::string& str);
    void clearInternal();

    IntfID itemId;
};

template <class Intf, class... Intfs>
FolderImpl<Intf, Intfs...>::FolderImpl(const IntfID& itemId,
                                       const ContextPtr& context,
                                       const ComponentPtr& parent,
                                       const StringPtr& localId,
                                       const StringPtr& className)
    : ComponentImpl<Intf, Intfs...>(context, parent, localId, className)
    , itemId(itemId)
{
}

template <class Intf, class... Intfs>
FolderImpl<Intf, Intfs...>::FolderImpl(const ContextPtr& context,
                                       const ComponentPtr& parent,
                                       const StringPtr& localId,
                                       const StringPtr& className)
    : FolderImpl(IComponent::Id, context, parent, localId, className)
{
}

template <class Intf, class ... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::setActive(Bool active)
{
    const ErrCode err = Super::setActive(active);
    OPENDAQ_RETURN_IF_FAILED(err);
    if (err == OPENDAQ_IGNORED)
        return err;

    return daqTry([&]
    {
        std::vector<ComponentPtr> itemsVec;
        for (const auto& [_, item] : this->items)
            itemsVec.emplace_back(item);
        this->setActiveRecursive(itemsVec, active);
        return OPENDAQ_SUCCESS;
    });
}

template <class Intf, class... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::getItems(IList** items, ISearchFilter* searchFilter)
{
    OPENDAQ_PARAM_NOT_NULL(items);

    auto lock = this->getRecursiveConfigLock();

    if (searchFilter)
    {
        return daqTry([&]
        {
            std::vector<ComponentPtr> itemsVec;
            for (const auto& [_, item] : this->items)
                itemsVec.emplace_back(item);

            *items = this->searchItems(searchFilter, itemsVec).detach();
            return OPENDAQ_SUCCESS;
        });
    }

    IList* list;
    auto err = createListWithElementType(&list, itemId);
    OPENDAQ_RETURN_IF_FAILED(err);

    ListPtr<IComponent> childList = ListPtr<IComponent>::Adopt(list);
    for (const auto& [_, item] : this->items)
        if (item.getVisible())
            childList.pushBack(item);

    *items = childList.detach();

    return OPENDAQ_SUCCESS;
}

template <class Intf, class... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::getItem(IString* localId, IComponent** item)
{
    OPENDAQ_PARAM_NOT_NULL(localId);
    OPENDAQ_PARAM_NOT_NULL(item);

    auto lock = this->getRecursiveConfigLock();

    auto it = items.find(StringPtr::Borrow(localId).toStdString());
    if (it == items.end())
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_NOTFOUND);

    *item = it->second.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

template <class Intf, class... Intfs>
ErrCode INTERFACE_FUNC FolderImpl<Intf, Intfs...>::isEmpty(Bool* empty)
{
    OPENDAQ_PARAM_NOT_NULL(empty);

    *empty = items.empty() ? True : False;

    return OPENDAQ_SUCCESS;
}

template <class Intf, class ... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::hasItem(IString* localId, Bool* value)
{
    OPENDAQ_PARAM_NOT_NULL(localId);

    auto lock = this->getRecursiveConfigLock();

    const auto it = items.find(StringPtr::Borrow(localId).toStdString());
    if (it == items.end())
        *value = False;
    else
        *value = True;

    return OPENDAQ_SUCCESS;
}

template <class Intf, class... Intfs>
void FolderImpl<Intf, Intfs...>::syncComponentOperationMode(const ComponentPtr& component)
{
    auto componentPrivate = component.template asPtrOrNull<IComponentPrivate>(true);
    if (!componentPrivate.assigned())
        return;

    OperationModeType modeType;
    const ErrCode errCode = this->getOperationMode(&modeType);
    if (errCode != OPENDAQ_SUCCESS)
        return;

    componentPrivate->updateOperationMode(modeType);
}

template <class Intf, class... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::addItem(IComponent* item)
{
    OPENDAQ_PARAM_NOT_NULL(item);
    ComponentPtr component = ComponentPtr::Borrow(item);

    {
        auto lock = this->getRecursiveConfigLock();

        const ErrCode err = daqTry([this, &component]
        {
            if (!addItemInternal(component))
                return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_DUPLICATEITEM, fmt::format("Component with id {} already exists", component.getGlobalId()));

            return OPENDAQ_SUCCESS;
        });

        OPENDAQ_RETURN_IF_FAILED(err);
    }

    if (!this->coreEventMuted && this->coreEvent.assigned())
    {
        const auto args = createWithImplementation<ICoreEventArgs, CoreEventArgsImpl>(
            CoreEventId::ComponentAdded,
            Dict<IString, IBaseObject>({{"Component", component}}));

        this->triggerCoreEvent(args);
        component.asPtr<IPropertyObjectInternal>(true).enableCoreEventTrigger();
    }

    // When a component is added to the subtree, the folder updates its operation mode to match the operation mode of the parent device.
    syncComponentOperationMode(component);

    return OPENDAQ_SUCCESS;
}

template <class Intf, class... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::removeItem(IComponent* item)
{
    OPENDAQ_PARAM_NOT_NULL(item);

    const auto str = ComponentPtr::Borrow(item).getLocalId().toStdString();

    {
        auto lock = this->getRecursiveConfigLock();

        const ErrCode err = daqTry([this, &str]
        {
            if (!removeItemWithLocalIdInternal(str))
                return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_NOTFOUND);

            return OPENDAQ_SUCCESS;
        });

        OPENDAQ_RETURN_IF_FAILED(err);
    }
    
    if (!this->coreEventMuted && this->coreEvent.assigned())
    {
        const auto args = createWithImplementation<ICoreEventArgs, CoreEventArgsImpl>(
                CoreEventId::ComponentRemoved,
                Dict<IString, IBaseObject>({{"Id", str}}));
        
        this->triggerCoreEvent(args);
    }

    return OPENDAQ_SUCCESS;
}

template <class Intf, class... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::removeItemWithLocalId(IString* localId)
{
    OPENDAQ_PARAM_NOT_NULL(localId);

    const auto str = StringPtr::Borrow(localId).toStdString();

    {
        auto lock = this->getRecursiveConfigLock();

        const ErrCode err = daqTry([this, &str]
        {
            if (!removeItemWithLocalIdInternal(str))
                return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_NOTFOUND);

            return OPENDAQ_SUCCESS;
        });

        OPENDAQ_RETURN_IF_FAILED(err);
    }

    if (!this->coreEventMuted && this->coreEvent.assigned())
    {
        const auto args = createWithImplementation<ICoreEventArgs, CoreEventArgsImpl>(
                CoreEventId::ComponentRemoved,
                Dict<IString, IBaseObject>({{"Id", str}}));
        
        this->triggerCoreEvent(args);
    }

    return OPENDAQ_SUCCESS;
}

template <class Intf, class... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::clear()
{
    auto lock = this->getRecursiveConfigLock();
    clearInternal();

    return OPENDAQ_SUCCESS;
}

template <class Intf, class... Intfs>
ErrCode INTERFACE_FUNC FolderImpl<Intf, Intfs...>::getSerializeId(ConstCharPtr* id) const
{
    OPENDAQ_PARAM_NOT_NULL(id);

    *id = SerializeId();

    return OPENDAQ_SUCCESS;
}

template <class Intf, class ... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::enableCoreEventTrigger()
{
    for (const auto& [_, item] : items)
    {
        const ErrCode err = item.template asPtr<IPropertyObjectInternal>(true)->enableCoreEventTrigger();
        OPENDAQ_RETURN_IF_FAILED(err);
    }

    return ComponentImpl<Intf, Intfs...>::enableCoreEventTrigger();
}

template <class Intf, class ... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::disableCoreEventTrigger()
{
    for (const auto& [_, item] : items)
    {
        const ErrCode err = item.template asPtr<IPropertyObjectInternal>(true)->disableCoreEventTrigger();
        OPENDAQ_RETURN_IF_FAILED(err);
    }

    return ComponentImpl<Intf, Intfs...>::disableCoreEventTrigger();
}

template <class Intf, class... Intfs>
ConstCharPtr FolderImpl<Intf, Intfs...>::SerializeId()
{
    return "Folder";
}

template <class Intf, class... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::Deserialize(ISerializedObject* serialized,
                                                IBaseObject* context,
                                                IFunction* factoryCallback,
                                                IBaseObject** obj)
{
    OPENDAQ_PARAM_NOT_NULL(context);

    return daqTry([&obj, &serialized, &context, &factoryCallback]
    {
        *obj = DeserializeFolder<IFolderConfig, FolderImpl>(serialized, context, factoryCallback).detach();
    });
}

template <class Intf, class... Intfs>
template <class Interface, class Implementation>
BaseObjectPtr FolderImpl<Intf, Intfs...>::DeserializeFolder(const SerializedObjectPtr& serialized,
                                                            const BaseObjectPtr& context,
                                                            const FunctionPtr& factoryCallback)
{
    return Super::DeserializeComponent(
        serialized,
        context,
        factoryCallback,
        [](const SerializedObjectPtr& serialized, const ComponentDeserializeContextPtr& deserializeContext, const StringPtr& className)
        {
            IntfID intfID;
            const auto errCode = deserializeContext->getIntfID(&intfID);
            if (errCode == OPENDAQ_SUCCESS)
            {
                return createWithImplementation<Interface, Implementation>(
                    intfID,
                    deserializeContext.getContext(),
                    deserializeContext.getParent(),
                    deserializeContext.getLocalId(),
                    className);
            }
            if (errCode == OPENDAQ_NOTFOUND)
            {
                return createWithImplementation<Interface, Implementation>(
                    deserializeContext.getContext(),
                    deserializeContext.getParent(),
                    deserializeContext.getLocalId(),
                    className);
            }
            checkErrorInfo(errCode);

            return typename InterfaceToSmartPtr<Interface>::SmartPtr();
        });
}


template <class Intf, class... Intfs>
void FolderImpl<Intf, Intfs...>::clearInternal()
{
    for (auto& item : items)
    {
        item.second.template asPtr<IPropertyObjectInternal>(true).disableCoreEventTrigger();
        item.second.remove();

        if (!this->coreEventMuted && this->coreEvent.assigned())
        {
            const auto args = createWithImplementation<ICoreEventArgs, CoreEventArgsImpl>(
                CoreEventId::ComponentRemoved,
                Dict<IString, IBaseObject>({{"Id", item.second.getLocalId()}}));
            
            this->triggerCoreEvent(args);
        }
    }

    items.clear();
}

template <class Intf, class... Intfs>
void FolderImpl<Intf, Intfs...>::removed()
{
    clearInternal();
}

template <class Intf, class... Intfs>
bool FolderImpl<Intf, Intfs...>::addItemInternal(const ComponentPtr& component)
{
    if (!component.supportsInterface(itemId))
        DAQ_THROW_EXCEPTION(InvalidParameterException, "Type of item not allowed in the folder");

    const auto res = items.emplace(component.getLocalId(), component);
    
    return res.second;
}

template <class Intf, class ... Intfs>
void FolderImpl<Intf, Intfs...>::serializeCustomObjectValues(const SerializerPtr& serializer, bool forUpdate)
{
    Super::serializeCustomObjectValues(serializer, forUpdate);

    if (!items.empty())
    {
        serializer.key("items");
        serializer.startObject();
        for (const auto& [itemId, item] : items)
        {
            if (!item.template asPtr<IPropertyObjectInternal>().hasUserReadAccess(serializer.getUser()))
                continue;

            serializer.key(itemId.c_str());

            if (forUpdate)
                item.template asPtr<IUpdatable>(true).serializeForUpdate(serializer);
            else
                item.serialize(serializer);
        }
        serializer.endObject();
    }
}

template <class Intf, class ... Intfs>
void FolderImpl<Intf, Intfs...>::deserializeCustomObjectValues(
    const SerializedObjectPtr& serializedObject,
    const BaseObjectPtr& context,
    const FunctionPtr& factoryCallback)
{
    Super::deserializeCustomObjectValues(serializedObject, context, factoryCallback);

    const auto deserializeContext = context.asPtr<IComponentDeserializeContext>(true);

    if (serializedObject.hasKey("items"))
    {
        const auto items = serializedObject.readSerializedObject("items");
        const auto keys = items.getKeys();
        for (const auto& key: keys)
        {
            const auto newDeserializeContext = deserializeContext.clone(this->template borrowPtr<ComponentPtr>(), key, nullptr);
            const auto item = items.readObject(key, newDeserializeContext, factoryCallback);

            const auto comp = item.template asPtr<IComponent>(true);
            addItemInternal(comp);
        }
    }
}

template <class Intf, class... Intfs>
void FolderImpl<Intf, Intfs...>::callBeginUpdateOnChildren()
{
    Super::callBeginUpdateOnChildren();

    for (const auto& [_, item] : items)
    {
        item.beginUpdate();
    }
}

template <class Intf, class... Intfs>
void FolderImpl<Intf, Intfs...>::callEndUpdateOnChildren()
{
    Super::callEndUpdateOnChildren();

    for (const auto& [_, item] : items)
    {
        item.endUpdate();
    }
}

template <class Intf, class ... Intfs>
void FolderImpl<Intf, Intfs...>::onUpdatableUpdateEnd(const BaseObjectPtr& context)
{
    for (const auto& [_, item] : items)
    {
        const auto updatable = item.template asPtrOrNull<IUpdatable>(true);
        if (updatable.assigned())
            updatable.updateEnded(context);
    }
    Super::onUpdatableUpdateEnd(context);
}

template <class Intf, class... Intfs>
ErrCode FolderImpl<Intf, Intfs...>::updateOperationMode(OperationModeType modeType)
{
    ErrCode errCode = Super::updateOperationMode(modeType);
    OPENDAQ_RETURN_IF_FAILED(errCode);

    for (const auto& [_, item] : items)
    {
        auto componentPrivate = item.template asPtrOrNull<IComponentPrivate>(true);
        if (componentPrivate.assigned())
        {
            errCode = componentPrivate->updateOperationMode(modeType);
            OPENDAQ_RETURN_IF_FAILED(errCode);
        }
    }

    return OPENDAQ_SUCCESS;
}

template <class Intf, class... Intfs>
bool FolderImpl<Intf, Intfs...>::removeItemWithLocalIdInternal(const std::string& str)
{
    const auto it = items.find(str);
    if (it == items.end())
        return false;

    it->second.template asPtr<IPropertyObjectInternal>(true).disableCoreEventTrigger();
    it->second.remove();
    items.erase(it);
    return true;
}

using StandardFolder = FolderImpl<>;

OPENDAQ_REGISTER_DESERIALIZE_FACTORY(StandardFolder)

END_NAMESPACE_OPENDAQ
