
#ifndef PARSER
#define PARSER

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <Eigen/Dense>

namespace Parser
{
  class Abstract_Parser
  {
  public:
    Abstract_Parser ();
    Abstract_Parser (
        const std::string &data_directory,
        const std::vector<std::string> filnames);
    virtual ~Abstract_Parser ();

    inline void set_data_directory(const std::string &data_directory)
    {
      _data_directory = data_directory;
    }

    void add_data_file(const std::string &filename);
    void add_data_files(const std::vector<std::string> &filenames);

    void open_files();

    virtual void read_format() = 0;
  protected:
    std::string _data_directory;
    std::vector<std::string> _filenames;
    std::vector<Eigen::MatrixXd> _datas;
    std::vector<std::shared_ptr<std::fstream> > _fps;
  };
}

#endif
