//
// Created by vruser on 03/07/2022.
//

#include "model/Map.h"

namespace Model {

    void Map::Test() {

    }

    void to_json(nlohmann::json& j, const Map& p) {
        j = nlohmann::json{
                {"name", p.name},
                {"width", p.width},
            {"height", p.height},
            {"nodes", p.nodes}
        };
    }

    void from_json(const nlohmann::json& j, Map& p) {
        j.at("name").get_to(p.name);
        j.at("width").get_to(p.width);
        j.at("height").get_to(p.height);

        const nlohmann::json& sj = j.at("nodes");
        p.nodes.resize(sj.size());
        std::copy(sj.begin(), sj.end(), p.nodes.begin());
    }
}
