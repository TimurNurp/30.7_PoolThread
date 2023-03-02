#pragma once
#include <mutex>
#include <condition_variable>
#include <queue>

template<class T>
class BlockedQueue {
   public:
   void push(T& item_);
   
   // блокирующий метод получения элемента из очереди
   void pop(T& item_) ;

   // неблокирующий метод получения элемента из очереди
   // возвращает false, если очередь пуста
   bool fast_pop(T& item_);

   private:
       std::mutex m_locker;
       // очередь задач
       std::queue<T> m_task_queue;
       // уведомитель
       std::condition_variable m_notifier;
};