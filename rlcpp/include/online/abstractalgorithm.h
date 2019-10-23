#ifndef __ABSTRACTALGO_H__
#define __ABSTRACTALGO_H__

#import "utils.h"

namespace online
{
  class Algorithm
  {
  public:
      Algorithm(/* args */){};
      ~Algorithm(){};

      virtual void reset()=0;
      virtual int run_episode(const utils::vec::vec_2d& trueV) = 0;

  };
}
#endif
