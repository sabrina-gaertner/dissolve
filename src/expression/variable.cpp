/*
	*** Expression Variable
	*** src/expression/variable.cpp
	Copyright T. Youngs 2015-2020

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

#include "expression/variable.h"
#include "base/messenger.h"
#include <string.h>

// Constructor
ExpressionVariable::ExpressionVariable(ExpressionValue value, bool readOnly) : ExpressionNode()
{
	// Private variables
	static int count = 0;
	name_.sprintf("_ExpressionVariable%02i", count++);
	initialValue_ = NULL;
	nodeType_ = ExpressionNode::VariableNode;
	value_ = value;
	readOnly_ = readOnly;
}

// Destructor (virtual)
ExpressionVariable::~ExpressionVariable()
{
}

// Set name of variable
void ExpressionVariable::setName(const char* s)
{
	name_ = s;
}

// Get name of variable
const char* ExpressionVariable::name() const
{
	return name_.get();
}

// Initialise variable
bool ExpressionVariable::initialise()
{
	if (initialValue_ == NULL) value_ = 0.0;
	else
	{
		ExpressionValue result;
		if (initialValue_->execute(result))
		{
			if (set(result)) return true;
			else
			{
				Messenger::error("Failed to initialise variable '%s'.\n", name_.get());
				return false;
			}
		}
		return false;
	}
	return true;
}

// Set initial value expression
bool ExpressionVariable::setInitialValue(ExpressionNode* node)
{
	initialValue_ = node;
	if (initialValue_ == NULL) return true;

	return true;
}

// Return Node corresponding to initial value
ExpressionNode* ExpressionVariable::initialValue() const
{
	return initialValue_;
}

/*
 * Set / Get
 */

// Set value of variable (real)
bool ExpressionVariable::set(ExpressionValue value)
{
	if (readOnly_)
	{
		printf("A constant value (in this case a double) cannot be assigned to.\n");
		return false;
	}

	value_ = value;

	return true;
}

// Return value
const ExpressionValue& ExpressionVariable::value() const
{
	return value_;
}

// Return pointer to value
ExpressionValue* ExpressionVariable::valuePointer()
{
	return &value_;
}

// Return value of node
bool ExpressionVariable::execute(ExpressionValue& value)
{
	value = value_;

	return true;
}

// Print node contents
void ExpressionVariable::nodePrint(int offset, const char* prefix)
{
	// Construct tabbed offset
	CharString tab;
	for (int n=0; n<offset-1; n++) tab += '\t';
	if (offset > 1) tab += "   |--> ";
	tab += prefix;

	// Output node data
	if (readOnly_)
	{
		if (value_.isInteger()) printf("[C]%s%i (constant integer value)\n", tab.get(), value_.asInteger());
		else printf("[C]%s%f (constant double value)\n", tab.get(), value_.asDouble());
	}
	else
	{
		if (value_.isInteger()) printf("[V]%s%i (integer variable '%s')\n", tab.get(), value_.asInteger(), name());
		else printf("[V]%s%f (double variable '%s')\n", tab.get(), value_.asDouble(), name());
	}
}
