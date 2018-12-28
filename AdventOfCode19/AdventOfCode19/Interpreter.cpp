#include "pch.h"
#include "Interpreter.h"
#include <sstream>
#include <iostream>

Interpreter::Interpreter(int ip) : m_ip(ip), m_registers(6, 0)
{
	Initialize();
}


Interpreter::~Interpreter()
{
}

bool Interpreter::SetRegisters(std::vector<int> values)
{
	if (values.size() != 6)
		return false;
	m_registers.assign(values.begin(), values.end());
}

void Interpreter::RunProgram(std::vector<std::string> program)
{
	PreProcess(program);
	while (m_registers[m_ip] < m_processedProgram.size())
	{
		RunOperation(m_processedProgram[m_registers[m_ip]]);
		m_registers[m_ip]++;
		PrintRegisters();
	}
}

void Interpreter::PrintRegisters()
{
	for (int reg : m_registers)
		std::cout << reg << " ";
	std::cout << std::endl;
}

void Interpreter::RunOperation(std::vector<int> instruction)
{
	if (instruction.size() != 4)
		std::cout << "Bad instruction" << std::endl;
	RunOperation((Opcodes)instruction[0], instruction[1], instruction[2], instruction[3]);
}

void Interpreter::RunOperation(Opcodes op, int a, int b, int c)
{
	switch (op)
	{
	case Interpreter::addr:
		Add(m_registers[a], m_registers[b], c);
		break;
	case Interpreter::addi:
		Add(m_registers[a], b, c);
		break;
	case Interpreter::mulr:
		Mul(m_registers[a], m_registers[b], c);
		break;
	case Interpreter::muli:
		Mul(m_registers[a], b, c);
		break;
	case Interpreter::banr:
		Ban(m_registers[a], m_registers[b], c);
		break;
	case Interpreter::bani:
		Ban(m_registers[a], b, c);
		break;
	case Interpreter::borr:
		Bor(m_registers[a], m_registers[b], c);
		break;
	case Interpreter::bori:
		Bor(m_registers[a], b, c);
		break;
	case Interpreter::setr:
		Set(m_registers[a], c);
		break;
	case Interpreter::seti:
		Set(a, c);
		break;
	case Interpreter::gtir:
		Gt(a, m_registers[b], c);
		break;
	case Interpreter::gtri:
		Gt(m_registers[a], b, c);
		break;
	case Interpreter::gtrr:
		Gt(m_registers[a], m_registers[b], c);
		break;
	case Interpreter::eqir:
		Eq(a, m_registers[b], c);
		break;
	case Interpreter::eqri:
		Eq(m_registers[a], b, c);
		break;
	case Interpreter::eqrr:
		Eq(m_registers[a], m_registers[b], c);
		break;
	default:
		std::cout << "Bad opcode" << std::endl;
		break;
	}
}

void Interpreter::Initialize()
{
	m_opMap.insert(std::make_pair("addr", addr));
	m_opMap.insert(std::make_pair("addi", addi));
	m_opMap.insert(std::make_pair("mulr", mulr));
	m_opMap.insert(std::make_pair("muli", muli));
	m_opMap.insert(std::make_pair("banr", banr));
	m_opMap.insert(std::make_pair("bani", bani));
	m_opMap.insert(std::make_pair("borr", borr));
	m_opMap.insert(std::make_pair("bori", bori));
	m_opMap.insert(std::make_pair("setr", setr));
	m_opMap.insert(std::make_pair("seti", seti));
	m_opMap.insert(std::make_pair("gtir", gtir));
	m_opMap.insert(std::make_pair("gtri", gtri));
	m_opMap.insert(std::make_pair("gtrr", gtrr));
	m_opMap.insert(std::make_pair("eqir", eqir));
	m_opMap.insert(std::make_pair("eqri", eqri));
	m_opMap.insert(std::make_pair("eqrr", eqrr));
}

void Interpreter::PreProcess(std::vector<std::string> program)
{
	for (std::string instruction : program)
	{
		std::stringstream sstrm(instruction);
		std::string opStr;
		int a, b, c;
		sstrm >> opStr >> a >> b >> c;
		std::vector<int> inst;
		inst.push_back(m_opMap.find(opStr)->second);
		inst.push_back(a);
		inst.push_back(b);
		inst.push_back(c);
		m_processedProgram.push_back(inst);
	}
}

void Interpreter::Add(int aVal, int bVal, int cReg)
{
	m_registers[cReg] = aVal + bVal;
}

void Interpreter::Mul(int aVal, int bVal, int cReg)
{
	m_registers[cReg] = aVal * bVal;
}

void Interpreter::Ban(int aVal, int bVal, int cReg)
{
	m_registers[cReg] = aVal & bVal;
}

void Interpreter::Bor(int aVal, int bVal, int cReg)
{
	m_registers[cReg] = aVal | bVal;
}

void Interpreter::Set(int aVal, int cReg)
{
	m_registers[cReg] = aVal;
}

void Interpreter::Gt(int aVal, int bVal, int cReg)
{
	m_registers[cReg] = aVal > bVal ? 1 : 0;
}

void Interpreter::Eq(int aVal, int bVal, int cReg)
{
	m_registers[cReg] = aVal == bVal ? 1 : 0;
}
