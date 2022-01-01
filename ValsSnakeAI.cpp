#include <windows.h>
#include <string>
#include <iostream>

#include "VirtualKeycodes.h"
#include "Game.h"
#include "StringDefs.h"
#include "AI.h"

DWORD EnableVirtualTerminal(HANDLE handleOut) {

    DWORD dwMode = 0;
    if (!GetConsoleMode(handleOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(handleOut, dwMode))
    {
        return GetLastError();
    }

    return ERROR_SUCCESS;
}

int main(int argc, char** argv) {
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
    ai.sensors.push_back({}); // 0: Map width
    ai.sensors.push_back({}); // 1: Map height
    ai.sensors.push_back({}); // 2: Map current direction
    ai.sensors.push_back({}); // 3: Eye Left
    ai.sensors.push_back({}); // 4: Eye Right
    ai.sensors.push_back({}); // 5: Eye Up
    ai.sensors.push_back({}); // 6: Eye Down
    ai.sensors.push_back({}); // 7: Snake lenght
    ai.sensors.push_back({}); // 8: Snake Head X
    ai.sensors.push_back({}); // 9: Snake Head Y
    ai.sensors.push_back({}); // A: Apple X
    ai.sensors.push_back({}); // B: Apple Y

    int32_t brainSize = 5;
    for (int32_t i = 0; i < brainSize; i++) {
        ai.brain.neurons.push_back({}); // Empty neurons
    }

    ai.motors.push_back({}); // 0: Move Left
    ai.motors.push_back({}); // 1: Move right
    ai.motors.push_back({}); // 2: Move forward

    ai.GENOME = L"S0500TF M0001TF C0001T7"; // Initial GENOME

    AssembleBrain(&ai);

    const int gamesToRun = 5;
    Coord size = { 30, 30 };

    for (int32_t i = 0; i < gamesToRun; i++) {
        Game* p_game = SetupGame(size);
        StartGame(p_game, &ai);

        // Mutate dna
        
    }

    return 0;
}