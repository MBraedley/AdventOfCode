#pragma once
#include <vector>

class Interpreter
{
public:
	enum Opcodes
	{
		addr,
		addi,
		mulr,
		muli,
		banr,
		bani,
		borr,
		bori,
		setr,
		seti,
		gtir,
		gtri,
		gtrr,
		eqir,
		eqri,
		eqrr,
		LAST
	};

	Interpreter();
	~Interpreter();

	bool SetRegisters(std::vector<int> values);
	std::vector<int> GetRegisters() { return m_registers; }

	void RunOperation(Opcodes op, int a, int b, int c);

private:
	std::vector<int> m_registers;

	void Add(int aVal, int bVal, int cReg);
	void Mul(int aVal, int bVal, int cReg);
	void Ban(int aVal, int bVal, int cReg);
	void Bor(int aVal, int bVal, int cReg);
	void Set(int aVal, int cReg);
	void Gt(int aVal, int bVal, int cReg);
	void Eq(int aVal, int bVal, int cReg);
};

