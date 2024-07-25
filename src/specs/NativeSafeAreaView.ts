import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent';
import type { WithDefault, Float, DirectEventHandler } from 'react-native/Libraries/Types/CodegenTypes';
import type { ViewProps, HostComponent } from 'react-native';

export type onSafeAreaValueChangeEvent = Readonly<{
  safeAreaViewInsetsValue?: {
    top?: Float;
    left?: Float;
    bottom?: Float
    right?: Float
  };
}>

export interface NativeProps extends ViewProps {
  mode?: WithDefault<'padding' | 'margin', 'padding'>;
  edges?: Readonly<{
    top: string;
    right: string;
    bottom: string;
    left: string;
  }>;
  isFirstRefresh: boolean;
  onSafeAreaValueChange: DirectEventHandler<onSafeAreaValueChangeEvent>,
}

export default codegenNativeComponent<NativeProps>('RNCSafeAreaView', {
  interfaceOnly: true,
}) as HostComponent<NativeProps>;