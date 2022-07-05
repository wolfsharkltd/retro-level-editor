//
// Created by vruser on 03/07/2022.
//

#ifndef EDITOR_MAP_H
#define EDITOR_MAP_H
#include "nlohmann/json.hpp"

namespace Model {

    class Map {
    protected:
        int m_width;
        int m_height;

    public:
        int getWidth() const;

        void setWidth(int mWidth);

        int getHeight() const;

        void setHeight(int mHeight);

    public:
        void Test();
    };
}


#endif //EDITOR_MAP_H
