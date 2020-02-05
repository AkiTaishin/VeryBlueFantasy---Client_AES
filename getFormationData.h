#pragma once

#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>
#include <vector>
#include <string>

#define FORMATION_MAX	(3)

struct GET_DETAIL
{
	int admin;
	int number;
	int id;
	std::string name;
	std::string asset;
	int attack;
	int hp;
	int element;
	std::string userID;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(

			CEREAL_NVP(admin),
			CEREAL_NVP(number),
			CEREAL_NVP(id),
			CEREAL_NVP(name),
			CEREAL_NVP(asset),
			CEREAL_NVP(attack),
			CEREAL_NVP(hp),
			CEREAL_NVP(element),
			CEREAL_NVP(userID)
		);
	}
};

struct SERIALIZE_DATA
{
	GET_DETAIL data;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(

			CEREAL_NVP(data)
			
		);
	}
};

//struct SENDUSERID
//{
//	std::string userID;
//
//	template <class Archive>
//	void serialize(Archive& archive)
//	{
//		archive(
//
//			CEREAL_NVP(userID)
//
//		);
//	}
//};

class CGetFormationData
{
private:

public:
	
	static std::vector<SERIALIZE_DATA> m_GetFormationData;
	static std::vector<SERIALIZE_DATA> GetFormationData();
};
