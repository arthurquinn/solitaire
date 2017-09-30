#include "stdafx.h"
#include "communication/command_result.h"

using namespace rapidjson;

CommandResult::CommandResult(const bool status, const std::string reason) : status(status), reason(reason) {}
CommandResult::~CommandResult() {}

void CommandResult::update_push(const size_t pile, const std::string card_str) {
  push_map[pile].push_back(card_str);
}

void CommandResult::update_pop(const size_t pile, size_t num_pop) {
  pop_map[pile] = num_pop;
}

const std::string CommandResult::stringify() {
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);
  writer.StartObject();
  writer.Key(RESPONSE_KEY);
  writer.String(status ? ENGINE_RESPONSE_OK : ENGINE_RESPONSE_ERROR);
  writer.Key(REASON_KEY);
  writer.String(reason.c_str());
  if (status) {
    writer.Key(UPDATE_KEY);
    writer.StartArray();
    for (const auto &update : push_map) {
      writer.StartObject();
      writer.Key(PILE_KEY);
      writer.Int(update.first);
      writer.Key(POP_KEY);
      writer.Int(pop_map[update.first]);
      writer.Key(PUSH_KEY);
      writer.StartArray();
      for (const std::string card_str : update.second) {
        writer.String(card_str.c_str());
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
