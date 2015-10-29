
#include <MiT/Parser/Parser.hpp>

namespace Parser
{

  Abstract_Parser::Abstract_Parser() :
    _data_directory(""),
    _filenames(),
    _fps()
  {
  }

  Abstract_Parser::Abstract_Parser(
      const std::string &data_directory,
      const std::vector<std::string> filenames) :
    _data_directory(data_directory),
    _filenames(filenames.begin(), filenames.end()),
    _fps()
  {
    //std::cout << "data directory : " << _data_directory << std::endl;
    //for (unsigned int i = 0; i < _filenames.size(); ++i) {
      //std::cout << "file " << i+1 << " : " << _filenames[i] << std::endl;
    //}
  }

  Abstract_Parser::~Abstract_Parser()
  {
    for (unsigned int i = 0; i < _fps.size(); ++i) {
      if (_fps[i]->is_open())
      {
        _fps[i]->close();
      }
    }
  }

  void Abstract_Parser::add_data_file(const std::string &filename)
  {
    _filenames.push_back(filename);
  }

  void Abstract_Parser::add_data_files(const std::vector<std::string> &filenames)
  {
    for (unsigned int i = 0; i < filenames.size(); ++i) {
      add_data_file(filenames[i]);
    }
  }

  void Abstract_Parser::open_files(std::ios_base::openmode op)
  {
    std::string filename;
    _fps.clear();
    for (unsigned int i = 0; i < _filenames.size(); ++i) {
      filename = _data_directory + _filenames[i];
      std::shared_ptr<std::fstream> fp(new std::fstream);
      fp->open(filename.c_str(), op);
      _fps.push_back(fp);
      if(!_fps[i]->good())
      {
        std::cerr << "Couldn't open " << filename << std::endl;
      }
    }
  }
}
