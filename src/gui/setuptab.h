/*
	*** Setup Tab
	*** src/gui/setuptab.h
	Copyright T. Youngs 2012-2018

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

#ifndef DUQ_SETUPTAB_H
#define DUQ_SETUPTAB_H

#include "gui/ui_setuptab.h"
#include "gui/maintab.h"

// Forward Declarations
/* none */

// Setup Tab
class SetupTab : public QWidget, public MainTab
{
	// All Qt declarations derived from QObject must include this macro
	Q_OBJECT

	public:
	// Constructor / Destructor
	SetupTab(DUQ& dUQ, QTabWidget* parent, const char* title);
	~SetupTab();
	// Main form declaration
	Ui::SetupTab ui;


	/*
	 * Data
	 */
	public:
	// Return MDI area available in tab (if any)
	QMdiArea* mdiArea();


	/*
	 * Update
	 */
	protected:
	// Update controls in page
	void updatePage();
	// Disable sensitive controls within page, ready for main code to run
	void disableSensitiveControlsInPage();
	// Enable sensitive controls within page, ready for main code to run
	void enableSensitiveControlsInPage();
};

#endif