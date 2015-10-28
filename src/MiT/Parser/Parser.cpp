
#include <MiT/Parser/Parser.hpp>
#include <iostream>

namespace Parser
{

  Abstract_Parser::Abstract_Parser() :
    _data_directory(""),
    _filenames(),
    _datas(),
    _fps()
  {
  }

  Abstract_Parser::Abstract_Parser(
      const std::string &data_directory,
      const std::vector<std::string> filenames) :
    _data_directory(data_directory),
    _filenames(filenames.begin(), filenames.end()),
    _datas(),
    _fps()
  {
    std::cout << "data directory : " << _data_directory << std::endl;
    for (unsigned int i = 0; i < _filenames.size(); ++i) {
      std::cout << "file " << i+1 << " : " << _filenames[i] << std::endl;
    }
  }

  Abstract_Parser::~Abstract_Parser()
  {
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

  void Abstract_Parser::open_files()
  {
    std::string filename;
    _fps.clear();
    for (unsigned int i = 0; i < _filenames.size(); ++i) {
      filename = _data_directory + _filenames[i];
      std::shared_ptr<std::fstream> fp(new std::fstream);
      fp->open(filename.c_str(), std::ios_base::in);
      _fps.push_back(fp);
      if(!_fps[i]->good())
      {
        std::cerr << "Couldn't open " << filename << std::endl;
      }
    }
  }
}
