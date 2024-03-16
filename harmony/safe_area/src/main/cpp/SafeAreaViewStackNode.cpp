/**
 * MIT License
 *
 * Copyright (C) 2023 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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
        ArkUI_AttributeItem columnAlignItem = {columnAlignValue,
                                               sizeof(columnAlignValue) / sizeof(ArkUI_AttributeItem)};
        NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_ALIGNMENT, &columnAlignItem);
        m_stackArkUINodeHandle = NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_STACK);

        ArkUI_NumberValue clipValue[] = {{.i32 = 1}};
        ArkUI_AttributeItem clipItem = {clipValue, 1};
        NativeNodeApi::getInstance()->setAttribute(m_stackArkUINodeHandle, NODE_CLIP, &clipItem);

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

    SafeAreaViewStackNode::~SafeAreaViewStackNode() {}

    SafeAreaViewStackNode &SafeAreaViewStackNode::contentSetMargin(const safeArea::EdgeInsets &edgeInsets) {
        ArkUI_NumberValue marginValue[] = {(float)edgeInsets.top, (float)edgeInsets.right, (float)edgeInsets.bottom, (float)edgeInsets.left};
        ArkUI_AttributeItem marginItem = {marginValue, sizeof(marginValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_MARGIN, &marginItem);
        return *this;
    }

    SafeAreaViewStackNode &SafeAreaViewStackNode::contentSetPadding(const safeArea::EdgeInsets &edgeInsets) {
        ArkUI_NumberValue paddingValue[] = {(float)edgeInsets.top, (float)edgeInsets.right, (float)edgeInsets.bottom, (float)edgeInsets.left};
        ArkUI_AttributeItem paddingItem = {paddingValue, sizeof(paddingValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_stackArkUINodeHandle, NODE_PADDING, &paddingItem);
        return *this;
    }

    
} // namespace rnoh
