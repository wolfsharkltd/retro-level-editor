//
// Created by vruser on 03/07/2022.
//

#include <iostream>

#include <fstream>

#include "nlohmann/json.hpp"

#include "ProjectManager.h"

std::shared_ptr<Model::Project> ProjectManager::NewProject()
{
    return std::make_shared<Model::Project>();
}

std::shared_ptr<Model::Project> ProjectManager::LoadFromFile(std::string filename) {

    std::ifstream ifs(filename.c_str());

    nlohmann::json jf = nlohmann::json::parse(ifs);

    auto project = jf.get<Model::Project>();

    return std::make_shared<Model::Project>(project);
}

void ProjectManager::SaveToFile(std::shared_ptr<Model::Project> project, std::string filename)
{
    nlohmann::json jf = *project.get();

    std::ofstream file(filename.c_str());
    file << std::setw(4) << jf << std::endl;
}
