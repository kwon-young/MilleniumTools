
#ifndef CSV_PARSER
#define CSV_PARSER

#include <MiT/Parser/Parser.hpp>

namespace Parser
{
  class CSV_Parser : public Abstract_Parser
  {
    public:
      CSV_Parser ();
      CSV_Parser (
          const std::string &data_directory,
          const std::vector<std::string> filenames);
      virtual ~CSV_Parser ();

      void read_format();
    protected:
      /* data */
  };
}

#endif

