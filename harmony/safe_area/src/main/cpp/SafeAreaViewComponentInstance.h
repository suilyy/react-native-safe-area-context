#pragma once
#include "RNOH/CppComponentInstance.h"
#include "SafeAreaViewStackNode.h"

namespace rnoh {
    class SafeAreaViewComponentInstance : public CppComponentInstance {
    private:
        SafeAreaViewStackNode m_stackNode;

    public:
        SafeAreaViewComponentInstance(Context context, facebook::react::Tag tag);

        void insertChild(ComponentInstance::Shared childComponentInstance, std::size_t index) override;

        void removeChild(ComponentInstance::Shared childComponentInstance) override;
    
        void setProps(facebook::react::Props::Shared props) override;

        SafeAreaViewStackNode &getLocalRootArkUINode() override;
    
        void updateInsert(facebook::react::Props::Shared props);
    
        std::size_t getEdgeValue(std::string edgeMode, std::size_t insetValue, std::size_t edgeValue);
    };
} // namespace rnoh