#pragma once

#include <vector>
#include <thread>
#include <future>
#include <map>


struct disk
{
  static const int block_size = 512;
  std::map<int /* what */, int /* location */> header;

  std::vector<int> phys_data;
  bool is_busy;

  int capasity, free;

  disk(int size_in_blocks)
    : capasity(size_in_blocks), free(size_in_blocks)
  {
    phys_data.resize(size_in_blocks);
  }

  bool IsBusy() const
  {
    return is_busy;
  }

  std::future<int> Read(int pos);
  std::future<int> Write(int pos, int value);

  int Capasity() const
  {
    return capasity;
  }

  int Free() const
  {
    return free;
  }
};