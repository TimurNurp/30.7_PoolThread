#include "BlockedQueue.h"

    template<class T> void BlockedQueue<T>::push(T& item_){
       std::lock_guard<std::mutex> l(m_locker);
       // обычный потокобезопасный push
       m_task_queue.push(item_);
       // делаем оповещение, чтобы поток, вызвавший
       // pop проснулся и забрал элемент из очереди
       m_notifier.notify_one();
   }

   // блокирующий метод получения элемента из очереди
   template<class T> void BlockedQueue<T>::pop(T& item_) {
       std::unique_lock<std::mutex> l(m_locker);
       if (m_task_queue.empty())
           // ждем, пока вызовут push
           m_notifier.wait(l, [this]{return !m_task_queue.empty();});
       item_ = m_task_queue.front();
       m_task_queue.pop();
   }

   // неблокирующий метод получения элемента из очереди
   // возвращает false, если очередь пуста
   template<class T> bool BlockedQueue<T>::fast_pop(T& item_) {
       std::lock_guard<std::mutex> l(m_locker);
       if(m_task_queue.empty())
           // просто выходим
           return false;
       // забираем элемент
       item_ = m_task_queue.front();
       m_task_queue.pop();
       return true;
   }