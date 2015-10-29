
#include <iostream>
#include <stdexcept>
#include <Eigen/Core>
#include <SFML/Graphics.hpp>
#include <MiT/parser/CSV_Parser.hpp>
#include <MiT/parser/MNIST_Parser.hpp>

using namespace Eigen;

int main(int argc, char *argv[])
{
  std::cout  << std::endl;
  std::string data_directory = "C:/Users/Kwon-Young/Documents/Prog/MilleniumTools/examples/parser/resources/";
  std::vector<std::string> files;
  std::vector<MatrixXd> datas;

  //Testing csv parser

  files.push_back("train_data.csv");
  files.push_back("train_label.csv");
  Parser::CSV_Parser myParser(data_directory, files);
  myParser.read_csv<Eigen::MatrixXd, double>(datas);
  for (unsigned int i = 0; i < datas.size(); ++i) {
    std::cout << datas[i] << std::endl;
  }

  //Testing mnist parser
  files.clear();
  files.push_back("train-images.idx3-ubyte");
  files.push_back("train-labels.idx1-ubyte");
  files.push_back("t10k-images.idx3-ubyte");
  files.push_back("t10k-labels.idx1-ubyte");
  Parser::MNIST_Parser mp(data_directory, files);
  datas.clear();
  try
  {
    mp.read_idx<MatrixXd, double>(datas);
  } catch (const std::exception & e) 
  {
    std::cerr << e.what() << std::endl;
  }

  // opening an sfml windows to show numbers
  
  sf::RenderWindow window(
      sf::VideoMode(28, 28, 32), "MNIST digit",
      sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  int *i_img = new int[datas[0].cols()];
  for (int i = 0; i < datas[0].cols(); i++) {
    i_img[i] = (int)*(datas[0].row(0).col(i).data());
  }
  Eigen::Map<Eigen::MatrixXi> data(i_img, 28, 28);
  data.transposeInPlace();

  sf::Uint8 *img = new sf::Uint8[datas[0].cols()*4];
  for (unsigned int i = 0; i < datas[0].cols(); i++) {
    img[i*4]   = (sf::Uint8)*(data.row(i/28).col(i%28).data());
    img[i*4+1] = (sf::Uint8)*(data.row(i/28).col(i%28).data());
    img[i*4+2] = (sf::Uint8)*(data.row(i/28).col(i%28).data());
    img[i*4+3] = 255;
  }

  sf::Image img_digit;
  img_digit.create(28, 28, img);
  sf::Texture txt_digit;
  txt_digit.loadFromImage(img_digit, sf::IntRect(0, 0, 28, 28));
  sf::Sprite sp_digit(txt_digit);
  while(window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      if ((event.type == sf::Event::Closed) ||
          ((event.type == sf::Event::KeyPressed) &&
           (event.key.code == sf::Keyboard::Escape)))
      {
        window.close();
        break;
      }
    }
    window.clear(sf::Color(0, 0, 0));
    window.draw(sp_digit);
    window.display();
  }

  return 0;
}
