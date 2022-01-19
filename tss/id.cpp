#include "id.h"

namespace tss
{
	IdType generateId()
	{
		static IdType idGenerator = 1;
		return idGenerator++;
	}
}