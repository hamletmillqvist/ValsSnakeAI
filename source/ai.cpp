#include <ai.h>

void AssembleBrain(AI* ai)
{
	std::vector<String> splitGenome = splitString(ai->GENOME, ' ');
}

// 3 motor functions (Turn right, turn left, or stay on course)
void ProcessAI(AI* ai, Game* game)
{
	float wantsLeft = 0, wantsRight = 0, wantsNone = 0;

	// Update all sensors

	// Dirty all neurons

	// Read motor neurons
}
