#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <signal.h>
#include <stdbool.h>

#if defined(_MSC_VER)
#define BREAK __debugbreak();
#else
#define BREAK raise(SIGINT)
#endif

#define ASSERT(x)                                                              \
	if (!(x))                                                                  \
		BREAK;
#define GLCall(x)                                                              \
	GLClearError();                                                            \
	x;                                                                         \
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

#endif // DEBUG_HPP
