#include "pch.h"
#include "Interpreter.h"


Interpreter::Interpreter()
{
}


Interpreter::~Interpreter()
{
}

bool Interpreter::SetRegisters(std::vector<int> values)
{
	if (values.size() != 4)
		return false;
	m_registers.assign(values.begin(), values.end());
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
		break;
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
