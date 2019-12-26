#pragma once
#include<unordered_map>
#include"OpcodeTypeParser.h"
#include"OpcodeRunner.h"

class OpcodeRunnerResolver
{
public:
	OpcodeRunnerResolver(OpcodeTypeParser& opcodeTypeParser, const std::unordered_map<uint8_t, OpcodeRunner&>& opcodeTypeToOpcodeRunnerResover);

	void operator()(uint16_t opcode);

private:
	const std::unordered_map<uint8_t, OpcodeRunner&>& _opcodeTypeToOpcodeRunnerResover;
	OpcodeTypeParser& _opcodeTypeParser;
};