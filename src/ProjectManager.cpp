//
// Created by vruser on 03/07/2022.
//

#include <iostream>

#include <fstream>

#include "nlohmann/json.hpp"

#include "ProjectManager.h"

#include <SDL_image.h>

std::shared_ptr<Model::Project> ProjectManager::NewProject()
{
    return std::make_shared<Model::Project>();
}

std::shared_ptr<Model::Project> ProjectManager::LoadFromFile(std::string filename) {

    std::ifstream ifs(filename.c_str());

    nlohmann::json jf = nlohmann::json::parse(ifs);

    auto project = jf.get<Model::Project>();

    // Load textures
    for(auto& texture : project.textures)
    {
        // Load from file
        texture.surface = IMG_Load(texture.filename.c_str());

        if(!texture.surface){
            printf("IMG_Load: %s\n", IMG_GetError());
        }

    }

    return std::make_shared<Model::Project>(project);
}

void ProjectManager::SaveToFile(std::shared_ptr<Model::Project> project, std::string filename)
{
    nlohmann::json jf = *project.get();

    std::ofstream file(filename.c_str());
    file << std::setw(4) << jf << std::endl;
}
