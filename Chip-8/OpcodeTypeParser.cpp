#include "OpcodeTypeParser.h"

uint8_t OpcodeTypeParser::Parse(uint16_t opcode)const
{
	uint16_t type = opcode & 0xF000;
	type /= 0x1000;
	return type;
}
