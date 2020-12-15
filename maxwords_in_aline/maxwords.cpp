#include <iostream>
#include <vector>
#include <string>

/*
Given a string s and an integer k, break up the string into multiple lines 
such that each line has a length of k or less. You must break it up so that
words don't break across lines. Each line has to have the maximum possible 
amount of words. If there's no way to break the text up, then return null.

You can assume that there are no spaces at the ends of the string and 
that there is exactly one space between each word.

For example, given the string "the quick brown fox jumps over the lazy dog" 
and k = 10, you should 
return: ["the quick", "brown fox", "jumps over", "the lazy", "dog"].
 No string in the list has a length of more than 10.
*/


/*
 * Tokenize the string, using the delimiter
 */
std::vector<std::string> tokenizeString(const std::string &str, const std::string &delimit=" ") {
  if ((str.size() == 0) || (delimit.size() == 0)) {
    return {};
  }

  size_t spos = 0;
  auto pos = str.find(delimit, spos);
  std::string sstr = {};

  std::vector<std::string> vs = {};

  // Parse the string till the end
  while (pos != std::string::npos) {
    sstr = std::move(str.substr(spos, (pos - spos)));
    spos += sstr.size() + 1;
    pos = str.find(delimit, spos);
    vs.push_back(sstr);
  }

  // Add the last item to the list
  if (spos < str.size()) {
    vs.push_back(std::move(str.substr(spos)));
  }
  
  return vs;
}

int main() {
  auto sentance = std::string("the quick brown fox jumps over the lazy dog");
  const auto lineWidth = 10;

  auto vs = std::move(tokenizeString(sentance));
  std::string out = {};
  std::vector<std::string> v = {};

  // Check for best fit and construct new vector of strings
  for (const auto &e : vs) {
    if (out.size() + e.size() < lineWidth) {
      if (out.size() == 0) {
        out = e;
      } else {
        out = out + " " + e;
      }
    } else {
      v.push_back(out);
      out = e;
    }
  }

  // Push the remaining element.
  v.push_back(out);

  // Output the result.
  for (const auto &e : v) {
    std::cout << e << "(" << e.size() << ")" << "\n";
  }
}