#include "Json.h"
#include "rapidjson/include/rapidjson/istreamwrapper.h"
#include "FileIO.h"
#include "Logger.h"
#include <sstream>




namespace kiko
{
	bool Json::Load(const std::string& filename, rapidjson::Document& document)
	{
		std::string buffer;
		if (!readFile(filename, buffer))
		{
			WARNING_LOG("Cannot open file: " << filename);
			return false;
		}
		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);

		// parse stream to json
		document.ParseStream(istream);
		if (!document.IsObject())
		{
			WARNING_LOG("Json file cannot be parsed: " << filename);
			return false;
		}
		return true;
	}
	// GetInt()
	bool Json::Read(const rapidjson::Value& value, const std::string& name, int& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetInt();
		return true;
	}

	// GetFloat()
	bool Json::Read(const rapidjson::Value& value, const std::string& name, float& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetFloat();
		return true;
	}
	// GetBool()
	bool Json::Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetBool();
		return true;
	}
	// GetString()
	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetString();
		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required)
	{
		// check if 'name' member exists and is an array with 2 elements
			if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
			{
				if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
				return false;
			}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data[i] = array[i].GetFloat();
		}
		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required)
	{// check if 'name' member exists and is an array with 2 elements
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data[i] = array[i].GetFloat();
		}
		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, Rect& data, int required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data[i] = array[i].GetInt();
		}
		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, int required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
		{	// check if 'name' member exists and is an array - don't care about the size 
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsString())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data.push_back(array[i].GetString()); // String is something surrounded by quotes
		}
		return true;
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, int required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
		{	// check if 'name' member exists and is an array - don't care about the size 
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data.push_back(array[i].GetInt());
		}
		return true;
	}

}
