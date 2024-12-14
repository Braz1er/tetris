#pragma once

#include <vector>
#include <array>

enum class ShapeType { None, I, J, L, O, S, T, Z };

class Shape {
public:
    Shape(ShapeType type = ShapeType::None);
    static Shape randomShape();
    void rotate();
    const std::vector<std::array<int, 2>>& blocks() const { return blocks_; }
    const ShapeType& type() const { return type_; }

private:
    ShapeType type_;
    std::vector<std::array<int, 2>> blocks_;  // Массив блоков фигуры
    void setShape(ShapeType type);
};