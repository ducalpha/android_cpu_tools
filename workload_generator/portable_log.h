

#if defined(USE_CHROMIUM)
#define PORTABLE_LOG LOG
#define PORTABLE_LOG_ERRNO PLOG
#elif define(USE_FIREFOX)
#define PORTABLE_LOG CHROMIUM_LOG
#define PORTABLE_LOG PortableLog
#else
#define PORTABLE_LOG(log_severity) PortableLog(log_severity)
#endif

PORTABLE_LOG(ERROR) << "Failed to do something: " << error;

PortableLog(ERROR) << "Test" << error;
