#pragma once

#include "convert.h"
#include "file_io.h"
#include "stream_wrap.h"

namespace convert {

class engine_v2 : public interface {
public:
  engine_v2(convert_config_v2 config_);

  void run() const override;
  bool proceed(const format_config &format) const;

private:
  void run_file_batch() const;
  void write(const std::string &str) const;

  std::unique_ptr<fileio::fstream_provider> file;
  convert_config_v2 config;
  stream_provider_v2 iostream;
};

} // namespace convert