#pragma once
#include <queue>
#include <future>
#include <condition_variable>
#include <vector>
#include <thread>
#include <mutex>

#include "BlockedQueue.h"

void taskFunc(int id, int delay);

// удобное определение для сокращения кода
typedef std::function<void()> task_type;

// тип указатель на функцию, которая является эталоном для функций задач
typedef void (*FuncType) (int, int);

// пул потоков
class ThreadPool {
   public:
       // запуск
       void start();
       // остановка
       void stop();
       // проброс задач
       void push_task(FuncType f, int id, int arg);
       // функция входа для потока
       void threadFunc(int qindex);

       ThreadPool();
   private:
          // количество потоков
       int m_thread_count;
       // потоки
       std::vector<std::thread> m_threads;
       // очереди задач для потоков
       std::vector<BlockedQueue<task_type>> m_thread_queues;
       // для равномерного распределения задач
       int m_index;
};

