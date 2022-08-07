#pragma once

#include <TabiContainers.h>
#include <TabiMacros.h>

#include <functional>
#include <mutex>

namespace tabi
{
	class ExecutionQueue
	{
	public:
		TABI_NO_COPY(ExecutionQueue);
		TABI_NO_MOVE(ExecutionQueue);

		/**
		 * @param a_InitialQueueCapacity The initial capacity of the queue
		 */
		ExecutionQueue(size_t a_InitialQueueCapacity = 64);
		~ExecutionQueue() = default;

		/**
		 * @brief Copy a function into the queue
		 */
		void Add(const std::function<void()>& a_Function);
		/**
		 * @brief Move a function into the queue
		 */
		void Add(std::function<void()>&& a_Function);

		/*
		 * @brief Execute all functions in the queue
		 * @note Does not empty the queue
		 */
		void Execute() const;

		/**
		 * @brief Clear the execution queue
		 */
		void Reset();

		/**
		 * @brief Copy another execution queue into the current queue
		 * @param a_Queue The queue to copy into the current queue
		 */
		void CopyQueue(const ExecutionQueue& a_Queue);

		inline ExecutionQueue& operator+=(const std::function<void()>& a_Function) { Add(a_Function); return *this; }
		inline ExecutionQueue& operator+=(std::function<void()>&& a_Function) { Add(a_Function); return*this; }
		inline ExecutionQueue& operator+=(const ExecutionQueue& a_Queue) { CopyQueue(a_Queue); return *this; }

	private:
		tabi::vector<std::function<void()>> m_FunctionQueue;
		mutable std::mutex m_QueueMutex;
	};
}
