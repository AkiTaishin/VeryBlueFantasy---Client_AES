#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#include <fstream>
#include <vector>
#include <string>

#define REGISTER_MAX	30

struct CLIENT_INFO
{
	std::string userID;
	std::string loginID;
	std::string passward;
	int deleteKey;

	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(

			CEREAL_NVP(userID),
			CEREAL_NVP(loginID),
			CEREAL_NVP(passward),
			CEREAL_NVP(deleteKey)
		);
	}
};

class CClientInfo
{
private:

public:
	static void SaveClientInfo(CLIENT_INFO save);
	static CLIENT_INFO LoadClientInfo(CLIENT_INFO senddata);
};
