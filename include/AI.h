#pragma once
#include <string>
#include <vector>

#include <stringdefs.h>

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
	FromSensor,
	FromNeuron
};

struct Sensor {
	float Strength = 0;
};

struct Neuron {
	float Strength = 0;
	std::vector<Connection> Connections;
};

struct Connection {
	ConnectionType type;
	float Weight = 1;

	union {
		Sensor* p_sensor;
		Neuron* p_neuron;
	} Source;

	Neuron* p_Target;
};

struct AI {
	std::vector<Neuron> Neurons;
	std::vector<Sensor> Sensors;
	std::vector<Neuron> Motors;
	//std::vector<Connection> Connections; // Could be redundant since neurons already have connections stored.
	int ConnectionCount = 0;
	String GENOME = L"";
};

void AssembleBrain(AI* ai);
void ProcessAI(AI* ai, Game* game);
const std::vector<Connection> GetConnectionList(AI* ai);
