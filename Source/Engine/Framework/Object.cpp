#include "Object.h"

namespace kiko
{
	bool Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
		//Json::Read(value, "m_name", m_name);

		return true;
	}
}