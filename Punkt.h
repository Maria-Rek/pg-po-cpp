#pragma once

class Punkt {
private:
    int x;
    int y;

public:
    Punkt(int x = 0, int y = 0) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }

    void setX(int val) { x = val; }
    void setY(int val) { y = val; }

    bool operator==(const Punkt& inny) const {
        return x == inny.x && y == inny.y;
    }

    bool operator!=(const Punkt& inny) const {
        return !(*this == inny);
    }
};
