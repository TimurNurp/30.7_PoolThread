#include "ThreadPool.h"

void ThreadPool::start() {
   m_work = true;
   for(int i=0;i<4; i++) {
       m_threads.push_back(thread(&ThreadPool::threadFunc, this));
   }
}

void ThreadPool::stop() {
   m_work = false;
   m_event_holder.notify_all();
   for(auto& t: m_threads) {
       t.join();
   }
}

void ThreadPool::push_task(FuncType f, int id, int arg) {
   lock_guard<mutex> l(m_locker);
   task_type new_task([=] {f(id, arg);});
   m_task_queue.push(new_task);
   // оповещаем случайный поток о новой задаче
   m_event_holder.notify_one();
}

void ThreadPool::threadFunc() {
   while(true) {
       // обработка очередной задачи
       task_type task_to_do;
       {
           unique_lock<mutex> l(m_locker);
           if(m_task_queue.empty() && !m_work)
               // очередь пуста и взведен флаг — выходим
               return;
           if (m_task_queue.empty()) {
               // очередь пуста — ждем события
               m_event_holder.wait(l, [&](){return !m_task_queue.empty() || !m_work;});
           }
           if(!m_task_queue.empty()) {
               // нужно снова проверить на пустоту, ведь могли
               // проснуться по !work
               task_to_do = m_task_queue.front();
               m_task_queue.pop();
           }
       }
       // выполняем задачу, вызвав функтор
       task_to_do();
   }
}
