//
// Created by vruser on 06/07/2022.
//

#include "imgui.h"

#include "widgets/MapWindow.h"

int n = 0;

class Node
{
public:
    ImVec2 position;
    ImVec2 size;

    ImVec2 handles[9];
};

Node r1 = {ImVec2(10,10), ImVec2(100,100)};
Node r2 = {ImVec2(100,100), ImVec2(100,100)};
Node r3 = {ImVec2(200,200), ImVec2(100,100)};


//ImVec2 r_start = {10,10};
//ImVec2 r_size = {100,100};
//
//ImVec2 r2_start = {80,80};
//ImVec2 r2_size = {200,100};
//
//ImVec2 r3_start = {120,120};
//ImVec2 r3_size = {200,100};


MapWindow::MapWindow(SDL_Renderer *renderer, std::shared_ptr<Model::Map> map)
{
    this->map = map;
    this->renderer = renderer;

    int w = 512;
    int h = 256;

    this->surface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,0);

    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);

}

bool isDragging = false;
ImVec2 dragOffset;
ImVec2 *handlePosition;

void DragBox(const ImVec2& viewport, ImVec2& min, ImVec2& size, ImVec2& handle)
{

    ImVec2 mouse = ImGui::GetMousePos();

    ImVec2 draw_min = ImVec2(viewport.x + min.x, viewport.y + min.y);
    ImVec2 draw_max = ImVec2(draw_min.x + size.x, draw_min.y + size.y);
    ImVec2 draw_handle = ImVec2(handle.x + viewport.x, handle.y + viewport.y);

    if(ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        if (ImGui::IsMouseHoveringRect(draw_min, draw_max)) {
            if (!isDragging) {
                isDragging = true;
                handlePosition = &handle;

                dragOffset = ImVec2(mouse.x - draw_handle.x, mouse.y - draw_handle.y);
            }
        }
    } else {
        if (isDragging) {
            isDragging = false;
            handlePosition = NULL;
            dragOffset = ImVec2(0, 0);
        }
    }

    if(handlePosition == &handle)
    {
        if(isDragging) {
            handlePosition->x = mouse.x - dragOffset.x - viewport.x;
            handlePosition->y = mouse.y - dragOffset.y - viewport.y;
        }
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    const ImU32 col32 = ImColor(255,255,255);
    const float th = 1.0f;

    draw_list->AddRect(draw_min, draw_max,
                       col32, 2.0f, ImDrawCornerFlags_All, th);

}

void DrawHandle(const ImVec2& viewport, ImVec2& handle)
{
    const float sz = 8;
    const float hz = sz/2;

    ImVec2 min = ImVec2(handle.x-hz, handle.y-hz);
    ImVec2 max = ImVec2(sz, sz);

    DragBox(viewport, min, max, handle);

    // Snapping?
//    handle.x = (int)(handle.x / 16) * 16;
//    handle.y = (int)(handle.y / 16) * 16;
}


void BoxHandles(const ImVec2 viewport, Node &node)
{
    const float padding = 6;

    ImVec2 &start = node.position;
    ImVec2 &size = node.size;

    float dx;
    float dy;

    ImVec2& topLeft = node.handles[0];
    ImVec2& top = node.handles[1];
    ImVec2& topRight = node.handles[2];
    ImVec2& left = node.handles[3];
    ImVec2& right = node.handles[4];
    ImVec2& bottomLeft = node.handles[5];
    ImVec2& bottom = node.handles[6];
    ImVec2& bottomRight = node.handles[7];

    topLeft = ImVec2(start.x - padding, start.y - padding);
    DrawHandle(viewport, topLeft);
    dx = start.x - (topLeft.x + padding);
    dy = start.y - (topLeft.y + padding);
    start.x = topLeft.x + padding;
    start.y = topLeft.y + padding;
    size.x += dx;
    size.y += dy;

    top = ImVec2(start.x + size.x * 0.5, start.y - padding);
    DrawHandle(viewport, top);
    dy = start.y - (top.y + padding);
    start.y = top.y + padding;
    size.y += dy;

    bottomLeft = ImVec2(start.x - padding, start.y + size.y + padding);
    DrawHandle(viewport, bottomLeft);
    dx = start.x - (bottomLeft.x + padding);
    start.x = bottomLeft.x + padding;
    size.x += dx;
    size.y = bottomLeft.y - start.y - padding;

    left = ImVec2(start.x - padding, start.y + size.y*0.5);
    DrawHandle(viewport, left);
    dx = start.x - (left.x + padding);
    start.x = left.x + padding;
    size.x += dx;

    topRight = ImVec2(start.x + size.x + padding, start.y - padding);
    DrawHandle(viewport, topRight);
    dy = start.y - (topRight.y + padding);
    size.x = topRight.x - start.x - padding;
    size.y += dy;
    start.y = topRight.y + padding;

    right = ImVec2(start.x + size.x + padding, start.y + size.y*0.5);
    DrawHandle(viewport, right);
    size.x = right.x - start.x - padding;

    bottomRight = ImVec2(start.x + size.x + padding, start.y + size.y + padding);
    DrawHandle(viewport, bottomRight);
    size.x = bottomRight.x - start.x - padding;
    size.y = bottomRight.y - start.y - padding;

    bottom = ImVec2(start.x + size.x*0.5f, start.y + size.y + padding);
    DrawHandle(viewport, bottom);
    size.y = bottom.y - start.y - padding;


    DragBox(viewport, start, size, start);
}

void MapWindow::Draw()
{
    ImGui::Begin("Map Window");

    const ImVec2 p = ImGui::GetCursorScreenPos();

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


    //ImGui::Image(this->texture, ImVec2(this->surface->w*2, this->surface->h*2));
    ImGui::SetCursorPos(p);


    BoxHandles(p, r1);
    BoxHandles(p, r2);
    BoxHandles(p, r3);

    ImGui::End();
}
