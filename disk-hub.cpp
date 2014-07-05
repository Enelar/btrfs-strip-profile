#include "disk-hub.h"

void disk_hub::InsertDisk(int capasity)
{
  int blocks = capasity / disk::block_size;
  char letter = next_letter++;
  disks.insert({ letter, std::make_shared<disk>(blocks) } );
}

int disk_hub::Capasity()
{
  auto disks = SortByCapasity();
  int remain = 0;
  int biggest = 0, current = 0;
  int total = 0;

  auto DiskCapasity = [this, disks](int id)
  {
    return this->disks[disks[id]]->Capasity();
  };

  while (current != disks.size())
  {
    int capasity = DiskCapasity(current);
    if (remain > capasity)
    {
      remain -= capasity;
      current++;
      continue;
    }
    remain = capasity - remain;
    total += remain;
    biggest = current;
    current++;
  }

  total -= remain; // could not be mirrored with greedy alghorythm
  return total * disk::block_size;
}

std::vector<char> disk_hub::SortBy( DiskCompareFunctor less, bool reverse)
{
  std::vector<char> keys;
  for (auto row : disks)
    keys.push_back(row.first);

  std::vector<char> ret;

  auto Compare = [reverse, less](const std::shared_ptr<disk> &a, const std::shared_ptr<disk> &b)
  {
    if (reverse)
      return less(a, b);
    return !less(a, b);
  };

  while (keys.size())
  {
    auto biggest_key = 0;
    for (auto i = 0; i < keys.size(); i++)
      if (Compare(disks[keys[biggest_key]], disks[keys[i]]))
        biggest_key = i;

    ret.push_back(keys[biggest_key]);
    keys.erase(keys.begin() + biggest_key);
  };

  return ret;
}
