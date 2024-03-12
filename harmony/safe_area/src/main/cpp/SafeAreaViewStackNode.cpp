#include "SafeAreaViewStackNode.h"
#include "RNOH/arkui/NativeNodeApi.h"
#include <memory>
#include "glog/logging.h"

namespace rnoh {
    SafeAreaViewStackNode::SafeAreaViewStackNode()
        : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_COLUMN)),
          m_stackArkUINodeHandle(nullptr) {
            maybeThrow(NativeNodeApi::getInstance()->registerNodeEvent(m_nodeHandle, NODE_TOUCH_EVENT, 0));
            ArkUI_NumberValue columnAlignValue[] = {{.i32 = ARKUI_ALIGNMENT_TOP_START}};
            ArkUI_AttributeItem columnAlignItem = {columnAlignValue, sizeof(columnAlignValue) / sizeof(ArkUI_AttributeItem)};
            NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_ALIGNMENT, &columnAlignItem);
            m_stackArkUINodeHandle = NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_STACK);
            NativeNodeApi::getInstance()->addChild(m_nodeHandle, m_stackArkUINodeHandle);
          }

    void SafeAreaViewStackNode::insertChild(ArkUINode &child, std::size_t index) {
        if (m_stackArkUINodeHandle != nullptr) {
            maybeThrow(NativeNodeApi::getInstance()->addChild(m_stackArkUINodeHandle, child.getArkUINodeHandle()));
        }
    }

    void SafeAreaViewStackNode::removeChild(ArkUINode &child) {
        if (m_stackArkUINodeHandle != nullptr) {
            maybeThrow(NativeNodeApi::getInstance()->removeChild(m_stackArkUINodeHandle, child.getArkUINodeHandle()));
            m_stackArkUINodeHandle = nullptr;
        }
    }

    SafeAreaViewStackNode::~SafeAreaViewStackNode() {
    }

    SafeAreaViewStackNode & SafeAreaViewStackNode::contentSetMargin(const EdgeInsets &edgeInsets) {
        ArkUI_NumberValue marginValue[] = {edgeInsets.top, edgeInsets.right, edgeInsets.bottom, edgeInsets.left};
        ArkUI_AttributeItem marginItem = {marginValue, sizeof(marginValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_stackArkUINodeHandle, NODE_MARGIN, &marginItem);
        return *this;
    }

    SafeAreaViewStackNode & SafeAreaViewStackNode::contentSetPadding(const EdgeInsets &edgeInsets) {
        ArkUI_NumberValue paddingValue[] = {edgeInsets.top, edgeInsets.right, edgeInsets.bottom, edgeInsets.left};
        ArkUI_AttributeItem paddingItem = {paddingValue, sizeof(paddingValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_stackArkUINodeHandle, NODE_PADDING, &paddingItem);
        return *this;
    }

    
} // namespace rnoh
