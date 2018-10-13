#include "client_http.hpp"
#include "server_http.hpp"
#include "Calculator.h"
#include "Calculator.cpp"
#include "Parser.h"
#include "Parser.cpp"
// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// Added for the default_resource example
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#ifdef HAVE_OPENSSL
#include "crypto.hpp"
#endif

using namespace std;
// Added for the json-example:
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main() {

  HttpServer server;
  Calculator c;
  server.config.port = 8080;

    //Gets a string as an input, and returns the evaluation
  server.resource["^/getresult$"]["POST"] = [&c](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    // Retrieve string from request:
    auto content = c.evaluate(request->content.string());

    *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
              << content;
  };

    server.resource["^/addvar$"]["POST"] = [&c](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {

        //Take the string from request
        c.addVar(request->content.string());
        string content = "Added New Variable!";

        *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;

    };

    server.resource["^/import$"]["POST"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {

        //Take the string from request
        auto content = request->content.string();

        //auto content = calculator.importData(content)
        //we can return a bool and send it as a JSON to cover exceptions.
        *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;

    };

    server.resource["^/export"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {

        //Take the string from request
        auto content = request->content.string();

        //auto content = calculator.exportData(content)
        //we can return a bool and send it as a JSON to cover exceptions.
        *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;

    };

    server.resource["^/clear"]["DELETE"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {

        //Take the string from request
        auto content = request->content.string();

        //auto content = calculator.clearVar(content)
        //we can return a bool and send it as a JSON to cover exceptions.
        *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;

    };

    server.resource["^/getvar$"]["POST"] = [&c](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {

        //returns a string in JSON style with all the variables.
        //auto content = calculator.getVars();

        string content = c.getVars();
        cout<<c.getVars();
        *response << "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " << content.length() << "\r\n\r\n"
                  << content;

    };

  //GET basic homepage
  server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    try {
      auto web_root_path = boost::filesystem::canonical("web");
      auto path = boost::filesystem::canonical(web_root_path / request->path);
      // Check if path is within web_root_path
      if(distance(web_root_path.begin(), web_root_path.end()) > distance(path.begin(), path.end()) ||
         !equal(web_root_path.begin(), web_root_path.end(), path.begin()))
        throw invalid_argument("path must be within root path");
      if(boost::filesystem::is_directory(path))
        path /= "index.html";

      SimpleWeb::CaseInsensitiveMultimap header;

#ifdef HAVE_OPENSSL
#endif

      auto ifs = make_shared<ifstream>();
      ifs->open(path.string(), ifstream::in | ios::binary | ios::ate);

      if(*ifs) {
        auto length = ifs->tellg();
        ifs->seekg(0, ios::beg);

        header.emplace("Content-Length", to_string(length));
        response->write(header);

        // Trick to define a recursive function within this scope (for example purposes)
        class FileServer {
        public:
          static void read_and_send(const shared_ptr<HttpServer::Response> &response, const shared_ptr<ifstream> &ifs) {
            // Read and send 128 KB at a time
            static vector<char> buffer(131072); // Safe when server is running on one thread
            streamsize read_length;
            if((read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount()) > 0) {
              response->write(&buffer[0], read_length);
              if(read_length == static_cast<streamsize>(buffer.size())) {
                response->send([response, ifs](const SimpleWeb::error_code &ec) {
                  if(!ec)
                    read_and_send(response, ifs);
                  else
                    cerr << "Connection interrupted" << endl;
                });
              }
            }
          }
        };
        FileServer::read_and_send(response, ifs);
      }
      else
        throw invalid_argument("could not read file");
    }
    catch(const exception &e) {
      response->write(SimpleWeb::StatusCode::client_error_bad_request, "Could not open path " + request->path + ": " + e.what());
    }
  };

  server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
    // Handle errors here
    // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
  };

  thread server_thread([&server]() {
    // Start server
    server.start();

  });
    cout<<"Calc Server has started at port 8080"<<endl;

  // Wait for server to start so that the client can connect
  this_thread::sleep_for(chrono::seconds(1));

  server_thread.join();
}
