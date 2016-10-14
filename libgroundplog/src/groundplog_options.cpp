
#include <groundplog/cli/groundplog_options.h>
#include <program_opts/program_options.h>
#include <program_opts/errors.h>

namespace GroundPlog {
    namespace Cli {


        enum OptionKey {
            detail__before_options = -1,
            meta_config = 0,
#define GROUNDPLOG_CONTEXT_OPTIONS  GRP(option_category_nodes_end,   option_category_context_begin),
#define GROUNDPLOG_GLOBAL_OPTIONS   GRP(option_category_context_end, option_category_global_begin),
#define GROUNDPLOG_SOLVER_OPTIONS   GRP(option_category_global_end,  option_category_solver_begin),
#define GROUNDPLOG_SEARCH_OPTIONS   GRP(option_category_solver_end,  option_category_search_begin),
#define GROUNDPLOG_ASP_OPTIONS      GRP(option_category_search_end,  option_category_asp_begin),
#define GROUNDPLOG_SOLVE_OPTIONS    GRP(option_category_asp_end,     option_category_solve_begin),
#define OPTION(k,e,...) opt_##k,
#define GROUP_BEGIN(X) X
#define GRP(X, Y) X, Y = X, detail__before_##Y = X - 1
#include <groundplog/cli/groundplog_cli_options.inl>
            option_category_solve_end,
            detail__num_options = option_category_solve_end,
            meta_tester = detail__num_options
        };

        bool GroundPlog::Cli::GroundPlogCliConfig::validate() {
            // nothing to validate
            return true;
        }

        bool GroundPlog::Cli::GroundPlogCliConfig::finalize(const ProgramOptions::ParsedOptions &parsed,
                                                            bool applyDefaults) {
            ParsedOpts temp;
            return finalizeAppConfig(this, parsed, applyDefaults);

        }

        bool GroundPlog::Cli::GroundPlogCliConfig::finalizeAppConfig(GroundPlog::GroundPlogConfig::UserConfig *active,
                                                                     const GroundPlog::Cli::GroundPlogCliConfig::ParsedOpts &exclude,
                                                                     bool defs) {
            if (defs && !setAppDefaults(active, exclude)) { return false; }
            active->hasConfig = 1;
            return true;

        }

        static inline bool isOption(int k) { return k >= option_category_nodes_end && k < detail__num_options; }

// Type for storing one command-line option.
        class GroundPlogCliConfig::ProgOption : public ProgramOptions::Value {
        public:
            ProgOption(GroundPlogCliConfig &c, int o) : ProgramOptions::Value(0), config_(&c), option_(o) {}

            bool doParse(const std::string &opt, const std::string &value) {
                int ret = isOption(option_) ? config_->setActive(option_, value.c_str()) : throw "not implemented";
                if (ret == -1) {
                    throw ProgramOptions::UnknownOption(config_->isGenerator() ? "<plog>" : throw "not implemented", opt);
                }
                return ret > 0;
            }

            int option() const { return option_; }

        private:
            GroundPlogCliConfig *config_;
            int option_;
        };


        bool GroundPlog::Cli::GroundPlogCliConfig::setAppDefaults(GroundPlog::GroundPlogConfig::UserConfig *active,
                                                                  const GroundPlog::Cli::GroundPlogCliConfig::ParsedOpts &exclude) {

            // there is no no modes and no solver ids, so we just return true
            return true;
        }

        void GroundPlog::Cli::GroundPlogCliConfig::addOptions(ProgramOptions::OptionContext &root) {
            createOptions();
            using namespace ProgramOptions;
            OptionGroup configOpts("Clasp.Config Options");
            OptionGroup solving("Clasp.Solving Options");
            OptionGroup asp("Clasp.ASP Options");
            OptionGroup search("Clasp.Search Options", ProgramOptions::desc_level_e1);
           configOpts.addOption(*opts_->begin());
            configOpts.addOption(*(opts_->end() - 1));
            for (Options::option_iterator it = opts_->begin() + 1, end = opts_->end() - 1; it != end; ++it) {
                int oId = static_cast<ProgOption *>(it->get()->value())->option();
                if (oId < option_category_global_end) { configOpts.addOption(*it); }
                else if (oId < option_category_solver_end) { solving.addOption(*it); }
                else if (oId < option_category_search_end) { search.addOption(*it); }
                else if (oId < option_category_asp_end) { asp.addOption(*it); }
                else { solving.addOption(*it); }
            }
            root.add(configOpts).add(solving).add(asp).add(search);

        }


        void GroundPlog::Cli::GroundPlogCliConfig::createOptions() {
            if (opts_.get()) { return; }
            opts_ = new Options();
            using namespace ProgramOptions;

            opts_->addOptions()("configuration",
                                createOption(meta_config)->defaultsTo("auto")->state(Value::value_defaulted),
                                "We need a description here");
            std::string cmdName;
#define CLASP_CONTEXT_OPTIONS
#define CLASP_GLOBAL_OPTIONS
#define CLASP_SOLVE_OPTIONS
#define CLASP_ASP_OPTIONS
#define CLASP_SOLVER_OPTIONS
#define CLASP_SEARCH_OPTIONS
#define OPTION(k, e, a, d, ...) keyToCliName(cmdName, #k, e); opts_->addOptions()(cmdName.c_str(),static_cast<ProgOption*>( createOption(opt_##k)a ), d);
#define ARG(a) ->a
#define ARG_EXT(a, X) ARG(a)
#define NO_ARG

#include <groundplog/cli/groundplog_cli_options.inl>

            opts_->addOptions()("tester", createOption(meta_tester)->arg("<options>"),
                                "Pass (quoted) string of %A to tester");

        }

        int GroundPlogCliConfig::setActive(int o, const char *value) {
            if      (isOption(o))     { return applyActive(o, value ? value : "", 0, 0, 0); }
            else throw "not implemented yet";
        }

        int GroundPlogCliConfig::applyActive(int o, const char *setValue, std::string *getValue, const char **getDesc,
                                             const char **name) {
            throw "not implemented yet";
        }

        GroundPlogCliConfig::ProgOption *GroundPlogCliConfig::createOption(int o) {
            return new ProgOption(*this, o);
        }

        void GroundPlogCliConfig::releaseOptions() {
            opts_=0;
        }

    }
}
