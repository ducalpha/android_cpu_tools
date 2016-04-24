// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FILES_FILE_PATH_H_
#define BASE_FILES_FILE_PATH_H_

#define FILE_PATH_LITERAL(x) x
#define PRFilePath "s"

// ducalpha: implement simple Chromium's FilePath

#include <string>

namespace base {

// An abstraction to isolate users from the differences between native
// pathnames on different platforms.
class BASE_EXPORT FilePath : public std::string {
 public:

  const std::string& value() const { return *this; }
};

}  // namespace base
#endif  // BASE_FILES_FILE_PATH_H_
