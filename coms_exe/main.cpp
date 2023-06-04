#include <iostream>
#include "test_lib.hpp"

#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"


using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;


// Class for servering incomming request
class RequestHandler: public HTTPRequestHandler {
    public: 
        RequestHandler(){}

        void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
            Application& app = Application::instance();
            app.logger().information("Request from %s", request.clientAddress().toString());

            // HTML server
            response.setStatus(HTTPServerResponse::HTTP_OK);
            response.setContentType("text/html");

            std::ostream& ostr = response.send();
            ostr << "<h1>Hello world!</h1>";
            ostr.flush();

            // JSON server
            // response.setStatus(HTTPServerResponse::HTTP_OK);
            // response.setContentType("application/json"); 

        }
};


// Corresponding factory class for 'RequestHandler' class. This is passed
// to HTTP server
class RequestHandlerFactory: public HTTPRequestHandlerFactory {
    public:
        virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &) {
            return new RequestHandler;
        }  
};


//Coms HTTP server
class ComsHTTPServer: public Poco::Util::ServerApplication {
    protected:
        void initialize(Application& self) {
            loadConfiguration();
            ServerApplication::initialize(self);
        }

        void defineOptions(OptionSet& options) {
            ServerApplication::defineOptions(options);

            options.addOption(
                Option("help", "h", "display argument help information")
                    .required(false)
                    .repeatable(false)
                    .callback(OptionCallback<ComsHTTPServer>(
                        this, &ComsHTTPServer::handleHelp
                    )));
        }

        void handleHelp(const std::string& name, const std::string& value) {
            HelpFormatter helpFormatter(options());
            helpFormatter.setCommand(commandName());
            helpFormatter.setUsage("OPTIONS");
            helpFormatter.setHeader(
                "A web server that serves the current date and time.");
            helpFormatter.format(std::cout);
            stopOptionsProcessing();
            _helpRequested = true;
        }

        int main(const std::vector<std::string>& args) {
            if(!_helpRequested){
                unsigned short port = static_cast<unsigned short>(
                    config().getInt("ComsHTTPServer.port", 9980));

                ServerSocket svs(port);
                HTTPServer server(new RequestHandlerFactory, svs, new HTTPServerParams);

                server.start();
                std::cout << "\nServer Started" << std::endl;
                waitForTerminationRequest();

                std::cout << "\nServer Stoped" << std::endl;
                server.stop();
            }
            return Application::EXIT_OK;
        }

    private:
        bool _helpRequested = false;
};


//run following command in terminal, export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
int main(int argc, char** argv) {
    std::cout << "Main Test  \n\n";

    ComsHTTPServer app;
    return app.run(argc, argv);
}   






