#include "shape.h"
#include <cstdlib>

Shape::Shape(ShapeType type)
{
    setShape(type);
}

Shape Shape::randomShape()
{
    return Shape(static_cast<ShapeType>(rand() % 7 + 1));
}

void Shape::rotate()
{
    for (auto& block : blocks_)
    {
        int temp = block[0];
        block[0] = -block[1];
        block[1] = temp;
    }
}

void Shape::setShape(ShapeType type)
{
    type_ = type;
    blocks_.clear();
    switch (type)
    {
        case ShapeType::I:
        {
            blocks_ = {{0, 0},
                       {0, 1},
                       {0, -1},
                       {0, -2}};
            break;
        }

        case ShapeType::J:
        {
            blocks_ = {{0,  0},
                       {0,  -1},
                       {-1, -1},
                       {0,  1}};
            break;
        }

        case ShapeType::L:
        {
            blocks_ = {{0, 0},
                       {0, -1},
                       {1, -1},
                       {0, 1}};
            break;
        }

        case ShapeType::O:
        {
            blocks_ = {{0, 0},
                       {0, 1},
                       {1, 0},
                       {1, 1}};
            break;
        }

        case ShapeType::S:
        {
            blocks_ = {{0, 0},
                       {0, 1},
                       {1, 0},
                       {1, -1}};
            break;
        }

        case ShapeType::T:
        {
            blocks_ = {{0,  0},
                       {-1, 0},
                       {1,  0},
                       {0,  1}};
            break;
        }

        case ShapeType::Z:
        {
            blocks_ = {{0, 0},
                       {0, -1},
                       {1, 0},
                       {1, 1}};
            break;
        }

        default:
        {
            break;
        }
    }
}