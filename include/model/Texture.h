//
// Created by vruser on 06/07/2022.
//

#ifndef EDITOR_TEXTURE_H
#define EDITOR_TEXTURE_H
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

#include <SDL.h>

namespace Model {

    struct Texture {
    public:
        std::string name;
        std::string filename;

    public:
        //std::vector<uint32_t> pixels;

        SDL_Surface* surface;
        SDL_Texture* texture;

        //int width;
        //int height;
    };

    void to_json(nlohmann::json& j, const Texture& p);
    void from_json(const nlohmann::json& j, Texture& p);
}

#endif //EDITOR_TEXTURE_H
