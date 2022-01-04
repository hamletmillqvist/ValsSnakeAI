#include <random>
#include <time.h>
#include <iostream>

#include <game.h>
#include <virtual_keycodes.h>
#include <stringdefs.h>
#include <ai.h>

using namespace VIRTUAL_KEYCODES;

void Print(String text, String modifiers)
{

    text = CSI + modifiers + text;

    wprintf(text.c_str());
}

void Print(String text)
{
    wprintf(text.c_str());
}

void Command(String modifiers)
{
    Print(L"", modifiers);
}

void ResetConsoleModifiers()
{
    Command(SGR::DEFAULT + SGR::END);
}

void ResetGrid(Game* game)
{
    int len = game->lenght;
    for (uint32_t i = 0; i < game->lenght; i++)
        game->p_grid[i].value = 0;
}

void SpawnApple(Game* game)
{

    Coord newPos;

    do {
        newPos = {
            rand() % game->size.X,
            rand() % game->size.Y };
    } while (game->p_grid[newPos.X + newPos.Y * game->size.X].value != GridPos::EMPTY);

    game->applePos = newPos;
}

Game* SetupGame(Coord size)
{
    srand((unsigned int)time(NULL));

    Game* game = new Game();
    game->size = size;
    game->lenght = size.X * size.Y;
    game->lookingDirection = { 0, -1 }; // UP
    game->applePos = { 15, 10 };

    // Create snake
    game->p_snake = new Coord[game->lenght];
    game->p_snake[0] = game->size / 2;
    for (uint32_t i = 1; i < game->lenght; i++) {
        game->p_snake[i] = { 0, 0 };
    }

    // Create grid
    game->p_grid = new GridPos[game->lenght];
    ResetGrid(game);

    return game;
}

void UpdateGrid(Game* game)
{
    ResetGrid(game);

    // Store reference to grid & snake
    GridPos* p_grid = game->p_grid;
    Coord* p_snake = game->p_snake;

    // Write apple to grid
    Coord pos = game->applePos;
    p_grid[pos.X + pos.Y * game->size.X].value = GridPos::APPLE;

    // Write snake to grid
    for (uint32_t i = 0; i < game->score + 1; i++) {
        pos = p_snake[i];
        p_grid[pos.X + pos.Y * game->size.X].value = GridPos::SNAKE;
    }
}

void DrawGame(Game* game)
{
    // Store reference to grid
    GridPos* p_grid = game->p_grid;

    Print(L" ");
    for (int32_t x = 1; x <= game->size.X; x++) {
        Print(L"__");
    }
    Print(L"\r\n");

    for (int32_t y = 0; y < game->size.Y; y++) {
        Print(L"|");
        for (int32_t x = 0; x < game->size.X; x++) {
            String modifier;

            switch (p_grid[x + y * game->size.X].value) {
            case GridPos::EMPTY:
                modifier = SGR::BACKGROUND::BLACK;
                break;
            case GridPos::APPLE:
                modifier = SGR::BACKGROUND::RED;
                break;
            case GridPos::SNAKE:
                modifier = SGR::BACKGROUND::BRIGHT_GREEN;
                break;
            }

            modifier += SGR::END;

            Print(L"  ", modifier);
        }
        ResetConsoleModifiers();
        Print(L"|\r\n");
    }

    Print(L" ");
    for (int32_t x = 1; x <= game->size.X; x++) {
        Print(L"--");
    }
    Print(L"\r\n");
}

void PrintGameInfo(Game* game, AI* ai)
{

    String str =
        L"---------------- Game ----------------\r\nSize: " +
        toStr(game->size.X) +
        L", " +
        toStr(game->size.Y) +
        L"\r\nScore: " +
        toStr(game->score) +
        L"\r\nRunning: ";
    Print(str);

    if (game->running) {
        Print(L"TRUE", SGR::FOREGROUND::BRIGHT_GREEN + SGR::END);
    } else {
        Print(L"FALSE", SGR::FOREGROUND::BRIGHT_RED + SGR::END);
    }
    ResetConsoleModifiers();

    str =
        L"\r\n\r\nApple Pos: " +
        toStr(game->applePos.X) +
        L"," +
        toStr(game->applePos.Y) +
        L"\r\nSnake Head: " +
        toStr(game->p_snake[0].X) +
        L"," +
        toStr(game->p_snake[0].Y) +
        L"\r\n----------------- AI -----------------\r\nDNA (Genome): " +
        ai->GENOME +
        L"\r\n";
    Print(str);
}

void MoveSnake(Game* game)
{
    // Store reference of snake
    Coord* p_snake = game->p_snake;
    Coord targetCoord = p_snake[0] + game->lookingDirection;

    // Check for collision.
    // 1. Out of bounds
    if (targetCoord.X < 0 || targetCoord.X >= game->size.X ||
        targetCoord.Y < 0 || targetCoord.Y >= game->size.Y) {
        game->running = false;
    } else {
        GridPos targetPos = game->p_grid[targetCoord.X + targetCoord.Y * game->size.X];

        // 2. Moved into snake body
        if (targetPos.value == GridPos::SNAKE) {
            game->running = false;
        } else {
            // 3. Apple collected
            bool gotFood = false;
            Coord tail;
            if (targetPos.value == GridPos::APPLE) {
                gotFood = true;
                SpawnApple(game);

                // Store copy of tail
                tail = p_snake[game->score];
            }

            for (uint32_t i = 0; i < game->score + 1; i++) {
                Coord temp = p_snake[i];
                p_snake[i] = targetCoord;
                targetCoord = temp;
            }

            // Paste tail where previous tail was
            if (gotFood) {
                game->score++;
                p_snake[game->score] = tail;
            }
        }
    }
}

void StartGame(Game* game, AI* ai)
{
    game->running = true;
    Command(CURSOR::SAVE_POS);
    Command(CURSOR::VISIBILITY_OFF);
    while (game->running) {
        UpdateGrid(game);

        Command(CURSOR::LOAD_POS);
        DrawGame(game);

        ProcessAI(ai, game);
        MoveSnake(game);

        PrintGameInfo(game, ai);
    }

    // Game end
    Command(CURSOR::VISIBILITY_ON);

    // Wait for keypress
    std::cout << "Press any key to continue...";
    int _ = std::getchar();

    Command(VIRTUAL_KEYCODES::SCREEN::CLEAR_SCREEN);
    Command(CURSOR::LOAD_POS);
}
