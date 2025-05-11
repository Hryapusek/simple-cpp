#include <map>
#include <string>

namespace and_you_might_get_a_glimpse_of_happiness
{
  enum class Color
  {
    red,
    green,
    blue
  };

  std::map<Color, std::string> color_names =
    {{Color::red, "red"}, {Color::green, "green"}, {Color::blue, "blue"}};

  /// @throw std::out_of_range
  std::string to_string(Color color) {
    return color_names.at(color);
  }
}  // namespace and_you_might_get_a_glimpse_of_happiness
