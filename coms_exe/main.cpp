#include <iostream>
#include "test_lib.hpp"
#include <boost/asio.hpp>
 
using namespace boost::asio::ip;
using boost::asio::ip::udp;
using std::string;
using std::cout;
using std::endl;



int main() {
    std::cout << "Main test  \n\n";
    
    boost::asio::io_service service;
    tcp::endpoint endpoint(address::from_string("127.0.0.1"), 4000);
    tcp::socket socket(service);

    std::cout << "\n\n[Client] Connecting to server..." << std::endl;
    socket.connect(endpoint);
    std::cout << "\n\n[Client] Connection successful" << std::endl;




}   






