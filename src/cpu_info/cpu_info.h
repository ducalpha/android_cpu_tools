// Copyright 2016 Duc Hoang Bui, KAIST. All rights reserved.
// Licensed under MIT ($DUC_LICENSE_URL)

namespace android_tools {
namespace cpu_info {

struct CpuClusterInfo {
  size_t min_core_id, max_core_id, min_freq, max_freq;
};

class CpuInfo {
 public:
  PopulateClusterInfo();

  size_t GetMaxCoreId() {
    return max_core_id_;
  }

  size_t GetMinCoreId() {
    return min_core_id_;
  }

 private:
  size_t min_core_id_, max_core_id_;

  // This is sorted by max freq
  vector<CpuClusterInfo> cpu_cluster_infos_;
};

}  // namespace cpu_info
}  // namespace switches
