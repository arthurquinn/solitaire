#include "stdafx.h"
#include "response.h"

using namespace rapidjson;

Response::Response() {
  
}

Response::~Response() {

}

std::string Response::make_response(const char* text) {
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  writer.StartObject();
  writer.Key(RESPONSE_KEY);
  writer.String(text);
  writer.EndObject();
  std::string str = std::string(buffer.GetString());
  return str;
}
