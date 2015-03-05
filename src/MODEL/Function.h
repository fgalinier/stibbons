
#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>

using namespace std;


/**
  * class Function
  * 
  */

class Function
{
public:

  // Constructors/Destructors
  //  

  Function (string n, int arg, string c);
  /**
   * Empty Constructor
   */
  Function ();

  /**
   * Empty Destructor
   */
  virtual ~Function ();


private:

  string name;
  double nbarg;
  string code;
  

public:

  /**
   * Set the value of name
   * @param new_var the new value of name
   */
  void setName (string new_var)   {
      name = new_var;
  }

  /**
   * Get the value of name
   * @return the value of name
   */
  string getName ()   {
    return name;
  }

  /**
   * Set the value of nbarg
   * @param new_var the new value of nbarg
   */
  void setNbarg (double new_var)   {
      nbarg = new_var;
  }

  /**
   * Get the value of nbarg
   * @return the value of nbarg
   */
  double getNbarg ()   {
    return nbarg;
  }

  /**
   * Set the value of code
   * @param new_var the new value of code
   */
  void setCode (string new_var)   {
      code = new_var;
  }

  /**
   * Get the value of code
   * @return the value of code
   */
  string getCode ()   {
    return code;
  }
private:
  void initAttributes () ;

};

#endif // FUNCTION_H
