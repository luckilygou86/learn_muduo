#include "muduo/base/CurrentThread.h"
#include "muduo/base/Exception.h"
#include <functional>
#include <vector>
#include <stdio.h>
#include <signal.h>
#include <iostream>

using namespace std;

class Bar
{
 public:
  void test(std::vector<std::string> names = {})
  {
    printf("Stack:\n%s\n", muduo::CurrentThread::stackTrace(true).c_str());
    [] {
      printf("Stack inside lambda:\n%s\n", muduo::CurrentThread::stackTrace(true).c_str());
    }();
    std::function<void()> func([] {
      printf("Stack inside std::function:\n%s\n", muduo::CurrentThread::stackTrace(true).c_str());
    });
    func();

    func = std::bind(&Bar::callback, this);
    func();
    char *c = new char[10];
    delete [] c;
    c=NULL;
    cout << c[2] << endl;
    //printf("c = %s\n", c);
    //throw muduo::Exception("oops");
  }

 private:
   void callback()
   {
     printf("Stack inside std::bind:\n%s\n", muduo::CurrentThread::stackTrace(true).c_str());
   }
};

void foo()
{
  Bar b;
  b.test();
}

void back_fun(int sig)
{
  printf("Stack---------:\n%s\n", muduo::CurrentThread::stackTrace(true).c_str());
  exit(1);
}

int main()
{
  signal(SIGSEGV, back_fun);
 /*  try
  { */
    foo();
  //}
  /* catch (const muduo::Exception& ex)
  {
    printf("reason: %s\n", ex.what());
    printf("stack trace:\n%s\n", ex.stackTrace());
  } */
}
