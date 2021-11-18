#ifndef CACHEENTRY_H
#define CACHEENTRY_H

namespace test3d
{
	class CacheEntry
	{
	public:

	// Constructors and Destructor:

		CacheEntry();

		~CacheEntry();

	// Public Variables:

		uint32 Index;

		CacheEntry* pNext;
	};
}

#endif // CACHEENTRY_H