#include "client_http.hpp"
#include "server_http.hpp"
#include "Calculator.h"
#include "Calculator.cpp"
#include "Parser.h"
#include "Parser.cpp"
#include <boost/filesystem.hpp>
#ifdef HAVE_OPENSSL
#include "crypto.hpp"
#endif

using namespace std;
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main() {

  HttpServer server;
  Calculator c;
  server.config.port = 8080;

  server.resource["^/getresult$"]["POST"] = [&c](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
      auto content = c.evaluate(request->content.string());
      *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
              << content;
  };

  server.resource["^/addvar$"]["POST"] = [&c](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
      c.addVar(request->content.string());
      string content = "Added New Variable!";
      *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;
  };

  server.resource["^/import$"]["POST"] = [&c](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
      string content = "";
      c.importSession(request->content.string());
      *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;
  };

  server.resource["^/export$"]["POST"] = [&c](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
      auto content = c.exportSession();
      *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;
  };

  server.resource["^/delvar$"]["POST"] = [&c](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {

      c.delVar(request->content.string());
      string content = "Deleted Variable!";
      *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;
  };

    server.resource["^/delall$"]["POST"] = [&c](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {

        c.delAll();
        string content = "Deleted All!";
        *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;
    };

  server.resource["^/getvar$"]["POST"] = [&c](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
      string content = c.getVars();
        cout<<c.getVars();
        *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;
    };

  //TODO add endpoint for clearing the whole thing.


  server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
  };

  thread server_thread([&server]() {
    // Start server
    server.start();

  });

  cout<<"Calc Server has started at port 8080"<<endl;

  // Wait for server to start so that the client can connect
    // MASTER Thread
  this_thread::sleep_for(chrono::seconds(1));
  server_thread.join();
}
