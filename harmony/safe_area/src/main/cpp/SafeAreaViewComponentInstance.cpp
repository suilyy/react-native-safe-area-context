#include "SafeAreaViewComponentInstance.h"
#include "Props.h"

namespace rnoh {

    SafeAreaViewComponentInstance::SafeAreaViewComponentInstance(Context context, facebook::react::Tag tag)
        : CppComponentInstance(std::move(context), tag) {}

    void SafeAreaViewComponentInstance::insertChild(ComponentInstance::Shared childComponentInstance,
                                                    std::size_t index) {
        CppComponentInstance::insertChild(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void SafeAreaViewComponentInstance::removeChild(ComponentInstance::Shared childComponentInstance) {
        CppComponentInstance::removeChild(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    SafeAreaViewStackNode &SafeAreaViewComponentInstance::getLocalRootArkUINode() { return m_stackNode; }

    std::string to_string(facebook::react::RNCSafeAreaViewMode mode) {
        switch (mode) {
        case facebook::react::RNCSafeAreaViewMode::PADDING:
            return "PADDING";
        case facebook::react::RNCSafeAreaViewMode::MARGIN:
            return "MARGIN";
        default:
            return "UNKNOWN";
        }
    }

    void SafeAreaViewComponentInstance::updateInsert(facebook::react::Props::Shared props){
    if (auto p = std::dynamic_pointer_cast<const facebook::react::RNCSafeAreaViewProps>(props)) {
            Edge edges = { "additive", "additive", "additive", "additive"};
            edges = {p->edges.top, p->edges.right, p->edges.bottom, p->edges.left};
            //todo rn框架目前获取getTurboModule还没有，假设有，先写后面的逻辑
            //todo 假设现在有通过getTurboModule获取的data
            Event data = {{30, 0, 0, 0}, {0, 0, 0, 0}};
            EdgeInsets edgesData;
            //todo marginInsets,paddingInsets应该是需要获取的，在capi中还不知道如何获取
            EdgeInsets marginInsets = {10, 0, 0, 0};
            EdgeInsets paddingInsets = {0, 0, 0 ,0};
            if (std::strcmp(to_string(p->mode).c_str(), "MARGIN") == 0) {
                edgesData = marginInsets;
            } else {
                edgesData = paddingInsets;
            }
            EdgeInsets insets = {(float)getEdgeValue(edges.top, data.insets.top, edgesData.top),
                                 (float)getEdgeValue(edges.right, data.insets.right, edgesData.right),
                                 (float)getEdgeValue(edges.bottom, data.insets.bottom, edgesData.bottom),
                                 (float)getEdgeValue(edges.left, data.insets.left, edgesData.left)};
            EdgeInsets zeroEdgeInsets = {0, 0, 0, 0};
            if (std::strcmp(to_string(p->mode).c_str(), "MARGIN") == 0) {
                this->getLocalRootArkUINode().contentSetMargin(insets);
                this->getLocalRootArkUINode().contentSetPadding(zeroEdgeInsets);
            } else {
                this->getLocalRootArkUINode().contentSetMargin(zeroEdgeInsets);
                this->getLocalRootArkUINode().contentSetPadding(insets);
            }
        }
    };

    std::size_t SafeAreaViewComponentInstance::getEdgeValue(std::string edgeMode, std::size_t insetValue, std::size_t edgeValue){
        if (std::strcmp(edgeMode.c_str(), "off") == 0) {
            return 0;
        } else if (std::strcmp(edgeMode.c_str(), "maximum") == 0) {
             //insetValue 安全区域    edgeValue原区域
              if (edgeValue > insetValue) {
                return edgeValue - insetValue;
              } else {
                return insetValue - edgeValue;
              }
        } else {
            return insetValue;
        }
    }

    void SafeAreaViewComponentInstance::setProps(facebook::react::Props::Shared props) {
        CppComponentInstance::setProps(props);
        if (auto p = std::dynamic_pointer_cast<const facebook::react::RNCSafeAreaViewProps>(props)) {
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.left: " << p->edges.left;
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.right: " << p->edges.right;
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.top: " << p->edges.top;
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.bottom: " << p->edges.bottom;
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> mode: " << to_string(p->mode);
            updateInsert(props);
        }
    }

} // namespace rnoh
