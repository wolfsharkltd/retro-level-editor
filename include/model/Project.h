//
// Created by vruser on 03/07/2022.
//

#ifndef EDITOR_MODEL_PROJECT_H
#define EDITOR_MODEL_PROJECT_H

#include <vector>
#include "nlohmann/json.hpp"

#include "Palette.h"
#include "Texture.h"

namespace Model {

    class Project {
    public:
        const std::string &getName() const;

        void setName(const std::string &mName);

        const std::vector<Palette> &getPalettes() const;

        void setPalettes(const std::vector<Model::Palette> &mPalettes);

    public:
        std::string name;
        std::vector<Model::Palette> palettes;
        std::vector<Model::Texture> textures;
    };

    void to_json(nlohmann::json& j, const Project& p);
    void from_json(const nlohmann::json& j, Project& p);
}

#endif //EDITOR_MODEL_PROJECT_H
