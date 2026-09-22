#include <fstream>
class Logger {
private:
	std::ofstream log_;
	Logger() : log_("log.txt") {
	}
	Logger& operator=(Logger&) = delete;
	Logger(const Logger&) = delete;

public:
	Logger& get_instance() {
		static Logger instance;
		return instance;
	};

	void log(const std::string& message) {
		log_ << message << std::endl;
	}

};
