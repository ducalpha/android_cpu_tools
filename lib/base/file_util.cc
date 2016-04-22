bool PathExists(const std::string& path) {
  return access(path.c_str(), F_OK) == 0;
}

