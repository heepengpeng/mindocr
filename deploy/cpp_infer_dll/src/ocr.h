#ifndef DEPLOY_CPP_INFER_SRC_INFER_H_
#define DEPLOY_CPP_INFER_SRC_INFER_H_
#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
extern "C" DLL_EXPORT int ocr(int argc, const char *argv[]);
#endif
