// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

#include <string>
#include <vector>

namespace android_tools {

struct CpuClusterInfo {
  size_t min_core_id, max_core_id, min_freq, max_freq;
  std::string freq_governor;
};

class CpuInfo {
 public:
  CpuInfo();

  void PopulateClusterInfo();

  size_t MaxCoreId() const {
    return max_core_id_;
  }

  size_t MinCoreId() const {
    return min_core_id_;
  }

  // Return a chrome command line
  std::string ToChromeCommandLine() const;

 private:

  enum class FreqType : int {
    MIN,
    CURRENT,
    MAX
  };

  bool ReadMinMaxCoreIds();

  // Return min/cur/max freq
  // Return 0 in case of failure
  size_t ReadFreqOfCore(FreqType freq_type, size_t core_id);
  std::string ReadFreqGovernorOfCore(size_t core_id);

  size_t min_core_id_, max_core_id_;

  // This is sorted by max freq
  std::vector<CpuClusterInfo> cpu_cluster_infos_;
};

}  // namespace switches
