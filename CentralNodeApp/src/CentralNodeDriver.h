#ifndef CENTRALNODEDRIVER_H
#define CENTRALNODEDRIVER_H

#include <string>
#include <map>
#include <stdio.h>

#include <central_node_bypass.h>
#include <central_node_firmware.h>
#include <asynPortDriver.h>

// Environment variables
#define MPS_ENV_CONFIG_PATH                        "MPS_ENV_CONFIG_PATH"
#define MPS_ENV_FW_CONFIG                          "MPS_ENV_FW_CONFIG"
#define MPS_ENV_HISTORY_HOST                       "MPS_ENV_HISTORY_HOST"
#define MPS_ENV_HISTORY_PORT                       "MPS_ENV_HISTORY_PORT"
#define MPS_ENV_UPDATE_TIMEOUT                     "MPS_ENV_UPDATE_TIMEOUT"

// List of ASYN parameter names
#define MPS_CONFIG_LOAD_STRING                     "MPS_CONFIG_LOAD"
#define MPS_DEVICE_INPUT_STRING                    "MPS_DEVICE_INPUT"
#define MPS_ANALOG_DEVICE_STRING                   "MPS_ANALOG_DEVICE"
#define MPS_SW_MITIGATION_STRING                   "MPS_SW_MITIGATION"
#define MPS_FAULT_STRING                           "MPS_FAULT"
#define MPS_FAULT_IGNORED_STRING                   "MPS_FAULT_IGNORED"
#define MPS_FAULT_LATCHED_STRING                   "MPS_FAULT_LATCHED"
#define MPS_FAULT_UNLATCH_STRING                   "MPS_FAULT_UNLATCH"
#define MPS_FAULT_STATE_STRING                     "MPS_FAULT_STATE"
#define MPS_FAULT_STATE_IGNORED_STRING             "MPS_FAULT_STATE_IGNORED"
#define MPS_DEVICE_INPUT_LATCHED_STRING            "MPS_DEVICE_INPUT_LATCHED"
#define MPS_DEVICE_INPUT_UNLATCH_STRING            "MPS_DEVICE_INPUT_UNLATCH"
#define MPS_DEVICE_INPUT_BYPV_STRING               "MPS_DEVICE_INPUT_BYPV"
#define MPS_DEVICE_INPUT_BYPS_STRING               "MPS_DEVICE_INPUT_BYPS"
#define MPS_DEVICE_INPUT_BYPEXPDATE_STRING         "MPS_DEVICE_INPUT_BYPEXPDATE"
#define MPS_DEVICE_INPUT_REMAINING_BYPTIME_STRING  "MPS_DEVICE_INPUT_REMAINING_BYPTIME"
#define MPS_DEVICE_INPUT_BYPEXPDATE_STRING_STRING  "MPS_DEVICE_INPUT_BYPEXPDATE_STRING"
#define MPS_ANALOG_DEVICE_LATCHED_STRING           "MPS_ANALOG_DEVICE_LATCHED"
#define MPS_ANALOG_DEVICE_UNLATCH_STRING           "MPS_ANALOG_DEVICE_UNLATCH"
#define MPS_ANALOG_DEVICE_BYPV_STRING              "MPS_ANALOG_DEVICE_BYPV"
#define MPS_ANALOG_DEVICE_BYPS_STRING              "MPS_ANALOG_DEVICE_BYPS"
#define MPS_ANALOG_DEVICE_BYPEXPDATE_STRING        "MPS_ANALOG_DEVICE_BYPEXPDATE"
#define MPS_ANALOG_DEVICE_REMAINING_BYPTIME_STRING "MPS_ANALOG_DEVICE_REMAINING_BYPTIME"
#define MPS_ANALOG_DEVICE_BYPEXPDATE_STRING_STRING "MPS_ANALOG_DEVICE_BYPEXPDATE_STRING"
#define MPS_ANALOG_DEVICE_IGNORED_STRING           "MPS_ANALOG_DEVICE_IGNORED"
#define MPS_ANALOG_DEVICE_IGNORED_INTEGRATOR_STRING "MPS_ANALOG_DEVICE_IGNORED_INTEGRATOR"
#define MPS_UNLATCH_ALL_STRING                     "MPS_UNLATCH_ALL"
#define MPS_FW_BUILD_STAMP_STRING_STRING           "MPS_FW_BUILD_STAMP_STRING"
#define MPS_ENABLE_STRING                          "MPS_ENABLE"
#define MPS_ENABLE_RBV_STRING                      "MPS_ENABLE_RBV"
#define MPS_SW_ENABLE_STRING                       "MPS_SW_ENABLE"
#define MPS_SW_ENABLE_RBV_STRING                   "MPS_SW_ENABLE_RBV"
#define MPS_FAULT_REASON_STRING                    "MPS_FAULT_REASON"
#define MPS_SW_UPDATE_RATE_STRING                  "MPS_SW_UPDATE_RATE"
#define MPS_TIMING_CHECK_ENABLE_STRING             "MPS_TIMING_CHECK_ENABLE"
#define MPS_TIMING_CHECK_ENABLE_RBV_STRING         "MPS_TIMING_CHECK_ENABLE_RBV"
#define MPS_FW_MITIGATION_STRING                   "MPS_FW_MITIGATION"
#define MPS_MITIGATION_STRING                      "MPS_MITIGATION"
#define MPS_SW_UPDATE_COUNTER_STRING               "MPS_SW_UPDATE_COUNTER"
#define MPS_ENGINE_START_TIME_STRING_STRING        "MPS_ENGINE_START_TIME_STRING"
#define MPS_LATCHED_MITIGATION_STRING              "MPS_LATCHED_MITIGATION"
#define MPS_MITIGATION_UNLATCH_STRING              "MPS_MITIGATION_UNLATCH"
#define MPS_APP_STATUS_STRING                      "MPS_APP_STATUS"
#define MPS_APP_TIMESTAMP_LOW_BITS_STRING          "MPS_APP_TIMESTAMP_LOW_BITS"
#define MPS_APP_TIMESTAMP_HIGH_BITS_STRING         "MPS_APP_TIMESTAMP_HIGH_BITS"
#define MPS_EVALUATION_ENABLE_STRING               "MPS_EVALUATION_ENABLE"
#define MPS_EVALUATION_ENABLE_RBV_STRING           "MPS_EVALUATION_ENABLE_RBV"
#define MPS_MON_ERR_CLEAR_STRING                   "MPS_MON_ERR_CLEAR"
#define MPS_SW_ERR_CLEAR_STRING                    "MPS_SW_ERR_CLEAR"
#define MPS_TO_ERR_CLEAR_STRING                    "MPS_TO_ERR_CLEAR"
#define MPS_MO_CONC_ERR_CLEAR_STRING               "MPS_MO_CONC_ERR_CLEAR"
#define MPS_BEAM_FAULT_CLEAR_STRING                "MPS_BEAM_FAULT_CLEAR"
#define MPS_TIMEOUT_ENABLE_STRING                  "MPS_TIMEOUT_ENABLE"
#define MPS_TIMEOUT_ENABLE_RBV_STRING              "MPS_TIMEOUT_ENABLE_RBV"
#define MPS_EVALCYCLE_AVG_TIME_STRING              "MPS_EVALCYCLE_AVG_TIME"
#define MPS_EVALCYCLE_MAX_TIME_STRING              "MPS_EVALCYCLE_MAX_TIME"
#define MPS_EVAL_AVG_TIME_STRING                   "MPS_EVAL_AVG_TIME"
#define MPS_EVAL_MAX_TIME_STRING                   "MPS_EVAL_MAX_TIME"
#define MPS_UPDATE_AVG_TIME_STRING                 "MPS_UPDATE_AVG_TIME"
#define MPS_UPDATE_MAX_TIME_STRING                 "MPS_UPDATE_MAX_TIME"
#define MPS_UPDATE_TIME_CLEAR_STRING               "MPS_UPDATE_TIME_CLEAR"
#define MPS_FWUPDATE_AVG_PERIOD_STRING             "MPS_FWUPDATE_AVG_PERIOD"
#define MPS_FWUPDATE_MAX_PERIOD_STRING             "MPS_FWUPDATE_MAX_PERIOD"
#define MPS_WDUPDATE_AVG_PERIOD_STRING             "MPS_WDUPDATE_AVG_PERIOD"
#define MPS_WDUPDATE_MAX_PERIOD_STRING             "MPS_WDUPDATE_MAX_PERIOD"
#define MPS_CONFIG_DB_SRC_STRING                   "MPS_CONFIG_DB_SRC"
#define MPS_CONFIG_DB_USER_STRING                  "MPS_CONFIG_DB_USER"
#define MPS_CONFIG_DB_DATE_STRING                  "MPS_CONFIG_DB_DATE"
#define MPS_CONFIG_DB_MD5SUM_STRING                "MPS_CONFIG_DB_MD5SUM"
#define MPS_STATE_STRING                           "MPS_STATE"
#define MPS_CONDITION_STRING                       "MPS_CONDITION"
#define MPS_FW_SOFTWARE_WDOG_COUNTER_STRING        "MPS_FW_SOFTWARE_WDOG_COUNTER"
#define MPS_FW_MONITOR_NOT_READY_COUNTER_STRING    "MPS_FW_MONITOR_NOT_READY_COUNTER"
#define MPS_SKIP_HEARTBEAT_STRING                  "MPS_SKIP_HEARTBEAT"
#define MPS_FORCE_LINAC_PC0_STRING                 "MPS_FORCE_LINAC_PC0"

#define TEST_DEVICE_INPUT_STRING               "TEST_DEVICE_INPUT"
#define TEST_ANALOG_DEVICE_STRING              "TEST_ANALOG_DEVICE"
#define TEST_CHECK_FAULTS_STRING               "TEST_CHECK_FAULTS"
#define TEST_CHECK_BYPASS_STRING               "TEST_CHECK_BYPASS"

enum CentralNodeState {
  MPS_STATE_IDLE,
  MPS_STATE_RUNNING,
  MPS_STATE_LOAD_CONFIG,
  MPS_STATE_LOAD_CONFIG_ERROR,
};

class CentralNodeDriver : public asynPortDriver {
public:
  CentralNodeDriver(const char *portname, std::string configPath,
		    std::string historyServer, int historyPort);
  virtual ~CentralNodeDriver();

  /* virtual asynStatus drvUserCreate(asynUser *pasynUser, const char *drvInfo, const char **ppTypeName, */
  /* 				   size_t *psize); */
  //virtual asynStatus readOctet(asynUser *pasynUser, char *value, size_t maxChars, size_t *nActual);
  virtual asynStatus writeOctet(asynUser *pasynUser, const char *value, size_t maxChars, size_t *nActual);
  virtual asynStatus readInt32(asynUser *pasynUser, epicsInt32 *value);
  virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
  virtual asynStatus readUInt32Digital(asynUser *pasynUser, epicsUInt32 *value, epicsUInt32 mask);
  virtual asynStatus writeUInt32Digital(asynUser *pasynUser, epicsUInt32 value, epicsUInt32 mask);

  virtual void report(FILE *fp, int details);

  void printQueue();
  void showMitigation();
  void showFaults();
  void showFirmware();
  void showDatabaseInfo();
  void showEngineInfo();

 private:
  std::string _configPath;
  uint32_t _inputUpdateTimeout;

  // List of ASYN parameters
  int _mpsConfigLoadParam;
  int _mpsDeviceInputParam;
  int _mpsAnalogDeviceParam;
  int _mpsSwMitigationParam;
  int _mpsFaultParam;
  int _mpsFaultIgnoredParam;
  int _mpsFaultLatchedParam;
  int _mpsFaultUnlatchParam;
  int _mpsFaultStateParam;
  int _mpsFaultStateIgnoredParam;
  int _mpsDeviceInputLatchedParam;
  int _mpsDeviceInputUnlatchParam;
  int _mpsDeviceInputBypassValueParam;
  int _mpsDeviceInputBypassStatusParam;
  int _mpsDeviceInputBypassExpirationDateParam;
  int _mpsDeviceInputBypassRemainingExpirationTimeParam;
  int _mpsDeviceInputBypassExpirationDateStringParam;
  int _mpsAnalogDeviceLatchedParam;
  int _mpsAnalogDeviceUnlatchParam;
  int _mpsAnalogDeviceBypassValueParam;
  int _mpsAnalogDeviceBypassStatusParam;
  int _mpsAnalogDeviceBypassExpirationDateParam;
  int _mpsAnalogDeviceBypassRemainingExpirationTimeParam;
  int _mpsAnalogDeviceBypassExpirationDateStringParam;
  int _mpsAnalogDeviceIgnoredParam;
  int _mpsAnalogDeviceIgnoredIntegratorParam;
  int _mpsUnlatchAllParam;
  int _mpsFwBuildStampParam;
  int _mpsEnableParam;
  int _mpsEnableRbvParam;
  int _mpsSwEnableParam;
  int _mpsSwEnableRbvParam;
  int _mpsFaultReasonParam;
  int _mpsUpdateRateParam;
  int _mpsTimingCheckEnableParam;
  int _mpsTimingCheckEnableRbvParam;
  int _mpsFwMitigationParam;
  int _mpsMitigationParam;
  int _mpsUpdateCounterParam;
  int _mpsEngineStartTimeStringParam;
  int _mpsLatchedMitigationParam;
  int _mpsMitigationUnlatchParam;
  int _mpsAppStatusParam;
  int _mpsAppTimestampLowBitsParam;
  int _mpsAppTimestampHighBitsParam;
  int _mpsEvaluationEnableParam;
  int _mpsEvaluationEnableRbvParam;
  int _mpsMonErrClearParam;
  int _mpsSwErrClearParam;
  int _mpsToErrClearParam;
  int _mpsMoConcErrClearParam;
  int _mpsBeamFaultClearParam;
  int _mpsTimeoutEnableParam;
  int _mpsTimeoutEnableRbvParam;
  int _mpsEvalAvgParam;
  int _mpsEvalMaxParam;
  int _mpsEvalCycleAvgParam;
  int _mpsEvalCycleMaxParam;
  int _mpsUpdateAvgParam;
  int _mpsUpdateMaxParam;
  int _mpsUpdateClearParam;
  int _mpsFwUpdateAvgParam;
  int _mpsFwUpdateMaxParam;
  int _mpsWdUpdateAvgParam;
  int _mpsWdUpdateMaxParam;
  int _mpsConfigDbSourceParam;
  int _mpsConfigDbUserParam;
  int _mpsConfigDbDateParam;
  int _mpsConfigDbMd5SumParam;
  int _mpsStateParam;
  int _mpsConditionParam;
  int _mpsFwSoftwareWdogCounterParam;
  int _mpsFwMonitorNotReadyCounterParam;
  int _mpsSkipHeartbeatParam;
  int _mpsForceLinacPc0Param;

  int _testDeviceInputParam;
  int _testAnalogDeviceParam;
  int _testCheckFaultsParam;
  int _testCheckBypassParam;

  //  CentralNodeState _mpsState;

  asynStatus loadConfig(const char *config);
  asynStatus loadTestDeviceInputs(const char *testFileName);
  asynStatus loadTestAnalogDevices(const char *testFileName);

  asynStatus setBypass(BypassType bypassType, int deviceId, int thresholdIndex, epicsInt32 expirationTime);

  int getParamStringOffset(int deviceIndex, int thresholdIndex);
};

#endif
