#pragma once

#include "color.h"
#include "agent.h"
#include <stdexcept>
#include <system_error>
#include <unordered_map>

#include <mutex>

namespace stibbons {

/**
 * \class Zone
 *
 * \brief class Zone
 *
 * \author Julia Bassoumi
 */
class Zone : public Agent{
	public:
		/**
		 * Create a zone
		 */
		Zone (Agent *parent);

		/**
		 * Create a copy of a zone
		 * @param other the other zone
		 */
		Zone (Zone &other);

		/**
		 * Move a zone
		 * @param other the other zone
		 */
		Zone (Zone &&other);

		/**
		 * Copy of a zone
		 * @param other the other zone
		 */
		Zone& operator= (Zone& other);

		/**
		 * Move a zone
		 * @param other the other zone
		 */
		Zone& operator= (Zone&& other);

		virtual Type getType() const;

		/**
		 * Set the value for an axis
		 * @param axis the axis
		 * @param value the value
		 */
		void setColor (Color color);

		/**
		 * Get the value for an axis
		 * @return a reference to the value for an axis
		 */
		Color getColor ();

		/**
		 * Get the value of world
		 * @return the value of world
		 */
		World* getWorld ();

		void changed ();

		/**
		 * Return a string corresponding to the value
		 * @return a string corresponding to the value
		 */
		virtual string toString ();

	private:
		Color color;

		std::mutex value_m;
};

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
