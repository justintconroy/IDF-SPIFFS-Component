#ifndef COMPONENT_H
#include <string>
#include "TaskBase.h"

namespace IDF
{
   class Spiffs : public TaskBase
   {
   public:
   private:
      std::string _basePath = "/spiffs";
      std::string _partitionLabel = NULL;
      int _maxFiles = 5;
      bool _formatIfMountFailed = true;

      void setup() override;
      void loop() override;
      void cleanup() override;
   }; // class Component
} // namespace IDF
#define COMPONENT_H
#endif // COMPONENT_H