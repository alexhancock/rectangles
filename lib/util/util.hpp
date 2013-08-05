#ifndef UTIL_H
#define	UTIL_H

#include <iostream>
#include <fstream>

class Util {
  public:
    Util(){}

    static std::string getStringFromPath(const char* path) {
      std::ifstream file;
      std::string line, buffer;
      file.open(path, std::ifstream::in);

      if (file.is_open()) {
        while (!file.eof()) {
            std::getline(file, line);
            buffer.append(line);
            buffer.append(std::string("\n"));
        }
        file.close();
        return buffer;
      } else {
        std::cout << "Unable to open file";
      }
    }

  private:
};

#endif	/* UTIL_H */
