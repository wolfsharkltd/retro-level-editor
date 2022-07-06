//
// Created by vruser on 06/07/2022.
//

#ifndef EDITOR_MAPNODE_H
#define EDITOR_MAPNODE_H

#include "nlohmann/json.hpp"

namespace Model {

    class MapNode {
    public:
        int x;
        int y;
        int w;
        int h;
    };

    void to_json(nlohmann::json& j, const MapNode& p);
    void from_json(const nlohmann::json& j, MapNode& p);
}

#endif //EDITOR_MAPNODE_H
