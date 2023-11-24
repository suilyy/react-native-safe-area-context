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
  ViewBaseProps,
  Tag
} from 'rnoh'

import { SafeAreaViewTurboModule } from "./SafeViewTurboModule"
import { ColorSegments } from './descriptor'
import { convertColorSegmentsToString } from './utils'
import { convertTransformMatrix } from "./utils"
import { SafeAreaManager } from './SafeAreaManager';
import { EdgeInsets, AvoidArea, Event, borderColor, Edges } from './common/SafeAreaType';
import Logger from './Logger'

export const SAFE_AREA_TYPE: string = "RNCSafeAreaView"


export interface AvoidAreaProps extends ViewBaseProps {
  edges: string
  mode: string
  margin: EdgeInsets
  padding: EdgeInsets
  backgroundColor?: ColorSegments
  borderWidth?: Edge
  borderColor?: borderColor
  borderRadius?: number
  opacity?: number
  overflow?: number

}


export type SafeAreaDescriptor = Descriptor<"RNCSafeAreaView", AvoidAreaProps>

const TAG: string = '[RNOH]RNCSafeAreaView'

@Component
export struct RNCSafeAreaView {
  ctx!: RNOHContext
  tag: number = 0
  @BuilderParam buildCustomComponent: (componentBuilderContext: ComponentBuilderContext) => void
  private unregisterDescriptorChangesListener?: () => void = undefined
  private cleanupCommandCallback?: () => void = undefined
  private unregisterComponentManager?: () => void = undefined
  @State descriptor: SafeAreaDescriptor = {} as SafeAreaDescriptor
  @State avoidArea: AvoidArea = {} as AvoidArea
  @State edgeInsets: EdgeInsets = { top: 0, right: 0, bottom: 0, left: 0 }
  private componentManager!: SafeAreaManager

  getEdgeValue(edgeMode: string, insetValue: number, edgeValue: number): number {
    if (edgeMode == 'off') {
      return 0;
    } else if (edgeMode == 'maximum') {
      //insetValue 安全区域    edgeValue原区域
      if (edgeValue > insetValue) {
        return edgeValue - insetValue
      } else {
        return insetValue - edgeValue
      }
    } else {
      return insetValue;
    }
  }

  updateInsets() {
    const safeAreaViewTurboModule = this.ctx.rnInstance.getTurboModule<SafeAreaViewTurboModule>("RNCSafeAreaContext")
    const safeAreaInsets = safeAreaViewTurboModule.getSafeAreaInsets();
    let edges: Edges = { top: 'additive', right: 'additive', bottom: 'additive', left: 'additive' };
    if (this.descriptor.props.edges) {
      edges = JSON.parse(this.descriptor.props.edges) as Edges
    }

    safeAreaInsets.then((data: Event) => {
      Logger.info(TAG, JSON.stringify(data))
      // Logger.info(TAG, Math.abs(data.frame.height - data.insets.top - this.descriptor.layoutMetrics.frame.size.height))
      // if (Math.abs(data.frame.height - data.insets.top - this.descriptor.layoutMetrics.frame.size.height) < 1) {
      //   throw "判断已经规避状态栏"
      // }
      if (data.insets) {
        this.edgeInsets = {
          top: this.getEdgeValue(edges.top, data.insets.top, (this.descriptor.props.mode == 'margin' ? this.descriptor.props.margin.top : this.descriptor.props.padding.top)),
          right: this.getEdgeValue(edges.right, data.insets.right, this.descriptor.props.mode == 'margin' ? this.descriptor.props.margin.right : this.descriptor.props.padding.right) | 0,
          bottom: this.getEdgeValue(edges.bottom, data.insets.bottom, this.descriptor.props.mode == 'margin' ? this.descriptor.props.margin.bottom : this.descriptor.props.padding.bottom) | 0,
          left: this.getEdgeValue(edges.left, data.insets.left, this.descriptor.props.mode == 'margin' ? this.descriptor.props.margin.left : this.descriptor.props.padding.left) | 0
        }
      }

      // this.edgeInsets = {
      //   top: this.getEdgeValue(edges.top, data.insets.top, (this.descriptor.props.mode == 'margin' ? this.descriptor.props.margin.top : this.descriptor.props.padding.top)),
      //   right: this.getEdgeValue(edges.right, data.insets.right, this.descriptor.props.mode == 'margin' ? this.descriptor.props.margin.right : this.descriptor.props.padding.right) | 0,
      //   bottom: this.getEdgeValue(edges.bottom, data.insets.bottom, this.descriptor.props.mode == 'margin' ? this.descriptor.props.margin.bottom : this.descriptor.props.padding.bottom) | 0,
      //   left: this.getEdgeValue(edges.left, data.insets.left, this.descriptor.props.mode == 'margin' ? this.descriptor.props.margin.left : this.descriptor.props.padding.left) | 0
      // }
      // Logger.info(TAG, "edgeInsets " + JSON.stringify(this.edgeInsets))

    })
      .catch((e: string | Error) => {
        Logger.error(TAG, JSON.stringify(e));
        this.edgeInsets = {
          top: 0,
          right: 0,
          bottom: 0,
          left: 0
        }
      })
      .finally(() => {
        let offsetY = this.edgeInsets.bottom - this.edgeInsets.top
        let offsetX = this.edgeInsets.right - this.edgeInsets.left
        this.componentManager.setOffsetY(offsetY)
        this.componentManager.setOffsetX(offsetX)
        this.componentManager.updateBoundingBox()
      })
  }

  aboutToAppear() {
    this.descriptor = this.ctx.descriptorRegistry.getDescriptor<SafeAreaDescriptor>(this.tag)
    Logger.info(TAG, JSON.stringify(this.descriptor))
    this.unregisterDescriptorChangesListener = this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
      (newDescriptor) => {
        Logger.info(TAG, JSON.stringify(newDescriptor))
        this.descriptor = (newDescriptor as SafeAreaDescriptor)
        this.updateInsets()
        Logger.info(TAG, 'updateInsets' + JSON.stringify(this.edgeInsets))
      }
    )
    this.componentManager = new SafeAreaManager(this.tag, this.ctx, 0, 0)
    this.unregisterComponentManager = this.ctx.componentManagerRegistry.registerComponentManager(this.tag, this.componentManager)
    this.updateInsets()
  }

  aboutToDisappear() {
    this.unregisterDescriptorChangesListener?.()
    this.unregisterComponentManager?.()
  }

  build() {
    Column() {
      Stack() {
        RNViewBase({ ctx: this.ctx, tag: this.tag, componentManager: this.componentManager }) {
          ForEach(this.descriptor.childrenTags, (tag: Tag) => {
            RNComponentFactory({
              ctx: this.ctx,
              tag: tag,
              buildCustomComponent: this.buildCustomComponent })
          }, (tag: Tag) => tag.toString())
        }
      }
      .width(this.descriptor.layoutMetrics.frame.size.width)
      .height(this.descriptor.layoutMetrics.frame.size.height)
      .backgroundColor(convertColorSegmentsToString(this.descriptor.props.backgroundColor))
      .borderWidth(this.descriptor.props.borderWidth)
      // .borderColor({
      //   left: convertColorSegmentsToString(this.descriptor.props.borderColor.left ? this.descriptor.props.borderColor.left : [0, 0, 0, 0]),
      //   top: convertColorSegmentsToString(this.descriptor.props.borderColor.top ? this.descriptor.props.borderColor.top : [0, 0, 0, 0]),
      //   right: convertColorSegmentsToString(this.descriptor.props.borderColor.right ? this.descriptor.props.borderColor.right : [0, 0, 0, 0]),
      //   bottom: convertColorSegmentsToString(this.descriptor.props.borderColor.bottom ? this.descriptor.props.borderColor.bottom : [0, 0, 0, 0]),
      // })
      .borderRadius(this.descriptor.props.borderRadius)
      .opacity(this.descriptor.props.opacity)
      .transform(this.descriptor.props.transform != undefined ? convertTransformMatrix(this.descriptor.props.transform) : undefined)
      .clip(this.descriptor.props.overflow == 1 ? true : false)
      .margin(this.descriptor.props.mode == 'margin' ? this.edgeInsets : 0)
      .padding(this.descriptor.props.mode == 'margin' ? 0 : this.edgeInsets)
    }
    .align(Alignment.TopStart)
    .position({ y: this.descriptor.layoutMetrics.frame.origin.y, x: this.descriptor.layoutMetrics.frame.origin.x })
    .width('100%')
    .height('100%')
  }
}
