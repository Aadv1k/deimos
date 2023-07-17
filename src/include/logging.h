#ifndef LOGGING_H
#define LOGGING_H

#ifdef _WIN32
    #define CV_WARN(...) printf("\033[33m[WARNING] "); printf(__VA_ARGS__); printf("\033[0m\n")
    #define CV_INFO(...) printf("\033[36m[INFO] "); printf(__VA_ARGS__); printf("\033[0m\n")
    #define CV_ERROR(...) printf("\033[31m[ERROR] "); printf(__VA_ARGS__); printf("\033[0m\n")
#else
    #define CV_WARN(...) printf("\033[33m[WARNING] "); printf(__VA_ARGS__); printf("\033[0m\n")
    #define CV_INFO(...) printf("\033[36m[INFO] "); printf(__VA_ARGS__); printf("\033[0m\n")
    #define CV_ERROR(...) printf("\033[31m[ERROR] "); printf(__VA_ARGS__); printf("\033[0m\n")
#endif


#endif
