#include "crow_all.h"
using namespace std;

 int main(int argc, char const *argv[]) {
  crow::SimpleApp app;
  CROW_ROUTE(app,"/")
  ([](){
    return "<div><h1>Hello, Crow.</h1></div>" ;
  });

  // get the port from environment variable
  char* port = getenv("PORT");
  //cast it to a string
  uint16_t iPort = static_cast<uint16_t>(port != NULL? stoi(port): 18080);
  cout <<"PORT = " << iPort << "\n";
  app.port(iPort).multithreaded().run() ;
}
