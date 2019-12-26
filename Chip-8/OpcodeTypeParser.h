#pragma once
#include<cstdint>

class OpcodeTypeParser
{
public:
	virtual uint8_t Parse(uint16_t opcode) const;
};