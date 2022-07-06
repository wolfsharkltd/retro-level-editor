//
// Created by vruser on 06/07/2022.
//

#include "model/MapNode.h"

namespace Model {

    void to_json(nlohmann::json& j, const MapNode& p) {
        j = nlohmann::json{
                {"x", p.x},
                {"y", p.y},
                {"w", p.w},
                {"h", p.h}
        };
    }

    void from_json(const nlohmann::json& j, MapNode& p) {
        j.at("x").get_to(p.x);
        j.at("y").get_to(p.y);
        j.at("w").get_to(p.w);
        j.at("h").get_to(p.h);
    }
}
