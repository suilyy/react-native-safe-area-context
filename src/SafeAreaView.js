import * as React from 'react';
import NativeSafeAreaView from './specs/NativeSafeAreaView';
import { useMemo, useState } from 'react';
const defaultEdges = {
    top: 'additive',
    left: 'additive',
    bottom: 'additive',
    right: 'additive',
};
let isOnChange = false;
let realTop = 0;
let realLeft = 0;
let realBottom = 0;
let realRight = 0;
let safeAreaTop = 0;
let safeAreaLeft = 0;
let safeAreaBottom = 0;
let safeAreaRight = 0;
function getEdgeValue(edgeMode, insetValue, edgeValue) {
    if (edgeMode === 'off') {
        return edgeValue;
    }
    else if (edgeMode === 'maximum') {
        return Math.max(insetValue, edgeValue);
    }
    else {
        return insetValue + edgeValue;
    }
}
export const SafeAreaView = React.forwardRef(({ edges, ...props }, ref) => {
    const nativeEdges = useMemo(() => {
        if (edges == null) {
            return defaultEdges;
        }
        const edgesObj = Array.isArray(edges)
            ? edges.reduce((acc, edge) => {
                acc[edge] = 'additive';
                return acc;
            }, {})
            : // ts has trouble with refining readonly arrays.
                edges;
        // make sure that we always pass all edges, required for fabric
        const requiredEdges = {
            top: edgesObj.top ?? 'off',
            right: edgesObj.right ?? 'off',
            bottom: edgesObj.bottom ?? 'off',
            left: edgesObj.left ?? 'off',
        };
        return requiredEdges;
    }, [edges]);
    const [isFirstRefresh, setIsFirstRefresh] = useState(false);
    let safeAreaStyle = [props.style];
    let rawPadding = 0;
    let rawMargin = 0;
    let rawPaddingTop = undefined;
    let rawPaddingLeft = undefined;
    let rawPaddingBottom = undefined;
    let rawPaddingRight = undefined;
    let rawMarginTop = undefined;
    let rawMarginLeft = undefined;
    let rawMarginBottom = undefined;
    let rawMarginRight = undefined;
    const safeAreaChange = (e) => {
        if (e.nativeEvent.safeAreaViewInsetsValue?.top) {
            safeAreaTop = e.nativeEvent.safeAreaViewInsetsValue?.top;
        }
        if (e.nativeEvent.safeAreaViewInsetsValue?.right) {
            safeAreaRight = e.nativeEvent.safeAreaViewInsetsValue?.right;
        }
        if (e.nativeEvent.safeAreaViewInsetsValue?.bottom) {
            safeAreaBottom = e.nativeEvent.safeAreaViewInsetsValue?.bottom;
        }
        if (e.nativeEvent.safeAreaViewInsetsValue?.left) {
            safeAreaLeft = e.nativeEvent.safeAreaViewInsetsValue?.left;
        }
        if (!isOnChange) {
            setIsFirstRefresh(true);
        }
        isOnChange = true;
    };
    let rawProp = props.style;
    let i;
    if (rawProp && rawProp.length > 0) {
        for (i = 0; i < rawProp.length; i++) {
            if (rawProp[i]?.padding) {
                rawPadding = rawProp[i]?.padding;
            }
            if (rawProp[i]?.margin) {
                rawMargin = rawProp[i]?.margin;
            }
            if (rawProp[i]?.paddingTop) {
                rawPaddingTop = rawProp[i]?.paddingTop;
            }
            if (rawProp[i]?.paddingLeft) {
                rawPaddingLeft = rawProp[i]?.paddingLeft;
            }
            if (rawProp[i]?.paddingRight) {
                rawPaddingRight = rawProp[i]?.paddingRight;
            }
            if (rawProp[i]?.paddingBottom) {
                rawPaddingBottom = rawProp[i]?.paddingBottom;
            }
            if (rawProp[i]?.marginTop) {
                rawMarginTop = rawProp[i]?.marginTop;
            }
            if (rawProp[i]?.marginLeft) {
                rawMarginLeft = rawProp[i]?.marginLeft;
            }
            if (rawProp[i]?.marginRight) {
                rawMarginRight = rawProp[i]?.marginRight;
            }
            if (rawProp[i]?.marginBottom) {
                rawMarginBottom = rawProp[i]?.marginBottom;
            }
        }
    }
    if (!rawPaddingTop) {
        rawPaddingTop = rawPadding;
    }
    if (!rawPaddingLeft) {
        rawPaddingLeft = rawPadding;
    }
    if (!rawPaddingRight) {
        rawPaddingRight = rawPadding;
    }
    if (!rawPaddingBottom) {
        rawPaddingBottom = rawPadding;
    }
    if (!rawMarginTop) {
        rawMarginTop = rawMargin;
    }
    if (!rawMarginLeft) {
        rawMarginLeft = rawMargin;
    }
    if (!rawMarginRight) {
        rawMarginRight = rawMargin;
    }
    if (!rawMarginBottom) {
        rawMarginBottom = rawMargin;
    }
    if (isOnChange) {
        if (props.mode === 'margin') {
            realTop = getEdgeValue(nativeEdges.top, safeAreaTop, rawMarginTop);
            realLeft = getEdgeValue(nativeEdges.left, safeAreaLeft, rawMarginLeft);
            realBottom = getEdgeValue(nativeEdges.bottom, safeAreaBottom, rawMarginBottom);
            realRight = getEdgeValue(nativeEdges.right, safeAreaRight, rawMarginRight);
            safeAreaStyle = [props.style, { marginTop: realTop, marginLeft: realLeft, marginBottom: realBottom, marginRight: realRight }];
        }
        else {
            realTop = getEdgeValue(nativeEdges.top, safeAreaTop, rawPaddingTop);
            realLeft = getEdgeValue(nativeEdges.left, safeAreaLeft, rawPaddingLeft);
            realBottom = getEdgeValue(nativeEdges.bottom, safeAreaBottom, rawPaddingBottom);
            realRight = getEdgeValue(nativeEdges.right, safeAreaRight, rawPaddingRight);
            safeAreaStyle = [props.style, { paddingTop: realTop, paddingLeft: realLeft, paddingBottom: realBottom, paddingRight: realRight }];
        }
    }
    return <NativeSafeAreaView {...props} style={safeAreaStyle} edges={nativeEdges} isFirstRefresh={isFirstRefresh} onSafeAreaValueChange={safeAreaChange} ref={ref}/>;
});
