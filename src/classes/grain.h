/*
	*** Grain
	*** src/classes/grain.h
	Copyright T. Youngs 2012-2017

	This file is part of dUQ.

	dUQ is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	dUQ is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with dUQ.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DUQ_GRAIN_H
#define DUQ_GRAIN_H

#include "classes/atom.h"
#include "math/matrix3.h"
#include "templates/list.h"
#include "templates/reflist.h"

// Forward Declarations
class Box;
class Cell;
class Molecule;
class PotentialMap;
class SpeciesAngle;
class SpeciesBond;
class SpeciesGrain;

/*
 * Grain
 */
class Grain
{
	public:
	// Constructor
	Grain();
	// Destructor
	~Grain();
	// Clear all data
	void clear();


	/*
	 * Atoms / Character
	 */
	private:
	// Parent molecule
	Molecule* parent_;
	// Source SpeciesGrain
	SpeciesGrain* source_;
	// Number of atoms contained in this grain
	int nAtoms_;
	// Array size
	int atomsArraySize_;
	// Pointers to atoms
	Atom** atoms_;
	// Index of Grain
	int index_;

	public:
	// Initialise from SpeciesGrain
	bool initialise(SpeciesGrain* sg);
	// Set parent molecule
	void setParent(Molecule* mol);
	// Return parent molecule
	Molecule* parent() const;
	// Return source SpeciesGrain
	const SpeciesGrain* source() const;
	// Add atom pointer to list
	bool addAtom(Atom* i);
	// Return number of atoms in grain
	int nAtoms() const;
	// Return atoms array
	Atom** atoms() const;
	// Return nth atom in grain
	Atom* atom(int n) const;
	// Set index of grain
	void setIndex(int index);
	// Return index of grain
	int index() const;


	/*
	 * Coordinates / Manipulation
	 */
	private:
	// Local index of grain in cell's list
	int localIndex_;
	
	public:
	// Translate grain centre
	void translate(const Vec3<double>& delta);
};

#endif
