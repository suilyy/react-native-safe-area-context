#pragma once

#include "RNOH/arkui/ArkUINode.h"
#include "RNOH/arkui/StackNode.h"

namespace rnoh {
    struct EdgeInsets {
        std::float_t top;
        std::float_t right;
        std::float_t bottom;
        std::float_t left;
    };

    struct Edge {
        std::string top;
        std::string right;
        std::string bottom;
        std::string left;
    };

    struct Frame {
        std::size_t x;
        std::size_t y;
        std::size_t width;
        std::size_t height;
    };

    struct Event {
        EdgeInsets insets;
        Frame frame;
    };

    class SafeAreaViewStackNode : public ArkUINode {
        protected:
        ArkUI_NodeHandle m_stackArkUINodeHandle;
    public:
        SafeAreaViewStackNode();
        ~SafeAreaViewStackNode() override;
        void insertChild(ArkUINode &child, std::size_t index);
        void removeChild(ArkUINode &child);
        SafeAreaViewStackNode &contentSetMargin(EdgeInsets const &);
        SafeAreaViewStackNode &contentSetPadding(EdgeInsets const &);
    };

} // namespace rnoh