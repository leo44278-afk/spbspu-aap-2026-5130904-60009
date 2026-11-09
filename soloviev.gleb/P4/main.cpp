#include <iostream>
#include <cstring>
#include <cstddef>
#include <new>
#include <limits>

constexpr std::size_t INITIAL_CAPACITY = 16;

char* readLine()
{
  std::size_t cap = INITIAL_CAPACITY;
  std::size_t len = 0;

  char* buf = nullptr;

  try
  {
    buf = new char[cap];
  }
  catch (const std::bad_alloc&)
  {
    return nullptr;
  }

  char c;

  while (std::cin.get(c))
  {
    if (c == '\n')
    {
      break;
    }

    if (len + 1 >= cap)
    {
      if (cap > std::numeric_limits<std::size_t>::max() / 2)
      {
        delete[] buf;
        return nullptr;
      }

      const std::size_t newCap = cap * 2;
      char* newBuf = nullptr;

      try
      {
        newBuf = new char[newCap];
      }
      catch (const std::bad_alloc&)
      {
        delete[] buf;
        return nullptr;
      }

      for (std::size_t i = 0; i < len; ++i)
      {
        newBuf[i] = buf[i];
      }

      delete[] buf;
      buf = newBuf;
      cap = newCap;
    }

    buf[len] = c;
    ++len;
  }

  if (std::cin.bad())
  {
    delete[] buf;
    return nullptr;
  }

  buf[len] = '\0';

  return buf;
}

int var13(const char* a, const char* b)
{
  for (std::size_t i = 0; a[i] != '\0'; ++i)
  {
    for (std::size_t j = 0; b[j] != '\0'; ++j)
    {
      if (a[i] == b[j])
      {
        return 1;
      }
    }
  }

  return 0;
}

std::size_t var4(const char* a, const char* b, char* res)
{
  std::size_t resLen = 0;

  for (std::size_t i = 0; a[i] != '\0'; ++i)
  {
    bool found = false;

    for (std::size_t j = 0; b[j] != '\0'; ++j)
    {
      if (a[i] == b[j])
      {
        found = true;
        break;
      }
    }

    if (found)
    {
      res[resLen] = a[i];
      ++resLen;
    }
  }

  res[resLen] = '\0';

  return resLen;
}

int main()
{
  char* str = readLine();

  if (str == nullptr)
  {
    std::cerr << "error\n";
    return 1;
  }

  const char* s1 = "aasdbs";
  const char* s2 = "abc ezxcbf";

  const std::size_t resCap = std::strlen(str) + 1;
  char* res = nullptr;

  try
  {
    res = new char[resCap];
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Memory error\n";
    delete[] str;
    return 1;
  }

  const int has = var13(str, s1);
  std::cout << has << '\n';

  var4(str, s2, res);
  std::cout << res << '\n';

  delete[] res;
  delete[] str;

  return 0;
}
