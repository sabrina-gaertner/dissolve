/*
	*** Analysis Node - Normalise1D
	*** src/analyse/nodes/normalise1d.cpp
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

#include "analyse/nodes/normalise1d.h"
#include "analyse/nodes/collect1d.h"
#include "analyse/nodecontextstack.h"
#include "base/lineparser.h"
#include "base/sysfunc.h"
#include "templates/genericlisthelper.h"

// Constructor
AnalysisNormalise1DNode::AnalysisNormalise1DNode() : AnalysisNode()
{
	type_ = AnalysisNode::Normalise1DNode;
	collectNode_ = NULL;
}

// Destructor
AnalysisNormalise1DNode::~AnalysisNormalise1DNode()
{
}

/*
 * Node Keywords
 */

// Node Keywords (note ordering for efficiency)
const char* Normalise1DNodeKeywords[] = { "EndNormalise1D", "NSites" };

// Convert string to node keyword
AnalysisNormalise1DNode::Normalise1DNodeKeyword AnalysisNormalise1DNode::normalise1DNodeKeyword(const char* s)
{
	for (int nk=0; nk < AnalysisNormalise1DNode::nNormalise1DNodeKeywords; ++nk) if (DissolveSys::sameString(s, Normalise1DNodeKeywords[nk])) return (AnalysisNormalise1DNode::Normalise1DNodeKeyword) nk;

	return AnalysisNormalise1DNode::nNormalise1DNodeKeywords;
}

// Convert node keyword to string
const char* AnalysisNormalise1DNode::normalise1DNodeKeyword(AnalysisNormalise1DNode::Normalise1DNodeKeyword nk)
{
	return Normalise1DNodeKeywords[nk];
}

/*
 * Data
 */

/*
 * Execute
 */

// Prepare any necessary data, ready for execution
bool AnalysisNormalise1DNode::prepare(Configuration* cfg, const char* dataPrefix, GenericList& targetList)
{
	return true;
}

// Execute node, targetting the supplied Configuration
AnalysisNode::NodeExecutionResult AnalysisNormalise1DNode::execute(ProcessPool& procPool, Configuration* cfg, const char* dataPrefix, GenericList& targetList)
{
	// Retrieve / realise the normalised data from the supplied list
	CharString dataName("%s_Normalised", name());
	Data1D& normalisedData = GenericListHelper<Data1D>::realise(targetList, dataName, dataPrefix, GenericItem::InRestartFileFlag);

	// Copy the averaged data from the associated Collect1D node, and normalise it accordingly
	normalisedData = collectNode_->accumulatedData();
	
	return AnalysisNode::Success;
}

// Finalise any necessary data after execution
bool AnalysisNormalise1DNode::finalise(Configuration* cfg, const char* dataPrefix, GenericList& targetList)
{
	return true;
}

/*
 * Read / Write
 */

// Read structure from specified LineParser
bool AnalysisNormalise1DNode::read(LineParser& parser, NodeContextStack& contextStack)
{
	// The current line in the parser must also contain the name of a Collect1D node which we will operate on
	if (parser.nArgs() != 2) return Messenger::error("A Normalise1D node must be given the name of a Collect1D node.\n");
	collectNode_ = contextStack.collect1DNode(parser.argc(1));
	if (!collectNode_) return Messenger::error("A valid Collect1D node name must be given as an argument to Normalise1D.\n");

	// Read until we encounter the EndNormalise1D keyword, or we fail for some reason
	while (!parser.eofOrBlank())
	{
		// Read and parse the next line
		if (parser.getArgsDelim(LineParser::Defaults+LineParser::SkipBlanks+LineParser::StripComments) != LineParser::Success) return false;

		// Is the first argument on the current line a valid control keyword?
		Normalise1DNodeKeyword nk = normalise1DNodeKeyword(parser.argc(0));
		switch (nk)
		{
			case (Normalise1DNodeKeyword::EndNormalise1DKeyword):
				return true;
			case (Normalise1DNodeKeyword::NSitesKeyword):
				// TODO
				break;
			case (Normalise1DNodeKeyword::nNormalise1DNodeKeywords):
				return Messenger::error("Unrecognised Normalise1D node keyword '%s' found.\n", parser.argc(0));
				break;
			default:
				return Messenger::error("Epic Developer Fail - Don't know how to deal with the Normalise1D node keyword '%s'.\n", parser.argc(0));
		}
	}

	return true;
}

// Write structure to specified LineParser
bool AnalysisNormalise1DNode::write(LineParser& parser, const char* prefix)
{
	// TODO
}
