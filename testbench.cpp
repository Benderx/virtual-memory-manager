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

	ReplacementPolicy POLICY = ReplacementPolicy::FIFO;
	unsigned int page_size = 2;
	unsigned int n_frames = 1;
	unsigned int v_addr = 8;

	virtualMemoryManager vm = virtualMemoryManager(POLICY, page_size, n_frames, v_addr);
	
	unsigned long long addr;
	unsigned long long addr2;
	
	cout << "addr? \n";
	cin >> addr;
	cout << "addr2? \n";
	cin >> addr2;
	cout << '\n';
	
	cout << "mem = " << vm.memoryAccess(addr) << '\n';
	cout << "mem = " << vm.memoryAccess(addr2) << '\n';
	



	cout << "Testing completed, exiting";
	
	return 0;
}
