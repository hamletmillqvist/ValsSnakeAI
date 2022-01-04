#include <windows.h>
#include <string>
#include <iostream>

#include <virtual_keycodes.h>
#include <game.h>
#include <stringdefs.h>
#include <ai.h>

DWORD EnableVirtualTerminal(HANDLE handleOut)
{

    DWORD dwMode = 0;
    if (!GetConsoleMode(handleOut, &dwMode)) {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(handleOut, dwMode)) {
        return GetLastError();
    }

    return ERROR_SUCCESS;
}

int main(int argc, char** argv)
{
    // Set output mode to handle virtual terminal sequences
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handleOut == INVALID_HANDLE_VALUE) {
        return GetLastError();
    }

    DWORD returnCode = EnableVirtualTerminal(handleOut);
    if (returnCode != ERROR_SUCCESS) { // If an error occured
        return returnCode;
    }

    AI ai;
    ai.Sensors.push_back({}); // 0: Map width
    ai.Sensors.push_back({}); // 1: Map height
    ai.Sensors.push_back({}); // 2: Map current direction
    ai.Sensors.push_back({}); // 3: Eye Left
    ai.Sensors.push_back({}); // 4: Eye Right
    ai.Sensors.push_back({}); // 5: Eye Up
    ai.Sensors.push_back({}); // 6: Eye Down
    ai.Sensors.push_back({}); // 7: Snake lenght
    ai.Sensors.push_back({}); // 8: Snake Head X
    ai.Sensors.push_back({}); // 9: Snake Head Y
    ai.Sensors.push_back({}); // A: Apple X
    ai.Sensors.push_back({}); // B: Apple Y

    int32_t brainSize = 5;
    for (int32_t i = 0; i < brainSize; i++) {
        ai.Neurons.push_back({}); // Empty neurons
    }

    ai.Motors.push_back({}); // 0: Move Left
    ai.Motors.push_back({}); // 1: Move right
    ai.Motors.push_back({}); // 2: Move forward

    ai.GENOME = L"S0500TF M0001TF C0001T7"; // Initial GENOME

    AssembleBrain(&ai);

    const int gamesToRun = 5;
    Coord size = { 20, 20 };

    for (int32_t i = 0; i < gamesToRun; i++) {
        Game* p_game = SetupGame(size);
        StartGame(p_game, &ai);

        // Mutate dna
    }

    return 0;
}
