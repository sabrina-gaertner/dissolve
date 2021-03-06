/*
	*** SpeciesRing Definition
	*** src/classes/speciesring.cpp
	Copyright T. Youngs 2012-2020

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

#include "classes/speciesring.h"
#include "classes/speciesatom.h"
#include "data/elements.h"

// Constructor
SpeciesRing::SpeciesRing() : ListItem<SpeciesRing>()
{
}

// Destructor
SpeciesRing::~SpeciesRing()
{
}

/*
 * Atoms
 */

// Set atoms in ring
void SpeciesRing::setAtoms(const PointerArray<const SpeciesAtom>& atoms)
{
	atoms_ = atoms;
}

// Return nth atom in ring
const SpeciesAtom* SpeciesRing::atom(int n) const
{
	return atoms_.at(n);
}

// Return array of atoms in ring
const PointerArray<const SpeciesAtom>& SpeciesRing::atoms() const
{
	return atoms_;
}

// Return size of ring (number of atoms in array)
int SpeciesRing::size() const
{
	return atoms_.nItems();
}

// Print ring information
void SpeciesRing::print() const
{
	printf("Ring(%i) :", atoms_.nItems());
	for (int n=0; n<atoms_.nItems(); ++n) printf(" %2i(%s)", atoms_.at(n)->userIndex(), atoms_.at(n)->element()->symbol());
	printf("\n");
}

/*
 * Comparison
 */

// Equality operator
bool SpeciesRing::operator==(const SpeciesRing& other)
{
	// Check ring size first
	const int nAtoms = atoms_.nItems();
	if (nAtoms != other.atoms_.nItems()) return false;

	// Find equivalent atom in second ring to determine starting index
	int indexA = 0, indexB;
	for (indexB = 0; indexB<nAtoms; ++indexB) if (atoms_.at(indexA) == other.atoms_.at(indexB)) break;

	// If we didn't find the atom, can return now
	if (indexB == nAtoms) return false;

	// Go over atoms and compare in both directions around the other ring
	for (int n=1; n<nAtoms; ++n)
	{
		if ((atoms_.at(indexA+n) != other.atoms_.at((indexB+n)%nAtoms)) && (atoms_.at(indexA+n) != other.atoms_.at((nAtoms+indexB-n)%nAtoms))) return false;
	}

	return true;
}
