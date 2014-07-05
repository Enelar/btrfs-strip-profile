#pragma once

#include "disk.h"
#include <memory>
#include <string>
#include <map>
#include <utility>

struct disk_hub
{
  struct chunk_location
  {
    char disks[2];
  };

  char next_letter = 'a';

  std::map<char, std::shared_ptr<disk>> disks;
  std::map<char, decltype(std::declval<disk>().header)> cached_header;
  std::map<int, chunk_location> header;

  void InsertDisk( int capasity );
  void RemoveDisk();

  int Capasity();

  typedef std::function<bool(const std::shared_ptr<disk> &, const std::shared_ptr<disk> &)> DiskCompareFunctor;
  std::vector<char> SortBy(DiskCompareFunctor less, bool reverse = false);

  std::vector<char> SortByCapasity(bool reverse = false)
  {
    return SortBy([](const std::shared_ptr<disk> &a, const std::shared_ptr<disk> &b)
    {
      return a->Capasity() < b->Capasity();
    }, reverse);
  }

  std::vector<char> SortByFreeSpace(bool reverse = false)
  {
    return SortBy([](const std::shared_ptr<disk> &a, const std::shared_ptr<disk> &b)
    {
      return a->Free() < b->Free();
    }, reverse);
  }
};