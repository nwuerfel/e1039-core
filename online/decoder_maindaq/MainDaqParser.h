#ifndef _MAIN_DAQ_PARSER_H_
#define _MAIN_DAQ_PARSER_H_
#include "DecoData.h"
#include "DecoParam.h"
#include "DecoError.h"
class CodaInputManager;
class PHTimer;

class MainDaqParser {
  static const std::vector<std::string> LIST_TIMERS;

  long m_file_size_min;
  int m_sec_wait;
  int m_n_wait;
  CodaInputManager* coda;

  /// Variables for data storage
  RunData run_data;
  SpillDataMap* list_sd;
  EventDataMap* list_ed;
  
  SpillData   * sd_now; //< Contain the spill info of the current spill
  EventDataMap* list_ed_now; //< Contain the event info only in the current spill

  std::map<std::string, PHTimer*> m_timers; // [timer name]

  // Handlers of CODA Event
  int ProcessCodaPrestart   (int* words);
  int ProcessCodaEnd        (int* words);
  int ProcessCodaFee        (int* words);
  int ProcessCodaFeeBoard   (int* words);
  int ProcessCodaFeePrescale(int* words);
  int ProcessCodaPhysics    (int* words);

  // Handlers of CODA PHYSICS Event
  int ProcessPhysRunDesc     (int* words);
  int ProcessPhysPrestart    (int* words);
  int ProcessPhysSlow        (int* words);
  int ProcessPhysSpillCounter(int* words);
  int ProcessPhysBOSEOS      (int* words, const int event_type);
  int ProcessPhysStdAndFlush (int* words, const int event_type);

  // Handlers of Board data in flush event
  int ProcessBoardData        (int* words, int idx, int idx_roc_end, int e906flag, const int event_type);
  int ProcessBoardScaler      (int* words, int j);
  int ProcessBoardTriggerBit  (int* words, int j, int idx_roc_end);
  int ProcessBoardTriggerCount(int* words, int j);
  int ProcessBoardFeeQIE      (int* words, int j);
  int ProcessBoardV1495TDC    (int* words, int idx);
  int ProcessBoardJyTDC2      (int* words, int idx_begin, int idx_roc_end);

  int ProcessBoardStdTriggerBit  (int* words, int idx);
  int ProcessBoardStdTriggerCount(int* words, int idx);
  int ProcessBoardStdFeeQIE      (int* words, int idx);
  int ProcessBoardStdV1495TDC    (int* words, int idx);
  int ProcessBoardStdJyTDC2      (int* words, int idx_begin, int idx_roc_end);

  int PackOneSpillData();
  int ParseOneSpill();
  void SetEventInfo(EventInfo* evt, const int eventID);

public:
  typedef enum {
    TYPE_BOS = 1,
    TYPE_EOS = 2
  } SpillType_t;

  MainDaqParser();
  ~MainDaqParser();

  CodaInputManager* GetCoda() { return coda; }
  int OpenCodaFile(const std::string fname, const long file_size_min=32768, const int sec_wait=15, const int n_wait=40);
  bool NextPhysicsEvent(EventData*& ed, SpillData*& sd, RunData*& rd);
  RunData* GetRunData() { return &run_data; }
  int End();

  DecoParam dec_par;
  DecoError dec_err;
};

#endif // _MAIN_DAQ_PARSER_H_
