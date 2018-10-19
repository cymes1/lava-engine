#include "utils.h"

namespace LavaEngine { namespace Utils {

	std::string versionIntToString(uint32_t version)
	{
		std::string parsedVersion = std::to_string(version >> 22) + std::string(".")
					+ std::to_string((version >> 11) & 0x000003ff) + std::string(".")
					+ std::to_string((version >> 0) & 0x000003ff);

		return parsedVersion;
	}

}}
