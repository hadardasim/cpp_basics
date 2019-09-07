/*
In the following example, multiple thread are incrementing a shared varaible.
when the shared resource is not protected we are expecting to get lower final value than num_threads*calls_per_thread
*/

#include "MTWrite.h"
#include <atomic>
#include <cstdint>
#include <iostream>
#include <thread>
#include <vector>

class CBase
{
public:
	virtual void inc() = 0;
	virtual uint32_t get() const = 0;
};



class C1 : public CBase
{
public:
	C1() : x(0)
	{

	}
	uint32_t x = 0;
	virtual void inc() override
	{
		x++;
	}
	virtual uint32_t get() const override
	{
		return x;
	}
};

class C2 : public CBase
{
public:
	C2() : x(0)
	{

	}

	std::atomic<uint32_t> x;
	virtual void inc() override
	{
		x++;
	}
	virtual uint32_t get() const override
	{
		return x;
	}
};

void test_write(CBase& data, int num_threads, int calls_per_thread)
{
	std::vector<std::thread*> arrThreads;

	auto thread_func = [=](CBase* data) {
		for (int i = 0; i < calls_per_thread; ++i)
			data->inc();
	};

	for (int i = 0; i < num_threads; ++i)
		arrThreads.push_back(new std::thread(thread_func, &data));

	for (auto pThread : arrThreads)
	{
		pThread->join();
		delete pThread;
	}

	std::cout << "output " << data.get() << " expected " << num_threads * calls_per_thread << std::endl;
}

void MTWrite::test(int num_threads, int calls_per_thread)
{
	std::cout << "C1 (Naive)\n ";
	C1 c1;
	test_write(c1, num_threads, calls_per_thread);

	std::cout << "C2 (atomic)\n";
	C2 c2;
	test_write(c2, num_threads, calls_per_thread);
	
}