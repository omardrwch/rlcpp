#ifndef __ABSTRACTALGO_H__
#define __ABSTRACTALGO_H__

#include "utils.h"

namespace online
{
  /**
   * @brief Abstract class for online RL algorithms.
   */
  class Algorithm
  {
  public:
      Algorithm(/* args */){};
      ~Algorithm(){};

      /**
       * @brief Reset algorithm
       */
      virtual void reset()=0;
      /**
       * @brief Run one episode.
       */
      virtual int run_episode()=0;
  };
}
#endif
