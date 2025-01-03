#include <iostream>
#include <boost/program_options.hpp>

int main(int argc, char *argv[]) {
  std::cout << "hi world\n";

  std::cout << "begin this\n";
  using namespace boost::program_options;
  bool is_recursive{};
  bool is_help{};

  options_description description{ "test_cmd [option] pattern p1 p2 ..." };
  try {
    description.add_options()
              ("help,h", bool_switch(&is_help), "display a help dialog")
              ("threads,t", value<int>()->default_value(4), "number of threads to use")
              ("recursive,r", bool_switch(&is_recursive), "search subdirectories recursively")
              ("pattern", value<std::string>(), "pattern to search for")
              ("paths", value<std::vector<std::string>>(), "path to search");

  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
  }
  std::cout << description;
  std::cout << "hello\n";

  system("pause");

  return 0;
}