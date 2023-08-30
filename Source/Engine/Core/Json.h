#pragma once
#include <rapidjson/include/rapidjson/rapidjson.h>
#include <rapidjson/include/rapidjson/document.h>
#include "Core/Math/Vector2.h"
#include "Core/Math/Color.h"
#include "Core/Math/Rect.h"

#include <string>
#include <vector> // dynamic arrays that can grow and shrink


#define READ_DATA(value, data) kiko::Json::Read(value, #data, data)
#define READ_DATA_REQUIRED(value, data) kiko::Json::Read(value, #data, data, true)
#define HAS_DATA(value, data) value.HasMember(#data) // c.str
#define GET_DATA(value, data) value[#data] // c.str
#define READ_NAME_DATA(value, name, data) kiko::Json::Read(value, name, data)
#define READ_NAME_DATA_REQUIRED(value, name, data) kiko::Json::Read(value, name, data, true)

namespace kiko
{
	class Json
	{
	public: 

		static bool Load(const std::string& filename, rapidjson::Document& documet);
		static bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, Rect& data, int required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, int required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, int required = false);



	};

	using json_t = rapidjson::Value;
}