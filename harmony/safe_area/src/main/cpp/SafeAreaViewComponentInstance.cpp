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
#include "SafeAreaViewComponentInstance.h"
#include "Props.h"
#include "TurboModuleRequest.h"

namespace rnoh {

    SafeAreaViewComponentInstance::SafeAreaViewComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {
        m_context = context;
    }

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
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.left: RNCSafeAreaViewMode::PADDING";
            return "PADDING";
        case facebook::react::RNCSafeAreaViewMode::MARGIN:
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.left: RNCSafeAreaViewMode::MARGIN";
            return "MARGIN";
        default:
            return "UNKNOWN";
        }
    }

    void SafeAreaViewComponentInstance::updateInsert(facebook::react::Props::Shared props) {
        if (auto p = std::dynamic_pointer_cast<const facebook::react::RNCSafeAreaViewProps>(props)) {
            safeArea::Edge edges = {"additive", "additive", "additive", "additive"};
            edges = {p->edges.top, p->edges.right, p->edges.bottom, p->edges.left};
            TurboModuleRequest request;
            safeArea::Event data = request.getTurboModuleData(this->m_context);
            safeArea::EdgeInsets edgesData;
            float_t rawPadding = p->rawProps["padding"].asInt();
            float_t rawMargin = p->rawProps["margin"].asInt();
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
                this->getLocalRootArkUINode().contentSetMargin(insets);
                this->getLocalRootArkUINode().contentSetPadding(zeroEdgeInsets);
            } else {
                this->getLocalRootArkUINode().contentSetMargin(zeroEdgeInsets);
                this->getLocalRootArkUINode().contentSetPadding(insets);
            }
        }
    };

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

    void SafeAreaViewComponentInstance::setProps(facebook::react::Props::Shared props) {
        CppComponentInstance::setProps(props);
        if (auto p = std::dynamic_pointer_cast<const facebook::react::RNCSafeAreaViewProps>(props)) {
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.left: " << p->edges.left;
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.right: " << p->edges.right;
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.top: " << p->edges.top;
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> edges.bottom: " << p->edges.bottom;
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> mode: " << to_string(p->mode);
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> padding: " << p->rawProps["padding"].asInt();
            LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> padding: " << p->rawProps["margin"].asInt();
            updateInsert(props);
        }
    }

} // namespace rnoh
