//
// Created by vruser on 06/07/2022.
//

#include "imgui.h"

#include "widgets/MapWindow.h"

int n = 0;

MapWindow::MapWindow(SDL_Renderer *renderer, std::shared_ptr<Model::Map> map)
{
    this->map = map;
    this->renderer = renderer;

    int w = 512;
    int h = 256;

    this->surface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);

    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);

}

void MapWindow::Draw()
{
    ImGui::Begin("Map Window");

    n ++;

    for(int y=0;y<this->surface->h;y++){
        for(int x=0;x<this->surface->w;x++){

            Uint32 * const target_pixel = (Uint32 *) ((Uint8 *) this->surface->pixels
                                                      + y * this->surface->pitch
                                                      + x * this->surface->format->BytesPerPixel);
            *target_pixel = 0x000000 | (n & 0xFF) | (((x+(n>>1)) * (y+(n>>2))) & 0xFF) << 16;
        }
    }

    SDL_Rect rect = {0,0,this->surface->w, this->surface->h};

    SDL_UpdateTexture(this->texture, &rect, this->surface->pixels, this->surface->pitch);


    ImGui::Image(this->texture, ImVec2(this->surface->w*2, this->surface->h*2));

    ImGui::End();
}
