#include <sstream>
#include <stdexcept>
#include <esp_log.h>
#include <esp_spiffs.h>

#include "spiffs.h"
using namespace IDF;
using namespace std;

static const char *TAG = "Spiffs++";

Spiffs::Spiffs(const string basePath,
               const string partitionLabel,
               const int maxFilesOpen,
               const bool formatIfMountFailed)
    : _basePath{basePath},
      _partitionLabel{partitionLabel},
      _maxFilesOpen{maxFilesOpen},
      _formatIfMountFailed{formatIfMountFailed}
{
  if (_maxFilesOpen <= 0)
  {
    ESP_LOGE(TAG, "parameter maxFilesOpen must be greater than zero. got: %d", _maxFilesOpen);
#ifdef CONFIG_COMPILER_CXX_EXCEPTIONS
    throw std::invalid_argument("maxFilesOpen");
#else
    abort();
#endif
  }
}

void Spiffs::Register()
{
  ESP_LOGI(TAG, "Initializing SPIFFS");

  esp_vfs_spiffs_conf_t conf;
  conf.base_path = _basePath.c_str();
  conf.partition_label = _partitionLabel.empty() ? NULL : _partitionLabel.c_str();
  conf.max_files = _maxFilesOpen;
  conf.format_if_mount_failed = _formatIfMountFailed;

  esp_err_t ret = esp_vfs_spiffs_register(&conf);

  if (ret != ESP_OK)
  {
    if (ret == ESP_FAIL)
    {
      ESP_LOGE(TAG, "Failed to mount or format filesystem. (%s)", esp_err_to_name(ret));
    }
    else if (ret == ESP_ERR_NOT_FOUND)
    {
      ESP_LOGE(TAG, "Failed to find SPIFFS partition (%s)", esp_err_to_name(ret));
    }
    else
    {
      ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
    }
#ifdef CONFIG_COMPILER_CXX_EXCEPTIONS
    stringstream s{"Could not initialize SPIFFS: "};
    s << esp_err_to_name(ret);
    runtime_error ex(s.str());
    throw &ex;
#else
    abort();
#endif
  }

  size_t total = 0, used = 0;
  ret = esp_spiffs_info(conf.partition_label, &total, &used);
  if (ret != ESP_OK)
  {
    ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
  }
  else
  {
    ESP_LOGI(TAG, "Partition size: total: %d, used %d", total, used);
  }
}

void Spiffs::Unregister()
{
  esp_vfs_spiffs_unregister(_partitionLabel.empty() ? NULL : _partitionLabel.c_str());
}
