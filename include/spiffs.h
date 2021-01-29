#ifndef COMPONENT_H
#include <string>

namespace IDF
{
class Spiffs {
public:
  Spiffs(const std::string basePath       = "/spiffs",
         const std::string partitionLabel = "",
         const int MaxFilesOpen           = 5,
         const bool formatIfMountFailed   = true);

  void Register();
  void Unregister();
  void Format();
  bool IsMounted();

  size_t TotalSize();
  size_t UsedSize();

  std::string BasePath()
  {
    return _basePath;
  };
  std::string PartitionLabel()
  {
    return _partitionLabel;
  };
  int MaxFilesOpen()
  {
    return _maxFilesOpen;
  };
  bool FormatIfMountFailed()
  {
    return _formatIfMountFailed;
  };

private:
  const std::string _basePath       = "/spiffs";
  const std::string _partitionLabel = "";
  const int _maxFilesOpen           = 5;
  const bool _formatIfMountFailed   = true;
}; // class Spiffs
} // namespace IDF
#define COMPONENT_H
#endif // COMPONENT_H