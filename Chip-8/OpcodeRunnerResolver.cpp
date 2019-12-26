#include "OpcodeRunnerResolver.h"

OpcodeRunnerResolver::OpcodeRunnerResolver(OpcodeTypeParser & opcodeTypeParser, const std::unordered_map<uint8_t, OpcodeRunner&>& opcodeTypeToOpcodeRunnerResover)
	:
	_opcodeTypeParser(opcodeTypeParser),
	_opcodeTypeToOpcodeRunnerResover(opcodeTypeToOpcodeRunnerResover)
{}

void OpcodeRunnerResolver::operator()(uint16_t opcode)
{
	uint8_t opcodeType = _opcodeTypeParser.Parse(opcode);
	OpcodeRunner& opcodeRunner = _opcodeTypeToOpcodeRunnerResover.at(opcodeType);
	opcodeRunner(opcode);
}
