#include <ai.h>
#include <exception>
#include <sstream>

void AssembleBrain(AI* p_ai)
{
	std::vector<String> splitGenome = splitString(p_ai->GENOME, ' ');

	for (int i = 0; i < splitGenome.size(); i++) {
		String& geneInfo = splitGenome.at(i);

		char typeChar = geneInfo[0];
		int sourceId = std::stoi(geneInfo.substr(1, 2));
		int targetId = std::stoi(geneInfo.substr(3, 2));
		int one_or_minus_one = (geneInfo[5] == 'T') ? 1 : -1;

		Connection connection;
		connection.Weight = hexToInt(geneInfo[6]) * 1.0f / 16 * one_or_minus_one;

		if (typeChar == 'S') {
			connection.type = ConnectionType::FromSensor;
			connection.Source.p_sensor = &(p_ai->Sensors.at(sourceId));
			connection.p_Target = &(p_ai->Neurons.at(targetId));
			connection.p_Target->Connections.push_back(connection);
		} else {
			connection.type = ConnectionType::FromNeuron;
			connection.Source.p_neuron = &(p_ai->Neurons.at(sourceId));

			// If motor gene: grab neuron at targetId index in motors list.
			// else grab neuron at targetId index in neurons list.
			std::vector<Neuron>& targetList = (typeChar == 'M' ? p_ai->Motors : p_ai->Neurons);
			connection.p_Target = &(targetList.at(targetId));
			connection.p_Target->Connections.push_back(connection);
		}

		p_ai->ConnectionCount++;
	}

}

// 3 motor functions (Turn right, turn left, or stay on course)
void ProcessAI(AI* p_ai, Game* game)
{
	float wantsLeft = 0, wantsRight = 0, wantsNone = 0;

	// Update all sensors

	// Dirty all neurons

	// Read motor neurons
}

const std::vector<Connection> GetConnectionList(AI* ai)
{
	std::vector<Connection> connections(ai->ConnectionCount);

	for (auto&& motor : ai->Motors) {
		connections.insert(connections.end(), motor.Connections.begin(), motor.Connections.end());
	}
	for (auto&& neuron : ai->Neurons) {
		connections.insert(connections.end(), neuron.Connections.begin(), neuron.Connections.end());
	}

	return connections;
}
