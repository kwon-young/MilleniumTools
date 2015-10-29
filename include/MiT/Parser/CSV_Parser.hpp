
#ifndef CSV_PARSER
#define CSV_PARSER

#include <iostream>
#include <Eigen/Core>
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

      template<typename MatrixXT, typename T>
      void read_csv(std::vector<MatrixXT> &datas)
      {
        if(_fps.size() == 0)
        {
          open_files();
        }
        std::string s;
        int row, col;
        T nbr;
        datas.clear();
        for (unsigned int i = 0; i < _fps.size(); ++i) {
          std::getline(*(_fps[i]), s);
          std::istringstream iss(s);
          iss >> row;
          iss.get();
          iss >> col;
          datas.push_back(MatrixXT(row, col));
          for (int j = 0; j < row; ++j) {
            std::getline(*(_fps[i]), s);
            std::istringstream iss2(s);
            for (int k = 0; k < col; ++k) {
              iss2 >> nbr;
              iss2.get();
              datas[i].row(j).col(k) << nbr;
            }
          }
        }
      }
    protected:
      /* data */
  };
}

#endif

