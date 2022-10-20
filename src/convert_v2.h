#pragma once

#include "convert.h"
#include "file_io.h"
#include "stream_io.h"

namespace convert {

class engine_v2 : public interface {
public:
  engine_v2(convert_config_v2 config_);

  void run() const override;
  bool proceed(const format_config &format) const;

private:
  void run_file_batch() const;
  void write(const std::string &str) const;

  std::unique_ptr<fileio::provider> fileio;
  convert_config_v2 config;
  streamio::provider iostream;
};

} // namespace convert