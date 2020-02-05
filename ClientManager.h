#pragma once
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>

//struct GETMESS
//{
//	char ret[256];
//	template <class Archive>
//	void serialize(Archive& archive)
//	{
//		archive(
//			CEREAL_NVP(ret)
//		);
//	}
//};

struct GETARRAY
{
	int id;
	std::string name;
	int param;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(
			CEREAL_NVP(id),
			CEREAL_NVP(name),
			CEREAL_NVP(param)
		);
	}
};

class CNetWorkManager
{
public:

	static int NetworkManager();
};
