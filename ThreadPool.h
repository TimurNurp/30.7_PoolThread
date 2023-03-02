#include <queue>
#include <future>
#include <condition_variable>
#include <vector>

void taskFunc(int id, int delay);
// удобное определение для сокращения кода
typedef function<void()> task_type;
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
       void threadFunc();
   private:
       // потоки
       vector<thread> m_threads;
       // поддержка синхронизации очереди
       mutex m_locker;
       // очередь задач
       queue<task_type> m_task_queue;
       // для синхронизации работы потоков
       condition_variable m_event_holder;
       // флаг для остановки работы потоков
       volatile bool m_work;
};
