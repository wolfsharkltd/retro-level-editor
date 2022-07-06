//
// Created by vruser on 03/07/2022.
//
#include <vector>
#include <memory>

#include "nlohmann/json.hpp"

#include "model/Project.h"

namespace Model {
    void to_json(nlohmann::json& j, const Project& p) {
        j = nlohmann::json{
            {"name", p.name},
            {"palettes", p.palettes },
            {"textures", p.textures },
        };
    }

    void from_json(const nlohmann::json& j, Project& p) {
        j.at("name").get_to(p.name);

        const nlohmann::json& sj = j.at("palettes");
        p.palettes.resize(sj.size());
        std::copy(sj.begin(), sj.end(), p.palettes.begin());

        const nlohmann::json& jpalettes = j.at("textures");
        p.textures.resize(jpalettes.size());
        std::copy(jpalettes.begin(), jpalettes.end(), p.textures.begin());
    }
}

const std::string &Model::Project::getName() const {
    return name;
}

void Model::Project::setName(const std::string &mName) {
    name = mName;
}

const std::vector<Model::Palette> &Model::Project::getPalettes() const {
    return palettes;
}

void Model::Project::setPalettes(const std::vector<Model::Palette> &mPalettes) {
    palettes = mPalettes;
}
