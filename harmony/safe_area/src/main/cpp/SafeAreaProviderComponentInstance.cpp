#include "SafeAreaProviderComponentInstance.h"

namespace rnoh {

    SafeAreaProviderComponentInstance::SafeAreaProviderComponentInstance(Context context, facebook::react::Tag tag)
        : CppComponentInstance(std::move(context), tag) {}

    void SafeAreaProviderComponentInstance::insertChild(ComponentInstance::Shared childComponentInstance, std::size_t index) {
        CppComponentInstance::insertChild(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void SafeAreaProviderComponentInstance::removeChild(ComponentInstance::Shared childComponentInstance) {
        CppComponentInstance::removeChild(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    StackNode &SafeAreaProviderComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

    
} // namespace rnoh
