#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>
#include <vector>
#include <string>

struct SAVE_DETAIL
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

class CSaveFormationData
{
private:

public:
	static void SaveFormation(SAVE_DETAIL data);
	static void ResetFormation(void);
};

