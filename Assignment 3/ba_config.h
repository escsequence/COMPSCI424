/**
 * ba - (Bankers Algorithm)
 * ba_config.h
 * Author: James Johnston
 *
 * Allows us to structure our config data from the file, into a more unified structure.
 * Each entry in the file is a config item that hold data and a config_flag.
 */
#ifndef BA_CONFIG_H
#define BA_CONFIG_H
namespace ba {
  /**
   * config_flag enumerator
   *
   * CF_INVALID - Invalid configuration entry.
   * CF_AVAILABLE - Entry indicates that is for the available array.
   * CF_MAX - Entry indicates that is for the maximum array.
   * CF_ALLOCATION - Entry indicates that is for the allocation array.
   * CF_REQUEST - Entry indicates that is for the request array.
   */
  enum config_flag {
    CF_INVALID,
    CF_AVAILABLE,
    CF_MAX,
    CF_ALLOCATION,
    CF_REQUEST
  };

  /**
   * config structure
   *
   * Used to structure the value array of the data we are loading from a config file.
   */
  struct config {
    int* value;
    config_flag flag;
  };
}
#endif
