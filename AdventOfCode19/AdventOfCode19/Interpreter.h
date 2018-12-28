#pragma once
#include <vector>
#include <string>
#include <map>

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

	Interpreter(int ip);
	~Interpreter();

	bool SetRegisters(std::vector<int> values);
	std::vector<int> GetRegisters() { return m_registers; }

	void RunProgram(std::vector<std::string> program);

	void PrintRegisters();

	void RunOperation(std::vector<int> instruction);
	void RunOperation(Opcodes op, int a, int b, int c);

private:
	void Initialize();

	void PreProcess(std::vector<std::string> program);

	std::vector<int> m_registers;
	std::map<std::string, Opcodes> m_opMap;
	int m_ip;

	std::vector<std::vector<int>> m_processedProgram;

	void Add(int aVal, int bVal, int cReg);
	void Mul(int aVal, int bVal, int cReg);
	void Ban(int aVal, int bVal, int cReg);
	void Bor(int aVal, int bVal, int cReg);
	void Set(int aVal, int cReg);
	void Gt(int aVal, int bVal, int cReg);
	void Eq(int aVal, int bVal, int cReg);
};

