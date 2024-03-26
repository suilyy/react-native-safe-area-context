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

#include "TurboModuleRequest.h"

safeArea::Event TurboModuleRequest::getTurboModuleData(rnoh::ComponentInstance::Dependencies::Shared deps) {
    safeArea::Event data = {{0, 0, 0, 0}, {0, 0, 0, 0}};
    auto rnInstancePtr = deps->rnInstance.lock();
    folly::dynamic result1;
    if (rnInstancePtr != nullptr) {
        auto turboModule = rnInstancePtr->getTurboModule("RNCSafeAreaContext");
        auto arkTsTurboModule = std::dynamic_pointer_cast<rnoh::ArkTSTurboModule>(turboModule);
        result1 = arkTsTurboModule->callSync("getConstants", {});
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: x:"
                  << result1["initialWindowMetrics"]["frame"]["x"].asDouble();
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: y:"
                  << result1["initialWindowMetrics"]["frame"]["y"].asDouble();
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: width:"
                  << result1["initialWindowMetrics"]["frame"]["width"].asDouble();
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: height:"
                  << result1["initialWindowMetrics"]["frame"]["height"].asDouble();
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: top:"
                  << result1["initialWindowMetrics"]["insets"]["top"].asDouble();
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: right:"
                  << result1["initialWindowMetrics"]["insets"]["right"].asDouble();
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: bottom:"
                  << result1["initialWindowMetrics"]["insets"]["bottom"].asDouble();
        LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: left:"
                  << result1["initialWindowMetrics"]["insets"]["left"].asDouble();
        double_t frameX = result1["initialWindowMetrics"]["frame"]["x"].asDouble();
        double_t frameY = result1["initialWindowMetrics"]["frame"]["y"].asDouble();
        double_t frameWidth = result1["initialWindowMetrics"]["frame"]["width"].asDouble();
        double_t frameHeight = result1["initialWindowMetrics"]["frame"]["height"].asDouble();
        double_t insetsTop = result1["initialWindowMetrics"]["insets"]["top"].asDouble();
        double_t insetsRight = result1["initialWindowMetrics"]["insets"]["right"].asDouble();
        double_t insetsBottom = result1["initialWindowMetrics"]["insets"]["bottom"].asDouble();
        double_t insetsLeft = result1["initialWindowMetrics"]["insets"]["left"].asDouble();

        data = {{insetsTop, insetsRight, insetsBottom, insetsLeft}, {frameX, frameY, frameWidth, frameHeight}};
    }
    return data;
};
