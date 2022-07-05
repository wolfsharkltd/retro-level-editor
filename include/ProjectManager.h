//
// Created by vruser on 03/07/2022.
//

#ifndef EDITOR_PROJECTMANAGER_H
#define EDITOR_PROJECTMANAGER_H

#include <memory>
#include <string>

#include "model/Project.h"

class ProjectManager {
public:

    static std::shared_ptr<Model::Project> NewProject();

    static std::shared_ptr<Model::Project> LoadFromFile(std::string filename);

    static void SaveToFile(std::shared_ptr<Model::Project> project, std::string filename);

};


#endif //EDITOR_PROJECTMANAGER_H
