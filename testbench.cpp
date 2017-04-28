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

	ReplacementPolicy policy = ReplacementPolicy::FIFO;
	cout << policy << '\n';
	unsigned int page_size = 4;
	unsigned int n_frames = 4;
	unsigned int v_addr = 64;

	virtualMemoryManager vm = virtualMemoryManager(policy, page_size, n_frames, v_addr);
	
	unsigned long long addr = 4;
	
	cout << vm.memoryAccess(addr) << '\n';
	



	cout << "Testing completed, exiting";
	
	return 0;
}
