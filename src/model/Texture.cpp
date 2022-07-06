//
// Created by vruser on 06/07/2022.
//


#include "model/Texture.h"

namespace Model {

    void to_json(nlohmann::json& j, const Texture& p) {
        j = nlohmann::json{
            {"name", p.name},
            {"filename", p.filename},
        };
    }

    void from_json(const nlohmann::json& j, Texture& p) {
        j.at("name").get_to(p.name);
        j.at("filename").get_to(p.filename);
    }
}
