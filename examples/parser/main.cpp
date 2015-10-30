
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
  std::vector<MatrixXi> datas;

  //Testing csv parser

  files.push_back("train_data.csv");
  files.push_back("train_label.csv");
  Parser::CSV_Parser myParser(data_directory, files);
  myParser.read_csv<Eigen::MatrixXi, int>(datas);
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
    mp.read_idx<MatrixXi, int>(datas);
  } catch (const std::exception & e) 
  {
    std::cerr << e.what() << std::endl;
  }

  // opening an sfml windows to show numbers
  
  sf::RenderWindow window(
      sf::VideoMode(280, 280, 32), "MNIST digit",
      sf::Style::Titlebar | sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  std::vector<std::vector<uint8_t> > images;
  mp.post_process<MatrixXi, int>(datas[0], images, 28, 28, 100);

  //sf::Image img_digit;
  //img_digit.create(28, 28, images[0].data());
  //sf::Texture txt_digit;
  //txt_digit.loadFromImage(img_digit, sf::IntRect(0, 0, 28, 28));
  //sf::Sprite sp_digit(txt_digit);

  std::vector<sf::Image> imgs_digit(100, sf::Image());
  std::vector<sf::Texture> txts_digit(100, sf::Texture());
  std::vector<sf::Sprite> sps_digit;
  for (unsigned int i = 0; i < images.size(); ++i) {
    imgs_digit[i].create(28, 28, images[i].data());
    txts_digit[i].loadFromImage(imgs_digit[i], sf::IntRect(0, 0, 28, 28));
    sps_digit.push_back(sf::Sprite(txts_digit[i]));
  }

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
    unsigned int x=0, y=0, inc = 28;
    for (unsigned int i = 0; i < sps_digit.size(); ++i) {
      sps_digit[i].setPosition(x, y);
      window.draw(sps_digit[i]);
      x+=inc;
      if (x > window.getSize().x-inc)
      {
        x = 0;
        y += inc;
      }
    }
    window.display();
  }

  return 0;
}
