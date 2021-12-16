#include "Rng.h"

int Rng::rng(int min, int max)
{
	FrameTimerRng ft;		//initializing timer, clock and dummy array
	clock.UpdateTime();
	int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int arr2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double time = (double)clock.GetTime();

	std::thread::id t_thread = std::this_thread::get_id();		//Getting current thread id number and converting to uint64
	std::stringstream ts;
	ts << t_thread;
	uint64_t id = std::stoull(ts.str());

	time /= 100;						//Getting value from the clock and converting to uint64, only seconds 
	time = std::modf(time, &time);
	time *= 100;
	time += 1;
	uint64_t cumulativeval = (uint64_t)time;

	uint64_t nanotimer = ft.GetNano();				//Getting timer value in nanoseconds
	std::string temp = std::to_string(nanotimer);
	char c = temp[temp.size() - 3];
	int lastnano = c - '0';				//Saving some numbers of the timer
	char c2 = temp[temp.size() - 4];
	int lastnano2 = c2 - '0';

	std::stringstream mem;			//Getting dummy array adress value in hexa based on the lastnano, and converting to uint64 decimal value
	mem << &arr[lastnano];
	std::string memtemp;
	mem >> memtemp;
	std::string memout = memtemp.substr(8, std::string::npos);  //Discarding first 8 hexa numbers, they are usualy the same
	uint64_t memval = HexaToDecConverion<uint64_t >(memout);
	std::stringstream mem2;
	mem2 << &arr2[lastnano2];
	std::string memtemp2;
	mem2 >> memtemp2;
	std::string memout2 = memtemp2.substr(14, std::string::npos);   //Discarding first 14 hexa numbers
	uint64_t memval2 = HexaToDecConverion<uint64_t >(memout2);
	if (memval2 == 0 || memval == 1)
	{
		memval2 = 2;
	}

	cumulativeval += nanotimer;				//Mixing all the values together
	cumulativeval -= id;
	cumulativeval += memval;
	cumulativeval /= memval2;

	cumulativeval %= max;						//Targeting the output range
	int output = (int)cumulativeval;

	if (output < min)					//if val is below min doing recursion
	{
		output = rng(min, max);
	}

	return output;
}

unsigned int Rng::rngtest(unsigned int min, unsigned int max)
{
	unsigned int out = rg();
	out %= max;
	if (out < min || out > max)
	{
		rngtest(min, max);
	}
	return out;
}
