
#ifndef MNIST_PARSER
#define MNIST_PARSER

#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <cassert>
#include <Eigen/Core>
#include <MiT/Parser/Parser.hpp>

namespace Parser
{
  class MNIST_Parser : public Abstract_Parser
  {
    public:
      MNIST_Parser ();
      MNIST_Parser (
          const std::string &data_directory,
          const std::vector<std::string> &filenames);
      virtual ~MNIST_Parser ();

      uint32_t toLSB(unsigned char* nbr)
      {
        int dec = 24;
        uint32_t temp = 0;
        for (int i = 0; i < 4; ++i) {
          temp |= nbr[i] << dec;
          dec -= 8;
        }
        return temp;
      }

      template<typename MatrixXT, typename T>
      void read_idx(std::vector<MatrixXT> &datas)
      {
        if(_fps.size() == 0)
        {
          open_files(std::ios::in | std::ios::binary);
        }
        uint32_t magic;
        int size = 4, header_size = 0;;
        unsigned char * buffer = new unsigned char [size];
        uint32_t *header = NULL;
        std::shared_ptr<std::fstream> f;
        std::string error;
        for (unsigned int i = 0; i < _fps.size(); ++i) {
          std::cout << "reading " << _filenames[i] << std::endl;
          f = _fps[i];
          f->read((char*)buffer, size);
          magic = toLSB(buffer);
          if (!(magic == 0x803 | magic == 0x801))
          {
            error = "the file " + _filenames[i] + " is not in idx format";
            throw std::logic_error(error);
          }
          header_size = buffer[3];
          header = new uint32_t[header_size];
          for (int j = 0; j < header_size; ++j) {
            f->read((char*)buffer, size);
            header[j] = toLSB(buffer);
          }
          switch (header_size) {
            case 1:
              datas.push_back(MatrixXT());
              read_idx1<MatrixXT, T>(f, datas[i], header, header_size);
              break;
            case 3:
              datas.push_back(MatrixXT());
              read_idx3<MatrixXT, T>(f, datas[i], header, header_size);
              break;
            default:
              error = "format of file " + _filenames[i] + " is unknown !";
              throw std::logic_error(error);
          }
        }
        delete[] buffer;
        delete[] header;
      }

      template<typename MatrixXT, typename T>
      void read_idx1(
          std::shared_ptr<std::fstream> f,
          MatrixXT &data,
          uint32_t *header,
          int header_size)
      {
        assert(header_size == 1);
        unsigned int data_size = header[0];
        data.resize(data_size, 1);
        unsigned char *char_data = new unsigned char[data_size];
        f->read((char*)char_data, data_size);
        for (unsigned int i = 0; i < data_size; i++) {
          data.row(i).col(0) << (T)(char_data[i]);
        }
        delete[] char_data;
      }

      template<typename MatrixXT, typename T>
      void read_idx3(
          std::shared_ptr<std::fstream> f,
          MatrixXT &data,
          uint32_t *header,
          int header_size)
      {
        assert(header_size == 3);
        unsigned int row = header[0], col = header[1]*header[2];
        unsigned int data_size = row * col;
        data.resize(row, col);
        unsigned char *char_data = new unsigned char[data_size];
        f->read((char*)char_data, data_size);
        for (unsigned int i = 0; i < row; i++) {
          for (unsigned int j = 0; j < col; j++) {
            data.row(i).col(j) << char_data[i*col+j];
          }
        }
        delete[] char_data;
      }
    protected:
      /* data */
  };
}
#endif
