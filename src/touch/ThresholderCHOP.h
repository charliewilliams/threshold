//
//  ThresholderCHOP.h
//  threshold
//
//  Created by tekt on 1/9/15.
//
//

#ifndef __threshold__ThresholderCHOP__
#define __threshold__ThresholderCHOP__

#include <string>
#include <vector>
#include <utility>

#include "ChopCPP_wrapper.h"
#include "CHOP_CPlusPlusBase.h"

#include "Thresholder.h"
#include "TouchCommon.h"
#include "PointSet.h"
#include "LineSet.h"

using namespace TD;

typedef std::pair<int, int> IndexPair;

struct OutputChannel {
  std::string outName;
  int outIndex;
  bool isStart;
  IndexPair sourceIndex;
};

using TouchThresholder = Thresholder<TouchPoint, CHOPInputPointSet>;

class ThresholderCHOP : public CHOP_CPlusPlusBase {

  //enum {
  //  INFO_ROW_WARNING,
  //  INFO_ROW_RESULT,

  //  NUM_INFO_ROWS
  //};
public:
  explicit ThresholderCHOP(const TD::OP_NodeInfo* info);
  virtual ~ThresholderCHOP() {}
    
    virtual void        getGeneralInfo(CHOP_GeneralInfo*, const TD::OP_Inputs*, void*) override;
    virtual bool        getOutputInfo(CHOP_OutputInfo*, const TD::OP_Inputs*, void*) override;
    virtual void        getChannelName(int32_t index, OP_String *name, const TD::OP_Inputs*, void*) override;

    virtual void        execute(CHOP_Output*, const TD::OP_Inputs*, void*) override;

    virtual void        setupParameters(OP_ParameterManager* manager, void*) override;

  virtual void		pulsePressed(const char* name, void* reserved1) override;
    
private:
  void loadParameters(OP_Inputs* inputs);
  bool shouldLoadChannels(OP_Inputs* inputs) const;
  void loadChannels(OP_Inputs* inputs);
  void loadChannelsSeparate(OP_Inputs* inputs);
  void outputLineSingle(const ThreshLine& line,
                        std::size_t i,
                        float** channels,
                        OP_Inputs *inputs) const;
  void outputLineSeparate(const ThreshLine& line,
                          std::size_t i,
                          float** channels,
                          OP_Inputs *inputs) const;
  
  TouchThresholder _thresholder;
  LineSet _lines;
  OutputChannel _xChannel;
  OutputChannel _yChannel;
  OutputChannel _zChannel;
  IndexPair _xInputIndex;
  IndexPair _yInputIndex;
  IndexPair _zInputIndex;
  IndexPair _groupIndex;
  std::vector<OutputChannel> _pointChannels;
  bool _resetChans;
  //SimpleInfoTable<NUM_INFO_ROWS> _debugInfo;
  bool _debugEnabled;
  std::string _error;
  std::string _warning;
  std::string _info;
};

#endif /* defined(__threshold__ThresholderCHOP__) */
