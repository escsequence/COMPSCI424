#ifndef BA_CONFIG_H
#define BA_CONFIG_H
namespace ba {
  enum config_flag {
    CF_INVALID,
    CF_AVAILABLE,
    CF_MAX,
    CF_ALLOCATION,
    CF_REQUEST
  };
  struct config {
    int* value;
    config_flag flag;
  };
}
#endif
