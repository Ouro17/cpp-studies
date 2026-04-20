#ifndef RACE_H
#define RACE_H
#include <string_view>
#include <unordered_map>

enum class Race { Unknown, Human, Orc, Elf, Dwarf };

static const std::unordered_map<std::string_view, Race> race_map = {
    {"unknown", Race::Unknown}, {"human", Race::Human}, {"orc", Race::Orc},
    {"elf", Race::Elf},         {"dwarf", Race::Dwarf},
};

static inline Race to_race(std::string_view input) {
  auto it = race_map.find(input);
  if (it != race_map.end()) {
    return it->second;
  }

  return Race::Unknown;
}

constexpr std::string_view to_string(Race race) {
  switch (race) {
  case Race::Human:
    return "Human";
  case Race::Orc:
    return "Orc";
  case Race::Elf:
    return "Elf";
  case Race::Dwarf:
    return "Dwarf";
    break;
  default:
    return "Unknown";
  }
}

#endif