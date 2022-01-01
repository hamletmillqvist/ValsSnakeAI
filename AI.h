#pragma once
#include <string>
#include <vector>

#include "StringDefs.h"

// GENOME DEFINITION
// A genome is an array of genes.
// A gene has a set of characters designated as: TSSTTPW
// -> T  [Type]		(Sensory / Calculating / Motor) 
// -> SS [Source]   (00 - FF)
// -> TT [Target]   (00 - FF)
// -> P  [Positive] (T/F)
// -> W  [Weight]   (0 - F)
//
// An example genome can be: TC01FTA
// This would be read as following:
// Reading from sensory organ C0 is read by neuron 1F with a positive reading mutliplied by a strenght of A (66%).

struct Game;
struct Connection;

enum ConnectionType {
	Undefined = -1,
	SensorToNeuron,
	NeuronToNeuron
};

struct Sensor {
	float strength = 0;
};

struct Neuron {
	float strength = 0;
	std::vector<Connection> connections;
};

struct Connection {
	ConnectionType type;
	float weight = 1;
};

struct Brain {
	std::vector<Neuron> neurons;
};

struct AI {
	Brain brain;
	std::vector<Sensor> sensors;
	std::vector<Neuron> motors;
	std::vector<Connection> connections;
	String GENOME = L"";
};

void AssembleBrain(AI* ai);
void ProcessAI(AI* ai, Game* game);