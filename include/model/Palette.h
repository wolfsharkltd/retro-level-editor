//
// Created by vruser on 03/07/2022.
//

#ifndef EDITOR_PALETTE_H
#define EDITOR_PALETTE_H

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace Model {

    struct Colour {
    public:
        union {
            float rgb[3];
            struct {
                float r;
                float g;
                float b;
            };
        };
    };

    void to_json(nlohmann::json& j, const Colour& p);
    void from_json(const nlohmann::json& j, Colour& p);

    class Palette {
    public:
        std::string name;
        std::vector<Colour> colours;
    };

    void to_json(nlohmann::json& j, const Palette& p);
    void from_json(const nlohmann::json& j, Palette& p);
}

#endif //EDITOR_PALETTE_H
