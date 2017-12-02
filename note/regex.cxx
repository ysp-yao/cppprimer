#include <regex>
#include <string>
#include <iostream>

using namespace std;

bool valid(const smatch &m);

int main() {
  string pattern("[^c]ei");
  pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
  
  regex r(pattern, regex::icase);
  
  smatch results;
  
  string test_str = "receipt freind theif receive";
  
  // 1
  if (regex_search(test_str, results, r)) {
    cout << results.str() << endl;
  }
  
  // 2
  for (sregex_iterator it(test_str.begin(), test_str.end(), r), end_it; it != end_it; ++it) {
    cout << it->str() << endl;
  }
  
  // 3
  for (sregex_iterator it(test_str.begin(), test_str.end(), r), end_it; it != end_it; ++it) {
    auto pos = it->prefix().length();
    //cout << "=========" << pos <<endl;
    pos = pos>40 ? pos-40 : 0;

    cout << it->prefix().str().substr(pos)
         << "\n\t\t>>> " << it->str() << " <<<\n"
         << it->suffix().str().substr(0, 40)
         << endl;
  }
  
  
  // 4
  //regex r1("[[:alnum:]]+\\.(cpp|cxx|cc)", regex::icase);
  regex r1("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase);
  string filename;
  /*
  while (cin >> filename) {
    if (regex_search(filename, results, r1)) {
      cout << results.str(0) << endl;
      cout << results.str(1) << endl;
      cout << results.str(2) << endl;
    }
  }
  */
  
  // 5
  cout << "============" << endl;
  string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
  regex r2(phone);
  smatch m;
  string s = "(908) 555-1800";
//  while (getline(cin, s)) {
    for (sregex_iterator it(s.begin(), s.end(), r2), end_it; it != end_it; ++it) {
      if (valid(*it)) {
        cout << "valid: " << it->str() << endl;
      }
      else {
        cout << "not valid: " << it->str() << endl;
      }
    }
//  }
  
  // 6
  string fmt = "$2.$5.$7";
  cout << regex_replace(s, r2, fmt) << endl;
  
  // 7
  std::string s1 = "morgan (201) 555-2368 862-555-0123\ndrew (973)555.0130\nlee (609) 555-0132 2015550175 800.555-0000";
  cout << regex_replace(s1, r2, fmt) << endl;
  cout << regex_replace(s1, r2, fmt, std::regex_constants::format_no_copy) << endl;
  
  return 0;
}

bool valid(const smatch &m) {
  if (m[1].matched) {
    return m[3].matched
          && (m[4].matched==0 || m[4].str()==" ");
  }
  else {
    return !m[3].matched
          && m[4].str()==m[6].str();
  }
}