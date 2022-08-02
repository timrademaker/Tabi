#include "Helpers/ExecutionQueue.h"

#include <iterator>

tabi::ExecutionQueue::ExecutionQueue(size_t a_InitialQueueCapacity)
{
	m_FunctionQueue.reserve(a_InitialQueueCapacity);
}

void tabi::ExecutionQueue::Add(const std::function<void()>& a_Function)
{
	std::lock_guard<std::mutex> guard(m_QueueMutex);
	m_FunctionQueue.push_back(a_Function);
}

void tabi::ExecutionQueue::Add(std::function<void()>&& a_Function)
{
	std::lock_guard<std::mutex> guard(m_QueueMutex);
	m_FunctionQueue.push_back(std::move(a_Function));
}

void tabi::ExecutionQueue::Execute()
{
	std::lock_guard<std::mutex> guard(m_QueueMutex);
	for (auto& func : m_FunctionQueue)
	{
		func();
	}
}

void tabi::ExecutionQueue::Reset()
{
	std::lock_guard<std::mutex> guard(m_QueueMutex);
	m_FunctionQueue.clear();
}

void tabi::ExecutionQueue::CopyQueue(const ExecutionQueue& a_Queue)
{
	std::lock_guard<std::mutex> guard(m_QueueMutex);

	const auto elementsToCopy = a_Queue.m_FunctionQueue.size();
	if(elementsToCopy > m_FunctionQueue.capacity() - m_FunctionQueue.size())
	{
		m_FunctionQueue.reserve(m_FunctionQueue.size() + elementsToCopy);
	}

	std::copy(a_Queue.m_FunctionQueue.begin(), a_Queue.m_FunctionQueue.end(), std::back_inserter(m_FunctionQueue));
}
