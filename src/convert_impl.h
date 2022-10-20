#pragma once

#include "convert.h"
#include "file_io.h"
#include "stream_io.h"

namespace convert {

class engine : public interface {
public:
  engine(convert_config config_);

  void run() const override;
  bool proceed(const format_config &format) const;

private:
  void run_file_batch() const;

  std::unique_ptr<fileio::provider> m_fileio;
  convert_config m_config;
  streamio::provider m_streamio;
};

} // namespace convert