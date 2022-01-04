#pragma once
#include <cstdint>

struct AI;

struct GridPos {
    static const uint32_t EMPTY = 0;
    static const uint32_t SNAKE = 1;
    static const uint32_t APPLE = 2;
    unsigned int value = EMPTY;
};

struct Coord {
    int32_t X = 0;
    int32_t Y = 0;

    static Coord Empty() { return Coord(); }

    Coord operator / (int32_t divider)
    {
        if (divider == 0) {
            return Coord::Empty();
        }

        return { X / divider, Y / divider };
    }

    Coord operator + (Coord other)
    {
        return { X + other.X, Y + other.Y };
    }
};

struct Game {
    Coord* p_snake = nullptr;
    Coord applePos;
    Coord lookingDirection;
    Coord size;
    uint32_t lenght = 0;
    uint32_t score = 0;
    bool running = false;
    GridPos* p_grid = nullptr;
};

Game* SetupGame(Coord size);
void UpdateGrid(Game* game);
void DrawGame(Game* game);
void PrintGameInfo(Game* game);
void StartGame(Game* game, AI* brain);
