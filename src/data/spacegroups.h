/*
	*** Crystallographic Spacegroups
	*** src/data/spacegroups.h
	Copyright T. Youngs 2019-2020

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

#ifndef DISSOLVE_SPACEGROUPS_H
#define DISSOLVE_SPACEGROUPS_H

// Spacegroup Name Data
class SpacegroupNameData
{
	public:
	// Constructor
	SpacegroupNameData(const char* name, const char* formattedName);

	private:
	// Name of the spacegroup
	const char* name_;
	// Formatted name of the spacegroup
	const char* formattedName_;

	public:
	// Return the name of the spacegroup
	const char* name() const;
	// Return the formatted name of the spacegroup
	const char* formattedName() const;
};

// Spacegroups
class Spacegroups
{
	private:
	// Return SpacegroupNameData with index specified
	static const SpacegroupNameData& spacegroupNameData(int id);
};

#endif
