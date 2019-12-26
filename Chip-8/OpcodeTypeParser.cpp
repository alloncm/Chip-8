#include "OpcodeTypeParser.h"

uint8_t OpcodeTypeParser::Parse(uint16_t opcode)const
{
	return opcode & 0xF000;
}
