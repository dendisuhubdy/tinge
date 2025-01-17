#pragma once

/*
	FLAGS:
		TINGE_PRINT_OFF  disables print function
		TINGE_ERR_OFF    disables err function
		TINGE_LOG_OFF    disables log function
		TINGE_PLAIN      disables all styles and colours
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <utility>
#include <string>
#include <stdexcept>



// Exceptions.
#define NEW_EXCEPTION_TYPE(name, default_msg)                                  \
	struct name: public std::runtime_error {                                   \
		template <typename... Ts>                                              \
		name(Ts&&... args): std::runtime_error(((std::string{args}) + ...)) {} \
		name(): std::runtime_error(default_msg) {}                             \
	};                                                                         \

namespace tinge::except {
	NEW_EXCEPTION_TYPE(SetConsoleModeError, "could not set console mode!")
}

#undef NEW_EXCEPTION_TYPE



// Platform specific stuff.
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(OS_WINDOWS)
	#define OS_WINDOWS

	#define WIN32_LEAN_AND_MEAN
	extern "C" {
		#include <windows.h>
	}

	// Ask console to use interpret ANSI escape sequences. (>=WIN10)
	namespace tinge::detail {
		struct Init {
			Init() {
				auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

				if (handle != INVALID_HANDLE_VALUE and handle != nullptr) {
					if (DWORD original_mode; GetConsoleMode(handle, &original_mode) == TRUE)
						return SetConsoleMode(handle, original_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
				}

				throw tinge::except::SetConsoleModeError();
			}
		};

		// Kind of a neat trick, allows to run code before anything else in main when constructor is called.
		// No need for any init functions.
		inline Init init{};
	}



#elif defined(__unix__) || defined(__unix) || defined(__linux__) || defined(OS_LINUX)
	#define OS_LINUX
#elif defined(__APPLE__) || defined(__MACH__) || defined(OS_MAC)
	#define OS_MAC
#endif



// Styles and colours.
namespace tinge {
	// Colours.
	#ifndef TINGE_PLAIN
		namespace fg {
			constexpr auto reset   = "\033[39m";
			constexpr auto grey    = "\033[38m";
			constexpr auto gray    = tinge::fg::grey;
			constexpr auto white   = "\033[37m";
			constexpr auto cyan    = "\033[36m";
			constexpr auto magenta = "\033[35m";
			constexpr auto blue    = "\033[34m";
			constexpr auto yellow  = "\033[33m";
			constexpr auto green   = "\033[32m";
			constexpr auto red     = "\033[31m";
			constexpr auto black   = "\033[30m";

			namespace bright {
				constexpr auto reset   = tinge::fg::reset;
				constexpr auto grey    = "\033[98m";
				constexpr auto gray    = tinge::fg::bright::grey;
				constexpr auto white   = "\033[97m";
				constexpr auto cyan    = "\033[96m";
				constexpr auto magenta = "\033[95m";
				constexpr auto blue    = "\033[94m";
				constexpr auto yellow  = "\033[93m";
				constexpr auto green   = "\033[92m";
				constexpr auto red     = "\033[91m";
				constexpr auto black   = "\033[90m";
			}

			namespace dim {
				constexpr auto reset   = tinge::fg::reset;
				constexpr auto grey    = "\033[2;98m";
				constexpr auto gray    = tinge::fg::dim::grey;
				constexpr auto white   = "\033[2;97m";
				constexpr auto cyan    = "\033[2;96m";
				constexpr auto magenta = "\033[2;95m";
				constexpr auto blue    = "\033[2;94m";
				constexpr auto yellow  = "\033[2;93m";
				constexpr auto green   = "\033[2;92m";
				constexpr auto red     = "\033[2;91m";
				constexpr auto black   = "\033[2;90m";
			}
		}

		namespace bg {
			constexpr auto reset   = "\033[49m";
			constexpr auto grey    = "\033[48m";
			constexpr auto gray    = tinge::bg::grey;
			constexpr auto white   = "\033[47m";
			constexpr auto cyan    = "\033[46m";
			constexpr auto magenta = "\033[45m";
			constexpr auto blue    = "\033[44m";
			constexpr auto yellow  = "\033[43m";
			constexpr auto green   = "\033[42m";
			constexpr auto red     = "\033[41m";
			constexpr auto black   = "\033[40m";

			namespace bright {
				constexpr auto reset   = tinge::bg::reset;
				constexpr auto grey    = "\033[108m";
				constexpr auto gray    = tinge::bg::bright::grey;
				constexpr auto white   = "\033[107m";
				constexpr auto cyan    = "\033[106m";
				constexpr auto magenta = "\033[105m";
				constexpr auto blue    = "\033[104m";
				constexpr auto yellow  = "\033[103m";
				constexpr auto green   = "\033[102m";
				constexpr auto red     = "\033[101m";
				constexpr auto black   = "\033[100m";
			}
		}

	#else
		namespace fg {
			constexpr auto reset   = "";
			constexpr auto grey    = "";
			constexpr auto gray    = tinge::fg::grey;
			constexpr auto white   = "";
			constexpr auto cyan    = "";
			constexpr auto magenta = "";
			constexpr auto blue    = "";
			constexpr auto yellow  = "";
			constexpr auto green   = "";
			constexpr auto red     = "";
			constexpr auto black   = "";

			namespace bright {
				constexpr auto reset   = tinge::fg::reset;
				constexpr auto grey    = "";
				constexpr auto gray    = tinge::fg::bright::grey;
				constexpr auto white   = "";
				constexpr auto cyan    = "";
				constexpr auto magenta = "";
				constexpr auto blue    = "";
				constexpr auto yellow  = "";
				constexpr auto green   = "";
				constexpr auto red     = "";
				constexpr auto black   = "";
			}

			namespace dim {
				constexpr auto reset   = tinge::fg::reset;
				constexpr auto grey    = "";
				constexpr auto gray    = tinge::fg::dim::grey;
				constexpr auto white   = "";
				constexpr auto cyan    = "";
				constexpr auto magenta = "";
				constexpr auto blue    = "";
				constexpr auto yellow  = "";
				constexpr auto green   = "";
				constexpr auto red     = "";
				constexpr auto black   = "";
			}
		}

		namespace bg {
			constexpr auto reset   = "";
			constexpr auto grey    = "";
			constexpr auto gray    = tinge::bg::grey;
			constexpr auto white   = "";
			constexpr auto cyan    = "";
			constexpr auto magenta = "";
			constexpr auto blue    = "";
			constexpr auto yellow  = "";
			constexpr auto green   = "";
			constexpr auto red     = "";
			constexpr auto black   = "";

			namespace bright {
				constexpr auto reset   = tinge::bg::reset;
				constexpr auto grey    = "";
				constexpr auto gray    = tinge::bg::bright::grey;
				constexpr auto white   = "";
				constexpr auto cyan    = "";
				constexpr auto magenta = "";
				constexpr auto blue    = "";
				constexpr auto yellow  = "";
				constexpr auto green   = "";
				constexpr auto red     = "";
				constexpr auto black   = "";
			}
		}
	#endif



	// Styles.
	#ifndef TINGE_PLAIN
		constexpr auto bold    = "\033[1m";
		constexpr auto reverse = "\033[7m";
	#else
		constexpr auto bold    = "";
		constexpr auto reverse = "";
	#endif


	// Reset colours and style.
	constexpr auto reset        = "\033[0;49;39m";
	constexpr auto reset_colour = "\033[49;39m";
	constexpr auto reset_style  = "\033[0m";


	// Presets.
	namespace detail {
		// Just used as tags.
		struct Notice  {};
		struct Warn    {};
		struct Error   {};
		struct Success {};


		// Overload operator<<
		inline std::ostream& operator<<(std::ostream& os, Notice) {
			return (os << tinge::bold << tinge::fg::white);
		}

		inline std::ostream& operator<<(std::ostream& os, Warn) {
			return (os << tinge::bold << tinge::fg::blue);
		}

		inline std::ostream& operator<<(std::ostream& os, Error) {
			return (os << tinge::bold << tinge::fg::red);
		}

		inline std::ostream& operator<<(std::ostream& os, Success) {
			return (os << tinge::bold << tinge::fg::green);
		}


		// Instantiate.
		constexpr detail::Notice  notice;
		constexpr detail::Warn    warn;
		constexpr detail::Error   error;
		constexpr detail::Success success;
	}
}




// Core print functions.
namespace tinge {
	// Print to stdout.
	template <typename... Ts> inline std::ostream& print(Ts&&... args) {
		#ifndef TINGE_PRINT_OFF
			return ((std::cout << tinge::reset) << ... << std::forward<Ts>(args)) << tinge::reset;
		#else
			return std::cout;
		#endif
	}


	// Print to buffered stderr.
	template <typename... Ts> inline std::ostream& log(Ts&&... args) {
		#ifndef TINGE_LOG_OFF
			return ((std::clog << tinge::reset) << ... << std::forward<Ts>(args)) << tinge::reset;
		#else
			return std::clog;
		#endif
	}


	// Print to stderr.
	template <typename... Ts> inline std::ostream& err(Ts&&... args) {
		#ifndef TINGE_ERR_OFF
			return ((std::cerr << tinge::reset) << ... << std::forward<Ts>(args)) << tinge::reset;
		#else
			return std::cerr;
		#endif
	}
}





// Helper print functions.
namespace tinge {
	// Symbols for special print functions.
	namespace detail::symbol {
		constexpr auto notice  = "[-] ";
		constexpr auto warn    = "[*] ";
		constexpr auto error   = "[!] ";
		constexpr auto success = "[^] ";
	}


	// Strong type to signal to the below functions that something should be printed before special symbol.
	template <typename T>
	struct before {
		using value_type = T;
		const T& s;
		before(const T& s_): s(s_) {}
	};

	template <typename T> std::ostream& operator<<(std::ostream& os, const before<T>& s) {
		return (os << s.s);
	}





	// fancy printing functions
	template <typename T, typename... Ts> inline std::ostream& notice(T&& arg, Ts&&... args) {
		return tinge::log(detail::notice, detail::symbol::notice, tinge::reset, std::forward<T>(arg), std::forward<Ts>(args)...);
	}

	template <typename T, typename... Ts> inline std::ostream& warn(T&& arg, Ts&&... args) {
		return tinge::log(detail::warn, detail::symbol::warn, tinge::reset, std::forward<T>(arg), std::forward<Ts>(args)...);
	}

	template <typename T, typename... Ts> inline std::ostream& error(T&& arg, Ts&&... args) {
		return tinge::err(detail::error, detail::symbol::error, tinge::reset, std::forward<T>(arg), std::forward<Ts>(args)...);
	}

	template <typename T, typename... Ts> inline std::ostream& success(T&& arg, Ts&&... args) {
		return tinge::log(detail::success, detail::symbol::success, tinge::reset, std::forward<T>(arg), std::forward<Ts>(args)...);
	}




	// const r-value ref
	template <typename T, typename... Ts> inline std::ostream& notice(before<T>& arg, Ts&&... args) {
		return tinge::log(arg, detail::notice, detail::symbol::notice, tinge::reset, std::forward<Ts>(args)...);
	}

	template <typename T, typename... Ts> inline std::ostream& warn(before<T>& arg, Ts&&... args) {
		return tinge::log(arg, detail::warn, detail::symbol::warn, tinge::reset, std::forward<Ts>(args)...);
	}

	template <typename T, typename... Ts> inline std::ostream& error(before<T>& arg, Ts&&... args) {
		return tinge::err(arg, detail::error, detail::symbol::error, tinge::reset, std::forward<Ts>(args)...);
	}

	template <typename T, typename... Ts> inline std::ostream& success(before<T>& arg, Ts&&... args) {
		return tinge::log(arg, detail::success, detail::symbol::success, tinge::reset, std::forward<Ts>(args)...);
	}



	// r-value overloads of above.
	template <typename T, typename... Ts> inline std::ostream& notice(before<T>&& arg, Ts&&... args) {
		return tinge::log(arg, detail::notice, detail::symbol::notice, tinge::reset, std::forward<Ts>(args)...);
	}

	template <typename T, typename... Ts> inline std::ostream& warn(before<T>&& arg, Ts&&... args) {
		return tinge::log(arg, detail::warn, detail::symbol::warn, tinge::reset, std::forward<Ts>(args)...);
	}

	template <typename T, typename... Ts> inline std::ostream& error(before<T>&& arg, Ts&&... args) {
		return tinge::err(arg, detail::error, detail::symbol::error, tinge::reset, std::forward<Ts>(args)...);
	}

	template <typename T, typename... Ts> inline std::ostream& success(before<T>&& arg, Ts&&... args) {
		return tinge::log(arg, detail::success, detail::symbol::success, tinge::reset, std::forward<Ts>(args)...);
	}




	// Newline variants.
	template <typename... Ts> inline std::ostream& println(Ts&&... args) {
		return tinge::print(std::forward<Ts>(args)..., '\n');
	}

	template <typename... Ts> inline std::ostream& logln(Ts&&... args) {
		return tinge::log(std::forward<Ts>(args)..., '\n');
	}

	template <typename... Ts> inline std::ostream& errln(Ts&&... args) {
		return tinge::err(std::forward<Ts>(args)..., '\n');
	}

	template <typename... Ts> inline std::ostream& noticeln(Ts&&... args) {
		return tinge::notice(std::forward<Ts>(args)..., '\n');
	}

	template <typename... Ts> inline std::ostream& warnln(Ts&&... args) {
		return tinge::warn(std::forward<Ts>(args)..., '\n');
	}

	template <typename... Ts> inline std::ostream& errorln(Ts&&... args) {
		return tinge::error(std::forward<Ts>(args)..., '\n');
	}

	template <typename... Ts> inline std::ostream& successln(Ts&&... args) {
		return tinge::success(std::forward<Ts>(args)..., '\n');
	}
}




// Utility functions.
namespace tinge {
	namespace details {
		// unsafe, can be called like: repeat(5, 'n') or repeat('n', 5)
		inline std::string repeat(char c, std::string::size_type n) {
			return std::string(n, c);
		}
	}


	// std::string constructor does not allow repeating a string so
	// this function implements it.
	inline std::string repeat(const std::string& c, std::string::size_type n) {
		if (not n)
			return ""; // Check for 0.

		std::string out = c;
		out.reserve(c.size() * n);

		for (n--; n > 0; n--)
			out += c;

		return out;
	}

	inline std::string space(std::string::size_type n = 1) {
		return details::repeat(' ', n);
	}

	inline std::string tab(std::string::size_type n = 1) {
		return details::repeat('\t', n);
	}

	inline std::string line(std::string::size_type n = 1) {
		return details::repeat('\n', n);
	}
}

