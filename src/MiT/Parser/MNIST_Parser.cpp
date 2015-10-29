
#include <MiT/Parser/MNIST_Parser.hpp>

namespace Parser
{
  MNIST_Parser::MNIST_Parser () :
    Abstract_Parser()
  {}

  MNIST_Parser::MNIST_Parser (
      const std::string &data_directory,
      const std::vector<std::string> &filenames) :
    Abstract_Parser(data_directory, filenames)
  {}

  MNIST_Parser::~MNIST_Parser ()
  {}

}
