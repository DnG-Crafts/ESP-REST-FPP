

// encode nonstandard chars for url compatibility

String urlEncode(String url) {
  const char *msg = url.c_str();
  const char *hex = "0123456789ABCDEF";
  String encodedMsg = "";
  while (*msg != '\0') {
    if (('a' <= *msg && *msg <= 'z') || ('A' <= *msg && *msg <= 'Z') || ('0' <= *msg && *msg <= '9') 
    || *msg == '-' || *msg == '_' || *msg == '.' || *msg == '/' || *msg == '&' || *msg == '=' || *msg == '~' || *msg == '?') {
      encodedMsg += *msg;
    } else {
      encodedMsg += '%';
      encodedMsg += hex[(unsigned char)*msg >> 4];
      encodedMsg += hex[*msg & 0xf];
    }
    msg++;
  }
  return encodedMsg;
}






// send REST command using GET

void getRESTCommand(String Command){
  if (client.connect(FPP_HOSTIP, 80)) {
    if (!Command.startsWith("/"))
    {
      Command = "/" + Command;
    }
    client.println("GET " + urlEncode(Command) + " HTTP/1.1");
    client.println("Host: " + String(FPP_HOSTIP));
    client.println("Connection: close");
    client.println();
  }
}






// send REST command and content using POST

void postRESTCommand(String Command,  char* Content){
  if (client.connect(FPP_HOSTIP, 80)) {
    if (!Command.startsWith("/"))
    {
      Command = "/" + Command;
    }
    client.println("POST " + urlEncode(Command) + " HTTP/1.1");
    client.println("Host: " + String(FPP_HOSTIP));
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(strlen(Content)));
    client.println("Connection: keep-alive");
    client.println();
    client.write(Content);
  }
}
