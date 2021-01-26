#ifndef COMPONENT_H

namespace IDF
{
   class Spiffs
   {
   public:
   private:
      void setup() override;
      void loop() override;
      void cleanup() override;
   }; // class Component
} // namespace IDF
#define COMPONENT_H
#endif // COMPONENT_H