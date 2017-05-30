/**
* \class GraphicFab
* \ingroup viewmodels
* \details class controlling cameras
* \author Marek Pelka
*/

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include "../models/Building.h"
#include "../models/Camera.h"
#include "../models/SqlConnector.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <list>
#include <memory>
#include <thread>

class CameraController {
public:
    ///singleton getInstance method
    static CameraController* getInstance();
    /**add camera object to cameras list
    * \param camera
    */
    void addCamera(Camera camera);
    /**add building object to buildings list
    * \param building
    */
    void addBuilding(Building building);
    /**delete camera object from cameras list
    * \param camera
    */
    void deleteCamera(Camera camera);
    /**delete building object from buildings list
    * \param building
    */
    void deleteBuilding(Building building);
    ///clear controller
    void clearController();
    /// update observations for all cameras 
    void updateObservations();
    ///check if between points there is a building
    bool checkIfBuilding(Position p1, Position p2);
    ///check if line between p1 and p2 intersects with line between q1 and q2
    bool LineIntersectsLine(Position p1, Position p2, Position q1, Position q2);
    ///return all cameras objects
    std::list<Camera> getCameras();
    ///return all buildings objects
    std::list<Building> getBuildings();
    /**write cameras observations to file
    * \param filename
    */
    void writeToFile(std::string name);
    ///write cameras observations to database cam_observations.db
    void writeToDatabase();
    ///flag to specify if write to file or database
    bool insertType = false;

private:
    ///default constructor
    CameraController();
    ///singleton instance pointer
    static CameraController* instance;
    ///all cameras objects
    std::list<Camera> cameras;
    ///all buildings objects
    std::list<Building> buildings;
    ///file object to write to
    std::ofstream file;
};
#endif