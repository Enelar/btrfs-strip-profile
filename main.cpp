#include "disk-hub.h"

#define gb *1024

#include <iostream>

void main()
{
  disk_hub h;

  h.InsertDisk(80 gb);
  std::cout << h.Capasity() << std::endl;
  h.InsertDisk(20 gb);
  std::cout << h.Capasity() << std::endl;
  h.InsertDisk(10 gb);
  std::cout << h.Capasity() << std::endl;
  h.InsertDisk(80 gb);
  std::cout << h.Capasity() << std::endl;
}