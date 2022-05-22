/* file		logger.h
 */

#ifndef LOGGER_H
#define LOGGER_H

#include "stdio.h"

#define Print LOG

template <typename T>
T Argument(T value) noexcept {
	return value;
}

template <typename T>
T const * Argument(std::basic_string<T> const & value) noexcept {
	return value.c_str();
}

template <typename ... Args>
void LOG(char const * const format, Args const & ... args) noexcept {
	printf(format, Argument(args) ...);
}

inline void LOG(char const * const format) noexcept {
	printf("%s", format);
}

inline void LOG(wchar_t const * const format) noexcept {
	printf("%ls", format);
}

#endif
