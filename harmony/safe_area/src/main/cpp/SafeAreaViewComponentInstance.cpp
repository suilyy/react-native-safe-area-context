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
#include "RNOH/arkui/NativeNodeApi.h"
#include "SafeAreaViewComponentInstance.h"
#include "Props.h"
#include "TurboModuleRequest.h"

namespace rnoh {

    SafeAreaViewComponentInstance::SafeAreaViewComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {
        m_safeAreaViewStackNode.insertChild(m_stackNode, 0);
    }

    void SafeAreaViewComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance,
                                                        std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);
        m_stackNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    void SafeAreaViewComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_stackNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    };

    SafeAreaViewStackNode &SafeAreaViewComponentInstance::getLocalRootArkUINode() { return m_safeAreaViewStackNode; }

    std::string to_string(facebook::react::RNCSafeAreaViewMode mode) {
        switch (mode) {
        case facebook::react::RNCSafeAreaViewMode::PADDING:
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.left: RNCSafeAreaViewMode::PADDING";
            return "PADDING";
        case facebook::react::RNCSafeAreaViewMode::MARGIN:
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.left: RNCSafeAreaViewMode::MARGIN";
            return "MARGIN";
        default:
            return "UNKNOWN";
        }
    }

    void SafeAreaViewComponentInstance::updateInsert(SharedConcreteProps p) {
        safeArea::Edge edges = {"additive", "additive", "additive", "additive"};
        edges = {p->edges.top, p->edges.right, p->edges.bottom, p->edges.left};
        TurboModuleRequest request;
        safeArea::Event data = request.getTurboModuleData(this->m_deps);
        safeArea::EdgeInsets edgesData;
        float_t rawPadding = 0;
        float_t rawMargin = 0;
        if (p->rawProps.get_ptr("padding") != nullptr) {
            rawPadding = p->rawProps["padding"].asInt();
        }
        if (p->rawProps.get_ptr("margin") != nullptr) {
            rawMargin = p->rawProps["margin"].asInt();
        }
        safeArea::EdgeInsets marginInsets = {rawMargin, rawMargin, rawMargin, rawMargin};
        safeArea::EdgeInsets paddingInsets = {rawPadding, rawPadding, rawPadding, rawPadding};
        if (std::strcmp(to_string(p->mode).c_str(), "MARGIN") == 0) {
            edgesData = marginInsets;
        } else {
            edgesData = paddingInsets;
        }
        safeArea::EdgeInsets insets = {getEdgeValue(edges.top, data.insets.top, edgesData.top),
                                       getEdgeValue(edges.right, data.insets.right, edgesData.right),
                                       getEdgeValue(edges.bottom, data.insets.bottom, edgesData.bottom),
                                       getEdgeValue(edges.left, data.insets.left, edgesData.left)};
        safeArea::EdgeInsets zeroEdgeInsets = {0, 0, 0, 0};
        if (std::strcmp(to_string(p->mode).c_str(), "MARGIN") == 0) {
            m_safeAreaViewStackNode.setMargin(insets);
            contentSetPadding(zeroEdgeInsets);
        } else {
            m_safeAreaViewStackNode.setMargin(zeroEdgeInsets);
            contentSetPadding(insets);
        }
    }

    void SafeAreaViewComponentInstance::contentSetPadding(const safeArea::EdgeInsets edgeInsets) {
        ArkUI_NumberValue paddingValue[] = {(float)edgeInsets.top, (float)edgeInsets.right, (float)edgeInsets.bottom,
                                            (float)edgeInsets.left};
        ArkUI_AttributeItem paddingItem = {paddingValue, sizeof(paddingValue) / sizeof(ArkUI_NumberValue)};
        NativeNodeApi::getInstance()->setAttribute(m_stackNode.getArkUINodeHandle(), NODE_PADDING, &paddingItem);
    }

    std::double_t SafeAreaViewComponentInstance::getEdgeValue(std::string edgeMode, double_t insetValue,
                                                              double_t edgeValue) {
        if (std::strcmp(edgeMode.c_str(), "off") == 0) {
            return 0;
        } else if (std::strcmp(edgeMode.c_str(), "maximum") == 0) {
            // insetValue 安全区域    edgeValue原区域
            if (edgeValue > insetValue) {
                return edgeValue - insetValue;
            } else {
                return insetValue - edgeValue;
            }
        } else {
            return insetValue;
        }
    }

    void SafeAreaViewComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
        CppComponentInstance::onPropsChanged(props);
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.left: " << props->edges.left;
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.right: " << props->edges.right;
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.top: " << props->edges.top;
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.bottom: " << props->edges.bottom;
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> mode: " << to_string(props->mode);
        if (props->rawProps.get_ptr("padding") != nullptr) {
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> padding: "
                      << props->rawProps["padding"].asInt();
        }
        if (props->rawProps.get_ptr("margin") != nullptr) {
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> margin: "
                      << props->rawProps["margin"].asInt();
        }
        m_stackNode.setSize(m_layoutMetrics.frame.size);
        m_stackNode.setBackgroundColor(props->backgroundColor);
        facebook::react::BorderMetrics borderMetrics = props->resolveBorderMetrics(m_layoutMetrics);
        m_stackNode.setBorderWidth(borderMetrics.borderWidths);
        m_stackNode.setBorderRadius(borderMetrics.borderRadii);
        auto opacity = props->opacity;
        float validOpacity = std::max(0.0f, std::min((float)opacity, 1.0f));
        facebook::react::Transform transform = props->transform;
        if (props->backfaceVisibility == facebook::react::BackfaceVisibility::Hidden) {
            facebook::react::Vector vec{0, 0, 1, 0};
            auto resVec = transform * vec;
            if (resVec.z < 0.0) {
                validOpacity = 0.0;
            }
        }
        m_stackNode.setOpacity(validOpacity);
        m_stackNode.setTransform(props->transform, m_layoutMetrics.pointScaleFactor);
        m_stackNode.setClip(props->getClipsContentToBounds() ? 1 : 0);
        updateInsert(props);
    }

} // namespace rnoh
