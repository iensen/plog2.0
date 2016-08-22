
#include <groundplog/cli/groundplog_options.h>
#include <program_opts/program_options.h>


bool GroundPlog::Cli::GroundPlogCliConfig::validate() {
    // nothing to validate
    return true;
}

bool GroundPlog::Cli::GroundPlogCliConfig::finalize(const ProgramOptions::ParsedOptions &parsed, bool applyDefaults) {
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

bool GroundPlog::Cli::GroundPlogCliConfig::setAppDefaults(GroundPlog::GroundPlogConfig::UserConfig *active,
                                                          const GroundPlog::Cli::GroundPlogCliConfig::ParsedOpts &exclude) {

    // there is no no modes and no solver ids, so we just return true
    return true;
}


