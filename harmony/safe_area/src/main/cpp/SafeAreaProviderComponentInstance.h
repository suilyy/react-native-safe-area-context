#pragma once
#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/StackNode.h"

namespace rnoh {
    class SafeAreaProviderComponentInstance : public CppComponentInstance {
    private:
        StackNode m_stackNode;

    public:
        SafeAreaProviderComponentInstance(Context context, facebook::react::Tag tag);

        void insertChild(ComponentInstance::Shared childComponentInstance, std::size_t index) override;

        void removeChild(ComponentInstance::Shared childComponentInstance) override;

        StackNode &getLocalRootArkUINode() override;
    };
} // namespace rnoh