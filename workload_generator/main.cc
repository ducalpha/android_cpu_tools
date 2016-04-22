#include "workload_generator.h"

#include <cstdio>
#include <vector>

int workload_length;

int main(int argc, char **argv)
{

  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <cpu_affinity> <workload_length>\n";
    exit(1);
  }
  
  int cpu_affinity = atoi(argv[1]);
  fprintf(stderr, "Set affinity to cpu %d\n", cpu_affinity);

  workload_length = atoi(argv[2]);

  browser_profiler::WorkloadGenerator::RunWorkload(
                        std::vector<int>(1, cpu_affinity), workload_length);

  return 0;
}
