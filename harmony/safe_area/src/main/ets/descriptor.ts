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

/** 0-1 */
export type NormalizedScalar = number;

/** RGBA */
export type ColorSegments = [
  NormalizedScalar,
  NormalizedScalar,
  NormalizedScalar,
  NormalizedScalar,
];

export type Tag = number;

export type LayoutProps = {
  top: number;
  left: number;
  width: number;
  height: number;
};

export type LayoutMetrics = {
  frame: {
    origin: {
      x: number;
      y: number;
    };
    size: {
      width: number;
      height: number;
    };
  };
};

export type Descriptor<
  TType = string,
  TProps extends Object = Object,
  TState = {},
> = {
  type: TType;
  tag: Tag;
  parentTag?: Tag;
  props: TProps;
  state: TState;
  childrenTags: Tag[];
  layoutMetrics: LayoutMetrics;
};

export class DescriptorClass<
  TType = string,
  TProps extends Object = Object,
  TState = {},
> implements Descriptor<TType, TProps, TState>
{
  type: TType;
  tag: Tag;
  parentTag?: Tag;
  props: TProps;
  state: TState;
  childrenTags: Tag[];
  layoutMetrics: LayoutMetrics;
}

export type PaddingProps = {
  top: number;
  right: number;
  bottom: number;
  left: number;
};
