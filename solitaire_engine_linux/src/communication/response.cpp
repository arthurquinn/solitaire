#include "stdafx.h"
#include "communication/response.h"

Response::Response() {}

const std::string Response::make_response(const char* text) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  writer.StartObject();
  writer.Key(RESPONSE_KEY);
  writer.String(text);
  writer.EndObject();
  std::string str = std::string(buffer.GetString());
  return str;
}

Response::~Response() {}
