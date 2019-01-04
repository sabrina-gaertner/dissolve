/*
	*** Energy Module
	*** src/modules/energy/energy.h
	Copyright T. Youngs 2012-2018

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

#ifndef DISSOLVE_ENERGYMODULE_H
#define DISSOLVE_ENERGYMODULE_H

#include "module/module.h"

// Forward Declarations
class PotentialMap;

// Energy Module
class EnergyModule : public Module
{
	/*
	 * Calculates the total energy of the system by one of several methods
	 */

	public:
	// Constructor
	EnergyModule();
	// Destructor
	~EnergyModule();


	/*
	 * Instances
	 */
	protected:
	// List of all instances of this Module type
	static List<Module> instances_;

	public:
	// Return list of all created instances of this Module
	List<Module>& instances();
	// Create instance of this module
	Module* createInstance();


	/*
	 * Definition
	 */
	public:
	// Return type of module
	const char* type() const;
	// Return brief description of module
	const char* brief() const;
	// Return the maximum number of Configurations the Module can target (or -1 for any number)
	int nTargetableConfigurations() const;


	/*
	 * Options
	 */
	protected:
	// Set up options for Module
	void setUpKeywords();
	// Parse complex keyword line, returning true (1) on success, false (0) for recognised but failed, and -1 for not recognised
	int parseComplexKeyword(ModuleKeywordBase* keyword, LineParser& parser, Dissolve* dissolve, GenericList& targetList, const char* prefix);


	/*
	 * Processing
	 */
	private:
	// Run main processing
	bool process(Dissolve& dissolve, ProcessPool& procPool);

	public:
	// Run set-up stage
	bool setUp(Dissolve& dissolve, ProcessPool& procPool);


	/* 
	 * Functions
	 */
	public:
	// Return total intramolecular energy
	static double intraMolecularEnergy(ProcessPool& procPool, Configuration* cfg, const PotentialMap& potentialMap);
	// Return total intramolecular energy, storing components in provided variables
	static double intraMolecularEnergy(ProcessPool& procPool, Configuration* cfg, const PotentialMap& potentialMap, double& bondEnergy, double& angleEnergy, double& torsionEnergy);
	// Return total interatomic energy
	static double interAtomicEnergy(ProcessPool& procPool, Configuration* cfg, const PotentialMap& potentialMap);
	// Return total intermolecular energy
	static double interMolecularEnergy(ProcessPool& procPool, Configuration* cfg, const PotentialMap& potentialMap);
	// Check energy stability of specified Configurations, returning the number that failed, or -1 if stability could not be assessed
	static int checkStability(const RefList<Configuration,bool>& configurations);


	/*
	 * GUI Widget
	 */
	public:
	// Return a new widget controlling this Module
	ModuleWidget* createWidget(QWidget* parent, Dissolve& dissolve);
};

#endif

