#include <iostream>
#include "Server.h"

using namespace std;

int main(int argc, char** argv )
{
  Server _Server;
  _Server.Create_Master_Socket();
  _Server.Set_Master_Socket_Multiple();
  _Server.Type_Socket();
  _Server.Bind_Socket();
  _Server.Specify_Pending();
  _Server.Accept_Incoming();
  _Server.Start_Run();
}
