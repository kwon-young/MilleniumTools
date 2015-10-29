
#include <iostream>
#include <Eigen/Core>
#include <MiT/parser/CSV_Parser.hpp>

using namespace Eigen;

int main(int argc, char *argv[])
{
  std::cout  << std::endl;
  std::string data_directory = "C:/Users/Kwon-Young/Documents/Prog/MilleniumTools/examples/parser/resources/";
  std::vector<std::string> files;
  files.push_back("train_data.csv");
  files.push_back("train_label.csv");

  Parser::CSV_Parser myParser(data_directory, files);
  std::vector<MatrixXd> datas;
  myParser.read_csv<Eigen::MatrixXd, double>(datas);
  for (unsigned int i = 0; i < datas.size(); ++i) {
    std::cout << datas[i] << std::endl;
  }
  return 0;
}
