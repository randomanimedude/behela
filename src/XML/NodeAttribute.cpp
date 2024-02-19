#include "NodeAttribute.h"

namespace XML
{
	StringNodeAttribute::StringNodeAttribute(std::string data)
		: _data(data)
	{
	}

	std::string StringNodeAttribute::GetDataString() const
	{
		return _data;
	}
}
