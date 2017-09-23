#include "stdafx.h"
#include "command_result.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

//
//// FIELD UPDATE
//
//FieldUpdate::FieldUpdate(const int pile, const int num_pop) : pile(pile), num_pop(num_pop) { }
//
//FieldUpdate::~FieldUpdate() { }

// COMMAND RESULT

CommandResult::CommandResult(const bool status, const char* reason) : status(status), reason(reason) { }

void CommandResult::update_push(const int pile, const char* card_str) {
  push_map[pile].push_back(card_str);
}

void CommandResult::update_pop(const int pile, int num_pop) {
  pop_map[pile] = num_pop;
}

const std::string CommandResult::stringify() {
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  writer.StartObject();
  writer.Key("response");
  writer.String(status ? "ok" : "error");
  writer.Key("reason");
  writer.String(reason);
  if (status) {
    writer.Key("update");
    writer.StartArray();
    for (const auto &update : push_map) {
      writer.StartObject();
      writer.Key("pile");
      writer.Int(update.first);
      writer.Key("pop");
      writer.Int(pop_map[update.first]);
      writer.Key("push");
      writer.StartArray();
      for (const char* card_str : update.second) {
        writer.String(card_str);
      }
      writer.EndArray();
      writer.EndObject();
    }
    writer.EndArray();
  }
  writer.EndObject();
  std::string str = std::string(buffer.GetString());
  return str;
}

CommandResult::~CommandResult() { }
