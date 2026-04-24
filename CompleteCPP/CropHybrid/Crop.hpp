#ifndef CROP_H
#define CROP_H

#include <format>

class Crop {
public:
  Crop(int height, int yield, int droughtResistance);

  int getHeight() const;
  int getYield() const;
  int getDroughtResistance() const;
  int getScore() const;

  Crop &operator=(const Crop &other) = default;
  Crop operator+(const Crop &other) const;
  bool operator==(const Crop &other);
  bool operator!=(const Crop &other);
  bool operator<(const Crop &other);
  bool operator>(const Crop &other);
  bool operator>=(const Crop &other);
  bool operator<=(const Crop &other);

private:
  int height{};
  int yield{};
  int droughtResistance{};
};

template <> struct std::formatter<Crop> {
  constexpr auto parse(std::format_parse_context &context) {
    return context.begin();
  }

  auto format(const Crop &crop, std::format_context &context) const {
    return std::format_to(
        context.out(),
        "Crop(Height: {}, Yield: {}, DroughtResistance: {}, Score: {})",
        crop.getHeight(), crop.getYield(), crop.getDroughtResistance(),
        crop.getScore());
  }
};

#endif