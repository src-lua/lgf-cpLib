string getHash(string code) {
  ofstream("z.cpp") << code;
  system("g++ -E -P -dD -fpreprocessed ./z.cpp"
         " | tr -d '[:space:]' | md5sum > sh");
  ifstream("sh") >> code;
  return code.substr(0, 3);
}
int main() {
  string line, context;
  stack<string> blocks({""});
  while (getline(cin, line)) {
    context = line;
    for (char c : line)
      if (c == '{') blocks.push("");
      else if (c == '}')
        context = blocks.top() + line, blocks.pop();
    cout << getHash(context) + " " + line << endl;
    blocks.top() += context;
  }
}
