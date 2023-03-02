#include "RequestHandler.h"
#include <iostream>

// функция, выполняющая задачу
void taskFunc(int id, int delay){
   std::mutex coutLocker;
   // имитируем время выполнения задачи
   std::this_thread::sleep_for(std::chrono::seconds(delay));
   // выводим информацию о завершении
   std::unique_lock<std::mutex> l(coutLocker);
   std::cout << "task " << id << " made by thread_id " << std::this_thread::get_id() << std::endl;
}


int main()
{
   std::srand(0);
   for(int i=0; i<20; i++)
      taskFunc(i, 1 + std::rand()%4);
      
//unsigned int n=std::thread::hardware_concurrency();
// std::cout << n << std::endl;
    return 0;

}
