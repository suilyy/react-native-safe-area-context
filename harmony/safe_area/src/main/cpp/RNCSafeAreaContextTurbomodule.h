#pragma once

#include <ReactCommon/TurboModule.h>
#include "RNOH/ArkTSTurboModule.h"

namespace rnoh {

    class JSI_EXPORT RNCSafeAreaContextTurbomodule : public ArkTSTurboModule {
    public:
        RNCSafeAreaContextTurbomodule(const ArkTSTurboModule::Context ctx, const std::string name);
    };

} // namespace rnoh