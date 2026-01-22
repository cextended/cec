#pragma once

#include <segvc/expressions.hxx>

namespace segvc {

	struct Typer;
	struct Expression;

	using ExprPtr = std::shared_ptr<Expression>;

	struct VariableEntry {
		//std::string name;
			// NOTE: This struct should just represent variable's type and it's initializer/default expression
		std::shared_ptr<Typer> typer;
		ExprPtr initializer;
	};

}
