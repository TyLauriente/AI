#ifndef INCLUDED_AI_MEMORYRECORD_H
#define INCLUDED_AI_MEMORYRECORD_H

#include <XEngine.h>

namespace AI {

class MemoryRecord
{
public:
	MemoryRecord()
		: lastRecordedTime(0.0f)
		, importance(0.0)
	{}

	virtual ~MemoryRecord() {}

	float lastRecordedTime;
	X::Math::Vector2 lastLocation;
	float importance;
};

typedef std::list<MemoryRecord*> MemoryRecords;

} // namespace AI

#endif // #include INCLUDED_AI_MEMORYRECORD_H