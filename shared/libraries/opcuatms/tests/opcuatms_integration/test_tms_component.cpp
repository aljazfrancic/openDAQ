#include <opendaq/component_factory.h>
#include <opcuatms_client/objects/tms_client_component_factory.h>
#include <opcuatms_server/objects/tms_server_component.h>
#include "tms_object_integration_test.h"
#include <coreobjects/property_object_factory.h>
#include <opendaq/context_factory.h>

using namespace daq;
using namespace opcua::tms;
using namespace opcua;

struct RegisteredComponent
{
    TmsServerComponentPtr serverObject;
    ComponentPtr serverComponent;
    ComponentPtr clientComponent;
};

class TmsComponentTest : public TmsObjectIntegrationTest
{
public:
    ComponentPtr createTestComponent()
    {
        auto component = Component(ctx, nullptr, "test");

        component.addProperty(StringProperty("foo", "bar"));
        auto obj = PropertyObject();
        obj.addProperty(IntProperty("Int", 0));
        component.addProperty(ObjectProperty("obj", obj));

        component.getTags().asPtr<ITagsPrivate>().add("tag1");
        component.getTags().asPtr<ITagsPrivate>().add("tag2");
        

        return component;
    }

    RegisteredComponent registerTestComponent(const ComponentPtr& customComponent = nullptr)
    {
        RegisteredComponent component{};

        if (customComponent == nullptr)
            component.serverComponent = createTestComponent();
        else
            component.serverComponent = customComponent;

        component.serverComponent.asPtr<IPropertyObjectInternal>().enableCoreEventTrigger();
        component.serverObject = std::make_shared<TmsServerComponent<>>(component.serverComponent, this->getServer(), ctx, serverContext);
        auto nodeId = component.serverObject->registerOpcUaNode();
        component.clientComponent = TmsClientComponent(NullContext(), nullptr, "test", clientContext, nodeId);
        return component;
    }
};

TEST_F(TmsComponentTest, Create)
{
    auto component = createTestComponent();
    auto serverComponent = TmsServerComponent(component, this->getServer(), ctx, serverContext);
}

TEST_F(TmsComponentTest, Register)
{
    auto component = registerTestComponent();
}

TEST_F(TmsComponentTest, Active)
{
    auto component = registerTestComponent();

    component.clientComponent.setActive(false);
    ASSERT_EQ(component.serverComponent.getActive(), component.clientComponent.getActive());

    component.clientComponent.setActive(true);
    ASSERT_EQ(component.serverComponent.getActive(), component.clientComponent.getActive());
}

TEST_F(TmsComponentTest, Tags)
{
    auto component = registerTestComponent();

    auto serverTags = component.serverComponent.getTags();
    auto clientTags = component.clientComponent.getTags();
    
    ASSERT_TRUE(clientTags.query("tag1") && clientTags.query("tag2"));
    ASSERT_TRUE(clientTags.contains("tag1") && clientTags.contains("tag2"));
}


TEST_F(TmsComponentTest, ModifyTags)
{
    auto component = registerTestComponent();

    auto serverTags = component.serverComponent.getTags();
    auto clientTags = component.clientComponent.getTags();
    
    ASSERT_TRUE(clientTags.query("tag1") && clientTags.query("tag2"));
    ASSERT_TRUE(clientTags.contains("tag1") && clientTags.contains("tag2"));

    serverTags.asPtr<ITagsPrivate>().remove("tag2");
    
    ASSERT_TRUE(clientTags.query("tag1") && !clientTags.query("tag2"));
    ASSERT_TRUE(clientTags.contains("tag1") && !clientTags.contains("tag2"));

    serverTags.asPtr<ITagsPrivate>().add("tag3");

    ASSERT_TRUE(clientTags.query("tag1") && clientTags.query("tag3"));
    ASSERT_TRUE(clientTags.contains("tag1") && clientTags.contains("tag3"));
}

TEST_F(TmsComponentTest, Properties)
{
    auto component = registerTestComponent();

    PropertyObjectPtr serverObj = component.serverComponent.getPropertyValue("obj");
    PropertyObjectPtr clientObj = component.clientComponent.getPropertyValue("obj");
    ASSERT_EQ(serverObj.getPropertyValue("Int"), clientObj.getPropertyValue("Int"));
    ASSERT_EQ(component.serverComponent.getPropertyValue("foo"), component.clientComponent.getPropertyValue("foo"));

    component.clientComponent.setPropertyValue("foo", "notbar");
    ASSERT_EQ(component.serverComponent.getPropertyValue("foo"), component.clientComponent.getPropertyValue("foo"));
}

TEST_F(TmsComponentTest, NameAndDescription)
{
    const auto component = registerTestComponent();
    ASSERT_EQ(component.serverComponent.getName(), component.clientComponent.getName());
    ASSERT_EQ(component.serverComponent.getDescription(), component.clientComponent.getDescription());

    component.serverComponent.setName("new_name");
    component.serverComponent.setDescription("new_description");

    ASSERT_EQ(component.serverComponent.getName(), component.clientComponent.getName());
    ASSERT_EQ(component.serverComponent.getDescription(), component.clientComponent.getDescription());

    component.clientComponent.setName("newer_name");
    component.clientComponent.setDescription("newer_description");

    ASSERT_EQ(component.serverComponent.getName(), "newer_name");
    ASSERT_EQ(component.clientComponent.getName(), "newer_name");
    ASSERT_EQ(component.serverComponent.getDescription(), "newer_description");
    ASSERT_EQ(component.clientComponent.getDescription(), "newer_description");
}

TEST_F(TmsComponentTest, NameAndDescriptionLocked)
{
    const auto name = "locked";
    const auto customComponent = Component(NullContext(), nullptr, name);
    customComponent.asPtr<IComponentPrivate>().lockAttributes(List<IString>("Name", "Description"));
    const auto component = registerTestComponent(customComponent);

    ASSERT_NO_THROW(component.clientComponent.setName("new_name"));
    ASSERT_NO_THROW(component.clientComponent.setDescription("new_description"));

    ASSERT_EQ(component.clientComponent.getName(), name);
}
