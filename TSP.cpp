#include "TSP.hpp"

/**
 * Displays the edges and total distance of the tour.
 * Each edge is printed in the format: "EDGE start_id -> end_id | WEIGHT: weight".
 */
void TSP::Tour::display() const {
  for (size_t i = 1; i < path.size(); i++) {
    std::cout << "EDGE " << path[i-1].id << " -> " << path[i].id << " | WEIGHT : " << weights[i] << std::endl;
  }
  std::cout << "TOTAL DISTANCE: " << total_distance << std::endl;
}

/**
 * Reads a .tsp file and constructs a list of cities as nodes.
 * The file should have a section labeled "NODE_COORD_SECTION" followed by lines with the format: ID x-coordinate y-coordinate.
 * 
 * @param filename The path to the TSP file.
 * @return A list of `Node` objects representing cities and their coordinates.
 * @throws std::runtime_error If the file cannot be read or parsed.
 * 
 * @pre The file specified by `filename` exists and follows the TSP format.
 */
std::list<Node> TSP::constructCities(const std::string& filename) {
  // Read past metadata
  std::ifstream fin(filename);
  if (fin.fail()) {
    std::cerr << "ERROR: Could not read file: " << filename << std::endl;
    throw std::runtime_error("Failed to read file. Terminating.");
  }

  std::string line;
  do { std::getline(fin, line); }
  while (line.find("NODE_COORD_SECTION"));

  // Read data from file into Node list "cities"
  std::list<Node> cities;
  size_t ID;
  double x, y;
  while (!fin.eof()){
    if (!(fin >> ID >> x >> y)) break;
    cities.push_back(Node(ID, x, y));
  }
  return cities;
}

TSP::Tour TSP::nearestNeighbor(std::list<Node> cities, const size_t& start_id){
  Tour tour;
  if(cities.empty()){
    return tour;
  }

  // all citiesa are not visited
  std::list<Node> notVisitedCities = cities;
  
  // find the start city and start the tour
  for(Node city : notVisitedCities){
    if(city.id == start_id){
      tour.path.push_back(city);
      tour.weights.push_back(0);
      tour.total_distance = 0;
      notVisitedCities.remove(city);
      break;
    }
  }

  // // find the nearest city and add it to the tour
  // while(!notVisitedCities.empty()){
  //   Node currentCity = tour.path.back();
  //   Node nearestCity = notVisitedCities.front();
  //   size_t minDistance = currentCity.distance(nearestCity);
  //   for(auto city : notVisitedCities){
  //     if(currentCity.distance(city) < minDistance){
  //       minDistance = currentCity.distance(city);
  //       nearestCity = city;
  //     }
  //   }
  //   tour.path.push_back(nearestCity);
  //   tour.weights.push_back(minDistance);
  //   tour.total_distance += minDistance;
  //   notVisitedCities.remove(nearestCity);
  // }
  // tour.path.push_back(tour.path.front());
  // tour.weights.push_back(tour.path.back().distance(tour.path.front()));
  // tour.total_distance += tour.path.back().distance(tour.path.front());


  // // while(!notVisitedCities.empty()){
  // //   Node currentCity = tour.path.back();
  // //   Node nearestCity = getNearestCity(notVisitedCities, currentCity);
  // //   tour.path.push_back(nearestCity);
  // //   tour.weights.push_back(currentCity.distance(nearestCity));
  // //   tour.total_distance += currentCity.distance(nearestCity);
  // //   notVisitedCities.remove(nearestCity);
  // // }
  // // tour.weights.push_back(tour.path.back().distance(tour.path.front()));
  // // tour.total_distance += tour.path.back().distance(tour.path.front());

  // return tour;
  
}