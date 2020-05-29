#include <iostream>
using namespace std;

enum event{
  e0=0,
  e1=1,
  e2=2,
  e3=3,
};

enum state{
  s0=0,
  s1=1,
  s2=2,
  s3=3,
};

state tranTable [][4]= {
      //e1, e2, e3
  {s0, s0, s0, s0},
  {s0, s1, s3, s2}, //s1 这一行表示，s1 收到事件e1 e2 e3 ，分别切换到 s1, s3, s2
  {s0, s2, s1, s3}, //s2 这一行表示，s2 收到事件e1 e2 e3 ，分别切换到 s2, s1, s3
  {s0, s3, s2, s1}  //s3 这一行表示，s3 收到事件e1 e2 e3 ，分别切换到 s3, s2, s1
};

typedef const char*(*action)();

const char* action1(){
  return "action1";
}

const char* action2(){
  return "action2";
}

const char* action3(){
  return "action3";
}

action actionTable[][4] {
  {NULL, NULL, NULL, NULL}, 
  {NULL, action1, action3, action2}, 
  {NULL, action2, action1, action3},
  {NULL, action3, action2, action1}
};

void print(state src, event e) {
  printf("state [%d] recvd [%d] goto [%d] action[%s]\n",
  src, e, tranTable[src][e], actionTable[src][e]());
}

int main() {
  print(s1, e1);
  print(s1, e2);
  print(s1, e3);
  printf("=========\n");

  print(s2, e1);
  print(s2, e2);
  print(s2, e3);
  printf("=========\n");

  print(s3, e1);
  print(s3, e2);
  print(s3, e3);
  printf("=========\n");
}	
