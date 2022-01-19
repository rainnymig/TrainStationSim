#pragma once

namespace tss
{
	using IdType = unsigned long;

	static constexpr IdType NULL_ID = 0;

	IdType generateId();
}