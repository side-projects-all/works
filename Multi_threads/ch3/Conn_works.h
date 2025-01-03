#include <iostream>
#include <mutex>

class Conn_works {
private:
  unsigned short port;
  std::once_flag conn_init_flag;

  void open_conn() {
    std::cout << "init connection\n";
  }

public:
  Conn_works(unsigned short prt) : port{ prt } {}

  void send_data() {
    std::call_once(conn_init_flag, &Conn_works::open_conn, this);
    std::cout << "start to send data\n";
  }

  void receive_data() {
    std::call_once(conn_init_flag, &Conn_works::open_conn, this);
    std::cout << "start to receive data\n";
  }
};