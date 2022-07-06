//
// Created by vruser on 06/07/2022.
//

#ifndef EDITOR_MAPWINDOW_H
#define EDITOR_MAPWINDOW_H

#include <memory>
#include "SDL.h"

#include "model/Map.h"

class MapWindow {
public:
    std::shared_ptr<Model::Map> map;


    SDL_Renderer *renderer;

    SDL_Surface *surface;
    SDL_Texture *texture;

public:
    MapWindow(SDL_Renderer *renderer, std::shared_ptr<Model::Map> map);

    void Draw();

};


#endif //EDITOR_MAPWINDOW_H
