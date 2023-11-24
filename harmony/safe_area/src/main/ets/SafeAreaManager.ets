import { RNOHContext, RNViewManager, Tag, OverflowMode, Point } from 'rnoh';

export class SafeAreaManager extends RNViewManager {
  protected offsetX: number = 0;
  protected offsetY: number = 0;

  constructor(
    tag: Tag,
    ctx: RNOHContext,
    offsetX: number,
    offsetY: number
  ) {
    super(tag, ctx);
    this.offsetX = offsetX
    this.offsetY = offsetY
  }

  setOffsetX(offsetX: number) {
    this.offsetX = offsetX
  }

  setOffsetY(offsetY: number) {
    this.offsetY = offsetY
  }

  public computeChildPoint(point: Point, childTag: Tag): Point {
    console.log("RNOH offsetY:" + this.offsetY);
    return super.computeChildPoint({ x: point.x + this.offsetX, y: point.y + this.offsetY }, childTag);
  }
}