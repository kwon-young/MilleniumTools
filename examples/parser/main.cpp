
#include <MiT/parser/CSV_Parser.hpp>

int main(int argc, char *argv[])
{
  std::string data_directory = "C:/Users/Kwon-Young/Documents/Prog/MilleniumTools/examples/parser/resources/";
  std::vector<std::string> files;
  files.push_back("train_data.csv");
  files.push_back("train_label.csv");

  Parser::CSV_Parser myParser(data_directory, files);
  return 0;
}
