#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace Tokenparser {
	uint8_t getPVarT(const std::string& str) {
		if(str == "u1")
			return VAR_U1;

		else if(str == "u8")
			return VAR_U8;
		else if(str == "i8")
			return VAR_I8;
		else if(str == "c8")
			return VAR_C8;

		else if(str == "u16")
			return VAR_U16;
		else if(str == "i16")
			return VAR_I16;
		else if(str == "c16")
			return VAR_C16;

		else if(str == "u32")
			return VAR_U32;
		else if(str == "i32")
			return VAR_I32;
		else if(str == "c32")
			return VAR_C32;
		else if(str == "f32")
			return VAR_F32;

		else if(str == "u64")
			return VAR_U64;
		else if(str == "i64")
			return VAR_I64;
		else if(str == "f64")
			return VAR_F64;

		else if(str == "u128")
			return VAR_U128;
		else if(str == "i128")
			return VAR_I128;
		else if(str == "f128")
			return VAR_F128;

		else if(str == "usize")
			return VAR_USIZE;
		else if(str == "isize")
			return VAR_ISIZE;

		else if(str == "bool")
			return VAR_BOOL;

		return VAR_UNDEFINED;
	}
}
