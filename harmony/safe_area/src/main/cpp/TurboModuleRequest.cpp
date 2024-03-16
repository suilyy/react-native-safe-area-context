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

safeArea::Event TurboModuleRequest::getTurboModuleData(rnoh::CppComponentInstance::Context context) {
    // start handle turboModule
    //todo getTurboModule新版本框架闪退，先用mock值
    safeArea::Event data = {{0, 0, 0, 0}, {0, 0, 0, 0}};
//     auto ctx = context;
//     ArkJS arkJs(ctx.env);
//     {
//         auto result = arkJs.getObject(ctx.arkTsTurboModuleProviderRef)
//                           .call("hasModule", {arkJs.createString("RNCSafeAreaContext")});
//         if (!arkJs.getBoolean(result)) {
//             return data;
//         }
//     }
//     auto obj = arkJs.getObject(ctx.arkTsTurboModuleProviderRef);
//     auto n_turboModuleInstance = obj.call("getModule", {arkJs.createString("RNCSafeAreaContext")});
//     napi_ref turboModuleInstanceRef = arkJs.createReference(n_turboModuleInstance);
//     auto napiResult1 = arkJs.getObject(turboModuleInstanceRef).call("getConstants", {});
//     auto result1 = arkJs.getDynamic(napiResult1);
//     LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: x:"
//               << result1["initialWindowMetrics"]["frame"]["x"].asDouble();
//     LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: y:"
//               << result1["initialWindowMetrics"]["frame"]["y"].asDouble();
//     LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: width:"
//               << result1["initialWindowMetrics"]["frame"]["width"].asDouble();
//     LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: height:"
//               << result1["initialWindowMetrics"]["frame"]["height"].asDouble();
//     LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: top:"
//               << result1["initialWindowMetrics"]["insets"]["top"].asDouble();
//     LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: right:"
//               << result1["initialWindowMetrics"]["insets"]["right"].asDouble();
//     LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: bottom:"
//               << result1["initialWindowMetrics"]["insets"]["bottom"].asDouble();
//     LOG(INFO) << "[clx] <SafeAreaViewComponentInstance::setProps> initialWindowMetrics: left:"
//               << result1["initialWindowMetrics"]["insets"]["left"].asDouble();
//    
//     double_t frameX = result1["initialWindowMetrics"]["frame"]["x"].asDouble();
//     double_t frameY = result1["initialWindowMetrics"]["frame"]["y"].asDouble();
//     double_t frameWidth = result1["initialWindowMetrics"]["frame"]["width"].asDouble();
//     double_t frameHeight = result1["initialWindowMetrics"]["frame"]["height"].asDouble();
//     double_t insetsTop = result1["initialWindowMetrics"]["insets"]["top"].asDouble();
//     double_t insetsRight = result1["initialWindowMetrics"]["insets"]["right"].asDouble();
//     double_t insetsBottom = result1["initialWindowMetrics"]["insets"]["bottom"].asDouble();
//     double_t insetsLeft = result1["initialWindowMetrics"]["insets"]["left"].asDouble();

    double_t frameX = 0;
    double_t frameY = 0;
    double_t frameWidth = 387.692;
    double_t frameHeight = 836.923;
    double_t insetsTop = 38.7692;
    double_t insetsRight = 0;
    double_t insetsBottom = 0;
    double_t insetsLeft = 0;
    data = {{insetsTop, insetsRight, insetsBottom, insetsLeft}, {frameX, frameY, frameWidth, frameHeight}};
    return data;
};
