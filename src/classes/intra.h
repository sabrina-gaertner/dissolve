/*
	*** Intramolecular Base Class
	*** src/classes/intra.h
	Copyright T. Youngs 2012-2019

	This file is part of Dissolve.

	Dissolve is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Dissolve is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Dissolve.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DISSOLVE_INTRA_H
#define DISSOLVE_INTRA_H

// Forward Declarations
class Molecule;

// Intra Definition
class Intra
{
	public:
	// Constructor
	Intra();
	// Destructor
	~Intra();


	/*
	 * Basic Data
	 */
	protected:
	// Molecule in which the term exists
	Molecule* molecule_;
	
	public:
	// Set Molecule in which the term exists
	void setMolecule(Molecule* parent);
	// Return Molecule in which the term exists
	Molecule* molecule() const;
};

#endif
