
class RequestHandler {
   public:
       RequestHandler();
       ~RequestHandler();
       // отправка запроса на выполнение
       void pushRequest(FuncType f, int id, int arg);
   private:
       // пул потоков
       ThreadPool m_tpool;
};
