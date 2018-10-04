/*
	*** Export Module - Formats
	*** src/modules/export/formats.h
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

#ifndef DISSOLVE_EXPORTMODULEFORMATS_H
#define DISSOLVE_EXPORTMODULEFORMATS_H

#include "base/fileandformat.h"

// Forward Declarations
/* none */

// Coordinate Export Formats
class CoordinateExportFileFormat : public FileAndFormat
{
	public:
	// Available coordinate formats
 	enum CoordinateExportFormat { XYZCoordinates, DLPOLYCoordinates, nCoordinateExportFormats };
	// Return number of available formats
	int nFormats() const;
	// Return formats array
	const char** formats() const;
	// Return nice formats array
	const char** niceFormats() const;
	// Return current format as CoordinateExportFormat
	CoordinateExportFormat coordinateFormat() const;
};


// Data2D Export Formats
class Data2DExportFileFormat : public FileAndFormat
{
	public:
	// Available data formats
 	enum Data2DExportFormat { BlockData, nCoordinateExportFormats };
	// Return number of available formats
	int nFormats() const;
	// Return formats array
	const char** formats() const;
	// Return nice formats array
	const char** niceFormats() const;
	// Return current format as Data2DExportFormat
	Data2DExportFormat data2DFormat() const;
};

#endif

