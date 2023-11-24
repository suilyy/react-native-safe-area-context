/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { ColorSegments } from '../descriptor'

export type Edge = {
  top?: number
  right?: number
  bottom?: number
  left?: number
}

export type EdgeInsets = {
  top: number
  right: number
  bottom: number
  left: number
}

export type Edges = {
  top: string
  right: string
  bottom: string
  left: string
}

export type borderColor = {
  top?: ColorSegments
  right?: ColorSegments
  bottom?: ColorSegments
  left?: ColorSegments
}

export type Frame = {
  x: number
  y: number
  width: number
  height: number
}

export type Event = {
  insets: EdgeInsets
  frame: Frame
}

export type Rect = {
  top?: number
  right?: number
  bottom?: number
  left?: number
}

export type AvoidArea = {
  margin?: Rect | number
  padding?: Rect | number
}

export type AvoidAreaProps = {
  edges: string
  mode: string
  margin: string
  padding: string
}

export type Tag = number;