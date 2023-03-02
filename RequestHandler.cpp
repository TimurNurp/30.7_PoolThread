#include "RequestHandler.h"

RequestHandler::RequestHandler() {
   m_tpool.start();
}
RequestHandler::~RequestHandler() {
   m_tpool.stop();
}
void RequestHandler::pushRequest(FuncType f, int id, int arg) {
   m_tpool.push_task(f, id, arg);
}
