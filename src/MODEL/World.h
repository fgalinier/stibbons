
#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

#include "Zone.h"
#include "Turtle.h"

using namespace std;
/**
  * class World
  * 
  */

class World
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  World ();

  /**
   * Empty Destructor
   */
  virtual ~World ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  


  vector<Zone*> zonesVector;

  vector<Turtle*> turtlesVector;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:


  /**
   * Add a Zones object to the m_zonesVector List
   */
  void addZones (Zone add_object);

  /**
   * Remove a Zones object from m_zonesVector List
   */
  void removeZones (Zone remove_object);

  /**
   * Get the list of Zones objects held by m_zonesVector
   * @return vector<Zone> list of Zones objects held by m_zonesVector
   */
  vector<Zone> getZonesList ();

  /**
   * Add a Turtles object to the m_turtlesVector List
   */
  void addTurtles (Turtle add_object);

  /**
   * Remove a Turtles object from m_turtlesVector List
   */
  void removeTurtles (Turtle remove_object);

  /**
   * Get the list of Turtles objects held by m_turtlesVector
   * @return vector<Turtle> list of Turtles objects held by m_turtlesVector
   */
  vector<Turtle> getTurtlesList ();


};

#endif // WORLD_H
