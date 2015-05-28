
#include "btm_td_helper.h"
#include "stdafx.h"

namespace btm_td {

	std::string PATH_ASSETS("./assets");
	std::string PATH_ASSETS_MIDI("./assets/midi");
	std::string PATH_LOG("./log");
	std::string PATH_DATA("./data");
	std::string LOG_FILE("btm_td.log");

	BTM_TD_DLL_API std::shared_ptr<spdlog::logger> logger;
	BTM_TD_DLL_API std::shared_ptr<spdlog::logger> console;

	void InitLogger(spdlog::level::level_enum level){
		InitLogger("", level);
	}
	void InitLogger(const char * filename, spdlog::level::level_enum level, size_t maxFileSize, size_t maxFile, bool forceFlush){
		spdlog::set_level(spdlog::level::debug);
		console = spdlog::stdout_logger_mt("console");
		if (filename == ""){
			logger = spdlog::stdout_logger_mt("logger");
		}
		else {
			try{
				logger = spdlog::rotating_logger_mt("logger", filename, maxFileSize, maxFile, forceFlush);
			}
			catch (spdlog::spdlog_ex ex) {
				logger = spdlog::stdout_logger_mt("logger_console");
				logger->error(ex.what());
			}
		}
	}

	namespace helper {

		void ListAllMidi(const char *dirname, std::vector<std::string> *found) {
			DIR *dir;
			struct dirent *ent;
			std::string stmp;
			std::string path;

			/* Open directory stream */
			dir = opendir(dirname);
			if (dir != NULL) {

				/* Print all files and directories within the directory */
				while ((ent = readdir(dir)) != NULL) {
					stmp = (std::string(ent->d_name)).substr(0, 1);
					if (ent->d_type == DT_DIR && stmp != "." && stmp != "_"){
						path = std::string(dirname);
						if (path.at(path.length() - 1) != '/')
							path += "/";
						path += ent->d_name;
						ListAllMidi(path.c_str(), found);
					}
					else if (ent->d_namlen > 4) {
						stmp = (std::string(ent->d_name)).substr(ent->d_namlen - 4, 4);
						if (stmp == ".mid"){
							path = std::string(dirname);
							if (path.at(path.length() - 1) != '/')
								path += "/";
							path += ent->d_name;
							found->push_back(path);
						}
					}
				}

				closedir(dir);
			}
		}

		const char * cpConstChar(const char * other){
			int len = strlen(other);
			char * cp = (char*)malloc((len + 1) * sizeof(char));
			strcpy_s(cp, len + 1, other);
			return cp;
		}

	}

}