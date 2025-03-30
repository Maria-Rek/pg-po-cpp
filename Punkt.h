#pragma once

struct Punkt {
    int x;
    int y;

    Punkt(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Punkt& inny) const {
        return x == inny.x && y == inny.y;
    }

    bool operator!=(const Punkt& inny) const {
        return !(*this == inny);
    }
};
