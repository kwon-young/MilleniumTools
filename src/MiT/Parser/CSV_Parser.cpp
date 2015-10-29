
#include <MiT/Parser/CSV_Parser.hpp>
#include <sstream>
#include <iostream>

namespace Parser
{
  CSV_Parser::CSV_Parser() :
    Abstract_Parser()
  {}

  CSV_Parser::CSV_Parser(
      const std::string &data_directory,
      const std::vector<std::string> filenames) :
    Abstract_Parser(data_directory, filenames)
  {}

  CSV_Parser::~CSV_Parser()
  {}
}

