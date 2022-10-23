#pragma once

#include "convert.h"
#include "file_io.h"
#include "stream_io.h"
#include "types.h"

namespace convert {

void convert_file_batch(const streamio::provider &ios,
                        const std::vector<std::string> &filenames,
                        const format_config &config, output_type outtype);

bool convert_next(const streamio::provider &ios, const format_config &config,
                  input_type intype, output_type outtype);

class engine : public interface {
public:
  engine(convert_config config_);

  void run() const override;

private:
  void run_loop() const;

  std::unique_ptr<fileio::provider> m_fileio;
  convert_config m_config;
  streamio::provider m_streamio;
};

} // namespace convert

namespace streamio {
provider get_stream_provider(fileio::provider &fileio,
                             const convert_config &config);
}