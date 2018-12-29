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

	Interpreter(int ip, bool printRegisters = false);
	~Interpreter();

	bool SetRegisters(std::vector<int> values);
	std::vector<int> GetRegisters() { return m_registers; }

	void RunProgram(std::vector<std::string> program);

	void PrintRegisters();

	void PrintRegisters(std::ofstream& fout);

	int GetInstructionCount() { return m_instructionCount; }
	void ResetInstructionCount() { m_instructionCount = 0; }

	void SetMaxInstructions(unsigned long long max) { m_maxInstructionsToRun = max; }
	void SetMaxRepeat(unsigned long long max) { m_maxInstructionRepeat = max; }

	void RunOperation(std::vector<int> instruction);
	void RunOperation(Opcodes op, int a, int b, int c);

	bool NormalExit() { return !m_wasHalted; }

private:
	void Initialize();

	void PreProcess(std::vector<std::string> program);

	std::vector<int> m_registers;
	std::map<std::string, Opcodes> m_opMap;
	int m_ip;

	std::vector<std::vector<int>> m_processedProgram;
	int m_instructionCount;

	bool m_printRegisters;

	unsigned long long m_maxInstructionsToRun;
	unsigned long long m_maxInstructionRepeat;
	std::map<int, unsigned long long> m_repeatCount;
	bool m_wasHalted;

	void Add(int aVal, int bVal, int cReg);
	void Mul(int aVal, int bVal, int cReg);
	void Ban(int aVal, int bVal, int cReg);
	void Bor(int aVal, int bVal, int cReg);
	void Set(int aVal, int cReg);
	void Gt(int aVal, int bVal, int cReg);
	void Eq(int aVal, int bVal, int cReg);
};

