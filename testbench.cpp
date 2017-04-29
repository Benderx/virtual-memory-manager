// testbench.cpp
// By Andrew Duerig and Gabe Stanton
//
// how to compile using mingw:
// g++ .\Project1.cpp myscheduler.cpp -o run.exe -std=c++11
//
//////////////////////////////////////////////////////////////////////////////////////////////
//
//ASSUMPTIONS
// assert(virtualAddressSpaceSize > N);
// assert(pow(2, virtualAddressSpaceSize) > numFrames * pow(2,N));

#include "virtualMemoryManager.cpp"
#include <random>

int main(int argc, char* argv[])
{
	cout << "\n--Andrew Duerig and Gabe Stanton's Testbench--\n\n";

	ReplacementPolicy POLICY = ReplacementPolicy::LRU;
	unsigned int page_size = 2;
	unsigned int n_frames = 3;
	unsigned int v_addr = 8;

	virtualMemoryManager vm = virtualMemoryManager(POLICY, page_size, n_frames, v_addr);
	
	unsigned long long addr;
	unsigned long long addr2;
	/*
	cout << "addr? \n";
	cin >> addr;
	cout << "addr2? \n";
	cin >> addr2;
	cout << '\n';
	
	
	cout << "mem = " << vm.memoryAccess(addr) << '\n';
	cout << "mem = " << vm.memoryAccess(addr2) << '\n';
	*/
	
	cout << "0: mem = " << vm.memoryAccess(0) << '\n' << '\n';
	cout << "2: mem = " << vm.memoryAccess(2) << '\n' << '\n';
	cout << "0: mem = " << vm.memoryAccess(0) << '\n' << '\n';
	cout << "6: mem = " << vm.memoryAccess(6) << '\n' << '\n';
	cout << "6: mem = " << vm.memoryAccess(6) << '\n' << '\n';
	cout << "8: mem = " << vm.memoryAccess(8) << '\n' << '\n';
	cout << "3: mem = " << vm.memoryAccess(3) << '\n' << '\n';
	cout << "1: mem = " << vm.memoryAccess(1) << '\n' << '\n';


	cout << "Testing completed, exiting";
	
	return 0;
}
