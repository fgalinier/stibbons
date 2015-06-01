/**
 * \file value.h
 * \brief An abstract class who represent a values of a given type
 * \author Julia Bassoumi, Adrien Plazas
 * \version 1.1
 * \date 08/04/2015
 */

#pragma once

#include <memory>
#include <string>

namespace stibbons {

/**
 * \class Type
 *
 * \brief The available value types.
 *
 * \author Julia Bassoumi
 */
enum class Type {
	NIL,
	NUMBER,
	BOOLEAN,
	STRING,
	COLOR,
	TABLE,
	FUNCTION,
	AGENT,
	TURTLE,
	ZONE,
	WORLD,
	TYPE
};

/**
 * Return a string corresponding to the given type.
 * \param type the type
 * \return a string corresponding to the type
 */
std::string toString(Type& type);

/**
 * Return a string corresponding to the given type (with r-value reference).
 * \param type the type
 * \return a string corresponding to the type
 */
std::string toString(Type&& type);

class Agent;
class Boolean;
class Breed;
class Color;
class Function;
class Nil;
class Number;
class String;
class Table;
class Turtle;
class TypeValue;
class Value;
class World;
class Zone;

typedef std::shared_ptr<Agent> AgentPtr;
typedef std::shared_ptr<Boolean> BooleanPtr;
typedef std::shared_ptr<Breed> BreedPtr;
typedef std::shared_ptr<Color> ColorPtr;
typedef std::shared_ptr<Function> FunctionPtr;
typedef std::shared_ptr<Nil> NilPtr;
typedef std::shared_ptr<Number> NumberPtr;
typedef std::shared_ptr<String> StringPtr;
typedef std::shared_ptr<Table> TablePtr;
typedef std::shared_ptr<Turtle> TurtlePtr;
typedef std::shared_ptr<TypeValue> TypeValuePtr;
typedef std::shared_ptr<Value> ValuePtr;
typedef std::shared_ptr<World> WorldPtr;
typedef std::shared_ptr<Zone> ZonePtr;

}

/*
 * Editor modelines  -  http://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: t
 * truncate-lines: 1
 * End:
 *
 * vim:set ft=cpp ts=4 sw=4 sts=4
 */
