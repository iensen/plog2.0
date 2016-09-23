//
// Created by iensen on 9/3/16.
//


#include <plog/plogparser.h>
#include <sys/stat.h>
#include <plog/plog.h>
#include <groundplog/logger.h>


PlogParser::PlogParser(NonGroundProgramBuilder &pb)   : not_("not")
        , pb_(pb)
        , _startSymbol(0)
        , _filename("") { }

void PlogParser::parseError(Location const &loc, std::string const &token) {
    throw "not implemented yet";
}
namespace {

    struct Free {
        void operator()(char *ptr) { free(ptr); }
    };

    template<typename T>
    void report_included(T const &loc, char const *filename, Logger &log) {
        PLOG_REPORT(log, plog_warning_file_included) << loc << ": warning: already included file:\n"
                                                     << "  " << filename << "\n";
    }

    template<typename T>
    void report_not_found(T const &loc, char const *filename, Logger &log) {
        PLOG_REPORT(log, plog_error_runtime) << loc << ": error: file could not be opened:\n"
                                             << "  " << filename << "\n";
    }

#ifdef __USE_GNU

#  include <libgen.h>

#  include <sys/types.h>
#  include <sys/stat.h>

#endif

// NOTE: is there a better way?
#ifdef __USE_GNU

    std::string check_file(std::string const &filename) {
        if (filename == "-") { return filename; }
        struct stat sb;
        if (stat(filename.c_str(), &sb) != -1) {
            if ((sb.st_mode & S_IFMT) == S_IFIFO) {
                return filename;
            } else {
                std::unique_ptr<char, Free> x(canonicalize_file_name(filename.c_str()));
                if (x) { return x.get(); }
            }
        }
        return "";
    }

    std::pair<std::string, std::string> check_file(std::string const &filename, std::string const &source) {
        struct stat sb;
        if (stat(filename.c_str(), &sb) != -1) {
            if ((sb.st_mode & S_IFMT) == S_IFIFO) {
                return {filename, filename};
            } else {
                std::unique_ptr<char, Free> x(canonicalize_file_name(filename.c_str()));
                if (x) { return {x.get(), filename}; }
            }
        } else if (filename.compare(0, 1, "/", 1) != 0) {
            std::unique_ptr<char, Free> x(strdup(source.c_str()));
            std::string path = dirname(x.get());
            path.push_back('/');
            path.append(filename);
            if (stat(path.c_str(), &sb) != -1) {
                if ((sb.st_mode & S_IFMT) == S_IFIFO) {
                    return {path, path};
                } else {
                    x.reset(canonicalize_file_name(path.c_str()));
                    if (x) { return {x.get(), path}; }
                }
            }
        }
        return {"", ""};
    }

#else

    std::string check_file(std::string const &filename) {
    if (filename == "-" && std::cin.good()) {
        return filename;
    }
    if (std::ifstream(filename).good()) {
        return filename;
    }
    return "";
}

std::pair<std::string, std::string> check_file(std::string const &filename, std::string const &source) {
    if (std::ifstream(filename).good()) {
        return {filename, filename};
    }
    else {
#if defined _WIN32 || defined __WIN32__ || defined __EMX__ || defined __DJGPP__
        const char *SLASH = "/\\";
#else
        const char *SLASH = "/";
#endif
        size_t slash = source.find_last_of(SLASH);
        if (slash != std::string::npos) {
            std::string path = source.substr(0, slash + 1);
            path.append(filename);
            if (std::ifstream(path).good()) {
                return {path, path};
            }
        }
    }
    return {"", ""};
}

#endif
}

void PlogParser::pushFile(std::string &&file, Logger &log) {
    auto checked = check_file(file);
    if (!checked.empty() && !filenames_.insert(checked).second) {
        report_included("<cmd>", file.c_str(), log);
    }
    else if (checked.empty() || !push(file)) {
        report_not_found("<cmd>", file.c_str(), log);
    }
}


void PlogParser::pushStream(std::string &&name, std::unique_ptr<std::istream>, Logger &log) {
    throw "not implemented yet";
}

void PlogParser::pushBlock(std::string const &name, IdVec const &vec, std::string const &block, Logger &log) {
    throw "not implemented yet";
}

int PlogParser::lex(void *pValue, Location &loc) {
    throw "not implemented yet";
}

bool PlogParser::parseDefine(std::string const &define, Logger &log) {
    throw "not implemented yet";
}

bool PlogParser::parse(Logger &log) {
    throw "not implemented yet";
}

bool PlogParser::empty() {  throw "not implemented yet";}

void PlogParser::include(std::string file, Location const &loc, bool include, Logger &log) {
    throw "not implemented yet";
}

NonGroundProgramBuilder &PlogParser::builder() {
    throw "not implemented yet";
}

PlogParser::~PlogParser() {
    throw "not implemented yet";
}

void PlogParser::lexerError(std::string token) {
    throw "not implemented yet";
}

bool PlogParser::push(std::string const &filename, bool include) {
    throw "not implemented yet";
}

bool PlogParser::push(std::string const &file, std::unique_ptr<std::istream> in) {
    throw "not implemented yet";
}

void PlogParser::pop() {
    LexerState::pop();
}

void PlogParser::_init() {
    throw "not implemented yet";
}

void PlogParser::condition(PlogParser::Condition cond) {
    throw "not implemented yet";
}

void PlogParser::start(Location &loc) {
    throw "not implemented yet";
}

PlogParser::Condition PlogParser::condition() const {
    throw "not implemented yet";
}

std::string PlogParser::filename() const {
    throw "not implemented yet";
};

int PlogParser::lex_impl(void *pValue, Location &loc) {
    throw "not implemented yet";
}