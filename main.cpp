#include "TSP.hpp"
#include "Time.hpp"
#include <iostream>

int main() {
  std::string filename = "test_data/mu1979.tsp";
  std::list<Node> cities = TSP::constructCities(filename);
  auto result = Time::timeAndExecute<TSP::Tour, std::list<Node>, size_t>(TSP::nearestNeighbor, cities, 1022);
  // result.summarize();

  TSP::Tour tour;
    Node city1(1, 0, 0);  // City 1
    Node city2(2, 1, 1);  // City 2
    Node city3(3, 4, 4);  // City 3

    tour.path.push_back(city1);
    tour.weights.push_back(0);  // No distance for the first city
    tour.path.push_back(city2);
    tour.weights.push_back(1);  // Some mock weight
    tour.path.push_back(city3);
    tour.weights.push_back(3);  // Another mock weight
    tour.total_distance = 4;   // Mock total distance

  

    tour.display();

  return 0;
}