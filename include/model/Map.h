//
// Created by vruser on 03/07/2022.
//

#ifndef EDITOR_MAP_H
#define EDITOR_MAP_H
#include "nlohmann/json.hpp"

#include "MapNode.h"

namespace Model {

    class Map {
    public:
        std::string name;
        int width;
        int height;

        std::vector<MapNode> nodes;

    public:

    public:
        void Test();
    };

    void to_json(nlohmann::json& j, const Map& p);
    void from_json(const nlohmann::json& j, Map& p);

}


#endif //EDITOR_MAP_H
