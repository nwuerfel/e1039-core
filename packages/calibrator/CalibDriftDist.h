#ifndef __CALIB_DRIFT_DIST_H__
#define __CALIB_DRIFT_DIST_H__
#include <fun4all/SubsysReco.h>
class SQHitVector;
class CalibParamXT;

/// SubsysReco module to calibrate the drift distance and also the in-time window of the chambers and the prop tube.
/**
 * This module automatically selects a proper set of calibration parameters based on the run number.
 * Only when necessary, you can manually give a parameter set via `ReadParamFromFile()`.
 */
class CalibDriftDist: public SubsysReco {
  bool m_manual_map_selection;
  std::string m_fn_xt;
  SQHitVector* m_vec_hit;
  CalibParamXT* m_cal_xt;

 public:
  CalibDriftDist(const std::string &name = "CalibDriftDist");
  virtual ~CalibDriftDist();
  int Init(PHCompositeNode *topNode);
  int InitRun(PHCompositeNode *topNode);
  int process_event(PHCompositeNode *topNode);
  int End(PHCompositeNode *topNode);

  void ReadParamFromFile(const char* fn_xt_curve);
  CalibParamXT* GetParamXT() { return m_cal_xt; }
};

#endif // __CALIB_DRIFT_DIST_H__
