#define COMMAND_BUFFER_SIZE 128
#define MAX_ARGUMENTS_COUNT 64
#define ARGUMENT_BUFFER_SIZE 128

#define DEBUG 1

#if __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #define BIN_PATH "/sbin/"
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    #define BIN_PATH "/bin/"
#else
#   error "Unknown compiler"
#endif