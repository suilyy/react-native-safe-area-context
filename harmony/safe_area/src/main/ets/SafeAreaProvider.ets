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

import {
  Descriptor,
  ComponentBuilderContext,
  RNComponentFactory,
  RNOHContext,
  RNViewBase,
  ViewRawProps,
} from 'rnoh'

import { SafeAreaViewTurboModule } from "./SafeViewTurboModule"
import { EdgeInsets, Frame, Event, Tag } from './common/SafeAreaType';
import Logger from './Logger'

export const SAFE_AREA_PROVIDER_TYPE: string = "RNCSafeAreaProvider"


export type RNCSafeAreaProviderDescriptor = Descriptor<"RNCSafeAreaProvider", ViewRawProps>

@Component
export struct SafeAreaProvider {
  ctx!: RNOHContext
  tag: number = 0
  // @State private childrenTags: Tag[] = []
  @BuilderParam buildCustomComponent: (componentBuilderContext: ComponentBuilderContext) => void
  private unregisterDescriptorChangesListener?: () => void = undefined
  private cleanupCommandCallback?: () => void = undefined
  @State descriptor: RNCSafeAreaProviderDescriptor = {} as RNCSafeAreaProviderDescriptor

  onInsetsChange() {
    const safeAreaViewTurboModule = this.ctx.rnInstance.getTurboModule<SafeAreaViewTurboModule>("RNCSafeAreaContext")
    const safeAreaInsets = safeAreaViewTurboModule.getSafeAreaInsets();
    safeAreaInsets.then((data: Event) => {
      this.ctx.rnInstance.emitComponentEvent(this.descriptor.tag, SAFE_AREA_PROVIDER_TYPE, {
        type: "onInsetsChange",
        insets: data.insets,
        frame: {
          x: this.descriptor.layoutMetrics.frame.origin.x,
          y: this.descriptor.layoutMetrics.frame.origin.y,
          width: this.descriptor.layoutMetrics.frame.size.width,
          height: this.descriptor.layoutMetrics.frame.size.height
        },
      })
    })
  }

  aboutToAppear() {
    this.descriptor = this.ctx.descriptorRegistry.getDescriptor<RNCSafeAreaProviderDescriptor>(this.tag)
    Logger.info(JSON.stringify(this.descriptor))
    this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
      (newDescriptor) => {
        Logger.info(JSON.stringify(newDescriptor))
        this.descriptor = (newDescriptor as RNCSafeAreaProviderDescriptor)
      }
    )
    this.onInsetsChange()
  }

  aboutToDisappear() {
    this.unregisterDescriptorChangesListener?.()
  }

  build() {
    RNViewBase({
      ctx: this.ctx,
      tag: this.tag
    }) {
      ForEach(this.descriptor.childrenTags, (childrenTag: Tag) => {
        RNComponentFactory({ ctx: this.ctx, tag: childrenTag, buildCustomComponent: this.buildCustomComponent })
      }, (childrenTag: Tag) => childrenTag.toString())
    }
  }
}
