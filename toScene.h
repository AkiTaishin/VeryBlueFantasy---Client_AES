#pragma once
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>

#define SCENE_MAX (10)

struct URI
{
	int number;
	std::string templateName;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(

			CEREAL_NVP(number),
			CEREAL_NVP(templateName)
		);
	}
};

class CtoScene
{
public:

	static std::string GoToScene(int index);
};
