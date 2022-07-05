//
// Created by vruser on 03/07/2022.
//

#include "model/Palette.h"

namespace Model {

    void to_json(nlohmann::json& j, const Colour& p) {
        j = nlohmann::json{
            {"r", p.r},
            {"g", p.g},
            {"b", p.b},
        };
    }

    void from_json(const nlohmann::json& j, Colour& p) {
        j.at("r").get_to(p.r);
        j.at("g").get_to(p.g);
        j.at("b").get_to(p.b);
    }

    void to_json(nlohmann::json& j, const Palette& p) {
        j = nlohmann::json{
            {"name", p.name},
            {"colours", p.colours }
        };
    }

    void from_json(const nlohmann::json& j, Palette& p) {
        j.at("name").get_to(p.name);
        j.at("colours").get_to(p.colours);
    }
}
