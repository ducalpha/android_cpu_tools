#include "workload_generator.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"

int main(int argc, char **argv)
{

  if (argc < 3) {
    CHROMIUM_LOG(ERROR) << "Usage: " << argv[0] << " <cpu_affinity> <workload_length>\n";
    exit(EXIT_FAILURE);
  }
  
  size_t cpu_affinity;
  if (!base::StringToUint(argv[1], &cpu_affinity)) {
    CHROMIUM_LOG(ERROR) << "Failed to convert cpu_affinity to uint";
    exit(EXIT_FAILURE);
  }

  fprintf(stderr, "Set affinity to cpu %d\n", cpu_affinity);

  int workload_length;
  if (!base::StringToInt(argv[2], &workload_length)) {
    CHROMIUM_LOG(ERROR) << "Failed to convert cpu_affinity to int";
    exit(EXIT_FAILURE);
  }

  android_cpu_tools::WorkloadGenerator::RunWorkload(
                        std::vector<size_t>(1, cpu_affinity), workload_length);

  return 0;
}
