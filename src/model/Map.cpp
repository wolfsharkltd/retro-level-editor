//
// Created by vruser on 03/07/2022.
//

#include "model/Map.h"

namespace Model {

    void Map::Test() {

    }

    int Map::getWidth() const {
        return m_width;
    }

    void Map::setWidth(int mWidth) {
        m_width = mWidth;
    }

    int Map::getHeight() const {
        return m_height;
    }

    void Map::setHeight(int mHeight) {
        m_height = mHeight;
    }
}